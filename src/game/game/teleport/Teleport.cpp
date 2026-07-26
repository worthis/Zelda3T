#include "Teleport.h"

#include "../../MainController.h"

Teleport::Teleport() : currentMap(0), dstMap(0), dstX(0), dstY(0), direction(N), instant(false), reload(true), etage(false) {
}

Teleport::~Teleport() {
}

void Teleport::loop() {
    if (!instant) {
        transition.loop();
        if (transition.isWaiting()) {
            Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
            BoundingBox* box = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCamera()->getBoundingBox();
            mid();
            transition.restart(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
        } else if (transition.isAchieved()) {
            end();
        }
    } else {
        mid();
        end();
    }
}


void Teleport::mid() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();

    link->setX(dstX);
    link->setY(dstY);
    link->setDirection(direction);

    if (!reload) {
        scene->getMap()->resetRoom(); // reset previous room
        scene->getMap()->launchRoom();
        link->startNewRoom();
        if (etage) {
            scene->getHud()->displayEtage();
        }
        link->setAnimation(IDLE);
    } else {
        Map* mp = new Map(dstMap, scene->getMetronome());
        mp->load();
        scene->setMap(mp);
        mp->launch();

        link->startNewMap();
    }
    scene->fixCameraBounds();

    // open door if needed
    if (scene->getMap()->getId() < 46) {
        int x = link->getX();
        int y = link->getY();
        if (scene->getMap()->getSol(x, y + 8 - 1) == 468 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 789 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 790 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 1903 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 1904 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 2276 ||
            scene->getMap()->getSol(x, y + 8 - 1) == 2277) {
            scene->getMap()->ouvrePorteMaison(x, y);
        }
        if (scene->getMap()->getSol(x, y + 8 - 1) == 1362) {
            scene->getMap()->ouvrePorte(x/16, y/16, 0);
        }
        if (scene->getMap()->getSol(x, y + 8 - 1) == 2826) {
            scene->getMap()->ouvrePorte(x/16, y/16, 0);
        }
        if (scene->getMap()->getSol(x, y + 8 - 1) == 1363) {
            scene->getMap()->ouvrePorte((x-16)/16, y/16, 0);
        }
        if (scene->getMap()->getSol(x, y + 8 - 1) == 2827) {
            scene->getMap()->ouvrePorte((x-16)/16, y/16, 0);
        }
    }
}

void Teleport::end() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    transition.reset();
    MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
    scene->getAnimationInGame()->testAnim();

    if (dstMap == 57 && dstMap != currentMap && dstY == 25 * 16 + 8) { // generique
        MainController::getInstance()->getGameController()->displayText(1332);
    } else if (dstMap == 137 && scene->getAvancement() < AV_GANON_CAPTURE && scene->getLink()->getInventory()->hasCristal(3)) {
        MainController::getInstance()->getGameController()->displayText(1062);
    } else if (dstMap >= 46 && dstMap < 61 && !etage && dstMap != currentMap
               && (dstMap != 57 || scene->getAvancement() >= AV_TELE_ZELDA)
               && (dstMap != 58 || scene->getLink()->getInventory()->hasObject(TRIFORCE))) {
        MainController::getInstance()->getGameController()->displayText(1208 + dstMap - 46);
    } else if (dstMap == 57 && scene->getAvancement() < AV_TELE_ZELDA && !etage && dstMap != currentMap) {
        MainController::getInstance()->getGameController()->displayText(1332);
    } else if (dstMap == 56 && dstX == 169*16+8 && dstY > 60*16) {
        MainController::getInstance()->getGameController()->displayText(1279);
    } else if (dstMap == 19 && scene->getAvancement() < AV_TELE_ZELDA && scene->getLink()->getEpee() == 5) {
        MainController::getInstance()->getGameController()->displayText(1298);
    } else if (dstMap == 156 && !etage && scene->getMap()->isIndoor()) {
        MainController::getInstance()->getGameController()->displayText(1723);
    }
}

void Teleport::draw() {
    if (!instant) {
        transition.draw();
    }
}

void Teleport::init() {
    if (!instant) {
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link* link = scene->getLink();
        BoundingBox* box = scene->getCamera()->getBoundingBox();
        transition.start(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
    }
}

void Teleport::setTeleport(int m, int x, int y, Direction dir, bool inst, bool reld, bool etg) {
    currentMap = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getId();
    dstMap = m;
    dstX = x;
    dstY = y;
    direction = dir;
    instant = inst;
    reload = reld;
    etage = etg;

    if (dstMap != currentMap) {
        reload = true;
    }
}

