/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GANONORCINQ_H__
#define __GANONORCINQ_H__

#include "../types/Item.h"

class GanonOrCinq : public Item
{
public:
    GanonOrCinq(int x, int y);
    ~GanonOrCinq();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // GanonOrCinq.h
