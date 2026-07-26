#include "Final.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/texts/TextManager.h"
#include "../../../engine/audio/AudioManager.h"

Final::Final() : anim(0), animMax(29), vanim(128) {
    for (int i = 0; i < 30; i++) {
        images[i] = 0;
    }
}

Final::~Final() {
    for (int i = 0; i < 30; i++) {
        ResourceManager::getInstance()->free(images[i]);
    }
}

void Final::init(int id) {
    ostringstream os1;
    os1 << (id + 1);
    ostringstream os2;
    for (int i = 0; i < 30; i++) {
        ResourceManager::getInstance()->free(images[i]);
        if (i < 10) os2 << "0";
        os2 << i;
        string filename = "data/images/ending/ending_" + os1.str() + "/final/final" + os2.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename);
        os2.str("");
    }
    anim = 0;
    chrono.reset();
}

void Final::handleActions(Action* action) {
    if (action->isAction(ACTION)) {
        AudioManager::getInstance()->playSound(TS_MENU1);
        AudioManager::getInstance()->stopMusic();
        MainController::getInstance()->setStep(LOGO);
    }
}

void Final::loop() {
    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Final::draw() {
    WindowManager::getInstance()->draw(images[anim], 0, 0, 320, 240, 0, 0);
}
