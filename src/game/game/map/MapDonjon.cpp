#include "MapDonjon.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../../config/ConfigurationManager.h"

#include "../../MainController.h"

MapDonjon::MapDonjon() : anim(0), animMax(1), vanim(480), started(false), xLink(0), yLink(0), offsetForme(0), offsetSkin(0), lapin(false) {
    wasFrench = ConfigurationManager::getInstance()->isFrench();
    if (wasFrench) {
        imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon.png");
        imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level.png");
        imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2.png");
    } else {
        imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon_us.png");
        imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level_us.png");
        imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2_us.png");
    }

    imageLink = ResourceManager::getInstance()->loadImage("data/images/maps/link.png", true);
    imageBoussole = ResourceManager::getInstance()->loadImage("data/images/maps/boussole.png", true);

    for (int i = 0; i < 5; i++) imageEtages[i] = 0;
    for (int i = 0; i < 5; i++) imageEtagesN[i] = 0;
    previousMapId = -1;
    previousEpoque = EP_RIEN;
}

MapDonjon::~MapDonjon() {
    ResourceManager::getInstance()->free(imageMap);
    ResourceManager::getInstance()->free(imageLevel);
    ResourceManager::getInstance()->free(imageLevel2);
    ResourceManager::getInstance()->free(imageLink);
    ResourceManager::getInstance()->free(imageBoussole);
    for (int i = 0; i < 5; i++) ResourceManager::getInstance()->free(imageEtages[i]);
    for (int i = 0; i < 5; i++) ResourceManager::getInstance()->free(imageEtagesN[i]);
}

void MapDonjon::handleActions(Action* action) {
    if (!started) return;
    if (action->isAction(DISPLAY_MAP) || action->isAction(QUIT_GAME)) {
        started = false;
        MainController::getInstance()->getGameController()->hideMap();
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCoffre(mapId == 156 ? 16 : mapId - 45, 0)) {

        int old = etage;
        int min = getEtageMin();
        int max = getEtageMax();

        if (action->isAction(PUSH_UP)) {
            if (++etage > max) etage = min;
        }
        if (action->isAction(PUSH_DOWN)) {
            if (--etage < min) etage = max;
        }

        if (old != etage) {
            AudioManager::getInstance()->playSound(TS_MENU3);
            //prepareMap();
            anim = 0;
            chrono.reset();
        }

    }
}

void MapDonjon::loop() {
    if (!started) return;
    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void MapDonjon::draw() {

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    WindowManager::getInstance()->draw(imageMap, 0, 0, 320, 240, 0, 0);
    TextManager::getInstance()->getText(mapId == 156 ? 1724 : 1229 + mapId - 45)->display(120 + 2, 24 + 2);

    if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 0)) {

        if (lapin) {
            WindowManager::getInstance()->draw(imageLink, 14, offsetSkin, 16, 15, 24, 64 + (2 - scene->getMap()->getEtage()) * 16);
        } else {
            WindowManager::getInstance()->draw(imageLink, offsetForme, offsetSkin, 14, 12, 24 + 1, 64 + (2 - scene->getMap()->getEtage()) * 16 + 2);
        }

        if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 1) && bossIsAlive()) {
            WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8, 72 + 4, 64 + (2 - getEtageBoss()) * 16 + 4);
        }

        drawMap();

        ItemHelper::getInstance()->drawItem(TI_CARTE_DONJON, 28 + 8, 192 + 8);

        int min = getEtageMin();
        int max = getEtageMax();
        WindowManager::getInstance()->draw(imageLevel, 0, (2 - max) * 16, 32, (max - min + 1) * 16, 40, 64 + (2 - max) * 16);
        WindowManager::getInstance()->draw(imageLevel2, 0, (2 - etage) * 16, 32, 16, 40, 64 + (2 - etage) * 16);

        if (anim == 0 && scene->getMap()->getEtage() == etage) {
            if (lapin) {
                WindowManager::getInstance()->draw(imageLink, 14, offsetSkin, 16, 15, xLink - 7, yLink - 6);
            } else {
                WindowManager::getInstance()->draw(imageLink, offsetForme, offsetSkin, 14, 12, xLink - 6, yLink - 4);
            }
        }
    }
    if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 1)) {
        ItemHelper::getInstance()->drawItem(TI_BOUSSOLE, 48 + 8, 192 + 8);
    }
    if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 2)) {
        ItemHelper::getInstance()->drawItem(TI_CLE_BOSS, 68 + 8, 192 + 8);
    }
}

void MapDonjon::launch() {

    if (ConfigurationManager::getInstance()->isFrench() != wasFrench) {
        wasFrench = !wasFrench;
        ResourceManager::getInstance()->free(imageMap);
        ResourceManager::getInstance()->free(imageLevel);
        ResourceManager::getInstance()->free(imageLevel2);
        if (wasFrench) {
            imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon.png");
            imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level.png");
            imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2.png");
        } else {
            imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon_us.png");
            imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level_us.png");
            imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2_us.png");
        }
    }

    offsetSkin = ConfigurationManager::getInstance()->getSkin() * 15;

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    offsetForme = scene->getLink()->getStatus()->isOniLink() ? 30 : 0;

    lapin = scene->getLink()->isLapin();

    mapId = scene->getMap()->getId();
    etage = scene->getMap()->getEtage();
    epoque = scene->getMap()->getEpoque();

    if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 0)) {
        loadImages();
    }

    anim = 0;
    chrono.reset();

    started = true;
}

void MapDonjon::drawMap() {

    int w = getWidth();
    int h = getHeight();
    int dx = getOffsetX();
    int dy = getOffsetY();

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            WindowManager::getInstance()->draw(scene->getRooms(mapId == 156 ? 15 : mapId - 46, i + dx, j + dy) ? imageEtages[2 - etage] : imageEtagesN[2 - etage],
                                           i * 16, j * 16, 16, 16,
                                           128 + (((10 - w) / 2) + i) * 16,
                                           48 + (((10 - h) / 2) + j) * 16);
        }
    }

    if (scene->getMap()->getEtage() == etage) {
        Link* link = scene->getLink();
        xLink = 128 + (((10 - w) / 2)) * 16 + ((link->getX() - getOffsetX() * 320) / 20);
        yLink = 48 + (((10 - h) / 2)) * 16 + ((link->getY() - getOffsetY() * 240) / 15);
    }

    if (scene->getCoffre(mapId == 156 ? 16 : mapId - 45, 1)) {
        switch (mapId) {
            case 46 :
                if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 25)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + ((10 - w) / 2) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(ARC)) { // arc
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                } else if (etage == 1) {
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == 2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + ((10 - w) / 2) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasMedaillon(0)) { // medaillon
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 8)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                }
                break;
            case 47 :
                if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                } else if (etage == -2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasMedaillon(1)) { // medaillon
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 20)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 3) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(GANTS)) { // gants
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 4,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7 - 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7 + 8,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7 + 8);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 5) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7 + 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 8)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7 - 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 9)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                }
                break;
            case 48 :
                if (etage == 0) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + ((10 - w) / 2) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 28)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 6) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(LANTERNE)) { // lanterne
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 6) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7 + 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 9)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                } else if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7 + 4,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7 - 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 8)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 + 4,
                                                           48 + (((10 - h) / 2) + 3) * 16 + 7 - 2);
                    }
                } else if (etage == -2) {
                    if (!scene->getLink()->getInventory()->hasMedaillon(2)) { // medaillon
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                }
                break;
            case 49 :
                if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 20)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(PALMES)) { // palmes
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7 - 4,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7);
                    }
                } else if (etage == -2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 4 + 8,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4 + 8);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7);
                    }
                }
                break;
            case 50 :
                if (etage == 0) {
                    if (!scene->getCoffre(mapId - 45, 41)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 5);
                    }
                    if (scene->getLink()->getTunique() < 2) { // tunique
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7 - 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                } else if (etage == -1) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(CLE_TEMPS)) { // cle temps
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7 + 8,
                                                           48 + (((10 - h) / 2) + 5) * 16 + 7 + 8);
                    }
                }
                break;
            case 51 :
                if (etage == 0) {
                    if (!scene->getCoffre(mapId - 45, 28)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 5);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 3) * 16 + 7);
                    }
                } else if (etage == -1) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4 + 16);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(MARTEAU)) { // marteau
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                }
                break;
            case 52 :
                if (etage == 0) {
                    if (!scene->getCoffre(mapId - 45, 24)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(GANTS_2)) { // gants 2
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 3) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 + 2);
                    }
                } else if (etage == -1) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(TROC_GEMME_JAUNE)) { // gemme jaune
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                }
                break;
            case 53 :
                if (etage == -2) {
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                } if (etage == 1) {
                    if (!scene->getCoffre(mapId - 45, 27)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + ((10 - w) / 2) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(ARC_FEE)) { // arc fee
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7 - 4,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 + 8);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                } if (etage == 2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 4,
                                                           48 + ((10 - h) / 2) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(TROC_GEMME_VERTE)) { // gemme verte
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                }
                break;
            case 54 :
                if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 56)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                           48 + ((10 - h) / 2) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(BAGUETTE_GLACE)) { // baguette glace
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7 + 8,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 5) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 8)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 5) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 9)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 3) * 16 + 7);
                    }
                } else if (etage == -2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 4 + 8,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(TROC_GEMME_BLEUE)) { // gemme bleue
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7 + 8,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 10)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 11)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 12)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 - 4);
                    }
                }
                break;
            case 55 :
                if (etage == 0) {
                    if (!scene->getLink()->getInventory()->hasObject(TROC_GEMME_ROUGE)) { // gemme rouge
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 56)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 5,
                                                           48 + ((10 - h) / 2) * 16 + 5);
                    }
                    if (!scene->getLink()->getInventory()->hasObject(BAGUETTE_FEU)) { // baguette feu
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == -2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 7)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 6) * 16 + 7 + 2,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7 - 4);
                    }
                }
                break;
            case 56 :
                if (etage == 0) {
                    if (!scene->getCoffre(mapId - 45, 19)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 6) * 16 + 5);
                    }
                    if (scene->getLink()->getBouclier() < 3) { // bouclier 3
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 6) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                } else if (etage == 1) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4);
                    }
                    if (scene->getLink()->getEpee() < 5) { // triforce
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                }
                break;
            case 57 :
                if (etage == 1) {
                    if (bossIsAlive() && !scene->getMonsters(50)) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 4,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 4);
                    }
                    if (bossIsAlive() && scene->getMonsters(50)) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 4,
                                                           48 + ((10 - h) / 2) * 16 + 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 6)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == 0) {
                    if (scene->getLink()->getBouclier() == 0) { // bouclier 1
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 2,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 6) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7 - 2,
                                                           48 + (((10 - h) / 2) + 6) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 12)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7 - 4,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                    if (!scene->getCoffre(mapId - 45, 13)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7 - 2);
                    }
                } else if (etage == -1) {
                    if (scene->getLink()->getTunique() < 3) { // tunique 3
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 6) * 16 + 7);
                    }
                } else if (etage == -2) {
                    if (!scene->getCoffre(mapId - 45, 11)) { // mini boss
                        WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                           128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 5);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7 + 2,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7 - 2);
                    }
                }
                break;
            case 58 :
                if (scene->getLink()->getBouclier() < 4) { // bouclier 4
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7 - 2,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (bossIsAlive()) { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 4);
                }
                if (!scene->getCoffre(mapId - 45, 2)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 45, 4)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 45, 5)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 45, 6)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 45, 7)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 45, 8)) {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 6) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 6) * 16 + 7);
                }
                break;
            case 59 :
                if (etage == -1) {
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == 0) {
                    if (!scene->getCoffre(mapId - 45, 5)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 7);
                    }
                } else if (etage == 2) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 4 + 8,
                                                           48 + (((10 - h) / 2) + 2) * 16 + 4);
                    }
                    if (scene->getLink()->getTunique() < 4) { // tunique 4
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7 + 8 - 2,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + ((10 - w) / 2) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 1) * 16 + 7);
                    }
                }
                break;
            case 60 :
                if (etage == -1) {
                    if (!scene->getLink()->getInventory()->hasObject(MASQUE)) { // masque oni link
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                } else if (etage == 0) {
                    if (bossIsAlive()) { // boss
                        WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                           128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                           48 + ((10 - h) / 2) * 16 + 4);
                    }
                    if (!scene->getCoffre(mapId - 45, 2)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                           48 + ((10 - h) / 2) * 16 + 7);
                    }
                    if (!scene->getCoffre(mapId - 45, 4)) {
                        WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                           128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                           48 + (((10 - h) / 2) + 4) * 16 + 7);
                    }
                }
                break;
            case 156 :
                if (epoque == EP_PASSE) {
                    if (etage == 2) {
                        if (!scene->getCoffre(16, 2)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                    }
                } else if (epoque == EP_PRESENT) {
                    if (etage == -1) {
                        if (!scene->getCoffre(16, 4)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + ((10 - w) / 2) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 8)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 3) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 10)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                    } else if (etage == 0) {
                        if (!scene->getCoffre(16, 5)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 2) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 6)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 7)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 2) * 16 + 7);
                        }
                    } else if (etage == 1) {
                        if (!scene->getCoffre(16, 9)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                    } else if (etage == 2) {
                        if (bossIsAlive()) { // boss
                            WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 4,
                                                               48 + ((10 - h) / 2) * 16 + 4);
                        }
                    }
                } else {
                    if (etage == -1) {
                        if (!scene->getCoffre(17, 43)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + ((10 - w) / 2) * 16 + 5,
                                                               48 + ((10 - h) / 2) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 44)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + ((10 - w) / 2) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 3) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 45)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + ((10 - w) / 2) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 4) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 46)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                               48 + ((10 - h) / 2) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 47)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 48)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 3) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 49)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 2) * 16 + 5 + 8,
                                                               48 + (((10 - h) / 2) + 4) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 50)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 5,
                                                               48 + ((10 - h) / 2) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 51)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 3) * 16 + 5);
                        }
                        if (!scene->getCoffre(17, 52)) { // mini boss
                            WindowManager::getInstance()->draw(imageBoussole, 10, 0, 6, 6,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 5,
                                                               48 + (((10 - h) / 2) + 4) * 16 + 5);
                        }
                        if (!scene->getCoffre(16, 12)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + ((10 - w) / 2) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 2) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 13)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 14)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 17)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 18)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 2) * 16 + 7);
                        }
                    } else if (etage == 0) {
                        if (!scene->getCoffre(16, 16)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 7);
                        }
                    } else if (etage == 1) {
                        if (!scene->getCoffre(16, 11)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + ((10 - w) / 2) * 16 + 7,
                                                               48 + ((10 - h) / 2) * 16 + 7);
                        }
                        if (!scene->getCoffre(16, 15)) {
                            WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                               128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                               48 + (((10 - h) / 2) + 1) * 16 + 7 + 8);
                        }
                    }
                }
                break;
        }
    }
}

int MapDonjon::getWidth() {
    switch (mapId) {
        case 46 : case 53 : case 59 : return 4;
        case 47 : case 49 : case 54 : return 6;
        case 48 : case 55 : case 58 : case 60 : return 7;
        case 50 : case 51 : case 52 :
            if (etage == 2) return 1;
            if (etage == 1) return 3;
            if (etage == 0) return 5;
            return 7;
        case 56 : return 7 - etage * 4;
        case 57 :
            if (etage >= 0) return 7 - etage * 4;
            if (etage == -1) return 8;
            return 7;
        case 156 : return 5;
        default : return 0;
    }
}

int MapDonjon::getHeight() {
    switch (mapId) {
        case 46 : case 53 : case 59 : return 4;
        case 47 : case 49 : case 54 : return 6;
        case 48 : case 55 : case 60 : case 156 : return 5;
        case 50 : case 51 : case 52 :
            if (etage == 2) return 1;
            if (etage == 1) return 3;
            if (etage == 0) return 5;
            return 7;
        case 56 : case 58 : return 7;
        case 57 :
            if (etage >= 0) return 7;
            if (etage == -1) return 8;
            return 3;
        default : return 0;
    }
}

int MapDonjon::getOffsetX() {
    switch (mapId) {
        case 46 : case 59 : return (etage + 1) * 4;
        case 47 : return etage * (-6);
        case 48 : return etage * (-7);
        case 49 : case 54 : return (etage * (-6)) - 5;
        case 50 : case 51 : case 52 :
            if (etage == 2) return 0;
            if (etage == 1) return 1;
            if (etage == 0) return 4;
            return 9;
        case 53 :
            if (etage == 0 || etage == -2) return 0;
            if (etage == 1 || etage == -1) return 4;
            return 8;
        case 55 : case 58 : case 60 : return 0;
        case 56 : return etage * 7;
        case 57 :
            if (etage >=0) return etage * 7;
            if (etage == -1) return 0;
            return 0;
        case 156 : return epoque * 5;
        default : return 0;
    }
}

int MapDonjon::getOffsetY() {
    switch (mapId) {
        case 46 : case 47 : case 48 : case 49 : case 54 : case 56 : case 58 : case 59 : return 0;
        case 50 : case 51 : case 52 :
            if (etage == 2) return 3;
            if (etage == 1) return 2;
            if (etage == 0) return 1;
            return 0;
        case 53 : return etage < 0 ? 4 : 0;
        case 55 : return (etage + 2) * 5;
        case 57 :
            if (etage >= 0) return 0;
            if (etage == -1) return 6;
            return 14;
        case 60 : return (etage + 1) * 5;
        case 156 : return 15 - ((etage + 1) * 5);
        default : return 0;
    }
}

void MapDonjon::loadImages() {
    if (previousMapId != mapId || previousEpoque != epoque) {
        for (int i = 0; i < 5; i++) {
            ResourceManager::getInstance()->free(imageEtages[i]);
            imageEtages[i] = 0;
            ResourceManager::getInstance()->free(imageEtagesN[i]);
            imageEtagesN[i] = 0;
        }

        switch (mapId) {
            case 46 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e-1.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e-1.png");
                break;
            case 47 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d2e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d2e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d2e-2.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd2e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd2e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd2e-2.png");
                break;
            case 48 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d3e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d3e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d3e-2.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd3e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd3e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd3e-2.png");
                break;
            case 49 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e-2.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e-2.png");
                break;
            case 50 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e-1.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e-1.png");
                break;
            case 51 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e-1.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e-1.png");
                break;
            case 52 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e-1.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e-1.png");
                break;
            case 53 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e-2.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e-2.png");
                break;
            case 54 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e-2.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e-2.png");
                break;
            case 55 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d10e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d10e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d10e-2.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd10e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd10e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd10e-2.png");
                break;
            case 56 :
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d11e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d11e0.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd11e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd11e0.png");
                break;
            case 57 :
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d12e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d12e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d12e-1.png");
                imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d12e-2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd12e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd12e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd12e-1.png");
                imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd12e-2.png");
                break;
            case 58 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d13e0.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd13e0.png");
                break;
            case 59 :
                imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d14e2.png");
                imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d14e1.png");
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d14e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d14e-1.png");
                imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd14e2.png");
                imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd14e1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd14e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd14e-1.png");
                break;
            case 60 :
                imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d15e0.png");
                imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d15e-1.png");
                imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd15e0.png");
                imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd15e-1.png");
                break;
            case 156 :
                if (epoque == EP_PASSE) {
                    imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e2a.png");
                    imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e1a.png");
                    imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e0a.png");
                    imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e-1a.png");
                    imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e2a.png");
                    imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e1a.png");
                    imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e0a.png");
                    imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e-1a.png");
                } else if (epoque == EP_PRESENT) {
                    imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e2b.png");
                    imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e1b.png");
                    imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e0b.png");
                    imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e-1b.png");
                    imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e2b.png");
                    imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e1b.png");
                    imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e0b.png");
                    imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e-1b.png");
                } else {
                    imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e2c.png");
                    imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e1c.png");
                    imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e0c.png");
                    imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d16e-1c.png");
                    imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e2c.png");
                    imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e1c.png");
                    imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e0c.png");
                    imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd16e-1c.png");
                }
                break;
            default : return;
        }

        previousMapId = mapId;
        previousEpoque = epoque;
    }
}

int MapDonjon::getEtageMin() {
    switch (mapId) {
        case 46 : case 50 : case 51 : case 52 : case 59 : case 60 : case 156 : return -1;
        case 47 : case 48 : case 49 : case 53 : case 54 : case 55 : case 57 : return -2;
        case 56 : case 58 : return 0;
        default : return 0;
    }
}

int MapDonjon::getEtageMax() {
    switch (mapId) {
        case 46 : case 50 : case 51 : case 52 : case 53 : case 59 : case 156 : return 2;
        case 47 : case 48 : case 49 : case 54 : case 55 : case 58 : case 60 : return 0;
        case 56 : case 57 : return 1;
        default : return 0;
    }
}

int MapDonjon::getEtageBoss() {
    switch (mapId) {
        case 46 : case 53 : case 59 : case 156 : return 2;
        case 47 : case 49 : case 54 : case 55 : return -2;
        case 48 : case 58 : case 60 : return 0;
        case 50 : case 51 : case 52 : return -1;
        case 56 : case 57 : return 1;
        default : return 0;
    }
}

bool MapDonjon::bossIsAlive() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (mapId) {
        case 46 : return !scene->getLink()->getInventory()->hasCoeur(0);
        case 47 : return !scene->getLink()->getInventory()->hasCoeur(1);
        case 48 : return !scene->getLink()->getInventory()->hasCoeur(2);
        case 49 : return !scene->getLink()->getInventory()->hasCoeur(3);
        case 50 : return !scene->getLink()->getInventory()->hasCoeur(4);
        case 51 : return !scene->getLink()->getInventory()->hasCoeur(5);
        case 52 : return !scene->getLink()->getInventory()->hasCoeur(6);
        case 53 : return !scene->getLink()->getInventory()->hasCoeur(7);
        case 54 : return !scene->getLink()->getInventory()->hasCoeur(8);
        case 55 : return !scene->getLink()->getInventory()->hasCoeur(9);
        case 56 : return !scene->getLink()->getInventory()->hasCoeur(10);
        case 57 : return true;
        case 58 : return !scene->getLink()->getInventory()->hasCoeur(11);
        case 59 : return !scene->getLink()->getInventory()->hasCoeur(12);
        case 60 : return true;
        case 156 : return epoque == EP_PRESENT;
        default : return false;
    }
}
