/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __INTERRUPTEUR_H__
#define __INTERRUPTEUR_H__

#include "../types/Object.h"
#include "../scene/Map.h"

class Interrupteur : public Object {
    public :
        Interrupteur(int x, int y, int type, bool used, Map* map, bool usable = true);
        ~Interrupteur();

        void loop();
        void draw(int offsetX, int offsetY);

        bool isResetable();
        void reset();

        void displayOnMap();
        void setUsed(bool b);
        bool isUsed();

    private :

        int type;
        bool used;
        Map* map;
        bool wasUsable;
        bool usable;
};

#endif  // Interrupteur.h
