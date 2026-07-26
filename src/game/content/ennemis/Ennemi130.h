/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI130_H__
#define __ENNEMI130_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi130 : public Ennemi {
    public :
        Ennemi130(int x, int y);
        ~Ennemi130();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();

    private :

        int anim;
        int animMax;
        int vanim;

        int cooldown;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi130.h
