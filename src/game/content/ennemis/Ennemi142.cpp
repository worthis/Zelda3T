#include "Ennemi142.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi142::Ennemi142(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi142.png", true);
    chrono.reset();

    type = 142;

    x = i;
    y = j;

    // for quadtree operations:
    width = 48;
    height = 51;

    box.setX(x);
    box.setY(y + 3);
    box.setW(width);
    box.setH(48);

    startX = x;
    startY = y;
    startDir = direction;

    life = 999;
    maxLife = 999;
    recul = 32;
    vitesseRecul = 4;

    forceEnn = 80;
}

Ennemi142::~Ennemi142()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi142::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi142::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    for (int i = 0; i < 4; i++)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        if (dir.first < 0)
            direction = W;
        if (dir.first > 0)
            direction = E;

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox()))
        {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }
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

void Ennemi142::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 6, 237, 36, 18, dstX + 6, dstY + height - 18);
    WindowManager::getInstance()->draw(image, (direction % 2) * 48, 102 + anim * 51, 48, 51, dstX, dstY);
}

int Ennemi142::getX()
{
    return x;
}

int Ennemi142::getY()
{
    return y;
}

BoundingBox *Ennemi142::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 1);
    return &box;
}

bool Ennemi142::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return false;
}
