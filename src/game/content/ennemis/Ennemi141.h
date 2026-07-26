/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI141_H__
#define __ENNEMI141_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi141 : public Ennemi {
    public :
        Ennemi141(int x, int y);
        ~Ennemi141();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    protected :

        void afterHit();

        bool canDie(TypeEffect effect);

    private :

        void snipe();

        int anim;
        int animMax;
        int vanim;

        int step; // 0 coming, 1 here, 2 wait, 3 dying, 4 very dying

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi141.h
