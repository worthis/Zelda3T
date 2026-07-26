#include "MapOverworld.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../../../config/ConfigurationManager.h"

MapOverworld::MapOverworld() : anim(0), animMax(1), vanim(480), started(false), xLink(0), yLink(0), lapin(false), offsetForme(0), offsetSkin(0)
{
    imageLink = ResourceManager::getInstance()->loadImage("data/images/maps/link.png", true);

    imageMap[0] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-1-1.png");
    imageMap[1] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-1-2.png");
    imageMap[2] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-1.png");
    imageMap[3] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-2.png");
    imageMap[4] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-3.png");
    imageMap[5] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-4.png");
    imageMap[6] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-3-1.png");
    imageMap[7] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-3-2.png");
    imageMapId = 3;
}

MapOverworld::~MapOverworld()
{
    ResourceManager::getInstance()->free(imageLink);
    for (int i = 0; i < 8; i++)
    {
        ResourceManager::getInstance()->free(imageMap[i]);
    }
}

void MapOverworld::handleActions(Action *action)
{
    if (!started)
        return;
    if (action->isAction(DISPLAY_MAP) || action->isAction(QUIT_GAME))
    {
        started = false;
        MainController::getInstance()->getGameController()->hideMap();
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
}

void MapOverworld::loop()
{
    if (!started)
        return;
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void MapOverworld::draw()
{
    WindowManager::getInstance()->draw(imageMap[imageMapId], 0, 0, 320, 240, 0, 0);
    if (anim == 0)
    {
        if (lapin)
        {
            WindowManager::getInstance()->draw(imageLink, 14, offsetSkin, 16, 15, xLink - 8, yLink - 6);
        }
        else
        {
            WindowManager::getInstance()->draw(imageLink, offsetForme, offsetSkin, 14, 12, xLink - 7, yLink - 8);
        }
    }
}

void MapOverworld::launch()
{
    offsetSkin = ConfigurationManager::getInstance()->getSkin() * 15;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    int mapId = scene->getMap()->getId();
    Link *link = scene->getLink();
    offsetForme = link->getStatus()->isOniLink() ? 30 : 0;
    lapin = link->isLapin();

    /*xLink = (8 * 20 * 16 + 21 * 16 + 8) / 18;
    yLink = ((6 * 15 * 16 + 24)/18);
} else if (mapId == 28) {*/
    if (mapId == 46 || mapId == 53)
    {
        xLink = (304 * 16) / 18;
        yLink = 8;
    }
    else if (mapId == 156)
    {
        xLink = 160;
        yLink = 60;
    }
    else
    {
        xLink = (getOffsetXForMap(mapId) * 20 * 16 + link->getX() + 8) / 18;
        yLink = (getOffsetYForMap(mapId) * 15 * 16 + link->getY() + 24) / 18;
    }
    switch (scene->getMap()->getEpoque())
    {
    case EP_PASSE:
        imageMapId = scene->getAvancement() < AV_TEMPLE_DEESSES_APPARU ? 0 : 1;
        break;
    case EP_PRESENT:
        if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PONT_CONSTRUIT)
            imageMapId = 2;
        else if (scene->getCoffre(0, 2))
            imageMapId = 5;
        else if (link->getInventory()->getTroc(TT_ROUAGE) == 0)
            imageMapId = 4;
        else
            imageMapId = 3;
        break;
    case EP_FUTUR:
        imageMapId = (!link->getInventory()->hasObject(FLECHE_FEU) || !link->getInventory()->hasObject(FLECHE_GLACE) || !link->getInventory()->hasObject(FLECHE_LUMIERE) || !link->getInventory()->hasObject(FLACON_4)) ? 6 : 7;
        break;
    default:
        break;
    }

    anim = 0;
    chrono.reset();

    started = true;
}

int MapOverworld::getOffsetXForMap(int mapId)
{
    switch (((mapId - 1) % 15) + 1)
    {
    case 1:
        return 0;
    case 2:
        return 4;
    case 3:
        return 7;
    case 4:
        return 7;
    case 5:
        return 11;
    case 6:
        return 14;
    case 7:
        return 11;
    case 8:
        return 7;
    case 9:
        return 11;
    case 10:
        return 14;
    case 11:
        return 7;
    case 12:
        return 0;
    case 13:
        return 0;
    case 14:
        return 4;
    case 15:
        return 0;
    default:
        return -1;
    }
}

int MapOverworld::getOffsetYForMap(int mapId)
{
    switch (((mapId - 1) % 15) + 1)
    {
    case 1:
        return 9;
    case 2:
        return 9;
    case 3:
        return 7;
    case 4:
        return 3;
    case 5:
        return 3;
    case 6:
        return 3;
    case 7:
        return 0;
    case 8:
        return 0;
    case 9:
        return 9;
    case 10:
        return 13;
    case 11:
        return 13;
    case 12:
        return 13;
    case 13:
        return 4;
    case 14:
        return 4;
    case 15:
        return 0;
    default:
        return -1;
    }
}
