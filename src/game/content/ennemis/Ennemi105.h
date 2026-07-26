/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI105_H__
#define __ENNEMI105_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi105 : public Ennemi
{
public:
    Ennemi105(int x, int y);
    ~Ennemi105();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);
    bool isToAvoid(Collision c);

protected:
    void giveItem(int x, int y);

private:
    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    int step;
    int elan;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi105.h
