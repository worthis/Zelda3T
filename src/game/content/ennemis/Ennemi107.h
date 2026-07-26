/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI107_H__
#define __ENNEMI107_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi107 : public Ennemi {
    public :
        Ennemi107(int x, int y);
        ~Ennemi107();

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

        int step; // 0 hidden, 1 coming, 2 shooting, 3 shocked, 4 going

        int anim;
        int animMax;
        int vanim;
        int special;
        int nbShots;

        WImage* image;

        BoundingBox box;

        Chrono chrono;
};

#endif  // Ennemi107.h
