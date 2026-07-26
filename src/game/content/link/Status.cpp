#include "Status.h"

#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

Status::Status(Save* save) : invincible(0), gel(0), maxGel(0), ivre(0), maxIvre(0) {
    loadFromSave(save);
    chrono.reset();
}

Status::~Status() {
}

void Status::loadFromSave(Save* save) {
    life = save->getLife();
    maxLife = save->getMaxLife();
    magic = save->getMagic();
    maxMagic = save->getMaxMagic();
    rupees = save->getRupees();
    maxRupees = save->getMaxRupees();
    ganonOr = save->getGanonOr();
    maxGanonOr = save->getMaxGanonOr();
    pieceOr = save->getPieceOr();
    maxPieceOr = save->getMaxPieceOr();
    arrows = save->getArrows();
    bombs = save->getBombs();
    maxArrows = save->getMaxArrows();
    maxBombs = save->getMaxBombs();
    lifeToAdd = save->getLifeToAdd();
    magicToAdd = save->getMagicToAdd();
    rupeesToAdd = save->getRupeesToAdd();
    ganonOrToAdd = save->getGanonOrToAdd();
    pieceOrToAdd = save->getPieceOrToAdd();
    deaths = save->getDeaths();
    oniLink = save->isOniLink();
}

void Status::saveData(Save* save) {
    save->setLife(life);
    save->setMaxLife(maxLife);
    save->setMagic(magic);
    save->setMaxMagic(maxMagic);
    save->setRupees(rupees);
    save->setMaxRupees(maxRupees);
    save->setGanonOr(ganonOr);
    save->setMaxGanonOr(maxGanonOr);
    save->setPieceOr(pieceOr);
    save->setMaxPieceOr(maxPieceOr);
    save->setArrows(arrows);
    save->setBombs(bombs);
    save->setMaxArrows(maxArrows);
    save->setMaxBombs(maxBombs);
    save->setLifeToAdd(lifeToAdd);
    save->setMagicToAdd(magicToAdd);
    save->setRupeesToAdd(rupeesToAdd);
    save->setGanonOrToAdd(ganonOrToAdd);
    save->setPieceOrToAdd(pieceOrToAdd);
    save->setDeaths(deaths);
    save->setOniLink(oniLink);
}

void Status::loop() {

    if (gel > 0) gel--;
    if (ivre > 0) ivre--;

    if (rupeesToAdd > 0) {
        if (rupees < maxRupees) {
            rupeesToAdd--;
            setRupees(rupees + 1);
        } else {
            rupeesToAdd = 0;
        }
    } else if (rupeesToAdd < 0) {
        if (rupees > 0) {
            rupeesToAdd++;
            setRupees(rupees - 1);
        } else {
            rupeesToAdd = 0;
        }
    }

    if (ganonOrToAdd > 0) {
        if (ganonOr < maxGanonOr) {
            ganonOrToAdd--;
            setGanonOr(ganonOr + 1);
        } else {
            ganonOrToAdd = 0;
        }
    } else if (ganonOrToAdd < 0) {
        if (ganonOr > 0) {
            ganonOrToAdd++;
            setGanonOr(ganonOr - 1);
        } else {
            ganonOrToAdd = 0;
        }
    }

    if (pieceOrToAdd > 0) {
        if (pieceOr < maxPieceOr) {
            pieceOrToAdd--;
            setPieceOr(pieceOr + 1);
        } else {
            pieceOrToAdd = 0;
        }
    } else if (pieceOrToAdd < 0) {
        if (pieceOr > 0) {
            pieceOrToAdd++;
            setPieceOr(pieceOr - 1);
        } else {
            pieceOrToAdd = 0;
        }
    }

    if (chrono.getElapsedTime() >= 80) {

        if (lifeToAdd > 0) {
            if (life < maxLife) {
                lifeToAdd--;
                setLife(life + 1);
                if (life % 2 == 0) {
                    AudioManager::getInstance()->playSound(TS_HEART);
                }
            } else {
                lifeToAdd = 0;
            }
        } else if (lifeToAdd < 0) {
            if (life > 0) {
                lifeToAdd++;
                setLife(life - 1);
            } else {
                lifeToAdd = 0;
            }
        }

        if (magicToAdd > 0) {
            if (magic < maxMagic) {
                magicToAdd--;
                setMagic(magic + 1);
            } else {
                magicToAdd = 0;
            }
        } else if (magicToAdd < 0) {
            if (magic > 0) {
                magicToAdd++;
                setMagic(magic - 1);
            } else {
                magicToAdd = 0;
            }
        }

        if (isInvincible()) {
            invincible--;
        }

        chrono.reset();
    }
}

void Status::updateLife(int i) {
    lifeToAdd += i;
    if (life + lifeToAdd > maxLife) lifeToAdd = maxLife - life;
}

void Status::updateMagic(int i) {
    magicToAdd += i;
    if (magic + magicToAdd > maxMagic) magicToAdd = maxMagic - magic;
}

void Status::updateRupees(int i) {
    rupeesToAdd += i;
    if (rupees + rupeesToAdd > maxRupees) rupeesToAdd = maxRupees - rupees;
}

void Status::updateGanonOr(int i) {
    ganonOrToAdd += i;
    if (ganonOr + ganonOrToAdd > maxGanonOr) ganonOrToAdd = maxGanonOr - ganonOr;
}

void Status::updatePieceOr(int i) {
    pieceOrToAdd += i;
    if (pieceOr + pieceOrToAdd > maxPieceOr) pieceOrToAdd = maxPieceOr - pieceOr;
}

int Status::getVirtualLife() {
    return life + lifeToAdd;
}

int Status::getVirtualMagic() {
    return magic + magicToAdd;
}

int Status::getVirtualRupees() {
    return rupees + rupeesToAdd;
}

int Status::getVirtualGanonOr() {
    return ganonOr + ganonOrToAdd;
}

int Status::getVirtualPieceOr() {
    return pieceOr + pieceOrToAdd;
}

int Status::getLife() {return life;}
int Status::getMaxLife() {return maxLife;}
int Status::getMagic() {return magic;}
int Status::getMaxMagic() {return maxMagic;}
int Status::getRupees() {return rupees;}
int Status::getMaxRupees() {return maxRupees;}
int Status::getGanonOr() {return ganonOr;}
int Status::getMaxGanonOr() {return maxGanonOr;}
int Status::getPieceOr() {return pieceOr;}
int Status::getMaxPieceOr() {return maxPieceOr;}
int Status::getArrows() {return arrows;}
int Status::getMaxArrows() {return maxArrows;}
int Status::getBombs() {return bombs;}
int Status::getMaxBombs() {return maxBombs;}
bool Status::isOniLink() {return oniLink;}

void Status::setLife(int i) {
    if  (i == 0) lifeToAdd = 0;
    if (i > maxLife) i = maxLife;
    life = i;
    if (life + lifeToAdd > 0 && life <= maxLife / 3) {
        AudioManager::getInstance()->playSound(TS_DANGER);
    }
}
void Status::setMaxLife(int i) {maxLife = i;}
void Status::setMagic(int i) {if (i > maxMagic) i = maxMagic; magic = i;}
void Status::setMaxMagic(int i) {maxMagic = i;}
void Status::setRupees(int i) {if (i > maxRupees) i = maxRupees; rupees = i;}
void Status::setMaxRupees(int i) {maxRupees = i;}
void Status::setGanonOr(int i) {if (i > maxGanonOr) i = maxGanonOr; if (i < 0) i = 0; ganonOr = i;}
void Status::setMaxGanonOr(int i) {maxGanonOr = i;}
void Status::setPieceOr(int i) {if (i > maxPieceOr) i = maxPieceOr; pieceOr = i;}
void Status::setMaxPieceOr(int i) {maxPieceOr = i;}
void Status::setArrows(int i) {if (i > maxArrows) i = maxArrows; arrows = i;}
void Status::setMaxArrows(int i) {maxArrows = i;}
void Status::setBombs(int i) {if (i > maxBombs) i = maxBombs; bombs = i;}
void Status::setMaxBombs(int i) {maxBombs = i;}
void Status::setOniLink(bool b) {oniLink = b;}

void Status::setInvincible() {invincible = 10;}
bool Status::isInvincible() {return (invincible > 0);}

void Status::increaseDeaths() {
    deaths ++;
    if (deaths > 999) deaths = 999;
}

int Status::getNbDeaths() {
    return deaths;
}

int Status::getMaxWeight() {
    Inventory* inventory = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory();
    if (inventory->hasObject(GANTS_2)) return 4;
    if (inventory->hasObject(GANTS)) return 2;
    return 1;
}

void Status::updateGel(int value) {
    gel += value;
    if (gel > 5000) gel = 5000;
    maxGel = gel;
}
void Status::resetGel() {
    gel = 0;
}
int Status::getGel() {
    return gel;
}
int Status::getMaxGel() {
    return maxGel;
}

void Status::updateIvre(int value) {
    ivre += value;
    if (ivre > 50000) ivre = 50000;
    maxIvre = ivre;
}
void Status::resetIvre() {
    ivre = 0;
}
int Status::getIvre() {
    return ivre;
}
int Status::getMaxIvre() {
    return maxIvre;
}
