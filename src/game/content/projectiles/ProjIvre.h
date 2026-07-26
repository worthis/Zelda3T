/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJIVRE_H__
#define __PROJIVRE_H__

#include "../types/Projectile.h"

class ProjIvre : public Projectile
{
public:
    ProjIvre(int x, int y, double dx, double dy);
    ~ProjIvre();

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
    double longX;
    double longY;
};

#endif // ProjIvre.h
