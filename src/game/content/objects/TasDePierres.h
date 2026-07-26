/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TASDEPIERRE_H__
#define __TASDEPIERRE_H__

#include "../types/Portable.h"
#include "../scene/Map.h"

class TasDePierres : public Portable {
    public :
        TasDePierres(int x, int y, int id);
        ~TasDePierres();

        void portLoop();
        void draw(int offsetX, int offsetY);

        Portable* getPierre();

    private :

        int type;
};

#endif  // TasDePierres.h
