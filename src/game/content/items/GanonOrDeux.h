/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GANONORDEUX_H__
#define __GANONORDEUX_H__

#include "../types/Item.h"

class GanonOrDeux : public Item
{
public:
    GanonOrDeux(int x, int y);
    ~GanonOrDeux();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // GanonOrDeux.h
