/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI131_H__
#define __ENNEMI131_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi131 : public Ennemi {
    public :
        Ennemi131(int x, int y);
        ~Ennemi131();

        void ennLoop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

        BoundingBox* getBoundingBox();

        void reset();

        bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    private :

        int cooldown;

        WImage* image;

        BoundingBox box;
};

#endif  // Ennemi131.h
