#include "Planches.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Planches::Planches(int i, int j)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 48;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(48);
    box.setH(16);
}

Planches::~Planches()
{
    ResourceManager::getInstance()->free(image);
}

void Planches::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }
    WindowManager::getInstance()->draw(image, 176, 112, 48, 16, x - offsetX, y - offsetY);
}

void Planches::action()
{
    getLink()->trouveObjet(TI_PLANCHES);
    alive = false;
}

bool Planches::isPickable() { return false; }
