#include "ProjSouffle.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjSouffle::ProjSouffle(int i, int j)
{
    x = i;
    y = j;

    // for quadtree operations:
    width = 64;
    height = 16;

    direction = S;
    dy = 2;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/souffle.png", true);

    chrono.reset();
}

ProjSouffle::~ProjSouffle()
{
    ResourceManager::getInstance()->free(image);
}

void ProjSouffle::projLoop()
{
    if (!alive)
    {
        return;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->checkCollisions(getBoundingBox(), (Collisionable *)this, false))
    {
        y += dy;

        if (getBoundingBox()->intersect(scene->getLink()->getBoundingBox()))
        {
            scene->getLink()->pousseY(1);
        }
    }
    else
    {
        alive = false;
    }
}

void ProjSouffle::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 0, 0, width, height, dstX, dstY);
}

BoundingBox *ProjSouffle::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}
