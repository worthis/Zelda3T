/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class Animal : public Object
{
public:
    Animal(int x, int y, int type);
    ~Animal();

    void loop();
    void draw(int offsetX, int offsetY);

    bool isCollision(Collision c);

    BoundingBox *getBoundingBox();

private:
    void moveX(int dx);
    void moveY(int dy);

    int type;

    int anim;
    int animMax;
    int vanim;

    Direction direction;

    Chrono chrono;
};

#endif // Animal.h
