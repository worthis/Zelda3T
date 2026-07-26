/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __NAUFRAGE_H__
#define __NAUFRAGE_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../CommonGame.h"

#include "../types/Effect.h"

class Naufrage : public Effect
{
public:
    Naufrage(int x, int y);
    ~Naufrage();

    void loop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

private:
    int x;
    int y;

    int anim;
    int animMax;
    int vanim;

    int step;

    WImage *image;

    Chrono chrono;
};

#endif // Naufrage.h
