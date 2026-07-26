/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PLANCHES_H__
#define __PLANCHES_H__

#include "../types/Item.h"

class Planches : public Item
{
public:
    Planches(int x, int y);
    ~Planches();

    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();

private:
    int id;
};

#endif // Planches.h
