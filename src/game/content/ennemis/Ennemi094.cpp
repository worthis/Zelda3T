#include "Ennemi094.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../objects/Pierre.h"

#include "../effects/FumeeBlanche.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi094::Ennemi094(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi94.png", true);
    chrono.reset();

    type = 94;

    cooldown = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 20;
    maxLife = 20;
    recul = 0;
    vitesseRecul = 0;
    step = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi094::~Ennemi094() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi094::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animMax = 1;
    cooldown = 0;
    step = 0;
    checkPosition();
}

bool Ennemi094::isResetable() {
    return alive;
}

void Ennemi094::ennLoop() {

    int v = life > 10 ? 1 : 2;
    for (int i = 0; i < v; i++) {
        if (step == 0) {
            if (x % 320 < 14 * 16 + 4) {
                 moveX(1);
            } else {
                step = 1;
                cooldown = 0;
                anim = 0;
                chrono.reset();
            }
        } else if (step == 2 && cooldown == 0) {
            if (x > getLink()->getX() - 8) {
                 moveX(-1);
            } else {
                Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                Pierre* pierre = new Pierre(x + 8, y - 8, 7, map, false, true);
                pierre->lance(y + 32, S, v*2);
                map->addObject(pierre);
                AudioManager::getInstance()->playSound(TS_THROW);
                step = 0;
            }
        }
    }
    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 1) {
                step = 2;
            }
        }
        chrono.reset();
    }
}

void Ennemi094::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 0, step * height, width, height, dstX, dstY);
    if (step == 2) {
        WindowManager::getInstance()->draw(image, 0, 96, 16, 16, dstX + 8, dstY - 8);
    }
}

void Ennemi094::moveX(int dx) {
    x += dx;
    getBoundingBox();
    checkPosition();
}

int Ennemi094::getX() {
    return x;
}

int Ennemi094::getY() {
    return y;
}

BoundingBox* Ennemi094::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

void Ennemi094::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    AudioManager::getInstance()->playMusic(20);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 1));
    map->setSol(349*16, 36*16, 2, 3, 4002, PIERRE);
    map->addEffect(new FumeeBlanche(350*16, 37*16+8));
}

bool Ennemi094::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return type == TA_MASSIF;
}
