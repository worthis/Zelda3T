/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI093_H__
#define __ENNEMI093_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi093 : public Ennemi
{
public:
    Ennemi093(int x, int y);
    ~Ennemi093();

    void ennLoop();
    void draw(int offsetX, int offsetY);
    void drawEncyclopedie();

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
    void snipe();

    int step; // 0 hidden, 1 tourbillon, 2 idle, 3 shoot, 4 tourbillon

    int anim;
    int animMax;
    int vanim;
    int special;

    WImage *image;

    BoundingBox box;

    Chrono chrono;
};

#endif // Ennemi093.h
