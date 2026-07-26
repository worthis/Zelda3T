/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI135_H__
#define __ENNEMI135_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi135 : public Ennemi
{
public:
    Ennemi135(int x, int y);
    ~Ennemi135();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

private:
    int anim;
    int animMax;
    int vanim;

    int step;
    int beforeRegen;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi135.h
