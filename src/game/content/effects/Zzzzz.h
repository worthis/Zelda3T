/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ZZZZZ_H__
#define __ZZZZZ_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../CommonGame.h"

#include "../types/Effect.h"

class Zzzzz : public Effect {
    public :
        Zzzzz(int x, int y);
        ~Zzzzz();

        void loop();
        void draw(int offsetX, int offsetY);

        int getX();
        int getY();

    private :

        int x;
        int y;

        int anim;
        int animMax;
        int vanim;

        BoundingBox box;

        WImage* image;

        Chrono chrono;
};

#endif  // Zzzzz.h
