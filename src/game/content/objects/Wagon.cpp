#include "Wagon.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

Wagon::Wagon(int i, int j, Direction dir) : direction(dir), running(false) {
    x = i - 4;
    y = j - 10;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/wagon.png", true);

    width = 24;
    height = 26;
}

Wagon::~Wagon() {
    ResourceManager::getInstance()->free(image);
}

void Wagon::loop() {
    if (!running) {
        return;
    }
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    int oldX = x;
    int oldY = y;

    if (link->getAnimation() == JUMP_IN_WAGON) {
        if (link->getX() < x + 4) link->setX(link->getX() + 2);
        if (link->getX() > x + 4) link->setX(link->getX() - 2);
        if (link->getY() < y + 2) link->setY(link->getY() + 2);
        if (link->getY() > y + 2) link->setY(link->getY() - 2);
    } else if (link->getAnimation() == WAGON) {
        if (scene->getCoffre(0, 14) == 0) {
            if (x + 4 < 31 * 16 && y + 10 == 23 * 16) moveE();
            else if (y + 10 > 13 * 16 && x + 4 == 31 * 16) moveN();
            else if (x + 4 < 34 * 16 && y + 10 == 13 * 16) moveE();

            else if (x + 4 < 45 * 16 && y + 10 == 13 * 16 && scene->getCoffre(0, 13) == 0) moveE();
            else if (x + 4 < 49 * 16 && y + 10 == 13 * 16 && x + 4 >= 45 * 16) moveE();
            else if (y + 10 < 22 * 16 && x + 4 == 49 * 16) moveS();
            else if (x + 4 < 50 * 16 && y + 10 == 22 * 16) moveE();

            else if (x + 4 == 34 * 16 && y + 10 > 9 * 16 && scene->getCoffre(0, 13) == 1) moveN();
            else if (x + 4 < 41 * 16 && y + 10 == 9 * 16) moveE();
            else if (x + 4 < 45 * 16 && y + 10 == 9 * 16 && scene->getCoffre(0, 13) == 1) moveE();
            else if (y + 10 < 13 * 16 && x + 4 == 45 * 16) moveS();

            else if (x + 4 == 41 * 16 && y + 10 > 5 * 16 && scene->getCoffre(0, 13) == 0) moveN();
            else if (x + 4 > 30 * 16 && y + 10 == 5 * 16) moveW();

            else if (link->getAnimation() == WAGON) {
                AudioManager::getInstance()->playSound(TS_JUMP);
                link->setAnimation(JUMP_OUT_WAGON);
                if (y + 10 == 5 * 16) scene->setCoffre(0, 14, 2);
                if (y + 10 == 22 * 16) scene->setCoffre(0, 14, 1);
            }
        } else if (scene->getCoffre(0, 14) == 1) {
            if (x + 4 > 49 * 16 && y + 10 == 22 * 16) moveW();
            else if (x + 4 == 49 * 16 && y + 10 > 13 * 16) moveN();
            else if (x + 4 > 45 * 16 && y + 10 == 13 * 16) moveW();

            else if (x + 4 > 34 * 16 && y + 10 == 13 * 16 && scene->getCoffre(0, 13) == 0) moveW();
            else if (x + 4 > 31 * 16 && y + 10 == 13 * 16 && x + 4 <= 34 * 16) moveW();
            else if (x + 4 == 31 * 16 && y + 10 < 23 * 16) moveS();
            else if (x + 4 > 29 * 16 && y + 10 == 23 * 16) moveW();

            else if (x + 4 == 45 * 16 && y + 10 > 9 * 16 && scene->getCoffre(0, 13) == 1) moveN();
            else if (x + 4 > 41 * 16 && y + 10 == 9 * 16) moveW();
            else if (x + 4 > 34 * 16 && y + 10 == 9 * 16 && scene->getCoffre(0, 13) == 1) moveW();
            else if (x + 4 == 34 * 16 && y + 10 < 13 * 16) moveS();

            else if (link->getAnimation() == WAGON) {
                AudioManager::getInstance()->playSound(TS_JUMP);
                link->setAnimation(JUMP_OUT_WAGON);
                scene->setCoffre(0, 14, 0);
            }
        } else if (scene->getCoffre(0, 14) == 2) {

            if (x + 4 < 41 * 16 && y + 10 == 5 * 16) moveE();
            else if (x + 4 == 41 * 16 && y + 10 < 9 * 16) moveS();
            else if (x + 4 > 34 * 16 && y + 10 == 9 * 16) moveW();
            else if (x + 4 == 34 * 16 && y + 10 < 13 * 16) moveS();
            else if (x + 4 > 31 * 16 && y + 10 == 13 * 16) moveW();
            else if (x + 4 == 31 * 16 && y + 10 < 23 * 16) moveS();
            else if (x + 4 > 29 * 16 && y + 10 == 23 * 16) moveW();

            else if (link->getAnimation() == WAGON) {
                AudioManager::getInstance()->playSound(TS_JUMP);
                link->setAnimation(JUMP_OUT_WAGON);
                scene->setCoffre(0, 14, 0);
            }
        }
        link->setDirection(direction);
    } else if (link->getAnimation() == JUMP_OUT_WAGON) {
        if (direction == E && link->getX() < x + 4 + 16 * 2) link->setX(link->getX() + 2);
        if (direction == W && link->getX() > x + 4 - 16 * 2) link->setX(link->getX() - 2);
    } else {
        direction = scene->getCoffre(0, 14) == 1 ? W : E;
        running = false;
    }

    if (scene->getAvancement() >= AV_PARLE_GARS_MINE_MINE) {
        if (x + 4 == 31 * 16 && y + 10 == 13 * 16 && direction == N && scene->getCoffre(0, 13) == 0) {
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
            scene->getMap()->switchLevier();
        } else if (x + 4 == 34 * 16 && y + 10 == 9 * 16 && direction == N) {
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
            scene->getMap()->switchLevier();
        } else if (x + 4 == 41 * 16 && y + 10 == 5 * 16 && direction == E && scene->getCoffre(0, 13) == 1) {
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
            scene->getMap()->switchLevier();
        } else if (x + 4 == 34 * 16 && y + 10 == 9 * 16 && direction == W) {
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
            scene->getMap()->switchLevier();
        }
    }

    if (x != oldX || y != oldY) checkPosition();
}

void Wagon::moveN() {
    y -= 2;
    link->setY(link->getY() - 2);
    direction = N;
}

void Wagon::moveS() {
    y += 2;
    link->setY(link->getY() + 2);
    direction = S;
}

void Wagon::moveW() {
    x -= 2;
    link->setX(link->getX() - 2);
    direction = W;
}

void Wagon::moveE() {
    x += 2;
    link->setX(link->getX() + 2);
    direction = E;
}

void Wagon::draw(int offsetX, int offsetY) {
    if (direction == N || direction == S) {
        WindowManager::getInstance()->draw(image, 0, 0, 20, 26, x + 2 - offsetX, y - offsetY);
    } else {
        WindowManager::getInstance()->draw(image, 20, 0, 24, 26, x - offsetX, y - offsetY);
    }
}

bool Wagon::action(Direction dir) {
    if (dir != direction) {
        return false;
    }
    link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    running = true;
    AudioManager::getInstance()->playSound(TS_JUMP);
    link->setAnimation(JUMP_IN_WAGON);
    link->setDirection(direction);
    return true;
}

int Wagon::getDown() {
    if (running) {
        return link->getY() + 24 - 1;
    }
    return y + height;
}
