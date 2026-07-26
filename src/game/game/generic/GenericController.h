/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GENERICCONTROLLER_H__
#define __GENERICCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "Generic.h"

class GenericController {
    public :
        GenericController();
        ~GenericController();

        void draw();
        void setId(int i);

    private :

        Generic generic;
};

#endif  // GenericController.h
