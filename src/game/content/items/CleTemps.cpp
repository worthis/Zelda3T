#include "CleTemps.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

CleTemps::CleTemps(int i, int j)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);
}

CleTemps::~CleTemps()
{
    ResourceManager::getInstance()->free(image);
}

void CleTemps::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }
    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, 240, 176, 16, 16, dstX, dstY);
}

void CleTemps::action()
{
    getLink()->trouveObjet(TI_CLE_TEMPS);
    alive = false;
}

bool CleTemps::isPickable()
{
    return false;
}
