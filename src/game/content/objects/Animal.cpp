#include "Animal.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

Animal::Animal(int i, int j, int t) : type(t), anim(0), animMax(1), vanim(180), direction(S) {
    x = i;
    y = j;

    image = 0;
    switch (type) {
        case 0 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/lapin.png", true);
            width = 16; height = 21; animMax = 2;
            box.setX(0); box.setY(5); box.setW(16); box.setH(16);
            break;
        case 1 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/autruche.png", true);
            width = 24; height = 32; animMax = 3;
            box.setX(4); box.setY(16); box.setW(16); box.setH(16);
            break;
        case 2 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/oiseau.png", true);
            width = 16; height = 32;
            box.setX(0); box.setY(0); box.setW(-1); box.setH(-1);
            break;
        case 3 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/ecureuil.png", true);
            width = 16; height = 21;
            box.setX(0); box.setY(5); box.setW(16); box.setH(16);
            break;
        case 4 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/papillon.png", true);
            width = 7; height = 21;
            box.setX(0); box.setY(0); box.setW(-1); box.setH(-1);
            break;
        case 5 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/mouette.png", true);
            width = 18; height = 32;
            box.setX(0); box.setY(0); box.setW(-1); box.setH(-1);
            break;
        case 6 :
            image = ResourceManager::getInstance()->loadImage("data/images/objects/zero.png", true);
            width = 24; height = 22;
            box.setX(x+4); box.setY(y+3); box.setW(16); box.setH(16);
            break;
    }

    chrono.reset();
}

Animal::~Animal() {
    ResourceManager::getInstance()->free(image);
}

void Animal::loop() {
    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue) {
        case 1 : moveX(-1); direction=W; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1); direction=N; break;
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

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Animal::draw(int offsetX, int offsetY) {
    switch (type) {
        case 0 :
        case 1 :
        case 3 :
            WindowManager::getInstance()->draw(image, width * (direction % 2), height * anim, width, height, x - offsetX, y - offsetY);
            break;
        case 2 :
            WindowManager::getInstance()->draw(image, 0, 30, 16, 6, x - offsetX, y - offsetY + height - 6);
            WindowManager::getInstance()->draw(image, 15 * (direction % 2), 15 * anim, 15, 15, x - offsetX + (direction%2), y - offsetY);
            break;
        case 4 :
            WindowManager::getInstance()->draw(image, 7 * (direction % 2), 7 * anim, 7, 7, x - offsetX, y - offsetY);
            break;
        case 5 :
            WindowManager::getInstance()->draw(image, 0, 28, 18, 6, x - offsetX, y - offsetY + height - 6);
            WindowManager::getInstance()->draw(image, 18 * (direction % 2), 14 * anim, 18, 14, x - offsetX + (direction%2), y - offsetY);
            break;
        case 6 :
            WindowManager::getInstance()->draw(image, width * direction, height * anim, width, height, x - offsetX, y - offsetY);
            break;
    }

}

void Animal::moveX(int dx) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + dx);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb)) {
        x += dx;
    }
    getBoundingBox();

    if (x != oldX) checkPosition();
}

void Animal::moveY(int dy) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + dy);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb)) {
        y += dy;
    }
    getBoundingBox();

    if (y != oldY) checkPosition();
}

bool Animal::isCollision(Collision c) {
    if (type == 2 || type == 4 || type == 5) {
        return true;
    }
    switch (c) {
        case TROU : case HERBE : case HERBE_HAUTE : case TERRE : case EAU :
        case GLACE : case SABLE : case NEIGE :
        case PIERRE : case SOL_BOIS : case TAPIS : case DANGER_BAS : return true;
        default : return false;
    }
}

BoundingBox* Animal::getBoundingBox() {
    switch (type) {
        case 0 : box.setX(x); box.setY(y+5); break;
        case 1 : box.setX(x+4); box.setY(y+16); break;
        case 2 : box.setX(0); box.setY(0); break;
        case 3 : box.setX(x); box.setY(y+5); break;
        case 4 : box.setX(0); box.setY(0); break;
        case 5 : box.setX(0); box.setY(0); break;
        case 6 : box.setX(x+4); box.setY(y+3); break;
    }
    return &box;
}
