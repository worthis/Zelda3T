#include "StatueGarde.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

StatueGarde::StatueGarde(int i, int j)
{
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/statueGarde.png", true);

    // for quadtree operations:
    width = 22;
    height = 27;

    box.setX(x + 3);
    box.setY(y + 11);
    box.setW(16);
    box.setH(16);
}

StatueGarde::~StatueGarde()
{
    ResourceManager::getInstance()->free(image);
}

void StatueGarde::draw(int offsetX, int offsetY)
{
    WindowManager::getInstance()->draw(image, 0, 0, width, height, x - offsetX, y - offsetY);
}
