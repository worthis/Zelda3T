/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJBOULEEXPO_H__
#define __PROJBOULEEXPO_H__

#include "../types/Projectile.h"

class ProjBouleExpo : public Projectile
{
public:
    ProjBouleExpo(int x, int y, double dx, double dy, BoundingBox *safeBox = 0);
    ~ProjBouleExpo();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    int getX();
    int getY();
    int getDown();

    void renvoie(Direction dir);

private:
    int speed;
    double dx;
    double dy;
    int force;
    int parcouru;
    double histX[16];
    double histY[16];
    double longX;
    double longY;
    bool retour;
    BoundingBox *safeBox;
};

#endif // ProjBouleExpo.h
