/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI109_H__
#define __ENNEMI109_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi109 : public Ennemi {
    public :
        Ennemi109(int x, int y);
        ~Ennemi109();

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

        void giveItem(int x, int y);

    private :

        void snipe();
        void snipeInternal(int dstX, int dstY);

        void moveX(int dx);

        int anim;
        int animMax;
        int vanim;

        int step;
        int cooldown;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi109.h
