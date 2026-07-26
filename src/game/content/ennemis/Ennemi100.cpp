#include "Ennemi100.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi100::Ennemi100(int i, int j)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi100.png", true);

    type = 100;

    x = i;
    y = j;

    // for quadtree operations:
    width = 63;
    height = 31;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    stunnable = false;

    forceEnn = 4;
}

Ennemi100::~Ennemi100()
{
    ResourceManager::getInstance()->free(image);
}

bool Ennemi100::isResetable()
{
    return alive;
}

void Ennemi100::reset()
{
    Ennemi::reset();
}

void Ennemi100::ennLoop()
{
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
}

void Ennemi100::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, 0, 0, width, height, dstX, dstY);
}

int Ennemi100::getX()
{
    return x;
}

int Ennemi100::getY()
{
    return y;
}

BoundingBox *Ennemi100::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi100::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return false;
}

bool Ennemi100::isToAvoid(Collision c)
{
    return c != EAU_PROF;
}
