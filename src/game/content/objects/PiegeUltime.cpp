#include "PiegeUltime.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

PiegeUltime::PiegeUltime(int i, int j, bool AF) : anim(0), animMax(16), vanim(120), autoFire(AF), enable(true) {
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/piegeFeu.png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    chrono.reset();
}

PiegeUltime::~PiegeUltime() {
    ResourceManager::getInstance()->free(image);
}

void PiegeUltime::loop() {
    if (!enable) {
        return;
    }
    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (autoFire) snipe();
        }
        chrono.reset();
    }
}

void PiegeUltime::draw(int offsetX, int offsetY) {
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x - offsetX, y - offsetY);
}

void PiegeUltime::snipe() {
    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    int origx = x + 8;
    int origy = y + 8;
    ProjectileHelper::getInstance()->addProjectile(TP_BOULE_ULTIME, origx, origy, link, false, getBoundingBox());
    AudioManager::getInstance()->playSound(TS_THROW);
}

void PiegeUltime::disable() {
    enable = false;
}
