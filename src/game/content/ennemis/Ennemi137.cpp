#include "Ennemi137.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi137::Ennemi137(int i, int j) : anim(0), animMax(1), vanim(180), cooldown(0), jump(false) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi137.png", true);
    chrono.reset();

    type = 137;

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

    life = 1;
    maxLife = 1;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    forceEnn = 1;
}

Ennemi137::~Ennemi137() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi137::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    cooldown = 0;
    jump = false;
    checkPosition();
}

bool Ennemi137::isResetable() {
    return true;
}

void Ennemi137::ennLoop() {

    if (cooldown) cooldown--;
    if (jump) jump = false;

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

void Ennemi137::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (jump) {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), 52, width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, direction * width + (gel ? 64 : 0), anim * height, width, height, dstX, dstY);
    }

}

int Ennemi137::getX() {
    return x;
}

int Ennemi137::getY() {
    return y;
}

BoundingBox* Ennemi137::getBoundingBox() {
    box.setX(x);
    box.setY(y + 10);
    return &box;
}

bool Ennemi137::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    /*if ((type == TA_SWORD || type == TA_SWORD_HOLD) && cooldown == 0) {
        cooldown = 32;
        jump = true;
        AudioManager::getInstance()->playSound(TS_THROW);
        jumpBack(dir);
        return false;
    } else {*/
        return false;
    //}
}
