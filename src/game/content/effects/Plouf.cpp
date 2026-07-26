#include "Plouf.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Plouf::Plouf(int x, int y) : x(x), y(y), anim(0), animMax(3), vanim(40)
{
    image = ResourceManager::getInstance()->loadImage("data/images/effects/plouf.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 40 + 16;
    height = 16;
}

Plouf::~Plouf()
{
    ResourceManager::getInstance()->free(image);
}

void Plouf::loop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    BoundingBox boxW(x - anim * 4 - 8, y, 16, 16);
    scene->getMap()->testDegat(&boxW, W, 0, TA_PHYSIC, TE_EAU, false);

    BoundingBox boxE(x + anim * 4 + 8, y, 16, 16);
    scene->getMap()->testDegat(&boxE, E, 0, TA_PHYSIC, TE_EAU, false);

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            alive = false;
        }
        chrono.reset();
    }
}

void Plouf::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, dstX - anim * 4 - 8, dstY);
    WindowManager::getInstance()->draw(image, 16, 0, 16, 16, dstX + anim * 4 + 8, dstY);
}

int Plouf::getX() { return x - 20; }
int Plouf::getY() { return y; }
