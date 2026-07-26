/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CAISSE_H__
#define __CAISSE_H__

#include "../types/Poussable.h"

class Caisse : public Poussable {
    public :
        Caisse(int x, int y, int id = 0, int nb = -1, bool p = false);
        ~Caisse();

        void loop();
        void draw(int offsetX, int offsetY);

        void pousse(Direction d, int v = 1);
        int getDown();

        bool isResetable();
        void reset();

        int getNbMoves();

        void underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect);

        void setNbMoves(int nbMoves);

    private :

        WImage* chiffres;

        int x0;
        int y0;

        int type;
        int nbMoves;
        int nbMovesDebut;

        bool persist;

};

#endif  // Caisse.h
