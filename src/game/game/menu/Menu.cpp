#include "Menu.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

Menu::Menu() : i(0), j(0), step(MENU_OFF), anim(0), link(0)
{
    imageMenu = ResourceManager::getInstance()->loadImage("data/images/status/bord.png", true);
    imageCoeur = ResourceManager::getInstance()->loadImage("data/images/status/coeur.png", true);
    imageChiffres = ResourceManager::getInstance()->loadImage("data/images/status/chiffres.png", true);
    imageStuff = ResourceManager::getInstance()->loadImage("data/images/status/stuff.png");
    imageStatus = ResourceManager::getInstance()->loadImage("data/images/status/status.png", true);
    metronome = new Metronome(2, ANIM_REFRESH * 3);
    metronome->reset();
    for (int i = 0; i < 49; i++)
    {
        texts[i] = 0;
    }
    magie = false;
    oniLink = false;
    nbGemme = 0;
    nbTotalGemme = 0;
    allGemme = 0;
}

Menu::~Menu()
{
    ResourceManager::getInstance()->free(imageMenu);
    ResourceManager::getInstance()->free(imageCoeur);
    ResourceManager::getInstance()->free(imageChiffres);
    ResourceManager::getInstance()->free(imageStuff);
    ResourceManager::getInstance()->free(imageStatus);
    delete metronome;
    for (int i = 0; i < 49; i++)
    {
        delete texts[i];
    }
}

void Menu::init()
{
    for (int ii = 0; ii < 49; ii++)
    {
        delete texts[ii];
        texts[ii] = TextManager::getInstance()->getText(108 + ii);
    }

    initFromSelectedStuff();
    step = MENU_OFF;
    anim = 0;
}

void Menu::handleActions(Action *action)
{
    if (action->isAction(INVENTAIRE))
    {
        stop();
        return;
    }
    if (!link->isAbleToChangeStuff() || step != MENU_ON)
    {
        return;
    }

    bool hasMoved = false;
    if (action->isAction(PUSH_UP))
    {
        if (--j < 0)
            j = 3;
        hasMoved = true;
    }
    if (action->isAction(PUSH_DOWN))
    {
        if (++j > 3)
            j = 0;
        hasMoved = true;
    }
    if (action->isAction(PUSH_LEFT))
    {
        if (--i < 0)
            i = 3;
        hasMoved = true;
    }
    if (action->isAction(PUSH_RIGHT))
    {
        if (++i > 3)
            i = 0;
        hasMoved = true;
    }

    if (hasMoved)
    {
        metronome->reset();
        updateSelectedStuff();
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Menu::loop()
{
    if (step == MENU_START)
    {
        if (++anim == 8)
        {
            step = MENU_ON;
            metronome->reset();
        }
    }
    else if (step == MENU_END)
    {
        if (--anim == 0)
        {
            step = MENU_OFF;
            MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        }
    }
    metronome->loop();
}

void Menu::draw()
{
    int df = 200 - anim * 25;
    drawObjects(df);
    drawNomObject(df);
    drawHearts(df);
    drawGemmes(df);
    drawEquipement(df);
    drawStatus(df);
}

void Menu::drawObjects(int df)
{

    drawCadre(16 - df, 16, 16 * 9, 16 * 9);

    if (link->getInventory()->hasObject(ARC_FEE))
    {
        link->getInventory()->draw(ARC_FEE, 32 - df, 32);
    }
    else if (link->getInventory()->hasObject(ARC))
    {
        link->getInventory()->draw(ARC, 32 - df, 32);
    }

    if (link->getInventory()->hasObject(GRAPPIN))
    {
        link->getInventory()->draw(GRAPPIN, 64 - df, 32);
    }

    if (link->getInventory()->hasObject(BOMBES) && link->getStatus()->getBombs())
    {
        link->getInventory()->draw(BOMBES, 96 - df, 32);
    }

    if (link->getInventory()->hasObject(FLECHE_FEU))
    {
        link->getInventory()->draw(FLECHE_FEU, 128 - df, 32);
    }
    else if (link->getInventory()->hasObject(TROC_GEMME_ROUGE))
    {
        link->getInventory()->draw(TROC_GEMME_ROUGE, 128 - df, 32);
    }

    if (link->getInventory()->hasObject(BAGUETTE_FEU))
    {
        link->getInventory()->draw(BAGUETTE_FEU, 32 - df, 64);
    }

    if (link->getInventory()->hasObject(BAGUETTE_GLACE))
    {
        link->getInventory()->draw(BAGUETTE_GLACE, 64 - df, 64);
    }

    if (link->getInventory()->hasObject(LANTERNE))
    {
        link->getInventory()->draw(LANTERNE, 96 - df, 64);
    }

    if (link->getInventory()->hasObject(FLECHE_GLACE))
    {
        link->getInventory()->draw(FLECHE_GLACE, 128 - df, 64);
    }
    else if (link->getInventory()->hasObject(TROC_GEMME_BLEUE))
    {
        link->getInventory()->draw(TROC_GEMME_BLEUE, 128 - df, 64);
    }

    if (link->getInventory()->hasObject(MARTEAU))
    {
        link->getInventory()->draw(MARTEAU, 32 - df, 96);
    }

    if (link->getInventory()->hasObject(OCARINA))
    {
        link->getInventory()->draw(OCARINA, 64 - df, 96);
    }

    if (link->getInventory()->hasObject(CANNE_A_PECHE_3))
    {
        link->getInventory()->draw(CANNE_A_PECHE_3, 96 - df, 96);
    }
    else if (link->getInventory()->hasObject(CANNE_A_PECHE_2))
    {
        link->getInventory()->draw(CANNE_A_PECHE_2, 96 - df, 96);
    }
    else if (link->getInventory()->hasObject(CANNE_A_PECHE_1))
    {
        link->getInventory()->draw(CANNE_A_PECHE_1, 96 - df, 96);
    }

    if (link->getInventory()->hasObject(FLECHE_LUMIERE))
    {
        link->getInventory()->draw(FLECHE_LUMIERE, 128 - df, 96);
    }
    else if (link->getInventory()->hasObject(TROC_GEMME_JAUNE))
    {
        link->getInventory()->draw(TROC_GEMME_JAUNE, 128 - df, 96);
    }

    if (link->getInventory()->hasObject(FLACON_1))
    {
        link->getInventory()->draw(FLACON_1, 32 - df, 128);
    }

    if (link->getInventory()->hasObject(FLACON_2))
    {
        link->getInventory()->draw(FLACON_2, 64 - df, 128);
    }

    if (link->getInventory()->hasObject(FLACON_3))
    {
        link->getInventory()->draw(FLACON_3, 96 - df, 128);
    }

    if (link->getInventory()->hasObject(FLACON_4))
    {
        link->getInventory()->draw(FLACON_4, 128 - df, 128);
    }
    else if (link->getInventory()->hasObject(TROC_GEMME_VERTE))
    {
        link->getInventory()->draw(TROC_GEMME_VERTE, 128 - df, 128);
    }

    if (df == 0 && !metronome->getValue())
    {
        if (link->isAbleToChangeStuff())
        {
            WindowManager::getInstance()->draw(imageMenu, 51, 3, 26, 26, 32 - 5 + i * 32, 32 - 5 + j * 32);
        }
        else
        {
            WindowManager::getInstance()->draw(imageMenu, 83, 3, 26, 26, 32 - 5 + i * 32, 32 - 5 + j * 32);
        }
    }
}

void Menu::drawNomObject(int df)
{
    drawCadre(16 * 11, 16 - df, 16 * 8, 16 * 2);
    Equipment current = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getCurrent();
    if (!link->getInventory()->hasObject(current))
    {
        return;
    }
    int tmp = 0;
    switch (current)
    {
    case ARC:
        tmp = 0;
        break;
    case ARC_FEE:
        tmp = 1;
        break;
    case GRAPPIN:
        tmp = 2;
        break;
    case BOMBES:
        tmp = 3;
        break;
    case FLECHE_FEU:
        tmp = 4;
        break;
    case TROC_GEMME_ROUGE:
        if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(0) == TGR_RIEN)
            return;
        if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(0) == TGR_RIEN_2)
            return;
        tmp = 5 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(0);
        if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(0) > TGR_RIEN)
        {
            tmp--;
        }
        if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(0) > TGR_RIEN_2)
        {
            tmp--;
        }
        break;
    case BAGUETTE_FEU:
        tmp = 12;
        break;
    case BAGUETTE_GLACE:
        tmp = 13;
        break;
    case LANTERNE:
        tmp = 14;
        break;
    case FLECHE_GLACE:
        tmp = 15;
        break;
    case TROC_GEMME_BLEUE:
        tmp = 16 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(1);
        break;
    case MARTEAU:
        tmp = 23;
        break;
    case OCARINA:
        tmp = 24;
        break;
    case CANNE_A_PECHE_1:
        tmp = 25;
        break;
    case CANNE_A_PECHE_2:
        tmp = 26;
        break;
    case CANNE_A_PECHE_3:
        tmp = 27;
        break;
    case FLECHE_LUMIERE:
        tmp = 28;
        break;
    case TROC_GEMME_JAUNE:
        tmp = 29 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(2);
        break;
    case TROC_GEMME_VERTE:
        tmp = 37 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getTrocGemme(3);
        break;
    case FLACON_1:
        tmp = 44 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getFlacon(0);
        break;
    case FLACON_2:
        tmp = 44 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getFlacon(1);
        break;
    case FLACON_3:
        tmp = 44 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getFlacon(2);
        break;
    case FLACON_4:
        tmp = 44 + MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getFlacon(3);
        break;
    default:
        tmp = 0;
    }
    texts[tmp]->display(184, 24 - df);
}

void Menu::drawHearts(int df)
{
    drawCadre(16 * 16 + df, 16 * 11, 16 * 3, 16 * 3);
    WindowManager::getInstance()->draw(imageCoeur, link->getInventory()->nbQuartCoeur() * 16, 0, 16, 16, 16 * 17 + df, 16 * 12);
}

void Menu::drawGemmes(int df)
{
    drawCadre(16, 16 * 11 + df, 16 * 3, 16 * 3);
    if (nbTotalGemme)
    {
        WindowManager::getInstance()->draw(imageStuff, 112, 16, 16, 16, 32, 188 + df);
        drawNombre(nbGemme, (nbGemme >= 100 ? 28 : 32), 16 * 13 + df, nbGemme >= 100 ? 3 : 2, allGemme);
    }
}

void Menu::drawEquipement(int df)
{
    drawCadre(16 * 5, 16 * 11 + df, 16 * 10, 16 * 3);

    texts[48]->display(84, 180 + df);

    if (link->getEpee())
    {
        int srcX = link->getStatus()->isOniLink() ? 96 : (link->getEpee() - 1) * 16;
        WindowManager::getInstance()->draw(imageStuff, srcX, 16, 16, 16, 86, 198 + df);
    }

    if (link->getBouclier())
    {
        int srcX = link->getStatus()->isOniLink() ? 64 : (link->getBouclier() - 1) * 16;
        WindowManager::getInstance()->draw(imageStuff, srcX, 32, 16, 16, 105, 198 + df);
    }

    WindowManager::getInstance()->draw(imageStuff, link->getStatus()->isOniLink() ? 64 : (link->getTunique() - 1) * 16, 0, 16, 16, 124, 198 + df);

    if (link->getInventory()->hasObject(BOTTES))
    {
        WindowManager::getInstance()->draw(imageStuff, 80, 0, 16, 16, 143, 198 + df);
    }

    if (link->getInventory()->hasObject(GANTS))
    {
        link->getInventory()->draw(link->getInventory()->hasObject(GANTS_2) ? GANTS_2 : GANTS, 162, 198 + df);
    }

    if (link->getInventory()->hasObject(PALMES))
    {
        link->getInventory()->draw(PALMES, 181, 198 + df);
    }

    if (link->getInventory()->hasObject(PERLE))
    {
        WindowManager::getInstance()->draw(imageStuff, 64, 64, 16, 16, 200, 198 + df);
    }

    if (link->getInventory()->hasObject(LIVRE))
    {
        WindowManager::getInstance()->draw(imageStuff, 96, 96, 16, 16, 219, 198 + df);
    }

    if (link->getInventory()->getTrocGemme(0) == TGR_ENCLUME)
    {
        if (link->getInventory()->hasObject(BOTTES))
        {
            WindowManager::getInstance()->draw(imageMenu, 83, 3, 26, 26, 143 - 5, 198 - 5 + df);
        }
        if (link->getInventory()->hasObject(PALMES))
        {
            WindowManager::getInstance()->draw(imageMenu, 83, 3, 26, 26, 181 - 5, 198 - 5 + df);
        }
    }
}

void Menu::drawStatus(int df)
{
    drawCadre(16 * 11, 16 * 4 - df, 16 * 8, 16 * 6);

    // ligne 1

    // force
    WindowManager::getInstance()->draw(imageStuff, 92, 32, 12, 12, 181, 69 - df);
    int force = link->getForce();
    drawNombre(force, 191, 72 - df, force > 9 ? 2 : 1, force == 10 ? 1 : 0);

    // defense
    WindowManager::getInstance()->draw(imageStuff, 104, 32, 12, 12, 207, 69 - df);
    int defense = link->getDefense();
    drawNombre(defense, 218, 72 - df, defense > 9 ? 2 : 1, defense == 10 ? 1 : 0);

    // time
    WindowManager::getInstance()->draw(imageStuff, 80, 32, 12, 12, 234, 69 - df);
    int time = MainController::getInstance()->getGameController()->getTime();
    int hours = time / 3600;
    int minutes = (time - hours * 3600) / 60;
    int seconds = time % 60;
    drawNombre(hours, 246, 72 - df, 2);
    drawSeparateur(261, 72 - df);
    drawNombre(minutes, 264, 72 - df, 2);
    drawSeparateur(279, 72 - df);
    drawNombre(seconds, 282, 72 - df, 2);

    // ligne 2

    // bourses
    int rubisMax = link->getStatus()->getMaxRupees();
    int ganonOrMax = link->getStatus()->getMaxGanonOr();
    int pieceOrMax = link->getStatus()->getMaxPieceOr();

    // bourse rubis
    if (rubisMax)
    {
        int srcX = 0;
        if (rubisMax >= 200)
            srcX += 16;
        if (rubisMax >= 500)
            srcX += 16;
        if (rubisMax == 999)
            srcX += 16;
        WindowManager::getInstance()->draw(imageStuff, srcX, 80, 16, 16, 180, 84 - df);
        int rubis = link->getStatus()->getVirtualRupees();
        drawNombre(rubis, 196, 89 - df, rubisMax > 99 ? 3 : 2, rubis == rubisMax ? 1 : 0);
    }

    // bourse ganon d'or
    if (ganonOrMax)
    {
        int offsetX = pieceOrMax ? 0 : 16;
        int srcX = 64;
        if (ganonOrMax >= 200)
            srcX += 16;
        if (ganonOrMax >= 500)
            srcX += 16;
        if (ganonOrMax == 999)
            srcX += 16;
        WindowManager::getInstance()->draw(imageStuff, srcX, 80, 16, 16, 220 + offsetX, 84 - df);
        int ganonOr = link->getStatus()->getVirtualGanonOr();
        drawNombre(ganonOr, 236 + offsetX, 89 - df, ganonOrMax > 99 ? 3 : 2, ganonOr == ganonOrMax ? 1 : 0);
    }

    // bourse piece or
    if (pieceOrMax)
    {
        int srcX = 0;
        if (pieceOrMax >= 200)
            srcX += 16;
        if (pieceOrMax >= 500)
            srcX += 16;
        if (pieceOrMax == 999)
            srcX += 16;
        WindowManager::getInstance()->draw(imageStuff, srcX, 96, 16, 16, 260, 84 - df);
        int pieceOr = link->getStatus()->getVirtualPieceOr();
        drawNombre(pieceOr, 276, 89 - df, pieceOrMax > 99 ? 3 : 2, pieceOr == pieceOrMax ? 1 : 0);
    }

    // ligne 3

    // carquois
    if (link->getInventory()->hasObject(ARC))
    {
        int fleches = link->getStatus()->getMaxArrows();
        WindowManager::getInstance()->draw(imageStuff, 112, 0, 16, 16, 180, 102 - df);
        drawNombre(fleches, 196, 109 - df, 2, fleches == 70 ? 1 : 0);
        if (link->getInventory()->hasObject(RECUP_FLECHE))
        {
            WindowManager::getInstance()->draw(imageStuff, 116, 32, 9, 8, 196, 102 - df);
        }
    }

    // bombes
    if (link->getInventory()->hasObject(BOMBES))
    {
        int bombes = link->getStatus()->getMaxBombs();
        WindowManager::getInstance()->draw(imageStuff, 96, 0, 16, 16, 220, 102 - df);
        drawNombre(bombes, 236, 109 - df, 2, bombes == 30 ? 1 : 0);
        if (link->getInventory()->hasObject(RECUP_BOMBE))
        {
            WindowManager::getInstance()->draw(imageStuff, 116, 32, 9, 8, 236, 102 - df);
        }
    }

    // chants
    if (link->getInventory()->hasObject(CHANT_1))
    {
        link->getInventory()->draw(CHANT_1, 256, 102 - df);
    }
    if (link->getInventory()->hasObject(CHANT_2))
    {
        link->getInventory()->draw(CHANT_2, 270, 102 - df);
    }
    if (link->getInventory()->hasObject(CHANT_3))
    {
        link->getInventory()->draw(CHANT_3, 284, 102 - df);
    }

    // ligne 4

    int dstY = link->getInventory()->nbCristaux() == 0 ? 138 : 120;

    // medaillons
    if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAvancement() >= AV_STELE_LUE)
    {
        for (int i = 0; i < NB_MEDAILLONS; i++)
        {
            if (link->getInventory()->hasMedaillon(i))
            {
                WindowManager::getInstance()->draw(imageStuff, 16 * i, 64, 16, 16, 180 + 17 * i, dstY - df);
            }
            else
            {
                WindowManager::getInstance()->draw(imageStuff, 48, 64, 16, 16, 180 + 17 * i, dstY - df);
            }
        }
    }

    // cle du temps
    if (link->getInventory()->hasObject(CLE_TEMPS))
    {
        WindowManager::getInstance()->draw(imageStuff, 80, 64, 16, 16, 231, dstY - df);
    }
    // arc or
    if (link->getInventory()->hasObject(ARC_OR))
    {
        WindowManager::getInstance()->draw(imageStuff, 96, 64, 16, 16, 248, dstY - df);
    }
    // detecteur
    if (link->getInventory()->hasObject(DETECTEUR))
    {
        WindowManager::getInstance()->draw(imageStuff, 112, 64, 16, 16, 265, dstY - df);
    }
    // masque
    if (link->getInventory()->hasObject(MASQUE))
    {
        link->getInventory()->draw(MASQUE, 282, dstY - df);
    }

    // ligne 5

    // cristaux
    if (dstY == 120)
    {
        for (int i = 0; i < NB_CRISTAUX; i++)
        {
            WindowManager::getInstance()->draw(imageStuff, link->getInventory()->hasCristal(i) ? 64 : 80, 96, 16, 16, 180 + 17 * i, 138 - df);
        }
    }
}

void Menu::drawCadre(int x, int y, int w, int h)
{
    WindowManager::getInstance()->draw(imageMenu, 0, 0, 16, 16, x, y);
    WindowManager::getInstance()->draw(imageMenu, 32, 0, 16, 16, x + w - 16, y);
    WindowManager::getInstance()->draw(imageMenu, 0, 32, 16, 16, x, y + h - 16);
    WindowManager::getInstance()->draw(imageMenu, 32, 32, 16, 16, x + w - 16, y + h - 16);

    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        WindowManager::getInstance()->draw(imageMenu, 16, 0, 16, 16, i, y);
        WindowManager::getInstance()->draw(imageMenu, 16, 32, 16, 16, i, y + h - 16);
    }

    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        WindowManager::getInstance()->draw(imageMenu, 0, 16, 16, 16, x, j);
        WindowManager::getInstance()->draw(imageMenu, 32, 16, 16, 16, x + w - 16, j);
    }

    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        for (int j = y + 16; j < y + h - 16; j += 16)
        {
            WindowManager::getInstance()->draw(imageMenu, 16, 16, 16, 16, i, j);
        }
    }
}

void Menu::drawNombre(int val, int x, int y, int nb, int color)
{
    int val2;
    int srcX;
    int srcY;
    int dstX = x;

    // si on commence par les centaines
    if (nb >= 3)
    {
        val2 = val / 100;
        srcX = (val2 % 5) * 8;
        srcY = ((int)(val2 / 5)) * 8 + 16 * color;
        WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    // les dizaines
    if (nb >= 2)
    {
        val2 = (val % 100) / 10;
        srcX = (val2 % 5) * 8;
        srcY = ((int)(val2 / 5)) * 8 + 16 * color;
        WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    // unit�es
    val2 = val % 10;
    srcX = (val2 % 5) * 8;
    srcY = ((int)(val2 / 5)) * 8 + 16 * color;
    WindowManager::getInstance()->draw(imageChiffres, srcX, srcY, 8, 8, dstX, y);
}

void Menu::drawSeparateur(int x, int y)
{
    WindowManager::getInstance()->draw(imageChiffres, 40, 0, 4, 8, x, y);
}

void Menu::start()
{
    if (step == MENU_OFF)
    {
        link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
        AudioManager::getInstance()->playSound(TS_MENU1);
        step = MENU_START;
        anim = 0;

        nbTotalGemme = link->getInventory()->totalGemmeForce();
        nbGemme = nbTotalGemme ? link->getInventory()->nbGemmeForce() : 0;
        if (link->getInventory()->hasObject(DETECTEUR))
        {
            allGemme = MainController::getInstance()->getGameController()->getSceneController()->getScene()->nbGemmeForce();
        }
        else
        {
            allGemme = 0;
        }
    }
}

void Menu::stop()
{
    if (step == MENU_START || step == MENU_ON)
    {
        AudioManager::getInstance()->playSound(TS_MENU2);
        step = MENU_END;
    }
}

void Menu::initFromSelectedStuff()
{
    Equipment current = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->getCurrent();
    int tmp = 0;
    switch (current)
    {
    case ARC:
    case ARC_FEE:
        tmp = 0;
        break;
    case GRAPPIN:
        tmp = 1;
        break;
    case BOMBES:
        tmp = 2;
        break;
    case FLECHE_FEU:
    case TROC_GEMME_ROUGE:
        tmp = 3;
        break;
    case BAGUETTE_FEU:
        tmp = 4;
        break;
    case BAGUETTE_GLACE:
        tmp = 5;
        break;
    case LANTERNE:
        tmp = 6;
        break;
    case FLECHE_GLACE:
    case TROC_GEMME_BLEUE:
        tmp = 7;
        break;
    case MARTEAU:
        tmp = 8;
        break;
    case OCARINA:
        tmp = 9;
        break;
    case CANNE_A_PECHE_1:
    case CANNE_A_PECHE_2:
    case CANNE_A_PECHE_3:
        tmp = 10;
        break;
    case FLECHE_LUMIERE:
    case TROC_GEMME_JAUNE:
        tmp = 11;
        break;
    case FLACON_1:
        tmp = 12;
        break;
    case FLACON_2:
        tmp = 13;
        break;
    case FLACON_3:
        tmp = 14;
        break;
    case FLACON_4:
    case TROC_GEMME_VERTE:
        tmp = 15;
        break;
    default:
        tmp = 0;
    }
    i = tmp % 4;
    j = tmp / 4;
}

Equipment Menu::getSelectedStuff()
{
    int tmp = i + j * 4;
    switch (tmp)
    {
    case 0:
        if (link->getInventory()->hasObject(ARC_FEE))
            return ARC_FEE;
        return ARC;
    case 1:
        return GRAPPIN;
    case 2:
        return BOMBES;
    case 3:
        if (link->getInventory()->hasObject(FLECHE_FEU))
            return FLECHE_FEU;
        return TROC_GEMME_ROUGE;
    case 4:
        return BAGUETTE_FEU;
    case 5:
        return BAGUETTE_GLACE;
    case 6:
        return LANTERNE;
    case 7:
        if (link->getInventory()->hasObject(FLECHE_GLACE))
            return FLECHE_GLACE;
        return TROC_GEMME_BLEUE;
    case 8:
        return MARTEAU;
    case 9:
        return OCARINA;
    case 10:
        if (link->getInventory()->hasObject(CANNE_A_PECHE_3))
            return CANNE_A_PECHE_3;
        if (link->getInventory()->hasObject(CANNE_A_PECHE_2))
            return CANNE_A_PECHE_2;
        return CANNE_A_PECHE_1;
    case 11:
        if (link->getInventory()->hasObject(FLECHE_LUMIERE))
            return FLECHE_LUMIERE;
        return TROC_GEMME_JAUNE;
    case 12:
        return FLACON_1;
    case 13:
        return FLACON_2;
    case 14:
        return FLACON_3;
    case 15:
        if (link->getInventory()->hasObject(FLACON_4))
            return FLACON_4;
        return TROC_GEMME_VERTE;
    }
    return ARC;
}

void Menu::updateSelectedStuff()
{
    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory()->setCurrent(getSelectedStuff());
}
