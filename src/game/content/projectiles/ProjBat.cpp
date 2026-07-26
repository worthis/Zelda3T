#include "ProjBat.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjBat::ProjBat(int i, int j, double dx, double dy) : dx(dx), dy(dy)
{
    x = i - 14;
    y = j - 8;
    longX = i;
    longY = j;

    if (dx > 0)
    {
        if (dy > 0)
        {
            if (dx > dy)
                direction = E;
            else
                direction = S;
        }
        else
        {
            if (dx > -dy)
                direction = E;
            else
                direction = N;
        }
    }
    else
    {
        if (dy > 0)
        {
            if (-dx > dy)
                direction = W;
            else
                direction = S;
        }
        else
        {
            if (-dx > -dy)
                direction = W;
            else
                direction = N;
        }
    }

    // for quadtree operations:
    width = 28;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    vanim = 120;
    anim = 0;
    animMax = 4;
    chrono.reset();

    force = 35;

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/bat.png", true);
}

ProjBat::~ProjBat()
{
    ResourceManager::getInstance()->free(image);
}

void ProjBat::projLoop()
{
    if (!alive)
    {
        return;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // compute bounding box for collisions
    box.setX(longX - 14 + dx);
    box.setY(longY - 8 + dy);

    longX += dx;
    longY += dy;

    x = longX - 14;
    y = longY - 8;

    if (scene->testDegatOnLink(getBoundingBox(), direction, force, TA_MAGIC, TE_FEU))
    {
        alive = false;
        return;
    }

    if (!scene->checkCollisions(&box, (Collisionable *)this, false, false, false, false, false))
    {
        alive = false;
    }

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

void ProjBat::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = longX - 14 - offsetX;
    int dstY = longY - 8 - offsetY;

    WindowManager::getInstance()->draw(image, 0, anim * 16, 28, 16, dstX, dstY);
}

BoundingBox *ProjBat::getBoundingBox()
{
    box.setX(longX - 14);
    box.setY(longY - 8);
    return &box;
}

int ProjBat::getX() { return x; }
int ProjBat::getY() { return y; }
int ProjBat::getDown() { return y + 240; }
