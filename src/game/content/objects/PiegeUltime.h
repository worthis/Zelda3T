/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEULTIME_H__
#define __PIEGEULTIME_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeUltime : public Object {
    public :
        PiegeUltime(int x, int y, bool autoFire = true);
        ~PiegeUltime();

        void loop();
        void draw(int offsetX, int offsetY);

        void snipe();

        void disable();

    private :

        Chrono chrono;

        int anim;
        int animMax;
        int vanim;

        bool autoFire;

        bool enable;
};

#endif  // PiegeUltime.h
