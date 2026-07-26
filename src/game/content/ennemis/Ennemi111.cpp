#include "Ennemi111.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../algo/AStar.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"
#include "../effects/Debris.h"

#include "../helper/ProjectileHelper.h"

Ennemi111::Ennemi111(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi111.png", true);
    chrono.reset();

    type = 111;

    x = i;
    y = j;

    // for quadtree operations:
    width = 63;
    height = 48;

    box.setX(x + 16);
    box.setY(y + 16);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 50;
    maxLife = 50;
    recul = 8;
    vitesseRecul = 4;
    maxGel = 128;

    step = 0;
    elan = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 24;
}

Ennemi111::~Ennemi111()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi111::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    step = 0;
    elan = 0;
    checkPosition();
}

bool Ennemi111::isResetable()
{
    return alive;
}

void Ennemi111::ennLoop()
{
    if (step == 0)
    {

        // retrieve target position ( = link ^^)
        Link *link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        for (int i = 0; i < 4; i++)
        {
            BoundingBox hitZone(box.getX(), box.getY(), box.getW(), box.getH());
            switch (i)
            {
            case 0:
                hitZone.setY(box.getY() - 32);
                break;
            case 1:
                hitZone.setY(box.getY() + 32);
                break;
            case 2:
                hitZone.setX(box.getX() - 32);
                break;
            case 3:
                hitZone.setX(box.getX() + 32);
                break;
            }
            if (hitZone.intersect(getLink()->getBoundingBox()))
            {
                direction = (Direction)i;
                step = 1;
                elan = 32;
                anim = 0;
                chrono.reset();
                break;
            }
        }
    }
    else if (step == 1 && anim == 1)
    {
        elan -= 2;
        switch (direction)
        {
        case N:
            moveY(-2);
            break;
        case S:
            moveY(2);
            break;
        case W:
            moveX(-2);
            break;
        case E:
            moveX(2);
            break;
        }
        if (elan == 0)
        {
            step = 0;
            anim = 0;
            chrono.reset();
        }
    }
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = step == 1 ? 1 : 0;
        }
        chrono.reset();
    }
}

void Ennemi111::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (gel)
    {
        anim = 0;
        step = 0;
        elan = 0;
        chrono.reset();
        WindowManager::getInstance()->draw(image, 4 * width, 0, width, height, dstX, dstY);
    }
    else if (step == 0)
    {
        WindowManager::getInstance()->draw(image, direction * width, anim * height, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction * width, (2 + anim) * height, width, height, dstX, dstY);
    }
}

void Ennemi111::moveX(int dx)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + 16 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi111::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + 16 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi111::getX()
{
    return x;
}

int Ennemi111::getY()
{
    return y;
}

BoundingBox *Ennemi111::getBoundingBox()
{
    box.setX(x + 16);
    box.setY(y + 16);
    return &box;
}

void Ennemi111::giveItem(int i, int j)
{
    Ennemi::giveItem(i, j);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156)
    {
        AudioManager::getInstance()->playMusic(20);
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 8));
    }
}
