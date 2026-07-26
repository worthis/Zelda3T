/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI110_H__
#define __ENNEMI110_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi110 : public Ennemi {
    public :
        Ennemi110(int x, int y);
        ~Ennemi110();

        void ennLoop();
        void draw(int offsetX, int offsetY);
        void drawEncyclopedie();

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    private :

        void moveX(int dx);
        void moveY(int dy);

        int anim;
        int animMax;
        int vanim;

        int step;

        WImage* image;

        Chrono chrono;

        BoundingBox box;

        int cooldown;
};

#endif  // Ennemi110.h
