/*

    Zelda Time to Triumph

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __FISH_H__
#define __FISH_H__

#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"
#include "../../keys/Action.h"


class Fish {
    public :
        Fish();
        ~Fish();

        void init();

        void handleActions(Action* action);
        void draw();

    private :

        void cadre(int x, int y, int w, int h, int type);

        void fish(int x, int y, int type);

        int getNextPageFrom(int page);
        int getPreviousPageFrom(int page);
        bool isPageEmpty(int page);

        int page;

        WImage* image;

        Text* texts[37];
};

#endif  // Fish.h
