/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIECEORUN_H__
#define __PIECEORUN_H__

#include "../types/Item.h"

class PieceOrUn : public Item
{
public:
    PieceOrUn(int x, int y);
    ~PieceOrUn();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // PieceOrUn.h
