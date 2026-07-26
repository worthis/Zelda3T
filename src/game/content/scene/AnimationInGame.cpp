#include "AnimationInGame.h"

#include "../../../game/MainController.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"

// #include "../objects/Pnj.h"

AnimationInGame::AnimationInGame() : id(0), anim(0), running(false)
{
    image = ResourceManager::getInstance()->loadImage("data/images/intro/nuit.png");
    zelda = 0;
    ganondorf = 0;
}

AnimationInGame::~AnimationInGame()
{
    ResourceManager::getInstance()->free(image);
}

void AnimationInGame::testAnim()
{

    if (running)
    {
        return;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Avancement avancement = scene->getAvancement();

    link = scene->getLink();
    map = scene->getMap();

    switch (avancement)
    {
    case AV_START:
        startAnim(1);
        break;
    case AV_INTRO_OK:
        if (map->getId() == 16)
        {
            startAnim(3);
        }
        break;
    case AV_STELE_LUE:
        if (link->getY() == 10 * 16 + 8)
            startAnim(2);
        break;
    case AV_SAGES_GROTTE:
        if (map->getId() == 70)
        {
            startAnim(4);
        }
        break;
    case AV_INFO_PASSE_OK:
        if (map->getId() == 3)
        {
            startAnim(6);
        }
        break;
    case AV_GANON_SORTI:
        if (map->getId() == 9 && link->getX() > 120 * 16)
        {
            startAnim(7);
        }
        break;
    case AV_MOT_DE_PASSE_DONNE:
        if (map->getId() == 155 && map->getBounds()->getX() == 320 * 3 && map->getBounds()->getY() == 240)
        {
            startAnim(10);
        }
        break;
    /*case AV_TUTO_OK :
        if (map->getId() == 1) {
            startAnim(2);
        }
        break;
    case AV_ONI_LINK_FREE :
        if (map->getId() < 15) {
            MainController::getInstance()->getGameController()->displayText(346);
        }
        break;
    case AV_GANON_VU :
        if (map->getId() < 15) {
            MainController::getInstance()->getGameController()->displayText(359);
        }
        break;*/
    default:
        break;
    }

    if (map->getId() == 21 && !scene->getCoffre(0, 2) && link->getInventory()->getTrocGemme(2) == TGJ_SCIE)
    {
        startAnim(8);
    }
}

void AnimationInGame::startAnim(int i)
{
    id = i;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    link = scene->getLink();
    map = scene->getMap();
    camera = scene->getCamera();

    lmap = false;
    lcamera = false;
    llink = false;

    switch (id)
    {
    case 1:
        AudioManager::getInstance()->stopMusic();
        MainController::getInstance()->getGameController()->displayText(95);
        break;
    case 2:
        lmap = true;
        zelda = new Pnj(9 * 16 + 8, 13 * 16 + 8, 15, 569, N);
        map->addObject(zelda);
        break;
    case 3:
        MainController::getInstance()->getGameController()->displayText(237);
        break;
    case 4:
        MainController::getInstance()->getGameController()->displayText(589);
        break;
    case 5:
        map->setAir(13 * 16, 5 * 16, 3331);
        break;
    case 6:
        MainController::getInstance()->getGameController()->displayText(408);
        break;
    case 7:
        link->setDirection(E);
        MainController::getInstance()->getGameController()->displayText(447);
        break;
    case 8:
        scene->setCoffre(0, 2, 1);
        MainController::getInstance()->getGameController()->getTransitionTimesController()->setSens(3);
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_TIME);
        break;
    case 9:
        scene->setAvancement(AV_GANON_SORTI);
        map->ouvrePorte(58, 19, 1);
        AudioManager::getInstance()->stopMusic();
        AudioManager::getInstance()->playSound(TS_BOOM, 2);
        break;
    case 10:
        AudioManager::getInstance()->playMusic(28);
        MainController::getInstance()->getGameController()->displayText(1196);
        break;
    case 11:
        lcamera = true;
        camera->setManuel(true);
        camera->moveTo(320 * 3 + 160, 240 * 2 + 120);
        AudioManager::getInstance()->stopMusic();
        break;
    case 12:
        lmap = true;
        AudioManager::getInstance()->stopMusic();
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        break;
    case 13:
        lmap = true;
        link->setDirection(W);
        link->setAnimation(IDLE);
        map->removeZelda();
        zelda = new Pnj(100 * 16, 171 * 16 + 9, 15, 1321, E);
        map->addObject(zelda);
        break;
    case 14:
        lmap = true;
        ganondorf = new Ennemi089(169 * 16 + 6, 19 * 16 + 6, 1, true);
        map->addEnnemi(ganondorf);
        MainController::getInstance()->getGameController()->displayText(1369);
        break;
    case 15:
    case 16:
    case 17:
        lmap = true;
        break;
    default:
        break;
    }

    running = true;
    anim = 0;
}

void AnimationInGame::loop()
{
    if (!running)
    {
        return;
    }
    switch (id)
    {
    case 1:
        MainController::getInstance()->getGameController()->displayText(96);
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_INTRO_OK);
        AudioManager::getInstance()->playMusic(70);
        running = false;
        break;
    case 2:
        if (anim == 0)
        {
            if (zelda->getY() > 16 * 11 + 1 + 8)
            {
                zelda->setDirection(N);
                zelda->moveY(-1);
            }
            else
            {
                anim = 1;
                MainController::getInstance()->getGameController()->displayText(562);
            }
        }
        else if (anim == 1)
        {
            if (zelda->getY() > 16 * 7 + 1 + 8)
            {
                if (link->getX() >= 16 * 8 + 8 && link->getX() <= 16 * 10 + 8 && zelda->getX() > 16 * 7)
                {
                    zelda->setDirection(W);
                    zelda->moveX(-1);
                }
                else
                {
                    zelda->setDirection(N);
                    zelda->moveY(-1);
                }
            }
            else if (zelda->getX() < 16 * 9 + 8)
            {
                zelda->setDirection(E);
                zelda->moveX(1);
            }
            else
            {
                anim = 2;
                zelda->setDirection(N);
                MainController::getInstance()->getGameController()->displayText(563);
                break;
            }
        }
        else if (anim == 2)
        {
            zelda->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(565);
            anim = 3;
        }
        else if (anim == 3)
        {
            zelda->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(576);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_PARLE_ZELDA_GROTTE);
            zelda = 0;
            running = false;
        }
        break;
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 10:
        running = false;
        break;
    case 5:
        anim++;
        if (anim == 80)
        {
            map->setAir(13 * 16, 5 * 16, 3329);
        }
        if (anim >= 100)
        {
            map->setAir(13 * 16, 5 * 16, 3332);
            map->pnjBoitCafe(true);
            running = false;
        }
        break;
    case 9:
        anim++;
        if (anim == 80)
        {
            AudioManager::getInstance()->playMusic(48);
            MainController::getInstance()->getGameController()->displayText(1182);
            running = false;
        }
        break;
    case 11:
        if (camera->getBoundingBox()->getX() == 320 * 3 && camera->getBoundingBox()->getY() == 240 * 2)
        {
            map->getBounds()->setX(320 * 3);
            map->getBounds()->setY(240 * 2);
            map->getBounds()->setW(320);
            map->getBounds()->setH(240);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->fixCameraBounds();
            camera->setManuel(false);
            map->testAnimRoom();
            link->setY(41 * 16 + 8);
            link->startNewRoom(false);
            running = false;
        }
        break;
    case 12:
        anim++;
        if (anim == 120)
        {
            running = false;
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(56, 169 * 16 + 8, 67 * 16 + 8, N, false, false, false);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
        }
        break;
    case 13:
        if (anim == 0)
        {
            if (zelda->getX() < 16 * 102 + 8)
            {
                zelda->setDirection(E);
                zelda->moveX(1);
            }
            else
            {
                anim = 1;
            }
        }
        else if (anim == 1)
        {
            MainController::getInstance()->getGameController()->displayText(1320);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setAvancement(AV_ZELDA_SOUS_SOL);
            zelda = 0;
            running = false;
        }
        break;
    case 14:
        if (anim == 0)
        {
            anim = 1;
            ganondorf->reset();
            MainController::getInstance()->getGameController()->displayText(1370);
        }
        else if (anim == 1)
        {
            anim = 2;
            ganondorf->setDirection(N);
        }
        else if (ganondorf->getY() == 15 * 16)
        {
            ganondorf->killNode();
            running = false;
        }
        break;
    case 15:
        anim++;
        if (anim == 80)
        {
            map->activateDices(3 * 16, 78 * 16, false);
        }
        else if (anim == 160)
        {
            map->activateDices(5 * 16, 78 * 16, false);
        }
        else if (anim == 240)
        {
            map->activateDices(7 * 16, 78 * 16, true);
            running = false;
        }
        break;
    case 16:
        anim++;
        if (anim == 80)
        {
            map->activateDices(103 * 16, 63 * 16, false);
        }
        else if (anim == 160)
        {
            map->activateDices(116 * 16, 63 * 16, false);
        }
        else if (anim == 240)
        {
            map->activateDices(103 * 16, 71 * 16, false);
        }
        else if (anim == 320)
        {
            map->activateDices(116 * 16, 71 * 16, false);
            if (map->isJeuCasinoGagne())
            {
                MainController::getInstance()->getGameController()->displayText(1439);
            }
            else
            {
                map->jeuCasinoPerdu();
                MainController::getInstance()->getGameController()->displayText(1440);
            }
            running = false;
        }
        break;
    case 17:
        anim++;
        if (anim == 80)
        {
            map->activateDices(83 * 16, 18 * 16, true);
            running = false;
        }
        break;
    }
}

void AnimationInGame::draw()
{
    if (!running)
    {
        return;
    }

    switch (id)
    {
    /*case 3 :
        oniLink->drawForMenu(link->getX() - anim * 2 - map->getBounds()->getX(), link->getY() - map->getBounds()->getY());
        break;
    case 4 :
        oniLink->drawForMenu(link->getX() - 96 - map->getBounds()->getX(), link->getY() - map->getBounds()->getY());
        break;*/
    default:
        break;
    }
}

void AnimationInGame::drawAfterHud()
{
    if (!running)
    {
        return;
    }

    switch (id)
    {
    case 1:
        WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);
        break;
    default:
        break;
    }
}

int AnimationInGame::getSpecialMusicId()
{
    if (!running)
    {
        return 0;
    }

    switch (id)
    {
    // case 1 : return 2;
    default:
        return 0;
    }
}

bool AnimationInGame::isRunning()
{
    return running;
}

bool AnimationInGame::loopMap()
{
    return !running || lmap;
}

bool AnimationInGame::loopCamera()
{
    return !running || lcamera;
}

bool AnimationInGame::loopLink()
{
    return !running || llink;
}

void AnimationInGame::stop()
{
    running = false;
}
