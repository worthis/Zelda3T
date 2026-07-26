/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJSOUFFLE_H__
#define __PROJSOUFFLE_H__

#include "../types/Projectile.h"

class ProjSouffle : public Projectile
{
public:
    ProjSouffle(int x, int y);
    ~ProjSouffle();

    void projLoop();
    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

private:
    int dy;
};

#endif // ProjSouffle.h
