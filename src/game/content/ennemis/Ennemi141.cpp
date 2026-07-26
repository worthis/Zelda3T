#include "Ennemi141.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeViolette.h"

#include "../helper/ProjectileHelper.h"

#include "Ennemi136.h"

Ennemi141::Ennemi141(int i, int j) : anim(0), animMax(11), vanim(240)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi141.png", true);

    type = 141;
    chrono.reset();

    step = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 57;
    height = 128;

    box.setX(x + 4);
    box.setY(y);
    box.setW(48);
    box.setH(128);

    startX = x;
    startY = y;
    startDir = direction;

    life = 500;
    maxLife = 500;
    recul = 0;
    vitesseRecul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 80;
}

Ennemi141::~Ennemi141()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi141::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animMax = 11;
    step = 0;
    checkPosition();
}

bool Ennemi141::isResetable()
{
    return alive;
}

void Ennemi141::ennLoop()
{

    if (step > 0)
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim)
    {
        if (!gel)
            anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (step == 0)
            {
                step = 1;
                animMax = 9;
            }
            else if (step == 1 && getLink()->getStatus()->getLife() > 0 && life > 1)
            {
                Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                if (map->nbEnnemis() < 7)
                {
                    int options = 3;
                    BoundingBox bb1 = BoundingBox(62 * 16 + 8, 78 * 16, 16, 16);
                    BoundingBox bb2 = BoundingBox(76 * 16, 78 * 16, 16, 16);
                    bool bb1Ok = map->checkCollisions(&bb1, this, true, false, false, false, false);
                    bool bb2Ok = map->checkCollisions(&bb2, this, true, false, false, false, false);
                    if (!bb1Ok)
                        options--;
                    if (!bb2Ok)
                        options--;
                    if (options == 1)
                    {
                        snipe();
                    }
                    else
                    {
                        int randomValue = (int)((float)rand() / RAND_MAX * (options));
                        if (randomValue == 1 && bb1Ok)
                        {
                            map->addEnnemi(new Ennemi136(62 * 16 - 4, 77 * 16 - 4, true));
                            map->addEffect(new FumeeViolette(63 * 16, 78 * 16 - 2));
                            AudioManager::getInstance()->playSound(TS_THROW);
                        }
                        else if (randomValue > 0 && bb2Ok)
                        {
                            map->addEnnemi(new Ennemi136(76 * 16 - 4 - 8, 77 * 16 - 4, true));
                            map->addEffect(new FumeeViolette(77 * 16 - 8, 78 * 16 - 2));
                            AudioManager::getInstance()->playSound(TS_THROW);
                        }
                        else
                        {
                            snipe();
                        }
                    }
                }
                else
                {
                    snipe();
                }
            }
        }
        chrono.reset();
    }
}

void Ennemi141::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step < 3)
    {
        WindowManager::getInstance()->draw(image, anim * width, step == 0 ? 0 : height, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, 570 + (step - 3) * 63, height, 63, height, dstX - 3, dstY);
    }
}

void Ennemi141::snipe()
{

    int origx = x + (width / 2);
    int origy = y + (height / 2);

    // throw proj and play sound
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
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

    ProjectileHelper::getInstance()->addProjectile(TP_FINAL, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_THROW);
}

int Ennemi141::getX()
{
    return x;
}

int Ennemi141::getY()
{
    return y;
}

BoundingBox *Ennemi141::getBoundingBox()
{
    box.setX(x + 4);
    box.setY(y);
    if (step >= 3)
    {
        box.setY(y + 64);
        box.setH(64);
    }
    return &box;
}

bool Ennemi141::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return (step == 1 && effect == TE_LUMIERE) || (step >= 2 && step <= 3 && effect == TE_MORT) || (step == 4 && (type == TA_SWORD || type == TA_SWORD_HOLD) && !getLink()->getStatus()->isOniLink());
}

void Ennemi141::afterHit()
{
    if (life <= 0)
    {
        life = 1;
        if (step == 1)
        {
            Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            map->killEnnemis(map->getBounds(), true);
            step = 2;
            map->ouvrePorte(58, 81, 1);
            map->addObject(new Pnj(60 * 16, 81 * 16 + 9, 15, 1657, E));
        }
    }
}

bool Ennemi141::canDie(TypeEffect effect)
{
    if (effect == TE_MORT)
    {
        if (step < 4)
        {
            step++;
            animMax = 0;
            if (step == 3)
            {
                Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                map->ouvrePorte(78, 81, 1);
                map->addObject(new Pnj(79 * 16, 81 * 16 + 5, 90, 1658, W));
            }
        }
        return false;
    }
    return step == 4;
}
