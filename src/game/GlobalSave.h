/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GLOBALSAVE_H__
#define __GLOBALSAVE_H__

#include "Save.h"

class GlobalSave
{
public:
    static GlobalSave *getInstance();

    void save();
    void erase();

    void update(Save *save, bool endGame);

    bool isFullROTH();
    bool isUltimeROTH();
    bool isRushROTH();
    bool isFullOLB();
    bool isUltimeOLB();
    bool isRushOLB();
    bool isFull3T();
    bool isUltime3T();
    bool isRush3T();
    int getBestTime();

    bool is9Ranks();

private:
    GlobalSave();
    ~GlobalSave();
    static GlobalSave instance;

    void init();
    void load();

    bool fullROTH;
    bool rushROTH;
    bool ultimeROTH;
    bool fullOLB;
    bool rushOLB;
    bool ultimeOLB;
    bool full3T;
    bool rush3T;
    bool ultime3T;
    int bestTime;
};

#endif // GlobalSave.h
