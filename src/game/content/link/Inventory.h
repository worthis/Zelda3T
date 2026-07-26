/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/resources/WImage.h"

#include "../../Save.h"

class Inventory
{
public:
    Inventory(Save *save);
    ~Inventory();

    void saveData(Save *save);

    void draw(Equipment e, int x, int y);

    void setObject(Equipment e, int value = 1);

    bool hasObject(Equipment e);

    bool hasObject();

    Equipment getCurrent();

    void setCurrent(Equipment e);

    bool hasQuartCoeur(int i);

    void setQuartCoeur(int i, int value = 1);

    int nbQuartCoeur();

    int totalQuartCoeur();

    bool hasCoeur(int i);

    void setCoeur(int i, int value = 1);

    void setMedaillon(int i, int value = 1);

    bool hasMedaillon(int i);

    int nbMedaillons();

    void setCristal(int i, int value = 1);

    bool hasCristal(int i);

    int nbCristaux();

    int getFlacon(int i);

    void setFlacon(int i, int value);

    int getCurrentFlacon();

    void setCurrentFlacon(int value);

    int getTrocGemme(int i);

    void setTrocGemme(int i, int value);

    void setGemmeForce(int i, int value = 1);

    bool hasGemmeForce(int i);

    int nbGemmeForce();

    int totalGemmeForce();

    void removeGemme(int nb);

    int getTroc(int i);

    void setTroc(int i, int value);

    void addTroc(int i, int value = 1);

    void removeTroc(int i, int val);

private:
    void loadFromSave(Save *save);

    void drawFlacon(int x, int y, int value);

    void drawTrocGemme(int x, int y, int troc, int value);

    int equipment[NB_EQPMT];

    Equipment current;

    WImage *inventaire;

    int quartCoeur[NB_QUART_COEUR];

    int coeur[NB_COEUR];

    int medaillons[NB_MEDAILLONS];

    int cristaux[NB_CRISTAUX];

    int flacons[NB_FLACON];

    int trocGemme[NB_TROC_GEMME];

    int gemmeForce[NB_GEMME_FORCE];

    int troc[NB_TROC];
};

#endif // Inventory.h
