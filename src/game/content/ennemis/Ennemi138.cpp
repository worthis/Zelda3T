#include "Ennemi138.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi138::Ennemi138(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi138.png", true);
    chrono.reset();

    type = 138;

    x = i;
    y = j;

    // for quadtree operations:
    width = 42;
    height = 30;

    box.setX(x+13);
    box.setY(y+12);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 20;
    maxLife = 20;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 64;

    forceEnn = 1;
}

Ennemi138::~Ennemi138() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi138::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi138::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        for (int i = 0; i < 2 ; i++) {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_EXPONENTIEL);
            }
        }
    } else {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi138::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height, width, height, dstX, dstY);
}

int Ennemi138::getX() {
    return x;
}

int Ennemi138::getY() {
    return y;
}

BoundingBox* Ennemi138::getBoundingBox() {
    box.setX(x + 13);
    box.setY(y + 12);
    return &box;
}
