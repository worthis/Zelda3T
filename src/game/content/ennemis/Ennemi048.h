/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI048_H__
#define __ENNEMI048_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi048 : public Ennemi {
    public :
        Ennemi048(int x, int y, bool ivre = false);
        ~Ennemi048();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();

        int getDown();

    private :

        void moveX(int dx);
        void moveY(int dy);

        int anim;
        int animMax;
        int vanim;

        bool ivre;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi048.h
