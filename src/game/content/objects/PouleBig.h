/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __POULEBIG_H__
#define __POULEBIG_H__

#include "../types/Portable.h"

#include "../../../engine/util/time/Chrono.h"

class PouleBig : public Portable
{
public:
    PouleBig(int x, int y);
    ~PouleBig();

    void portLoop();
    void draw(int offsetX, int offsetY);

    void impact();

    void onLift();

    void stopBeforeUp();

    bool isCollision(Collision c);

    BoundingBox *getBoundingBox();

    BoundingBox *getSecondBoundingBox();

    void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

    void enerve();

private:
    void snipe();

    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    Chrono chrono;

    int stop;
    int invul;
    int tolerance;

    int step;
    int special;

    BoundingBox box2;
};

#endif // PouleBig.h
