/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __FISHCONTROLLER_H__
#define __FISHCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "Fish.h"

class FishController
{
public:
    FishController();
    ~FishController();

    void launch();

    void handleActions(Action *action);
    void loop();
    void draw();

private:
    Fish fish;
};

#endif // FishController.h
