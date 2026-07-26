#include "GameController.h"

#include "../keys/KeyBinder.h"

GameController::GameController() : needLoad(true), timeOffset(0) {
}

GameController::~GameController() {
}

void GameController::launch() {
    chrono.reset();
    setStep(GAME_MAIN);
}

void GameController::handleEvents(Event* event) {
    if (!transition.isRunning()) {

        Action* action = KeyBinder::getInstance()->getActionForGame(event);
        switch(step) {
            case GAME_MAIN : scene.handleActions(action); break;
            case GAME_MENU : menu.handleActions(action); break;
            case GAME_TEXT : case GAME_GENERIC : text.handleActions(action); break;
            case GAME_OCARINA : ocarina.handleActions(action); break;
            case GAME_MAP : map.handleActions(action); break;
            case GAME_HELP : help.handleActions(action); break;
            case GAME_MONSTERS : monsters.handleActions(action); break;
            case GAME_FISH : fish.handleActions(action); break;
            case GAME_TROC : troc.handleActions(action); break;
            default : break;
        }

    }
    // Escape should not end the game
    if (event->isPushed(kEscape)) {
        event->setEvent(kEscape, false);
    }
}

void GameController::loop() {
    if (transition.isRunning()) {
        return;
    }
    switch(step) {
        case GAME_MAIN : scene.loop(); break;
        case GAME_MENU : menu.loop(); break;
        case GAME_TEXT : case GAME_GENERIC : text.loop(); break;
        case GAME_SWITCH_MAP : transitionMaps.loop(); break;
        case GAME_SWITCH_ROOM : transitionRooms.loop(); break;
        case GAME_SWITCH_TIME : transitionTimes.loop(); break;
        case GAME_TELEPORT : teleport.loop(); break;
        case GAME_OCARINA : ocarina.loop(); break;
        case GAME_MAP : map.loop(); break;
        case GAME_HELP : help.loop(); break;
        case GAME_MONSTERS : monsters.loop(); break;
        case GAME_FISH : fish.loop(); break;
        case GAME_TROC : troc.loop(); break;
        default : break;
    }
}

void GameController::draw() {
    switch(step) {
        case GAME_MAIN : case GAME_OCARINA : case GAME_SWITCH_ROOM : scene.draw(); break;
        case GAME_MENU : scene.draw(); menu.draw(); break;
        case GAME_TEXT : scene.draw(); text.draw(); break;
        case GAME_SWITCH_MAP : transitionMaps.draw(); break;
        case GAME_SWITCH_TIME : transitionTimes.draw(); break;
        case GAME_TELEPORT : scene.draw(); teleport.draw(); break;
        case GAME_MAP : map.draw(); break;
        case GAME_HELP : help.draw(); break;
        case GAME_MONSTERS : monsters.draw(); break;
        case GAME_FISH : fish.draw(); break;
        case GAME_TROC : troc.draw(); break;
        case GAME_GENERIC : generic.draw(); text.draw(); break;
        default : break;
    }

    if (transition.isRunning()) {
        transition.loop();
        transition.draw();

        if (transition.isWaiting()) {
            setStep(nextStep);
            transition.restart();
        } else if (transition.isAchieved()) {
            transition.reset();
            if (step == GAME_MAIN) {
                if (scene.getScene()->getMap()->getId() == 57 && scene.getScene()->getAvancement() == AV_RETOUR_PRESENT) displayText(1332);
            }
        }
    }
}

void GameController::setStep(GameStep newStep) {
    step = newStep;
    switch(step) {
        case GAME_MAIN : if (needLoad) {scene.launch(save); menu.init(); needLoad = false;} break;
        case GAME_MENU : menu.launch(); break;
        case GAME_TEXT : case GAME_GENERIC : text.launch(); break;
        case GAME_SWITCH_MAP : transitionMaps.launch(); break;
        case GAME_SWITCH_ROOM : transitionRooms.launch(); break;
        case GAME_SWITCH_TIME : transitionTimes.launch(); break;
        case GAME_TELEPORT : teleport.launch(); break;
        case GAME_OCARINA : ocarina.launch(); break;
        case GAME_MAP : map.launch(); break;
        case GAME_HELP : help.launch(); break;
        case GAME_MONSTERS : monsters.launch(); break;
        case GAME_FISH : fish.launch(); break;
        case GAME_TROC : troc.launch(); break;
        default : break;
    }
}

void GameController::setSave(Save* sv) {
    save = sv;
    timeOffset = save->getTime();
    needLoad = true;
}

void GameController::displayText(int id) {
    text.setTextId(id);
    setStep(GAME_TEXT);
}

void GameController::displayGeneric(int id) {
    generic.setId(id);
    text.setTextId(id == 0 ? 1385 : 1386);
    nextStep = GAME_GENERIC;
    transition.start();
}

void GameController::hideGeneric() {
    if (step != GAME_GENERIC) return;
    nextStep = GAME_MAIN;
    transition.start();
}

void GameController::displayMap(int mapId, bool withTp) {
    if (mapId >= 61 && mapId != 156) return;
    map.setStep(mapId, withTp);
    nextStep = GAME_MAP;
    transition.start();
}

void GameController::hideMap() {
    if (step != GAME_MAP) return;
    nextStep = GAME_MAIN;
    transition.start();
}

bool GameController::isTransitionRoom() {
    return step == GAME_SWITCH_ROOM;
}

bool GameController::isTeleport() {
    return step == GAME_TELEPORT;
}

SceneController* GameController::getSceneController() {
    return &scene;
}

GameMenuController* GameController::getGameMenuController() {
    return &menu;
}

TextController* GameController::getTextController() {
    return &text;
}

TeleportController* GameController::getTeleportController() {
    return &teleport;
}

OcarinaController* GameController::getOcarinaController() {
    return &ocarina;
}

MapController* GameController::getMapController() {
    return &map;
}

TransitionTimesController* GameController::getTransitionTimesController() {
    return &transitionTimes;
}

void GameController::saveData(bool endGame) {
    scene.saveData();
    save->setTime(timeOffset + (chrono.getElapsedTime() / 1000));
    save->save(endGame);
}

int GameController::getTime() {
    int t = timeOffset + (chrono.getElapsedTime() / 1000);
    if (t > 359999) t = 359999;
    return t;
}

Save* GameController::getSave() {
    return save;
}

