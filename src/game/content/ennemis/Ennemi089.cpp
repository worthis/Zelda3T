#include "Ennemi089.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi089::Ennemi089(int i, int j, int a, bool ko) : anim(0), animMax(1), vanim(120) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi89.png", true);
    chrono.reset();

    type = 89;

    x = i;
    y = j;

    // for quadtree operations:
    width = 20;
    height = 26;

    box.setX(x+2);
    box.setY(y+10);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 50;
    maxLife = 50;
    recul = 32;
    vitesseRecul = 4;

    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    isBoss = map->getId() != 57 || map->getBounds()->getY() == 0;
    stunnable = false;

    forceEnn = a == 0 ? 12 : 40;

    animSword = 0;
    isKo = ko;
    speed = 2;
    weapon = a;
}

Ennemi089::~Ennemi089() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi089::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animSword = 0;
    isKo = false;
    recul = 32;
    vitesseRecul = 4;
    checkPosition();
}

bool Ennemi089::isResetable() {
    return !isKo;
}

void Ennemi089::ennLoop() {

    if (isKo) return;

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();

    if (map->getId() == 57 && map->getBounds()->getY() == 240) {
        if (y > 15*16 && direction == N) {
            idle = false;
            y--;
        }
        if (chrono.getElapsedTime() >= vanim) {
            anim++;
            if (anim > animMax) {
                anim = 0;
            }
            chrono.reset();
        }
        return;
    }


    if (animSword) {
        if (chrono.getElapsedTime() >= 40) {
            animSword++;
            chrono.reset();
        }
        if (animSword > 3 + weapon) {
            animSword = 0;
            anim = 0;
            idle = true;
        } else {
            BoundingBox hitZone;
            if (weapon == 0) {
                switch (animSword) {
                    case 1 :
                        if (direction == N) {hitZone.setX(x - 5); hitZone.setY(y - 7); hitZone.setW(8); hitZone.setH(14);}
                        if (direction == S) {hitZone.setX(x + 16); hitZone.setY(y - 6); hitZone.setW(8); hitZone.setH(14);}
                        if (direction == W) {hitZone.setX(x + 16); hitZone.setY(y - 1); hitZone.setW(8); hitZone.setH(14);}
                        if (direction == E) {hitZone.setX(x - 6); hitZone.setY(y - 1); hitZone.setW(8); hitZone.setH(14);}
                        break;
                    case 2 :
                        if (direction == N) {hitZone.setX(x - 8); hitZone.setY(y - 3); hitZone.setW(12); hitZone.setH(16);}
                        if (direction == S) {hitZone.setX(x + 13); hitZone.setY(y); hitZone.setW(14); hitZone.setH(31);}
                        if (direction == W) {hitZone.setX(x - 15); hitZone.setY(y); hitZone.setW(16); hitZone.setH(16);}
                        if (direction == E) {hitZone.setX(x + 17); hitZone.setY(y); hitZone.setW(16); hitZone.setH(16);}
                        break;
                    case 3 :
                        if (direction == N) {hitZone.setX(x); hitZone.setY(y - 8); hitZone.setW(8); hitZone.setH(18);}
                        if (direction == S) {hitZone.setX(x + 12); hitZone.setY(y + 22); hitZone.setW(12); hitZone.setH(19);}
                        if (direction == W) {hitZone.setX(x - 21); hitZone.setY(y + 10); hitZone.setW(21); hitZone.setH(8);}
                        if (direction == E) {hitZone.setX(x + 18); hitZone.setY(y + 10); hitZone.setW(21); hitZone.setH(8);}
                        break;
                }
            } else {
                switch (animSword) {
                    case 1 :
                        if (direction == N) {hitZone.setX(x - 12); hitZone.setY(y - 7); hitZone.setW(15); hitZone.setH(15);}
                        if (direction == S) {hitZone.setX(x + 16); hitZone.setY(y - 8); hitZone.setW(15); hitZone.setH(15);}
                        if (direction == W) {hitZone.setX(x + 16); hitZone.setY(y - 1); hitZone.setW(15); hitZone.setH(15);}
                        if (direction == E) {hitZone.setX(x - 13); hitZone.setY(y - 1); hitZone.setW(15); hitZone.setH(15);}
                        break;
                    case 2 :
                        if (direction == N) {hitZone.setX(x - 1); hitZone.setY(y - 10); hitZone.setW(13); hitZone.setH(17);}
                        if (direction == S) {hitZone.setX(x + 7); hitZone.setY(y); hitZone.setW(13); hitZone.setH(36);}
                        if (direction == W) {hitZone.setX(x - 18); hitZone.setY(y + 7); hitZone.setW(20); hitZone.setH(13);}
                        if (direction == E) {hitZone.setX(x + 16); hitZone.setY(y + 7); hitZone.setW(20); hitZone.setH(13);}
                        break;
                    case 3 :
                        if (direction == N) {hitZone.setX(x - 1); hitZone.setY(y - 14); hitZone.setW(13); hitZone.setH(22);}
                        if (direction == S) {hitZone.setX(x + 10); hitZone.setY(y + 21); hitZone.setW(13); hitZone.setH(21);}
                        if (direction == W) {hitZone.setX(x - 23); hitZone.setY(y + 8); hitZone.setW(23); hitZone.setH(13);}
                        if (direction == E) {hitZone.setX(x + 18); hitZone.setY(y + 8); hitZone.setW(23); hitZone.setH(13);}
                        break;
                    case 4 :
                        if (direction == N) {hitZone.setX(x - 1); hitZone.setY(y - 17); hitZone.setW(13); hitZone.setH(25);}
                        if (direction == S) {hitZone.setX(x + 10); hitZone.setY(y + 21); hitZone.setW(13); hitZone.setH(24);}
                        if (direction == W) {hitZone.setX(x - 28); hitZone.setY(y + 8); hitZone.setW(28); hitZone.setH(13);}
                        if (direction == E) {hitZone.setX(x + 18); hitZone.setY(y + 8); hitZone.setW(28); hitZone.setH(13);}
                        break;
                }
            }
            if (hitZone.intersect(getLink()->getBoundingBox())) {
                testDegatOnLink(&hitZone, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
        }
    } else {

        // retrieve target position ( = link ^^)
        Link* link = getLink();

        int dstX = link->getX() + 8;
        int dstY = link->getY() + 24;

        int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
        if (dist <= maxDist) {
            for (int s = 0; s < speed; s++) {
                pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

                move(dir.first, dir.second);

                if (link->getBoundingBox()->intersect(getBoundingBox())) {
                    testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
                }
            }
        } else {
            idle = true;
        }

        BoundingBox hitZone(box.getX(), box.getY(), box.getW(), box.getH());
        if (weapon == 0) {
            switch (direction) {
                case N :
                    hitZone.setY(box.getY() - 16);
                    break;
                case S :
                    hitZone.setY(box.getY() + 16);
                    break;
                case W :
                    hitZone.setX(box.getX() - 16);
                    break;
                case E :
                    hitZone.setX(box.getX() + 16);
                    break;
            }
        } else {
            switch (direction) {
                case N :
                    hitZone.setY(box.getY() - 24);
                    hitZone.setH(24);
                    break;
                case S :
                    hitZone.setY(box.getY() + 16 - 5);
                    hitZone.setH(24);
                    break;
                case W :
                    hitZone.setX(box.getX() - 24);
                    hitZone.setW(24);
                    break;
                case E :
                    hitZone.setX(box.getX() + 16);
                    hitZone.setW(24);
                    break;
            }
        }
        if (hitZone.intersect(link->getBoundingBox())) {
            animSword = 1;
            chrono.reset();
        } else if (chrono.getElapsedTime() >= vanim) {
            anim++;
            if (anim > animMax) {
                anim = 0;
            }
            chrono.reset();
        }

    }
}

void Ennemi089::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (isKo) {
        WindowManager::getInstance()->draw(image, 0, 78, 23, 14, dstX - 2, dstY + 12);
    } else if (animSword) {
        if (weapon == 0) {
            switch (direction) {
                case N :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 224, 0, 25, 33, dstX - 5, dstY - 7);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 224, 33, 28, 29, dstX - 8, dstY - 3);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 224, 62, 19, 34, dstX, dstY - 8);
                    break;
                case S :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 252, 0, 23, 32, dstX + 1, dstY - 6);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 252, 32, 26, 30, dstX + 1, dstY + 1);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 252, 62, 19, 38, dstX + 1, dstY + 3);
                    break;
                case W :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 278, 0, 24, 27, dstX, dstY - 1);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 278, 27, 28, 26, dstX - 15, dstY);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 278, 53, 34, 25, dstX - 21, dstY + 1);
                    break;
                case E :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 312, 0, 24, 27, dstX - 6, dstY - 1);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 312, 27, 28, 26, dstX + 5, dstY);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 312, 53, 34, 25, dstX + 5, dstY + 1);
                    break;
            }
        } else {
            switch (direction) {
                case N :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 80, 0, 32, 33, dstX - 12, dstY - 7);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 80, 33, 21, 36, dstX - 1, dstY - 10);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 80, 69, 21, 40, dstX - 1, dstY - 14);
                    if (animSword == 4) WindowManager::getInstance()->draw(image, 80, 109, 21, 43, dstX - 1, dstY - 17);
                    break;
                case S :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 112, 0, 30, 34, dstX + 1, dstY - 8);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 112, 34, 26, 30, dstX + 1, dstY + 1);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 112, 69, 22, 39, dstX + 1, dstY + 3);
                    if (animSword == 4) WindowManager::getInstance()->draw(image, 112, 108, 22, 42, dstX + 1, dstY + 3);
                    break;
                case W :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 142, 0, 31, 27, dstX, dstY - 1);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 142, 27, 31, 26, dstX - 18, dstY);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 142, 53, 36, 25, dstX - 23, dstY + 1);
                    if (animSword == 4) WindowManager::getInstance()->draw(image, 142, 78, 41, 25, dstX - 28, dstY + 1);
                    break;
                case E :
                    if (animSword == 1) WindowManager::getInstance()->draw(image, 183, 0, 31, 27, dstX - 13, dstY - 1);
                    if (animSword == 2) WindowManager::getInstance()->draw(image, 183, 27, 31, 26, dstX + 5, dstY);
                    if (animSword == 3) WindowManager::getInstance()->draw(image, 183, 53, 36, 25, dstX + 5, dstY + 1);
                    if (animSword == 4) WindowManager::getInstance()->draw(image, 183, 78, 41, 25, dstX + 5, dstY + 1);
                    break;
            }
        }
    } else if (idle) {
        WindowManager::getInstance()->draw(image, direction * width, 0, width, height, dstX, dstY);
    } else {
        WindowManager::getInstance()->draw(image, direction * width, (anim + 1) * height, width, height, dstX, dstY);
    }
}

int Ennemi089::getX() {
    return x;
}

int Ennemi089::getY() {
    return y;
}

BoundingBox* Ennemi089::getBoundingBox() {
    box.setX(x + 2);
    box.setY(y + 10);
    return &box;
}

bool Ennemi089::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return !isKo;
}

void Ennemi089::afterHit() {
    if (life <= 0) {
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        scene->setMonsters(type);
        life = 1;
        isKo = true;
        recul = 0;
        vitesseRecul = 0;
        animSword = 0;
        anim = 0;
        MainController::getInstance()->getGameController()->displayText(1061);
        AudioManager::getInstance()->stopMusic();
        AudioManager::getInstance()->playSound(TS_DOOR);
        scene->getMap()->ouvrePorte(9, 13, 0);
        scene->getHud()->setBossLife(0, maxLife);
        isBoss = false;
    }
}

bool Ennemi089::canDie(TypeEffect effect) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    return map->getId() == 57;
}

void Ennemi089::setDirection(Direction dir) {
    direction = N;
}

void Ennemi089::giveItem(int x, int y) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_TRIFORCE, x, y));
}
