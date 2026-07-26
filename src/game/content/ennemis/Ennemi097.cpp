#include "Ennemi097.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"
#include "../effects/Debris.h"

#include "../helper/ProjectileHelper.h"

Ennemi097::Ennemi097(int i, int j) : anim(0), animMax(3), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi97.png", true);
    chrono.reset();

    type = 97;

    x = i;
    y = j;

    // for quadtree operations:
    width = 54;
    height = 64;

    box.setX(x + 3);
    box.setY(y + 16);
    box.setW(48);
    box.setH(48);

    startX = x;
    startY = y;
    startDir = direction;

    life = 200;
    maxLife = 200;
    recul = 0;
    vitesseRecul = 0;

    step = 0;
    elan = 0;
    colere = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi097::~Ennemi097() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi097::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    step = 0;
    elan = 0;
    colere = 0;
    checkPosition();
}

bool Ennemi097::isResetable() {
    return alive;
}

void Ennemi097::ennLoop() {

    if (step == 0) {
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

        if (getLink()->getStatus()->getVirtualLife() > 0) {
            for (int i = 0; i < 4; i++) {
                BoundingBox hitZone(box.getX(), box.getY(), box.getW(), box.getH());
                switch (i) {
                    case 0 : hitZone.setY(box.getY() - 48); break;
                    case 1 : hitZone.setY(box.getY() + 48); break;
                    case 2 : hitZone.setX(box.getX() - 48); break;
                    case 3 : hitZone.setX(box.getX() + 48); break;
                }
                if (hitZone.intersect(getLink()->getBoundingBox())) {
                    direction = (Direction)i;
                    step = 1;
                    elan = 48;
                    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                    if (map->getId() != 156) {
                        colere++;
                    }
                    animMax = 1;
                    anim = 0;
                    chrono.reset();
                    break;
                }
            }
        }
    } else if (step == 1 && anim == 1) {
        elan -= 2;
        switch (direction) {
            case N : moveY(-2); break;
            case S : moveY(2); break;
            case W : moveX(-2); break;
            case E : moveX(2); break;
        }
        if (elan == 0) {
            if (colere == 10 && getLink()->getStatus()->getVirtualLife() > 0) {
                step = 2;
            } else {
                step = 0;
            }
            animMax = 3;
            anim = 0;
            chrono.reset();
        }
    } else if (step == 2) {
        if (x % 320 < 8*16+5) {moveX(1); direction = E;}
        if (x % 320 > 8*16+5) {moveX(-1); direction = W;}
        if (y % 240 < 5*16) {moveY(1); direction = S;}
        if (y % 240 > 5*16) {moveY(-1); direction = N;}
        if (x % 320 == 8*16+5 && y % 240 == 5*16) {
            step = 3;
            animMax = 5;
            anim = 0;
            direction = S;
            chrono.reset();
        }
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (step == 3 && anim == 4) {
            Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            AudioManager::getInstance()->playSound(TS_BREAK);
            if (x < 320) {
                map->addEffect(new Debris(7 * 16, 35 * 16, direction, 1));
                map->addEffect(new Debris(13 * 16, 35 * 16, direction, 1));
                map->addEffect(new Debris(7 * 16, 40 * 16, direction, 1));
                map->addEffect(new Debris(13 * 16, 40 * 16, direction, 1));
                map->ouvrePorte(x, y, 5);
            } else if (x < 320 * 14) {
                map->addEffect(new Debris(148 * 16, 36 * 16, direction, 1));
                map->addEffect(new Debris(152 * 16, 36 * 16, direction, 1));
                map->addEffect(new Debris(148 * 16, 39 * 16, direction, 1));
                map->addEffect(new Debris(152 * 16, 39 * 16, direction, 1));
                map->ouvrePorte(x, y, 6);
            } else {
                map->addEffect(new Debris(289 * 16, 36 * 16, direction, 1));
                map->addEffect(new Debris(291 * 16, 36 * 16, direction, 1));
                map->addEffect(new Debris(289 * 16, 38 * 16, direction, 1));
                map->addEffect(new Debris(291 * 16, 38 * 16, direction, 1));
                map->ouvrePorte(x, y, 7);
            }
        }
        if (anim > animMax) {
            anim = step == 1 ? 1 : 0;
            if (step == 3) {
                anim = animMax;
            }
        }
        chrono.reset();
    }
}

void Ennemi097::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 0 || step == 2) {
        WindowManager::getInstance()->draw(image, 0, anim * height, width, height, dstX, dstY);
    } else if (step == 1) {
        int srcX = 54 + 49 * (direction / 2);
        int srcY = 0;
        int srcW = 0;
        int srcH = 0;
        switch (direction) {
            case N : srcY = anim * 75; srcW = 49; srcH = 75 - 20 * anim; dstX += 5; dstY -= (11-20*anim); break;
            case S : srcY = 130 + anim * 71; srcW = 45; srcH = 71 - 15 * anim; dstX += 7 - 2 * anim; dstY -= (7-15*anim); break;
            case W : srcY = anim * 68; srcW = 59; srcH = 68 - 19 * anim; dstX += 3 - 3 * anim; dstY -= (4-19*anim); break;
            case E : srcY = 117 + anim * 68; srcW = 59; srcH = 68 - 19 * anim; dstX += 4 - 9 * anim; dstY -= (4-19*anim); break;
        }
        WindowManager::getInstance()->draw(image, srcX, srcY, srcW, srcH, dstX, dstY);
    } else if (step == 3) {
        if (anim / 2 == 0) {
            WindowManager::getInstance()->draw(image, 162, 0, 60, 52, dstX - 6, dstY + 12);
        } else if (anim / 2 == 1) {
            WindowManager::getInstance()->draw(image, 162, 52, 48, 69, dstX + 6, dstY -5);
        } else {
            WindowManager::getInstance()->draw(image, 162, 121, 55, 57, dstX - 6, dstY +13);
        }
    }

}

void Ennemi097::moveX(int dx) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + 3 + dx);

    if (map->checkCollisions(bb, this, true, false, true, false)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Ennemi097::moveY(int dy) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + 16 + dy);

    if (map->checkCollisions(bb, this, false, false, true, false)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

int Ennemi097::getX() {
    return x;
}

int Ennemi097::getY() {
    return y;
}

BoundingBox* Ennemi097::getBoundingBox() {
    box.setX(x + 3);
    box.setY(y + 16);
    return &box;
}

void Ennemi097::afterFall() {
    if (x < 320 * 14) {
        x += 140*16;
        step = 0;
        animMax = 3;
        anim = 0;
        colere = 0;
        elan = 0;
        alive = true;
        getBoundingBox();
        checkPosition();
    } else {
        giveItem(290*16, 37*16);
    }
}

void Ennemi097::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156) {
        AudioManager::getInstance()->playMusic(20);
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 290*16, 33*16+8, 2));
    }
}

bool Ennemi097::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return effect == TE_FEU;
}
