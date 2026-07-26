/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI097_H__
#define __ENNEMI097_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi097 : public Ennemi
{
public:
    Ennemi097(int x, int y);
    ~Ennemi097();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

protected:
    void afterFall();
    void giveItem(int x, int y);

private:
    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    int step;
    int elan;
    int colere;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi097.h
