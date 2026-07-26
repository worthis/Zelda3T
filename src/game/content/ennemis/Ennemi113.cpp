#include "Ennemi113.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi113::Ennemi113(int i, int j) : anim(0), animMax(31), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi113.png", true);
    chrono.reset();

    type = 113;

    x = i;
    y = j;

    // for quadtree operations:
    width = 28;
    height = 29;

    box.setX(x - 2);
    box.setY(y - 2);
    box.setW(32);
    box.setH(32);

    life = 30;
    maxLife = 30;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 8;
}

Ennemi113::~Ennemi113()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi113::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
}

bool Ennemi113::isResetable()
{
    return alive;
}

void Ennemi113::ennLoop()
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

void Ennemi113::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int srcX = 0;
    if (anim < 14)
        srcX = 0;
    else if (anim == 14 || anim == 31)
        srcX = width;
    else if (anim == 15 || anim == 30)
        srcX = width * 2;
    else
        srcX = width * 3;

    WindowManager::getInstance()->draw(image, srcX, 0, width, height, dstX, dstY);
}

void Ennemi113::drawEncyclopedie()
{
    WindowManager::getInstance()->draw(image, width * 3, 0, width, height, x, y);
}

void Ennemi113::moveX(int dx)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x - 2 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi113::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y - 2 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi113::getX()
{
    return x;
}

int Ennemi113::getY()
{
    return y;
}

BoundingBox *Ennemi113::getBoundingBox()
{
    box.setX(x - 2);
    box.setY(y - 2);
    return &box;
}

bool Ennemi113::hasEffect(TypeAttack ta, TypeEffect te, Direction dir)
{
    return anim >= 14 && ta == TA_ARROW;
}
