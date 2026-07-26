#include "Ennemi132.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi132::Ennemi132(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi132.png", true);
    chrono.reset();

    type = 132;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 26;

    box.setX(x);
    box.setY(y+10);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 5;
    maxLife = 5;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    forceEnn = 1;
}

Ennemi132::~Ennemi132() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi132::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi132::ennLoop() {

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

void Ennemi132::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height + (gel ? height * 2 : 0), width, height, dstX, dstY);
}

int Ennemi132::getX() {
    return x;
}

int Ennemi132::getY() {
    return y;
}

BoundingBox* Ennemi132::getBoundingBox() {
    box.setX(x);
    box.setY(y + 10);
    return &box;
}

bool Ennemi132::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return effect == TE_FEU;
}
