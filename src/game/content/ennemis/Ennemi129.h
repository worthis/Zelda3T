/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI129_H__
#define __ENNEMI129_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi129 : public Ennemi
{
public:
    Ennemi129(int x, int y);
    ~Ennemi129();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    void reset();

private:
    int anim;
    int animMax;
    int vanim;

    bool actif;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi129.h
