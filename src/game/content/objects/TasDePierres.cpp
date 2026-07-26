#include "TasDePierres.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "Pierre.h"

#include "../effects/Debris.h"

#include "../../MainController.h"

TasDePierres::TasDePierres(int i, int j, int id) : type(id) {
    x = i;
    y = j;

    poids = (type + 1) * 2; // should be 2 or 4

    image = ResourceManager::getInstance()->loadImage("data/images/objects/pierres.png", true);

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

TasDePierres::~TasDePierres() {
    ResourceManager::getInstance()->free(image);
}

void TasDePierres::portLoop() {
    // nothing to do
}

void TasDePierres::draw(int offsetX, int offsetY) {
    WindowManager::getInstance()->draw(image, 0, type * 32, 32, 32, x - offsetX, y - offsetY);
}

Portable* TasDePierres::getPierre() {
    return new Pierre(x+8, y+8, type+7, MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap(), false);
}
