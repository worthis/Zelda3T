/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GEMME_H__
#define __GEMME_H__

#include "../types/Item.h"

class Gemme : public Item {
    public :
        Gemme(int x, int y, int id);
        ~Gemme();

        void loop();
        void draw(int offsetX, int offsetY);

        void action();

        bool isPickable();

    private :

        int id;
};

#endif  // Gemme.h
