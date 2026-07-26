/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CLETEMPS_H__
#define __CLETEMPS_H__

#include "../types/Item.h"

class CleTemps : public Item
{
public:
    CleTemps(int x, int y);
    ~CleTemps();

    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();
};

#endif // CleTemps.h
