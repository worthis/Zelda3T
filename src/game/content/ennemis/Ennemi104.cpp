#include "Ennemi104.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi104::Ennemi104(int i, int j) : anim(0), animMax(7), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi104.png", true);
    chrono.reset();

    type = 104;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(32);
    box.setH(32);

    life = 400;
    maxLife = 400;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 8;
}

Ennemi104::~Ennemi104()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi104::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
}

bool Ennemi104::isResetable()
{
    return alive;
}

void Ennemi104::ennLoop()
{

    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue)
    {
    case 1:
        moveX(-1);
        direction = W;
        break;
    case 2:
        moveX(1);
        direction = E;
        break;
    case 3:
        moveY(-1);
        direction = N;
        break;
    case 4:
        moveY(1);
        direction = S;
        break;
    default:
        if (randomValue < 10)
            break;
        switch (direction)
        {
        case N:
            moveY(-1);
            break;
        case S:
            moveY(1);
            break;
        case W:
            moveX(-1);
            break;
        case E:
            moveX(1);
            break;
        }
        break;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

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

void Ennemi104::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, 31, dstX, dstY);
}

void Ennemi104::moveX(int dx)
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

void Ennemi104::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + dy);

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi104::getX()
{
    return x;
}

int Ennemi104::getY()
{
    return y;
}

BoundingBox *Ennemi104::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}
