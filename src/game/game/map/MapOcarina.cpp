#include "MapOcarina.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

#include "../../../config/ConfigurationManager.h"

MapOcarina::MapOcarina() : started(false), teleport(false), position(0), offsetForme(0), offsetSkin(0) {
    imageLink = ResourceManager::getInstance()->loadImage("data/images/maps/link.png", true);

    imageMap[0] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-1-1.png");
    imageMap[1] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-1-2.png");
    imageMap[2] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-1.png");
    imageMap[3] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-2.png");
    imageMap[4] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-3.png");
    imageMap[5] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-2-4.png");
    imageMap[6] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-3-1.png");
    imageMap[7] = ResourceManager::getInstance()->loadImage("data/images/maps/overworld-3-2.png");
    imageMapId = 3;
}

MapOcarina::~MapOcarina() {
    ResourceManager::getInstance()->free(imageLink);
    for (int i = 0; i < 8; i++) {
        ResourceManager::getInstance()->free(imageMap[i]);
    }
}

void MapOcarina::handleActions(Action* action) {
    if (teleport || !started) return;
    if (action->isAction(ACTION)) {
        AudioManager::getInstance()->playSound(TS_TELEPORT, 2);
        teleport = true;
        return;
    }
    if (action->isAction(QUIT_GAME)) {
        started = false;
        MainController::getInstance()->getGameController()->hideMap();
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    int old = position;
    if (action->isAction(MAP_1)) position = 0;
    if (action->isAction(MAP_2)) position = 1;
    if (action->isAction(MAP_3)) position = 2;
    if (action->isAction(MAP_4)) position = 3;
    if (action->isAction(MAP_5)) position = 4;
    if (action->isAction(MAP_6)) position = 5;
    if (action->isAction(MAP_7)) position = 6;
    if (action->isAction(MAP_8)) position = 7;
    if (action->isAction(MAP_9)) position = 8;

    if (action->isAction(PUSH_UP) || action->isAction(PUSH_LEFT)) {
        if (--position < 0) position = 8;
    }
    if (action->isAction(PUSH_DOWN) || action->isAction(PUSH_RIGHT)) {
        if (++position > 8) position = 0;
    }

    if (old != position) {
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void MapOcarina::loop() {
    if (!started) return;
    if (teleport && !AudioManager::getInstance()->isPlaying(2)) {
        MainController::getInstance()->getGameController()->hideMap();

        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        int offsetTime = scene->getMap()->getEpoque() == EP_FUTUR ? 30 : scene->getMap()->getEpoque() == EP_PRESENT ? 15 : 0;
        switch (position) {
            case 0 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8 + offsetTime, 39 * 16 + 8, 14 * 16, S, true, true); break;
            case 1 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7 + offsetTime, 84 * 16, 12 * 16, S, true, true); break;
            case 2 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6 + offsetTime, 62 * 16 + 8, 15 * 16, S, true, true); break;
            case 3 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13 + offsetTime, 42 * 16 + 8, 38 * 16, S, true, true); break;
            case 4 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1 + offsetTime, 39 * 16 + 8, 42 * 16, S, true, true); break;
            case 5 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3 + offsetTime, 39 * 16 + 8, 53 * 16, S, true, true); break;
            case 6 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12 + offsetTime, 45 * 16, 40 * 16, S, true, true); break;
            case 7 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11 + offsetTime, 72 * 16 + 8, 60 * 16, S, true, true); break;
            case 8 : MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(10 + offsetTime, 50 * 16, 31 * 16, S, true, true); break;
            default : return;
        }
        MainController::getInstance()->getGameController()->getTeleportController()->loop();
        int i = position;
        MainController::getInstance()->getGameController()->setStep(GAME_MAP);
        position = i;
        started = false;
        teleport = false;
    }
}

void MapOcarina::draw() {
    WindowManager::getInstance()->draw(imageMap[imageMapId], 0, 0, 320, 240, 0, 0);

    displayLinkOrNumber(position == 0, 161, 12, '1');
    displayLinkOrNumber(position == 1, 271, 11, '2');
    displayLinkOrNumber(position == 2, 305, 53, '3');
    displayLinkOrNumber(position == 3, 38, 87, '4');
    displayLinkOrNumber(position == 4, 35, 157, '5');
    displayLinkOrNumber(position == 5, 160, 140, '6');
    displayLinkOrNumber(position == 6, 40, 209, '7');
    displayLinkOrNumber(position == 7, 189, 227, '8');
    displayLinkOrNumber(position == 8, 294, 201, '9');
}

void MapOcarina::launch() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    switch (scene->getMap()->getEpoque()) {
        case EP_PASSE : imageMapId = scene->getAvancement() < AV_TEMPLE_DEESSES_APPARU ? 0 : 1; break;
        case EP_PRESENT :
            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PONT_CONSTRUIT) imageMapId = 2;
            else if (scene->getCoffre(0, 2)) imageMapId = 5;
            else if (link->getInventory()->getTroc(TT_ROUAGE) == 0) imageMapId = 4;
            else imageMapId = 3;
            break;
        case EP_FUTUR : imageMapId = (!link->getInventory()->hasObject(FLECHE_FEU) || !link->getInventory()->hasObject(FLECHE_GLACE)
                || !link->getInventory()->hasObject(FLECHE_LUMIERE) || !link->getInventory()->hasObject(FLACON_4)) ? 6 : 7; break;
        default : break;
    }
    offsetSkin = ConfigurationManager::getInstance()->getSkin() * 15;
    offsetForme = link->getStatus()->isOniLink() ? 30 : 0;
    position = 0;
    started = true;
    teleport = false;
}

void MapOcarina::displayLinkOrNumber(bool link, int dstX, int dstY, char nb) {
    if (link) {
        WindowManager::getInstance()->draw(imageLink, offsetForme, offsetSkin, 14, 12, dstX - 7, dstY - 8);
    } else {
        TextManager::getInstance()->drawLetter(nb, dstX - 4, dstY - 10, 0);
    }
}
