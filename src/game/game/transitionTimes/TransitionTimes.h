/*

    Zelda Time to Triumph

    Copyright (C) 2007-2024  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONTIMES_H__
#define __TRANSITIONTIMES_H__

#include "../../content/CommonGame.h"
#include "../../content/scene/Map.h"

class TransitionTimes
{
public:
    TransitionTimes();
    ~TransitionTimes();

    void loop();
    void draw();

    void init();
    void setSens(int s);

private:
    int getSecondMapId(int mapId);

    Map *mapDestination;
    BoundingBox *box;

    WImage *imageJurassique;
    WImage *imageApocalypse;

    WImage *filterForest[3];
    WImage *filterRain[3];
    WImage *filterSnow[3];
    WImage *filterSky[3];

    WImage *imageDestination;
    int alpha;
    bool reset;
    int sens;
    int destinationId;
};

#endif // TransitionTimes.h
