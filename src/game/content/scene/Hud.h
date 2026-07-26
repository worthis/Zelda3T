/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __HUD_H__
#define __HUD_H__

#include "../../../engine/resources/WImage.h"

#include "../link/Status.h"
#include "../link/Inventory.h"


class Hud {
    public :
        Hud(Status* status, Inventory* inventory, bool isFrench);
        ~Hud();

        void loop();
        void draw();

        void setBossLife(int life, int maxLife);
        void setBossLife2(int life, int maxLife);
        void reset();

        void displayEtage();

        void displayTime();
        void hideTime();
        void displayCasino();
        void hideCasino();
        void instantBoss();

        void displayDestFinal();
        void hideDestFinal();

    private :

        void drawLife();
        void drawMagic();
        void drawItems();
        void drawObject();
        void drawBonus();
        void drawBoss();
        void drawEtage();
        void drawInfo();

        void drawNombre(int val, int max, int x, int y, int nb);

        Status* status;
        Inventory* inventory;
        bool french;
        int animBoss;
        int animBoss2;
        int animBossX;
        int bossLife;
        int bossMaxLife;
        int bossLife2;
        int bossMaxLife2;
        bool removeBoss;
        int etage;
        int displayEtg;
        bool time;
        bool casino;
        bool destFinal;

        WImage* image;
        WImage* chiffres;
        WImage* level;

};

#endif  // Hud.h
