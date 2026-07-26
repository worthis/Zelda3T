/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI099_H__
#define __ENNEMI099_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi099 : public Ennemi {
    public :
        Ennemi099(int x, int y);
        ~Ennemi099();

        void ennLoop();
        void draw(int offsetX, int offsetY);
        void drawEncyclopedie();

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        bool isToAvoid(Collision c);

    protected :

        void afterHit();

        void giveItem(int x, int y);

    private :

        void snipe();

        int step; // 0 hidden, 1 coming, 2 waiting, 3 shooting, 4 shocked, 5 going

        int anim;
        int animMax;
        int vanim;
        int special;

        WImage* image;

        BoundingBox box;

        Chrono chrono;
};

#endif  // Ennemi099.h
