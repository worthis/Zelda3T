#include "Ennemi077.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi077::Ennemi077(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi77.png", true);
    chrono.reset();

    type = 77;

    x = i;
    y = j;

    // for quadtree operations:
    width = 42;
    height = 30;

    box.setX(x+13);
    box.setY(y+12);
    box.setW(16);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 64;

    items.addType(TI_BOMBE, 40);
    items.addType(TI_RUBIS_BLEU, 20);
    items.addType(TI_RUBIS_BLEU, 10);

    forceEnn = 12;
}

Ennemi077::~Ennemi077() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi077::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi077::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
    if (dist <= maxDist) {
        for (int i = 0; i < 2 ; i++) {
            pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

            move(dir.first, dir.second);

            if (link->getBoundingBox()->intersect(getBoundingBox())) {
                testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
            }
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

void Ennemi077::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction * width, anim * height, width, height, dstX, dstY);
}

int Ennemi077::getX() {
    return x;
}

int Ennemi077::getY() {
    return y;
}

BoundingBox* Ennemi077::getBoundingBox() {
    box.setX(x + 13);
    box.setY(y + 12);
    return &box;
}

void Ennemi077::giveItem(int i, int j) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    int nbLoups = scene->getCoffre(0, 1);
    if (nbLoups < 101) {
        scene->setCoffre(0, 1, ++nbLoups);
    }
    Ennemi::giveItem(i, j);
}
