#include "Ennemi087.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi087::Ennemi087(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi87.png", true);
    chrono.reset();

    type = 87;

    x = i;
    y = j;

    // for quadtree operations:
    width = 58;
    height = 24;

    box.setX(x + 21);
    box.setY(y + 8);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 7;
    maxLife = 7;
    recul = 32;
    vitesseRecul = 4;

    items.addType(TI_MAGIE_PEU, 40);
    items.addType(TI_MAGIE_BEAUCOUP, 10);

    forceEnn = 10;
}

Ennemi087::~Ennemi087()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi087::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi087::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (anim == 1)
        {
            box.setX(x);
            box.setY(y);
            box.setW(58);
            box.setH(24);
        }

        if (link->getBoundingBox()->intersect(&box))
        {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_GLACE);
        }
        getBoundingBox();
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

void Ennemi087::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

int Ennemi087::getX()
{
    return x;
}

int Ennemi087::getY()
{
    return y;
}

BoundingBox *Ennemi087::getBoundingBox()
{
    box.setX(x + 21);
    box.setY(y + 8);
    box.setW(16);
    box.setH(16);
    return &box;
}
