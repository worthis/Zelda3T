/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GENERIC_H__
#define __GENERIC_H__

#include "../../../engine/resources/WImage.h"

class Generic {
    public :
        Generic();
        ~Generic();

        void draw();

        void setId(int id);

    private :

        WImage* image;

        int id;
};

#endif  // Generic.h
