/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI086_H__
#define __ENNEMI086_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi086 : public Ennemi
{
public:
    Ennemi086(int x, int y);
    ~Ennemi086();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();

    bool isToAvoid(Collision c);

private:
    int cooldown;

    WImage *image;

    BoundingBox box;
};

#endif // Ennemi086.h
