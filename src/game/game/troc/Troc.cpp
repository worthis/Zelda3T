#include "Troc.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"


Troc::Troc() : inventory(0) {
    imageMenu = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    imageItems = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    for (int i = 0; i < 28; i++) {
        texts[i] = 0;
    }
}

Troc::~Troc() {
    ResourceManager::getInstance()->free(imageMenu);
    ResourceManager::getInstance()->free(imageItems);
    for (int i = 0; i < 28; i++) {
        delete texts[i];
    }
}

void Troc::handleActions(Action* action) {
    if (action->isAction(TROC)) {
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
}

void Troc::init() {
    inventory = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory();

    for (int i = 0; i < 28; i++) {
        delete texts[i];
    }

    for (int i = 0; i < 28; i++) {
        texts[i] = TextManager::getInstance()->getText(308 + i);
    }
}

void Troc::draw() {

    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(imageMenu, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    drawTitre();
    drawObjects();
}

void Troc::drawTitre() {
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[0]->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(imageMenu, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(imageMenu, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(imageMenu, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++) {
        x += 16;
        WindowManager::getInstance()->draw(imageMenu, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(imageMenu, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(imageMenu, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(imageMenu, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(imageMenu, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(imageMenu, 32, 32, 16, 16, x, 32);

    texts[0]->display(32 + 8 + ((blocs * 16) - size) / 2, 16);
}

void Troc::drawObjects() {
    drawCadre(16, 16 * 3, 16 * 18, 16 * 11);

    int dstX = 24;
    int dstY = 58;
    int txt = 0;

    for (int i = 0; i < 16; i++) {
        if (inventory->getTroc(i) > -1) {
            WindowManager::getInstance()->draw(imageItems, 160 + 16 * (i%4), 128 + 16 * ((int)(i/4)), 16, 16, dstX, dstY);
            switch (i) {
                case 0 : txt = inventory->getTroc(i) > 1 ? 1 : 2; break;
                case 1 : txt = inventory->getTroc(i) > 1 ? 3 : 4; break;
                case 2 : txt = inventory->getTroc(i) > 1 ? 5 : 6; break;
                case 3 : txt = inventory->getTroc(i) > 1 ? 7 : 8; break;
                case 4 : txt = inventory->getTroc(i) > 1 ? 9 : 10; break;
                case 5 : txt = inventory->getTroc(i) > 1 ? 11 : 12; break;
                case 6 : txt = inventory->getTroc(i) > 1 ? 13 : 14; break;
                case 7 : txt = inventory->getTroc(i) > 1 ? 15 : 16; break;
                case 8 : txt = inventory->getTroc(i) > 1 ? 17 : 18; break;
                case 9 : txt = inventory->getTroc(i) > 1 ? 19 : 20; break;
                case 10 : txt = inventory->getTroc(i) > 1 ? 21 : 22; break;
                case 11 : txt = 23; break;
                case 12 : txt = 24; break;
                case 13 : txt = 25; break;
                case 14 : txt = 26; break;
                case 15 : txt = 27; break;
            }
            texts[txt]->display(dstX + 20, dstY);
        }


        dstY += 20;
        if (dstY > 198) {
            dstY = 58;
            dstX += 136;
        }
    }
}

void Troc::drawCadre(int x, int y, int w, int h) {

    // center
    for (int j = y + 16; j < y + h - 16; j += 16) {
        for (int i = x + 16; i < x + w - 16; i += 16) {
            WindowManager::getInstance()->draw(imageMenu, 16, 64, 16, 16, i, j);
        }
    }

    //top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16) {
        WindowManager::getInstance()->draw(imageMenu, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(imageMenu, 16, 80, 16, 16, i, y + h - 16);
    }

    //left and right
    for (int j = y + 16; j < y + h - 16; j += 16) {
        WindowManager::getInstance()->draw(imageMenu, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(imageMenu, 32, 64, 16, 16, x + w - 16, j);
    }

    //top left corner
    WindowManager::getInstance()->draw(imageMenu, 0, 48, 16, 16, x, y);

    //top right corner
    WindowManager::getInstance()->draw(imageMenu, 32, 48, 16, 16, x + w - 16, y);

    //bottom left corner
    WindowManager::getInstance()->draw(imageMenu, 0, 80, 16, 16, x, y + h - 16);

    //bottom right corner
    WindowManager::getInstance()->draw(imageMenu, 32, 80, 16, 16, x + w - 16, y + h - 16);

}
