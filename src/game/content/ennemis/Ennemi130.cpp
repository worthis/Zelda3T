#include "Ennemi130.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi130::Ennemi130(int i, int j) : anim(0), animMax(1), vanim(180), cooldown(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi130.png", true);
    chrono.reset();

    type = 130;

    x = i;
    y = j;

    // for quadtree operations:
    width = 24;
    height = 31;

    box.setX(x);
    box.setY(y + 15);
    box.setW(24);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 20;
    maxLife = 20;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    forceEnn = 1;
}

Ennemi130::~Ennemi130()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi130::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    cooldown = 0;
    checkPosition();
}

void Ennemi130::ennLoop()
{

    if (cooldown && !gel)
        cooldown--;

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {

        bool fire = false;
        if (!cooldown)
        {

            int dx = x + width / 2 - dstX;
            int dy = y + height - dstY;

            switch (direction)
            {
            case N:
                fire = (dy > 0 && abs(dx) <= 8);
                break;
            case S:
                fire = (dy < 0 && abs(dx) <= 8);
                break;
            case W:
                fire = (dx > 0 && abs(dy) <= 8);
                break;
            case E:
                fire = (dx < 0 && abs(dy) <= 8);
                break;
            }
        }

        if (fire)
        {
            idle = true;
            testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_EXPONENTIEL);

            switch (direction)
            {
            case N:
                ProjectileHelper::getInstance()->addProjectile(TP_FEU_LONG_ENN, x + 8, y - 4, N, true);
                break;
            case S:
                ProjectileHelper::getInstance()->addProjectile(TP_FEU_LONG_ENN, x + 8, y + 20, S, true);
                break;
            case W:
                ProjectileHelper::getInstance()->addProjectile(TP_FEU_LONG_ENN, x - 4, y + 15, W, true);
                break;
            case E:
                ProjectileHelper::getInstance()->addProjectile(TP_FEU_LONG_ENN, x + 20, y + 15, E, true);
                break;
            }
            AudioManager::getInstance()->playSound(TS_BURN);
            cooldown = 128;
        }
        else
        {
            if (cooldown < 64)
            {
                pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);
                move(dir.first, dir.second);
            }
            if (link->getBoundingBox()->intersect(getBoundingBox()))
            {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_EXPONENTIEL);
            }
        }
    }
    else
    {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi130::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width,
                                       ((cooldown == 0 || cooldown < 64) ? anim * height : height * 2) + (gel ? height * 3 : 0),
                                       width, height, dstX, dstY);
}

int Ennemi130::getX()
{
    return x;
}

int Ennemi130::getY()
{
    return y;
}

BoundingBox *Ennemi130::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 15);
    return &box;
}
