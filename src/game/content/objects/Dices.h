/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __DICES_H__
#define __DICES_H__

#include "../types/Object.h"

#include "../scene/Map.h"

#include "Caisse.h"

#include "../../../engine/util/time/Chrono.h"

class Dices : public Object
{
public:
    Dices(int x, int y, bool signes = true, bool moving = false, bool actif = false, Map *map = 0, Caisse *caisse = 0);
    ~Dices();

    void loop();

    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

    bool isResetable();
    void reset();

    bool isActif();
    int getValue();

    void activer(bool moving);
    void stopper();

private:
    void moveX(int dx);
    void moveY(int dy);

    Direction direction;

    int anim;
    int animMax;
    int vanim;

    Chrono chrono;

    int x0;
    int y0;
    Direction dir0;
    bool randomMove0;
    bool actif0;

    int force;
    bool signes;
    bool randomMove;
    bool actif;
    int value;

    Caisse *caisse;
};

#endif // Dices.h
