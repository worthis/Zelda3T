/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI116_H__
#define __ENNEMI116_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi116 : public Ennemi {
    public :
        Ennemi116(int x, int y);
        ~Ennemi116();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        bool isToAvoid(Collision c);

    private :

        void snipe();

        int step; // -1 not started, 0 hidden, 1 coming, 2 closing, 3 waiting, 4 shooting

        int anim;
        int animMax;
        int vanim;
        int special;

        WImage* image;

        BoundingBox box;

        Chrono chrono;
};

#endif  // Ennemi116.h
