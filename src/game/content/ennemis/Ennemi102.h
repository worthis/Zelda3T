/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI102_H__
#define __ENNEMI102_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi102 : public Ennemi {
    public :
        Ennemi102(int x, int y);
        ~Ennemi102();

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

        void computeAlpha();

        void moveX(int dx);
        void moveY(int dy);

        int anim;
        int animMax;
        int vanim;

        WImage* image;

        Chrono chrono;

        BoundingBox box;

        int cooldown;
        int step; // 0 hidden, 1 stun
        int alpha;
};

#endif  // Ennemi102.h
