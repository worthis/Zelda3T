/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI128_H__
#define __ENNEMI128_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi128 : public Ennemi
{
public:
    Ennemi128(int x, int y);
    ~Ennemi128();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

protected:
    void giveItem(int x, int y);

private:
    void snipe(int origx, int origy);

    int anim;
    int animMax;
    int vanim;

    int step; // 0 normal, 1 souffle, 2 glace

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi128.h
