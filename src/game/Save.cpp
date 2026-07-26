#include "Save.h"

#include "GlobalSave.h"

Save::Save(int i) : id (i), loaded(false) {
    init();
    load();
}

Save::~Save() {
}

void Save::init() {
    // set default values
    map = 79;
    x = 16 * 7;
    y = 16 * 3 + 8;
    direction = S;
    tunique = 1;
    epee = 0;
    bouclier = 0;
    life = 6;
    maxLife = 6;
    magic = 0;
    maxMagic = 0;//32;
    rupees = 0;
    maxRupees = 0;
    ganonOr = 0;
    maxGanonOr = 0;
    pieceOr = 0;
    maxPieceOr = 0;
    arrows = 0;
    maxArrows = 30;
    bombs = 0;
    maxBombs = 10;
    oniLink = false;
    lifeToAdd = 0;
    magicToAdd = 0;
    rupeesToAdd = 0;
    ganonOrToAdd = 0;
    pieceOrToAdd = 0;
    deaths = 0;
    avancement = AV_START;
    time = 0;
    currentStuff = (Equipment)0;

    for (int i = 0; i < NB_EQPMT; i++) {
        equipment[i] = 0;
    }

    for (int i = 0; i < NB_FLACON; i++) {
        flacons[i] = 0;
    }

    for (int i = 0; i < NB_TROC_GEMME; i++) {
        trocGemme[i] = 0;
    }

    for (int i = 0; i < NB_GEMME_FORCE; i++) {
        gemmeForce[i] = 0;
    }

    for (int i = 0; i < NB_QUART_COEUR; i++) {
        quartCoeur[i] = 0;
    }

    for (int i = 0; i < NB_COEUR; i++) {
        coeur[i] = 0;
    }

    for (int i = 0; i < NB_MEDAILLONS; i++) {
        medaillons[i] = 0;
    }

    for (int i = 0; i < NB_CRISTAUX; i++) {
        cristaux[i] = 0;
    }

    for (int i = 0; i < NB_TROC; i++) {
        troc[i] = -1;
    }

    for (int i = 0; i < NB_POISSONS; i++) {
        poissons[i] = 0;
    }

    for (int j = 0; j < COFFRES_MAX_SIZE; j++) {
        for (int i = 0; i < NB_COFFRES; i++) {
            coffres[i][j] = 0;
        }
    }

    for (int j = 0; j < MAX_ROOMS_Y; j++) {
        for (int i = 0; i < MAX_ROOMS_X; i++) {
            for (int d = 0; d < NB_DONJON; d++) {
                rooms[d][i][j] = 0;
            }
        }
    }

    for (int i = 0; i < NB_MONSTERS; i++) {
        monsters[i] = 0;
    }
}

void Save::load() {
    ostringstream im;
    im << id;
    ifstream f(("saves/3t" + im.str() + ".dat").c_str(), ios::in | ios::binary);
    if(!f.is_open()) {
        return;
    }
    f.read((char *)&map,sizeof(int));
    f.read((char *)&x,sizeof(int));
    f.read((char *)&y,sizeof(int));
    f.read((char *)&direction,sizeof(int));
    f.read((char *)&tunique,sizeof(int));
    f.read((char *)&epee,sizeof(int));
    f.read((char *)&bouclier,sizeof(int));
    f.read((char *)&life,sizeof(int));
    f.read((char *)&maxLife,sizeof(int));
    f.read((char *)&magic,sizeof(int));
    f.read((char *)&maxMagic,sizeof(int));
    f.read((char *)&rupees,sizeof(int));
    f.read((char *)&maxRupees,sizeof(int));
    f.read((char *)&ganonOr,sizeof(int));
    f.read((char *)&maxGanonOr,sizeof(int));
    f.read((char *)&pieceOr,sizeof(int));
    f.read((char *)&maxPieceOr,sizeof(int));
    f.read((char *)&arrows,sizeof(int));
    f.read((char *)&maxArrows,sizeof(int));
    f.read((char *)&bombs,sizeof(int));
    f.read((char *)&maxBombs,sizeof(int));
    f.read((char *)&oniLink,sizeof(bool));
    f.read((char *)&currentStuff,sizeof(Equipment));
    f.read((char *)&lifeToAdd,sizeof(int));
    f.read((char *)&magicToAdd,sizeof(int));
    f.read((char *)&rupeesToAdd,sizeof(int));
    f.read((char *)&ganonOrToAdd,sizeof(int));
    f.read((char *)&pieceOrToAdd,sizeof(int));
    f.read((char *)&deaths,sizeof(int));
    f.read((char *)&avancement,sizeof(int));
    f.read((char *)&time,sizeof(int));
    for (int i = 0; i < NB_EQPMT; i++) f.read((char *)&equipment[i],sizeof(int));
    for (int i = 0; i < NB_FLACON; i++) f.read((char *)&flacons[i],sizeof(int));
    for (int i = 0; i < NB_TROC_GEMME; i++) f.read((char *)&trocGemme[i],sizeof(int));
    for (int i = 0; i < NB_GEMME_FORCE; i++) f.read((char *)&gemmeForce[i],sizeof(int));
    for (int i = 0; i < NB_QUART_COEUR; i++) f.read((char *)&quartCoeur[i],sizeof(int));
    for (int i = 0; i < NB_COEUR; i++) f.read((char *)&coeur[i],sizeof(int));
    for (int i = 0; i < NB_MEDAILLONS; i++) f.read((char *)&medaillons[i],sizeof(int));
    for (int i = 0; i < NB_CRISTAUX; i++) f.read((char *)&cristaux[i],sizeof(int));
    for (int i = 0; i < NB_TROC; i++) f.read((char *)&troc[i],sizeof(int));
    for (int i = 0; i < NB_POISSONS; i++) f.read((char *)&poissons[i],sizeof(int));
    for (int j = 0; j < COFFRES_MAX_SIZE; j++) for (int i = 0; i < NB_COFFRES; i++) f.read((char *)&coffres[i][j],sizeof(int));
    for (int j = 0; j < MAX_ROOMS_Y; j++) for (int i = 0; i < MAX_ROOMS_X; i++) for (int d = 0; d < NB_DONJON; d++) f.read((char *)&rooms[d][i][j],sizeof(int));
    for (int i = 0; i < NB_MONSTERS; i++) f.read((char *)&monsters[i],sizeof(int));
    f.close();
    loaded = true;
}

void Save::save(bool endGame) {
    if (endGame) {
        life = maxLife;
        map = 79;
        x = 16 * 7;
        y = 16 * 3 + 8;
        direction = S;
    }
    ostringstream im;
    im << id;
    ofstream f(("saves/3t" + im.str() + ".dat").c_str(), ios::out | ios::binary);
    f.write((char *)&map,sizeof(int));
    f.write((char *)&x,sizeof(int));
    f.write((char *)&y,sizeof(int));
    f.write((char *)&direction,sizeof(int));
    f.write((char *)&tunique,sizeof(int));
    f.write((char *)&epee,sizeof(int));
    f.write((char *)&bouclier,sizeof(int));
    f.write((char *)&life,sizeof(int));
    f.write((char *)&maxLife,sizeof(int));
    f.write((char *)&magic,sizeof(int));
    f.write((char *)&maxMagic,sizeof(int));
    f.write((char *)&rupees,sizeof(int));
    f.write((char *)&maxRupees,sizeof(int));
    f.write((char *)&ganonOr,sizeof(int));
    f.write((char *)&maxGanonOr,sizeof(int));
    f.write((char *)&pieceOr,sizeof(int));
    f.write((char *)&maxPieceOr,sizeof(int));
    f.write((char *)&arrows,sizeof(int));
    f.write((char *)&maxArrows,sizeof(int));
    f.write((char *)&bombs,sizeof(int));
    f.write((char *)&maxBombs,sizeof(int));
    f.write((char *)&oniLink,sizeof(bool));
    f.write((char *)&currentStuff,sizeof(Equipment));
    f.write((char *)&lifeToAdd,sizeof(int));
    f.write((char *)&magicToAdd,sizeof(int));
    f.write((char *)&rupeesToAdd,sizeof(int));
    f.write((char *)&ganonOrToAdd,sizeof(int));
    f.write((char *)&pieceOrToAdd,sizeof(int));
    f.write((char *)&deaths,sizeof(int));
    f.write((char *)&avancement,sizeof(int));
    f.write((char *)&time,sizeof(int));
    for (int i = 0; i < NB_EQPMT; i++) f.write((char *)&equipment[i],sizeof(int));
    for (int i = 0; i < NB_FLACON; i++) f.write((char *)&flacons[i],sizeof(int));
    for (int i = 0; i < NB_TROC_GEMME; i++) f.write((char *)&trocGemme[i],sizeof(int));
    for (int i = 0; i < NB_GEMME_FORCE; i++) f.write((char *)&gemmeForce[i],sizeof(int));
    for (int i = 0; i < NB_QUART_COEUR; i++) f.write((char *)&quartCoeur[i],sizeof(int));
    for (int i = 0; i < NB_COEUR; i++) f.write((char *)&coeur[i],sizeof(int));
    for (int i = 0; i < NB_MEDAILLONS; i++) f.write((char *)&medaillons[i],sizeof(int));
    for (int i = 0; i < NB_CRISTAUX; i++) f.write((char *)&cristaux[i],sizeof(int));
    for (int i = 0; i < NB_TROC; i++) f.write((char *)&troc[i],sizeof(int));
    for (int i = 0; i < NB_POISSONS; i++) f.write((char *)&poissons[i],sizeof(int));
    for (int j = 0; j < COFFRES_MAX_SIZE; j++) for (int i = 0; i < NB_COFFRES; i++) f.write((char *)&coffres[i][j],sizeof(int));
    for (int j = 0; j < MAX_ROOMS_Y; j++) for (int i = 0; i < MAX_ROOMS_X; i++) for (int d = 0; d < NB_DONJON; d++) f.write((char *)&rooms[d][i][j],sizeof(int));
    for (int i = 0; i < NB_MONSTERS; i++) f.write((char *)&monsters[i],sizeof(int));
    f.close();
    GlobalSave::getInstance()->update(this, endGame);
    loaded = true;
}

void Save::erase() {
    ostringstream im;
    im << id;
    remove(("saves/3t" + im.str() + ".dat").c_str());
    init();
    loaded = false;
}

bool Save::isLoaded() {return loaded;}

int Save::getMap() {return map;}
int Save::getX() {return x;}
int Save::getY() {return y;}
Direction Save::getDirection() {return direction;}
int Save::getTunique() {return tunique;}
int Save::getEpee() {return epee;}
int Save::getBouclier() {return bouclier;}
int Save::getLife() {return life;}
int Save::getMaxLife() {return maxLife;}
int Save::getMagic() {return magic;}
int Save::getMaxMagic() {return maxMagic;}
int Save::getRupees() {return rupees;}
int Save::getMaxRupees() {return maxRupees;}
int Save::getGanonOr() {return ganonOr;}
int Save::getMaxGanonOr() {return maxGanonOr;}
int Save::getPieceOr() {return pieceOr;}
int Save::getMaxPieceOr() {return maxPieceOr;}
int Save::getArrows() {return arrows;}
int Save::getMaxArrows() {return maxArrows;}
int Save::getBombs() {return bombs;}
int Save::getMaxBombs() {return maxBombs;}
bool Save::isOniLink() {return oniLink;}
Equipment Save::getCurrentStuff() {return currentStuff;}
int Save::getLifeToAdd() {return lifeToAdd;}
int Save::getMagicToAdd() {return magicToAdd;}
int Save::getRupeesToAdd() {return rupeesToAdd;}
int Save::getGanonOrToAdd() {return ganonOrToAdd;}
int Save::getPieceOrToAdd() {return pieceOrToAdd;}
int Save::getDeaths() {return deaths;}
Avancement Save::getAvancement() {return avancement;}
int Save::getTime() {return time;}
int Save::getEquipment(int i) {return equipment[i];}
int Save::getFlacons(int i) {return flacons[i];}
int Save::getTrocGemme(int i) {return trocGemme[i];}
int Save::getGemmeForce(int i) {return gemmeForce[i];}
int Save::getQuartCoeur(int i) {return quartCoeur[i];}
int Save::getCoeur(int i) {return coeur[i];}
int Save::getMedaillons(int i) {return medaillons[i];}
int Save::getCristaux(int i) {return cristaux[i];}
int Save::getTroc(int i) {return troc[i];}
int Save::getPoissons(int i) {return poissons[i];}
int Save::getCoffre(int i, int j) {return coffres[i][j];}
int Save::getRooms(int d, int i, int j) {return rooms[d][i][j];}
int Save::getMonsters(int i) {return monsters[i];}

void Save::setMap(int i) {map = i;}
void Save::setX(int i) {x = i;}
void Save::setY(int i) {y = i;}
void Save::setDirection(Direction dir) {direction = dir;}
void Save::setTunique(int i) {tunique = i;}
void Save::setEpee(int i) {epee = i;}
void Save::setBouclier(int i) {bouclier = i;}
void Save::setLife(int i) {life = i;}
void Save::setMaxLife(int i) {maxLife = i;}
void Save::setMagic(int i) {magic = i;}
void Save::setMaxMagic(int i) {maxMagic = i;}
void Save::setRupees(int i) {rupees = i;}
void Save::setMaxRupees(int i) {maxRupees = i;}
void Save::setGanonOr(int i) {ganonOr = i;}
void Save::setMaxGanonOr(int i) {maxGanonOr = i;}
void Save::setPieceOr(int i) {pieceOr = i;}
void Save::setMaxPieceOr(int i) {maxPieceOr = i;}
void Save::setArrows(int i) {arrows = i;}
void Save::setMaxArrows(int i) {maxArrows = i;}
void Save::setBombs(int i) {bombs = i;}
void Save::setMaxBombs(int i) {maxBombs = i;}
void Save::setOniLink(bool b) {oniLink = b;}
void Save::setCurrentStuff(Equipment current) {currentStuff = current;}
void Save::setLifeToAdd(int i) {lifeToAdd = i;}
void Save::setMagicToAdd(int i) {magicToAdd = i;}
void Save::setRupeesToAdd(int i) {rupeesToAdd = i;}
void Save::setGanonOrToAdd(int i) {ganonOrToAdd = i;}
void Save::setPieceOrToAdd(int i) {pieceOrToAdd = i;}
void Save::setDeaths(int i) {deaths = i;}
void Save::setAvancement(Avancement av) {avancement = av;}
void Save::setTime(int i) {time = i;}
void Save::setEquipment(int i, int value) {equipment[i] = value;}
void Save::setFlacons(int i, int value) {flacons[i] = value;}
void Save::setTrocGemme(int i, int value) {trocGemme[i] = value;}
void Save::setGemmeForce(int i, int value) {gemmeForce[i] = value;}
void Save::setQuartCoeur(int i, int value) {quartCoeur[i] = value;}
void Save::setCoeur(int i, int value) {coeur[i] = value;}
void Save::setMedaillons(int i, int value) {medaillons[i] = value;}
void Save::setCristaux(int i, int value) {cristaux[i] = value;}
void Save::setTroc(int i, int value) {troc[i] = value;}
void Save::setPoissons(int i, int value) {poissons[i] = value;}
void Save::setCoffre(int i, int j, int value) {coffres[i][j] = value;}
void Save::setRooms(int d, int i, int j, int value) {rooms[d][i][j] = value;}
void Save::setMonsters(int i, int value) {monsters[i] = value;}

int Save::getCompletion() {
    int tmp = 0;

    for (int i = 0; i < NB_QUART_COEUR; i++) if (quartCoeur[i] != 0) tmp++;// 16
    for (int i = 0; i < NB_GEMME_FORCE; i++) if (gemmeForce[i] != 0) tmp++;// 200 -> 216
    for (int i = 0; i < NB_EQPMT; i++) if (equipment[i] != 0) tmp++;// 47 -> 263
    tmp += bouclier;// 4 -> 267
    tmp += tunique - 1;// 3 -> 270
    tmp += epee - 1;// 4 -> 274
    if (maxMagic > 32) tmp++; // 1 -> 275
    for (int i = 0; i < NB_CRISTAUX; i++) if (cristaux[i] != 0) tmp++; // 7 -> 282
    for (int i = 0; i < NB_MEDAILLONS; i++) if (medaillons[i] != 0) tmp++; // 3 -> 285
    for (int j = 1; j < 16; j++) for (int i = 0; i < 3; i++) if (coffres[j][i] != 0) tmp++;// 45 -> 330
    for (int i = 0; i < NB_MONSTERS; i++) if (monsters[i] != 0) tmp++;// 100 -> 430
    tmp += maxRupees == 999 ? 4 : maxRupees == 500 ? 3 : maxRupees == 200 ? 2 : maxRupees == 99 ? 1 : 0;
    tmp += maxGanonOr == 999 ? 4 : maxGanonOr == 500 ? 3 : maxGanonOr == 200 ? 2 : maxGanonOr == 99 ? 1 : 0;
    tmp += maxPieceOr == 999 ? 4 : maxPieceOr == 500 ? 3 : maxPieceOr == 200 ? 2 : maxPieceOr == 99 ? 1 : 0; // 12 -> 442
    tmp += (maxArrows - 30) / 5; // 8 -> 450
    tmp += (maxBombs - 10) / 2; // 10 -> 460
    for (int i = 0; i < NB_TROC; i++) if (troc[i] > -1) tmp++; // 16 -> 476
    for (int i = 0; i < NB_TROC_GEMME; i++) tmp += trocGemme[i]; // 29 -> 505
    if (trocGemme[0] >= TGR_RIEN) tmp--;
    if (trocGemme[0] >= TGR_RIEN_2) tmp--;
    for (int i = 0; i < NB_POISSONS; i++) if (poissons[i] != 0) tmp++;// 30 -> 535

    return ((double)((double)tmp * 100)) / 535;
}

