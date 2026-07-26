#include "PiegeFlammeVerte.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

PiegeFlammeVerte::PiegeFlammeVerte(int i, int j) : direction(S), anim(0), animMax(2), vanim(180)
{
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/piegeFlammeVerte.png", true);

    // for quadtree operations:
    width = 16;
    height = 32;

    box.setX(x);
    box.setY(y + 16);
    box.setW(16);
    box.setH(16);

    chrono.reset();
}

PiegeFlammeVerte::~PiegeFlammeVerte()
{
    ResourceManager::getInstance()->free(image);
}

void PiegeFlammeVerte::loop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    BoundingBox *bb = getBoundingBox();
    scene->testDegatOnLink(bb, direction, 1, TA_MAGIC, TE_MORT);

    for (int i = 0; i < 2; i++)
    {
        if (bb->intersect(scene->getLink()->getBoundingBox()))
        {
            scene->getLink()->pousseY(1);
        }
        else
        {
            break;
        }
    }

    if (y < 24 * 16)
    {
        moveY(1);
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

void PiegeFlammeVerte::draw(int offsetX, int offsetY)
{
    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, x - offsetX, y - offsetY);
}

BoundingBox *PiegeFlammeVerte::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 16);
    return &box;
}

void PiegeFlammeVerte::moveY(int dy)
{
    y += dy;
    checkPosition();
}
