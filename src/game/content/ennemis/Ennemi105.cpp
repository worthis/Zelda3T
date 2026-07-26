#include "Ennemi105.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../algo/AStar.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"
#include "../effects/Debris.h"

#include "../helper/ProjectileHelper.h"

Ennemi105::Ennemi105(int i, int j) : anim(0), animMax(5), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi105.png", true);
    chrono.reset();

    type = 105;

    x = i;
    y = j;

    // for quadtree operations:
    width = 80;
    height = 87;

    box.setX(x + 16);
    box.setY(y + 32);
    box.setW(48);
    box.setH(48);

    startX = x;
    startY = y;
    startDir = direction;

    life = 21;
    maxLife = 21;
    recul = 0;
    vitesseRecul = 0;

    step = 0;
    elan = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 12;
}

Ennemi105::~Ennemi105()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi105::reset()
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

bool Ennemi105::isResetable()
{
    return alive;
}

void Ennemi105::ennLoop()
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
                hitZone.setY(box.getY() - 48);
                break;
            case 1:
                hitZone.setY(box.getY() + 48);
                break;
            case 2:
                hitZone.setX(box.getX() - 48);
                break;
            case 3:
                hitZone.setX(box.getX() + 48);
                break;
            }
            if (hitZone.intersect(getLink()->getBoundingBox()))
            {
                direction = (Direction)i;
                step = 1;
                elan = 48;
                animMax = 1;
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
            animMax = 5;
            anim = 0;
            chrono.reset();
        }
    }

    if (step == 1)
    {
        BoundingBox bb(x, y, 80, 80);
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        map->testDegat(&bb, direction, forceEnn, TA_MARTEAU, TE_NORMAL, false);
    }
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_MARTEAU, TE_NORMAL);

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

void Ennemi105::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 0)
    {
        WindowManager::getInstance()->draw(image, direction * width, anim * 80, width, 80, dstX, dstY);
    }
    else if (step == 1 && anim == 1)
    {
        WindowManager::getInstance()->draw(image, direction * width, (6 + anim) * 80, width, 87, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction * width, (6 + anim) * 80, width, 80, dstX, dstY);
    }
}

void Ennemi105::moveX(int dx)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + 16 + dx);

    if (step == 1)
    {
        map->testDegat(bb, direction, forceEnn, TA_MARTEAU, TE_NORMAL, false);
    }

    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi105::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + 32 + dy);

    if (step == 1)
    {
        map->testDegat(bb, direction, forceEnn, TA_MARTEAU, TE_NORMAL, false);
    }

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi105::getX()
{
    return x;
}

int Ennemi105::getY()
{
    return y;
}

BoundingBox *Ennemi105::getBoundingBox()
{
    box.setX(x + 16);
    box.setY(y + 32);
    return &box;
}

void Ennemi105::giveItem(int i, int j)
{
    Ennemi::giveItem(i, j);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156)
    {
        AudioManager::getInstance()->playMusic(20);
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 5));
    }
}

bool Ennemi105::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return type == TA_MAGIC && effect == TE_NORMAL;
}

bool Ennemi105::isToAvoid(Collision c)
{
    return false;
}
