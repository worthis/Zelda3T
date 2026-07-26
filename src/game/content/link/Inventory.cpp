#include "Inventory.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Inventory::Inventory(Save* save) {
    loadFromSave(save);
    inventaire = ResourceManager::getInstance()->loadImage("data/images/status/inventaire.png");
}

Inventory::~Inventory() {
    ResourceManager::getInstance()->free(inventaire);
}

void Inventory::saveData(Save* save) {
    for (int i = 0; i < NB_EQPMT; i++) {
        save->setEquipment(i, equipment[i]);
    }
    for (int i = 0; i < NB_FLACON; i++) {
        save->setFlacons(i, flacons[i]);
    }
    for (int i = 0; i < NB_TROC_GEMME; i++) {
        save->setTrocGemme(i, trocGemme[i]);
    }
    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        save->setGemmeForce(i, gemmeForce[i]);
    }
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        save->setQuartCoeur(i, quartCoeur[i]);
    }
    for (int i = 0; i < NB_COEUR; i++) {
        save->setCoeur(i, coeur[i]);
    }
    for (int i = 0; i < NB_MEDAILLONS; i++) {
        save->setMedaillons(i, medaillons[i]);
    }
    for (int i = 0; i < NB_CRISTAUX; i++) {
        save->setCristaux(i, cristaux[i]);
    }
    for (int i = 0; i < NB_TROC; i++) {
        save->setTroc(i, troc[i]);
    }
    save->setCurrentStuff(current);
}

void Inventory::loadFromSave(Save* save) {
    for (int i = 0; i < NB_EQPMT; i++) {
        equipment[i] = save->getEquipment(i);
    }
    for (int i = 0; i < NB_FLACON; i++) {
        flacons[i] = save->getFlacons(i);
    }
    for (int i = 0; i < NB_TROC_GEMME; i++) {
        trocGemme[i] = save->getTrocGemme(i);
    }
    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        gemmeForce[i] = save->getGemmeForce(i);
    }
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        quartCoeur[i] = save->getQuartCoeur(i);
    }
    for (int i = 0; i < NB_COEUR; i++) {
        coeur[i] = save->getCoeur(i);
    }
    for (int i = 0; i < NB_MEDAILLONS; i++) {
        medaillons[i] = save->getMedaillons(i);
    }
    for (int i = 0; i < NB_CRISTAUX; i++) {
        cristaux[i] = save->getCristaux(i);
    }
    for (int i = 0; i < NB_TROC; i++) {
        troc[i] = save->getTroc(i);
    }
    current = save->getCurrentStuff();
}

void Inventory::draw(Equipment e, int x, int y) {
    switch (e) {
        case ARC : WindowManager::getInstance()->draw(inventaire, 16, 68, 16, 17, x, y); break;
        case ARC_FEE : WindowManager::getInstance()->draw(inventaire, 0, 0, 16, 17, x, y); break;
        case BOMBES : WindowManager::getInstance()->draw(inventaire, 32, 0, 16, 17, x, y); break;
        case GRAPPIN : WindowManager::getInstance()->draw(inventaire, 16, 0, 16, 17, x, y); break;
        case BAGUETTE_FEU : WindowManager::getInstance()->draw(inventaire, 0, 17, 16, 17, x, y); break;
        case BAGUETTE_GLACE : WindowManager::getInstance()->draw(inventaire, 16, 17, 16, 17, x, y); break;
        case LANTERNE : WindowManager::getInstance()->draw(inventaire, 32, 17, 16, 17, x, y); break;
        case MARTEAU : WindowManager::getInstance()->draw(inventaire, 0, 34, 16, 17, x, y); break;
        case FLACON_1 : drawFlacon(x, y, flacons[0]); break;
        case FLACON_2 : drawFlacon(x, y, flacons[1]); break;
        case FLACON_3 : drawFlacon(x, y, flacons[2]); break;
        case FLACON_4 : drawFlacon(x, y, flacons[3]); break;
        case GANTS : WindowManager::getInstance()->draw(inventaire, 48, 34, 16, 17, x, y); break;
        case GANTS_2 : WindowManager::getInstance()->draw(inventaire, 32, 34, 16, 17, x, y); break;
        case PALMES : WindowManager::getInstance()->draw(inventaire, 16, 34, 16, 17, x, y); break;
        case OCARINA : WindowManager::getInstance()->draw(inventaire, 0, 68, 16, 17, x, y); break;
        case MASQUE : WindowManager::getInstance()->draw(inventaire, 16, 136, 16, 17, x, y); break;
        case BOTTES : WindowManager::getInstance()->draw(inventaire, 48, 85, 16, 17, x, y); break;
        case CANNE_A_PECHE_1 : WindowManager::getInstance()->draw(inventaire, 32, 136, 16, 17, x, y); break;
        case CANNE_A_PECHE_2 : WindowManager::getInstance()->draw(inventaire, 48, 136, 16, 17, x, y); break;
        case CANNE_A_PECHE_3 : WindowManager::getInstance()->draw(inventaire, 64, 136, 16, 17, x, y); break;
        case FLECHE_FEU : WindowManager::getInstance()->draw(inventaire, 80, 136, 16, 17, x, y); break;
        case FLECHE_GLACE : WindowManager::getInstance()->draw(inventaire, 96, 136, 16, 17, x, y); break;
        case FLECHE_LUMIERE : WindowManager::getInstance()->draw(inventaire, 112, 136, 16, 17, x, y); break;
        case TROC_GEMME_ROUGE : drawTrocGemme(x, y, 0, trocGemme[0]); break;
        case TROC_GEMME_BLEUE : drawTrocGemme(x, y, 1, trocGemme[1]); break;
        case TROC_GEMME_JAUNE : drawTrocGemme(x, y, 2, trocGemme[2]); break;
        case TROC_GEMME_VERTE : drawTrocGemme(x, y, 3, trocGemme[3]); break;
        case CHANT_1 : WindowManager::getInstance()->draw(inventaire, 0, 102, 16, 17, x, y); break;
        case CHANT_2 : WindowManager::getInstance()->draw(inventaire, 16, 102, 16, 17, x, y); break;
        case CHANT_3 : WindowManager::getInstance()->draw(inventaire, 32, 102, 16, 17, x, y); break;
        default : break;
    }
}

void Inventory::drawFlacon(int x, int y, int value) {
    WindowManager::getInstance()->draw(inventaire, (value%4) * 16, 51 + 68 * (value / 4), 16, 17, x, y);
}

void Inventory::drawTrocGemme(int x, int y, int troc, int value) {
    int tmp = value;
    if (troc == 0 && (tmp == TGR_RIEN || tmp == TGR_RIEN_2)) return;
    if (troc == 0 && tmp > TGR_RIEN_2) tmp--;
    if (troc == 0 && tmp > TGR_RIEN) tmp--;
    WindowManager::getInstance()->draw(inventaire, (troc + 4) * 16, 17 * tmp, 16, 17, x, y);
}

void Inventory::setObject(Equipment e, int value) {
    equipment[e] = value;
}

bool Inventory::hasObject(Equipment e) {
    return (equipment[e] == 1);
}

bool Inventory::hasObject() {
    for (int i = 0; i < NB_EQPMT; i++) {
        if (i != CARTE && i != ENCYCLOPEDIE && equipment[i] && i != SAC_TROC) return true;
    }
    return false;
}

Equipment Inventory::getCurrent() {
    if (current == ARC && hasObject(ARC_FEE)) {
        current = ARC_FEE;
    }
    if (current == CANNE_A_PECHE_1 && hasObject(CANNE_A_PECHE_2)) {
        current = CANNE_A_PECHE_2;
    }
    if (current == CANNE_A_PECHE_2 && hasObject(CANNE_A_PECHE_3)) {
        current = CANNE_A_PECHE_3;
    }
    if (current == TROC_GEMME_ROUGE && hasObject(FLECHE_FEU)) {
        current = FLECHE_FEU;
    }
    if (current == TROC_GEMME_BLEUE && hasObject(FLECHE_GLACE)) {
        current = FLECHE_GLACE;
    }
    if (current == TROC_GEMME_JAUNE && hasObject(FLECHE_LUMIERE)) {
        current = FLECHE_LUMIERE;
    }
    if (current == TROC_GEMME_VERTE && hasObject(FLACON_4)) {
        current = FLACON_4;
    }
    return current;
}

void Inventory::setCurrent(Equipment e) {
    current = e;
    if (current == ARC && hasObject(ARC_FEE)) {
        current = ARC_FEE;
    }
}

bool Inventory::hasQuartCoeur(int i) {
    return (quartCoeur[i] == 1);
}

void Inventory::setQuartCoeur(int i, int value) {
    quartCoeur[i] = value;
}

int Inventory::nbQuartCoeur() {
    return totalQuartCoeur() % 4;
}

int Inventory::totalQuartCoeur() {
    int total = 0;
    for (int i = 0; i < NB_QUART_COEUR; i++) {
        if (quartCoeur[i]) total++;
    }
    return total;
}

bool Inventory::hasCoeur(int i) {
    return (coeur[i] == 1);
}

void Inventory::setCoeur(int i, int value) {
    coeur[i] = value;
}

void Inventory::setMedaillon(int i, int value) {
    medaillons[i] = value;
}

bool Inventory::hasMedaillon(int i) {
    return (medaillons[i] == 1);
}

int Inventory::nbMedaillons() {
    int total = 0;
    for (int i = 0; i < NB_MEDAILLONS; i++) {
        if (medaillons[i]) total++;
    }
    return total;
}

void Inventory::setCristal(int i, int value) {
    cristaux[i] = value;
}

bool Inventory::hasCristal(int i) {
    return (cristaux[i] == 1);
}

int Inventory::nbCristaux() {
    int total = 0;
    for (int i = 0; i < NB_CRISTAUX; i++) {
        if (cristaux[i]) total++;
    }
    return total;
}

int Inventory::getFlacon(int i) {
    return flacons[i];
}

void Inventory::setFlacon(int i, int value) {
    flacons[i] = value;
}

int Inventory::getCurrentFlacon() {
    switch (current) {
        case FLACON_1 : return flacons[0];
        case FLACON_2 : return flacons[1];
        case FLACON_3 : return flacons[2];
        case FLACON_4 : return flacons[3];
        default : return 0;
    }
}

void Inventory::setCurrentFlacon(int value) {
    switch (current) {
        case FLACON_1 : flacons[0] = value; break;
        case FLACON_2 : flacons[1] = value; break;
        case FLACON_3 : flacons[2] = value; break;
        case FLACON_4 : flacons[3] = value; break;
        default : break;
    }
}

int Inventory::getTrocGemme(int i) {
    return trocGemme[i];
}

void Inventory::setTrocGemme(int i, int value) {
    trocGemme[i] = value;
}

void Inventory::setGemmeForce(int i, int value) {
    gemmeForce[i] = value;
}

bool Inventory::hasGemmeForce(int i) {
    return gemmeForce[i];
}

int Inventory::nbGemmeForce() {
    int total = 0;
    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        if (gemmeForce[i] == 1) total++; // == 2 if already used
    }
    return total;
}

int Inventory::totalGemmeForce() {
    int total = 0;
    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        if (gemmeForce[i]) total++;
    }
    return total;
}

void Inventory::removeGemme(int nb) {
    int total = nb;
    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        if (!total) return;
        if (gemmeForce[i] == 1) {
            gemmeForce[i] = 2;
            total--;
        }
    }
}

int Inventory::getTroc(int i) {
    return troc[i];
}

void Inventory::setTroc(int i, int value) {
    troc[i] = value;
}

void Inventory::addTroc(int i, int value) {
    if (troc[i] == -1) {
        troc[i] = value;
    } else {
        troc[i]+=value;
    }
    if (troc[i] > 99) troc[i] = 99;
}

void Inventory::removeTroc(int i, int val) {
    troc[i] -= val;
}
