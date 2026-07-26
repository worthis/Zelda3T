#include "Hud.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

Hud::Hud(Status* status, Inventory* inventory, bool isFrench) : status(status), inventory(inventory), french(isFrench),
animBoss(0), animBoss2(0), animBossX(0), bossLife(0), bossMaxLife(0), bossLife2(0), bossMaxLife2(0), removeBoss(false), etage(0), displayEtg(0),
time(false), casino(false), destFinal(false) {
    image = ResourceManager::getInstance()->loadImage("data/images/status/status.png", true);
    chiffres = ResourceManager::getInstance()->loadImage("data/images/status/chiffres.png", true);
    level = ResourceManager::getInstance()->loadImage("data/images/status/level.png", true);
}

Hud::~Hud() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(chiffres);
    ResourceManager::getInstance()->free(level);
}

void Hud::loop() {
    if (animBoss > 0 && (bossLife <= 0 || removeBoss))  {
        animBoss--;
    } else if (animBoss > 0 && animBoss < 50) {
        animBoss++;
    }
    if (animBoss2 > 0 && (bossLife2 <= 0 || removeBoss))  {
        animBoss2--;
    } else if (animBoss2 > 0 && animBoss2 < 50) {
        animBoss2++;
    }
    if (animBoss && animBoss2 && animBossX < 50) {
        animBossX++;
    }
    if (animBossX > 0 && (animBoss == 0 || animBoss2 == 0)) {
        animBossX--;
    }

    if (displayEtg) displayEtg--;
}

void Hud::draw() {
    drawLife();
    drawMagic();
    drawItems();
    drawObject();
    drawBonus();
    drawBoss();
    drawEtage();
    drawInfo();
}

void Hud::reset() {
    removeBoss = true;
    time = false;
    casino = false;
    destFinal = false;
}

void Hud::displayTime() {
    time = true;
}

void Hud::hideTime() {
    time = false;
}

void Hud::displayCasino() {
    casino = true;
}

void Hud::hideCasino() {
    casino = false;
}

void Hud::displayDestFinal() {
    destFinal = true;
}
void Hud::hideDestFinal() {
    destFinal = false;
}

void Hud::displayEtage() {
    displayEtg = 128;
    etage = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getEtage();
    if (etage == 3) {
        displayEtg = 0;
    }
}

void Hud::drawEtage() {
    if (displayEtg) {
        WindowManager::getInstance()->draw(level, french ? 0 : 32, 32 - etage * 16, 32, 16, 288, 0);
    }
}

void Hud::setBossLife(int life, int maxLife) {
    bossLife = life;
    bossMaxLife = maxLife;
    removeBoss = false;
    if (animBoss == 0) {
        animBoss = 1;
    }
}

void Hud::setBossLife2(int life, int maxLife) {
    bossLife2 = life;
    bossMaxLife2 = maxLife;
    removeBoss = false;
    if (animBoss2 == 0) {
        animBoss2 = 1;
    }
}

void Hud::drawBoss() {
    if (animBoss) {
        int dstY = 220 + 50 - animBoss;
        WindowManager::getInstance()->draw(image, 100, 45, 100, 10, 110 - animBossX, dstY);
        int srcW = (bossLife * 90) / bossMaxLife;
        WindowManager::getInstance()->draw(image, 95 - srcW, 49, srcW, 2, 115 - animBossX, dstY + 4);
    }
    if (animBoss2) {
        int dstY = 220 + 50 - animBoss2;
        WindowManager::getInstance()->draw(image, 100, 45, 100, 10, 110 + animBossX, dstY);
        int srcW = (bossLife2 * 90) / bossMaxLife2;
        WindowManager::getInstance()->draw(image, 95 - srcW, 49, srcW, 2, 115 + animBossX, dstY + 4);
    }
}

void Hud::drawBonus() {
    int dstX = 320 - 24;
    int dstY = 240 - 24;
    if (status->getGel()) {
        WindowManager::getInstance()->draw(image, 104, 55, 12, 12, dstX + 2, dstY);
        WindowManager::getInstance()->draw(image, 68, 67, 16, 3, dstX, dstY + 13);
        int value = (status->getGel() * 14) / status->getMaxGel();
        if (value < 14) value ++;
        WindowManager::getInstance()->draw(image, 49, 65, value, 1, dstX + 1, dstY + 14);
        dstX -= 24;
    }
    if (status->getIvre()) {
        WindowManager::getInstance()->draw(image, 132, 55, 12, 12, dstX + 2, dstY);
        WindowManager::getInstance()->draw(image, 68, 67, 16, 3, dstX, dstY + 13);
        int value = (status->getIvre() * 14) / status->getMaxIvre();
        if (value < 14) value ++;
        WindowManager::getInstance()->draw(image, 49, 65, value, 1, dstX + 1, dstY + 14);
    }
}

void Hud::drawInfo() {
    if (casino) {
        int value = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getCasino();
        int dstY = 16*14 - (animBoss ? 8 : 0);
        WindowManager::getInstance()->draw(image, 64, 18, 8, 8, 16, dstY);
        drawNombre(value, 150, 32, dstY, 3);
    }
    if (time) {
        int value = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getTempsCasinoRestant();
        WindowManager::getInstance()->draw(image, 92, 55, 12, 10, 16*17+8, 16*14);
        drawNombre(value, 12, 320-24, 16*14, 2);
    }
    if (destFinal) {
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        // degats
        int value = scene->getMap()->getDestFinal();
        int value2 = value == 1 ? value : value / 2;
        WindowManager::getInstance()->draw(image, value == 1 ? 149 : 141, 9, 7, 7, 16, 16*14);
        drawNombre(value2, 20, 32, 16*14, 2);

        // monsters
        if (!scene->getCoffre(15, 13) || !scene->getCoffre(15, 14) || !scene->getCoffre(15, 15) || !scene->getCoffre(15, 16)
            || !scene->getCoffre(15, 17) || !scene->getCoffre(15, 18) || !scene->getCoffre(15, 19)) {
            value = scene->getMap()->getDestFinalTypeEnn();
            WindowManager::getInstance()->draw(image, 96, 33, 8, 8, 16*15, 16*14);
            drawNombre(value, 12, 16*16, 16*14, 2);

            value = scene->getMap()->getDestFinalNbEnn();
            WindowManager::getInstance()->draw(image, 104, 33, 6, 6, 16*17+5, 16*14+1);
            drawNombre(value, 99, 16*18, 16*14, 2);
        }
    }
}

void Hud::drawLife() {

    //life
    int srcY = french ? 17 : 0;
    int srcH = french ? 8 : 7;
    WindowManager::getInstance()->draw(image, 158, srcY, 44, srcH, 250, 10);

    //hearts
    int srcX = 0;
    int life = status->getLife();
    for(int i = 0; i < status->getMaxLife() / 2; i++) {
        if (life - (i * 2) > 1) srcX = 141;
        if (life - (i * 2) == 1) srcX = 149;
        if (life - (i * 2) < 1) srcX = 157;

        WindowManager::getInstance()->draw(image, srcX, 9, 7, 7, 233 + ((i % 10) * 8), 19 + 8 * ((int)(i / 10)));
    }
}

void Hud::drawMagic() {
    int dstX = 10;
    //jauge magie
    if (status->getMaxMagic() > 0) {
        WindowManager::getInstance()->draw(image, 0, 0, 16, 45, dstX, 10);

        //demi magie
        if (status->getMaxMagic() > 32) {
            WindowManager::getInstance()->draw(image, 186, 37, 16, 8, dstX, 10);
        }

        int ratio = status->getMagic() / (status->getMaxMagic() / 32);
        WindowManager::getInstance()->draw(image, 124, 8, 8, ratio, dstX + 4, 50 - ratio);
    }
}

void Hud::drawItems() {

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Epoque epoque = scene->getMap()->getEpoque();

    //rupees
    if (epoque == EP_PASSE && status->getMaxPieceOr()) {
        WindowManager::getInstance()->draw(image, 52, 18, 8, 8, 129, 10);
        drawNombre(status->getPieceOr(), status->getMaxPieceOr(), status->getMaxPieceOr() > 99 ? 121 : 125, 20, status->getMaxPieceOr() > 99 ? 3 : 2);
    } else if (epoque == EP_FUTUR && status->getMaxGanonOr()) {
        WindowManager::getInstance()->draw(image, 64, 18, 8, 8, 129, 10);
        drawNombre(status->getGanonOr(), status->getMaxGanonOr(), status->getMaxGanonOr() > 99 ? 121 : 125, 20, status->getMaxGanonOr() > 99 ? 3 : 2);
    } else if (epoque == EP_PRESENT && status->getMaxRupees()) {
        WindowManager::getInstance()->draw(image, 52, 0, 8, 8, 129, 10);
        drawNombre(status->getRupees(), status->getMaxRupees(), status->getMaxRupees() > 99 ? 121 : 125, 20, status->getMaxRupees() > 99 ? 3 : 2);
    }

    //bombs
    if (inventory->hasObject(BOMBES)) {
        WindowManager::getInstance()->draw(image, 80, 0, 8, 8, 157, 10);
        drawNombre(status->getBombs(), status->getMaxBombs(), 153, 20, 2);
    }

    //arrows
    if (inventory->hasObject(ARC)) {
        int srcY = inventory->hasObject(ARC_FEE) ? 21 : 0;
        WindowManager::getInstance()->draw(image, 101, srcY, 14, 8, 178, 10);
        drawNombre(status->getArrows(), status->getMaxArrows(), 177, 20, 2);
    }

    //keys
    if (scene->getMap()->getId() >= 46 && scene->getMap()->getId() < 61
        && (scene->getMap()->getId() != 57 || scene->getAvancement() >= AV_TELE_ZELDA)) {
        int nbKeys = scene->getCoffre(scene->getMap()->getId() - 45, 3);
        WindowManager::getInstance()->draw(image, 50, 28, 8, 8, 89, 10);
        drawNombre(nbKeys, 99, nbKeys > 9 ? 85 : 89, 20, nbKeys > 9 ? 2 : 1);
    } else if (scene->getMap()->getId() == 155 && scene->getAvancement() == AV_CLE_PRISON_F_TROUVEE) {
        WindowManager::getInstance()->draw(image, 50, 28, 8, 8, 89, 10);
        drawNombre(1, 99, 89, 20, 1);
    } else if (scene->getMap()->getId() == 156 && scene->getMap()->isIndoor()) {
        int nbKeys = scene->getCoffre(16, 3);
        WindowManager::getInstance()->draw(image, 50, 28, 8, 8, 89, 10);
        drawNombre(nbKeys, 99, nbKeys > 9 ? 85 : 89, 20, nbKeys > 9 ? 2 : 1);
    }
}

void Hud::drawObject() {
    if (inventory->hasObject()) {
        int dstX = 10;
        if (status->getMaxMagic() > 0) dstX += 17;

        WindowManager::getInstance()->draw(image, 17, 5, 22, 22, dstX, 15);

        Equipment e = inventory->getCurrent();
        if (inventory->hasObject(e)) {
            if (e == BOMBES && !status->getBombs()) {
                return;
            }
            inventory->draw(e, dstX + 3, 18);
        }
    }
}

void Hud::drawNombre(int val, int max, int x, int y, int nb) {
    int val2;
    int srcX;
    int srcY;
    int dstX = x;

    //si on commence par les centaines
    if (nb >= 3) {
        val2 = val / 100;
        srcX = (val2%5)*8;
        srcY = ((int)(val2/5))*8;
        if (val == max) srcY += 16;
        WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    //les dizaines
    if (nb >= 2) {
        val2 = (val%100)/10;
        srcX = (val2%5)*8;
        srcY = ((int)(val2/5))*8;
        if (val == max) srcY += 16;
        WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);
        dstX += 8;
    }

    //unitées
    val2 = val%10;
    srcX = (val2%5)*8;
    srcY = ((int)(val2/5))*8;
    if (val == max) srcY += 16;
    WindowManager::getInstance()->draw(chiffres, srcX, srcY, 8, 8, dstX, y);

}

void Hud::instantBoss() {
    animBoss = 50;
}
