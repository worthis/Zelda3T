/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEFLAMMEVERTE_H__
#define __PIEGEFLAMMEVERTE_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class PiegeFlammeVerte : public Object {
    public :
        PiegeFlammeVerte(int x, int y);
        ~PiegeFlammeVerte();

        void loop();

        void draw(int offsetX, int offsetY);

        BoundingBox* getBoundingBox();

    private :
        void moveY(int dy);

        Direction direction;

        int anim;
        int animMax;
        int vanim;

        Chrono chrono;
};

#endif  // PiegeFlammeVerte.h
