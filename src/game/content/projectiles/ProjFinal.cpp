#include "ProjFinal.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

ProjFinal::ProjFinal(int i, int j, double dx, double dy) : dx(dx), dy(dy) {
    x = i - 15;
    y = j - 15;
    longX = i;
    longY = j;

    if (dx > 0) {
        if (dy > 0) {
            if (dx > dy) direction = E;
            else direction = S;
        } else {
            if (dx > -dy) direction = E;
            else direction = N;
        }
    } else {
        if (dy > 0) {
            if (-dx > dy) direction = W;
            else direction = S;
        } else {
            if (-dx > -dy) direction = W;
            else direction = N;
        }
    }

    // for quadtree operations:
    width = 31;
    height = 31;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    vanim = 120;
    anim = 0;
    animMax = 3;
    chrono.reset();

    force = 80;

    image = ResourceManager::getInstance()->loadImage("data/images/projectiles/final.png", true);
}

ProjFinal::~ProjFinal() {
    ResourceManager::getInstance()->free(image);
}

void ProjFinal::projLoop() {
    if (!alive) {
        return;
    }

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // compute bounding box for collisions
    box.setX(longX - 15 + dx); box.setY(longY - 15 + dy);

    longX += dx;
    longY += dy;

    x = longX - 15;
    y = longY - 15;

    if (scene->testDegatOnLink(getBoundingBox(), direction, force, TA_MAGIC, TE_FEU)
         || scene->testDegat(getBoundingBox(), direction, force, TA_MAGIC, TE_FEU, false, false)) {
        alive = false;
        return;
    }

    if (!scene->checkCollisions(&box, (Collisionable*)this, false, false, false, false, false)) {
        alive = false;
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void ProjFinal::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = longX - 15 - offsetX;
    int dstY = longY - 15 - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

BoundingBox* ProjFinal::getBoundingBox() {
    box.setX(longX - 15);
    box.setY(longY - 15);
    return &box;
}

int ProjFinal::getX() {return x;}
int ProjFinal::getY() {return y;}
int ProjFinal::getDown() {return y + 240;}
