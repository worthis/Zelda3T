/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI111_H__
#define __ENNEMI111_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi111 : public Ennemi {
    public :
        Ennemi111(int x, int y);
        ~Ennemi111();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

    protected :

        void giveItem(int x, int y);

    private :

        void moveX(int dx);
        void moveY(int dy);

        int anim;
        int animMax;
        int vanim;

        int step;
        int elan;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi111.h
