/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEFLAMME_H__
#define __PIEGEFLAMME_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeFlamme : public Object
{
public:
    PiegeFlamme(int x, int y, bool randomMove = true);
    ~PiegeFlamme();

    void loop();

    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

    bool isResetable();
    void reset();

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

    int force;
    bool randomMove;
};

#endif // PiegeFlamme.h
