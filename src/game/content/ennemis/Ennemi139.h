/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI139_H__
#define __ENNEMI139_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi139 : public Ennemi
{
public:
    Ennemi139(int x, int y);
    ~Ennemi139();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

private:
    void snipe();

    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    int animDispel;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    int cooldown;
};

#endif // Ennemi139.h
