/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI120_H__
#define __ENNEMI120_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi120 : public Ennemi {
    public :
        Ennemi120(int x, int y);
        ~Ennemi120();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    protected :

        void giveItem(int x, int y);

    private :

        void snipe();

        int anim;
        int animMax;
        int vanim;

        int step; // 0 normal, 1 rabbit, 2 thunder

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi120.h
