/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MAP_H__
#define __MAP_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Metronome.h"
#include "../../../engine/util/tree/Quadtree.h"

#include "../CommonGame.h"

#include "../types/Effect.h"
#include "../types/Ennemi.h"
#include "../types/Item.h"
#include "../types/Projectile.h"
#include "../types/Object.h"
#include "../types/Portable.h"

#include "MapInitializer.h"

#define NB_IMAGES 7

class Map
{
public:
    Map(int level, Metronome *metronome);
    ~Map();

    void launch();
    void reset();
    void load();

    void launchRoom();
    BoundingBox *getBounds();
    void resetRoom();

    void loop();
    void draw(List *toDraw, BoundingBox *box, int dstX = 0, int dstY = 0);

    int getW();
    int getH();

    int getId();

    short getMur(int x, int y); // returns mur value from coordinatess
    short getSol(int x, int y); // returns sol value from coordinatess

    void setSol(int x, int y, short s);
    void setSol(int x, int y, short s, Collision c);
    void setSol(int x, int y, int w, int h, short s, Collision c);

    void setAir(int x, int y, short s);

    void setMur(int x, int y, Collision c);
    void setMur(int x, int y, Collision c1, Collision c2, Collision c3, Collision c4);

    void addEffect(Effect *effect);
    void addEnnemi(Ennemi *ennemi);
    void addItem(Item *item);
    void addProjectile(Projectile *projectile);
    void addObject(Object *object);

    void removeObject(Object *object);

    bool isOnWater(BoundingBox *box);

    bool checkCollisions(BoundingBox *box, Collisionable *object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox,
                         bool checkObjects = true, int safeX = 0, int safeY = 0, int safeW = -1, int safeH = -1, bool checkDanger = false);

    bool testDegat(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis = true, bool onObjects = true);

    bool testTransition(int x, int y);
    bool testInnerTransition(int x, int y);
    bool testTeleport(int x, int y);
    bool testBarque(int x, int y);

    void testAnim(int x, int y, Direction dir, bool sound = true);
    void testAnimRoom();

    void ouvrePorteMaison(int x, int y);

    bool testGemmeForce(int x, int y);

    void activateInter(int x, int y, bool sound = true);
    bool desactivateInter(int x, int y, bool sound = true);
    void allumeTorche(int x, int y);
    void eteintTorche(int x, int y);
    void activateInterStar(int x, int y, bool sound = true);

    void pickUpItems(BoundingBox *box);
    Item *getItem(BoundingBox *box);
    void killItems(BoundingBox *box);
    void killEnnemis(BoundingBox *box, bool withEffect = false);
    Portable *pickUpObject(BoundingBox *box);
    void pushObject(BoundingBox *box, Direction dir);

    bool tryToTalk(BoundingBox *box, Direction dir);

    void permuteBlocs(int step); // 0 = orange up - blue down

    int nbObjects();
    int nbEnnemis();

    void ouvrePorte(int x, int y, int type);
    void fermePorte(int x, int y, int type);

    void removeZelda();
    void removeStele();

    void songPlayed(int id);

    void disablePiege();

    // game map 30
    void closeChests();
    void openChests(int x, int y);
    bool areChestsClosed();

    void pnjBoitCafe(bool boit);

    int getEtage();
    Epoque getEpoque();

    void addCoffre(int x, int y, TypeItem type, int id);

    void enervePoules();
    void cachetteZora(bool cache);
    void barque(bool visible = true);
    void updatePonton(int x, int y);
    int getOldBarque();

    void addWagon();
    void switchLevier();

    void switchSphere(bool blue);
    void switchStar();

    void displayInterruptor(int x, int y);
    void reactiveInterruptor(int x, int y, bool used = false);

    void impFire(int x, int y);
    void cleanImp();

    void tigreFire(int x, int y);
    void piegeFire(int x, int y);

    void cleanFlamme();

    void activateStatue();

    void drawSol(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);
    void drawAir(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);

    void onJarreBroken();

    void increaseCasino();
    int getCasino();
    bool isJeuCasinoStarted();
    void startJeuCasino();
    bool isJeuCasinoGagne();
    bool isJeuCasinoFini();
    void recompenseJeuCasino();
    int getTempsCasinoRestant();
    void activateDices(int i, int j, bool gameReady);
    void choixCasinoUn(bool choix);
    void jeuCasinoPerdu();
    int getPriceCasino();
    bool bossCasinoVaincu();

    void startDestFinal();
    void increaseDestFinal();
    int getDestFinal();
    void setDestFinalTypeEnn(int type);
    int getDestFinalTypeEnn();
    int getDestFinalNbEnn();
    void startFinalBattle();

    void testFinBoss();

    bool isIndoor();

private:
    void init();

    void loadFromFile();

    int getMotif(int value);

    int nbJarres();
    void persistJarres(int nb);    // boss map 46
    void resetRandomJarre(int nb); // boss map 46
    int nbCaissesMovable();
    int nbCaisses();
    int nbCoffres();
    bool isCaisse(int x, int y);

    void holeStar(int x, int y, int w, int h);
    void fullStar(int x, int y, int w, int h);

    int getTotalDices(int x, int y, int w, int h);

    Metronome *metronome;
    int map;
    int w; // size
    int h;

    int music;

    int stones;        // for the puzzle in the desert
    Object *jarres[6]; // boss map 15
    int oldBarque;
    int casino; // count for map 58
    int jeuCasinoStarted;
    double tempsCasinoEcoule;
    bool choixCasino;

    short sol[MAX_CASE_X][MAX_CASE_Y];
    short air[MAX_CASE_X][MAX_CASE_Y];
    short mur[MAX_CASE_X * 2][MAX_CASE_Y * 2];

    WImage *images[NB_IMAGES];

    Quadtree *effects;
    Quadtree *ennemis;
    Quadtree *items;
    Quadtree *projectiles;
    Quadtree *objects;

    MapInitializer *initializer;

    BoundingBox bounds; // room limits

    int oldMetronomeValue;
};

#endif // Map.h
