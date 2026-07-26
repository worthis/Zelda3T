#include "Zzzzz.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

Zzzzz::Zzzzz(int i, int j)  : x(i), y(j), anim(0), animMax(3), vanim(240) {
    image = ResourceManager::getInstance()->loadImage("data/images/effects/Zzzz.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 8;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

Zzzzz::~Zzzzz() {
    ResourceManager::getInstance()->free(image);
}

void Zzzzz::loop() {
    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Zzzzz::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

int Zzzzz::getX() {
    return x;
}

int Zzzzz::getY() {
    return y;
}
