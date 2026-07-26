#include "Ennemi136.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi136::Ennemi136(int i, int j, bool ignoreDist) : anim(0), animMax(3), vanim(120) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi136.png", true);
    chrono.reset();

    type = 136;

    x = i;
    y = j;

    // for quadtree operations:
    width = 40;
    height = 36;

    box.setX(x+12);
    box.setY(y+20);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 30;
    maxLife = 30;
    recul = 8;
    vitesseRecul = 4;
    maxGel = 128;

    forceEnn = 1;
    if (ignoreDist) maxDist = 500;
}

Ennemi136::~Ennemi136() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi136::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi136::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox())) {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_EXPONENTIEL);
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

void Ennemi136::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width + (gel ? width * 4 : 0), anim * height, width, height, dstX, dstY);
}

int Ennemi136::getX() {
    return x;
}

int Ennemi136::getY() {
    return y;
}

BoundingBox* Ennemi136::getBoundingBox() {
    box.setX(x + 12);
    box.setY(y + 20);
    return &box;
}
