#include "Ennemi126.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi126::Ennemi126(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi126.png", true);
    chrono.reset();

    type = 126;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    startX = x;
    startY = y;
    startDir = direction;

    life = 3;
    maxLife = 3;
    recul = 32;
    vitesseRecul = 4;

    items.addType(TI_RUBIS_VERT, 10);

    forceEnn = 1;
}

Ennemi126::~Ennemi126()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi126::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi126::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        if (dir.first < 0)
            direction = W;
        if (dir.first > 0)
            direction = E;

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox()))
        {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_ARGENT);
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
        if (dist <= 100)
        {
            link->getStatus()->updateGanonOr(-1);
            if (link->getStatus()->getVirtualGanonOr() <= 0)
            {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(58, 69 * 16 + 8, 102 * 16, N, false, true);
                MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                AudioManager::getInstance()->playSound(TS_TELEPORT);
            }
        }
        chrono.reset();
    }
}

void Ennemi126::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, (direction % 2) * 14, anim * 15, 14, 15, dstX + 1, dstY + 1);
}

int Ennemi126::getX()
{
    return x;
}

int Ennemi126::getY()
{
    return y;
}

BoundingBox *Ennemi126::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}
