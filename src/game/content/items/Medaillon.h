/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MEDAILLON_H__
#define __MEDAILLON_H__

#include "../types/Item.h"

class Medaillon : public Item
{
public:
    Medaillon(int x, int y, int id);
    ~Medaillon();

    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();

private:
    int id;
};

#endif // Medaillon.h
