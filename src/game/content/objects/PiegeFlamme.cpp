#include "PiegeFlamme.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

PiegeFlamme::PiegeFlamme(int i, int j, bool rm) : direction(S), anim(0), animMax(2), vanim(180) {
    x = i;
    y = j;
    x0 = x;
    y0 = y;
    dir0 = direction;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/piegeFlamme.png", true);

    // for quadtree operations:
    width = 16;
    height = 32;

    box.setX(x);
    box.setY(y+16);
    box.setW(16);
    box.setH(16);

    force = 8;
    randomMove = rm;

    attackable = true;

    chrono.reset();
}

PiegeFlamme::~PiegeFlamme() {
    ResourceManager::getInstance()->free(image);
}

void PiegeFlamme::loop() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    BoundingBox* bb = getBoundingBox();
    scene->testDegatOnLink(bb, direction, force, TA_MAGIC, TE_FEU);

    if (!randomMove) {
        for (int i = 0; i < 2; i++) {
            if (bb->intersect(scene->getLink()->getBoundingBox())) {
                scene->getLink()->pousseY(1);
            } else {
                break;
            }
        }
    }

    if (randomMove) {
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
    } else if (y < 24 * 16) {
        moveY(1);
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void PiegeFlamme::draw(int offsetX, int offsetY) {
    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, x - offsetX, y - offsetY);
}

BoundingBox* PiegeFlamme::getBoundingBox() {
    box.setX(x);
    box.setY(y+16);
    return &box;
}

void PiegeFlamme::moveX(int dx) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + dx);

    if (scene->checkCollisions(bb, this, false)) {
        x += dx;
    }

    if (x != oldX) {
        checkPosition();
    }
}

void PiegeFlamme::moveY(int dy) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + 16 + dy);

    if (randomMove) {
        scene->testDegatOnLink(bb, S, force, TA_MAGIC, TE_FEU);
    }

    if (!randomMove || scene->checkCollisions(bb, this, false)) {
        y += dy;
    }

    if (y != oldY) {
        checkPosition();
    }
}

bool PiegeFlamme::isResetable() {
    return true;
}

void PiegeFlamme::reset() {
    x = x0;
    y = y0;
    direction = dir0;
    anim = 0;
    chrono.reset();
    checkPosition();
}

void PiegeFlamme::underAttack(Direction dir, int force, TypeAttack t, TypeEffect effect) {
    if (effect == TE_GLACE) alive = false;
}
