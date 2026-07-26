#include "Help.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../../config/ConfigurationManager.h"

Help::Help() : page(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    for (int i = 0; i < 33; i++) {
        texts[i] = 0;
    }
}

Help::~Help() {
    ResourceManager::getInstance()->free(image);
    for (int i = 0; i < 33; i++) {
        delete texts[i];
    }
}

void Help::init() {

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    total = 5;
    if (link->getEpee()) total += 2;
    if (link->getInventory()->hasObject(BOTTES)) total++;
    if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS)) total++;
    if (link->getInventory()->hasObject(SAC_TROC)) total++;
    if (link->getInventory()->hasObject(ENCYCLOPEDIE)) total++;
    if (link->getInventory()->hasObject(CARTE)) total++;
    if (link->getInventory()->hasObject(MASQUE)) total += 2;

    page = 0;
    pageMax = total > 7 ? 2 : 1;


    for (int i = 0; i < 33; i++) {
        delete texts[i];
    }

    for (int i = 0; i < 18; i++) {
        texts[i] = TextManager::getInstance()->getText(1672 + i);
    }

    KeyBinder* kb = KeyBinder::getInstance();
    texts[18] = kb->getTextForType(BT_EPEE);
    texts[19] = kb->getTextForType(BT_ACTION);
    texts[20] = kb->getTextForType(BT_OBJET);
    texts[21] = kb->getTextForType(BT_INVENTAIRE);
    texts[22] = kb->getTextForType(BT_COURSE);
    texts[23] = kb->getTextForType(BT_CAMERA);
    texts[24] = kb->getTextForType(BT_POISSONS);
    texts[25] = kb->getTextForType(BT_TROC);
    texts[26] = kb->getTextForType(BT_MONSTERS);
    texts[27] = kb->getTextForType(BT_CARTE);
    texts[28] = kb->getTextForType(BT_OPTIONS);
    texts[29] = kb->getTextForType(BT_ONILINK);
    texts[30] = kb->getTextForType(BT_TELEPORT);

    if (pageMax == 1) {
        texts[31] = TextManager::getInstance()->getText(1690);
        texts[32] = TextManager::getInstance()->getText(1691);
    }
}

void Help::cadre(int x, int y, int w, int h) {

    // center
    for (int j = y + 16; j < y + h - 16; j += 16) {
        for (int i = x + 16; i < x + w - 16; i += 16) {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    //top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16) {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    //left and right
    for (int j = y + 16; j < y + h - 16; j += 16) {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    //top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    //top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    //bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    //bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);
}

void Help::handleActions(Action* action) {
    if (action->isAction(AIDE)) {
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
    if (action->isAction(PUSH_LEFT) && page > 0) {
        page--;
        AudioManager::getInstance()->playSound(TS_MENU3);
        return;
    }
    if (action->isAction(PUSH_RIGHT) && page < 1 && pageMax > 1) {
        page++;
        AudioManager::getInstance()->playSound(TS_MENU3);
        return;
    }
}

void Help::draw() {
    int letterSize = TextManager::getInstance()->getWSpace();

    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    cadre(16, 56, 288, 128);
    cadre(16, 200, 288, 32);

    // title

    Text* title = pageMax == 2 ? texts[page] : texts[31];
    int size = title->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++) {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    title->display(32 + 8 + ((blocs * 16) - size) / 2, 16);

    // footer

    Text* footer = pageMax == 2 ? texts[2 + page] : texts[32];
    footer->display(24, 208);

    // content

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    int y = 64;
    if (page == 0) {

        if (link->getEpee()) {
            texts[4]->display(24, y);
            size = texts[18]->getLength() * letterSize;
            texts[18]->display(16 + 288 - 10 - size, y);
            y += 16;

            texts[5]->display(24, y);
            y += 16;
        }

        texts[6]->display(24, y);
        size = texts[19]->getLength() * letterSize;
        texts[19]->display(16 + 288 - 10 - size, y);
        y += 16;

        texts[8]->display(24, y);
        size = texts[21]->getLength() * letterSize;
        texts[21]->display(16 + 288 - 10 - size, y);
        y += 16;

        texts[7]->display(24, y);
        size = texts[20]->getLength() * letterSize;
        texts[20]->display(16 + 288 - 10 - size, y);
        y += 16;

        if (link->getInventory()->hasObject(BOTTES)) {
            texts[9]->display(24, y); // courrir
            size = texts[22]->getLength() * letterSize;
            texts[22]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        texts[10]->display(24, y);
        size = texts[23]->getLength() * letterSize;
        texts[23]->display(16 + 288 - 10 - size, y);
        y += 16;

        if (y < 176 && link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS)) {
            texts[11]->display(24, y);
            size = texts[24]->getLength() * letterSize;
            texts[24]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (y < 176 && link->getInventory()->hasObject(SAC_TROC)) {
            texts[12]->display(24, y);
            size = texts[25]->getLength() * letterSize;
            texts[25]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (y < 176 && link->getInventory()->hasObject(ENCYCLOPEDIE)) {
            texts[13]->display(24, y);
            size = texts[26]->getLength() * letterSize;
            texts[26]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (y < 176 && link->getInventory()->hasObject(CARTE)) {
            texts[14]->display(24, y);
            size = texts[27]->getLength() * letterSize;
            texts[27]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (link->getInventory()->hasObject(MASQUE)) { // oni link
            if (y < 176) {
                texts[16]->display(24, y);
                size = texts[29]->getLength() * letterSize;
                texts[29]->display(16 + 288 - 10 - size, y);
                y += 16;
            }

            if (y < 176) {
                texts[17]->display(24, y);
                size = texts[30]->getLength() * letterSize;
                texts[30]->display(16 + 288 - 10 - size, y);
                y += 16;
            }
        }

        if (y < 176) { // save / quit
            texts[15]->display(24, y);
            size = texts[28]->getLength() * letterSize;
            texts[28]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

    } else {

        int indexDebut = 0;
        if (!link->getEpee()) indexDebut+=2;
        if (!link->getInventory()->hasObject(BOTTES)) indexDebut++;

        if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS) && indexDebut-- <= 0) {
            texts[11]->display(24, y);
            size = texts[24]->getLength() * letterSize;
            texts[24]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (link->getInventory()->hasObject(SAC_TROC) && indexDebut-- <= 0) {
            texts[12]->display(24, y);
            size = texts[25]->getLength() * letterSize;
            texts[25]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (link->getInventory()->hasObject(ENCYCLOPEDIE) && indexDebut-- <= 0) {
            texts[13]->display(24, y);
            size = texts[26]->getLength() * letterSize;
            texts[26]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (link->getInventory()->hasObject(CARTE) && indexDebut-- <= 0) {
            texts[14]->display(24, y);
            size = texts[27]->getLength() * letterSize;
            texts[27]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        if (link->getInventory()->hasObject(MASQUE) && indexDebut-- <= 0) { // oni link
            texts[16]->display(24, y);
            size = texts[29]->getLength() * letterSize;
            texts[29]->display(16 + 288 - 10 - size, y);
            y += 16;
        }
        if (link->getInventory()->hasObject(MASQUE) && indexDebut-- <= 0) {
            texts[17]->display(24, y);
            size = texts[30]->getLength() * letterSize;
            texts[30]->display(16 + 288 - 10 - size, y);
            y += 16;
        }

        texts[15]->display(24, y);// save / quit
        size = texts[28]->getLength() * letterSize;
        texts[28]->display(16 + 288 - 10 - size, y);
        y += 16;

    }
}
