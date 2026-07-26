/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONTIMESCONTROLLER_H__
#define __TRANSITIONTIMESCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "TransitionTimes.h"

class TransitionTimesController {
    public :
        TransitionTimesController();
        ~TransitionTimesController();

        void launch();

        void loop();
        void draw();
        void setSens(int s);

    private :

        TransitionTimes transitionTimes;
};

#endif  // TransitionTimesController.h
