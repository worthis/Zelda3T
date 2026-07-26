#include "Ennemi110.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi110::Ennemi110(int i, int j) : anim(0), animMax(3), vanim(180), cooldown(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi110.png", true);
    chrono.reset();

    type = 110;

    x = i;
    y = j;

    // for quadtree operations:
    width = 29;
    height = 32;

    box.setX(x + 7);
    box.setY(y + 16);
    box.setW(16);
    box.setH(16);

    life = 15;
    maxLife = 15;
    recul = 8;
    vitesseRecul = 4;

    step = 0;

    isBoss = true;
    stunnable = true;

    forceEnn = 8;
}

Ennemi110::~Ennemi110()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi110::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
    step = 0;
}

bool Ennemi110::isResetable()
{
    return alive;
}

void Ennemi110::ennLoop()
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
        if (randomValue == 10)
        {
            animMax = 4;
        }
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
            if (animMax == 4)
            {
                animMax = 3;
                step = step == 1 ? 0 : 1;
                cooldown = 0;
            }
        }

        if (step == 1 && ++cooldown == 8)
        {

            // retrieve target position ( = link ^^)
            Link *link = getLink();

            int dstX = link->getX() + 8;
            int dstY = link->getY() + 24;

            // throw proj and play sound
            double anglx = 0;
            double angly = 0;
            int origx = x + 12;
            int origy = y + 24;
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

            ProjectileHelper::getInstance()->addProjectile(TP_BIG_GLACE, origx, origy, anglx, angly);
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi110::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (invul && step == 1)
    {
        WindowManager::getInstance()->draw(image, 4 * width, height, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, anim * width, anim == 4 ? 0 : step * height, width, height, dstX, dstY);
    }
}

void Ennemi110::drawEncyclopedie()
{
    WindowManager::getInstance()->draw(image, width, height, width, height, x, y);
}

void Ennemi110::moveX(int dx)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + 7 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Ennemi110::moveY(int dy)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + 16 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

int Ennemi110::getX()
{
    return x;
}

int Ennemi110::getY()
{
    return y;
}

BoundingBox *Ennemi110::getBoundingBox()
{
    box.setX(x + 7);
    box.setY(y + 16);
    return &box;
}

bool Ennemi110::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return step == 1 && effect == TE_FEU;
}
