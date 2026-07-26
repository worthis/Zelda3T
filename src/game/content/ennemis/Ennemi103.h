/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENNEMI103_H__
#define __ENNEMI103_H__

#include "../../../engine/resources/WImage.h"

#include "../types/Ennemi.h"

class Map;

class Ennemi103 : public Ennemi
{
public:
    Ennemi103(int x, int y);
    ~Ennemi103();

    void ennLoop();
    void draw(int offsetX, int offsetY);
    void drawEncyclopedie();

    int getX();
    int getY();

    BoundingBox *getBoundingBox();

    void reset();
    bool isResetable();

    bool hasEffect(TypeAttack type, TypeEffect effect, Direction dir);

protected:
    void giveItem(int x, int y);

private:
    void moveX(int dx);
    void moveY(int dy);

    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;

    BoundingBox box;

    int cooldown;
    int step; // 0 hidden, 1 shoot, 2 go away, 3 come back, 4 blind, 5 attack, 6 attacking
    int alpha;
};

#endif // Ennemi103.h
