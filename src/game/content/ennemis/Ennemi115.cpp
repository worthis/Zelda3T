#include "Ennemi115.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi115::Ennemi115(int i, int j) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi115.png", true);
    chrono.reset();

    type = 115;

    x = i;
    y = j;

    // for quadtree operations:
    width = 128;
    height = 91;

    box.setX(x + 32);
    box.setY(y + 27);
    box.setW(64);
    box.setH(64);

    startX = x;
    startY = y;
    startDir = direction;

    life = 100;
    maxLife = 100;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    step = 0;
    anim = 0;
    animMax = 25;
    vanim = 240;
    special = 90;
    maxGel = 0;

    isBoss = false; // will be set to true later
    stunnable = false;

    forceEnn = 10;
}

Ennemi115::~Ennemi115() {
    ResourceManager::getInstance()->free(image);
}

bool Ennemi115::isResetable() {
    return alive;
}

void Ennemi115::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    step = 0;
    anim = 0;
    animMax = 25;
    special = 90;
    maxGel = 0;
    checkPosition();
}

void Ennemi115::ennLoop() {
    if (!isBoss) {
        Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        if (map->getBounds()->getX() == 320 * 3 || map->getId() == 156) {
            isBoss = true;
            step = 0;
            anim = 0;
            animMax = 25;
            special = 90;
            getBoundingBox();
            checkPosition();
            chrono.reset();
        }
    }
    if (step != 0) {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (step == 1) {
        special--;
        if (special <= 0) {
            step = 2;
            animMax = 15;
            special = 0;
            maxGel = 128;
        }
        getBoundingBox();
        checkPosition();
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 0 && isBoss) {
                step = 1;
            } else if (step == 2) {
                if (getLink()->getX() + 16 >= x + 24 && getLink()->getX() <= x + 24 + 80) {
                    step = 3;
                    animMax = 4;
                }
            } else if (step == 3) {
                step = 2;
                animMax = life < 25 ? 5 : 15;
            }
        }
        if (step == 3 && anim == animMax) {
            snipe();
        }
        chrono.reset();
    }

}

void Ennemi115::draw(int offsetX, int offsetY) {
    if (!alive || step == 0) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int srcX = step == 3 ? anim * width : 0;
    int srcW = width;

    if (step == 1) {
        srcX = 24;
        srcW = 80;
        dstX += 24;
    }

    WindowManager::getInstance()->draw(image, srcX, 0, srcW, height-special, dstX, dstY+special);
}

void Ennemi115::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, 0, 0, width, height, x, y);
}

int Ennemi115::getX() {
    return x;
}

int Ennemi115::getY() {
    return y;
}

BoundingBox* Ennemi115::getBoundingBox() {
    box.setX(x + 32);
    box.setY(special == 0 ? y + 27 : y + special);
    box.setH(special == 0 ? 64 : height - special);
    return &box;
}

void Ennemi115::snipe() {
    int origx = x + 64;
    int origy = y + 54;
    ProjectileHelper::getInstance()->addProjectile(TP_ECLAIR, origx, origy, S);
    AudioManager::getInstance()->playSound(TS_MAGIC);
}

bool Ennemi115::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return step > 0 && effect != TE_FEU;
}

void Ennemi115::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156) {
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 70 * 16, 38 * 16 + 8, 9));
    }
    map->killEnnemis(map->getBounds());
}

bool Ennemi115::isToAvoid(Collision c) {
    return false;
}
