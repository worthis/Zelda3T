/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __STATUS_H__
#define __STATUS_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/util/time/Chrono.h"

#include "../../Save.h"

class Status
{
public:
    Status(Save *save);
    ~Status();

    void saveData(Save *save);

    void loop();

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
    int getArrows();
    int getMaxArrows();
    int getBombs();
    int getMaxBombs();
    bool isOniLink();

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
    void setArrows(int i);
    void setMaxArrows(int i);
    void setBombs(int i);
    void setMaxBombs(int i);
    void setOniLink(bool b);

    void updateLife(int i);
    void updateRupees(int i);
    void updateGanonOr(int i);
    void updatePieceOr(int i);
    void updateMagic(int i);

    int getVirtualLife();
    int getVirtualRupees();
    int getVirtualGanonOr();
    int getVirtualPieceOr();
    int getVirtualMagic();

    void setInvincible();
    bool isInvincible();

    void increaseDeaths();
    int getNbDeaths();

    int getMaxWeight();

    void updateGel(int value);
    void resetGel();
    int getGel();
    int getMaxGel();

    void updateIvre(int value);
    void resetIvre();
    int getIvre();
    int getMaxIvre();

private:
    void loadFromSave(Save *save);

    Chrono chrono;

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
    bool oniLink; // transform�

    int lifeToAdd;
    int magicToAdd;
    int rupeesToAdd;
    int ganonOrToAdd;
    int pieceOrToAdd;

    int invincible;

    int deaths;

    int gel;
    int maxGel;

    int ivre;
    int maxIvre;
};

#endif // Status.h
