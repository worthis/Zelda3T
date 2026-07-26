#include "Ennemi121.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

Ennemi121::Ennemi121(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi121.png", true);
    chrono.reset();

    type = 121;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 32;
    vitesseRecul = 4;

    items.addType(TI_RUBIS_VERT, 30);
    items.addType(TI_PETIT_COEUR, 40);

    forceEnn = 1;
}

Ennemi121::~Ennemi121()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi121::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi121::ennLoop()
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

void Ennemi121::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, direction * width, anim * height, 16, 16, dstX, dstY);
}

int Ennemi121::getX()
{
    return x;
}

int Ennemi121::getY()
{
    return y;
}

BoundingBox *Ennemi121::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}

void Ennemi121::moveX(int dx)
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

void Ennemi121::moveY(int dy)
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
