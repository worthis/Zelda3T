/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI108_H__
#define __ENNEMI108_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi108 : public Ennemi
{
public:
    Ennemi108(int x, int y);
    ~Ennemi108();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool isToAvoid(Collision c);

private:
    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    int cooldown;
};

#endif // Ennemi108.h
