#include "Ennemi108.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi108::Ennemi108(int i, int j) : anim(0), animMax(2), vanim(180), cooldown(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi108.png", true);
    chrono.reset();

    type = 108;

    x = i;
    y = j;

    // for quadtree operations:
    width = 42;
    height = 35;

    box.setX(x + 5);
    box.setY(y + 3);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 40;
    maxLife = 40;
    recul = 32;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 8;
}

Ennemi108::~Ennemi108() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi108::reset() {
    Ennemi::reset();
    x = startX;
    y = startY;
    direction = startDir;
    chrono.reset();
    anim = 0;
    cooldown = 0;
}

bool Ennemi108::isResetable() {
    return alive;
}

void Ennemi108::ennLoop() {

    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue) {
        case 1 : moveX(-1);direction=W; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1);direction=N; break;
        case 4 : moveY(1); direction=S; break;
        default :
            if (randomValue < 10) break;
            switch (direction) {
                case N : moveY(-1); break;
                case S : moveY(1); break;
                case W : moveX(-1); break;
                case E : moveX(1); break;
            }
            break;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        cooldown++;
        if (cooldown == 16) {
            Link* link = getLink();
            int origx = (direction % 2) * 18 + x + 12;
            int origy = y + 24;
            ProjectileHelper::getInstance()->addProjectile(TP_BOULE_ULTIME, origx, origy, link);
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi108::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, (direction % 2) * width, anim * height, width, height, dstX, dstY);

}

void Ennemi108::moveX(int dx) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + 5 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Ennemi108::moveY(int dy) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + 3 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

int Ennemi108::getX() {
    return x;
}

int Ennemi108::getY() {
    return y;
}

BoundingBox* Ennemi108::getBoundingBox() {
    box.setX(x + 5);
    box.setY(y + 3);
    return &box;
}

bool Ennemi108::isToAvoid(Collision c) {
    return false;
}
