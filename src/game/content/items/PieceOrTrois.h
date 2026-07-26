/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIECEORTROIS_H__
#define __PIECEORTROIS_H__

#include "../types/Item.h"

class PieceOrTrois : public Item
{
public:
    PieceOrTrois(int x, int y);
    ~PieceOrTrois();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();
};

#endif // PieceOrTrois.h
