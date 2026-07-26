#include "Scene.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../config/ConfigurationManager.h"
#include "../../MainController.h"

Scene::Scene() : step(SCENE_MAIN), save(0), map(0), link(0), hud(0), avancement(AV_START) {
    metronome = new Metronome(120, ANIM_REFRESH);
    metronome->reset();

    filterNight = new WImage(320, 240, 0, 0, 255, 80);

    ostringstream os;
    for (int i = 0; i < 3; i++) {
        os << (i + 1);
        string filenameForest = "data/images/tileset/foret" + os.str() + ".png";
        filterForest[i] = ResourceManager::getInstance()->loadImage(filenameForest);
        string filenameRain = "data/images/tileset/pluie" + os.str() + ".png";
        filterRain[i] = ResourceManager::getInstance()->loadImage(filenameRain, true);
        string filenameSky = "data/images/tileset/fond" + os.str() + ".png";
        filterSky[i] = ResourceManager::getInstance()->loadImage(filenameSky);
        string filenameSnow = "data/images/tileset/neige" + os.str() + ".png";
        filterSnow[i] = ResourceManager::getInstance()->loadImage(filenameSnow, true);
        os.str("");
    }
    planeAndUfo = ResourceManager::getInstance()->loadImage("data/images/tileset/ciel.png", true);
    lightning = ResourceManager::getInstance()->loadImage("data/images/tileset/eclair.png", true);
    godnesses = ResourceManager::getInstance()->loadImage("data/images/tileset/deesses.png", true);

    displayPlane = false;
    displayUfo = false;
    displayLightning1 = false;
    displayLightning2 = false;
    filtreForest2 = 0;
}

Scene::~Scene() {
    delete metronome;
    delete map;
    delete link;
    delete hud;

    ResourceManager::getInstance()->free(filterNight);
    ResourceManager::getInstance()->free(planeAndUfo);
    ResourceManager::getInstance()->free(lightning);
    ResourceManager::getInstance()->free(godnesses);
    for (int i = 0; i < 3; i++) {
        ResourceManager::getInstance()->free(filterForest[i]);
        ResourceManager::getInstance()->free(filterRain[i]);
        ResourceManager::getInstance()->free(filterSky[i]);
        ResourceManager::getInstance()->free(filterSnow[i]);
    }
}

void Scene::init(Save* sv) {
    save = sv;

    delete map;
    delete link;
    delete hud;

    avancement = sv->getAvancement();

    for (int j = 0; j < COFFRES_MAX_SIZE; j++) {
        for (int i = 0; i < NB_COFFRES; i++) {
            coffres[i][j] = sv->getCoffre(i, j);
        }
    }

    for (int j = 0; j < MAX_ROOMS_Y; j++) {
        for (int i = 0; i < MAX_ROOMS_X; i++) {
            for (int d = 0; d < NB_DONJON; d++) {
                rooms[d][i][j] = sv->getRooms(d, i, j);
            }
        }
    }

    for (int i = 0; i < NB_MONSTERS; i++) {
        monsters[i] = sv->getMonsters(i);
    }

    for (int i = 0; i < NB_POISSONS; i++) {
        poissons[i] = sv->getPoissons(i);
    }

    link = new Link(save, metronome);
    hud = new Hud(link->getStatus(), link->getInventory(), ConfigurationManager::getInstance()->isFrench());

    map = new Map(save->getMap(), metronome);
    map->load();

    animation.testAnim();
    map->launch();

    if (map->getId() >= 46 && map->getId() < 61
        && (map->getId() != 57 || avancement >= AV_TELE_ZELDA)
        && (map->getId() != 58 || link->getInventory()->hasObject(TRIFORCE))) {
        MainController::getInstance()->getGameController()->displayText(1208 + map->getId() - 46);
    }
    if (map->getId() == 57 && avancement < AV_TELE_ZELDA) {
        MainController::getInstance()->getGameController()->displayText(1332);
    } else if (map->getId() == 137 && avancement < AV_GANON_CAPTURE && link->getInventory()->hasCristal(3)) {
        MainController::getInstance()->getGameController()->displayText(1062);
    }
    if (map->getId() == 156) {
        MainController::getInstance()->getGameController()->displayText(1723);
    }
    /*if (map->getId() == 26 && map->getEtage() == -2) {
        MainController::getInstance()->getGameController()->displayText(358);
    } else if (map->getId() < 15 && avancement == AV_ONI_LINK_FREE) {
        MainController::getInstance()->getGameController()->displayText(346);
    } else if (map->getId() == 18 && link->getEpee() > 1) {
        MainController::getInstance()->getGameController()->displayText(132);
    } else if (map->getId() >= 15 && map->getId() < 23) {
        MainController::getInstance()->getGameController()->displayText(124 + map->getId() - 15);
    } else if (map->getId() >= 23 && map->getId() < 29) {
        MainController::getInstance()->getGameController()->displayText(133 + map->getId() - 23);
    }*/

    // open door if needed
    if (map->getId() < 46) {
        int x = link->getX();
        int y = link->getY();
        if (map->getSol(x, y + 8 - 1) == 468 || map->getSol(x, y + 8 - 1) == 789 || map->getSol(x, y + 8 - 1) == 790) {
            map->ouvrePorteMaison(x, y);
        }
        if (map->getSol(x, y + 8 - 1) == 1362) {
            map->ouvrePorte(x/16, y/16, 0);
        }
        if (map->getSol(x, y + 8 - 1) == 1363) {
            map->ouvrePorte((x-16)/16, y/16, 0);
        }
    }
    link->startNewMap();

    fixCameraBounds();
}

void Scene::fixCameraBounds() {
    BoundingBox* bounds = map->getBounds();
    camera.setBounds(bounds->getX(), bounds->getY(), bounds->getW(), bounds->getH());

    int bx = link->getX() + link->getW() / 2 - 160;
    if (bx < 0) bx = 0;
    if (bx + 320 > bounds->getX() + bounds->getW()) bx = bounds->getX() + bounds->getW() - 320;
    int by = link->getY() + link->getH() / 2 - 116;
    if (by < 0) by = 0;
    if (by + 240 > bounds->getY() + bounds->getH()) by = bounds->getY() + bounds->getH() - 240;
    camera.setBox(bx, by,320,240);
}

void Scene::saveData() {

    save->setMap(map->getId());
    save->setAvancement(avancement);

    int tmp = 0;
    if (map->getId() == 26) { // reset position barque
        tmp = getCoffre(0, 5);
        setCoffre(0, 5, map->getOldBarque());
    }
    if (map->getId() == 68) { // reset position wagon
        tmp = getCoffre(0, 14);
        setCoffre(0, 14, map->getOldBarque());
    }

    for (int j = 0; j < COFFRES_MAX_SIZE; j++) {
        for (int i = 0; i < NB_COFFRES; i++) {
            save->setCoffre(i, j, coffres[i][j]);
        }
    }

    for (int j = 0; j < MAX_ROOMS_Y; j++) {
        for (int i = 0; i < MAX_ROOMS_X; i++) {
            for (int d = 0; d < NB_DONJON; d++) {
                save->setRooms(d, i, j, rooms[d][i][j]);
            }
        }
    }

    for (int i = 0; i < NB_MONSTERS; i++) {
        save->setMonsters(i, monsters[i]);
    }

    for (int i = 0; i < NB_POISSONS; i++) {
        save->setPoissons(i, poissons[i]);
    }

    link->saveData(save);

    if (map->getId() == 26) {
        setCoffre(0, 5, tmp);
    }
    if (map->getId() == 68) {
        setCoffre(0, 14, tmp);
    }
}

void Scene::handleActions(Action* action) {
    switch (step) {
        case SCENE_MAIN :

            if (animation.isRunning()) {
                break;
            }

            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(INVENTAIRE)) {
                MainController::getInstance()->getGameController()->setStep(GAME_MENU);
                return;
            }
            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(DISPLAY_MAP) && (map->getId() < 61 || map->getId() == 156)
                && (map->getId() != 57 || avancement >= AV_TELE_ZELDA)
                && (map->getId() != 58 || link->getInventory()->hasObject(TRIFORCE))) {
                if (map->getId() >= 46 || link->getInventory()->hasObject(CARTE)) {
                    MainController::getInstance()->getGameController()->displayMap(map->getId());
                    AudioManager::getInstance()->playSound(TS_MENU1);
                    return;
                }
            }
            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(AIDE)) {
                MainController::getInstance()->getGameController()->setStep(GAME_HELP);
                AudioManager::getInstance()->playSound(TS_MENU1);
                return;
            }
            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(MONSTERS) && link->getInventory()->hasObject(ENCYCLOPEDIE)) {
                MainController::getInstance()->getGameController()->setStep(GAME_MONSTERS);
                AudioManager::getInstance()->playSound(TS_MENU1);
                return;
            }
            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(POISSONS) && link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS)) {
                MainController::getInstance()->getGameController()->setStep(GAME_FISH);
                AudioManager::getInstance()->playSound(TS_MENU1);
                return;
            }
            if (link->getStatus()->getVirtualLife() > 0 && action->isAction(TROC) && link->getInventory()->hasObject(SAC_TROC)) {
                MainController::getInstance()->getGameController()->setStep(GAME_TROC);
                AudioManager::getInstance()->playSound(TS_MENU1);
                return;
            }

            boxOnLink = !action->isAction(CAMERA);
            if (!boxOnLink) {
                camera.handleAction(action, link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4);
                action->reset();
            }
            link->handleAction(action);

            break;
        default : break;
    }
}

void Scene::loop() {

    switch (step) {
        case SCENE_MAIN :
            animation.loop();
            metronome->loop();
            if (animation.loopMap()) {
                if (map->getId() == 36) {
                    filtreForest2++;
                    if (filtreForest2 > 512) filtreForest2 -= 512;
                }
                if (map->getId() == 70 && avancement < AV_PORTAIL_PRE_PRESENT_FERME && link->getInventory()->hasObject(OCARINA)) {
                    MainController::getInstance()->getGameController()->displayText(598);
                }
                // armee ganon
                /*if (map->getId() == 9 && avancement == AV_ARMEE_UP) {
                    hud->setBossLife(map->nbEnnemis(), 20);
                }*/
                // plane and ufo
                if (map->getId() == 15 || map->getId() == 30 || map->getId() == 45 || map->getId() == 46 || map->getId() == 53 || map->getId() == 156) {
                    if (!displayPlane && !displayUfo) {
                        int tmp = (int)((float)rand() / RAND_MAX * 36000);
                        if (tmp == 42) {
                            displayUfo = true;
                            planeX = -19;
                        } else if (tmp < 4) {
                            displayPlane = true;
                            planeX = -31;
                        }
                    } else {
                        planeX++;
                        if (planeX >= 320) {
                            displayUfo = false;
                            displayPlane = false;
                        }
                    }
                }
                // lightning
                if (map->getId() == 156) {
                    if (displayLightning1) {
                        lightning1Duration++;
                        if (lightning1Duration >= 12) {
                            displayLightning1 = false;
                        }
                    }
                    if (displayLightning2) {
                        lightning2Duration++;
                        if (lightning2Duration >= 12) {
                            displayLightning2 = false;
                        }
                    }
                    if (!displayLightning1 || !displayLightning2) {
                        int tmp = (int)((float)rand() / RAND_MAX * 90);
                        if (tmp == 7 && !displayLightning1) {
                            lightning1X = (int)((float)rand() / RAND_MAX * 288);
                            if (!displayLightning2 || lightning1X+32<lightning2X || lightning1X>lightning2X+32) {
                                displayLightning1 = true;
                                lightning1Duration = 0;
                            }
                        }
                        if (tmp == 12 && !displayLightning2) {
                            lightning2X = (int)((float)rand() / RAND_MAX * 288);
                            if (!displayLightning1 || lightning2X+32<lightning1X || lightning2X>lightning1X+32) {
                                displayLightning2 = true;
                                lightning2Duration = 0;
                            }
                        }
                    }
                }
                map->loop();
            }
            if (animation.loopLink()) link->loop();

            if (link->hasMoved()) {
                map->testAnim(link->getX(), link->getY(), link->getDirection());
            }

            if (animation.loopCamera()) {
                if (!camera.isManuel()) {
                    if (boxOnLink) {
                        camera.moveTo(link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4, 4);
                    }
                }
                camera.loop();
            }
            hud->loop();

            if (!animation.isRunning()) testTransition();
            break;
        case SCENE_TRANSITION_LIVE :
            transition.loop();
            if (transition.isWaiting()) {
                link->revit();
                fixCameraBounds();
                camera.loop();
                hud->loop();
                hud->reset();
                BoundingBox* box = camera.getBoundingBox();
                transition.restart(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
            } else if (transition.isAchieved()) {
                transition.reset();
                step = SCENE_MAIN;
            }
            break;
        case SCENE_ONLY_LINK :
            link->loop();

            camera.setPosition(link->getX() + link->getW() / 2, link->getY() + link->getH() / 2 + 4);
            camera.loop();
            hud->loop();
            break;
        default : break;
    }
}

void Scene::draw() {

    BoundingBox* box = camera.getBoundingBox();

    List toDraw;
    toDraw.add((Listable*)link);

    if (map->getId() == 15 || map->getId() == 30 || map->getId() == 46 || map->getId() == 53) {
        WindowManager::getInstance()->draw(filterSky[0], 0, 0, 320, 240, 0, 0);
    } else if (map->getId() == 45) {
        WindowManager::getInstance()->draw(filterSky[1], 0, 0, 320, 240, 0, 0);
    } else if (map->getId() == 156) {
        WindowManager::getInstance()->draw(filterSky[2], 0, 0, 320, 240, 0, 0);
        if (displayLightning1) {
            WindowManager::getInstance()->draw(lightning, 32 * (lightning1Duration / 4), 0, 32, 64, lightning1X, 0);
        }
        if (displayLightning2) {
            WindowManager::getInstance()->draw(lightning, 32 * (lightning2Duration / 4), 64, 32, 64, lightning2X, 0);
        }
    } else if (map->getId() == 56) {
        WindowManager::getInstance()->draw(godnesses, 0, 0, 320, 240, 0, 0);
    }
    if (map->getId() == 15 || map->getId() == 30 || map->getId() == 45 || map->getId() == 46 || map->getId() == 53 || map->getId() == 156) {
        if (displayPlane) {
            WindowManager::getInstance()->draw(planeAndUfo, 31 * (metronome->getValue() % 2), 11, 31, 13, planeX, 32);
        } else if (displayUfo) {
            WindowManager::getInstance()->draw(planeAndUfo, 19 * (metronome->getValue() % 4), 0, 19, 11, planeX, 32);
        }
    }

    map->draw(&toDraw, box);

    // forest effect
    if (map->getId() == 6) {
        WindowManager::getInstance()->draw(filterForest[2], (box->getX()/2) % 256, (box->getY()/2) % 256, 320, 240, 0, 0);
    } else if (map->getId() == 21) {
        WindowManager::getInstance()->draw(filterForest[0], (box->getX()/2) % 256, (box->getY()/2) % 256, 320, 240, 0, 0);
    } else if (map->getId() == 36) {
        int srcX = (box->getX() + (filtreForest2 / 2)) % 256;
        int srcY = (box->getY() + (filtreForest2 / 2)) % 256;
        WindowManager::getInstance()->draw(filterForest[1], srcX, srcY, 320, 240, 0, 0);
    } else if (map->getId() == 40) {
        WindowManager::getInstance()->draw(filterRain[metronome->getValue() % 3], 0, 0, 320, 240, 0, 0);
    }

    if (map->getId() < 16 && avancement < AV_INFO_PASSE_OK) {
        WindowManager::getInstance()->draw(filterSnow[metronome->getValue() % 3], 0, 0, 320, 240, 0, 0);
    } else if (map->getId() >= 16 && map->getId() < 31
               && avancement >= AV_PORTAIL_PRE_PRESENT_UTILISE && avancement < AV_PORTAIL_PRE_PRESENT_FERME) {
        WindowManager::getInstance()->draw(filterNight, 0, 0, 320, 240, 0, 0);
    }

    animation.draw();

    if (step == SCENE_TRANSITION_LIVE) {
        transition.draw();
    }

    hud->draw();

    animation.drawAfterHud();
}

bool Scene::checkCollisions(BoundingBox* box, Collisionable* object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox,
                            bool checkObjects, int safeX, int safeY, int safeW, int safeH, bool checkDanger) {
    return map->checkCollisions(box, object, checkEnnemis, ignoreNotIdle, withAvoid, onlyBox, checkObjects, safeX, safeY, safeW, safeH, checkDanger);
}
bool Scene::checkCollisionsWithLink(BoundingBox* box) {
    return !box->intersect(link->getBoundingBox());
}


Map* Scene::getMap() {
    return map;
}

Link* Scene::getLink() {
    return link;
}

Metronome* Scene::getMetronome() {
    return metronome;
}

Camera* Scene::getCamera() {
    return &camera;
}

Hud* Scene::getHud() {
    return hud;
}

AnimationInGame* Scene::getAnimationInGame() {
    return &animation;
}

Avancement Scene::getAvancement() {
    return avancement;
}

void Scene::setAvancement(Avancement av) {
    avancement = av;
}

bool Scene::testDegatOnLink(BoundingBox* box, Direction dir, int force, TypeAttack type, TypeEffect effect) {
    if (box->intersect(link->getBoundingBox())) {
        return link->underAttack(dir, force, type, effect);
    }
    return false;
}

bool Scene::testDegat(BoundingBox* box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis, bool onObjects) {
    return map->testDegat(box, dir, force, type, effect, onEnnemis, onObjects);
}

void Scene::testTransition() {
    if (map->testTransition(link->getX(), link->getY())) {
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_MAP);
    } else if (map->testTeleport(link->getX(), link->getY())) {
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
    } else if (map->testInnerTransition(link->getX(), link->getY())) {
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_ROOM);
    }
}

void Scene::setStep(SceneStep s) {
    step = s;
    if (step == SCENE_TRANSITION_LIVE) {
        BoundingBox* box = camera.getBoundingBox();
        transition.start(link->getX() + 8 - box->getX(), link->getY() + 16 - box->getY());
    }
}

void Scene::instantTeleport(int dstMap, int dstX, int dstY, Direction dstDir) {
    link->setX(dstX);
    link->setY(dstY);
    link->setDirection(dstDir);
    Map* mp = new Map(dstMap, metronome);
    mp->load();
    setMap(mp);
    mp->launch();
    link->startNewMap();
    fixCameraBounds();
}

void Scene::setMap(Map* mp) {
    delete map;
    map = mp;

    camera.setBounds(0, 0, map->getW(), map->getH());

    int bx = link->getX() + link->getW() / 2 - 160;
    if (bx < 0) bx = 0;
    if (bx + 320 > map->getW()) bx = map->getW() - 320;
    int by = link->getY() + link->getH() / 2 - 120;
    if (by < 0) by = 0;
    if (by + 240 > map->getH()) by = map->getH() - 240;
    camera.setBox(bx, by,320,240);
}

bool Scene::permuteBlocs(int step) {
    // 0 = orange up - blue down
    map->permuteBlocs(step);

    if (checkCollisions(link->getBoundingBox(), (Collisionable*)link, false, false, false, false, false)) {
        return true;
    } else {
        map->permuteBlocs(step == 0 ? 1 : 0);
        return false;
    }
}

int Scene::getCoffre(int i, int j) {
    return coffres[i][j];
}

void Scene::setCoffre(int i, int j, int val) {
    coffres[i][j] = val;
}

int Scene::getRooms(int d, int i, int j) {
    return rooms[d][i][j];
}

void Scene::setRooms(int d, int i, int j, int value) {
    rooms[d][i][j] = value;
}

int Scene::getMonsters(int i) {
    return monsters[i];
}

void Scene::setMonsters(int i, int val) {
    if (i < NB_MONSTERS) monsters[i] = val;
}

int Scene::getTotalMonsters() {
    int total = 0;
    for (int i = 0; i < NB_MONSTERS; i++) {
        total += monsters[i];
    }
    return total;
}

int Scene::getMonstersSolde() {
    int alreadyPaid = getCoffre(0, 24);
    return getTotalMonsters() * 40 - alreadyPaid;
}

void Scene::payForMonsters() {
    int maxPayable = 0;
    int solde = 0;
    int amount = 0;
    switch (map->getEpoque()) {
        case EP_PASSE :
            maxPayable = link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr();
            solde = getMonstersSolde() / 4;
            amount = (solde > maxPayable) ? maxPayable : solde;
            setCoffre(0, 24, getCoffre(0, 24) + amount * 4);
            link->getStatus()->updatePieceOr(amount);
            break;
        case EP_PRESENT :
            maxPayable = link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees();
            solde = getMonstersSolde();
            amount = (solde > maxPayable) ? maxPayable : solde;
            setCoffre(0, 24, getCoffre(0, 24) + amount);
            link->getStatus()->updateRupees(amount);
            break;
        case EP_FUTUR :
            maxPayable = link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr();
            solde = getMonstersSolde() / 2;
            amount = (solde > maxPayable) ? maxPayable : solde;
            setCoffre(0, 24, getCoffre(0, 24) + amount * 2);
            link->getStatus()->updateGanonOr(amount);
            break;
        default : break;
    }
}

int Scene::getPoissons(int i) {
    return poissons[i];
}

void Scene::setPoissons(int i, int val) {
    poissons[i] = val;
}

int Scene::getTotalPoissons() {
    int total = 0;
    for (int i = 0; i < NB_POISSONS; i++) {
        total += poissons[i];
    }
    return total;
}

int Scene::nbGemmeForce() {
    if (nbGemmeForce(map->getId()) > 0) {
        return 0;
    }

    int total = 0;

    switch (map->getId()) {
        case 1 :
            total = nbGemmeForce(2) + nbGemmeForce(12) + nbGemmeForce(13) + nbGemmeForce(75) + nbGemmeForce(128);
            break;
        case 2 :
            total = nbGemmeForce(1) + nbGemmeForce(3) + nbGemmeForce(12) + nbGemmeForce(14);
            break;
        case 3 :
            total = nbGemmeForce(2) + nbGemmeForce(4) + nbGemmeForce(5) + nbGemmeForce(9) + nbGemmeForce(11) + nbGemmeForce(14)
                    + nbGemmeForce(128) + nbGemmeForce(129) + nbGemmeForce(130) + nbGemmeForce(131) + nbGemmeForce(132)
                    + nbGemmeForce(133) + nbGemmeForce(134) + nbGemmeForce(135) + nbGemmeForce(136);
            break;
        case 4 :
            total = nbGemmeForce(3) + nbGemmeForce(5) + nbGemmeForce(8) + nbGemmeForce(14) + nbGemmeForce(56);
            break;
        case 5 :
            total = nbGemmeForce(3) + nbGemmeForce(4) + nbGemmeForce(6) + nbGemmeForce(7) + nbGemmeForce(9);
            break;
        case 6 :
            total = nbGemmeForce(5) + nbGemmeForce(7) + nbGemmeForce(9) + nbGemmeForce(77) + nbGemmeForce(78);
            break;
        case 7 :
            total = nbGemmeForce(5) + nbGemmeForce(6) + nbGemmeForce(8) + nbGemmeForce(53) + nbGemmeForce(74);
            break;
        case 8 :
            total = nbGemmeForce(4) + nbGemmeForce(7) + nbGemmeForce(15) + nbGemmeForce(124);
            break;
        case 9 :
            total = nbGemmeForce(3) + nbGemmeForce(5) + nbGemmeForce(6) + nbGemmeForce(10) + nbGemmeForce(11) + nbGemmeForce(154);
            break;
        case 10 :
            total = nbGemmeForce(9) + nbGemmeForce(11) + nbGemmeForce(137) + nbGemmeForce(138) + nbGemmeForce(139)
                    + nbGemmeForce(140) + nbGemmeForce(141) + nbGemmeForce(142) + nbGemmeForce(143);
            break;
        case 11 :
            total = nbGemmeForce(3) + nbGemmeForce(9) + nbGemmeForce(10) + nbGemmeForce(12) + nbGemmeForce(54)
                    + nbGemmeForce(127);
            break;
        case 12 :
            total = nbGemmeForce(1) + nbGemmeForce(2) + nbGemmeForce(11) + nbGemmeForce(52) + nbGemmeForce(76);
            break;
        case 13 :
            total = nbGemmeForce(1) + nbGemmeForce(14) + nbGemmeForce(15) + nbGemmeForce(144) + nbGemmeForce(145)
                    + nbGemmeForce(146) + nbGemmeForce(147) + nbGemmeForce(148) + nbGemmeForce(149);
            break;
        case 14 :
            total = nbGemmeForce(2) + nbGemmeForce(3) + nbGemmeForce(4) + nbGemmeForce(13) + nbGemmeForce(15)
                    + nbGemmeForce(125) + nbGemmeForce(153);
            break;
        case 15 :
            total = nbGemmeForce(8) + nbGemmeForce(13) + nbGemmeForce(14) + nbGemmeForce(55);
            break;
        case 16 :
            total = nbGemmeForce(17) + nbGemmeForce(27) + nbGemmeForce(28) + nbGemmeForce(61) + nbGemmeForce(79);
            break;
        case 17 :
            total = nbGemmeForce(16) + nbGemmeForce(18) + nbGemmeForce(27) + nbGemmeForce(29);
            break;
        case 18 :
            total = nbGemmeForce(17) + nbGemmeForce(19) + nbGemmeForce(20) + nbGemmeForce(24) + nbGemmeForce(26) + nbGemmeForce(29)
                    + nbGemmeForce(80) + nbGemmeForce(81) + nbGemmeForce(82) + nbGemmeForce(83) + nbGemmeForce(84)
                    + nbGemmeForce(85) + nbGemmeForce(86) + nbGemmeForce(87) + nbGemmeForce(88) + nbGemmeForce(89);
            break;
        case 19 :
            total = nbGemmeForce(18) + nbGemmeForce(20) + nbGemmeForce(23) + nbGemmeForce(29) + nbGemmeForce(57);
            break;
        case 20 :
            total = nbGemmeForce(18) + nbGemmeForce(19) + nbGemmeForce(21) + nbGemmeForce(22) + nbGemmeForce(24);
            break;
        case 21 :
            total = nbGemmeForce(20) + nbGemmeForce(22) + nbGemmeForce(24) + nbGemmeForce(62) + nbGemmeForce(63)
                    + nbGemmeForce(64) + nbGemmeForce(69) + nbGemmeForce(150);
            break;
        case 22 :
            total = nbGemmeForce(20) + nbGemmeForce(21) + nbGemmeForce(23) + nbGemmeForce(46) + nbGemmeForce(65)
                    + nbGemmeForce(90) + nbGemmeForce(91) + nbGemmeForce(92);
            break;
        case 23 :
            total = nbGemmeForce(19) + nbGemmeForce(22) + nbGemmeForce(30) + nbGemmeForce(66) + nbGemmeForce(111);
            break;
        case 24 :
            total = nbGemmeForce(18) + nbGemmeForce(20) + nbGemmeForce(21) + nbGemmeForce(25) + nbGemmeForce(26);
            break;
        case 25 :
            total = nbGemmeForce(24) + nbGemmeForce(26) + nbGemmeForce(93) + nbGemmeForce(94) + nbGemmeForce(95)
                    + nbGemmeForce(96) + nbGemmeForce(97) + nbGemmeForce(98) + nbGemmeForce(99) + nbGemmeForce(100);
            break;
        case 26 :
            total = nbGemmeForce(18) + nbGemmeForce(24) + nbGemmeForce(25) + nbGemmeForce(27) + nbGemmeForce(47)
                    + nbGemmeForce(101);
            break;
        case 27 :
            total = nbGemmeForce(16) + nbGemmeForce(17) + nbGemmeForce(26) + nbGemmeForce(51) + nbGemmeForce(67);
            break;
        case 28 :
            total = nbGemmeForce(16) + nbGemmeForce(29) + nbGemmeForce(30) + nbGemmeForce(102) + nbGemmeForce(103)
                    + nbGemmeForce(104) + nbGemmeForce(105) + nbGemmeForce(106) + nbGemmeForce(107) + nbGemmeForce(108);
            break;
        case 29 :
            total = nbGemmeForce(17) + nbGemmeForce(18) + nbGemmeForce(19) + nbGemmeForce(28) + nbGemmeForce(30)
                    + nbGemmeForce(109) + nbGemmeForce(110) + nbGemmeForce(151);
            break;
        case 30 :
            total = nbGemmeForce(23) + nbGemmeForce(28) + nbGemmeForce(29) + nbGemmeForce(48) + nbGemmeForce(68);
            break;
        case 31 :
            total = nbGemmeForce(32) + nbGemmeForce(42) + nbGemmeForce(43) + nbGemmeForce(71) + nbGemmeForce(116);
            break;
        case 32 :
            total = nbGemmeForce(31) + nbGemmeForce(33) + nbGemmeForce(42) + nbGemmeForce(44);
            break;
        case 33 :
            total = nbGemmeForce(32) + nbGemmeForce(34) + nbGemmeForce(35) + nbGemmeForce(39) + nbGemmeForce(41) + nbGemmeForce(44)
                    + nbGemmeForce(117) + nbGemmeForce(118) + nbGemmeForce(119) + nbGemmeForce(120) + nbGemmeForce(121)
                    + nbGemmeForce(122) + nbGemmeForce(123);
            break;
        case 34 :
            total = nbGemmeForce(33) + nbGemmeForce(35) + nbGemmeForce(38) + nbGemmeForce(44) + nbGemmeForce(155);
            break;
        case 35 :
            total = nbGemmeForce(33) + nbGemmeForce(34) + nbGemmeForce(36) + nbGemmeForce(37) + nbGemmeForce(39);
            break;
        case 36 :
            total = nbGemmeForce(35) + nbGemmeForce(37) + nbGemmeForce(39) + nbGemmeForce(70);
            break;
        case 37 :
            total = nbGemmeForce(35) + nbGemmeForce(36) + nbGemmeForce(38) + nbGemmeForce(73) + nbGemmeForce(115);
            break;
        case 38 :
            total = nbGemmeForce(34) + nbGemmeForce(37) + nbGemmeForce(45) + nbGemmeForce(72) + nbGemmeForce(114);
            break;
        case 39 :
            total = nbGemmeForce(33) + nbGemmeForce(35) + nbGemmeForce(36) + nbGemmeForce(40) + nbGemmeForce(41);
            break;
        case 40 :
            total = nbGemmeForce(39) + nbGemmeForce(41);
            break;
        case 41 :
            total = nbGemmeForce(33) + nbGemmeForce(39) + nbGemmeForce(40) + nbGemmeForce(42) + nbGemmeForce(49);
            break;
        case 42 :
            total = nbGemmeForce(31) + nbGemmeForce(32) + nbGemmeForce(41) + nbGemmeForce(50);
            break;
        case 43 :
            total = nbGemmeForce(31) + nbGemmeForce(44) + nbGemmeForce(45);
            break;
        case 44 :
            total = nbGemmeForce(32) + nbGemmeForce(33) + nbGemmeForce(34) + nbGemmeForce(43) + nbGemmeForce(45)
                    + nbGemmeForce(58) + nbGemmeForce(112) + nbGemmeForce(113) + nbGemmeForce(152);
            break;
        case 45 :
            total = nbGemmeForce(38) + nbGemmeForce(43) + nbGemmeForce(44) + nbGemmeForce(59);
            break;
        case 46 : case 65 : case 90 : case 91 : case 92 : total = nbGemmeForce(22); break;
        case 47 : case 101 : total = nbGemmeForce(26); break;
        case 48 : case 68 : total = nbGemmeForce(30); break;
        case 49 : total = nbGemmeForce(41); break;
        case 50 : total = nbGemmeForce(42); break;
        case 51 : case 67 : total = nbGemmeForce(27); break;
        case 52 : case 76 : total = nbGemmeForce(12); break;
        case 53 : case 74 : total = nbGemmeForce(7); break;
        case 54 : case 127 : total = nbGemmeForce(11); break;
        case 55 : total = nbGemmeForce(15); break;
        case 56 : total = nbGemmeForce(4); break;
        case 57 : total = nbGemmeForce(19); break;
        case 58 : case 112 : case 113 : case 152 : total = nbGemmeForce(44); break;
        case 61 : case 79 : total = nbGemmeForce(16); break;
        case 62 : case 63 : case 64 : case 69 : case 150 : total = nbGemmeForce(21); break;
        case 66 : case 111 : total = nbGemmeForce(23); break;
        case 70 : total = nbGemmeForce(36); break;
        case 71 : case 116 : total = nbGemmeForce(31); break;
        case 72 : case 114 : total = nbGemmeForce(38); break;
        case 73 : case 115 : total = nbGemmeForce(37); break;
        case 75 : case 126 : total = nbGemmeForce(1); break;
        case 77 : case 78 : total = nbGemmeForce(6); break;
        case 80 : case 81 : case 82 : case 83 : case 84 : case 85 : case 86 : case 87 : case 88 : case 89 : total = nbGemmeForce(18); break;
        case 93 : case 94 : case 95 : case 96 : case 97 : case 98 : case 99 : case 100 : total = nbGemmeForce(25); break;
        case 102 : case 103 : case 104 : case 105 : case 106 : case 107 : case 108 : total = nbGemmeForce(28); break;
        case 109 : case 110 : case 151 : total = nbGemmeForce(29); break;
        case 117 : case 118 : case 119 : case 120 : case 121 : case 122 : case 123 : total = nbGemmeForce(33); break;
        case 124 : total = nbGemmeForce(8); break;
        case 125 : case 153 : total = nbGemmeForce(14); break;
        case 128 : case 129 : case 130 : case 131 : case 132 : case 133 : case 134 : case 135 : case 136 : total = nbGemmeForce(3); break;
        case 137: case 138 : case 139 : case 140 : case 141 : case 142 : case 143 : total = nbGemmeForce(10); break;
        case 144: case 145 : case 146 : case 147 : case 148 : case 149 : total = nbGemmeForce(13); break;
        case 154 : total = nbGemmeForce(9); break;
        case 155 : total = nbGemmeForce(34); break;
    }

    return total > 0 ? 2 : 1;
}

int Scene::nbGemmeForce(int mapId) {
    Inventory* inventory = link->getInventory();
    int total = 0;
    int current = 0;

    switch (mapId) {
        case 1 :
            total = 3;
            if (inventory->hasGemmeForce(6)) current++;
            if (inventory->hasGemmeForce(7)) current++;
            if (inventory->hasGemmeForce(8)) current++;
            break;
        case 2 :
            total = 3;
            if (inventory->hasGemmeForce(15)) current++;
            if (inventory->hasGemmeForce(16)) current++;
            if (inventory->hasGemmeForce(17)) current++;
            break;
        case 3 :
            total = 3;
            if (inventory->hasGemmeForce(21)) current++;
            if (inventory->hasGemmeForce(22)) current++;
            if (inventory->hasGemmeForce(23)) current++;
            break;
        case 4 :
            total = 2;
            if (inventory->hasGemmeForce(32)) current++;
            if (inventory->hasGemmeForce(33)) current++;
            break;
        case 5 :
            total = 2;
            if (inventory->hasGemmeForce(40)) current++;
            if (inventory->hasGemmeForce(41)) current++;
            break;
        case 6 :
            total = 2;
            if (inventory->hasGemmeForce(53)) current++;
            if (inventory->hasGemmeForce(54)) current++;
            break;
        case 7 :
            total = 3;
            if (inventory->hasGemmeForce(62)) current++;
            if (inventory->hasGemmeForce(63)) current++;
            if (inventory->hasGemmeForce(64)) current++;
            break;
        case 8 :
            total = 3;
            if (inventory->hasGemmeForce(71)) current++;
            if (inventory->hasGemmeForce(72)) current++;
            if (inventory->hasGemmeForce(73)) current++;
            break;
        case 9 :
            total = 3;
            if (inventory->hasGemmeForce(82)) current++;
            if (inventory->hasGemmeForce(83)) current++;
            if (inventory->hasGemmeForce(84)) current++;
            break;
        case 10 :
            total = 5;
            if (inventory->hasGemmeForce(89)) current++;
            if (inventory->hasGemmeForce(90)) current++;
            if (inventory->hasGemmeForce(91)) current++;
            if (inventory->hasGemmeForce(92)) current++;
            if (inventory->hasGemmeForce(93)) current++;
            break;
        case 11 :
            total = 3;
            if (inventory->hasGemmeForce(102)) current++;
            if (inventory->hasGemmeForce(103)) current++;
            if (inventory->hasGemmeForce(104)) current++;
            break;
        case 12 :
            total = 3;
            if (inventory->hasGemmeForce(111)) current++;
            if (inventory->hasGemmeForce(112)) current++;
            if (inventory->hasGemmeForce(113)) current++;
            break;
        case 13 :
            total = 3;
            if (inventory->hasGemmeForce(119)) current++;
            if (inventory->hasGemmeForce(120)) current++;
            if (inventory->hasGemmeForce(121)) current++;
            break;
        case 14 :
            total = 3;
            if (inventory->hasGemmeForce(128)) current++;
            if (inventory->hasGemmeForce(129)) current++;
            if (inventory->hasGemmeForce(130)) current++;
            break;
        case 15 :
            total = 5;
            if (inventory->hasGemmeForce(141)) current++;
            if (inventory->hasGemmeForce(142)) current++;
            if (inventory->hasGemmeForce(143)) current++;
            if (inventory->hasGemmeForce(144)) current++;
            if (inventory->hasGemmeForce(145)) current++;
            break;
        case 16 :
            total = 4;
            if (inventory->hasGemmeForce(0)) current++;
            if (inventory->hasGemmeForce(1)) current++;
            if (inventory->hasGemmeForce(2)) current++;
            if (inventory->hasGemmeForce(3)) current++;
            break;
        case 17 :
            total = 3;
            if (inventory->hasGemmeForce(9)) current++;
            if (inventory->hasGemmeForce(10)) current++;
            if (inventory->hasGemmeForce(11)) current++;
            break;
        case 18 :
            total = 2;
            if (inventory->hasGemmeForce(18)) current++;
            if (inventory->hasGemmeForce(24)) current++;
            break;
        case 19 :
            total = 3;
            if (inventory->hasGemmeForce(26)) current++;
            if (inventory->hasGemmeForce(27)) current++;
            if (inventory->hasGemmeForce(28)) current++;
            break;
        case 20 :
            total = 3;
            if (inventory->hasGemmeForce(34)) current++;
            if (inventory->hasGemmeForce(35)) current++;
            if (inventory->hasGemmeForce(36)) current++;
            break;
        case 21 :
            total = 5;
            if (inventory->hasGemmeForce(42)) current++;
            if (inventory->hasGemmeForce(43)) current++;
            if (inventory->hasGemmeForce(44)) current++;
            if (inventory->hasGemmeForce(45)) current++;
            if (inventory->hasGemmeForce(46)) current++;
            break;
        case 22 :
            total = 3;
            if (inventory->hasGemmeForce(55)) current++;
            if (inventory->hasGemmeForce(56)) current++;
            if (inventory->hasGemmeForce(57)) current++;
            break;
        case 23 :
            total = 3;
            if (inventory->hasGemmeForce(65)) current++;
            if (inventory->hasGemmeForce(66)) current++;
            if (inventory->hasGemmeForce(67)) current++;
            break;
        case 24 :
            total = 4;
            if (inventory->hasGemmeForce(74)) current++;
            if (inventory->hasGemmeForce(75)) current++;
            if (inventory->hasGemmeForce(76)) current++;
            if (inventory->hasGemmeForce(77)) current++;
            break;
        case 25 :
            total = 2;
            if (inventory->hasGemmeForce(85)) current++;
            if (inventory->hasGemmeForce(86)) current++;
            break;
        case 26 :
            total = 3;
            if (inventory->hasGemmeForce(94)) current++;
            if (inventory->hasGemmeForce(95)) current++;
            if (inventory->hasGemmeForce(96)) current++;
            break;
        case 27 :
            total = 3;
            if (inventory->hasGemmeForce(105)) current++;
            if (inventory->hasGemmeForce(106)) current++;
            if (inventory->hasGemmeForce(107)) current++;
            break;
        case 28 :
            total = 3;
            if (inventory->hasGemmeForce(114)) current++;
            if (inventory->hasGemmeForce(115)) current++;
            if (inventory->hasGemmeForce(116)) current++;
            break;
        case 29 :
            total = 3;
            if (inventory->hasGemmeForce(122)) current++;
            if (inventory->hasGemmeForce(123)) current++;
            if (inventory->hasGemmeForce(124)) current++;
            break;
        case 30 :
            total = 5;
            if (inventory->hasGemmeForce(131)) current++;
            if (inventory->hasGemmeForce(132)) current++;
            if (inventory->hasGemmeForce(133)) current++;
            if (inventory->hasGemmeForce(134)) current++;
            if (inventory->hasGemmeForce(135)) current++;
            break;
        case 31 :
            total = 2;
            if (inventory->hasGemmeForce(4)) current++;
            if (inventory->hasGemmeForce(5)) current++;
            break;
        case 32 :
            total = 3;
            if (inventory->hasGemmeForce(12)) current++;
            if (inventory->hasGemmeForce(13)) current++;
            if (inventory->hasGemmeForce(14)) current++;
            break;
        case 33 :
            total = 3;
            if (inventory->hasGemmeForce(19)) current++;
            if (inventory->hasGemmeForce(20)) current++;
            if (inventory->hasGemmeForce(25)) current++;
            break;
        case 34 :
            total = 3;
            if (inventory->hasGemmeForce(29)) current++;
            if (inventory->hasGemmeForce(30)) current++;
            if (inventory->hasGemmeForce(31)) current++;
            break;
        case 35 :
            total = 3;
            if (inventory->hasGemmeForce(37)) current++;
            if (inventory->hasGemmeForce(38)) current++;
            if (inventory->hasGemmeForce(39)) current++;
            break;
        case 36 :
            total = 6;
            if (inventory->hasGemmeForce(47)) current++;
            if (inventory->hasGemmeForce(48)) current++;
            if (inventory->hasGemmeForce(49)) current++;
            if (inventory->hasGemmeForce(50)) current++;
            if (inventory->hasGemmeForce(51)) current++;
            if (inventory->hasGemmeForce(52)) current++;
            break;
        case 37 :
            total = 4;
            if (inventory->hasGemmeForce(58)) current++;
            if (inventory->hasGemmeForce(59)) current++;
            if (inventory->hasGemmeForce(60)) current++;
            if (inventory->hasGemmeForce(61)) current++;
            break;
        case 38 :
            total = 3;
            if (inventory->hasGemmeForce(68)) current++;
            if (inventory->hasGemmeForce(69)) current++;
            if (inventory->hasGemmeForce(70)) current++;
            break;
        case 39 :
            total = 4;
            if (inventory->hasGemmeForce(78)) current++;
            if (inventory->hasGemmeForce(79)) current++;
            if (inventory->hasGemmeForce(80)) current++;
            if (inventory->hasGemmeForce(81)) current++;
            break;
        case 40 :
            total = 2;
            if (inventory->hasGemmeForce(87)) current++;
            if (inventory->hasGemmeForce(88)) current++;
            break;
        case 41 :
            total = 5;
            if (inventory->hasGemmeForce(97)) current++;
            if (inventory->hasGemmeForce(98)) current++;
            if (inventory->hasGemmeForce(99)) current++;
            if (inventory->hasGemmeForce(100)) current++;
            if (inventory->hasGemmeForce(101)) current++;
            break;
        case 42 :
            total = 3;
            if (inventory->hasGemmeForce(108)) current++;
            if (inventory->hasGemmeForce(109)) current++;
            if (inventory->hasGemmeForce(110)) current++;
            break;
        case 43 :
            total = 2;
            if (inventory->hasGemmeForce(117)) current++;
            if (inventory->hasGemmeForce(118)) current++;
            break;
        case 44 :
            total = 3;
            if (inventory->hasGemmeForce(125)) current++;
            if (inventory->hasGemmeForce(126)) current++;
            if (inventory->hasGemmeForce(127)) current++;
            break;
        case 45 :
            total = 5;
            if (inventory->hasGemmeForce(136)) current++;
            if (inventory->hasGemmeForce(137)) current++;
            if (inventory->hasGemmeForce(138)) current++;
            if (inventory->hasGemmeForce(139)) current++;
            if (inventory->hasGemmeForce(140)) current++;
            break;
        case 46 :
            total = 1;
            if (inventory->hasGemmeForce(185)) current++;
            break;
        case 47 :
            total = 1;
            if (inventory->hasGemmeForce(186)) current++;
            break;
        case 48 :
            total = 1;
            if (inventory->hasGemmeForce(187)) current++;
            break;
        case 49 :
            total = 1;
            if (inventory->hasGemmeForce(188)) current++;
            break;
        case 50 :
            total = 1;
            if (inventory->hasGemmeForce(189)) current++;
            break;
        case 51 :
            total = 1;
            if (inventory->hasGemmeForce(190)) current++;
            break;
        case 52 :
            total = 1;
            if (inventory->hasGemmeForce(191)) current++;
            break;
        case 53 :
            total = 1;
            if (inventory->hasGemmeForce(192)) current++;
            break;
        case 54 :
            total = 1;
            if (inventory->hasGemmeForce(193)) current++;
            break;
        case 55 :
            total = 1;
            if (inventory->hasGemmeForce(194)) current++;
            break;
        case 56 :
            total = 1;
            if (inventory->hasGemmeForce(195)) current++;
            break;
        case 57 :
            total = 2;
            if (inventory->hasGemmeForce(197)) current++;
            if (inventory->hasGemmeForce(198)) current++;
            break;
        case 58 :
            total = 1;
            if (inventory->hasGemmeForce(199)) current++;
            break;
        case 63 :
            total = 1;
            if (inventory->hasGemmeForce(146)) current++;
            break;
        case 66 :
            total = 1;
            if (inventory->hasGemmeForce(148)) current++;
            break;
        case 67 :
            total = 1;
            if (inventory->hasGemmeForce(149)) current++;
            break;
        case 68 :
            total = 3;
            if (inventory->hasGemmeForce(150)) current++;
            if (inventory->hasGemmeForce(151)) current++;
            if (inventory->hasGemmeForce(152)) current++;
            break;
        case 76 :
            total = 1;
            if (inventory->hasGemmeForce(153)) current++;
            break;
        case 77 :
            total = 1;
            if (inventory->hasGemmeForce(154)) current++;
            break;
        case 78 :
            total = 2;
            if (inventory->hasGemmeForce(155)) current++;
            if (inventory->hasGemmeForce(156)) current++;
            break;
        case 80 :
            total = 1;
            if (inventory->hasGemmeForce(157)) current++;
            break;
        case 85 :
            total = 1;
            if (inventory->hasGemmeForce(158)) current++;
            break;
        case 88 :
            total = 1;
            if (inventory->hasGemmeForce(159)) current++;
            break;
        case 89 :
            total = 3;
            if (inventory->hasGemmeForce(160)) current++;
            if (inventory->hasGemmeForce(161)) current++;
            if (inventory->hasGemmeForce(162)) current++;
            break;
        case 90 :
            total = 1;
            if (inventory->hasGemmeForce(163)) current++;
            break;
        case 91 :
            total = 1;
            if (inventory->hasGemmeForce(164)) current++;
            break;
        case 92 :
            total = 1;
            if (inventory->hasGemmeForce(165)) current++;
            break;
        case 95 :
            total = 1;
            if (inventory->hasGemmeForce(166)) current++;
            break;
        case 101 :
            total = 1;
            if (inventory->hasGemmeForce(167)) current++;
            break;
        case 102 :
            total = 1;
            if (inventory->hasGemmeForce(168)) current++;
            break;
        case 103 :
            total = 1;
            if (inventory->hasGemmeForce(169)) current++;
            break;
        case 113 :
            total = 1;
            if (inventory->hasGemmeForce(170)) current++;
            break;
        case 116 :
            total = 1;
            if (inventory->hasGemmeForce(172)) current++;
            break;
        case 119 :
            total = 1;
            if (inventory->hasGemmeForce(173)) current++;
            break;
        case 120 :
            total = 1;
            if (inventory->hasGemmeForce(174)) current++;
            break;
        case 127 :
            total = 1;
            if (inventory->hasGemmeForce(175)) current++;
            break;
        case 130 :
            total = 1;
            if (inventory->hasGemmeForce(176)) current++;
            break;
        case 135 :
            total = 1;
            if (inventory->hasGemmeForce(177)) current++;
            break;
        case 137 :
            total = 1;
            if (inventory->hasGemmeForce(178)) current++;
            break;
        case 139 :
            total = 1;
            if (inventory->hasGemmeForce(179)) current++;
            break;
        case 140 :
            total = 1;
            if (inventory->hasGemmeForce(180)) current++;
            break;
        case 141 :
            total = 1;
            if (inventory->hasGemmeForce(181)) current++;
            break;
        case 145 :
            total = 1;
            if (inventory->hasGemmeForce(182)) current++;
            break;
        case 147 :
            total = 1;
            if (inventory->hasGemmeForce(183)) current++;
            break;
        case 154 :
            total = 1;
            if (inventory->hasGemmeForce(184)) current++;
            break;
        case 155 :
            total = 3;
            if (inventory->hasGemmeForce(147)) current++;
            if (inventory->hasGemmeForce(171)) current++;
            if (inventory->hasGemmeForce(196)) current++;
            break;
    }

    return total - current;
}

int Scene::getFiltreForest2() {
    return filtreForest2;
}
