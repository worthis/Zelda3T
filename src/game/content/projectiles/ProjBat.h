/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJBAT_H__
#define __PROJBAT_H__

#include "../types/Projectile.h"

class ProjBat : public Projectile
{
public:
    ProjBat(int x, int y, double dx, double dy);
    ~ProjBat();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    int getX();
    int getY();
    int getDown();

private:
    int speed;
    double dx;
    double dy;
    int force;
    double longX;
    double longY;
};

#endif // ProjBat.h
