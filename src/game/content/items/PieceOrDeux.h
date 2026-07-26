/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIECEORDEUX_H__
#define __PIECEORDEUX_H__

#include "../types/Item.h"

class PieceOrDeux : public Item
{
public:
    PieceOrDeux(int x, int y);
    ~PieceOrDeux();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // PieceOrDeux.h
