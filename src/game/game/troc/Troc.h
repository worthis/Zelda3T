/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TROC_H__
#define __TROC_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/window/Event.h"
#include "../../../engine/resources/WImage.h"
#include "../../../engine/texts/Text.h"

#include "../../content/CommonGame.h"

#include "../../keys/Action.h"

#include "../../content/link/Inventory.h"

class Troc
{
public:
    Troc();
    ~Troc();

    void init();

    void handleActions(Action *action);
    void draw();

private:
    void drawTitre();

    void drawObjects();

    void drawCadre(int x, int y, int w, int h);

    WImage *imageMenu;
    WImage *imageItems;

    Inventory *inventory;

    Text *texts[28];
};

#endif // Troc.h
