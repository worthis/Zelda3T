/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PNJ_H__
#define __PNJ_H__

#include "../types/Object.h"

#include "../../../engine/util/time/Chrono.h"

class Pnj : public Object
{
public:
    Pnj(int x, int y, int type, int texte, Direction dir = S);
    ~Pnj();

    void loop();

    void draw(int offsetX, int offsetY);

    bool action(Direction dir);

    BoundingBox *getBoundingBox();

    int getDown();

    void moveTo(int x, int y, Direction dir);

    void setDirection(Direction dir);
    void moveX(int dx);
    void moveY(int dy);

    void setAnimMax(int i);
    int getType();

    bool isResetable();
    void reset();

private:
    void init();

    int getDynamicText();

    int type;
    int texte;

    int anim;
    int animMax;
    int vanim;

    Chrono chrono;

    int w;
    int h;

    int displayW;
    int displayH;

    bool idle;

    Direction direction;

    bool stop;

    int x0;
    int y0;
    Direction dir0;

    int cooldown;
};

#endif // Pnj.h
