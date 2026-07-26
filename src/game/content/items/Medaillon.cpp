#include "Medaillon.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Medaillon::Medaillon(int i, int j, int num) : id(num) {
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

Medaillon::~Medaillon() {
    ResourceManager::getInstance()->free(image);
}

void Medaillon::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }
    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, 144, id * 16, 16, 16, dstX, dstY);
}

void Medaillon::action() {
    if (id == 0) getLink()->trouveObjet(TI_MEDAILLON_1);
    else if (id == 1) getLink()->trouveObjet(TI_MEDAILLON_2);
    else getLink()->trouveObjet(TI_MEDAILLON_3);
    alive = false;
}

bool Medaillon::isPickable() {
    return false;
}
