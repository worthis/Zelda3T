#include "Ennemi116.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi116::Ennemi116(int i, int j)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi116.png", true);
    chrono.reset();

    type = 116;

    x = i;
    y = j;

    // for quadtree operations:
    width = 78;
    height = 68;

    box.setX(x + 16);
    box.setY(y + 16);
    box.setW(48);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    step = -1;
    anim = 0;
    animMax = 5;
    vanim = 240;
    special = 67;

    isBoss = false;
    stunnable = false;

    forceEnn = 10;
}

Ennemi116::~Ennemi116()
{
    ResourceManager::getInstance()->free(image);
}

bool Ennemi116::isResetable()
{
    return alive;
}

void Ennemi116::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    step = -1;
    anim = 0;
    animMax = 5;
    special = 67;
    checkPosition();
}

void Ennemi116::ennLoop()
{
    if (step == -1)
    {
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        if (map->getBounds()->getX() == 320 * 3 || map->getId() == 156)
        {
            step = 0;
            anim = 0;
            animMax = 5;
            special = 67;
            getBoundingBox();
            checkPosition();
            chrono.reset();
        }
    }
    if (step > 1)
    {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (step == 1)
    {
        special--;
        if (special <= 0)
        {
            step = 2;
            animMax = 6 + 25;
            special = 0;
        }
        getBoundingBox();
        checkPosition();
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (step == 0 || step == 2)
            {
                step++;
                animMax = 6;
            }
            if (step == 4)
            {
                step = 3;
                animMax = 6;
            }
            if (step == 3)
            {
                if (getLink()->getX() % 320 <= 9 * 16 + 8)
                {
                    step = 4;
                    animMax = 6;
                }
            }
        }
        if (step == 4 && anim == 4)
        {
            snipe();
        }
        chrono.reset();
    }
}

void Ennemi116::draw(int offsetX, int offsetY)
{
    if (!alive || special >= 50)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 1)
    {
        int srcH = 50 - special;
        WindowManager::getInstance()->draw(image, 0, 0, width, srcH, dstX, dstY + special);
    }
    else if (step == 2)
    {
        WindowManager::getInstance()->draw(image, (anim <= 6 ? anim : 6) * width, 0, width, height, dstX, dstY);
    }
    else if (step == 3)
    {
        WindowManager::getInstance()->draw(image, 6 * width, 0, width, height, dstX, dstY);
    }
    else if (step == 4)
    {
        WindowManager::getInstance()->draw(image, (anim >= 4 && anim <= 5 ? 8 : 7) * width, 0, width, height, dstX, dstY);
    }
}

int Ennemi116::getX()
{
    return x;
}

int Ennemi116::getY()
{
    return y;
}

BoundingBox *Ennemi116::getBoundingBox()
{
    if (step < 2 || (step == 2 && anim < 6))
    {
        box.setY(special == 0 ? y + 16 : y + special);
    }
    else
    {
        box.setY(y + 28);
    }
    return &box;
}

void Ennemi116::snipe()
{
    Link *link = getLink();
    int origx = x + 40;
    int origy = y + 59;
    ProjectileHelper::getInstance()->addProjectile(TP_BOULE_ULTIME, origx, origy, link);
    AudioManager::getInstance()->playSound(TS_THROW);
}

bool Ennemi116::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return false;
}

bool Ennemi116::isToAvoid(Collision c)
{
    return false;
}
