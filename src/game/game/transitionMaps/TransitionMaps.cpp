#include "TransitionMaps.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../MainController.h"
#include "../../content/link/Link.h"
#include "../scene/Scene.h"

TransitionMaps::TransitionMaps() : offset(0), offsetMax(0), offsetX(0), offsetY(0), direction(N), map1(0), map2(0),
                                   box1(0), box2(0), alpha(0)
{
    filterNight = new WImage(320, 240, 0, 0, 255, 80);

    ostringstream os;
    for (int i = 0; i < 3; i++)
    {
        os << (i + 1);
        string filenameForest = "data/images/tileset/foret" + os.str() + ".png";
        filterForest[i] = ResourceManager::getInstance()->loadImage(filenameForest);
        SDL_SetTextureBlendMode(filterForest[i]->getImage(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(filterForest[i]->getImage(), 128);
        string filenameRain = "data/images/tileset/pluie" + os.str() + ".png";
        filterRain[i] = ResourceManager::getInstance()->loadImage(filenameRain, true);
        string filenameSnow = "data/images/tileset/neige" + os.str() + ".png";
        filterSnow[i] = ResourceManager::getInstance()->loadImage(filenameSnow, true);
        os.str("");
    }
}

TransitionMaps::~TransitionMaps()
{
    ResourceManager::getInstance()->free(filterNight);
    for (int i = 0; i < 3; i++)
    {
        ResourceManager::getInstance()->free(filterForest[i]);
        ResourceManager::getInstance()->free(filterRain[i]);
        ResourceManager::getInstance()->free(filterSnow[i]);
    }
}

void TransitionMaps::loop()
{

    if (map1->getId() == 6 || map2->getId() == 6 || map1->getId() == 21 || map2->getId() == 21 || map1->getId() == 36 || map2->getId() == 36)
    {
        if (map1->getId() == 6 || map1->getId() == 21 || map1->getId() == 36)
        {
            alpha -= 4;
            if (alpha < 0)
                alpha = 0;
        }
        if (map2->getId() == 6 || map2->getId() == 21 || map2->getId() == 36)
        {
            alpha += 4;
            if (alpha > 128)
                alpha = 128;
        }
        for (int i = 0; i < 3; i++)
            filterForest[i]->setAlpha(alpha);
    }

    offset += 8;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    switch (direction)
    {
    case N:
        box1->setH(240 - offset);
        box2->setY(map2->getH() - offset);
        box2->setH(offset);
        if (offset <= 80)
        {
            link->setY(link->getY() - 4);
        }
        break;
    case S:
        box1->setY(map1->getH() - 240 + offset);
        box1->setH(240 - offset);
        box2->setH(offset);
        if (offset <= 80)
        {
            link->setY(link->getY() + 4);
        }
        break;
    case W:
        box1->setW(320 - offset);
        box2->setX(map2->getW() - offset);
        box2->setW(offset);
        if (offset <= 80)
        {
            link->setX(link->getX() - 4);
        }
        break;
    case E:
        box1->setX(map1->getW() - 320 + offset);
        box1->setW(320 - offset);
        box2->setW(offset);
        if (offset <= 80)
        {
            link->setX(link->getX() + 4);
        }
        break;
    }
    if (offset >= offsetMax)
    {

        scene->setMap(map2); // setMap delete map1
        switch (direction)
        {
        case N:
            link->setX(link->getX() - offsetX * 320);
            link->setY(map2->getH() - 40);
            break;
        case S:
            link->setX(link->getX() - offsetX * 320);
            link->setY(8);
            break;
        case W:
            link->setX(map2->getW() - 32);
            link->setY(link->getY() - offsetY * 240);
            break;
        case E:
            link->setX(16);
            link->setY(link->getY() - offsetY * 240);
            break;
        }
        box1->setX(box2->getX());
        box1->setY(box2->getY());
        box1->setW(box2->getW());
        box1->setH(box2->getH());
        delete box2;
        box2 = 0;

        scene->getAnimationInGame()->testAnim();
        map2->launch();
        link->startNewMap();

        if (alpha != 128)
        {
            alpha = 128;
            for (int i = 0; i < 3; i++)
                filterForest[i]->setAlpha(alpha);
        }
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
    }
}

void TransitionMaps::draw()
{

    int dstX1 = 0;
    int dstX2 = 0;
    int dstY1 = 0;
    int dstY2 = 0;
    switch (direction)
    {
    case N:
        dstY1 = offset;
        dstY2 = 0;
        break;
    case S:
        dstY1 = 0;
        dstY2 = 240 - offset;
        break;
    case W:
        dstX1 = offset;
        dstX2 = 0;
        break;
    case E:
        dstX1 = 0;
        dstX2 = 320 - offset;
        break;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    List toDraw1;

    map1->draw(&toDraw1, box1, dstX1, dstY1);

    List toDraw2;

    map2->draw(&toDraw2, box2, dstX2, dstY2);

    link->draw(box1->getX() - dstX1, box1->getY() - dstY1);

    map1->drawAir(box1->getX(), box1->getY(), box1->getW(), box1->getH(), dstX1, dstY1);
    map2->drawAir(box2->getX(), box2->getY(), box2->getW(), box2->getH(), dstX2, dstY2);

    if (map1->getId() == 6)
    {
        WindowManager::getInstance()->draw(filterForest[2], (box1->getX() / 2) % 256, (box1->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if (map2->getId() == 6)
    {
        WindowManager::getInstance()->draw(filterForest[2], (box2->getX() / 2) % 256, (box2->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if (map1->getId() == 21)
    {
        WindowManager::getInstance()->draw(filterForest[0], (box1->getX() / 2) % 256, (box1->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if (map2->getId() == 21)
    {
        WindowManager::getInstance()->draw(filterForest[0], (box2->getX() / 2) % 256, (box2->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if (map1->getId() == 36)
    {
        int srcX = (box1->getX() + (scene->getFiltreForest2() / 2)) % 256;
        int srcY = (box1->getY() + (scene->getFiltreForest2() / 2)) % 256;
        WindowManager::getInstance()->draw(filterForest[1], srcX, srcY, 320, 240, 0, 0);
    }
    else if (map2->getId() == 36)
    {
        int srcX = (box2->getX() + (scene->getFiltreForest2() / 2)) % 256;
        int srcY = (box2->getY() + (scene->getFiltreForest2() / 2)) % 256;
        WindowManager::getInstance()->draw(filterForest[1], srcX, srcY, 320, 240, 0, 0);
    }
    else if (map1->getId() == 40 || map2->getId() == 40)
    {
        WindowManager::getInstance()->draw(filterRain[scene->getMetronome()->getValue() % 3], 0, 0, 320, 240, 0, 0);
    }

    if (map1->getId() < 16 && scene->getAvancement() < AV_INFO_PASSE_OK)
    {
        WindowManager::getInstance()->draw(filterSnow[scene->getMetronome()->getValue() % 3], 0, 0, 320, 240, 0, 0);
    }
    else if (map1->getId() >= 16 && map1->getId() < 31 && scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
    {
        WindowManager::getInstance()->draw(filterNight, 0, 0, 320, 240, 0, 0);
    }

    scene->getHud()->draw();
}

void TransitionMaps::init()
{
    offset = 0;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    map1 = scene->getMap();
    box1 = scene->getCamera()->getBoundingBox();

    // direction
    Link *link = scene->getLink();
    int x = link->getX();
    int y = link->getY();

    int offX = getOffsetXForMap(map1);
    int offY = getOffsetYForMap(map1);

    if (y <= 0 && offY > 0)
        direction = N;
    else if (y >= map1->getH() - 32 && offY < 18 - (map1->getH() / 240))
        direction = S;
    else if (x <= 8 && offX > 0)
        direction = W;
    else if (x >= map1->getW() - 32 && offX < 18 - (map1->getW() / 320))
        direction = E;

    if (direction == N || direction == S)
    {
        offsetMax = 240;
    }
    else
    {
        offsetMax = 320;
    }

    // second map
    map2 = new Map(getSecondMapId(x, y), scene->getMetronome());
    map2->load();

    offsetX = getOffsetXForMap(map2) - offX;
    offsetY = getOffsetYForMap(map2) - offY;

    box2 = new BoundingBox();
    switch (direction)
    {
    case N:
        box2->setX(box1->getX() - offsetX * 320);
        box2->setY(map2->getH());
        box2->setW(320);
        box2->setH(0);
        break;
    case S:
        box2->setX(box1->getX() - offsetX * 320);
        box2->setY(0);
        box2->setW(320);
        box2->setH(0);
        break;
    case W:
        box2->setX(map2->getW());
        box2->setY(box1->getY() - offsetY * 240);
        box2->setW(0);
        box2->setH(240);
        break;
    case E:
        box2->setX(0);
        box2->setY(box1->getY() - offsetY * 240);
        box2->setW(0);
        box2->setH(240);
        break;
    }

    if (map1->getId() == 6 || map2->getId() == 6)
    {
        if (map1->getId() == 6)
            alpha = 128;
        if (map2->getId() == 6)
            alpha = 0;
        SDL_SetTextureAlphaMod(filterForest[2]->getImage(), alpha);
    }
    if (map1->getId() == 21 || map2->getId() == 21)
    {
        if (map1->getId() == 21)
            alpha = 128;
        if (map2->getId() == 21)
            alpha = 0;
        SDL_SetTextureAlphaMod(filterForest[0]->getImage(), alpha);
    }
    if (map1->getId() == 36 || map2->getId() == 36)
    {
        if (map1->getId() == 36)
            alpha = 128;
        if (map2->getId() == 36)
            alpha = 0;
        SDL_SetTextureAlphaMod(filterForest[1]->getImage(), alpha);
    }
}

int TransitionMaps::getOffsetXForMap(Map *map)
{
    switch (((map->getId() - 1) % 15) + 1)
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

int TransitionMaps::getOffsetYForMap(Map *map)
{
    switch (((map->getId() - 1) % 15) + 1)
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

int TransitionMaps::getSecondMapId(int x, int y)
{
    int offset = ((int)((map1->getId() - 1) / 15)) * 15;
    switch (((map1->getId() - 1) % 15) + 1)
    {
    case 1:
        if (direction == N)
            return 13 + offset;
        if (direction == E)
            return 2 + offset;
        break;
    case 2:
        if (direction == N)
            return 14 + offset;
        if (direction == S)
            return 12 + offset;
        if (direction == E)
            return 3 + offset;
        if (direction == W)
            return 1 + offset;
        break;
    case 3:
        if (direction == N)
            return 4 + offset;
        if (direction == S)
            return 11 + offset;
        if (direction == E && y / 240 < 2)
            return 5 + offset;
        if (direction == E && y / 240 >= 2)
            return 9 + offset;
        if (direction == W && y / 240 < 2)
            return 14 + offset;
        if (direction == W && y / 240 >= 2)
            return 2 + offset;
        break;
    case 4:
        if (direction == N)
            return 8 + offset;
        if (direction == S)
            return 3 + offset;
        if (direction == E)
            return 5 + offset;
        if (direction == W)
            return 14 + offset;
        break;
    case 5:
        if (direction == N)
            return 7 + offset;
        if (direction == S)
            return 9 + offset;
        if (direction == E)
            return 6 + offset;
        if (direction == W && y / 240 < 4)
            return 4 + offset;
        if (direction == W && y / 240 >= 4)
            return 3 + offset;
        break;
    case 6:
        if (direction == N)
            return 7 + offset;
        if (direction == S)
            return 9 + offset;
        if (direction == W)
            return 5 + offset;
        break;
    case 7:
        if (direction == S && x / 320 < 3)
            return 5 + offset;
        if (direction == S && x / 320 >= 3)
            return 6 + offset;
        if (direction == W)
            return 8 + offset;
        break;
    case 8:
        if (direction == S)
            return 4 + offset;
        if (direction == E)
            return 7 + offset;
        break;
    case 9:
        if (direction == N && x / 320 < 3)
            return 5 + offset;
        if (direction == N && x / 320 >= 3)
            return 6 + offset;
        if (direction == S && x / 320 < 3)
            return 11 + offset;
        if (direction == S && x / 320 >= 3)
            return 10 + offset;
        if (direction == W)
            return 3 + offset;
        break;
    case 10:
        if (direction == N)
            return 9 + offset;
        if (direction == W)
            return 11 + offset;
        break;
    case 11:
        if (direction == N && x / 320 < 4)
            return 3 + offset;
        if (direction == N && x / 320 >= 4)
            return 9 + offset;
        if (direction == E)
            return 10 + offset;
        if (direction == W)
            return 12 + offset;
        break;
    case 12:
        if (direction == N)
            return 2 + offset;
        if (direction == E)
            return 11 + offset;
        break;
    case 13:
        if (direction == N)
            return 15 + offset;
        if (direction == S)
            return 1 + offset;
        if (direction == E)
            return 14 + offset;
        break;
    case 14:
        if (direction == S)
            return 2 + offset;
        if (direction == E && y / 240 < 3)
            return 4 + offset;
        if (direction == E && y / 240 >= 3)
            return 3 + offset;
        if (direction == W)
            return 13 + offset;
        break;
    case 15:
        if (direction == S)
            return 13 + offset;
        break;
    default:
        break;
    }
    return -1;
}
