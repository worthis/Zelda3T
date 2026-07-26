/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI101_H__
#define __ENNEMI101_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Ennemi101 : public Ennemi
{
public:
    Ennemi101(int x, int y, Direction dir);
    ~Ennemi101();

    void ennLoop();
    void draw(int offsetX, int offsetY);
    void drawEncyclopedie();

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

    int getDown();

private:
    int cooldown;
    bool special;

    WImage *image;

    BoundingBox box;
};

#endif // Ennemi101.h
