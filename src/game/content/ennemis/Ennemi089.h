/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI089_H__
#define __ENNEMI089_H__

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../types/Ennemi.h"

class Ennemi089 : public Ennemi {
    public :
        Ennemi089(int x, int y, int a = 0, bool ko = false);
        ~Ennemi089();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();
        bool isResetable();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

        void setDirection(Direction dir);

    protected :

        void afterHit();

        void giveItem(int x, int y);

        bool canDie(TypeEffect effect);

    private :

        int anim;
        int animMax;
        int vanim;

        int animSword;
        bool isKo;
        int speed;
        int weapon;

        WImage* image;

        Chrono chrono;

        BoundingBox box;
};

#endif  // Ennemi089.h
