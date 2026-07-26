#include "Ennemi024.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

#include "../../algo/AStar.h"

Ennemi024::Ennemi024(int i, int j, bool water) : anim(0), animMax(1), vanim(180), inWater(water)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi24.png", true);
    chrono.reset();

    type = 24;

    beforeMove = 0;
    moving = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = water ? 38 : 48;

    box.setX(x);
    box.setY(water ? y : y + 16);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 8;
    vitesseRecul = 4;

    stunnable = false;

    vitesse = water ? 2 : 1;

    forceEnn = 2;
}

Ennemi024::~Ennemi024()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi024::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    beforeMove = 0;
    moving = 0;
    checkPosition();
}

bool Ennemi024::isResetable()
{
    return alive;
}

void Ennemi024::ennLoop()
{

    if (moving)
    {

        // retrieve target position ( = link ^^)
        Link *link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }
    else
    {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        if (beforeMove > 0)
        {
            beforeMove--;
            if (beforeMove == 0)
            {
                moving = 1;
            }
        }
        else if (moving < 12)
        {
            moving++;
            if (moving == 12)
            {
                moving = 0;
                beforeMove = 4;
            }
        }
        chrono.reset();
    }
}

void Ennemi024::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (inWater)
    {
        WindowManager::getInstance()->draw(image, 64 + anim * width, 0, 32, 31, dstX, dstY);
        WindowManager::getInstance()->draw(image, 64 + anim * 36, 32, 36, 19, dstX - 2, dstY + 18);
    }
    else
    {
        WindowManager::getInstance()->draw(image, anim * width, 0, 32, 48, dstX, dstY);
    }
}

void Ennemi024::moveX(int dx)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + dx);

    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi024::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY((inWater ? y : y + 16) + dy);

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi024::getX()
{
    return x;
}

int Ennemi024::getY()
{
    return y;
}

BoundingBox *Ennemi024::getBoundingBox()
{
    box.setX(x);
    box.setY(inWater ? y : y + 16);
    return &box;
}

bool Ennemi024::isToAvoid(Collision c)
{
    if (inWater)
        return c != EAU && c != EAU_PROF;
    else
        return Collisionable::isToAvoid(c);
}
