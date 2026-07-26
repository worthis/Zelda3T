#include "Ennemi050.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../objects/PiegeFlamme.h"
#include "../objects/PiegeFlammeVerte.h"

#include "../helper/ProjectileHelper.h"

Ennemi050::Ennemi050(int i, int j) : anim(0), animMax(1), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi50.png", true);
    chrono.reset();

    type = 50;

    x = i;
    y = j;

    // for quadtree operations:
    width = 52;
    height = 36;

    box.setX(x + 10);
    box.setY(y + 4);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 300;
    maxLife = 300;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 50;
    snipeMode = false;
    step = 0;
    cooldown = 0;
    beforeZelda = 15;
}

Ennemi050::~Ennemi050()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi050::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    snipeMode = false;
    step = 0;
    cooldown = 0;
    beforeZelda = 15;
    checkPosition();
}

bool Ennemi050::isResetable()
{
    return alive;
}

void Ennemi050::ennLoop()
{

    Link *link = getLink();

    if (step == 1 || step == 3 || step == 5)
    {
        if (x != 169 * 16 - 10 || y != 19 * 16 - 4 + 8)
        {
            if (x < 169 * 16 - 10)
            {
                direction = E;
                x++;
            }
            else if (x > 169 * 16 - 10)
            {
                direction = W;
                x--;
            }
            if (y > 19 * 16 - 4 + 8)
            {
                direction = N;
                y--;
            }
            else if (y < 19 * 16 - 4 + 8)
            {
                direction = S;
                y++;
            }
            checkPosition();
            if (x == 169 * 16 - 10 && y == 19 * 16 - 4 + 8)
            {
                direction = S;
                snipeMode = true;
                cooldown = 1;
            }
        }
    }
    else if (!snipeMode)
    {
        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);
        move(dir.first, dir.second);
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        if (snipeMode)
        {
            cooldown++;
            if (link->getStatus()->getLife() <= 0)
            {
                cooldown = 9;
            }
            else if (cooldown == 8)
            {

                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;

                // throw proj and play sound
                double anglx = 0;
                double angly = 0;
                int origx = x + 26;
                int origy = y + 10;
                int destx = dstX;
                int desty = dstY - 8;

                double coef1 = 0;
                double coef2 = 0;

                if ((destx - origx) == 0)
                {
                    anglx = 0;
                    angly = 12;
                }
                else if ((desty - origy) == 0)
                {
                    anglx = 12;
                    angly = 0;
                }
                else
                {
                    coef1 = ((double)(desty - origy)) / ((double)(destx - origx));
                    coef2 = ((double)(destx - origx)) / ((double)(desty - origy));
                    anglx = (sqrt(12 / (1 + (coef1 * coef1))));
                    angly = (sqrt(12 / (1 + (coef2 * coef2))));
                }
                if (destx - origx < 0)
                    anglx = -anglx;
                if (desty - origy < 0)
                    angly = -angly;

                if (anglx > 4)
                    anglx = 4;
                if (angly > 4)
                    angly = 4;
                if (anglx < -4)
                    anglx = -4;
                if (angly < -4)
                    angly = -4;

                ProjectileHelper::getInstance()->addProjectile(TP_BAT, origx, origy, anglx, angly);
                AudioManager::getInstance()->playSound(TS_BURN);
            }
            else if (cooldown >= 10)
            {
                if (step == 1 || step == 3 || step == 5)
                {
                    cooldown = step == 1 ? 2 : 5;
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    Map *map = scene->getMap();
                    if (step == 5 && beforeZelda > 0 && scene->getCoffre(12, 14))
                    {
                        beforeZelda--;
                        if (beforeZelda == 0)
                        {
                            AudioManager::getInstance()->playSound(TS_DOOR);
                            map->ouvrePorte(158, 21, 1);
                            map->removeZelda();
                            map->addObject(new Pnj(16 * 160 + 8, 16 * 21 + 9, 15, 1355, E));
                        }
                    }
                }
                else
                {
                    int randomValue = (int)((float)rand() / RAND_MAX * (2));
                    if (randomValue == 0)
                    {
                        cooldown = 0;
                        snipeMode = false;
                    }
                    else
                    {
                        cooldown = 5;
                    }
                }
            }
        }
        else if (step == 0 || step == 2 || step == 4)
        {
            int randomValue = (int)((float)rand() / RAND_MAX * (15));
            if (randomValue == 10)
            {
                direction = S;
                snipeMode = true;
                cooldown = 1;
            }
        }
        chrono.reset();
    }
}

void Ennemi050::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (snipeMode)
    {
        WindowManager::getInstance()->draw(image, cooldown > 7 ? 0 : width, 113, width, 42, dstX, dstY - 6);
    }
    else
    {
        WindowManager::getInstance()->draw(image, direction == N ? 0 : width, anim * height, width, height, dstX, dstY);
    }
}

int Ennemi050::getX()
{
    return x;
}

int Ennemi050::getY()
{
    return y;
}

BoundingBox *Ennemi050::getBoundingBox()
{
    box.setX(x + 10);
    box.setY(y + 4);
    return &box;
}

bool Ennemi050::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return (effect == TE_MORT) || (life > 1 && (type == TA_SWORD || type == TA_SWORD_HOLD));
}

void Ennemi050::afterHit()
{
    if (life <= 0)
    {
        life = 1;
        recul = 0;
        vitesseRecul = 0;
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->setBossLife(life, maxLife);
    }
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    if ((life <= 200 && step == 0) || (life <= 100 && step == 2) || (life <= 1 && step == 4))
    {
        step++;
        snipeMode = false;
        cooldown = 0;
        for (int i = 0; i < 10; i++)
        {
            if (step == 5)
            {
                map->addObject(new PiegeFlammeVerte((165 + i) * 16, 16 * 16));
            }
            else
            {
                map->addObject(new PiegeFlamme((165 + i) * 16, 16 * 16, false));
            }
        }
    }
    else if (step == 1 || step == 3)
    {
        step++;
        snipeMode = false;
        cooldown = 0;
        map->cleanFlamme();
    }
}

bool Ennemi050::canDie(TypeEffect effect)
{
    return effect == TE_MORT;
}

void Ennemi050::giveItem(int x, int y)
{
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map *map = scene->getMap();
    map->cleanFlamme();
    map->addEffect(new FumeeBlanche(x, y));
    // map->addItem(ItemHelper::getInstance()->createItem(TI_TRIFORCE, x, y));
    scene->getAnimationInGame()->startAnim(14);
}
