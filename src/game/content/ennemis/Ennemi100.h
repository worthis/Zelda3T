/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI100_H__
#define __ENNEMI100_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi100 : public Ennemi
{
public:
    Ennemi100(int x, int y);
    ~Ennemi100();

    void ennLoop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    bool isToAvoid(Collision c);

private:
    WImage *image;

    BoundingBox box;
};

#endif // Ennemi100.h
