/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI106_H__
#define __ENNEMI106_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi106 : public Ennemi {
    public :
        Ennemi106(int x, int y);
        ~Ennemi106();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        void reset();
        bool isResetable();

        void pousseX(int dx);

    private :

        void snipe(int dx, int dy);

        int anim;
        int animMax;
        int vanim;

        int step;

        WImage* image;

        Chrono chrono;

        BoundingBox box;

        int cooldown;
};

#endif  // Ennemi106.h
