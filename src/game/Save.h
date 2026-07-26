/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SAVE_H__
#define __SAVE_H__

#include "../engine/common/Common.h"

#include "content/CommonGame.h"

class Save
{
public:
    Save(int i);
    ~Save();

    void save(bool endGame = false);
    void erase();

    bool isLoaded();

    int getCompletion();

    int getMap();
    int getX();
    int getY();
    Direction getDirection();
    int getTunique();
    int getEpee();
    int getBouclier();
    int getLife();
    int getMaxLife();
    int getMagic();
    int getMaxMagic();
    int getRupees();
    int getMaxRupees();
    int getGanonOr();
    int getMaxGanonOr();
    int getPieceOr();
    int getMaxPieceOr();
    int getLifeToAdd();
    int getMagicToAdd();
    int getRupeesToAdd();
    int getGanonOrToAdd();
    int getPieceOrToAdd();
    int getDeaths();
    int getEquipment(int i);
    int getFlacons(int i);
    int getTrocGemme(int i);
    int getGemmeForce(int i);
    int getQuartCoeur(int i);
    int getCoeur(int i);
    int getMedaillons(int i);
    int getCristaux(int i);
    int getTroc(int i);
    int getPoissons(int i);
    int getArrows();
    int getMaxArrows();
    int getBombs();
    int getMaxBombs();
    bool isOniLink();
    Equipment getCurrentStuff();
    Avancement getAvancement();
    int getTime();
    int getCoffre(int i, int j);
    int getRooms(int d, int i, int j);
    int getMonsters(int i);

    void setMap(int i);
    void setX(int i);
    void setY(int i);
    void setDirection(Direction dir);
    void setTunique(int i);
    void setEpee(int i);
    void setBouclier(int i);
    void setLife(int i);
    void setMaxLife(int i);
    void setMagic(int i);
    void setMaxMagic(int i);
    void setRupees(int i);
    void setMaxRupees(int i);
    void setGanonOr(int i);
    void setMaxGanonOr(int i);
    void setPieceOr(int i);
    void setMaxPieceOr(int i);
    void setLifeToAdd(int i);
    void setMagicToAdd(int i);
    void setRupeesToAdd(int i);
    void setGanonOrToAdd(int i);
    void setPieceOrToAdd(int i);
    void setDeaths(int i);
    void setEquipment(int i, int value);
    void setFlacons(int i, int value);
    void setTrocGemme(int i, int value);
    void setGemmeForce(int i, int value);
    void setQuartCoeur(int i, int value);
    void setCoeur(int i, int value);
    void setMedaillons(int i, int value);
    void setCristaux(int i, int value);
    void setTroc(int i, int value);
    void setPoissons(int i, int value);
    void setArrows(int i);
    void setMaxArrows(int i);
    void setBombs(int i);
    void setMaxBombs(int i);
    void setOniLink(bool b);
    void setCurrentStuff(Equipment current);
    void setAvancement(Avancement avancement);
    void setTime(int t);
    void setCoffre(int i, int j, int val);
    void setRooms(int d, int i, int j, int val);
    void setMonsters(int i, int val);

private:
    void init();
    void load();

    int id;
    bool loaded;

    int map;
    int x;
    int y;
    Direction direction;
    int tunique;
    int epee;
    int bouclier;

    int life;
    int maxLife;
    int magic;
    int maxMagic;
    int rupees;
    int maxRupees;
    int ganonOr;
    int maxGanonOr;
    int pieceOr;
    int maxPieceOr;
    int arrows;
    int maxArrows;
    int bombs;
    int maxBombs;
    bool oniLink;
    Equipment currentStuff;

    int lifeToAdd;
    int magicToAdd;
    int rupeesToAdd;
    int ganonOrToAdd;
    int pieceOrToAdd;

    int deaths;

    Avancement avancement;

    int time;

    int equipment[NB_EQPMT];
    int flacons[NB_FLACON];
    int trocGemme[NB_TROC_GEMME];
    int gemmeForce[NB_GEMME_FORCE];
    int quartCoeur[NB_QUART_COEUR];
    int coeur[NB_COEUR];
    int medaillons[NB_MEDAILLONS];
    int cristaux[NB_CRISTAUX];
    int troc[NB_TROC];
    int poissons[NB_POISSONS];
    int coffres[NB_COFFRES][COFFRES_MAX_SIZE];
    int rooms[NB_DONJON][MAX_ROOMS_X][MAX_ROOMS_Y];
    int monsters[NB_MONSTERS];
};

#endif // Save.h
