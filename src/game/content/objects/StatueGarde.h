/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __STATUEGARDE_H__
#define __STATUEGARDE_H__

#include "../types/Object.h"

class StatueGarde : public Object {
    public :
        StatueGarde(int x, int y);
        ~StatueGarde();

        void draw(int offsetX, int offsetY);
};

#endif  // StatueGarde.h
