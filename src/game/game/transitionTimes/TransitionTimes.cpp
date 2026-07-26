#include "TransitionTimes.h"

#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../MainController.h"
#include "../../content/link/Link.h"
#include "../scene/Scene.h"

TransitionTimes::TransitionTimes() : mapDestination(0), box(0), alpha(0), reset(false)
{
    imageJurassique = ResourceManager::getInstance()->loadImage("data/images/tileset/jurassique.png");
    imageApocalypse = ResourceManager::getInstance()->loadImage("data/images/tileset/apocalypse.png");

    ostringstream os;
    for (int i = 0; i < 3; i++)
    {
        os << (i + 1);
        string filenameForest = "data/images/tileset/foret" + os.str() + ".png";
        filterForest[i] = ResourceManager::getInstance()->loadImage(filenameForest);
        SDL_SetTextureBlendMode(filterForest[i]->getImage(), SDL_BLENDMODE_BLEND);
        filterForest[i]->setAlpha(128);
        string filenameRain = "data/images/tileset/pluie" + os.str() + ".png";
        filterRain[i] = ResourceManager::getInstance()->loadImage(filenameRain, true);
        string filenameSnow = "data/images/tileset/neige" + os.str() + ".png";
        filterSnow[i] = ResourceManager::getInstance()->loadImage(filenameSnow, true);
        string filenameSky = "data/images/tileset/fond" + os.str() + ".png";
        filterSky[i] = ResourceManager::getInstance()->loadImage(filenameSky);
        os.str("");
    }

    imageDestination = 0;
    sens = 0;
    destinationId = 0;
}

TransitionTimes::~TransitionTimes()
{
    ResourceManager::getInstance()->free(imageJurassique);
    ResourceManager::getInstance()->free(imageApocalypse);
    for (int i = 0; i < 3; i++)
    {
        ResourceManager::getInstance()->free(filterForest[i]);
        ResourceManager::getInstance()->free(filterRain[i]);
        ResourceManager::getInstance()->free(filterSnow[i]);
        ResourceManager::getInstance()->free(filterSky[i]);
    }
    ResourceManager::getInstance()->free(imageDestination);
}

void TransitionTimes::loop()
{
    if (reset)
    {
        alpha -= 4;
        if (alpha < 0)
            alpha = 0;
        if (alpha == 0)
        {
            delete mapDestination;
            MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
            AudioManager::getInstance()->replayMusic();
        }
    }
    else
    {
        if (sens > 1)
        {
            alpha += 2;
        }
        else
        {
            alpha += 4;
        }
        if (alpha > 255)
            alpha = 255;
        if (alpha == 255)
        {
            Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
            Link *link = scene->getLink();
            link->getStatus()->setInvincible();

            int dx = sens == 0 ? -1600 : 1600;
            if (destinationId == 156)
            {
                link->setX(link->getX() + dx);
            }

            if (destinationId > 0 && mapDestination->checkCollisions(link->getBoundingBox(), (Collisionable *)link, false, false, false, false, true, 0, 0, -1, -1, true) && !mapDestination->isOnWater(link->getBoundingBox()))
            {
                int boxX = box->getX();
                int boxY = box->getY();
                scene->setMap(mapDestination);
                scene->getCamera()->setX(boxX);
                scene->getCamera()->setY(boxY);

                scene->getAnimationInGame()->testAnim();
                mapDestination->launch();
                link->startNewMap();

                if (destinationId == 156)
                {
                    scene->getMap()->launchRoom();
                    scene->fixCameraBounds();
                    link->startNewRoom();
                }

                MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
            }
            else
            {
                if (destinationId == 156)
                {
                    link->setX(link->getX() - dx);
                }
                reset = true;
            }
        }
    }
}

void TransitionTimes::draw()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    box = scene->getCamera()->getBoundingBox();

    if (imageDestination == 0)
    {
        if (destinationId == -1)
        {
            WindowManager::getInstance()->draw(imageJurassique, 0, 0, 320, 240, 0, 0);
            link->draw(box->getX(), box->getY());
        }
        else if (destinationId == -2)
        {
            WindowManager::getInstance()->draw(imageApocalypse, 0, 0, 320, 240, 0, 0);
            link->draw(box->getX(), box->getY());
        }
        else
        {

            int dx = sens == 0 ? -1600 : 1600;
            if (destinationId == 156)
            {
                link->setX(link->getX() + dx);
                box->setX(box->getX() + dx);
            }

            if (mapDestination->getId() == 15 || mapDestination->getId() == 30 || mapDestination->getId() == 46 || mapDestination->getId() == 53)
            {
                WindowManager::getInstance()->draw(filterSky[0], 0, 0, 320, 240, 0, 0);
            }
            else if (mapDestination->getId() == 45)
            {
                WindowManager::getInstance()->draw(filterSky[1], 0, 0, 320, 240, 0, 0);
            }
            else if (mapDestination->getId() == 156)
            {
                WindowManager::getInstance()->draw(filterSky[2], 0, 0, 320, 240, 0, 0);
            }

            List toDraw;
            toDraw.add((Listable *)link);
            mapDestination->draw(&toDraw, box);

            if (mapDestination->getId() < 16 && scene->getAvancement() < AV_INFO_PASSE_OK)
            {
                WindowManager::getInstance()->draw(filterSnow[scene->getMetronome()->getValue() % 3], 0, 0, 320, 240, 0, 0);
            }
            if (mapDestination->getId() == 6)
            {
                filterForest[2]->setAlpha(128);
                WindowManager::getInstance()->draw(filterForest[2], (box->getX() / 2) % 256, (box->getY() / 2) % 256, 320, 240, 0, 0);
            }
            else if (mapDestination->getId() == 21)
            {
                filterForest[0]->setAlpha(128);
                WindowManager::getInstance()->draw(filterForest[0], (box->getX() / 2) % 256, (box->getY() / 2) % 256, 320, 240, 0, 0);
            }
            else if (mapDestination->getId() == 36)
            {
                filterForest[1]->setAlpha(128);
                int srcX = (box->getX() + (scene->getFiltreForest2() / 2)) % 256;
                int srcY = (box->getY() + (scene->getFiltreForest2() / 2)) % 256;
                WindowManager::getInstance()->draw(filterForest[1], srcX, srcY, 320, 240, 0, 0);
            }
            else if (mapDestination->getId() == 40)
            {
                WindowManager::getInstance()->draw(filterRain[scene->getMetronome()->getValue() % 3], 0, 0, 320, 240, 0, 0);
            }

            if (destinationId == 156)
            {
                link->setX(link->getX() - dx);
                box->setX(box->getX() - dx);
            }
        }
        imageDestination = WImage::createClip();
    }

    scene->draw();
    imageDestination->setAlpha(alpha);
    WindowManager::getInstance()->draw(imageDestination, 0, 0, 320, 240, 0, 0);
    scene->getHud()->draw();
}

void TransitionTimes::init()
{
    alpha = 0;
    reset = false;
    ResourceManager::getInstance()->free(imageDestination);
    mapDestination = 0;
    imageDestination = 0;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // second map
    destinationId = getSecondMapId(scene->getMap()->getId());
    if (destinationId > 0)
    {
        mapDestination = new Map(destinationId, scene->getMetronome());
        mapDestination->load();
    }
}

void TransitionTimes::setSens(int s)
{
    sens = s;
}

int TransitionTimes::getSecondMapId(int mapId)
{
    if (mapId == 156)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();
        if (sens == 0 && link->getX() < 1600)
        {
            return -1;
        }
        if (sens == 1 && link->getX() >= 3200)
        {
            return -2;
        }
        return mapId;
    }
    if (sens == 0)
    {
        return (mapId > 15) ? mapId - 15 : -1;
    }
    if (sens == 1)
    {
        return mapId < 31 ? mapId + 15 : -2;
    }
    if (sens == 2)
    {
        return 4;
    }
    return sens == 3 ? 21 : 9;
}
