/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WAGON_H__
#define __WAGON_H__

#include "../types/Object.h"
#include "../link/Link.h"

class Wagon : public Object {
    public :
        Wagon(int x, int y, Direction dir);
        ~Wagon();

        void loop();

        void draw(int offsetX, int offsetY);
        bool action(Direction dir);

        int getDown();

    private :

        void moveN();
        void moveS();
        void moveW();
        void moveE();

        Direction direction;
        bool running;

        Link* link;
};

#endif  // Wagon.h
