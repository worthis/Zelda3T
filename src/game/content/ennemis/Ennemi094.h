/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI094_H__
#define __ENNEMI094_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi094 : public Ennemi
{
public:
    Ennemi094(int x, int y);
    ~Ennemi094();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

protected:
    void giveItem(int x, int y);

private:
    void moveX(int dx);

    int anim;
    int animMax;
    int vanim;

    int step;
    int cooldown;

    WImage *image;

    Chrono chrono;

    BoundingBox box;
};

#endif // Ennemi094.h
