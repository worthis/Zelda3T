/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI098_H__
#define __ENNEMI098_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi098 : public Ennemi {
    public :
        Ennemi098(int x, int y);
        ~Ennemi098();

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

    private :

        void snipe();

        int step; // 0 hidden, 1 tourbillon, 2 idle, 3 shoot, 4 tourbillon

        int anim;
        int animMax;
        int vanim;
        int special;

        WImage* image;

        BoundingBox box;

        Chrono chrono;
};

#endif  // Ennemi098.h
