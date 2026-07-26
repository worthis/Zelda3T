#include "Ennemi095.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../objects/Pierre.h"

#include "../effects/FumeeBlanche.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi095::Ennemi095(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi95.png", true);
    chrono.reset();

    type = 95;

    x = i;
    y = j;
    direction = W;

    // for quadtree operations:
    width = 20;
    height = 22;

    box.setX(x);
    box.setY(y);
    box.setW(20);
    box.setH(22);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 0;
    vitesseRecul = 0;
    step = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi095::~Ennemi095()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi095::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animMax = 1;
    step = 0;
    checkPosition();
}

bool Ennemi095::isResetable()
{
    return alive;
}

void Ennemi095::ennLoop()
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (step == 0)
    {
        int randomValue = (int)((float)rand() / RAND_MAX * (250));
        if (randomValue == 0)
        {
            step = 1; // special attack
            anim = 0;
            animMax = 5;
            chrono.reset();
        }
        else
        {
            if (direction == W)
            {
                if (x % 320 > 4 * 16 - 2)
                {
                    moveX(-1);
                }
                else
                {
                    direction = E;
                }
            }
            else
            {
                if (x % 320 < 15 * 16 - 2)
                {
                    moveX(1);
                }
                else
                {
                    direction = W;
                }
            }
            if ((x % 320 == 4 * 16 - 2 && map->getSol(124 * 16, 33 * 16) == 2545) || (x % 320 == 9 * 16 - 2 && map->getSol(129 * 16, 33 * 16) == 2545) || (x % 320 == 15 * 16 - 2 && map->getSol(135 * 16, 33 * 16) == 2545))
            {
                step = 2; // activate inter
                anim = 0;
                animMax = 1;
                chrono.reset();
            }
        }
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (step != 0)
            {
                step = 0;
                animMax = 1;
            }
        }
        if (step == 2)
        {
            map->reactiveInterruptor(x + 2, 33 * 16, true);
            map->activateInter(x + 2, 33 * 16, true);
        }
        chrono.reset();
    }
}

void Ennemi095::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 0)
    {
        WindowManager::getInstance()->draw(image, (direction % 2) * width, anim * height, width, height, dstX, dstY);
    }
    else if (step == 1)
    {
        WindowManager::getInstance()->draw(image, (anim % 2) * 27, 44, 27, 24, dstX - 3, dstY - 2);
    }
    else if (step == 2)
    {
        WindowManager::getInstance()->draw(image, 40 + anim * 19, 0, 19, 31, dstX + 1, dstY - 9);
    }
    else if (step == 3)
    {
        WindowManager::getInstance()->draw(image, 59, 0, 19, 31, dstX + 1, dstY - 9);
    }
}

void Ennemi095::moveX(int dx)
{
    x += dx;
    getBoundingBox();
    checkPosition();
}

int Ennemi095::getX()
{
    return x;
}

int Ennemi095::getY()
{
    return y;
}

BoundingBox *Ennemi095::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi095::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return effect == TE_FEU;
}

void Ennemi095::afterHit()
{
    step = 3; // hurt
    anim = 0;
    animMax = 2;
}
