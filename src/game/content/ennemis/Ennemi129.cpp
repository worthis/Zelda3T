#include "Ennemi129.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "cstdlib"

Ennemi129::Ennemi129(int i, int j) : anim(0), animMax(9), vanim(80), actif(false) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi129.png", true);
    chrono.reset();

    type = 129;

    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 37;

    box.setX(x);
    box.setY(y + 21);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 30;
    maxLife = 30;
    recul = 0;
    vitesseRecul = 4;
    maxDist = 64;
    maxGel = 128;

    forceEnn = 1;
}

Ennemi129::~Ennemi129() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi129::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    anim = 0;
    actif = false;
    recul = 0;
    maxDist = 64;
    checkPosition();
}

void Ennemi129::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + 8 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        if (!actif) {
            actif = true;
            recul = 24;
            maxDist = 200;
            anim = 0;
            chrono.reset();
        } else {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_EXPONENTIEL);
            }
        }
    } else {
        idle = true;
    }

    if (actif && chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi129::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (actif) {
        WindowManager::getInstance()->draw(image, 16 * anim, 0, 16, 37, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, 160, 0, 16, 37, dstX, dstY);
    }
}

int Ennemi129::getX() {
    return x;
}

int Ennemi129::getY() {
    return y;
}

BoundingBox* Ennemi129::getBoundingBox() {
    box.setX(x);
    box.setY(y + 21);
    return &box;
}

bool Ennemi129::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return actif;
}
