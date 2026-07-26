/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GANONORUN_H__
#define __GANONORUN_H__

#include "../types/Item.h"

class GanonOrUn : public Item
{
public:
    GanonOrUn(int x, int y);
    ~GanonOrUn();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // GanonOrUn.h
