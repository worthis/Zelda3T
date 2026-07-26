#include "Ennemi106.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi106::Ennemi106(int i, int j) : anim(0), animMax(1), vanim(180), step(0), cooldown(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi106.png", true);
    chrono.reset();

    type = 106;

    x = i;
    y = j;

    // for quadtree operations:
    width = 39;
    height = 48;

    box.setX(x + 15);
    box.setY(y);
    box.setW(16);
    box.setH(height);

    life = 1;
    maxLife = 1;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = true;

    forceEnn = 1;
}

Ennemi106::~Ennemi106()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi106::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    step = 0;
    cooldown = 0;
}

bool Ennemi106::isResetable()
{
    return alive;
}

void Ennemi106::ennLoop()
{

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (step != 0)
            {
                step = 0;
            }
        }
        cooldown++;
        if (cooldown == 8)
        {
            step = 1 + ((int)((float)rand() / RAND_MAX * 3));
            if (step == 1 || step == 3)
            {
                snipe(8, 10);
            }
            if (step == 2 || step == 3)
            {
                snipe(9, 27);
            }
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi106::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, invul && recul ? 4 * width : step * width, anim * height, width, height, dstX, dstY);
}

int Ennemi106::getX()
{
    return x;
}

int Ennemi106::getY()
{
    return y;
}

BoundingBox *Ennemi106::getBoundingBox()
{
    box.setX(x + 15);
    box.setY(y);
    return &box;
}

void Ennemi106::snipe(int dx, int dy)
{
    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    // throw proj and play sound
    double anglx = 0;
    double angly = 0;
    int origx = x + dx;
    int origy = y + dy;
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

    ProjectileHelper::getInstance()->addProjectile(TP_BIG_FEU, origx, origy, anglx, angly);
}

bool Ennemi106::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    recul = (type != TA_MAGIC || effect != TE_FEU) ? 0 : 12;
    return false;
}

void Ennemi106::pousseX(int dx)
{
    x += dx;
    getBoundingBox();
    checkPosition();
}
