#include "MapInitializer.h"

#include "Map.h"

#include "../../MainController.h"
#include "../../GlobalSave.h"

#include "../objects/Pierre.h"
#include "../objects/TasDePierres.h"
#include "../objects/Pancarte.h"
#include "../objects/Pnj.h"
#include "../objects/Poule.h"
#include "../objects/PouleBig.h"
#include "../objects/Animal.h"
#include "../objects/Coffre.h"
#include "../objects/PiegePics.h"
#include "../objects/PiegeLong.h"
#include "../objects/PiegeMurs.h"
#include "../objects/PiegeFeu.h"
#include "../objects/PiegeFlamme.h"
#include "../objects/PiegeDemi.h"
#include "../objects/PiegeColere.h"
#include "../objects/PiegeUltime.h"
#include "../objects/Dices.h"
#include "../objects/Jarre.h"
#include "../objects/Sphere.h"
#include "../objects/Caisse.h"
#include "../objects/Interrupteur.h"
#include "../objects/InterrupteurStar.h"
#include "../objects/PiegeMain.h"
#include "../objects/TalkableArea.h"
#include "../objects/Barriere.h"
#include "../objects/StatueGarde.h"
#include "../objects/Stele.h"
#include "../objects/Switch.h"
#include "../effects/Zzzzz.h"
#include "../ennemis/Ennemi001.h"
#include "../ennemis/Ennemi002.h"
#include "../ennemis/Ennemi003.h"
#include "../ennemis/Ennemi004.h"
#include "../ennemis/Ennemi005.h"
#include "../ennemis/Ennemi006.h"
#include "../ennemis/Ennemi007.h"
#include "../ennemis/Ennemi008.h"
#include "../ennemis/Ennemi009.h"
#include "../ennemis/Ennemi010.h"
#include "../ennemis/Ennemi011.h"
#include "../ennemis/Ennemi012.h"
#include "../ennemis/Ennemi013.h"
#include "../ennemis/Ennemi014.h"
#include "../ennemis/Ennemi015.h"
#include "../ennemis/Ennemi016.h"
#include "../ennemis/Ennemi018.h"
#include "../ennemis/Ennemi019.h"
#include "../ennemis/Ennemi022.h"
#include "../ennemis/Ennemi023.h"
#include "../ennemis/Ennemi024.h"
#include "../ennemis/Ennemi025.h"
#include "../ennemis/Ennemi026.h"
#include "../ennemis/Ennemi027.h"
#include "../ennemis/Ennemi028.h"
#include "../ennemis/Ennemi029.h"
#include "../ennemis/Ennemi030.h"
#include "../ennemis/Ennemi031.h"
#include "../ennemis/Ennemi032.h"
#include "../ennemis/Ennemi033.h"
#include "../ennemis/Ennemi034.h"
#include "../ennemis/Ennemi035.h"
#include "../ennemis/Ennemi037.h"
#include "../ennemis/Ennemi038.h"
#include "../ennemis/Ennemi039.h"
#include "../ennemis/Ennemi040.h"
#include "../ennemis/Ennemi041.h"
#include "../ennemis/Ennemi042.h"
#include "../ennemis/Ennemi043.h"
#include "../ennemis/Ennemi044.h"
#include "../ennemis/Ennemi046.h"
#include "../ennemis/Ennemi047.h"
#include "../ennemis/Ennemi048.h"
#include "../ennemis/Ennemi050.h"
#include "../ennemis/Ennemi053.h"
#include "../ennemis/Ennemi054.h"
#include "../ennemis/Ennemi055.h"
#include "../ennemis/Ennemi056.h"
#include "../ennemis/Ennemi062.h"
#include "../ennemis/Ennemi064.h"
#include "../ennemis/Ennemi072.h"
#include "../ennemis/Ennemi076.h"
#include "../ennemis/Ennemi077.h"
#include "../ennemis/Ennemi084.h"
#include "../ennemis/Ennemi086.h"
#include "../ennemis/Ennemi087.h"
#include "../ennemis/Ennemi089.h"
#include "../ennemis/Ennemi091.h"
#include "../ennemis/Ennemi092.h"
#include "../ennemis/Ennemi093.h"
#include "../ennemis/Ennemi094.h"
#include "../ennemis/Ennemi095.h"
#include "../ennemis/Ennemi097.h"
#include "../ennemis/Ennemi098.h"
#include "../ennemis/Ennemi099.h"
#include "../ennemis/Ennemi100.h"
#include "../ennemis/Ennemi101.h"
#include "../ennemis/Ennemi102.h"
#include "../ennemis/Ennemi103.h"
#include "../ennemis/Ennemi104.h"
#include "../ennemis/Ennemi105.h"
#include "../ennemis/Ennemi106.h"
#include "../ennemis/Ennemi107.h"
#include "../ennemis/Ennemi108.h"
#include "../ennemis/Ennemi109.h"
#include "../ennemis/Ennemi110.h"
#include "../ennemis/Ennemi111.h"
#include "../ennemis/Ennemi112.h"
#include "../ennemis/Ennemi113.h"
#include "../ennemis/Ennemi115.h"
#include "../ennemis/Ennemi116.h"
#include "../ennemis/Ennemi117.h"
#include "../ennemis/Ennemi118.h"
#include "../ennemis/Ennemi119.h"
#include "../ennemis/Ennemi120.h"
#include "../ennemis/Ennemi121.h"
#include "../ennemis/Ennemi123.h"
#include "../ennemis/Ennemi126.h"
#include "../ennemis/Ennemi127.h"
#include "../ennemis/Ennemi128.h"
#include "../ennemis/Ennemi129.h"
#include "../ennemis/Ennemi130.h"
#include "../ennemis/Ennemi131.h"
#include "../ennemis/Ennemi132.h"
#include "../ennemis/Ennemi133.h"
#include "../ennemis/Ennemi134.h"
#include "../ennemis/Ennemi135.h"
#include "../ennemis/Ennemi136.h"
#include "../ennemis/Ennemi137.h"
#include "../ennemis/Ennemi138.h"
#include "../ennemis/Ennemi139.h"
#include "../ennemis/Ennemi140.h"

MapInitializer::MapInitializer(Map* m) : map(m) {
}

MapInitializer::~MapInitializer() {
}


void MapInitializer::addEnnemi(Ennemi* ennemi) {
    map->addEnnemi(ennemi);
}

void MapInitializer::addItem(Item* item) {
    map->addItem(item);
}

void MapInitializer::addObject(Object* object) {
    map->addObject(object);
}

void MapInitializer::addEffect(Effect* effect) {
    map->addEffect(effect);
}

void MapInitializer::ouvrePorte(int x, int y, int type) {
    map->ouvrePorte(x, y, type);
}


void MapInitializer::init() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    Inventory* inventory = link->getInventory();
    Switch* levier;

    switch (map->getId()) {
        case 1 :
            addObject(new Pierre(16*3, 16*31, 1, map));
            addObject(new Pierre(16*18, 16*15, 1, map));
            addObject(new Pierre(16*29, 16*25, 1, map));
            addObject(new Pierre(16*32, 16*8, 1, map));
            addObject(new Pierre(16*72, 16*17, 1, map));
            addObject(new Pierre(16*77, 16*38, 1, map));
            addObject(new Pierre(16*4, 16*52, 2, map));
            addObject(new Pierre(16*26, 16*44, 2, map));
            addObject(new Pierre(16*31, 16*18, 2, map));
            addObject(new Pierre(16*33, 16*36, 2, map));
            addObject(new Pierre(16*60, 16*51, 2, map));
            addObject(new Pierre(16*65, 16*28, 2, map));

            if (scene->getCoffre(0, 0)) {
                ouvrePorte(59, 10, 0);
            }

            addEnnemi(new Ennemi077(7*16-13, 53*16-12)); addEnnemi(new Ennemi077(8*16-13, 34*16-12));
            addEnnemi(new Ennemi077(13*16-13, 18*16-12)); addEnnemi(new Ennemi077(13*16-13, 43*16-12));
            addEnnemi(new Ennemi077(26*16-13, 29*16-12)); addEnnemi(new Ennemi077(31*16-13, 51*16-12));
            addEnnemi(new Ennemi077(35*16-13, 15*16-12)); addEnnemi(new Ennemi077(51*16-13, 15*16-12));
            addEnnemi(new Ennemi077(53*16-13, 29*16-12)); addEnnemi(new Ennemi077(62*16-13, 49*16-12));
            addEnnemi(new Ennemi077(70*16-13, 38*16-12));
            break;
        case 2 :
            addObject(new Pierre(16*6, 16*8, 1, map));
            addObject(new Pierre(16*7, 16*21, 1, map));
            addObject(new Pierre(16*26, 16*50, 1, map));
            addObject(new Pierre(16*56, 16*8, 1, map));
            addObject(new Pierre(16*36, 16*10, 2, map));
            addObject(new Pierre(16*53, 16*41, 2, map));

            if (!inventory->hasGemmeForce(15)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 38*16, 36*16 + 8, 15, false));
            }

            addEnnemi(new Ennemi077(13*16-13, 34*16-12)); addEnnemi(new Ennemi077(15*16-13, 48*16-12));
            addEnnemi(new Ennemi077(23*16-13, 45*16-12)); addEnnemi(new Ennemi077(29*16-13, 12*16-12));
            addEnnemi(new Ennemi077(41*16-13, 33*16-12)); addEnnemi(new Ennemi077(47*16-13, 40*16-12));
            addEnnemi(new Ennemi077(54*16-13, 14*16-12));
            break;
        case 3 :
            addObject(new Pierre(16*25, 16*26, 1, map));
            addObject(new Pierre(16*31, 16*85, 1, map));
            addObject(new Pierre(16*35, 16*9, 1, map));
            addObject(new Pierre(16*36, 16*28, 1, map));
            addObject(new Pierre(16*57, 16*22, 1, map));
            addObject(new Pierre(16*72, 16*86, 1, map));
            addObject(new Pierre(16*74, 16*40, 1, map));
            addObject(new Pierre(16*75, 16*70, 1, map));
            addObject(new Pierre(16*4, 16*45, 2, map));
            addObject(new Pierre(16*5, 16*79, 2, map));
            addObject(new Pierre(16*65, 16*7, 2, map));
            addObject(new Pancarte(16*44, 16*8, 371, map));

            if (!inventory->hasQuartCoeur(5)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 19*16+8, 5*16+8, 5));
            }

            if (scene->getAvancement() >= AV_INFO_PASSE_OK) {
                if (!inventory->hasObject(TROC_GEMME_VERTE) || inventory->getTrocGemme(3) < TGV_CONFITURE) {
                    addObject(new Pnj(33*16+8, 75*16+6, 9, 391, N));
                } else {
                    addObject(new Pnj(33*16+8, 75*16+6, 9, 391));
                }

                addObject(new Pnj(46*16+8, 30*16+6, 20, 372, N));
                addObject(new TalkableArea(46*16+8, 32*16, 372));
                if (link->getStatus()->getMaxPieceOr() < 999) {
                    map->setSol(45*16, 31*16, link->getStatus()->getMaxPieceOr() == 500 ? 2179 :
                                    link->getStatus()->getMaxPieceOr() == 200 ? 2177 : 2175);
                }
                map->setSol(45*16, 32*16, link->getStatus()->getMaxPieceOr() == 999 ? 2173 :
                                link->getStatus()->getMaxPieceOr() == 500 ? 2178 :
                                link->getStatus()->getMaxPieceOr() == 200 ? 2176 : 2174);

                addObject(new Pnj(16*46 + 8, 16*37 + 5, 12, 381, W));
                map->setSol(45*16, 39*16, 2180);
                map->setSol(45*16, 38*16, 2181);

                addObject(new Pnj(16*32 + 8, 16*44+8, 42, 283));
                if (!inventory->hasQuartCoeur(4)) {
                    map->setSol(31*16, 45*16, 2183);
                }
                map->setSol(31*16, 46*16, inventory->hasQuartCoeur(4) ? 2173 : 2182);

                addObject(new Pnj(16*46+4, 16*45-4, 39, 384));
                map->setSol(45*16, 46*16, 2184);
                map->setSol(45*16, 45*16, 2185);

                addObject(new Pnj(16*57, 16*51, 14, 386));
                addObject(new Pnj(46*16, 65*16+2, 35, 387));
                addObject(new Pnj(16*27+8, 16*57+8, 10, 388));

                addObject(new Pnj(16*17, 16*66, 23, 389));
                addObject(new Pnj(16*57, 16*81, 51, 390));

                addObject(new Poule(16*25, 16*58));
                addObject(new Poule(16*30, 16*57));
                addObject(new Poule(16*26, 16*61));
                addObject(new Poule(16*33, 16*62));
                addObject(new Poule(16*29, 16*59));
            }
            break;
        case 4 :
            addObject(new Pierre(16*8, 16*10, 1, map));
            addObject(new Pierre(16*29, 16*54, 1, map));
            addObject(new Pierre(16*57, 16*9, 1, map));
            addObject(new Pierre(16*68, 16*10, 1, map));
            addObject(new Pierre(16*71, 16*33, 1, map));
            addObject(new Pierre(16*16, 16*5, 2, map));
            addObject(new Pierre(16*70, 16*48, 2, map));

            if (scene->getAvancement() < AV_TEMPLE_DEESSES_APPARU) {
                map->setSol(19*16, 22*16, 42, 11, 549, NEIGE);
                map->setSol(19*16, 38*16, 42, 7, 549, NEIGE);
                map->setSol(20*16, 33*16, 40, 5, 549, NEIGE);
                map->setSol(32*16, 45*16, 16, 3, 549, NEIGE);
                for (int j = 0; j < 22; j++) {
                    for (int i = 0; i < 42; i++) {
                        map->setAir((19 + i) * 16, (22 + j) * 16, -1);
                    }
                }
                map->setSol(22*16, 28*16, 550); map->setSol(25*16, 24*16, 550); map->setSol(25*16, 34*16, 550);
                map->setSol(26*16, 41*16, 550); map->setSol(28*16, 37*16, 550); map->setSol(30*16, 31*16, 550);
                map->setSol(33*16, 25*16, 550); map->setSol(34*16, 36*16, 550); map->setSol(36*16, 43*16, 550);
                map->setSol(38*16, 38*16, 550); map->setSol(39*16, 32*16, 550); map->setSol(41*16, 45*16, 550);
                map->setSol(42*16, 25*16, 550); map->setSol(44*16, 36*16, 550); map->setSol(47*16, 41*16, 550);
                map->setSol(48*16, 30*16, 550); map->setSol(51*16, 26*16, 550); map->setSol(52*16, 33*16, 550);
                map->setSol(53*16, 37*16, 550); map->setSol(55*16, 24*16, 550); map->setSol(56*16, 28*16, 550);
                map->setSol(56*16, 42*16, 550); map->setSol(57*16, 34*16, 550);

                // triforce
                map->setSol(39*16, 36*16, 2301); map->setSol(40*16, 36*16, 2302);
                map->setSol(38*16, 37*16, 2303); map->setSol(39*16, 37*16, 2304); map->setSol(40*16, 37*16, 2305); map->setSol(41*16, 37*16, 2306);
                map->setSol(38*16, 38*16, 2307); map->setSol(39*16, 38*16, 2308); map->setSol(40*16, 38*16, 2307); map->setSol(41*16, 38*16, 2308);

                addObject(new Animal(32 * 16, 29 * 16, 0));
                addObject(new Animal(53 * 16, 24 * 16, 0));
                addObject(new Animal(39 * 16, 23 * 16, 1));
                addObject(new Animal(25 * 16, 38 * 16, 2));
                addObject(new Animal(55 * 16, 39 * 16, 2));
                addObject(new Animal(45 * 16, 47 * 16, 3));
                addObject(new Animal(21 * 16, 23 * 16, 3));
                addObject(new Animal(49 * 16, 31 * 16, 4));
                addObject(new Animal(32 * 16, 44 * 16, 4));
                addObject(new Animal(43 * 16, 28 * 16, 4));
            }
            break;
        case 5 :
            addObject(new Pierre(16*2, 16*71, 1, map));
            addObject(new Pierre(16*9, 16*39, 1, map));
            addObject(new Pierre(16*10, 16*20, 1, map));
            addObject(new Pierre(16*16, 16*51, 1, map));
            addObject(new Pierre(16*29, 16*30, 1, map));
            addObject(new Pierre(16*32, 16*79, 1, map));
            addObject(new Pierre(16*44, 16*14, 1, map));
            addObject(new Pierre(16*54, 16*69, 1, map));
            addObject(new Pierre(16*56, 16*22, 1, map));

            addObject(new Pierre(16*4, 16*34, 2, map));
            addObject(new Pierre(16*10, 16*81, 2, map));
            addObject(new Pierre(16*29, 16*14, 2, map));
            addObject(new Pierre(16*41, 16*53, 2, map));
            addObject(new Pierre(16*49, 16*5, 2, map));
            addObject(new Pierre(16*56, 16*50, 2, map));

            if (!inventory->hasQuartCoeur(6)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 9*16, 75*16+8, 6));
            }

            addEnnemi(new Ennemi077(43*16-13, 59*16-12)); addEnnemi(new Ennemi077(32*16-13, 68*16-12));
            addEnnemi(new Ennemi077(52*16-13, 21*16-12)); addEnnemi(new Ennemi077(23*16-13, 9*16-12));
            addEnnemi(new Ennemi077(13*16-13, 27*16-12)); addEnnemi(new Ennemi077(14*16-13, 55*16-12));
            addEnnemi(new Ennemi077(48*16-13, 72*16-12)); addEnnemi(new Ennemi077(53*16-13, 41*16-12));
            break;
        case 6 :
            addObject(new Pierre(16*4, 16*31, 1, map));
            addObject(new Pierre(16*10, 16*71, 1, map));
            addObject(new Pierre(16*32, 16*11, 1, map));
            addObject(new Pierre(16*5, 16*65, 2, map));
            addObject(new Pierre(16*55, 16*55, 2, map));
            addObject(new Pierre(16*71, 16*14, 2, map));

            addObject(new Coffre(48 * 16, 42 * 16, 0, inventory->hasCristal(4), TI_CRISTAL, 4));

            if (!inventory->hasGemmeForce(53)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 66*16, 36*16 + 8, 53, false));
            }

            addObject(new Pnj(16*16+8, 16*66+3, 66, 420));

            addEnnemi(new Ennemi042(31*16-5,27*16-3)); addEnnemi(new Ennemi042(41*16-5,12*16-3));
            addEnnemi(new Ennemi042(64*16-5,28*16-3)); addEnnemi(new Ennemi042(7*16-5,18*16-3));
            addEnnemi(new Ennemi042(54*16-5,82*16-3)); addEnnemi(new Ennemi042(41*16-5,44*16-3));
            addEnnemi(new Ennemi042(25*16-5,39*16-3));
            break;
        case 7 :
            addObject(new Pierre(16*18, 16*3, 1, map));
            addObject(new Pierre(16*21, 16*35, 1, map));
            addObject(new Pierre(16*62, 16*31, 1, map));
            addObject(new Pierre(16*92, 16*3, 1, map));
            addObject(new Pierre(16*110, 16*22, 1, map));
            addObject(new Pierre(16*130, 16*24, 1, map));
            addObject(new Pierre(16*7, 16*36, 2, map));
            addObject(new Pierre(16*7, 16*37, 2, map));
            addObject(new Pierre(16*8, 16*38, 2, map));
            addObject(new Pierre(16*10, 16*21, 2, map));
            addObject(new Pierre(16*32, 16*13, 2, map));
            addObject(new Pierre(16*52, 16*30, 2, map));
            addObject(new Pierre(16*67, 16*8, 2, map));
            addObject(new Pierre(16*106, 16*15, 2, map));
            addObject(new Pierre(16*114, 16*40, 2, map));
            addObject(new Pancarte(16*87, 16*13, 445, map));

            addEnnemi(new Ennemi077(19*16-13, 28*16-12));

            addEnnemi(new Ennemi041(27*16,6*16-8)); addEnnemi(new Ennemi041(65*16,14*16-8));
            addEnnemi(new Ennemi041(94*16,7*16-8)); addEnnemi(new Ennemi041(112*16,17*16-8));
            addEnnemi(new Ennemi041(52*16,34*16-8)); addEnnemi(new Ennemi041(89*16,37*16-8));
            break;
        case 8 :
            addObject(new Pierre(16*22, 16*26, 1, map));
            addObject(new Pierre(16*28, 16*4, 1, map));
            addObject(new Pierre(16*69, 16*30, 1, map));
            addObject(new Pierre(16*29, 16*30, 2, map));
            addObject(new Pierre(16*48, 16*7, 2, map));
            addObject(new Pierre(16*67, 16*18, 2, map));
            addObject(new Pierre(16*75, 16*38, 2, map));

            addObject(new Coffre(75 * 16, 20 * 16, 0, inventory->hasCristal(0), TI_CRISTAL, 0));

            addEnnemi(new Ennemi064(39*16-4, 20*16-4)); addEnnemi(new Ennemi064(18*16-4, 33*16-4));
            addEnnemi(new Ennemi064(55*16-4, 22*16-4)); addEnnemi(new Ennemi064(20*16-4, 22*16-4));
            break;
        case 9 :
            addObject(new Pierre(16*13, 16*56, 1, map));
            addObject(new Pierre(16*28, 16*44, 1, map));
            addObject(new Pierre(16*39, 16*17, 1, map));
            addObject(new Pierre(16*41, 16*30, 1, map));
            addObject(new Pierre(16*57, 16*3, 1, map));
            addObject(new Pierre(16*61, 16*40, 1, map));
            addObject(new Pierre(16*79, 16*31, 1, map));
            addObject(new Pierre(16*95, 16*8, 1, map));
            addObject(new Pierre(16*124, 16*49, 1, map));
            addObject(new Pierre(16*7, 16*37, 2, map));
            addObject(new Pierre(16*24, 16*57, 2, map));
            addObject(new Pierre(16*27, 16*54, 2, map));
            addObject(new Pierre(16*28, 16*54, 2, map));
            addObject(new Pierre(16*43, 16*52, 2, map));
            addObject(new Pierre(16*54, 16*21, 2, map));
            addObject(new Pierre(16*67, 16*56, 2, map));
            addObject(new Pierre(16*80, 16*14, 2, map));
            addObject(new Pierre(16*85, 16*3, 2, map));
            addObject(new Pierre(16*86, 16*3, 2, map));
            addObject(new Pierre(16*87, 16*54, 2, map));

            if (scene->getAvancement() == AV_GANON_SORTI) {
                addObject(new Pnj(16*135, 16*35, 90, 447));
                addObject(new Pnj(16*134, 16*38, 101, 447));
            }

            addObject(new Coffre(136 * 16, 22 * 16, 0, inventory->hasCristal(6), TI_CRISTAL, 6));

            addEnnemi(new Ennemi077(33*16-13, 38*16-12)); addEnnemi(new Ennemi077(38*16-13, 50*16-12));
            addEnnemi(new Ennemi077(49*16-13, 30*16-12)); addEnnemi(new Ennemi077(59*16-13, 55*16-12));
            addEnnemi(new Ennemi077(65*16-13, 42*16-12)); addEnnemi(new Ennemi077(86*16-13, 13*16-12));
            addEnnemi(new Ennemi077(99*16-13, 42*16-12)); addEnnemi(new Ennemi077(110*16-13, 23*16-12));
            break;
        case 10 :
            addObject(new Pierre(16*15, 16*25, 1, map));
            addObject(new Pierre(16*23, 16*72, 1, map));
            addObject(new Pierre(16*26, 16*43, 1, map));
            addObject(new Pierre(16*41, 16*39, 1, map));
            addObject(new Pierre(16*43, 16*14, 1, map));
            addObject(new Pierre(16*56, 16*16, 1, map));
            addObject(new Pierre(16*59, 16*29, 1, map));
            addObject(new Pierre(16*59, 16*69, 1, map));
            addObject(new Pierre(16*61, 16*53, 1, map));
            addObject(new Pierre(16*71, 16*44, 1, map));

            addObject(new Pierre(16*15, 16*12, 2, map));
            addObject(new Pierre(16*30, 16*18, 2, map));
            addObject(new Pierre(16*49, 16*55, 2, map));
            addObject(new Pierre(16*53, 16*7, 2, map));

            addObject(new Pancarte(16*40, 16*11, scene->getAvancement() < AV_GANON_CAPTURE ? 470 : 469, map));
            addObject(new Pancarte(16*54, 16*12, 450, map));
            addObject(new Pancarte(16*60, 16*59, 450, map));

            addObject(new Pnj(16*62 + 8, 16*40 + 5, 12, 471, W));
            if (inventory->hasGemmeForce(93)) {
                map->setSol(61*16, 42*16, 2173);
            } else {
                map->setSol(61*16, 42*16, 2600);
                map->setSol(61*16, 41*16, 2601);
            }

            addObject(new Pnj(16*49 + 8, 16*48 + 5, 19, 477));
            map->setSol(48*16, 50*16, 2602);
            map->setSol(48*16, 49*16, 2603);

            if (inventory->nbCristaux() >= 3 && inventory->getTrocGemme(3) >= TGV_BIERE && !inventory->hasCristal(3)) {
                addObject(new Pnj(43*16, 12*16, 37, 483, W));
                addObject(new Pnj(45*16, 8*16, 36, 484, W));
            } else {
                addObject(new Pnj(39*16, 31*16, 37, 479));
                addObject(new Pnj(55*16, 36*16, 36, 481));
            }
            break;
        case 11 :
            addObject(new Pierre(16*16, 16*56, 1, map));
            addObject(new Pierre(16*31, 16*72, 1, map));
            addObject(new Pierre(16*37, 16*46, 1, map));
            addObject(new Pierre(16*66, 16*44, 1, map));
            addObject(new Pierre(16*80, 16*19, 1, map));
            addObject(new Pierre(16*95, 16*72, 1, map));
            addObject(new Pierre(16*125, 16*14, 1, map));
            addObject(new Pierre(16*133, 16*72, 1, map));

            addObject(new Pierre(16*6, 16*67, 2, map));
            addObject(new Pierre(16*12, 16*13, 2, map));
            addObject(new Pierre(16*16, 16*31, 2, map));
            addObject(new Pierre(16*41, 16*66, 2, map));
            addObject(new Pierre(16*46, 16*25, 2, map));
            addObject(new Pierre(16*75, 16*38, 2, map));
            addObject(new Pierre(16*113, 16*67, 2, map));
            addObject(new Pierre(16*115, 16*31, 2, map));
            addObject(new Pierre(16*135, 16*8, 2, map));

            addObject(new Pancarte(16*77, 16*46, 494, map));

            addEnnemi(new Ennemi041(59*16,63*16-8)); addEnnemi(new Ennemi041(78*16,60*16-8));
            addEnnemi(new Ennemi041(120*16,68*16-8)); addEnnemi(new Ennemi041(121*16,38*16-8));
            addEnnemi(new Ennemi041(13*16,38*16-8));

            addEnnemi(new Ennemi077(119*16-13, 9*16-12)); addEnnemi(new Ennemi077(23*16-13, 8*16-12));
            addEnnemi(new Ennemi077(65*16-13, 10*16-12));
            break;
        case 12 :
            addObject(new Pierre(16*23, 16*45, 1, map));
            addObject(new Pierre(16*40, 16*21, 1, map));
            addObject(new Pierre(16*42, 16*66, 1, map));
            addObject(new Pierre(16*70, 16*33, 1, map));
            addObject(new Pierre(16*99, 16*30, 1, map));
            addObject(new Pierre(16*102, 16*57, 1, map));
            addObject(new Pierre(16*114, 16*33, 1, map));
            addObject(new Pierre(16*132, 16*72, 1, map));
            addObject(new Pierre(16*135, 16*56, 1, map));

            addObject(new Pierre(16*15, 16*66, 2, map));
            addObject(new Pierre(16*51, 16*45, 2, map));
            addObject(new Pierre(16*63, 16*9, 2, map));
            addObject(new Pierre(16*87, 16*68, 2, map));
            addObject(new Pierre(16*111, 16*72, 2, map));
            addObject(new Pierre(16*128, 16*12, 2, map));

            addObject(new Pancarte(16*10, 16*32, 495, map));

            addObject(new Coffre(101 * 16, 3 * 16, 0, inventory->hasCristal(1), TI_CRISTAL, 1));

            addEnnemi(new Ennemi041(108*16,24*16-8)); addEnnemi(new Ennemi041(109*16,62*16-8));

            addEnnemi(new Ennemi087(48*16+3,27*16-8)); addEnnemi(new Ennemi087(16*16+3,43*16-8));
            addEnnemi(new Ennemi087(33*16+3,57*16-8)); addEnnemi(new Ennemi087(55*16+3,51*16-8));
            addEnnemi(new Ennemi087(71*16+3,59*16-8)); addEnnemi(new Ennemi087(72*16+3,35*16-8));
            break;
        case 13 :
            addObject(new Pierre(16*3, 16*57, 1, map));
            addObject(new Pierre(16*20, 16*70, 1, map));
            addObject(new Pierre(16*28, 16*10, 1, map));
            addObject(new Pierre(16*63, 16*16, 1, map));
            addObject(new Pierre(16*70, 16*61, 1, map));

            addObject(new Pierre(16*7, 16*5, 2, map));
            addObject(new Pierre(16*9, 16*27, 2, map));
            addObject(new Pierre(16*58, 16*53, 2, map));
            addObject(new Pierre(16*73, 16*23, 2, map));

            addObject(new Pancarte(16*39, 16*7, 501, map));
            addObject(new Pancarte(16*46, 16*55, 502, map));

            addObject(new Pnj(16*34+8, 16*34+8, 41, 517));
            map->setSol(33*16, 36*16, 2777);
            map->setSol(33*16, 35*16, 2778);

            addObject(new Pnj(16*50+8, 16*44+9, 43, 520));
            map->setSol(49*16, 46*16, 2779);
            map->setSol(49*16, 45*16, 2780);

            addObject(new Pnj(16*17, 16*28, 33, 522));
            addObject(new Pnj(16*42+8, 16*30, 14, 523));
            break;
        case 14 :
            addObject(new Pierre(16*8, 16*51, 1, map));
            addObject(new Pierre(16*9, 16*61, 1, map));
            addObject(new Pierre(16*23, 16*28, 1, map));
            addObject(new Pierre(16*34, 16*17, 1, map));
            addObject(new Pierre(16*46, 16*12, 1, map));

            addObject(new Pierre(16*14, 16*37, 2, map));
            addObject(new Pierre(16*20, 16*13, 2, map));
            addObject(new Pierre(16*26, 16*39, 2, map));
            addObject(new Pierre(16*40, 16*28, 2, map));

            addObject(new Pancarte(16*37, 16*56, 524, map));

            addEnnemi(new Ennemi077(16*16-13, 64*16-12)); addEnnemi(new Ennemi077(33*16-13, 38*16-12));
            break;
        case 15 :
            addObject(new Pierre(16*9, 16*39, 1, map));
            addObject(new Pierre(16*20, 16*46, 1, map));
            addObject(new Pierre(16*26, 16*27, 1, map));
            addObject(new Pierre(16*42, 16*23, 1, map));
            addObject(new Pierre(16*52, 16*30, 1, map));
            addObject(new Pierre(16*71, 16*18, 1, map));
            addObject(new Pierre(16*71, 16*45, 1, map));
            addObject(new Pierre(16*87, 16*33, 1, map));
            addObject(new Pierre(16*97, 16*29, 1, map));
            addObject(new Pierre(16*98, 16*40, 1, map));

            addObject(new Pierre(16*6, 16*9, 2, map));
            addObject(new Pierre(16*16, 16*28, 2, map));
            addObject(new Pierre(16*35, 16*39, 2, map));
            addObject(new Pierre(16*68, 16*30, 2, map));
            addObject(new Pierre(16*118, 16*49, 2, map));

            addObject(new Pancarte(16*125, 16*40, 545, map));

            if (scene->getCoffre(0, 6)) {
                ouvrePorte(120, 33, 0);
            }

            addObject(new Coffre(59 * 16, 48 * 16, 0, inventory->hasCristal(5), TI_CRISTAL, 5));

            addObject(new Pnj(16*117+8, 16*6+7, 74, 547));
            addObject(new Pnj(16*102, 16*4, 75, 546));
            addObject(new Pnj(16*114, 16*12, inventory->getTrocGemme(1) >= TGB_HACHE ? 77 : 76, 546));

            addEnnemi(new Ennemi042(105*16-5,45*16-3)); addEnnemi(new Ennemi042(86*16-5,25*16-3));
            addEnnemi(new Ennemi042(50*16-5,36*16-3)); addEnnemi(new Ennemi042(28*16-5,45*16-3));
            addEnnemi(new Ennemi042(25*16-5,21*16-3)); addEnnemi(new Ennemi042(52*16-5,18*16-3));
            addEnnemi(new Ennemi042(58*16-5,43*16-3));
            break;
        case 16 :
            addObject(new Pierre(16*3, 16*45, 1, map));
            addObject(new Pierre(16*5, 16*17, 1, map));
            addObject(new Pierre(16*23, 16*47, 1, map));
            addObject(new Pierre(16*24, 16*48, 1, map));
            addObject(new Pierre(16*24, 16*49, 1, map));
            addObject(new Pierre(16*24, 16*50, 1, map));
            addObject(new Pierre(16*23, 16*51, 1, map));
            addObject(new Pierre(16*27, 16*24, 1, map));
            addObject(new Pierre(16*27, 16*34, 1, map));
            addObject(new Pierre(16*33, 16*36, 1, map));
            addObject(new Pierre(16*34, 16*30, 1, map));
            addObject(new Pierre(16*40, 16*53, 1, map));
            addObject(new Pierre(16*41, 16*22, 1, map));
            addObject(new Pierre(16*42, 16*21, 1, map));
            addObject(new Pierre(16*43, 16*22, 1, map));
            addObject(new Pierre(16*51, 16*40, 1, map));
            addObject(new Pierre(16*58, 16*37, 1, map));
            addObject(new Pierre(16*67, 16*51, 1, map));
            addObject(new Pierre(16*69, 16*25, 1, map));
            addObject(new Pierre(16*3, 16*25, 2, map));
            addObject(new Pierre(16*11, 16*54, 2, map));
            addObject(new Pierre(16*14, 16*43, 2, map));
            addObject(new Pierre(16*15, 16*42, 2, map));
            addObject(new Pierre(16*20, 16*10, 2, map));
            addObject(new Pierre(16*24, 16*44, 2, map));
            addObject(new Pierre(16*55, 16*53, 1, map));
            addObject(new Pancarte(16*38, 16*43, 228, map));
            addObject(new Pancarte(16*49, 16*3, 229, map));
            addObject(new Pancarte(16*76, 16*39, 230, map));

            if (!inventory->hasQuartCoeur(0)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 57*16+8, 6*16+8, 0));
            }

            if (!inventory->hasGemmeForce(3)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 26*16, 4*16 + 8, 3, false));
            }

            if (scene->getAvancement() < AV_PARLE_ZELDA_PALAIS) {
                addObject(new Pnj(41*16+5, 42*16+5, 46, 231));
            } else if (link->getEpee() > 0 || inventory->hasObject(OCARINA)) {
                addEnnemi(new Ennemi003(53*16+2, 46*16-1));
                addEnnemi(new Ennemi003(23*16+2, 27*16-1));
                addEnnemi(new Ennemi003(48*16+2, 15*16-1));

                addEnnemi(new Ennemi004(71*16, 45*16-1));
                addEnnemi(new Ennemi004(53*16, 29*16-1));
                addEnnemi(new Ennemi004(32*16, 14*16-1));
                addEnnemi(new Ennemi004(9*16, 17*16-1));
                addEnnemi(new Ennemi004(9*16, 42*16-1));
                addEnnemi(new Ennemi004(28*16, 48*16-1));
                addEnnemi(new Ennemi004(38*16, 51*16-1));
            }
            break;
        case 17 :
            addObject(new Pierre(16*4, 16*52, 1, map));
            addObject(new Pierre(16*18, 16*5, 1, map));
            addObject(new Pierre(16*50, 16*6, 1, map));
            addObject(new Pierre(16*34, 16*13, 2, map));
            addObject(new Pierre(16*57, 16*13, 2, map));
            addObject(new Pancarte(16*4, 16*39, 250, map));
            addObject(new Pancarte(16*56, 16*28, 251, map));

            if (!inventory->hasGemmeForce(11)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 16*16, 6*16 + 8, 11, false));
            }

            if (link->getEpee() > 0 || inventory->hasObject(OCARINA)) {
                addEnnemi(new Ennemi053(16*16, 30*16));
                addEnnemi(new Ennemi053(18*16, 45*16));
                addEnnemi(new Ennemi053(23*16, 12*16));
                addEnnemi(new Ennemi053(36*16, 10*16));
                addEnnemi(new Ennemi053(42*16, 36*16));
                addEnnemi(new Ennemi053(46*16, 26*16));
                addEnnemi(new Ennemi053(52*16, 13*16));
                addEnnemi(new Ennemi053(51*16, 39*16));

                addEnnemi(new Ennemi054(8*16, 31*16, S));
                addEnnemi(new Ennemi054(37*16, 25*16, S));
                addEnnemi(new Ennemi054(24*16, 48*16, S));
            }
            break;
        case 18 :
            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PONT_CONSTRUIT) {
                ouvrePorte(66, 0, 0);
            }
            addObject(new Pierre(16*46, 16*14, 1, map));
            addObject(new Pancarte(16*44, 16*8, 252, map));

            if (link->getEpee() > 0 || inventory->hasObject(OCARINA)) {
                if (inventory->hasObject(SAC_TROC)
                    && (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_UTILISE || scene->getAvancement()>= AV_PORTAIL_PRE_PRESENT_FERME)) {
                    addObject(new Poule(16*25, 16*58));
                    addObject(new Poule(16*30, 16*57));
                    addObject(new Poule(16*26, 16*61));
                    addObject(new Poule(16*33, 16*62));
                    addObject(new Poule(16*29, 16*59));

                    addObject(new Pnj(27*16+8, 57*16+6, 10, 257));
                    addObject(new Pnj(56*16+8, 67*16+8, 11, 258));
                    addObject(new Pnj(21*16+8, 83*16+7, 1, 259));
                    addObject(new Pnj(39*16+8, 33*16+8, 36, 260));
                    addObject(new Pnj(43*16+8, 51*16+2, 35, 261));
                    addObject(new Pnj(3*16+5, 64*16+5+8, 57, 262, E));
                    addObject(new Pnj(3*16+5, 59*16+5, 57, 263, E));
                    addObject(new Pnj(53*16+8, 72*16+7, 34, 264));
                    addObject(new Pnj(75*16+5, 59*16+5, 57, 265, W));
                    addObject(new Pnj(75*16+5, 64*16+5+8, 57, 266, W));
                    addObject(new Pnj(36*16+5, 85*16+5, 57, 267, N));
                    addObject(new Pnj(42*16+5, 85*16+5, 57, 269, N));
                    addEffect(new Zzzzz(43*16+5, 85*16));

                    if (!inventory->hasObject(TROC_GEMME_VERTE) || inventory->getTrocGemme(3) < TGV_BALAIS) {
                        addObject(new Pnj(33*16+8, 75*16+6, 9, 270));
                    }

                    addObject(new Pnj(16*32 + 8, 16*30 + 5, 7, 280));
                    map->setSol(31*16, 31*16, inventory->getTroc(TT_ROUAGE) == -1 ? 1961 :
                                inventory->hasQuartCoeur(2) ? 1959 : 1960);
                    addObject(new Pnj(16*46 + 8, 16*30 + 6, 2, 286));
                    map->setSol(45*16, 31*16, link->getStatus()->getMaxRupees() == 999 ? 1959 :
                                link->getStatus()->getMaxRupees() == 500 ? 1964 :
                                link->getStatus()->getMaxRupees() == 200 ? 1963 : 1962);
                    addObject(new Pnj(16*32 + 8, 16*37 + 4, 20, 295));
                    map->setSol(31*16, 38*16, 1965);
                    addObject(new Pnj(16*46 + 8, 16*37 + 6, 45, 299));
                    map->setSol(45*16, 38*16, 1966);
                    addObject(new Pnj(16*32 + 8, 16*44 + 9, 24, 302));
                    map->setSol(31*16, 45*16, 1967);
                    addObject(new Pnj(16*46 + 8, 16*44 + 5, 12, 305));
                    map->setSol(45*16, 45*16, 1968);
                }
            } else {
                addObject(new Pnj(15*16+5, 61*16+5, 46, 254));
                addObject(new Pnj(15*16+5, 77*16+5, 46, 254));
                addObject(new Pnj(29*16+5, 77*16+5, 46, 254));
                addObject(new Pnj(49*16+5, 77*16+5, 46, 254));
                addObject(new Pnj(63*16+5, 77*16+5, 46, 254));
                addObject(new Pnj(49*16+5, 61*16+5, 46, 254));
                addObject(new Pnj(63*16+5, 61*16+5, 46, 254));
                addObject(new Pnj(17*16+5, 40*16+5, 46, 254));
                addObject(new Pnj(63*16+5, 34*16+5, 46, 254));
                addObject(new Pnj(63*16+5, 45*16+5, 46, 254));
                addObject(new Pnj(39*16+5, 7*16+5, 58, 255));
                addObject(new Pnj(3*16+5, 59*16+5, 57, 256));
                addObject(new Pnj(3*16+5, 64*16+5+8, 57, 256, N));
                addObject(new Pnj(38*16+5, 87*16+5, 57, 256, N));
                addObject(new Pnj(40*16+5, 87*16+5, 57, 256, N));
                addObject(new Pnj(77*16+5, 61*16+5, 57, 256, W));
                addObject(new Pnj(77*16+5, 63*16+5, 57, 256, W));
            }
            break;
        case 19 :
            addObject(new Pierre(16*9, 16*27, 1, map));
            addObject(new Pierre(16*32, 16*21, 1, map));
            addObject(new Pierre(16*59, 16*5, 1, map));
            addObject(new Pierre(16*70, 16*54, 1, map));
            addObject(new Pierre(16*16, 16*5, 2, map));
            addObject(new Pierre(16*70, 16*10, 2, map));
            addObject(new Pancarte(16*44, 16*6, 400, map));
            addObject(new Pancarte(16*45, 16*50, 399, map));

            if (link->getEpee() < 5) {
                addObject(new Pnj(37*16+5, 43*16+5, 58, 401));
                addObject(new Pnj(41*16+5, 43*16+5, 58, 402));
            }
            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                addObject(new Pnj(61*16+5, 30*16+5, 68, 269));
                addEffect(new Zzzzz(62*16+5, 30*16));
                addObject(new Pnj(52*16+5, 48*16+5, 68, 269));
                addEffect(new Zzzzz(53*16+5, 48*16));
            }
            break;
        case 20 :
            addObject(new Pierre(16*10, 16*16, 1, map));
            addObject(new Pierre(16*18, 16*5, 1, map));
            addObject(new Pierre(16*26, 16*46, 1, map));
            addObject(new Pierre(16*27, 16*82, 1, map));
            addObject(new Pierre(16*28, 16*83, 1, map));
            addObject(new Pierre(16*44, 16*79, 1, map));
            addObject(new Pierre(16*44, 16*4, 2, map));
            addObject(new Pierre(16*56, 16*57, 2, map));
            addObject(new Pancarte(16*13, 16*38, 410, map));
            addObject(new Pancarte(16*28, 16*6, 411, map));
            addObject(new Pancarte(16*55, 16*26, 412, map));

            if ((link->getEpee() > 0 && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_UTILISE)
                || scene->getAvancement()>= AV_PORTAIL_PRE_PRESENT_FERME) {
                addEnnemi(new Ennemi053(16*16, 52*16));
                addEnnemi(new Ennemi053(10*16, 77*16));
                addEnnemi(new Ennemi053(39*16, 75*16));
                addEnnemi(new Ennemi053(34*16, 60*16));
                addEnnemi(new Ennemi053(53*16, 43*16));
                addEnnemi(new Ennemi053(53*16, 20*16));
                addEnnemi(new Ennemi053(35*16, 31*16));
                addEnnemi(new Ennemi053(23*16, 8*16));
                addEnnemi(new Ennemi053(14*16, 34*16));

                addEnnemi(new Ennemi054(17*16, 22*16, S));
                addEnnemi(new Ennemi054(45*16, 9*16, N));
                addEnnemi(new Ennemi054(40*16, 40*16, S));
                addEnnemi(new Ennemi054(24*16, 47*16, S));
                addEnnemi(new Ennemi054(50*16, 66*16, N));
                addEnnemi(new Ennemi054(26*16, 80*16, S));
            }

            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                addObject(new Pnj(25*16+5, 13*16+5, 68, 269)); addEffect(new Zzzzz(26*16+5, 13*16));
                addObject(new Pnj(17*16+5, 59*16+5, 68, 269)); addEffect(new Zzzzz(18*16+5, 59*16));
                addObject(new Pnj(27*16+5, 79*16+5, 68, 269)); addEffect(new Zzzzz(28*16+5, 79*16));
                addObject(new Pnj(41*16+5, 36*16+5, 68, 269)); addEffect(new Zzzzz(42*16+5, 36*16));
                addObject(new Pnj(19*16+5, 28*16+5, 68, 269)); addEffect(new Zzzzz(20*16+5, 28*16));
                addObject(new Pnj(9*16+5, 85*16+5, 68, 269)); addEffect(new Zzzzz(10*16+5, 85*16));
                addObject(new Pnj(7*16+5, 84*16+5, 68, 269)); addEffect(new Zzzzz(8*16+5, 84*16));
            }
            break;
        case 21 :
            addObject(new Pierre(16*24, 16*71, 1, map));
            addObject(new Pierre(16*32, 16*11, 1, map));
            addObject(new Pierre(16*45, 16*17, 1, map));
            addObject(new Pierre(16*46, 16*18, 1, map));
            addObject(new Pierre(16*50, 16*55, 1, map));
            addObject(new Pierre(16*61, 16*85, 1, map));
            addObject(new Pierre(16*73, 16*63, 1, map));
            addObject(new Pierre(16*54, 16*23, 2, map));

            if (scene->getCoffre(0, 2)) {
                map->setSol(13*16, 62*16, 8, 9, 0, HERBE);
                for (int j = 0; j < 9; j++) {
                    for (int i = 0; i < 8; i++) {
                        map->setAir((13 + i) * 16, (62 + j) * 16, -1);
                    }
                }
            }

            if (!inventory->hasQuartCoeur(7)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 77*16+8, 76*16+8, 7));
            }

            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                addObject(new Pnj(44*16+5, 2*16+5, 68, 269)); addEffect(new Zzzzz(45*16+5, 2*16));
                addObject(new Pnj(27*16+5, 11*16+5-8, 68, 269)); addEffect(new Zzzzz(28*16+5, 11*16-8));
                addObject(new Pnj(33*16+5-8, 31*16+5, 68, 269)); addEffect(new Zzzzz(34*16+5-8, 31*16));
                addObject(new Pnj(15*16+5, 11*16+5-8, 68, 269)); addEffect(new Zzzzz(16*16+5, 11*16-8));
                addObject(new Pnj(9*16+5, 8*16+5, 68, 269)); addEffect(new Zzzzz(10*16+5, 8*16));
                addObject(new Pnj(8*16+5-8, 31*16+5, 68, 269)); addEffect(new Zzzzz(9*16+5-8, 31*16));
            } else if (scene->getAvancement() >= AV_STELE_LUE) {
                addEnnemi(new Ennemi004(9*16, 51*16-1)); addEnnemi(new Ennemi004(4*16, 60*16-1));
                addEnnemi(new Ennemi004(22*16, 46*16-1)); addEnnemi(new Ennemi004(25*16, 52*16-1));
                addEnnemi(new Ennemi004(14*16, 35*16-1)); addEnnemi(new Ennemi004(7*16, 16*16-1));
                addEnnemi(new Ennemi004(20*16, 25*16-1)); addEnnemi(new Ennemi004(41*16, 12*16-1));
                addEnnemi(new Ennemi004(61*16, 45*16-1)); addEnnemi(new Ennemi004(54*16, 54*16-1));
                addEnnemi(new Ennemi004(61*16, 62*16-1)); addEnnemi(new Ennemi004(53*16, 83*16-1));
                addEnnemi(new Ennemi004(38*16, 73*16-1)); addEnnemi(new Ennemi004(32*16, 67*16-1));
                addEnnemi(new Ennemi004(41*16, 46*16-1)); addEnnemi(new Ennemi004(50*16, 32*16-1));
                addEnnemi(new Ennemi004(74*16, 30*16-1)); addEnnemi(new Ennemi004(34*16, 34*16-1));
                addEnnemi(new Ennemi004(42*16, 21*16-1)); addEnnemi(new Ennemi004(47*16, 59*16-1));

                addEnnemi(new Ennemi054(69*16, 16*16, N)); addEnnemi(new Ennemi054(37*16, 25*16, N));
                addEnnemi(new Ennemi054(69*16, 60*16, S)); addEnnemi(new Ennemi054(49*16, 72*16, S));
                addEnnemi(new Ennemi054(12*16, 62*16, S)); addEnnemi(new Ennemi054(45*16, 83*16, N));
                addEnnemi(new Ennemi054(75*16, 72*16, S)); addEnnemi(new Ennemi054(13*16, 82*16, S));
                addEnnemi(new Ennemi054(6*16, 73*16, S)); addEnnemi(new Ennemi054(21*16, 78*16, S));
                addEnnemi(new Ennemi054(4*16, 85*16, S)); addEnnemi(new Ennemi054(11*16, 40*16, S));
                addEnnemi(new Ennemi054(45*16, 65*16, S)); addEnnemi(new Ennemi054(68*16, 49*16, S));
                addEnnemi(new Ennemi054(50*16, 14*16, S)); addEnnemi(new Ennemi054(59*16, 23*16, S));
            }
            break;
        case 22 :
            addObject(new Pierre(16*7, 16*36, 1, map));
            addObject(new Pierre(16*7, 16*37, 1, map));
            addObject(new Pierre(16*8, 16*38, 1, map));
            addObject(new Pierre(16*16, 16*35, 1, map));
            addObject(new Pierre(16*19, 16*13, 1, map));
            addObject(new Pierre(16*26, 16*3, 1, map));
            addObject(new Pierre(16*53, 16*3, 1, map));
            addObject(new Pierre(16*89, 16*17, 1, map));
            addObject(new Pierre(16*92, 16*40, 1, map));
            addObject(new Pierre(16*106, 16*13, 1, map));
            addObject(new Pierre(16*44, 16*37, 2, map));
            addObject(new Pierre(16*67, 16*8, 2, map));
            addObject(new Pierre(16*134, 16*23, 2, map));
            addObject(new Pancarte(16*87, 16*13, 431, map));
            addObject(new Pancarte(16*114, 16*20, 432, map));

            if (!inventory->hasQuartCoeur(8)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 132*16+8, 20*16+8, 8));
            }

            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                addObject(new Pnj(9*16+5-8, 36*16+5+2, 68, 269)); addEffect(new Zzzzz(10*16+5-8, 36*16+2));
                addObject(new Pnj(21*16+5, 12*16+5, 68, 269)); addEffect(new Zzzzz(22*16+5, 12*16));
                addObject(new Pnj(36*16+5, 4*16+5-8, 68, 269)); addEffect(new Zzzzz(37*16+5, 4*16-8));
                addObject(new Pnj(49*16+5, 9*16+5, 68, 269)); addEffect(new Zzzzz(50*16+5, 9*16));
                addObject(new Pnj(56*16+5, 29*16+5, 68, 269)); addEffect(new Zzzzz(57*16+5, 29*16));

                if (scene->getAvancement() < AV_PLANCHES_TROUVEES) {
                    addItem(ItemHelper::getInstance()->createItem(TI_PLANCHES, 23*16, 28*16));
                }

            } else {
                if (inventory->getTroc(TT_ROUAGE) == 0) {
                    map->setSol(24*16, 14*16, 1, 1, 2389, PIERRE);
                    map->setSol(25*16, 14*16, 6, 1, 2390, PIERRE);
                    map->setSol(31*16, 14*16, 1, 1, 2391, PIERRE);
                    map->setSol(24*16, 15*16, 1, 8, 2417, PIERRE);
                    map->setSol(25*16, 15*16, 6, 8, 2418, PIERRE);
                    map->setSol(31*16, 15*16, 1, 8, 2419, PIERRE);
                    for (int i = 0; i < 9; i++) map->setMur(24*16, (14 + i) *16, MUR, PIERRE, MUR, PIERRE);
                    for (int i = 0; i < 9; i++) map->setMur(31*16, (14 + i) *16, PIERRE, MUR, PIERRE, MUR);
                }
                addObject(new Pnj(124*16, 8*16, 71, 433));

                Ennemi010* enn = new Ennemi010(119*16,7*16); enn->cachette(); addEnnemi(enn);
                enn = new Ennemi010(119*16,9*16); enn->cachette(); addEnnemi(enn);
                enn = new Ennemi010(123*16,12*16); enn->cachette(); addEnnemi(enn);
                enn = new Ennemi010(126*16,12*16); enn->cachette(); addEnnemi(enn);

                addEnnemi(new Ennemi027(29*16,3*16-1)); addEnnemi(new Ennemi027(53*16,12*16-1));
                addEnnemi(new Ennemi027(76*16,16*16-1));

                addEnnemi(new Ennemi053(27*16, 27*16)); addEnnemi(new Ennemi053(94*16, 38*16));
                addEnnemi(new Ennemi053(59*16, 39*16)); addEnnemi(new Ennemi053(54*16, 31*16));

                addEnnemi(new Ennemi054(108*16, 39*16, N)); addEnnemi(new Ennemi054(124*16, 32*16, N));
                addEnnemi(new Ennemi054(79*16, 37*16, S)); addEnnemi(new Ennemi054(94*16, 15*16, N));
            }
            break;
        case 23 :
            addObject(new Pierre(16*48, 16*30, 1, map));
            addObject(new Pierre(16*62, 16*30, 1, map));
            addObject(new Pierre(16*63, 16*30, 1, map));

            if (scene->getCoffre(0, 4)) {
                ouvrePorte(58, 18, 0);
            }

            addEnnemi(new Ennemi012(17*16,8*16)); addEnnemi(new Ennemi012(62*16,8*16));
            addEnnemi(new Ennemi012(16*16,24*16));
            break;
        case 24 :
            addObject(new Pierre(16*13, 16*56, 1, map));
            addObject(new Pierre(16*24, 16*57, 1, map));
            addObject(new Pierre(16*25, 16*38, 1, map));
            addObject(new Pierre(16*27, 16*54, 1, map));
            addObject(new Pierre(16*28, 16*54, 1, map));
            addObject(new Pierre(16*39, 16*17, 1, map));
            addObject(new Pierre(16*45, 16*33, 1, map));
            addObject(new Pierre(16*51, 16*49, 1, map));
            addObject(new Pierre(16*67, 16*56, 1, map));
            addObject(new Pierre(16*80, 16*25, 1, map));
            addObject(new Pierre(16*87, 16*54, 1, map));
            addObject(new Pierre(16*95, 16*8, 1, map));
            addObject(new Pierre(16*101, 16*29, 1, map));
            addObject(new Pierre(16*114, 16*5, 1, map));
            addObject(new Pierre(16*7, 16*28, 2, map));
            addObject(new Pierre(16*54, 16*21, 2, map));
            addObject(new Pierre(16*63, 16*38, 2, map));
            addObject(new Pierre(16*84, 16*2, 2, map));
            addObject(new Pierre(16*85, 16*3, 2, map));
            addObject(new Pierre(16*86, 16*3, 2, map));
            addObject(new Pierre(16*87, 16*2, 2, map));
            addObject(new Pancarte(16*5, 16*30, 251, map));
            addObject(new Pancarte(16*114, 16*55, 446, map));

            addObject(new Sphere(6*16, 17*16));
            addObject(new Pnj(8*16+5, 15*16+5, 68, 269)); addEffect(new Zzzzz(9*16+5, 15*16));

            addEnnemi(new Ennemi008(48*16, 32*16)); addEnnemi(new Ennemi008(34*16, 50*16));
            addEnnemi(new Ennemi008(64*16, 44*16)); addEnnemi(new Ennemi008(97*16, 28*16));

            addEnnemi(new Ennemi053(27*16, 35*16)); addEnnemi(new Ennemi053(21*16, 9*16));
            addEnnemi(new Ennemi053(45*16, 10*16)); addEnnemi(new Ennemi053(98*16, 7*16));
            addEnnemi(new Ennemi053(113*16, 22*16)); addEnnemi(new Ennemi053(83*16, 25*16));
            addEnnemi(new Ennemi053(49*16, 46*16)); addEnnemi(new Ennemi053(90*16, 39*16));
            addEnnemi(new Ennemi053(116*16, 51*16));

            addEnnemi(new Ennemi054(65*16, 31*16, S)); addEnnemi(new Ennemi054(92*16, 22*16, N));
            addEnnemi(new Ennemi054(80*16, 10*16, S)); addEnnemi(new Ennemi054(34*16, 11*16, S));
            addEnnemi(new Ennemi054(54*16, 6*16, S)); addEnnemi(new Ennemi054(104*16, 17*16, S));
            addEnnemi(new Ennemi054(104*16, 43*16, N)); addEnnemi(new Ennemi054(74*16, 54*16, S));
            addEnnemi(new Ennemi054(115*16, 8*16, N)); addEnnemi(new Ennemi054(95*16, 53*16, N));
            addEnnemi(new Ennemi054(41*16, 55*16, N));
            break;
        case 25 :
            addObject(new Pierre(16*6, 16*37, 1, map));
            addObject(new Pierre(16*24, 16*72, 1, map));
            addObject(new Pierre(16*30, 16*43, 1, map));
            addObject(new Pierre(16*31, 16*43, 1, map));
            addObject(new Pierre(16*67, 16*11, 1, map));

            addObject(new Pierre(16*14, 16*22, 2, map));
            addObject(new Pierre(16*63, 16*70, 2, map));

            addObject(new Pancarte(16*14, 16*28, 450, map));
            addObject(new Pancarte(16*54, 16*12, 450, map));
            addObject(new Pancarte(16*60, 16*59, 450, map));

            addObject(new Pnj(16*56 + 8, 16*19 + 4, 20, 451));
            map->setSol(55*16, 20*16, 2581);

            addObject(new Pnj(16*56 + 8, 16*26 + 5, 7, 454));
            map->setSol(55*16, 27*16, 2582);

            addObject(new Pnj(16*62 + 8, 16*40 + 6, 45, 456));
            map->setSol(61*16, 41*16, 2583);

            addObject(new Pnj(16*49 + 8, 16*48 + 9, 24, 458));
            map->setSol(48*16, 49*16, 2584);

            addObject(new Pnj(16*41, 16*31, 52, 460));
            addObject(new Pnj(16*56, 16*40, 69, 465));

            addObject(new Animal(11 * 16, 55 * 16, 5)); addObject(new Animal(32 * 16, 52 * 16, 5));
            addObject(new Animal(37 * 16, 18 * 16, 5)); addObject(new Animal(65 * 16, 28 * 16, 5));
            addObject(new Animal(42 * 16, 41 * 16, 5)); addObject(new Animal(64 * 16, 57 * 16, 5));
            addObject(new Animal(61 * 16, 23 * 16, 5)); addObject(new Animal(49 * 16, 34 * 16, 5));
            addObject(new Animal(8 * 16, 31 * 16, 5)); addObject(new Animal(51 * 16, 61 * 16, 5));
            break;
        case 26 :
            addObject(new Pierre(16*3, 16*13, 1, map));
            addObject(new Pierre(16*16, 16*31, 1, map));
            addObject(new Pierre(16*23, 16*72, 1, map));
            addObject(new Pierre(16*32, 16*52, 1, map));
            addObject(new Pierre(16*33, 16*52, 1, map));
            addObject(new Pierre(16*38, 16*4, 1, map));
            addObject(new Pierre(16*39, 16*5, 1, map));
            addObject(new Pierre(16*40, 16*5, 1, map));
            addObject(new Pierre(16*41, 16*4, 1, map));
            addObject(new Pierre(16*46, 16*31, 1, map));
            addObject(new Pierre(16*85, 16*72, 1, map));
            addObject(new Pierre(16*86, 16*5, 1, map));
            addObject(new Pierre(16*93, 16*19, 1, map));
            addObject(new Pierre(16*126, 16*32, 1, map));
            addObject(new Pierre(16*133, 16*72, 1, map));
            addObject(new Pierre(16*134, 16*24, 1, map));

            addObject(new Pierre(16*27, 16*4, 2, map));
            addObject(new Pierre(16*61, 16*68, 2, map));
            addObject(new Pierre(16*135, 16*8, 2, map));

            addObject(new Pancarte(16*43, 16*5, 251, map));
            addObject(new Pancarte(16*77, 16*46, 485, map));
            addObject(new Pancarte(16*116, 16*39, 486, map));

            if (!inventory->hasGemmeForce(96)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 91*16, 7*16 + 8, 96, false));
            }

            addEnnemi(new Ennemi008(113*16, 10*16));

            addEnnemi(new Ennemi009(13*16,35*16+8)); addEnnemi(new Ennemi009(23*16,70*16+8));
            addEnnemi(new Ennemi009(116*16,69*16+8)); addEnnemi(new Ennemi009(62*16,61*16+8));
            addEnnemi(new Ennemi009(69*16,42*16+8));

            addEnnemi(new Ennemi010(97*16,42*16)); addEnnemi(new Ennemi010(52*16,46*16));
            addEnnemi(new Ennemi010(31*16,30*16)); addEnnemi(new Ennemi010(71*16,27*16));

            addEnnemi(new Ennemi053(22*16, 10*16)); addEnnemi(new Ennemi053(45*16, 12*16));
            addEnnemi(new Ennemi053(74*16, 8*16)); addEnnemi(new Ennemi053(86*16, 17*16));
            addEnnemi(new Ennemi053(129*16, 13*16));

            addEnnemi(new Ennemi054(124*16, 4*16, N)); addEnnemi(new Ennemi054(118*16, 17*16, S));
            addEnnemi(new Ennemi054(56*16, 71*16, N)); addEnnemi(new Ennemi054(80*16, 69*16, S));

            if (inventory->hasObject(ENCYCLOPEDIE_POISSONS)) {
                // barque
                if (!inventory->hasObject(PALMES)) {
                    map->barque();
                }
                addObject(new Pnj(16*121, 16*40+3, 73, 488));
            } else {
                addObject(new Pnj(16*118+8, 16*45+3+8, 73, 487));
            }
            break;
        case 27 :
            addObject(new Pierre(16*3, 16*33, 1, map));
            addObject(new Pierre(16*22, 16*52, 1, map));
            addObject(new Pierre(16*33, 16*14, 1, map));
            addObject(new Pierre(16*41, 16*41, 1, map));
            addObject(new Pierre(16*48, 16*25, 1, map));
            addObject(new Pierre(16*51, 16*49, 1, map));
            addObject(new Pierre(16*58, 16*32, 1, map));
            addObject(new Pierre(16*70, 16*55, 1, map));
            addObject(new Pierre(16*78, 16*13, 1, map));
            addObject(new Pierre(16*99, 16*45, 1, map));
            addObject(new Pierre(16*112, 16*11, 1, map));
            addObject(new Pierre(16*124, 16*29, 1, map));
            addObject(new Pierre(16*135, 16*56, 1, map));

            addObject(new Pierre(16*20, 16*66, 2, map));
            addObject(new Pierre(16*42, 16*25, 2, map));
            addObject(new Pierre(16*61, 16*16, 2, map));
            addObject(new Pierre(16*66, 16*5, 2, map));
            addObject(new Pierre(16*68, 16*32, 2, map));
            addObject(new Pierre(16*70, 16*68, 2, map));
            addObject(new Pierre(16*99, 16*28, 2, map));
            addObject(new Pierre(16*111, 16*72, 2, map));

            addObject(new Pancarte(16*10, 16*32, 495, map));
            addObject(new Pancarte(16*16, 16*63, 496, map));
            addObject(new Pancarte(16*46, 16*6, 497, map));
            addObject(new Pancarte(16*65, 16*65, 499, map));
            addObject(new Pancarte(16*85, 16*8, 500, map));
            addObject(new Pancarte(16*86, 16*65, 498, map));

            addEnnemi(new Ennemi007(17*16, 37*16)); addEnnemi(new Ennemi007(31*16, 58*16));
            addEnnemi(new Ennemi007(56*16, 20*16)); addEnnemi(new Ennemi007(75*16, 53*16));
            addEnnemi(new Ennemi007(31*16, 19*16));

            addEnnemi(new Ennemi009(123*16,69*16+8)); addEnnemi(new Ennemi009(102*16,32*16+8));

            addEnnemi(new Ennemi013(12*16,47*16-4)); addEnnemi(new Ennemi013(43*16,15*16-4));
            addEnnemi(new Ennemi013(69*16,45*16-4)); addEnnemi(new Ennemi013(43*16,61*16-4));

            addEnnemi(new Ennemi014(26*16-12,44*16)); addEnnemi(new Ennemi014(67*16-12,59*16));
            addEnnemi(new Ennemi014(72*16-12,16*16)); addEnnemi(new Ennemi014(51*16-12,31*16));
            break;
        case 28 :
            addObject(new Pierre(16*6, 16*65, 1, map));
            addObject(new Pierre(16*9, 16*44, 1, map));
            addObject(new Pierre(16*20, 16*70, 1, map));
            addObject(new Pierre(16*24, 16*57, 1, map));
            addObject(new Pierre(16*31, 16*12, 1, map));
            addObject(new Pierre(16*50, 16*53, 1, map));
            addObject(new Pierre(16*64, 16*65, 1, map));
            addObject(new Pierre(16*69, 16*51, 1, map));
            addObject(new Pierre(16*73, 16*41, 1, map));

            addObject(new Pierre(16*27, 16*56, 2, map));
            addObject(new Pierre(16*36, 16*49, 2, map));
            addObject(new Pierre(16*69, 16*10, 2, map));

            addObject(new Pancarte(16*39, 16*7, 501, map));
            addObject(new Pancarte(16*46, 16*55, 502, map));

            addObject(new Pnj(16*34 + 8, 16*34 + 5, 12, 503));
            map->setSol(33*16, 35*16, inventory->hasObject(BOTTES) ? 2772 : 2773);

            addObject(new Pnj(16*50 + 8, 16*34 + 4, 20, 506));
            map->setSol(49*16, 35*16, 2774);

            addObject(new Pnj(16*34 + 8, 16*44 + 6, 2, 509));
            map->setSol(33*16, 45*16, 2775);

            addObject(new Pnj(16*50 + 8, 16*44 + 5, 7, 511));
            map->setSol(49*16, 45*16, 2776);

            addObject(new Pnj(16*13, 16*24, 13, 513));
            addObject(new Pnj(16*68, 16*32, 23, 514));
            addObject(new Pnj(16*42, 16*33, 1, 515));
            break;
        case 29 :
            addObject(new Pierre(16*14, 16*69, 1, map));
            addObject(new Pierre(16*20, 16*25, 1, map));
            addObject(new Pierre(16*23, 16*54, 1, map));
            addObject(new Pierre(16*26, 16*36, 1, map));
            addObject(new Pierre(16*39, 16*39, 1, map));
            addObject(new Pierre(16*46, 16*12, 1, map));
            addObject(new Pierre(16*54, 16*29, 1, map));

            addObject(new Pierre(16*14, 16*37, 2, map));
            addObject(new Pierre(16*33, 16*55, 2, map));
            addObject(new Pierre(16*34, 16*56, 2, map));
            addObject(new Pierre(16*35, 16*56, 2, map));
            addObject(new Pierre(16*36, 16*17, 2, map));
            addObject(new Pierre(16*36, 16*55, 2, map));
            addObject(new Pierre(16*40, 16*65, 2, map));
            addObject(new Pierre(16*49, 16*9, 2, map));

            addObject(new Pancarte(16*37, 16*56, 524, map));

            if (!inventory->hasQuartCoeur(13)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 40*16, 71*16, 13));
            }

            addEnnemi(new Ennemi008(19*16, 61*16));

            addEnnemi(new Ennemi053(39*16, 41*16));

            addEnnemi(new Ennemi054(11*16, 47*16, S)); addEnnemi(new Ennemi054(17*16, 24*16, S));
            addEnnemi(new Ennemi054(34*16, 9*16, N));
            break;
        case 30 :
            addObject(new Pierre(16*9, 16*39, 1, map));
            addObject(new Pierre(16*25, 16*31, 1, map));
            addObject(new Pierre(16*32, 16*42, 1, map));
            addObject(new Pierre(16*58, 16*38, 1, map));
            addObject(new Pierre(16*72, 16*42, 1, map));
            addObject(new Pierre(16*77, 16*35, 1, map));
            addObject(new Pierre(16*97, 16*29, 1, map));

            addObject(new Pierre(16*13, 16*28, 2, map));
            addObject(new Pierre(16*28, 16*23, 2, map));
            addObject(new Pierre(16*29, 16*52, 2, map));
            addObject(new Pierre(16*37, 16*39, 2, map));
            addObject(new Pierre(16*65, 16*31, 2, map));
            addObject(new Pierre(16*101, 16*41, 2, map));

            addObject(new Pancarte(16*24, 16*43, 525, map));
            addObject(new Pancarte(16*126, 16*43, 526, map));

            addObject(new Pnj(16*9+8, 16*8, 21, 527));

            addEnnemi(new Ennemi005(87*16,22*16-10)); addEnnemi(new Ennemi005(61*16,22*16-10));
            addEnnemi(new Ennemi005(31*16,49*16-10)); addEnnemi(new Ennemi005(62*16,43*16-10));
            addEnnemi(new Ennemi005(96*16,41*16-10)); addEnnemi(new Ennemi005(32*16,28*16-10));

            addEnnemi(new Ennemi006(50*16,35*16-21)); addEnnemi(new Ennemi006(23*16,21*16-21));
            addEnnemi(new Ennemi006(75*16+8,30*16-21)); addEnnemi(new Ennemi006(28*16+8,36*16-21));
            addEnnemi(new Ennemi006(49*16,46*16-21));
            break;
        case 31 :
            addObject(new Pierre(16*3, 16*25, 3, map));
            addObject(new Pierre(16*3, 16*48, 3, map));
            addObject(new Pierre(16*11, 16*14, 3, map));
            addObject(new Pierre(16*27, 16*34, 3, map));
            addObject(new Pierre(16*35, 16*12, 3, map));
            addObject(new Pierre(16*45, 16*6, 3, map));
            addObject(new Pierre(16*51, 16*40, 3, map));
            addObject(new Pierre(16*58, 16*37, 3, map));
            addObject(new Pierre(16*65, 16*36, 3, map));
            addObject(new Pierre(16*67, 16*51, 3, map));
            addObject(new Pierre(16*69, 16*25, 3, map));
            addObject(new Pierre(16*15, 16*41, 4, map));
            addObject(new Pierre(16*32, 16*8, 4, map));
            addObject(new Pierre(16*46, 16*36, 4, map));
            addObject(new Pierre(16*51, 16*54, 4, map));

            if (!inventory->hasQuartCoeur(1)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 11*16+8, 5*16+8, 1));
            }

            addEnnemi(new Ennemi011(9*16,2*16));

            addEnnemi(new Ennemi032(9*16,41*16-7)); addEnnemi(new Ennemi032(11*16,17*16-7));
            addEnnemi(new Ennemi032(27*16,28*16-7)); addEnnemi(new Ennemi032(29*16,50*16-7));
            addEnnemi(new Ennemi032(47*16,50*16-7)); addEnnemi(new Ennemi032(48*16,12*16-7));
            addEnnemi(new Ennemi032(55*16,28*16-7)); addEnnemi(new Ennemi032(68*16,10*16-7));
            addEnnemi(new Ennemi032(70*16,46*16-7)); addEnnemi(new Ennemi032(36*16,16*16-7));
            addEnnemi(new Ennemi032(8*16,53*16-7));
            break;
        case 32 :
            addObject(new Pierre(16*9, 16*54, 3, map));
            addObject(new Pierre(16*25, 16*42, 3, map));
            addObject(new Pierre(16*44, 16*41, 3, map));
            addObject(new Pierre(16*48, 16*25, 3, map));
            addObject(new Pierre(16*57, 16*3, 3, map));
            addObject(new Pierre(16*18, 16*5, 4, map));
            addObject(new Pierre(16*57, 16*21, 4, map));

            addEnnemi(new Ennemi011(33*16,10*16));

            addEnnemi(new Ennemi032(15*16,7*16-7)); addEnnemi(new Ennemi032(19*16,28*16-7));
            addEnnemi(new Ennemi032(40*16,27*16-7)); addEnnemi(new Ennemi032(52*16,8*16-7));

            addEnnemi(new Ennemi055(27*16+5,12*16)); addEnnemi(new Ennemi055(9*16+5,28*16));
            addEnnemi(new Ennemi055(21*16+5,45*16)); addEnnemi(new Ennemi055(43*16+5,37*16));
            addEnnemi(new Ennemi055(56*16+5,18*16));
            break;
        case 33 :
            addObject(new Pierre(16*33, 16*14, 3, map));
            addObject(new Pierre(16*65, 16*14, 3, map));
            addObject(new Pancarte(16*44, 16*8, 336, map));

            if (!inventory->hasQuartCoeur(3)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 28*16+8, 60*16+8, 3));
            }

            if (!inventory->hasGemmeForce(19)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 54*16, 43*16 + 8, 19, false));
            }
            if (!inventory->hasGemmeForce(25)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 40*16, 50*16 + 8, 25, false));
            }

            addObject(new Poule(16*25, 16*58, 1));
            addObject(new Poule(16*30, 16*57, 1));
            addObject(new Poule(16*26, 16*61, 1));
            addObject(new Poule(16*33, 16*62, 1));
            addObject(new Poule(16*29, 16*59, 1));

            addObject(new Pnj(54*16, 68*16-4, 61, 364));
            addObject(new Pnj(16*23, 16*51, 3, 365));
            addObject(new Pnj(16*64, 16*83-1, 4, 366));
            addObject(new Pnj(16*40+2, 16*36, 5, 368));
            addObject(new Pnj(16*22, 16*67, 6, 369));


            if (!inventory->hasObject(PERLE)) {
                addObject(new Pnj(16*32 + 8, 16*30 + 5, 7, 337));
                map->setSol(31*16, 31*16, 2090);
        } else {
                addObject(new Pnj(32*16+8, 30*16+11, 53, 337));
                map->setSol(31*16, 31*16, 2089);
            }

            addObject(new Pnj(46*16+8, 30*16+11, 30, 340));
            map->setSol(45*16, 31*16, link->getStatus()->getMaxGanonOr() == 999 ? 2089 :
                                link->getStatus()->getMaxGanonOr() == 500 ? 2093 :
                                link->getStatus()->getMaxGanonOr() == 200 ? 2092 : 2091);

            addObject(new Pnj(32*16+8, 37*16+11, 49, 349));
            map->setSol(31*16, 38*16, inventory->getTroc(TT_ROUE) == -1 ? 2094 : link->getInventory()->hasObject(BOMBES) ? 2089 : 2098);

            addObject(new Pnj(46*16+8, 37*16+11, 27, 355));
            map->setSol(45*16, 38*16, 2095);

            addObject(new Pnj(32*16+8, 44*16+11, 59, 358));
            map->setSol(31*16, 45*16, 2096);

            addObject(new Pnj(46*16+8, 44*16+11, 31, 361));
            map->setSol(45*16, 45*16, 2097);

            break;
        case 34 :
            addObject(new Pierre(16*28, 16*9, 3, map));
            addObject(new Pierre(16*29, 16*54, 3, map));
            addObject(new Pierre(16*73, 16*10, 3, map));
            addObject(new Pierre(16*4, 16*21, 4, map));
            addObject(new Pierre(16*54, 16*37, 4, map));
            addObject(new Pierre(16*70, 16*54, 4, map));
            addObject(new Pierre(16*76, 16*26, 4, map));
            addObject(new Pancarte(16*44, 16*6, 400, map));
            addObject(new Pancarte(16*45, 16*50, 403, map));
            if (scene->getAvancement() >= AV_GARDES_F_ACHETES) {
                addObject(new Pnj(37*16+5, 43*16+5, 65, 406));
                addObject(new Pnj(41*16+5, 43*16+5, 65, 406));
            } else {
                addObject(new Pnj(38*16+5, 43*16+5, 65, 404));
                addObject(new Pnj(40*16+5, 43*16+5, 65, 404));
            }
            break;
        case 35 :
            addObject(new Pierre(16*26, 16*5, 3, map));
            addObject(new Pierre(16*26, 16*46, 3, map));
            addObject(new Pierre(16*44, 16*4, 3, map));
            addObject(new Pierre(16*56, 16*12, 3, map));
            addObject(new Pierre(16*56, 16*57, 3, map));
            addObject(new Pierre(16*9, 16*51, 4, map));
            addObject(new Pierre(16*14, 16*39, 4, map));
            addObject(new Pierre(16*33, 16*79, 4, map));

            if (!inventory->hasGemmeForce(39)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 30*16, 61*16 + 8, 39, false));
            }

            addEnnemi(new Ennemi011(8*16,86*16));

            if (inventory->hasObject(PERLE)) {
                addEnnemi(new Ennemi032(12*16,36*16-7));
                addEnnemi(new Ennemi032(30*16,6*16-7));
                addEnnemi(new Ennemi032(35*16,34*16-7));
                addEnnemi(new Ennemi032(49*16,11*16-7));
                addEnnemi(new Ennemi032(8*16,79*16-7));
                addEnnemi(new Ennemi032(51*16,71*16-7));
                addEnnemi(new Ennemi032(27*16,79*16-7));

                addEnnemi(new Ennemi055(17*16+5,15*16));
                addEnnemi(new Ennemi055(53*16+5,49*16));
                addEnnemi(new Ennemi055(38*16+5,65*16));
                addEnnemi(new Ennemi055(25*16+5,51*16));
            }
            break;
        case 36 :
            addObject(new Pierre(16*10, 16*4, 3, map));
            addObject(new Pierre(16*25, 16*12, 3, map));
            addObject(new Pierre(16*31, 16*68, 3, map));
            addObject(new Pierre(16*46, 16*25, 3, map));
            addObject(new Pierre(16*32, 16*11, 4, map));
            addObject(new Pierre(16*32, 16*37, 4, map));
            addObject(new Pierre(16*37, 16*45, 4, map));
            addObject(new Pierre(16*67, 16*19, 4, map));
            addObject(new Pierre(16*77, 16*76, 4, map));

            if (!inventory->hasGemmeForce(47)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 18*16, 65*16 + 8, 47, false));
            }

            addEnnemi(new Ennemi011(23*16,65*16));

            if (inventory->hasObject(PERLE)) {
                addEnnemi(new Ennemi032(8*16,22*16-7)); addEnnemi(new Ennemi032(54*16,65*16-7));
                addEnnemi(new Ennemi032(40*16,65*16-7)); addEnnemi(new Ennemi032(13*16,78*16-7));
                addEnnemi(new Ennemi032(10*16,51*16-7)); addEnnemi(new Ennemi032(38*16,43*16-7));
                addEnnemi(new Ennemi032(54*16,16*16-7));

                addEnnemi(new Ennemi037(30*16, 13*16-10)); addEnnemi(new Ennemi037(61*16, 46*16-10));
                addEnnemi(new Ennemi037(56*16, 82*16-10)); addEnnemi(new Ennemi037(21*16, 84*16-10));
                addEnnemi(new Ennemi037(22*16, 45*16-10)); addEnnemi(new Ennemi037(40*16, 20*16-10));
            }
            break;
        case 37 :
            addObject(new Pierre(16*10, 16*21, 3, map));
            addObject(new Pierre(16*34, 16*38, 3, map));
            addObject(new Pierre(16*59, 16*17, 3, map));
            addObject(new Pierre(16*62, 16*30, 3, map));
            addObject(new Pierre(16*98, 16*3, 3, map));
            addObject(new Pierre(16*127, 16*34, 3, map));
            addObject(new Pierre(16*134, 16*23, 3, map));

            addObject(new Pierre(16*35, 16*3, 4, map));
            addObject(new Pierre(16*67, 16*8, 4, map));
            addObject(new Pierre(16*109, 16*41, 4, map));
            addObject(new Pierre(16*119, 16*13, 4, map));


            if (scene->getCoffre(0, 3)) {
                ouvrePorte(88, 10, 0);
            }

            if (!inventory->hasQuartCoeur(9)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 84*16+8, 4*16, 9));
            }

            addEnnemi(new Ennemi011(17*16,35*16));

            addEnnemi(new Ennemi032(26*16,5*16-7)); addEnnemi(new Ennemi032(90*16,15*16-7));
            addEnnemi(new Ennemi032(61*16,15*16-7)); addEnnemi(new Ennemi032(51*16,34*16-7));
            addEnnemi(new Ennemi032(123*16,36*16-7));

            addEnnemi(new Ennemi084(50*16, 4*16, N)); addEnnemi(new Ennemi084(79*16, 37*16, S));
            addEnnemi(new Ennemi084(33*16, 29*16, S)); addEnnemi(new Ennemi084(78*16, 14*16, N));
            addEnnemi(new Ennemi084(107*16, 20*16, N));
            break;
        case 38 :
            addObject(new Pierre(16*32, 16*26, 3, map));
            addObject(new Pierre(16*65, 16*26, 3, map));
            addObject(new Pierre(16*69, 16*30, 3, map));
            addObject(new Pierre(16*49, 16*30, 4, map));
            addObject(new Pierre(16*66, 16*17, 4, map));
            addObject(new Pierre(16*71, 16*38, 4, map));

            addEnnemi(new Ennemi011(48*16,4*16));

            if (inventory->hasObject(PERLE)) {
                addEnnemi(new Ennemi056(17*16-1,8*16-1)); addEnnemi(new Ennemi056(62*16-1,8*16-1));
                addEnnemi(new Ennemi056(16*16-1,24*16-1)); addEnnemi(new Ennemi056(46*16-1,19*16-1));
                addEnnemi(new Ennemi056(61*16-1,23*16-1));
            }
            break;
        case 39 :
            addObject(new Pierre(16*2, 16*25, 3, map));
            addObject(new Pierre(16*27, 16*44, 3, map));
            addObject(new Pierre(16*30, 16*30, 3, map));
            addObject(new Pierre(16*32, 16*15, 3, map));
            addObject(new Pierre(16*51, 16*30, 3, map));
            addObject(new Pierre(16*54, 16*56, 3, map));
            addObject(new Pierre(16*65, 16*36, 3, map));
            addObject(new Pierre(16*80, 16*14, 3, map));
            addObject(new Pierre(16*102, 16*4, 3, map));
            addObject(new Pierre(16*116, 16*47, 3, map));
            addObject(new Pierre(16*13, 16*56, 4, map));
            addObject(new Pierre(16*41, 16*49, 4, map));
            addObject(new Pierre(16*61, 16*3, 4, map));
            addObject(new Pierre(16*122, 16*26, 4, map));

            addEnnemi(new Ennemi011(69*16,51*16));

            addEnnemi(new Ennemi032(113*16,51*16-7)); addEnnemi(new Ennemi032(99*16,30*16-7));
            addEnnemi(new Ennemi032(99*16,6*16-7)); addEnnemi(new Ennemi032(53*16,30*16-7));
            addEnnemi(new Ennemi032(21*16,10*16-7)); addEnnemi(new Ennemi032(40*16,11*16-7));
            addEnnemi(new Ennemi032(30*16,49*16-7)); addEnnemi(new Ennemi032(29*16,28*16-7));

            addEnnemi(new Ennemi055(38*16+5,38*16)); addEnnemi(new Ennemi055(59*16+5,46*16));
            addEnnemi(new Ennemi055(96*16+5,44*16)); addEnnemi(new Ennemi055(87*16+5,23*16));
            addEnnemi(new Ennemi055(113*16+5,22*16));
            break;
        case 40 :
            addObject(new Pierre(16*15, 16*12, 3, map));
            addObject(new Pierre(16*24, 16*72, 3, map));
            addObject(new Pierre(16*45, 16*14, 3, map));
            addObject(new Pierre(16*48, 16*63, 3, map));
            addObject(new Pierre(16*59, 16*69, 3, map));
            addObject(new Pierre(16*38, 16*28, 4, map));
            addObject(new Pierre(16*56, 16*9, 4, map));
            addObject(new Pancarte(16*54, 16*12, 468, map));

            if (!inventory->hasGemmeForce(87)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 12*16, 14*16 + 8, 87, false));
            }

            addEnnemi(new Ennemi011(40*16,41*16)); addEnnemi(new Ennemi011(62*16,26*16));
            addEnnemi(new Ennemi011(69*16,44*16));

            addEnnemi(new Ennemi056(35*16-1,31*16-1)); addEnnemi(new Ennemi056(60*16-1,47*16-1));
            addEnnemi(new Ennemi056(55*16-1,23*16-1));
            break;
        case 41 :
            addObject(new Pierre(16*24, 16*13, 3, map));
            addObject(new Pierre(16*28, 16*52, 3, map));
            addObject(new Pierre(16*45, 16*4, 3, map));
            addObject(new Pierre(16*83, 16*72, 3, map));
            addObject(new Pierre(16*93, 16*19, 3, map));
            addObject(new Pierre(16*104, 16*67, 3, map));
            addObject(new Pierre(16*126, 16*32, 3, map));

            addObject(new Pierre(16*16, 16*31, 4, map));
            addObject(new Pierre(16*55, 16*25, 4, map));
            addObject(new Pierre(16*60, 16*13, 4, map));
            addObject(new Pierre(16*79, 16*49, 4, map));
            addObject(new Pierre(16*135, 16*8, 4, map));

            addObject(new Pancarte(16*77, 16*46, 493, map));

            if (!inventory->hasQuartCoeur(10)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 105*16+8, 23*16+8, 10));
            }

            if (!inventory->hasGemmeForce(100)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 34*16, 46*16 + 8, 100, false));
            }

            addEnnemi(new Ennemi011(115*16,14*16));

            if (inventory->hasObject(PERLE)) {
                addEnnemi(new Ennemi032(82*16,61*16-7)); addEnnemi(new Ennemi032(60*16,66*16-7));
                addEnnemi(new Ennemi032(13*16,37*16-7));

                addEnnemi(new Ennemi055(63*16+5,10*16)); addEnnemi(new Ennemi055(27*16+5,7*16));
                addEnnemi(new Ennemi055(120*16+5,68*16)); addEnnemi(new Ennemi055(12*16+5,69*16));
                addEnnemi(new Ennemi055(123*16+5,10*16));

                addEnnemi(new Ennemi086(97*16,44*16)); addEnnemi(new Ennemi086(51*16,46*16));
                addEnnemi(new Ennemi086(28*16,29*16)); addEnnemi(new Ennemi086(130*16,55*16));
            }
            break;
        case 42 :
            addObject(new Pierre(16*41, 16*41, 5, map));
            addObject(new Pierre(16*43, 16*23, 5, map));
            addObject(new Pierre(16*58, 16*32, 5, map));
            addObject(new Pierre(16*66, 16*53, 5, map));
            addObject(new Pierre(16*106, 16*65, 3, map));
            addObject(new Pierre(16*124, 16*29, 3, map));
            addObject(new Pierre(16*128, 16*12, 3, map));
            addObject(new Pierre(16*135, 16*56, 3, map));

            addObject(new Pierre(16*22, 16*51, 6, map));
            addObject(new Pierre(16*45, 16*66, 6, map));
            addObject(new Pierre(16*52, 16*5, 6, map));
            addObject(new Pierre(16*68, 16*32, 6, map));
            addObject(new Pierre(16*78, 16*18, 6, map));
            addObject(new Pierre(16*86, 16*6, 4, map));
            addObject(new Pierre(16*114, 16*21, 4, map));
            addObject(new Pierre(16*128, 16*72, 4, map));

            addObject(new Pancarte(16*10, 16*32, 495, map));

            if (!inventory->hasQuartCoeur(11)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 10*16+8, 71*16+8, 11));
            }

            if (!inventory->hasQuartCoeur(12)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 132*16+8, 49*16+8, 12));
            }

            addEnnemi(new Ennemi011(99*16,29*16));

            addEnnemi(new Ennemi015(17*16+4,41*16)); addEnnemi(new Ennemi015(31*16+4,57*16));
            addEnnemi(new Ennemi015(39*16+4,21*16)); addEnnemi(new Ennemi015(70*16+4,57*16));
            addEnnemi(new Ennemi015(62*16+4,12*16)); addEnnemi(new Ennemi015(57*16+4,37*16));

            addEnnemi(new Ennemi055(120*16+5,67*16)); addEnnemi(new Ennemi055(107*16+5,24*16));
            break;
        case 43 :
            addObject(new Pierre(16*4, 16*32, 3, map));
            addObject(new Pierre(16*9, 16*51, 3, map));
            addObject(new Pierre(16*27, 16*53, 3, map));
            addObject(new Pierre(16*33, 16*5, 3, map));
            addObject(new Pierre(16*63, 16*16, 3, map));
            addObject(new Pierre(16*64, 16*65, 3, map));

            addObject(new Pierre(16*6, 16*65, 4, map));
            addObject(new Pierre(16*9, 16*10, 4, map));
            addObject(new Pierre(16*49, 16*53, 4, map));
            addObject(new Pierre(16*70, 16*61, 4, map));
            addObject(new Pierre(16*73, 16*27, 4, map));

            addObject(new Pancarte(16*39, 16*7, 501, map));
            addObject(new Pancarte(16*46, 16*55, 502, map));

            addEnnemi(new Ennemi011(69*16,47*16));

            addEnnemi(new Ennemi056(16*16-1,20*16-1)); addEnnemi(new Ennemi056(27*16-1,40*16-1));
            addEnnemi(new Ennemi056(45*16-1,31*16-1)); addEnnemi(new Ennemi056(65*16-1,55*16-1));
            break;
        case 44 :
            addObject(new Pierre(16*7, 16*61, 3, map));
            addObject(new Pierre(16*26, 16*31, 3, map));
            addObject(new Pierre(16*54, 16*51, 3, map));

            addObject(new Pierre(16*14, 16*69, 4, map));
            addObject(new Pierre(16*20, 16*13, 4, map));
            addObject(new Pierre(16*43, 16*21, 4, map));

            addObject(new Pancarte(16*37, 16*56, 524, map));

            if (!inventory->hasObject(FLECHE_FEU) || !inventory->hasObject(FLECHE_GLACE)
                || !inventory->hasObject(FLECHE_LUMIERE) || !inventory->hasObject(FLACON_4)) {
                ouvrePorte(31, 28, 1);
            }

            addEnnemi(new Ennemi011(46*16,17*16));

            addEnnemi(new Ennemi032(51*16,20*16-7)); addEnnemi(new Ennemi032(36*16,40*16-7));

            addEnnemi(new Ennemi055(19*16+5,61*16));
            break;
        case 45 :
            addObject(new Pierre(16*13, 16*28, 3, map));
            addObject(new Pierre(16*23, 16*28, 3, map));
            addObject(new Pierre(16*52, 16*30, 3, map));
            addObject(new Pierre(16*71, 16*27, 3, map));

            addObject(new Pierre(16*26, 16*27, 4, map));
            addObject(new Pierre(16*97, 16*29, 4, map));
            addObject(new Pierre(16*97, 16*46, 4, map));

            addObject(new Pancarte(16*112, 16*13, 536, map));

            if (inventory->totalGemmeForce() < 200) {
                ouvrePorte(108, 4, 0); // ferme donjon
            }

            if (!inventory->hasGemmeForce(138)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 82*16, 24*16 + 8, 138, false));
            }

            addEnnemi(new Ennemi011(121*16,54*16));

            addEnnemi(new Ennemi015(53*16+4,35*16)); addEnnemi(new Ennemi015(26*16+4,20*16));
            addEnnemi(new Ennemi015(88*16+4,21*16)); addEnnemi(new Ennemi015(92*16+4,40*16));
            addEnnemi(new Ennemi015(111*16+4,45*16)); addEnnemi(new Ennemi015(59*16+4,21*16));

            addEnnemi(new Ennemi044(32*16-3,28*16-10)); addEnnemi(new Ennemi044(73*16-3,31*16-10));
            addEnnemi(new Ennemi044(121*16-3,48*16-10)); addEnnemi(new Ennemi044(22*16-3,36*16-10));

            addObject(new Pnj(9*16+8, 8*16+8, 63, 537));
            break;
        case 46 :
            //mini boss
            if (!scene->getCoffre(1,25)) {
                addEnnemi(new Ennemi091(9*16+5, 38*16, true));
            } else {
                ouvrePorte(18, 36, 1);
            }
            //boss
            if (!inventory->hasCoeur(0)) {
                addEnnemi(new Ennemi092(349*16-52, 17*16-8));
            }
            if (!inventory->hasMedaillon(0)) {
                addItem(ItemHelper::getInstance()->createItem(TI_MEDAILLON_1, 250*16, 5*16+8));
            }

            addObject(new Coffre(70 * 16, 51 * 16, 0, scene->getCoffre(1, 0), TI_CARTE_DONJON));
            addObject(new Coffre(229 * 16 + 8, 34 * 16, 0, scene->getCoffre(1, 1), TI_BOUSSOLE));
            addObject(new Coffre(270 * 16, 6 * 16, 0, scene->getCoffre(1, 2), TI_CLE_BOSS));

            if (scene->getCoffre(1, 2) == 2) ouvrePorte(249, 28, 0);

            addObject(new Coffre(28 * 16 + 8, 36 * 16 + 8, 1, link->getInventory()->hasObject(ARC), TI_ARC));

            addObject(new Coffre(70 * 16, 36 * 16, 0, scene->getCoffre(1, 4), TI_CLE, 4));
            addObject(new Coffre(189 * 16 + 8, 6 * 16, 0, scene->getCoffre(1, 5), TI_CLE, 5));
            addObject(new Coffre(268 * 16, 20 * 16, 0, scene->getCoffre(1, 7), TI_CLE, 7));
            addObject(new Coffre(309 * 16 + 8, 20 * 16, 0, scene->getCoffre(1, 8), TI_CLE, 8));

            if (scene->getCoffre(1, 9)) ouvrePorte(89, 43, 0);
            if (scene->getCoffre(1, 10)) ouvrePorte(98, 6, 1);
            if (scene->getCoffre(1, 11)) ouvrePorte(129, 13, 0);
            if (scene->getCoffre(1, 12)) ouvrePorte(218, 6, 1);
            if (scene->getCoffre(1, 13)) ouvrePorte(278, 6, 1);
            if (scene->getCoffre(1, 14)) ouvrePorte(29, 28, 0);
            if (scene->getCoffre(1, 15)) ouvrePorte(29, 43, 0);
            if (scene->getCoffre(1, 16)) ouvrePorte(69, 13, 0);
            if (scene->getCoffre(1, 17)) ouvrePorte(69, 43, 0);
            if (scene->getCoffre(1, 18)) ouvrePorte(98, 21, 1);
            if (scene->getCoffre(1, 19)) ouvrePorte(109, 43, 0);
            if (scene->getCoffre(1, 20)) ouvrePorte(138, 6, 1);
            if (scene->getCoffre(1, 21)) ouvrePorte(169, 28, 0);
            if (scene->getCoffre(1, 22)) ouvrePorte(209, 43, 0);
            if (scene->getCoffre(1, 23)) ouvrePorte(298, 36, 1);
            if (scene->getCoffre(1, 24)) ouvrePorte(298, 21, 1);

            addObject(new Interrupteur(33*16, 34*16, 0, scene->getCoffre(1, 14), map));
            addObject(new Interrupteur(33*16, 40*16, 0, scene->getCoffre(1, 15), map));
            addObject(new Interrupteur(73*16, 11*16, 0, scene->getCoffre(1, 16), map));
            addObject(new Interrupteur(64*16, 37*16, 0, scene->getCoffre(1, 17), map));
            addObject(new Interrupteur(104*16, 26*16, 0, scene->getCoffre(1, 18), map));
            addObject(new Interrupteur(113*16, 41*16, 0, scene->getCoffre(1, 19), map));
            addObject(new Interrupteur(123*16, 7*16, 0, scene->getCoffre(1, 20), map));
            addObject(new Interrupteur(166*16, 34*16, 0, scene->getCoffre(1, 21), map));
            addObject(new Interrupteur(212*16, 41*16, 0, scene->getCoffre(1, 22), map));
            addObject(new Interrupteur(310*16, 40*16, 0, scene->getCoffre(1, 23), map));
            addObject(new Interrupteur(304*16, 17*16, 0, scene->getCoffre(1, 24), map));

            addObject(new Interrupteur(4*16, 42*16, 0, true, map));
            addObject(new Interrupteur(357*16, 27*16, 0, true, map));

            addObject(new Caisse(70*16, 52*16, 1));

            addEnnemi(new Ennemi001(169*16+8,21*16+6)); addEnnemi(new Ennemi001(209*16,5*16+6));
            addEnnemi(new Ennemi001(26*16,4*16+6));addEnnemi(new Ennemi001(33*16,4*16+6));
            addEnnemi(new Ennemi001(73*16,21*16+6));addEnnemi(new Ennemi001(131*16,5*16+6));
            addEnnemi(new Ennemi001(200*16,36*16+6)); addEnnemi(new Ennemi001(277*16,23*16+6));
            addEnnemi(new Ennemi001(287*16,34*16+6)); addEnnemi(new Ennemi001(249*16,35*16+6));
            addEnnemi(new Ennemi001(270*16,8*16+6));

            addEnnemi(new Ennemi004(129*16+8, 56*16-1)); addEnnemi(new Ennemi004(29*16, 52*16-1));
            addEnnemi(new Ennemi004(106*16, 51*16-1)); addEnnemi(new Ennemi004(113*16, 51*16-1));
            addEnnemi(new Ennemi004(184*16+8, 47*16-1)); addEnnemi(new Ennemi004(315*16, 7*16-1));
            addEnnemi(new Ennemi004(227*16, 22*16-1));

            addEnnemi(new Ennemi018(287*16,3*16+2)); addEnnemi(new Ennemi018(287*16,11*16+2));
            addEnnemi(new Ennemi018(128*16,27*16+2)); addEnnemi(new Ennemi018(70*16,35*16+2));
            addEnnemi(new Ennemi018(125*16,48*16+2)); addEnnemi(new Ennemi018(134*16,48*16+2));
            addEnnemi(new Ennemi018(189*16+8,5*16+2)); addEnnemi(new Ennemi018(265*16,48*16+2));
            addEnnemi(new Ennemi018(294*16,48*16+2)); addEnnemi(new Ennemi018(309*16+8,19*16+2));
            addEnnemi(new Ennemi018(278*16,43*16+2)); addEnnemi(new Ennemi018(268*16,19*16+2));

            addEnnemi(new Ennemi053(67*16, 51*16)); addEnnemi(new Ennemi053(70*16, 54*16));
            addEnnemi(new Ennemi053(72*16, 50*16)); addEnnemi(new Ennemi053(90*16, 36*16));
            addEnnemi(new Ennemi053(124*16, 19*16)); addEnnemi(new Ennemi053(117*16, 36*16));
            addEnnemi(new Ennemi053(106*16, 30*16)); addEnnemi(new Ennemi053(226*16, 51*16));
            addEnnemi(new Ennemi053(45*16, 13*16)); addEnnemi(new Ennemi053(90*16, 22*16));
            addEnnemi(new Ennemi053(136*16, 32*16)); addEnnemi(new Ennemi053(163*16, 4*16));
            addEnnemi(new Ennemi053(176*16, 4*16)); addEnnemi(new Ennemi053(185*16, 33*16));
            addEnnemi(new Ennemi053(205*16, 20*16)); addEnnemi(new Ennemi053(197*16, 24*16));
            addEnnemi(new Ennemi053(306*16, 23*16)); addEnnemi(new Ennemi053(313*16, 23*16));
            addEnnemi(new Ennemi053(293*16, 26*16));

            addObject(new PiegePics(34*16, 49*16, S)); addObject(new PiegePics(38*16, 49*16, S));
            addObject(new PiegePics(42*16, 49*16, S)); addObject(new PiegePics(46*16, 49*16, S));
            addObject(new PiegePics(190*16, 53*16, S)); addObject(new PiegePics(201*16, 53*16, S));
            addObject(new PiegePics(196*16, 51*16, S)); addObject(new PiegePics(305*16, 32*16, S));
            addObject(new PiegePics(308*16, 32*16, S)); addObject(new PiegePics(305*16, 51*16, S));
            addObject(new PiegePics(51*16, 7*16, S)); addObject(new PiegePics(52*16, 7*16, S));

            addObject(new PiegeLong(6*16, 25*16, S)); addObject(new PiegeLong(166*16, 40*16, S));
            addObject(new PiegeLong(106*16, 2*16, S)); addObject(new PiegeLong(48*16, 18*16, S));

            addObject(new Jarre(4*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 42*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 34*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 40*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(44*16, 2*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(46*16, 2*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(120*16, 17*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(121*16, 17*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(125*16, 34*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(125*16, 35*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(165*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(166*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(201*16, 19*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(202*16, 19*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(206*16, 47*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(244*16, 40*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(253*16, 19*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(295*16, 29*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(315*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(348*16, 22*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(351*16, 22*16, 0, TI_PETIT_COEUR, map));

            addObject(new Jarre(47*16, 2*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(122*16, 17*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(167*16, 55*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(246*16, 40*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(295*16, 31*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(315*16, 34*16, 0, TI_RUBIS_VERT, map));

            addObject(new Jarre(246*16, 19*16, 0, TI_FLECHE, map));

            addObject(new Jarre(45*16, 2*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(203*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(207*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(213*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(245*16, 40*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(279*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(280*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(295*16, 28*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(295*16, 30*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(305*16, 53*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(315*16, 33*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(342*16, 22*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(345*16, 22*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(354*16, 22*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(357*16, 22*16, 0, TI_NO_ITEM, map));
            break;
        case 47 :
            //mini boss
            if (scene->getCoffre(2,20)) {
                addObject(new Pnj(326*16, 54*16+8, 71, 1247));
                ouvrePorte(329, 58, 0);
            } else {
                addEnnemi(new Ennemi093(326*16, 54*16+8));
            }
            //boss
            if (!inventory->hasCoeur(1)) {
                addEnnemi(new Ennemi094(349*16, 34*16));
            }
            if (!inventory->hasMedaillon(1)) {
                addItem(ItemHelper::getInstance()->createItem(TI_MEDAILLON_2, 350*16, 20*16+8));
            }

            addObject(new Coffre(307 * 16, 81 * 16, 0, scene->getCoffre(2, 0), TI_CARTE_DONJON));
            addObject(new Coffre(269 * 16 + 8, 51 * 16, 0, scene->getCoffre(2, 1), TI_BOUSSOLE));
            addObject(new Coffre(299 * 16, 44 * 16, 0, scene->getCoffre(2, 2), TI_CLE_BOSS));

            if (scene->getCoffre(2, 2) == 2) ouvrePorte(349, 43, 0);

            if (link->getInventory()->hasObject(GANTS)) addObject(new Coffre(322 * 16, 62 * 16 + 8, 1, true, TI_NO_ITEM));

            if (scene->getCoffre(2, 4)) ouvrePorte(178, 21, 1);
            if (scene->getCoffre(2, 10)) ouvrePorte(129, 73, 0);
            if (scene->getCoffre(2, 11)) ouvrePorte(149, 73, 0);
            if (scene->getCoffre(2, 12)) ouvrePorte(189, 13, 0);
            if (scene->getCoffre(2, 13)) ouvrePorte(209, 43, 0);
            if (scene->getCoffre(2, 14)) ouvrePorte(258, 6, 1);
            if (scene->getCoffre(2, 15)) ouvrePorte(329, 28, 0);
            if (scene->getCoffre(2, 16)) ouvrePorte(289, 28, 0);
            if (scene->getCoffre(2, 17)) ouvrePorte(318, 36, 1);
            if (scene->getCoffre(2, 18)) ouvrePorte(338, 66, 1);
            if (scene->getCoffre(2, 19)) ouvrePorte(258, 51, 1);

            addObject(new Interrupteur(283*16, 24*16, 0, scene->getCoffre(2, 16), map));
            addObject(new Interrupteur(314*16, 33*16, 0, scene->getCoffre(2, 17), map));
            addObject(new Interrupteur(336*16, 69*16, 0, scene->getCoffre(2, 18), map));
            addObject(new Interrupteur(257*16, 49*16, 0, scene->getCoffre(2, 19), map, false));

            addObject(new Coffre(169 * 16, 22 * 16, 0, scene->getCoffre(2, 4), TI_CLE, 4));
            if (scene->getCoffre(2, 5)) addObject(new Coffre(204 * 16, 34 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(249 * 16 + 8, 81 * 16, 0, scene->getCoffre(2, 6), TI_CLE, 6));
            addObject(new Coffre(287 * 16 + 8, 39 * 16, 0, scene->getCoffre(2, 7), TI_CLE, 7));
            if (scene->getCoffre(2, 8)) addObject(new Coffre(334 * 16, 33 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(350 * 16, 6 * 16, 0, scene->getCoffre(2, 9), TI_CLE, 9));

            addObject(new Sphere(269*16+8, 67*16)); addObject(new Sphere(337*16, 64*16));
            addObject(new Sphere(260*16, 34*16)); addObject(new Sphere(329*16+8, 20*16));
            addObject(new Sphere(168*16, 4*16)); addObject(new Sphere(166*16, 19*16));

            addObject(new TasDePierres(342*16, 39*16, 0)); addObject(new TasDePierres(356*16, 34*16, 0));

            addObject(new Caisse(208*16, 36*16, 2, 3)); addObject(new Caisse(212*16, 38*16, 2, 2));
            addObject(new Caisse(209*16, 39*16, 2, 1)); addObject(new Caisse(300*16, 75*16, 2, 1, true));
            addObject(new Caisse(306*16, 82*16, 2, 1)); addObject(new Caisse(315*16, 75*16, 2, 1));
            addObject(new Caisse(271*16, 80*16, 2, 3)); addObject(new Caisse(268*16, 81*16, 2, 4));
            addObject(new Caisse(270*16, 81*16, 2, 3)); addObject(new Caisse(272*16, 82*16, 2, 2));
            addObject(new Caisse(270*16, 83*16, 2, 2)); addObject(new Caisse(271*16, 83*16, 2, 2));
            addObject(new Caisse(268*16, 84*16, 2, 1)); addObject(new Caisse(272*16, 84*16, 2, 1));
            addObject(new Caisse(172*16, 6*16, 2, 1)); addObject(new Caisse(172*16, 7*16, 2, 1));
            addObject(new Caisse(172*16, 8*16, 2, 1)); addObject(new Caisse(260*16, 37*16, 2, 1));
            addObject(new Caisse(261*16, 38*16, 2, 1)); addObject(new Caisse(260*16, 39*16, 2, 1));
            addObject(new Caisse(329*16, 5*16, 2, 1)); addObject(new Caisse(330*16, 5*16, 2, 1));
            addObject(new Caisse(328*16, 6*16, 2, 1)); addObject(new Caisse(331*16, 6*16, 2, 1));
            addObject(new Caisse(328*16, 7*16, 2, 1)); addObject(new Caisse(331*16, 7*16, 2, 1));
            addObject(new Caisse(329*16, 8*16, 2, 1)); addObject(new Caisse(330*16, 8*16, 2, 1));
            addObject(new Caisse(329*16, 35*16, 2, 2)); addObject(new Caisse(329*16, 36*16, 2, 2));
            addObject(new Caisse(330*16, 36*16, 2, 3)); addObject(new Caisse(331*16, 36*16, 2, 2));
            addObject(new Caisse(329*16, 37*16, 2, 1)); addObject(new Caisse(330*16, 38*16, 2, 1));
            addObject(new Caisse(332*16, 38*16, 2, 2)); addObject(new Caisse(326*16, 63*16, 2, 9));
            addObject(new Caisse(328*16, 63*16, 2, 9)); addObject(new Caisse(330*16, 63*16, 2, 9));
            addObject(new Caisse(332*16, 63*16, 2, 9)); addObject(new Caisse(334*16, 63*16, 2, 9));

            addEnnemi(new Ennemi009(250*16,84*16)); addEnnemi(new Ennemi009(311*16,66*16));

            addEnnemi(new Ennemi010(279*16,14*16)); addEnnemi(new Ennemi010(255*16,41*16));
            addEnnemi(new Ennemi010(264*16,41*16)); addEnnemi(new Ennemi010(354*16,74*16));
            addEnnemi(new Ennemi010(139*16+8,78*16));

            addEnnemi(new Ennemi022(185*16,18*16-7)); addEnnemi(new Ennemi022(245*16,7*16-7));
            addEnnemi(new Ennemi022(252*16,16*16-7)); addEnnemi(new Ennemi022(245*16,23*16-7));
            addEnnemi(new Ennemi022(348*16,6*16-7)); addEnnemi(new Ennemi022(270*16,52*16-7));
            addEnnemi(new Ennemi022(266*16,69*16-7)); addEnnemi(new Ennemi022(272*16,64*16-7));
            addEnnemi(new Ennemi022(349*16+8,67*16-7)); addEnnemi(new Ennemi022(349*16+8,78*16-7));

            addEnnemi(new Ennemi023(209*16+3,52*16-1)); addEnnemi(new Ennemi023(267*16+3,5*16-1));
            addEnnemi(new Ennemi023(291*16+3,5*16-1)); addEnnemi(new Ennemi023(313*16+3,37*16-1));
            addEnnemi(new Ennemi023(291*16+3,44*16-1)); addEnnemi(new Ennemi023(286*16+3,65*16-1));
            addEnnemi(new Ennemi023(291*16+3,84*16-1)); addEnnemi(new Ennemi023(129*16+3,82*16-1));
            addEnnemi(new Ennemi023(149*16+3,82*16-1)); addEnnemi(new Ennemi023(109*16+3,38*16-1));

            addEnnemi(new Ennemi027(309*16+8,4*16-1)); addEnnemi(new Ennemi027(247*16,51*16-1));
            addEnnemi(new Ennemi027(329*16+8,82*16-1));

            addObject(new Jarre(204*16, 49*16, 0, TI_FLECHE, map));
            addObject(new Jarre(204*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(244*16, 49*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(244*16, 78*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(244*16, 86*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(257*16, 49*16, 0, TI_INTERRUPTEUR, map));
            addObject(new Jarre(264*16, 63*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(264*16, 71*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(286*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(287*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(288*16, 4*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(288*16, 53*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(289*16, 53*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(296*16, 55*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(297*16, 55*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(301*16, 55*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(308*16, 40*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(309*16, 40*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(323*16, 47*16, 0, TI_FLECHE, map));
            addObject(new Jarre(324*16, 78*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(335*16, 78*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(336*16, 47*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(337*16, 62*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(345*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(354*16, 55*16, 0, TI_FLECHE, map));
            break;
        case 48 :
            //mini boss
            if (!scene->getCoffre(3, 28)) {
                addEnnemi(new Ennemi095(132*16+6, 32*16+8-2));
                addObject(new Interrupteur(124*16, 33*16, 0, false, map));
                addObject(new Interrupteur(129*16, 33*16, 0, false, map));
                addObject(new Interrupteur(135*16, 33*16, 0, false, map));
                addObject(new Interrupteur(126*16, 42*16, 0, true, map));
                addObject(new Interrupteur(133*16, 42*16, 0, true, map));
                addObject(new PiegeFeu(124*16, 35*16, false));
                addObject(new PiegeFeu(129*16, 35*16, false));
                addObject(new PiegeFeu(135*16, 35*16, false));
                addObject(new PiegeFeu(124*16, 39*16, false));
                addObject(new PiegeFeu(135*16, 39*16, false));
            } else {
                ouvrePorte(129, 28, 0);
                ouvrePorte(128, 34, 3);
            }
            //boss
            if (!inventory->hasCoeur(2)) {
                addEnnemi(new Ennemi097(8*16+5, 32*16));
            } else {
                ouvrePorte(289*16, 40*16, 4);
                ouvrePorte(3*16, 33*16, 5);
                ouvrePorte(144*16, 34*16, 6);
                ouvrePorte(288*16, 35*16, 7);
            }
            if (!inventory->hasMedaillon(2)) {
                addItem(ItemHelper::getInstance()->createItem(TI_MEDAILLON_3, 290*16, 21*16+8));
            }

            if (scene->getMonsters(19)) {
                addObject(new Coffre(69 * 16, 66 * 16, 0, scene->getCoffre(3, 4), TI_CLE, 4));
            } else {
                addEnnemi(new Ennemi019(68*16, 64*16));
            }
            if (scene->getMonsters(24)) {
                addObject(new Coffre(36 * 16, 33 * 16, 0, scene->getCoffre(3, 0), TI_CARTE_DONJON));
            } else {
                addEnnemi(new Ennemi024(29*16, 34*16, false));
            }
            if (scene->getMonsters(28)) {
                addObject(new Coffre(216 * 16, 62 * 16, 0, scene->getCoffre(3, 5), TI_CLE, 5));
            } else {
                addEnnemi(new Ennemi028(209*16, 66*16-6));
            }
            if (scene->getMonsters(35)) {
                addObject(new Interrupteur(195*16, 12*16, 0, scene->getCoffre(3, 22), map));
            } else {
                addEnnemi(new Ennemi035(189*16, 3*16));
            }
            if (scene->getMonsters(40)) {
                addObject(new Coffre(244 * 16, 33 * 16, 0, scene->getCoffre(3, 1), TI_BOUSSOLE));
            } else {
                addEnnemi(new Ennemi040(249*16-11, 33*16));
            }
            if (scene->getMonsters(43)) {
                addObject(new Interrupteur(57*16, 3*16, 0, scene->getCoffre(3, 16), map));
            } else {
                addEnnemi(new Ennemi043(49*16, 3*16));
            }

            addObject(new Coffre(209 * 16 + 8, 5 * 16, 0, scene->getCoffre(3, 2), TI_CLE_BOSS));

            if (scene->getCoffre(3, 2) == 2) ouvrePorte(9, 43, 0);

            addObject(new Coffre(129 * 16, 20 * 16 + 8, 1, link->getInventory()->hasObject(LANTERNE), TI_LANTERNE));

            addObject(new Coffre(88 * 16, 37 * 16, 0, scene->getCoffre(3, 7), TI_CLE, 7));
            addObject(new Coffre(235 * 16, 48 * 16, 0, scene->getCoffre(3, 8), TI_CLE, 8));
            addObject(new Coffre(69 * 16 + 8, 5 * 16, 0, scene->getCoffre(3, 9), TI_CLE, 9));

            if (scene->getCoffre(3, 10)) ouvrePorte(58, 66, 1);
            if (scene->getCoffre(3, 11)) ouvrePorte(78, 66, 1);
            if (scene->getCoffre(3, 12)) ouvrePorte(129, 43, 0);
            if (scene->getCoffre(3, 13)) ouvrePorte(169, 43, 0);
            if (scene->getCoffre(3, 14)) ouvrePorte(229, 58, 0);
            if (scene->getCoffre(3, 15)) ouvrePorte(238, 66, 1);
            if (scene->getCoffre(3, 16)) ouvrePorte(58, 6, 1);
            if (scene->getCoffre(3, 17)) ouvrePorte(69, 13, 0);
            if (scene->getCoffre(3, 18)) ouvrePorte(69, 58, 0);
            if (scene->getCoffre(3, 19)) ouvrePorte(258, 6, 1);
            if (scene->getCoffre(3, 20)) ouvrePorte(109, 58, 0);
            if (scene->getCoffre(3, 21)) ouvrePorte(149, 58, 0);
            if (scene->getCoffre(3, 22)) ouvrePorte(189, 13, 0);
            if (scene->getCoffre(3, 23)) ouvrePorte(178, 21, 1);
            if (scene->getCoffre(3, 24)) ouvrePorte(178, 51, 1);
            if (scene->getCoffre(3, 25)) ouvrePorte(209, 58, 0);
            if (scene->getCoffre(3, 26)) ouvrePorte(238, 36, 1);
            if (scene->getCoffre(3, 27)) ouvrePorte(289, 13, 2);

            if (scene->getCoffre(3, 29)) map->setSol(37*16, 50*16, 1936);
            if (scene->getCoffre(3, 30)) map->setSol(37*16, 54*16, 1936);
            if (scene->getCoffre(3, 31)) map->setSol(68*16, 27*16, 1936);
            if (scene->getCoffre(3, 32)) map->setSol(71*16, 27*16, 1936);
            if (scene->getCoffre(3, 33)) map->setSol(69*16, 41*16, 1936);
            if (scene->getCoffre(3, 34)) map->setSol(70*16, 41*16, 1936);
            if (scene->getCoffre(3, 35)) map->setSol(109*16, 7*16, 1936);
            if (scene->getCoffre(3, 36)) map->setSol(102*16, 35*16, 1936);
            if (scene->getCoffre(3, 37)) map->setSol(102*16, 39*16, 1936);
            if (scene->getCoffre(3, 38)) map->setSol(127*16, 17*16, 1936);
            if (scene->getCoffre(3, 39)) map->setSol(132*16, 17*16, 1936);
            if (scene->getCoffre(3, 40)) map->setSol(186*16, 26*16, 1936);
            if (scene->getCoffre(3, 41)) map->setSol(191*16, 49*16, 1936);
            if (scene->getCoffre(3, 42)) map->setSol(191*16, 34*16, 1936);
            if (scene->getCoffre(3, 43)) map->setSol(196*16, 34*16, 1936);
            if (scene->getCoffre(3, 44)) map->setSol(207*16, 24*16, 1936);
            if (scene->getCoffre(3, 45)) map->setSol(212*16, 24*16, 1936);
            if (scene->getCoffre(3, 46)) map->setSol(204*16, 35*16, 1936);
            if (scene->getCoffre(3, 47)) map->setSol(215*16, 35*16, 1936);
            if (scene->getCoffre(3, 48)) map->setSol(206*16, 51*16, 1936);
            if (scene->getCoffre(3, 49)) map->setSol(213*16, 51*16, 1936);
            if (scene->getCoffre(3, 50)) map->setSol(224*16, 20*16, 1936);
            if (scene->getCoffre(3, 51)) map->setSol(234*16, 26*16, 1936);
            if (scene->getCoffre(3, 52)) map->setSol(229*16, 37*16, 1936);
            if (scene->getCoffre(3, 53)) map->setSol(234*16, 53*16, 1936);
            if (scene->getCoffre(3, 54)) map->setSol(227*16, 56*16, 1936);
            if (scene->getCoffre(3, 55)) map->setSol(242*16, 49*16, 1936);
            if (scene->getCoffre(3, 56)) map->setSol(242*16, 55*16, 1936);
            if (scene->getCoffre(3, 57)) map->setSol(247*16, 57*16, 1936);
            if (scene->getCoffre(3, 58)) map->setSol(252*16, 57*16, 1936);

            if (scene->getCoffre(3, 29) && scene->getCoffre(3, 30)) ouvrePorte(38, 51, 1);
            if (scene->getCoffre(3, 31) && scene->getCoffre(3, 32)) ouvrePorte(69, 28, 0);
            if (scene->getCoffre(3, 33) && scene->getCoffre(3, 34)) addObject(new Coffre(75 * 16, 40 * 16, 0, scene->getCoffre(3, 6), TI_CLE, 6));
            if (scene->getCoffre(3, 35)) ouvrePorte(98, 6, 1);
            if (scene->getCoffre(3, 36) && scene->getCoffre(3, 37)) ouvrePorte(98, 36, 1);
            if (scene->getCoffre(3, 38) && scene->getCoffre(3, 39)) ouvrePorte(129, 13, 0);
            if (scene->getCoffre(3, 40) && scene->getCoffre(3, 41) && scene->getCoffre(3, 42) && scene->getCoffre(3, 43)
                && scene->getCoffre(3, 44) && scene->getCoffre(3, 45) && scene->getCoffre(3, 46) && scene->getCoffre(3, 47)
                && scene->getCoffre(3, 48) && scene->getCoffre(3, 49) && scene->getCoffre(3, 50) && scene->getCoffre(3, 51)
                && scene->getCoffre(3, 52) && scene->getCoffre(3, 53)&& scene->getCoffre(3, 54)) ouvrePorte(209, 13, 0);
            if (scene->getCoffre(3, 55) && scene->getCoffre(3, 56)) ouvrePorte(238, 51, 1);
            if (scene->getCoffre(3, 57) && scene->getCoffre(3, 58)) ouvrePorte(249, 58, 0);

            addObject(new Interrupteur(75*16, 12*16, 0, scene->getCoffre(3, 17), map));
            addObject(new Interrupteur(67*16, 57*16, 0, scene->getCoffre(3, 18), map));
            addObject(new Interrupteur(250*16, 11*16, 0, scene->getCoffre(3, 19), map));
            addObject(new Interrupteur(103*16, 52*16, 0, scene->getCoffre(3, 20), map));
            addObject(new Interrupteur(147*16, 57*16, 0, scene->getCoffre(3, 21), map));
            addObject(new Interrupteur(189*16, 20*16, 0, scene->getCoffre(3, 23), map));
            addObject(new Interrupteur(184*16, 55*16, 0, scene->getCoffre(3, 24), map));
            addObject(new Interrupteur(207*16, 56*16, 0, scene->getCoffre(3, 25), map));
            addObject(new Interrupteur(236*16, 37*16, 0, scene->getCoffre(3, 26), map));

            addObject(new PiegeFeu(275*16, 49*16)); addObject(new PiegeFeu(275*16, 55*16));
            addObject(new PiegeFeu(164*16, 70*16)); addObject(new PiegeFeu(90*16, 67*16));
            addObject(new PiegeFeu(117*16, 4*16)); addObject(new PiegeFeu(64*16, 32*16));
            addObject(new PiegeFeu(75*16, 32*16)); addObject(new PiegeFeu(18*16, 21*16));

            addEnnemi(new Ennemi005(49*16+8,67*16-10)); addEnnemi(new Ennemi005(29*16+8,52*16-10));
            addEnnemi(new Ennemi005(249*16+8,52*16-10)); addEnnemi(new Ennemi005(263*16,18*16-10));
            addEnnemi(new Ennemi005(255*16+8,27*16-10)); addEnnemi(new Ennemi005(269*16+8,37*16-10));
            addEnnemi(new Ennemi005(89*16+8,52*16-10)); addEnnemi(new Ennemi005(189*16+8,66*16-10));
            addEnnemi(new Ennemi005(229*16+8,7*16-10)); addEnnemi(new Ennemi005(89*16+8,7*16-10));
            addEnnemi(new Ennemi005(69*16+8,7*16-10)); addEnnemi(new Ennemi005(169*16+8,7*16-10));
            addEnnemi(new Ennemi005(149*16+8,22*16-10)); addEnnemi(new Ennemi005(129*16+8,52*16-10));

            addEnnemi(new Ennemi018(124*16,63*16+2)); addEnnemi(new Ennemi018(259*16,48*16+2));
            addEnnemi(new Ennemi018(270*16,21*16+2)); addEnnemi(new Ennemi018(250*16,23*16+2));
            addEnnemi(new Ennemi018(233*16,63*16+2)); addEnnemi(new Ennemi018(269*16,72*16+2));
            addEnnemi(new Ennemi018(144*16,64*16+2)); addEnnemi(new Ennemi018(155*16,64*16+2));
            addEnnemi(new Ennemi018(144*16,69*16+2)); addEnnemi(new Ennemi018(155*16,69*16+2));
            addEnnemi(new Ennemi018(53*16,48*16+2)); addEnnemi(new Ennemi018(264*16,11*16+2));
            addEnnemi(new Ennemi018(108*16,23*16+2)); addEnnemi(new Ennemi018(111*16,23*16+2));
            addEnnemi(new Ennemi018(146*16,12*16+2)); addEnnemi(new Ennemi018(14*16,12*16+2));

            addEnnemi(new Ennemi025(109*16-6+8,66*16+2)); addEnnemi(new Ennemi025(29*16-6+8,66*16+2));
            addEnnemi(new Ennemi025(248*16-6+8,66*16+2)); addEnnemi(new Ennemi025(69*16-6+8,49*16+2));
            addEnnemi(new Ennemi025(249*16-6+8,5*16+2)); addEnnemi(new Ennemi025(91*16-6+8,21*16+2));
            addEnnemi(new Ennemi025(149*16-6+8,51*16+2)); addEnnemi(new Ennemi025(49*16-6+8,36*16+2));
            addEnnemi(new Ennemi025(69*16-6+8,21*16+2)); addEnnemi(new Ennemi025(106*16-6+8,36*16+2));
            addEnnemi(new Ennemi025(169*16-6+8,21*16+2));

            addEnnemi(new Ennemi053(13*16, 69*16)); addEnnemi(new Ennemi053(5*16, 63*16));
            addEnnemi(new Ennemi053(125*16, 5*16)); addEnnemi(new Ennemi053(133*16, 10*16));
            addEnnemi(new Ennemi053(49*16+8, 22*16)); addEnnemi(new Ennemi053(32*16, 7*16));
            addEnnemi(new Ennemi053(197*16, 26*16)); addEnnemi(new Ennemi053(198*16, 47*16));
            addEnnemi(new Ennemi053(219*16, 27*16)); addEnnemi(new Ennemi053(221*16, 47*16));

            addObject(new Jarre(6*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(13*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 62*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 72*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(26*16, 6*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(26*16, 7*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(26*16, 8*16, 0, TI_FLECHE, map));
            addObject(new Jarre(27*16, 70*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(28*16, 70*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(29*16, 70*16, 0, TI_FLECHE, map));
            addObject(new Jarre(46*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(75*16, 57*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(122*16, 25*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(124*16, 27*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(135*16, 27*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(137*16, 25*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(124*16, 49*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(135*16, 49*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(155*16, 49*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(174*16, 10*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(175*16, 10*16, 0, TI_FLECHE, map));
            addObject(new Jarre(190*16, 55*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(191*16, 55*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(215*16, 57*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(216*16, 19*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(216*16, 20*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(233*16, 17*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(233*16, 57*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(254*16, 70*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(255*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(264*16, 25*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(264*16, 49*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(264*16, 55*16, 0, TI_FLECHE, map));
            addObject(new Jarre(289*16, 6*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(290*16, 6*16, 0, TI_NO_ITEM, map));
            break;
        case 49 :
            //mini boss
            if (!scene->getCoffre(4,20)) {
                addEnnemi(new Ennemi098(83*16, 21*16+8));
            } else {
                ouvrePorte(89, 13, 0);
            }
            //boss
            if (!inventory->hasCoeur(3)) {
                addEnnemi(new Ennemi099(198*16-2, 32*16));
                addEnnemi(new Ennemi100(183*16-1, 20*16));
                addEnnemi(new Ennemi100(185*16-1, 40*16));
                addEnnemi(new Ennemi100(192*16-1, 30*16));
                addEnnemi(new Ennemi100(205*16-1, 34*16));
                addEnnemi(new Ennemi100(207*16-1, 24*16));
            }
            if (!scene->getCoffre(4, 30)) {
                addObject(new Pnj(16*199+8, 16*3, 62, 1252));
            }
            if (scene->getCoffre(4, 21)) {
                addObject(new Coffre(103 * 16, 83 * 16, 0, scene->getCoffre(4, 0), TI_CARTE_DONJON));
            }
            addObject(new Coffre(29 * 16, 25 * 16, 0, scene->getCoffre(4, 1), TI_BOUSSOLE));
            addObject(new Coffre(69 * 16 + 8, 21 * 16, 0, scene->getCoffre(4, 2), TI_CLE_BOSS));

            if (scene->getCoffre(4, 2) == 2) ouvrePorte(199, 43, 0);

            addObject(new Coffre(89 * 16, 6 * 16 + 8, 1, link->getInventory()->hasObject(PALMES), TI_PALMES));

            addObject(new Coffre(69 * 16 + 8, 7 * 16, 0, scene->getCoffre(4, 4), TI_CLE, 4));
            addObject(new Coffre(84 * 16, 68 * 16, 0, scene->getCoffre(4, 5), TI_CLE, 5));
            addObject(new Coffre(119 * 16, 5 * 16, 0, scene->getCoffre(4, 6), TI_CLE, 6));
            addObject(new Coffre(210 * 16, 67 * 16, 0, scene->getCoffre(4, 7), TI_CLE, 7));

            if (scene->getCoffre(4, 8)) ouvrePorte(49, 58, 0);
            if (scene->getCoffre(4, 9)) ouvrePorte(69, 28, 0);
            if (scene->getCoffre(4, 10)) ouvrePorte(118, 51, 1);
            if (scene->getCoffre(4, 11)) ouvrePorte(129, 43, 0);
            if (scene->getCoffre(4, 12)) ouvrePorte(29, 28, 0);
            if (scene->getCoffre(4, 13)) ouvrePorte(58, 51, 1);
            if (scene->getCoffre(4, 14)) ouvrePorte(89, 28, 0);
            if (scene->getCoffre(4, 15)) ouvrePorte(98, 66, 1);
            if (scene->getCoffre(4, 16)) ouvrePorte(149, 73, 0);
            if (scene->getCoffre(4, 17)) ouvrePorte(158, 81, 1);
            if (scene->getCoffre(4, 18)) ouvrePorte(158, 6, 1);
            if (scene->getCoffre(4, 19)) ouvrePorte(229, 73, 0);

            if (scene->getCoffre(4, 22)) map->setSol(222*16, 21*16, 1936);
            if (scene->getCoffre(4, 23)) map->setSol(228*16, 27*16, 1936);
            if (scene->getCoffre(4, 24)) map->setSol(231*16, 27*16, 1936);
            if (scene->getCoffre(4, 25)) map->setSol(237*16, 19*16, 1936);
            if (scene->getCoffre(4, 26)) map->setSol(222*16, 9*16, 1936);
            if (scene->getCoffre(4, 27)) map->setSol(230*16, 2*16, 1936);
            if (scene->getCoffre(4, 28)) map->setSol(237*16, 5*16, 1936);
            if (scene->getCoffre(4, 29)) map->setSol(237*16, 9*16, 1936);
            if (scene->getCoffre(4, 31)) map->setSol(117*16, 35*16, 1936);
            if (scene->getCoffre(4, 32)) map->setSol(117*16, 39*16, 1936);

            if (scene->getCoffre(4, 22) && scene->getCoffre(4, 23) && scene->getCoffre(4, 24) && scene->getCoffre(4, 25)
                && scene->getCoffre(4, 26) && scene->getCoffre(4, 27) && scene->getCoffre(4, 28) && scene->getCoffre(4, 29)) ouvrePorte(238, 6, 1);

            if (scene->getCoffre(4, 31) && scene->getCoffre(4, 32)) ouvrePorte(118, 36, 1);

            addObject(new Interrupteur(30*16, 21*16, 0, scene->getCoffre(4, 12), map));
            addObject(new Interrupteur(62*16, 55*16, 0, scene->getCoffre(4, 13), map));
            addObject(new Interrupteur(82*16, 32*16, 0, scene->getCoffre(4, 14), map));
            addObject(new Interrupteur(88*16, 71*16, 0, scene->getCoffre(4, 15), map));
            addObject(new Interrupteur(155*16, 69*16, 0, scene->getCoffre(4, 16), map));
            addObject(new Interrupteur(157*16, 85*16, 0, scene->getCoffre(4, 17), map));
            addObject(new Interrupteur(162*16, 5*16, 0, scene->getCoffre(4, 18), map));
            addObject(new Interrupteur(228*16, 62*16, 0, scene->getCoffre(4, 19), map));

            addEnnemi(new Ennemi026(101*16,21*16)); addEnnemi(new Ennemi026(95*16,31*16));
            addEnnemi(new Ennemi026(58*16,61*16)); addEnnemi(new Ennemi026(23*16,64*16));
            addEnnemi(new Ennemi026(47*16,8*16)); addEnnemi(new Ennemi026(24*16,0));
            addEnnemi(new Ennemi026(58*16,15*16)); addEnnemi(new Ennemi026(225*16,80*16));
            addEnnemi(new Ennemi026(231*16,84*16)); addEnnemi(new Ennemi026(155*16,72*16));
            addEnnemi(new Ennemi026(155*16,76*16));

            addEnnemi(new Ennemi032(134*16,22*16-7)); addEnnemi(new Ennemi032(65*16,50*16-7));
            addEnnemi(new Ennemi032(110*16,52*16-7)); addEnnemi(new Ennemi032(90*16,67*16-7));
            addEnnemi(new Ennemi032(89*16,82*16-7)); addEnnemi(new Ennemi032(49*16,52*16-7));
            addEnnemi(new Ennemi032(29*16,52*16-7)); addEnnemi(new Ennemi032(49*16,36*16-7));
            addEnnemi(new Ennemi032(67*16,7*16-7)); addEnnemi(new Ennemi032(70*16,4*16-7));
            addEnnemi(new Ennemi032(72*16,10*16-7)); addEnnemi(new Ennemi032(126*16,38*16-7));
            addEnnemi(new Ennemi032(229*16,67*16-7)); addEnnemi(new Ennemi032(166*16,84*16-7));
            addEnnemi(new Ennemi032(173*16,82*16-7)); addEnnemi(new Ennemi032(223*16,10*16-7));

            /*addEnnemi(new Ennemi086(109*16,15*16));*/ addEnnemi(new Ennemi086(117*16,8*16));
            addEnnemi(new Ennemi086(118*16,21*16)); addEnnemi(new Ennemi086(105*16,34*16));
            /*addEnnemi(new Ennemi086(114*16,40*16));*/ addEnnemi(new Ennemi086(71*16,43*16));
            addEnnemi(new Ennemi086(108*16,76*16)); addEnnemi(new Ennemi086(116*16,85*16-8));
            addEnnemi(new Ennemi086(120*16,64*16)); addEnnemi(new Ennemi086(132*16,75*16));
            addEnnemi(new Ennemi086(134*16,55*16)); addEnnemi(new Ennemi086(69*16,82*16));
            addEnnemi(new Ennemi086(35*16,71*16)); addEnnemi(new Ennemi086(25*16,34*16));
            addEnnemi(new Ennemi086(24*16+8,21*16)); addEnnemi(new Ennemi086(35*16,11*16));
            addEnnemi(new Ennemi086(42*16,23*16)); addEnnemi(new Ennemi086(225*16,37*16));
            addEnnemi(new Ennemi086(238*16,36*16)); addEnnemi(new Ennemi086(251*16,39*16));
            addEnnemi(new Ennemi086(223*16,17*16)); addEnnemi(new Ennemi086(227*16,7*16));
            addEnnemi(new Ennemi086(234*16,20*16)); addEnnemi(new Ennemi086(246*16,63*16));
            addEnnemi(new Ennemi086(231*16,51*16)); addEnnemi(new Ennemi086(205*16,78*16));
            addEnnemi(new Ennemi086(150*16,57*16)); addEnnemi(new Ennemi086(160*16,65*16));
            addEnnemi(new Ennemi086(171*16,57*16)); addEnnemi(new Ennemi086(143*16,22*16));
            addEnnemi(new Ennemi086(144*16,39*16)); addEnnemi(new Ennemi086(156*16,31*16));
            addEnnemi(new Ennemi086(163*16,18*16)); addEnnemi(new Ennemi086(167*16,40*16));
            addEnnemi(new Ennemi086(175*16,22*16));

            addObject(new Jarre(29*16, 72*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(32*16, 25*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(32*16, 73*16, 1, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(33*16, 66*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(33*16, 72*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(62*16, 49*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(75*16, 62*16, 1, TI_FLECHE, map));
            addObject(new Jarre(76*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(77*16, 40*16, 1, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(80*16, 40*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(87*16, 50*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(92*16, 32*16, 1, TI_FLECHE, map));
            addObject(new Jarre(95*16, 41*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(104*16, 12*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(104*16, 13*16, 1, TI_FLECHE, map));
            addObject(new Jarre(106*16, 74*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(112*16, 24*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(121*16, 79*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(124*16, 70*16, 1, TI_FLECHE, map));
            addObject(new Jarre(125*16, 21*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(145*16, 25*16, 1, TI_FLECHE, map));
            addObject(new Jarre(145*16, 85*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(146*16, 4*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(153*16, 38*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(162*16, 85*16, 1, TI_FLECHE, map));
            addObject(new Jarre(172*16, 53*16, 1, TI_FLECHE, map));
            addObject(new Jarre(172*16, 77*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(175*16, 39*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(187*16, 53*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(192*16, 69*16, 1, TI_FLECHE, map));
            addObject(new Jarre(212*16, 53*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(222*16, 13*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(222*16, 14*16, 1, TI_RUBIS_VERT, map));
            addObject(new Jarre(224*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(224*16, 41*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(227*16, 54*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(237*16, 27*16, 1, TI_PETIT_COEUR, map));
            break;
        case 50 :
            // mini boss
            if (!scene->getCoffre(5, 41)) {
                addEnnemi(new Ennemi102(169*16+4,51*16));
            } else {
                ouvrePorte(169, 43, 0);
            }
            //boss
            if (!inventory->hasCoeur(4)) {
                addEnnemi(new Ennemi103(247*16+6, 17*16-3));
            }
            //clé du temps
            if (!inventory->hasObject(CLE_TEMPS)) {
                addItem(ItemHelper::getInstance()->createItem(TI_CLE_TEMPS, 250*16, 6*16+8));
            }

            addObject(new Coffre(249 * 16 + 8, 82 * 16, 0, scene->getCoffre(5, 0), TI_CARTE_DONJON));
            if (scene->getCoffre(5, 38)) {
                addObject(new Coffre(49 * 16, 37 * 16, 0, scene->getCoffre(5, 1), TI_BOUSSOLE));
            }
            addObject(new Coffre(129 * 16 + 8, 37 * 16, 0, scene->getCoffre(5, 2), TI_CLE_BOSS));

            if (scene->getCoffre(5, 2) == 2) ouvrePorte(249, 28, 0);

            addObject(new Coffre(169 * 16, 36 * 16 + 8, 1, link->getTunique() > 1, TI_TUNIQUE_BLEUE));

            if (scene->getCoffre(5, 27)) {
                addObject(new Coffre(84 * 16, 49 * 16, 0, scene->getCoffre(5, 4), TI_CLE, 4));
            }
            addObject(new Coffre(149 * 16 + 8, 51 * 16, 0, scene->getCoffre(5, 5), TI_CLE, 5));
            if (scene->getCoffre(5, 39)) {
                addObject(new Coffre(290 * 16, 37 * 16, 0, scene->getCoffre(5, 6), TI_CLE, 6));
            }
            if (scene->getCoffre(5, 40)) {
                addObject(new Coffre(300 * 16, 90 * 16, 0, scene->getCoffre(5, 7), TI_CLE, 7));
            }

            if (scene->getCoffre(5, 8)) ouvrePorte(49, 58, 0);
            if (scene->getCoffre(5, 9)) ouvrePorte(98, 36, 1);
            if (scene->getCoffre(5, 10)) ouvrePorte(98, 81, 1);
            if (scene->getCoffre(5, 11)) ouvrePorte(169, 58, 0);
            if (scene->getCoffre(5, 12)) ouvrePorte(98, 66, 3);
            if (scene->getCoffre(5, 13)) ouvrePorte(209, 28, 2);
            if (scene->getCoffre(5, 14)) ouvrePorte(278, 21, 3);
            if (scene->getCoffre(5, 15)) ouvrePorte(289, 73, 2);
            if (scene->getCoffre(5, 16)) ouvrePorte(6, 51, 4);
            if (scene->getCoffre(5, 17)) ouvrePorte(24, 54, 4);
            if (scene->getCoffre(5, 18)) ouvrePorte(28, 51, 4);
            if (scene->getCoffre(5, 19)) ouvrePorte(33, 49, 4);
            if (scene->getCoffre(5, 20)) ouvrePorte(35, 53, 4);
            if (scene->getCoffre(5, 21)) ouvrePorte(64, 53, 4);
            if (scene->getCoffre(5, 22)) ouvrePorte(69, 52, 4);
            if (scene->getCoffre(5, 23)) ouvrePorte(73, 49, 4);
            if (scene->getCoffre(5, 24)) ouvrePorte(74, 53, 4);
            if (scene->getCoffre(5, 25)) ouvrePorte(269, 6, 4);
            if (scene->getCoffre(5, 26)) ouvrePorte(58, 66, 1);
            if (scene->getCoffre(5, 28)) ouvrePorte(129, 28, 0);
            if (scene->getCoffre(5, 29)) ouvrePorte(158, 66, 1);
            if (scene->getCoffre(5, 30)) ouvrePorte(169, 28, 0);
            if (scene->getCoffre(5, 31)) ouvrePorte(158, 81, 1);
            if (scene->getCoffre(5, 32)) ouvrePorte(189, 73, 0);
            if (scene->getCoffre(5, 33)) ouvrePorte(209, 73, 0);
            if (scene->getCoffre(5, 34)) ouvrePorte(258, 36, 1);
            if (scene->getCoffre(5, 35)) ouvrePorte(249, 73, 0);
            if (scene->getCoffre(5, 36)) ouvrePorte(249, 88, 0);
            if (scene->getCoffre(5, 37)) ouvrePorte(289, 58, 0);

            addObject(new Interrupteur(43*16, 67*16, 0, scene->getCoffre(5, 26), map));
            addObject(new Interrupteur(89*16, 56*16, 0, scene->getCoffre(5, 27), map));
            addObject(new Interrupteur(134*16, 34*16, 0, scene->getCoffre(5, 28), map));
            addObject(new Interrupteur(150*16, 63*16, 0, scene->getCoffre(5, 29), map));
            addObject(new Interrupteur(167*16, 32*16, 0, scene->getCoffre(5, 30), map));
            addObject(new Interrupteur(162*16, 79*16, 0, scene->getCoffre(5, 31), map));
            addObject(new Interrupteur(196*16, 67*16, 0, scene->getCoffre(5, 32), map));
            addObject(new Interrupteur(204*16, 81*16, 0, scene->getCoffre(5, 33), map));
            addObject(new Interrupteur(243*16, 37*16, 0, scene->getCoffre(5, 34), map));
            addObject(new Interrupteur(247*16, 79*16, 0, scene->getCoffre(5, 35), map));
            addObject(new Interrupteur(256*16, 97*16, 0, scene->getCoffre(5, 36), map));
            addObject(new Interrupteur(283*16, 52*16, 0, scene->getCoffre(5, 37), map));

            addObject(new PiegeMain(242*16, 47*16)); addObject(new PiegeMain(182*16, 77*16));
            addObject(new PiegeMain(182*16, 2*16)); addObject(new PiegeMain(282*16, 77*16));
            addObject(new PiegeMain(282*16, 2*16)); addObject(new PiegeMain(62*16, 62*16));

            addEnnemi(new Ennemi001(106*16,50*16+6)); addEnnemi(new Ennemi001(114*16,55*16+6));
            addEnnemi(new Ennemi001(107*16,84*16+6)); addEnnemi(new Ennemi001(112*16,79*16+6));
            addEnnemi(new Ennemi001(226*16,96*16+6)); addEnnemi(new Ennemi001(233*16,97*16+6));
            addEnnemi(new Ennemi001(208*16,66*16+6)); addEnnemi(new Ennemi001(109*16,20*16+6));
            addEnnemi(new Ennemi001(152*16,23*16+6)); addEnnemi(new Ennemi001(144*16,21*16+6));
            addEnnemi(new Ennemi001(25*16,50*16+6)); addEnnemi(new Ennemi001(33*16,53*16+6));
            addEnnemi(new Ennemi001(267*16,36*16+6)); addEnnemi(new Ennemi001(273*16,38*16+6));
            addEnnemi(new Ennemi001(305*16,49*16+6)); addEnnemi(new Ennemi001(310*16,53*16+6));
            addEnnemi(new Ennemi001(314*16,50*16+6));

            addEnnemi(new Ennemi026(146*16,66*16)); addEnnemi(new Ennemi026(153*16,66*16));
            addEnnemi(new Ennemi026(86*16,65*16)); addEnnemi(new Ennemi026(90*16,71*16));
            addEnnemi(new Ennemi026(93*16,64*16)); addEnnemi(new Ennemi026(85*16,53*16));
            addEnnemi(new Ennemi026(266*16,63*16)); addEnnemi(new Ennemi026(273*16,69*16));
            addEnnemi(new Ennemi026(282*16,48*16)); addEnnemi(new Ennemi026(283*16,56*16));
            addEnnemi(new Ennemi026(265*16,101*16)); addEnnemi(new Ennemi026(266*16,93*16));
            addEnnemi(new Ennemi026(273*16,97*16)); addEnnemi(new Ennemi026(243*16,93*16));
            addEnnemi(new Ennemi026(253*16,101*16)); addEnnemi(new Ennemi026(206*16,71*16));
            addEnnemi(new Ennemi026(194*16,63*16)); addEnnemi(new Ennemi026(196*16,71*16));
            addEnnemi(new Ennemi026(185*16,39*16)); addEnnemi(new Ennemi026(194*16,34*16));
            addEnnemi(new Ennemi026(224*16,11*16)); addEnnemi(new Ennemi026(95*16,16*16));
            addEnnemi(new Ennemi026(145*16,42*16)); addEnnemi(new Ennemi026(156*16,35*16));
            addEnnemi(new Ennemi026(141*16,49*16)); addEnnemi(new Ennemi026(153*16,58*16));
            addEnnemi(new Ennemi026(26*16,42*16)); addEnnemi(new Ennemi026(31*16,31*16));
            addEnnemi(new Ennemi026(35*16,39*16)); addEnnemi(new Ennemi026(45*16,63*16));
            addEnnemi(new Ennemi026(46*16,71*16)); addEnnemi(new Ennemi026(53*16,63*16));
            addEnnemi(new Ennemi026(64*16,33*16)); addEnnemi(new Ennemi026(71*16,31*16));
            addEnnemi(new Ennemi026(75*16,38*16)); addEnnemi(new Ennemi026(273*16,26*16));
            addEnnemi(new Ennemi026(305*16,69*16)); addEnnemi(new Ennemi026(314*16,65*16));

            addEnnemi(new Ennemi037(112*16, 48*16-10)); addEnnemi(new Ennemi037(249*16, 96*16-10));
            addEnnemi(new Ennemi037(125*16, 20*16-10)); addEnnemi(new Ennemi037(285*16, 66*16-10));
            addEnnemi(new Ennemi037(294*16, 68*16-10));

            addEnnemi(new Ennemi056(126*16-1,80*16-1)); addEnnemi(new Ennemi056(133*16-1,80*16-1));
            addEnnemi(new Ennemi056(129*16-1,71*16-1)); addEnnemi(new Ennemi056(91*16-1,49*16-1));
            addEnnemi(new Ennemi056(166*16-1,82*16-1)); addEnnemi(new Ennemi056(246*16-1,67*16-1));
            addEnnemi(new Ennemi056(253*16-1,67*16-1)); addEnnemi(new Ennemi056(273*16-1,53*16-1));
            addEnnemi(new Ennemi056(289*16-1,52*16-1)); addEnnemi(new Ennemi056(189*16-1,85*16-1));
            addEnnemi(new Ennemi056(195*16-1,95*16-1)); addEnnemi(new Ennemi056(202*16-1,87*16-1));
            addEnnemi(new Ennemi056(212*16-1,89*16-1)); addEnnemi(new Ennemi056(190*16-1,10*16-1));
            addEnnemi(new Ennemi056(195*16-1,20*16-1)); addEnnemi(new Ennemi056(203*16-1,9*16-1));
            addEnnemi(new Ennemi056(206*16-1,18*16-1)); addEnnemi(new Ennemi056(229*16-1,36*16-1));
            addEnnemi(new Ennemi056(106*16-1,40*16-1)); addEnnemi(new Ennemi056(113*16-1,33*16-1));
            addEnnemi(new Ennemi056(249*16-1,37*16-1)); addEnnemi(new Ennemi056(169*16-1,66*16-1));
            addEnnemi(new Ennemi056(33*16-1,66*16-1)); addEnnemi(new Ennemi056(66*16-1,50*16-1));
            addEnnemi(new Ennemi056(73*16-1,54*16-1)); addEnnemi(new Ennemi056(50*16-1,48*16-1));
            addEnnemi(new Ennemi056(273*16-1,7*16-1)); addEnnemi(new Ennemi056(287*16-1,14*16-1));
            addEnnemi(new Ennemi056(296*16-1,7*16-1)); addEnnemi(new Ennemi056(297*16-1,24*16-1));
            addEnnemi(new Ennemi056(307*16-1,14*16-1)); addEnnemi(new Ennemi056(287*16-1,36*16-1));

            addEnnemi(new Ennemi062(269*16+4, 81*16, false)); addEnnemi(new Ennemi062(189*16+4, 51*16, false));
            addEnnemi(new Ennemi062(298*16+4, 90*16, false));

            addEnnemi(new Ennemi064(106*16-4, 65*16-4)); addEnnemi(new Ennemi064(112*16-4, 69*16-4));
            addEnnemi(new Ennemi064(93*16-4, 82*16-4)); addEnnemi(new Ennemi064(148*16-4, 84*16-4));
            addEnnemi(new Ennemi064(152*16-4, 78*16-4)); addEnnemi(new Ennemi064(229*16-4, 66*16-4));
            addEnnemi(new Ennemi064(189*16-4, 66*16-4)); addEnnemi(new Ennemi064(228*16-4, 6*16-4));
            addEnnemi(new Ennemi064(209*16-4, 36*16-4)); addEnnemi(new Ennemi064(209*16-4, 53*16-4));
            addEnnemi(new Ennemi064(218*16-4, 50*16-4)); addEnnemi(new Ennemi064(227*16-4, 52*16-4));
            addEnnemi(new Ennemi064(89*16-4, 37*16-4)); addEnnemi(new Ennemi064(166*16-4, 21*16-4));
            addEnnemi(new Ennemi064(69*16-4, 66*16-4)); addEnnemi(new Ennemi064(271*16-4, 21*16-4));
            addEnnemi(new Ennemi064(292*16-4, 12*16-4)); addEnnemi(new Ennemi064(309*16-4, 36*16-4));

            addEnnemi(new Ennemi091(229*16+5, 82*16)); addEnnemi(new Ennemi091(226*16+5, 20*16));
            addEnnemi(new Ennemi091(232*16+5, 23*16)); addEnnemi(new Ennemi091(119*16+5, 23*16));
            addEnnemi(new Ennemi091(135*16+5, 23*16)); addEnnemi(new Ennemi091(46*16+5, 34*16));
            addEnnemi(new Ennemi091(48*16+5, 39*16)); addEnnemi(new Ennemi091(53*16+5, 36*16));
            addEnnemi(new Ennemi091(288*16+5, 89*16)); addEnnemi(new Ennemi091(296*16+5, 96*16));
            addEnnemi(new Ennemi091(298*16+5, 83*16)); addEnnemi(new Ennemi091(307*16+5, 91*16));

            addEnnemi(new Ennemi101(29*16, 58*16, S)); addEnnemi(new Ennemi101(238*16, 36*16+8, E));
            addEnnemi(new Ennemi101(298*16, 36*16+8, E));

            addObject(new Jarre(43*16, 55*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(56*16, 55*16, 1, TI_FLECHE, map));
            addObject(new Jarre(95*16, 87*16, 1, TI_BOMBE, map));
            addObject(new Jarre(96*16, 55*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(97*16, 55*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(162*16, 25*16, 1, TI_FLECHE, map));
            addObject(new Jarre(166*16, 64*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(173*16, 64*16, 1, TI_FLECHE, map));
            addObject(new Jarre(184*16, 85*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(185*16, 85*16, 1, TI_BOMBE, map));
            addObject(new Jarre(188*16, 9*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(188*16, 10*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(194*16, 81*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(195*16, 81*16, 1, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(211*16, 27*16, 1, TI_FLECHE, map));
            addObject(new Jarre(244*16, 70*16, 1, TI_FLECHE, map));
            addObject(new Jarre(248*16, 40*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(251*16, 40*16, 1, TI_FLECHE, map));
            addObject(new Jarre(255*16, 70*16, 1, TI_BOMBE, map));
            addObject(new Jarre(272*16, 6*16, 1, TI_FLECHE, map));
            addObject(new Jarre(272*16, 7*16, 1, TI_BOMBE, map));
            addObject(new Jarre(272*16, 8*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(282*16, 25*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(283*16, 25*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(284*16, 77*16, 1, TI_FLECHE, map));
            addObject(new Jarre(284*16, 78*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(284*16, 79*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(284*16, 100*16, 1, TI_BOMBE, map));
            addObject(new Jarre(285*16, 100*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(310*16, 100*16, 1, TI_FLECHE, map));
            addObject(new Jarre(315*16, 100*16, 1, TI_BOMBE, map));
            break;
        case 51 :
            // mini boss
            if (!scene->getCoffre(6, 28)) {
                addEnnemi(new Ennemi104(129*16,34*16));
                addObject(new PiegeDemi(123*16, 32*16));
                addObject(new PiegeDemi(137*16, 32*16));
            } else {
                ouvrePorte(129, 28, 0);
            }
            //boss
            if (!inventory->hasCoeur(5)) {
                addEnnemi(new Ennemi105(247*16+8, 25*16));
                addObject(new Interrupteur(240*16, 23*16, 0, false, map));
                addObject(new Interrupteur(259*16, 23*16, 0, false, map));
                addObject(new Interrupteur(240*16, 40*16, 0, false, map));
                addObject(new Interrupteur(259*16, 40*16, 0, false, map));
                addObject(new PiegeUltime(236*16, 19*16, false));
                addObject(new PiegeUltime(263*16, 19*16, false));
                addObject(new PiegeUltime(236*16, 40*16, false));
                addObject(new PiegeUltime(263*16, 40*16, false));
            }

            addObject(new Coffre(169 * 16 + 8, 21 * 16, 0, scene->getCoffre(6, 0), TI_CARTE_DONJON));
            if (scene->getCoffre(6, 27)) {
                addObject(new Coffre(150 * 16, 21 * 16, 0, scene->getCoffre(6, 1), TI_BOUSSOLE));
            }
            addObject(new Coffre(89 * 16 + 8, 21 * 16, 0, scene->getCoffre(6, 2), TI_CLE_BOSS));

            if (scene->getCoffre(6, 2) == 2) ouvrePorte(249, 43, 0);

            addObject(new Coffre(249 * 16, 5 * 16 + 8, 1, link->getInventory()->hasObject(MARTEAU), TI_MARTEAU));

            addObject(new Coffre(109 * 16 + 8, 65 * 16, 0, scene->getCoffre(6, 4), TI_CLE, 4));
            addObject(new Coffre(229 * 16 + 8, 6 * 16, 0, scene->getCoffre(6, 5), TI_CLE, 5));
            addObject(new Coffre(269 * 16 + 8, 6 * 16, 0, scene->getCoffre(6, 6), TI_CLE, 6));

            if (scene->getCoffre(6, 7)) ouvrePorte(89, 28, 0);
            if (scene->getCoffre(6, 8)) ouvrePorte(109, 73, 0);
            if (scene->getCoffre(6, 9)) ouvrePorte(138, 36, 1);
            if (scene->getCoffre(6, 10)) ouvrePorte(118, 81, 3);
            if (scene->getCoffre(6, 11)) ouvrePorte(309, 73, 2);
            if (scene->getCoffre(6, 12)) ouvrePorte(38, 66, 1);
            if (scene->getCoffre(6, 13)) ouvrePorte(69, 58, 0);
            if (scene->getCoffre(6, 14)) ouvrePorte(98, 66, 1);
            if (scene->getCoffre(6, 15)) ouvrePorte(109, 28, 0);
            if (scene->getCoffre(6, 16)) ouvrePorte(129, 58, 0);
            if (scene->getCoffre(6, 17)) ouvrePorte(129, 73, 0);
            if (scene->getCoffre(6, 18)) ouvrePorte(138, 66, 1);
            if (scene->getCoffre(6, 19)) ouvrePorte(209, 58, 0);
            if (scene->getCoffre(6, 20)) ouvrePorte(198, 51, 1);
            if (scene->getCoffre(6, 21)) ouvrePorte(229, 73, 0);
            if (scene->getCoffre(6, 22)) ouvrePorte(249, 88, 0);
            if (scene->getCoffre(6, 23)) ouvrePorte(269, 58, 0);
            if (scene->getCoffre(6, 24)) ouvrePorte(289, 28, 0);
            if (scene->getCoffre(6, 25)) ouvrePorte(289, 58, 0);
            if (scene->getCoffre(6, 26)) ouvrePorte(298, 66, 1);

            addObject(new Interrupteur(37*16, 70*16, 0, scene->getCoffre(6, 12), map));
            addObject(new Interrupteur(67*16, 57*16, 0, scene->getCoffre(6, 13), map));
            addObject(new Interrupteur(97*16, 64*16, 0, scene->getCoffre(6, 14), map));
            addObject(new Interrupteur(108*16, 21*16, 0, scene->getCoffre(6, 15), map));
            addObject(new Interrupteur(127*16, 57*16, 0, scene->getCoffre(6, 16), map));
            addObject(new Interrupteur(136*16, 82*16, 0, scene->getCoffre(6, 17), map));
            addObject(new Interrupteur(149*16, 72*16, 0, scene->getCoffre(6, 18), map));
            addObject(new Interrupteur(217*16, 57*16, 0, scene->getCoffre(6, 19), map, false));
            addObject(new Interrupteur(216*16, 52*16, 0, scene->getCoffre(6, 20), map));
            addObject(new Interrupteur(229*16, 85*16, 0, scene->getCoffre(6, 21), map));
            addObject(new Interrupteur(246*16, 92*16, 0, scene->getCoffre(6, 22), map));
            addObject(new Interrupteur(263*16, 67*16, 0, scene->getCoffre(6, 23), map));
            addObject(new Interrupteur(295*16, 25*16, 0, scene->getCoffre(6, 24), map));
            addObject(new Interrupteur(285*16, 57*16, 0, scene->getCoffre(6, 25), map, false));
            addObject(new Interrupteur(302*16, 64*16, 0, scene->getCoffre(6, 26), map));

            addObject(new InterrupteurStar(130*16, 22*16, scene->getCoffre(6, 29), map));
            if (scene->getCoffre(6, 29)) {
                map->activateInterStar(130*16, 22*16, false);
            }

            addObject(new PiegeMurs(80*16, 41*16-1)); addObject(new PiegeMurs(160*16, 41*16-1));

            addObject(new PiegePics(164*16, 64*16-8, S)); addObject(new PiegePics(34*16, 36*16-8, S));
            addObject(new PiegePics(113*16, 21*16, S)); addObject(new PiegePics(114*16, 22*16, S));
            addObject(new PiegePics(115*16, 23*16, S)); addObject(new PiegePics(286*16, 51*16, S));
            addObject(new PiegePics(293*16, 51*16, S)); addObject(new PiegePics(192*16, 51*16, S));
            addObject(new PiegePics(194*16, 51*16, S)); addObject(new PiegePics(196*16, 51*16, S));
            addObject(new PiegePics(269*16, 100*16, S)); addObject(new PiegePics(271*16, 93*16, S));

            addObject(new PiegeLong(109*16, 81*16-8, S)); addObject(new PiegeLong(26*16, 55*16+8, S));
            addObject(new PiegeLong(86*16, 64*16, S));

            addEnnemi(new Ennemi007(146*16, 70*16)); addEnnemi(new Ennemi007(154*16, 63*16));
            addEnnemi(new Ennemi007(143*16, 21*16)); addEnnemi(new Ennemi007(147*16, 26*16));
            addEnnemi(new Ennemi007(148*16, 18*16)); addEnnemi(new Ennemi007(151*16, 22*16));
            addEnnemi(new Ennemi007(153*16, 25*16)); addEnnemi(new Ennemi007(156*16, 20*16));
            addEnnemi(new Ennemi007(129*16+8, 81*16)); addEnnemi(new Ennemi007(45*16, 55*16));
            addEnnemi(new Ennemi007(49*16, 54*16)); addEnnemi(new Ennemi007(55*16, 51*16));
            addEnnemi(new Ennemi007(105*16, 71*16)); addEnnemi(new Ennemi007(106*16, 63*16));
            addEnnemi(new Ennemi007(115*16, 66*16)); addEnnemi(new Ennemi007(288*16, 88*16));
            addEnnemi(new Ennemi007(297*16, 97*16)); addEnnemi(new Ennemi007(302*16, 81*16));
            addEnnemi(new Ennemi007(312*16, 87*16)); addEnnemi(new Ennemi007(294*16, 20*16));
            addEnnemi(new Ennemi007(296*16, 11*16)); addEnnemi(new Ennemi007(304*16, 22*16));
            addEnnemi(new Ennemi007(306*16, 12*16)); addEnnemi(new Ennemi007(307*16, 37*16));
            addEnnemi(new Ennemi007(275*16, 81*16)); addEnnemi(new Ennemi007(226*16, 96*16));
            addEnnemi(new Ennemi007(233*16, 98*16)); addEnnemi(new Ennemi007(199*16, 85*16));
            addEnnemi(new Ennemi007(207*16, 98*16)); addEnnemi(new Ennemi007(209*16, 88*16));
            addEnnemi(new Ennemi007(189*16, 18*16)); addEnnemi(new Ennemi007(196*16, 8*16));
            addEnnemi(new Ennemi007(201*16, 21*16)); addEnnemi(new Ennemi007(214*16, 15*16));
            addEnnemi(new Ennemi007(226*16, 51*16)); addEnnemi(new Ennemi007(230*16, 54*16));

            addEnnemi(new Ennemi016(149*16+8, 37*16-8)); addEnnemi(new Ennemi016(51*16+8, 37*16-8));
            addEnnemi(new Ennemi016(69*16+8, 37*16-8)); addEnnemi(new Ennemi016(69*16+8, 67*16-8));
            addEnnemi(new Ennemi016(109*16+8, 51*16-8)); addEnnemi(new Ennemi016(149*16+8, 82*16-8));
            addEnnemi(new Ennemi016(289*16+8, 52*16-8)); addEnnemi(new Ennemi016(268*16, 85*16));
            addEnnemi(new Ennemi016(229*16+8, 67*16-8)); addEnnemi(new Ennemi016(189*16+8, 37*16-8));
            addEnnemi(new Ennemi016(209*16+8, 67*16-8)); addEnnemi(new Ennemi016(270*16, 97*16-8));
            addEnnemi(new Ennemi016(249*16+8, 82*16-8));

            addEnnemi(new Ennemi029(125*16, 64*16-10)); addEnnemi(new Ennemi029(134*16, 68*16-10));
            addEnnemi(new Ennemi029(166*16, 66*16-10)); addEnnemi(new Ennemi029(47*16, 34*16-10));
            addEnnemi(new Ennemi029(65*16, 52*16-10)); addEnnemi(new Ennemi029(73*16, 54*16-10));
            addEnnemi(new Ennemi029(54*16, 66*16-10)); addEnnemi(new Ennemi029(27*16, 65*16-10));
            addEnnemi(new Ennemi029(34*16, 68*16-10)); addEnnemi(new Ennemi029(105*16, 54*16-10));
            addEnnemi(new Ennemi029(114*16, 56*16-10)); addEnnemi(new Ennemi029(147*16, 50*16-10));
            addEnnemi(new Ennemi029(153*16, 52*16-10)); addEnnemi(new Ennemi029(292*16, 71*16-10));
            addEnnemi(new Ennemi029(294*16, 63*16-10)); addEnnemi(new Ennemi029(266*16, 8*16-10));
            addEnnemi(new Ennemi029(272*16, 3*16-10)); addEnnemi(new Ennemi029(307*16, 51*16-10));
            addEnnemi(new Ennemi029(286*16, 37*16-10)); addEnnemi(new Ennemi029(270*16, 51*16-10));
            addEnnemi(new Ennemi029(273*16, 66*16-10)); addEnnemi(new Ennemi029(249*16, 96*16-10));
            addEnnemi(new Ennemi029(228*16, 6*16-10)); addEnnemi(new Ennemi029(205*16, 35*16-10));
            addEnnemi(new Ennemi029(214*16, 37*16-10)); addEnnemi(new Ennemi029(193*16, 66*16-10));
            addEnnemi(new Ennemi029(233*16, 78*16-10));

            addEnnemi(new Ennemi062(309*16+4, 67*16, false)); addEnnemi(new Ennemi062(207*16+4, 51*16, false));
            addEnnemi(new Ennemi062(249*16+4, 66*16, false));

            addObject(new Jarre(64*16, 49*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(75*16, 49*16, 0, TI_FLECHE, map));
            addObject(new Jarre(84*16, 62*16, 0, TI_BOMBE, map));
            addObject(new Jarre(104*16, 49*16, 0, TI_FLECHE, map));
            addObject(new Jarre(115*16, 49*16, 0, TI_BOMBE, map));
            addObject(new Jarre(134*16, 19*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(142*16, 35*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(142*16, 39*16, 0, TI_BOMBE, map));
            addObject(new Jarre(202*16, 57*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(206*16, 16*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(207*16, 16*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(213*16, 87*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(213*16, 88*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(217*16, 57*16, 0, TI_INTERRUPTEUR, map));
            addObject(new Jarre(244*16, 54*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(255*16, 54*16, 0, TI_BOMBE, map));
            addObject(new Jarre(284*16, 11*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(284*16, 20*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(285*16, 57*16, 0, TI_INTERRUPTEUR, map));
            addObject(new Jarre(294*16, 57*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(314*16, 77*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(315*16, 11*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(315*16, 20*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(315*16, 77*16, 0, TI_PETIT_COEUR, map));
            break;
        case 52 :
            // mini boss
            if (!scene->getCoffre(7, 24)) {
                addEnnemi(new Ennemi106(132*16-15,51*16));
            } else {
                ouvrePorte(129, 43, 0);
                ouvrePorte(130, 52, 2);
            }
            //boss
            if (!inventory->hasCoeur(6)) {
                addEnnemi(new Ennemi107(247*16+9, 30*16));
                map->setAir(249 * 16, 30 * 16, -1);
                map->setAir(250 * 16, 30 * 16, -1);
            } else {
                ouvrePorte(248, 32, 3);
            }
            if (!inventory->hasObject(TROC_GEMME_JAUNE)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_JAUNE, 250*16, 21*16+8));
            }

            if (scene->getCoffre(7, 22)) {
                addObject(new Coffre(109 * 16, 82 * 16, 0, scene->getCoffre(7, 0), TI_CARTE_DONJON));
            }
            if (scene->getCoffre(7, 23)) {
                addObject(new Coffre(150 * 16, 82 * 16, 0, scene->getCoffre(7, 1), TI_BOUSSOLE));
            }
            addObject(new Coffre(249 * 16 + 8, 7 * 16, 0, scene->getCoffre(7, 2), TI_CLE_BOSS));

            if (scene->getCoffre(7, 2) == 2) ouvrePorte(249, 43, 0);

            addObject(new Coffre(129 * 16, 36 * 16 + 8, 1, link->getInventory()->hasObject(GANTS_2), TI_GANT2));

            if (scene->getCoffre(7, 21)) {
                addObject(new Coffre(90 * 16, 66 * 16, 0, scene->getCoffre(7, 4), TI_CLE, 4));
            }
            addObject(new Coffre(146 * 16, 64 * 16, 0, scene->getCoffre(7, 5), TI_CLE, 5));
            addObject(new Coffre(169 * 16 + 8, 39 * 16, 0, scene->getCoffre(7, 6), TI_CLE, 6));
            addObject(new Coffre(209 * 16 + 8, 6 * 16, 0, scene->getCoffre(7, 7), TI_CLE, 7));

            if (scene->getCoffre(7, 8)) ouvrePorte(58, 51, 1);
            if (scene->getCoffre(7, 9)) ouvrePorte(118, 81, 1);
            if (scene->getCoffre(7, 10)) ouvrePorte(138, 81, 1);
            if (scene->getCoffre(7, 11)) ouvrePorte(258, 6, 1);
            if (scene->getCoffre(7, 12)) ouvrePorte(38, 66, 1);
            if (scene->getCoffre(7, 13)) ouvrePorte(49, 58, 0);
            if (scene->getCoffre(7, 14)) ouvrePorte(69, 43, 0);
            if (scene->getCoffre(7, 15)) ouvrePorte(58, 66, 1);
            if (scene->getCoffre(7, 16)) ouvrePorte(118, 21, 1);
            if (scene->getCoffre(7, 17)) ouvrePorte(129, 28, 0);
            if (scene->getCoffre(7, 18)) ouvrePorte(138, 21, 1);
            if (scene->getCoffre(7, 19)) ouvrePorte(169, 43, 0);
            if (scene->getCoffre(7, 20)) ouvrePorte(198, 36, 1);

            addObject(new Interrupteur(28*16, 68*16, 0, scene->getCoffre(7, 12), map));
            addObject(new Interrupteur(48*16, 57*16, 0, scene->getCoffre(7, 13), map));
            addObject(new Interrupteur(63*16, 37*16, 0, scene->getCoffre(7, 14), map));
            addObject(new Interrupteur(71*16, 68*16, 0, scene->getCoffre(7, 15), map));
            addObject(new Interrupteur(103*16, 22*16, 0, scene->getCoffre(7, 16), map));
            addObject(new Interrupteur(127*16, 32*16, 0, scene->getCoffre(7, 17), map));
            addObject(new Interrupteur(156*16, 22*16, 0, scene->getCoffre(7, 18), map));
            addObject(new Interrupteur(167*16, 33*16, 0, scene->getCoffre(7, 19), map));
            addObject(new Interrupteur(216*16, 37*16, 0, scene->getCoffre(7, 20), map));

            addObject(new TasDePierres(156*16, 71*16, 1)); addObject(new TasDePierres(243*16, 41*16, 1));

            addObject(new Pierre(16*265, 16*6, 8, map)); addObject(new Pierre(16*265, 16*7, 8, map));
            addObject(new Pierre(16*265, 16*8, 8, map));

            addObject(new Caisse(310*16, 81*16, 0, 1)); addObject(new Caisse(309*16, 82*16, 0, 1));
            addObject(new Caisse(310*16, 83*16, 0, 1));

            addEnnemi(new Ennemi007(147*16, 66*16)); addEnnemi(new Ennemi007(153*16, 68*16));
            addEnnemi(new Ennemi007(146*16, 85*16)); addEnnemi(new Ennemi007(148*16, 79*16));
            addEnnemi(new Ennemi007(152*16, 86*16)); addEnnemi(new Ennemi007(105*16, 50*16));
            addEnnemi(new Ennemi007(114*16, 54*16)); addEnnemi(new Ennemi007(167*16, 41*16));
            addEnnemi(new Ennemi007(173*16, 40*16)); addEnnemi(new Ennemi007(114*16, 22*16));
            addEnnemi(new Ennemi007(165*16, 20*16)); addEnnemi(new Ennemi007(174*16, 23*16));
            addEnnemi(new Ennemi007(189*16+8, 22*16)); addEnnemi(new Ennemi007(263*16, 63*16));
            addEnnemi(new Ennemi007(276*16, 71*16)); addEnnemi(new Ennemi007(287*16, 82*16));
            addEnnemi(new Ennemi007(309*16+8, 7*16)); addEnnemi(new Ennemi007(203*16, 63*16));
            addEnnemi(new Ennemi007(216*16, 71*16));

            addEnnemi(new Ennemi030(124*16+8, 67*16-8)); addEnnemi(new Ennemi030(134*16+8, 67*16-8));
            addEnnemi(new Ennemi030(109*16+8, 67*16-8)); addEnnemi(new Ennemi030(83*16+8, 33*16));
            addEnnemi(new Ennemi030(95*16+8, 40*16)); addEnnemi(new Ennemi030(89*16+8, 18*16-8));
            addEnnemi(new Ennemi030(129*16+8, 22*16-8)); addEnnemi(new Ennemi030(49*16+8, 37*16-8));
            addEnnemi(new Ennemi030(29*16+8, 67*16-8)); addEnnemi(new Ennemi030(69*16+8, 67*16-8));
            addEnnemi(new Ennemi030(229*16+8, 67*16-8)); addEnnemi(new Ennemi030(229*16+8, 7*16-8));
            addEnnemi(new Ennemi030(229*16+8, 37*16-8)); addEnnemi(new Ennemi030(189*16+8, 37*16-8));
            addEnnemi(new Ennemi030(289*16+8, 97*16-8)); addEnnemi(new Ennemi030(309*16+8, 22*16-8));
            addEnnemi(new Ennemi030(289*16+8, 7*16-8));

            addEnnemi(new Ennemi042(125*16-5,81*16-3)); addEnnemi(new Ennemi042(134*16-5,81*16-3));
            addEnnemi(new Ennemi042(85*16-5,68*16-3)); addEnnemi(new Ennemi042(89*16-5,64*16-3));
            addEnnemi(new Ennemi042(92*16-5,69*16-3)); addEnnemi(new Ennemi042(169*16-5+8,69*16-3));
            addEnnemi(new Ennemi042(85*16-5,79*16-3)); addEnnemi(new Ennemi042(93*16-5,84*16-3));
            addEnnemi(new Ennemi042(106*16-5,37*16-3)); addEnnemi(new Ennemi042(114*16-5,39*16-3));
            addEnnemi(new Ennemi042(93*16-5,22*16-3)); addEnnemi(new Ennemi042(149*16-5+8,22*16-3));
            addEnnemi(new Ennemi042(69*16-5+8,52*16-3)); addEnnemi(new Ennemi042(249*16-5+8,97*16-3));
            addEnnemi(new Ennemi042(189*16-5+8,7*16-3)); addEnnemi(new Ennemi042(209*16-5+8,37*16-3));
            addEnnemi(new Ennemi042(189*16-5+8,67*16-3)); addEnnemi(new Ennemi042(309*16-5+8,67*16-3));
            addEnnemi(new Ennemi042(269*16-5+8,22*16-3));

            addEnnemi(new Ennemi062(166*16+4, 80*16, false)); addEnnemi(new Ennemi062(171*16+4, 83*16, false));
            addEnnemi(new Ennemi062(106*16+4, 80*16, false)); addEnnemi(new Ennemi062(111*16+4, 84*16, false));
            addEnnemi(new Ennemi062(85*16+4, 22*16, false));

            addObject(new Jarre(24*16, 40*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(35*16, 40*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(104*16, 55*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(115*16, 33*16, 0, TI_FLECHE, map));
            addObject(new Jarre(172*16, 33*16, 0, TI_BOMBE, map));
            addObject(new Jarre(175*16, 72*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(196*16, 96*16, 0, TI_FLECHE, map));
            addObject(new Jarre(203*16, 6*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(243*16, 8*16, 0, TI_BOMBE, map));
            addObject(new Jarre(255*16, 51*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(255*16, 52*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(255*16, 53*16, 0, TI_FLECHE, map));
            addObject(new Jarre(263*16, 51*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(308*16, 18*16, 0, TI_BOMBE, map));
            break;
        case 53 :
            // mini boss
            if (!scene->getCoffre(8, 27)) {
                addEnnemi(new Ennemi108(89*16-5,21*16+6));
            } else{
                ouvrePorte(89, 13, 0);
            }
            //boss
            if (!inventory->hasCoeur(7)) {
                addEnnemi(new Ennemi109(180*16, 75*16));
            }
            if (!inventory->hasObject(TROC_GEMME_VERTE)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_VERTE, 210*16, 5*16+8));
            }

            if (scene->getCoffre(8, 26)) {
                addObject(new Coffre(89 * 16, 67 * 16, 0, scene->getCoffre(8, 0), TI_CARTE_DONJON));
            }
            addObject(new Coffre(39 * 16 + 8, 20 * 16, 0, scene->getCoffre(8, 1), TI_BOUSSOLE));
            addObject(new Coffre(169 * 16 + 8, 21 * 16, 0, scene->getCoffre(8, 2), TI_CLE_BOSS));

            if (scene->getCoffre(8, 2) == 2) ouvrePorte(189, 13, 0);

            addObject(new Coffre(85 * 16 + 8, 4 * 16 + 8, 1, link->getInventory()->hasObject(ARC_FEE), TI_ARC_FEE));

            if (scene->getCoffre(8, 25)) {
                addObject(new Coffre(9 * 16, 37 * 16, 0, scene->getCoffre(8, 4), TI_CLE, 4));
            }
            addObject(new Coffre(69 * 16 + 8, 96 * 16, 0, scene->getCoffre(8, 5), TI_CLE, 5));
            addObject(new Coffre(109 * 16, 29 * 16, 0, scene->getCoffre(8, 6), TI_CLE, 6));
            addObject(new Coffre(149 * 16 + 8, 37 * 16, 0, scene->getCoffre(8, 7), TI_CLE, 7));

            if (scene->getCoffre(8, 8)) ouvrePorte(18, 51, 1);
            if (scene->getCoffre(8, 9)) ouvrePorte(98, 21, 1);
            if (scene->getCoffre(8, 10)) ouvrePorte(138, 21, 1);
            if (scene->getCoffre(8, 11)) ouvrePorte(169, 13, 0);
            if (scene->getCoffre(8, 12)) ouvrePorte(229, 6, 4);
            if (scene->getCoffre(8, 13)) ouvrePorte(9, 28, 0);
            if (scene->getCoffre(8, 14)) ouvrePorte(29, 13, 0);
            if (scene->getCoffre(8, 15)) ouvrePorte(29, 43, 0);
            if (scene->getCoffre(8, 16)) ouvrePorte(58, 36, 1);
            if (scene->getCoffre(8, 17)) ouvrePorte(69, 28, 0);
            if (scene->getCoffre(8, 18)) ouvrePorte(69, 103, 0);
            if (scene->getCoffre(8, 19)) ouvrePorte(98, 6, 1);
            if (scene->getCoffre(8, 20)) ouvrePorte(89, 73, 0);
            if (scene->getCoffre(8, 21)) ouvrePorte(109, 73, 0);
            if (scene->getCoffre(8, 22)) ouvrePorte(129, 43, 0);
            if (scene->getCoffre(8, 23)) ouvrePorte(129, 103, 0);
            if (scene->getCoffre(8, 24)) ouvrePorte(198, 51, 1);

            addObject(new Interrupteur(12*16, 27*16, 0, scene->getCoffre(8, 13), map));
            addObject(new Interrupteur(23*16, 7*16, 0, scene->getCoffre(8, 14), map));
            addObject(new Interrupteur(32*16, 42*16, 0, scene->getCoffre(8, 15), map));
            addObject(new Interrupteur(50*16, 41*16, 0, scene->getCoffre(8, 16), map));
            addObject(new Interrupteur(72*16, 27*16, 0, scene->getCoffre(8, 17), map));
            addObject(new Interrupteur(68*16, 92*16, 0, scene->getCoffre(8, 18), map));
            addObject(new Interrupteur(97*16, 5*16, 0, scene->getCoffre(8, 19), map));
            addObject(new Interrupteur(87*16, 72*16, 0, scene->getCoffre(8, 20), map));
            addObject(new Interrupteur(107*16, 77*16, 0, scene->getCoffre(8, 21), map));
            addObject(new Interrupteur(132*16, 47*16, 0, scene->getCoffre(8, 22), map));
            addObject(new Interrupteur(134*16, 102*16, 0, scene->getCoffre(8, 23), map));
            addObject(new Interrupteur(197*16, 55*16, 0, scene->getCoffre(8, 24), map));

            addObject(new PiegePics(124*16, 37*16, S));

            addObject(new PiegeLong(106*16, 49*16, S)); addObject(new PiegeLong(126*16, 4*16, S));

            addEnnemi(new Ennemi012(234*16,48*16)); addEnnemi(new Ennemi012(234*16,54*16));
            addEnnemi(new Ennemi012(225*16,38*16)); addEnnemi(new Ennemi012(230*16,35*16));
            addEnnemi(new Ennemi012(234*16,37*16)); addEnnemi(new Ennemi012(184*16,30*16));
            addEnnemi(new Ennemi012(193*16,37*16)); addEnnemi(new Ennemi012(204*16,22*16));
            addEnnemi(new Ennemi012(215*16,28*16)); addEnnemi(new Ennemi012(229*16+8,8*16));
            addEnnemi(new Ennemi012(229*16+8,22*16)); addEnnemi(new Ennemi012(209*16+8,51*16));
            addEnnemi(new Ennemi012(187*16,50*16)); addEnnemi(new Ennemi012(192*16,53*16));
            addEnnemi(new Ennemi012(169*16,52*16));

            addEnnemi(new Ennemi013(44*16,46*16-4)); addEnnemi(new Ennemi013(55*16,46*16-4));
            addEnnemi(new Ennemi013(58*16,31*16-4)); addEnnemi(new Ennemi013(40*16,39*16-4));
            addEnnemi(new Ennemi013(21*16,31*16-4)); addEnnemi(new Ennemi013(18*16,43*16-4));
            addEnnemi(new Ennemi013(44*16,16*16-4)); addEnnemi(new Ennemi013(18*16,13*16-4));
            addEnnemi(new Ennemi013(61*16,13*16-4)); addEnnemi(new Ennemi013(142*16,36*16-4));
            addEnnemi(new Ennemi013(144*16,43*16-4)); addEnnemi(new Ennemi013(149*16,31*16-4));
            addEnnemi(new Ennemi013(155*16,43*16-4)); addEnnemi(new Ennemi013(157*16,36*16-4));
            addEnnemi(new Ennemi013(124*16,46*16-4)); addEnnemi(new Ennemi013(135*16,46*16-4));
            addEnnemi(new Ennemi013(109*16,37*16-4)); addEnnemi(new Ennemi013(104*16,24*16-4));
            addEnnemi(new Ennemi013(134*16,24*16-4)); addEnnemi(new Ennemi013(147*16,7*16-4));
            addEnnemi(new Ennemi013(146*16,16*16-4)); addEnnemi(new Ennemi013(152*16,28*16-4));
            addEnnemi(new Ennemi013(105*16,1*16-4)); addEnnemi(new Ennemi013(114*16,1*16-4));
            addEnnemi(new Ennemi013(84*16,46*16-4)); addEnnemi(new Ennemi013(90*16,58*16-4));
            addEnnemi(new Ennemi013(96*16,46*16-4));

            addEnnemi(new Ennemi033(26*16-3+8,50*16-9)); addEnnemi(new Ennemi033(32*16-3+8,50*16-9));
            addEnnemi(new Ennemi033(49*16-3,52*16-9)); addEnnemi(new Ennemi033(67*16-3,51*16-9));
            addEnnemi(new Ennemi033(71*16-3,55*16-9)); addEnnemi(new Ennemi033(73*16-3,49*16-9));
            addEnnemi(new Ennemi033(69*16-3,36*16-9)); addEnnemi(new Ennemi033(13*16-3,51*16-9));
            addEnnemi(new Ennemi033(6*16-3,35*16-9)); addEnnemi(new Ennemi033(11*16-3,39*16-9));
            addEnnemi(new Ennemi033(65*16-3,22*16-9)); addEnnemi(new Ennemi033(26*16-3,20*16-9));
            addEnnemi(new Ennemi033(6*16-3,7*16-9)); addEnnemi(new Ennemi033(12*16-3,4*16-9));
            addEnnemi(new Ennemi033(13*16-3,21*16-9)); addEnnemi(new Ennemi033(51*16-3,5*16-9));
            addEnnemi(new Ennemi033(69*16-3,6*16-9)); addEnnemi(new Ennemi033(91*16-3,107*16-9));
            addEnnemi(new Ennemi033(93*16-3,115*16-9)); addEnnemi(new Ennemi033(129*16-3,111*16-9));
            addEnnemi(new Ennemi033(85*16-3,84*16-9)); addEnnemi(new Ennemi033(109*16-3,87*16-9));
            addEnnemi(new Ennemi033(120*16-3,95*16-9)); addEnnemi(new Ennemi033(128*16-3,84*16-9));
            addEnnemi(new Ennemi033(109*16-3,66*16-9)); addEnnemi(new Ennemi033(147*16-3,66*16-9));
            addEnnemi(new Ennemi033(146*16-3,95*16-9)); addEnnemi(new Ennemi033(152*16-3,98*16-9));
            addEnnemi(new Ennemi033(148*16-3,111*16-9));

            addEnnemi(new Ennemi034(109*16-4+8,111*16-9)); addEnnemi(new Ennemi034(91*16-4,65*16-9));
            addEnnemi(new Ennemi034(89*16-4+8,96*16-9)); addEnnemi(new Ennemi034(129*16-4+8,66*16-9));
            addEnnemi(new Ennemi034(9*16-4,66*16-9)); addEnnemi(new Ennemi034(10*16-4,81*16-9));
            addEnnemi(new Ennemi034(10*16-4,112*16-9)); addEnnemi(new Ennemi034(11*16-4,97*16-9));
            addEnnemi(new Ennemi034(28*16-4,111*16-9)); addEnnemi(new Ennemi034(29*16-4,67*16-9));
            addEnnemi(new Ennemi034(30*16-4,88*16-9)); addEnnemi(new Ennemi034(38*16-4,81*16-9));
            addEnnemi(new Ennemi034(41*16-4,93*16-9)); addEnnemi(new Ennemi034(49*16-4,112*16-9));
            addEnnemi(new Ennemi034(50*16-4,65*16-9)); addEnnemi(new Ennemi034(51*16-4,85*16-9));
            addEnnemi(new Ennemi034(69*16-4,111*16-9)); addEnnemi(new Ennemi034(70*16-4,67*16-9));
            addEnnemi(new Ennemi034(65*16-4,96*16-9)); addEnnemi(new Ennemi034(74*16-4,96*16-9));

            addObject(new Jarre(26*16, 36*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(27*16, 86*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(34*16, 102*16, 0, TI_FLECHE, map));
            addObject(new Jarre(43*16, 19*16, 0, TI_BOMBE, map));
            addObject(new Jarre(49*16, 83*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(53*16, 37*16, 0, TI_FLECHE, map));
            addObject(new Jarre(104*16, 84*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(108*16, 97*16, 0, TI_FLECHE, map));
            addObject(new Jarre(131*16, 81*16, 0, TI_BOMBE, map));
            addObject(new Jarre(135*16, 84*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(148*16, 6*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(151*16, 6*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(186*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(193*16, 4*16, 0, TI_FLECHE, map));
            addObject(new Jarre(226*16, 5*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(227*16, 5*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(232*16, 5*16, 0, TI_BOMBE, map));
            addObject(new Jarre(233*16, 5*16, 0, TI_FLECHE, map));
            break;
        case 54 :
            // mini boss
            if (!scene->getCoffre(9, 56)) {
                addEnnemi(new Ennemi110(70*16+2,6*16));
            } else {
                ouvrePorte(78, 6, 1);
            }
            //boss
            if (!inventory->hasCoeur(8)) {
                addEnnemi(new Ennemi111(198*16, 19*16));
                addObject(new PiegeColere(193*16, 17*16));
                addObject(new PiegeColere(206*16, 17*16));
            }
            if (!inventory->hasObject(TROC_GEMME_BLEUE)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_BLEUE, 200*16, 5*16+8));
            }

            if (scene->getCoffre(9, 52)) {
                addObject(new Coffre(71 * 16, 45 * 16, 0, scene->getCoffre(9, 0), TI_CARTE_DONJON));
            }
            addObject(new Coffre(26 * 16, 65 * 16, 0, scene->getCoffre(9, 1), TI_BOUSSOLE));
            addObject(new Coffre(79 * 16 + 8, 22 * 16, 0, scene->getCoffre(9, 2), TI_CLE_BOSS));

            if (scene->getCoffre(9, 2) == 2) ouvrePorte(199, 28, 0);

            addObject(new Coffre(89 * 16 + 8, 6 * 16 + 8, 1, link->getInventory()->hasObject(BAGUETTE_GLACE), TI_BAGUETTE_GLACE));

            if (scene->getCoffre(9, 51)) {
                addObject(new Coffre(29 * 16, 7 * 16, 0, scene->getCoffre(9, 4), TI_CLE, 4));
            }
            if (scene->getCoffre(9, 46)) {
                addObject(new Coffre(50 * 16, 20 * 16, 0, scene->getCoffre(9, 4), TI_CLE, 5));
                map->setSol(47*16, 20*16, 1935);
                map->setSol(53*16, 20*16, 1935);
            }
            addObject(new Coffre(69 * 16 + 8, 82 * 16, 0, scene->getCoffre(9, 6), TI_CLE, 6));
            addObject(new Coffre(106 * 16, 21 * 16, 0, scene->getCoffre(9, 7), TI_CLE, 7));
            addObject(new Coffre(106 * 16, 82 * 16, 0, scene->getCoffre(9, 8), TI_CLE, 8));
            addObject(new Coffre(129 * 16 + 8, 51 * 16, 0, scene->getCoffre(9, 9), TI_CLE, 9));
            if (scene->getCoffre(9, 53)) {
                addObject(new Coffre(150 * 16, 6 * 16, 0, scene->getCoffre(9, 10), TI_CLE, 10));
            }
            addObject(new Coffre(229 * 16 + 8, 20 * 16, 0, scene->getCoffre(9, 11), TI_CLE, 11));
            if (scene->getCoffre(9, 49)) {
                addObject(new Coffre(249 * 16 + 8, 17 * 16, 0, scene->getCoffre(9, 12), TI_CLE, 12));
                map->setSol(247*16, 17*16, 1935);
                map->setSol(251*16, 17*16, 1935);
            }

            if (scene->getCoffre(9, 13)) ouvrePorte(38, 51, 1);
            if (scene->getCoffre(9, 14)) ouvrePorte(58, 6, 1);
            if (scene->getCoffre(9, 15)) ouvrePorte(58, 51, 1);
            if (scene->getCoffre(9, 16)) ouvrePorte(149, 58, 0);
            if (scene->getCoffre(9, 17)) ouvrePorte(169, 13, 0);
            if (scene->getCoffre(9, 18)) ouvrePorte(178, 36, 1);
            if (scene->getCoffre(9, 19)) ouvrePorte(189, 58, 0);
            if (scene->getCoffre(9, 20)) ouvrePorte(209, 58, 0);
            if (scene->getCoffre(9, 21)) ouvrePorte(218, 51, 1);
            if (scene->getCoffre(9, 22)) ouvrePorte(109, 21, 4);
            if (scene->getCoffre(9, 23)) ouvrePorte(29, 13, 0);
            if (scene->getCoffre(9, 24)) ouvrePorte(69, 73, 0);
            if (scene->getCoffre(9, 25)) ouvrePorte(109, 28, 0);
            if (scene->getCoffre(9, 26)) ouvrePorte(109, 43, 0);
            if (scene->getCoffre(9, 27)) ouvrePorte(118, 6, 1);
            if (scene->getCoffre(9, 28)) ouvrePorte(118, 51, 1);
            if (scene->getCoffre(9, 29)) ouvrePorte(158, 51, 1);
            if (scene->getCoffre(9, 30)) ouvrePorte(169, 28, 0);
            if (scene->getCoffre(9, 31)) ouvrePorte(178, 81, 1);
            if (scene->getCoffre(9, 32)) ouvrePorte(218, 36, 1);
            if (scene->getCoffre(9, 33)) ouvrePorte(229, 73, 0);
            if (scene->getCoffre(9, 34)) ouvrePorte(238, 81, 1);
            if (scene->getCoffre(9, 35)) ouvrePorte(249, 58, 0);
            if (scene->getCoffre(9, 36)) map->setSol(102*16, 71*16, 1936);
            if (scene->getCoffre(9, 37)) map->setSol(115*16, 62*16, 1936);
            if (scene->getCoffre(9, 38)) map->setSol(127*16, 62*16, 1936);
            if (scene->getCoffre(9, 39)) map->setSol(135*16, 62*16, 1936);
            if (scene->getCoffre(9, 40)) map->setSol(133*16, 76*16, 1936);
            if (scene->getCoffre(9, 41)) map->setSol(107*16, 80*16, 1936);
            if (scene->getCoffre(9, 42)) map->setSol(102*16, 86*16, 1936);
            if (scene->getCoffre(9, 43)) map->setSol(107*16, 86*16, 1936);
            if (scene->getCoffre(9, 44)) map->setSol(130*16, 86*16, 1936);
            if (scene->getCoffre(9, 45)) map->setSol(135*16, 83*16, 1936);
            if (scene->getCoffre(9, 36) && scene->getCoffre(9, 37) && scene->getCoffre(9, 38) && scene->getCoffre(9, 39) && scene->getCoffre(9, 40)
                && scene->getCoffre(9, 41) && scene->getCoffre(9, 42) && scene->getCoffre(9, 43) && scene->getCoffre(9, 44) && scene->getCoffre(9, 45))
                    ouvrePorte(129, 58, 0);
            if (scene->getCoffre(9, 47)) {
                map->setSol(80*16, 45*16, 1935);
                ouvrePorte(79, 28, 0);
            }
            if (scene->getCoffre(9, 48)) {
                map->setSol(182*16, 50*16, 1935);
                map->setSol(182*16, 54*16, 1935);
                ouvrePorte(178, 51, 1);
            }
            if (scene->getCoffre(9, 50)) {
                map->setSol(248*16, 37*16, 1935);
                map->setSol(251*16, 37*16, 1935);
                ouvrePorte(249, 28, 0);
            }
            if (scene->getCoffre(9, 54)) ouvrePorte(98, 81, 1);
            if (scene->getCoffre(9, 55)) ouvrePorte(229, 58, 0);
            if (scene->getCoffre(9, 57)) {
                map->setSol(97*16, 2*16, 1935);
                map->setSol(97*16, 12*16, 1935);
                ouvrePorte(98, 6, 1);
            }

            addObject(new Interrupteur(36*16, 21*16, 0, scene->getCoffre(9, 23), map));
            addObject(new Interrupteur(72*16, 77*16, 0, scene->getCoffre(9, 24), map));
            addObject(new Interrupteur(108*16, 17*16, 0, scene->getCoffre(9, 25), map));
            addObject(new Interrupteur(112*16, 47*16, 0, scene->getCoffre(9, 26), map));
            addObject(new Interrupteur(117*16, 10*16, 0, scene->getCoffre(9, 27), map));
            addObject(new Interrupteur(122*16, 55*16, 0, scene->getCoffre(9, 28), map));
            addObject(new Interrupteur(148*16, 55*16, 0, scene->getCoffre(9, 29), map));
            addObject(new Interrupteur(171*16, 40*16, 0, scene->getCoffre(9, 30), map));
            addObject(new Interrupteur(196*16, 82*16, 0, scene->getCoffre(9, 31), map));
            addObject(new Interrupteur(236*16, 37*16, 0, scene->getCoffre(9, 32), map));
            addObject(new Interrupteur(233*16, 67*16, 0, scene->getCoffre(9, 33), map));
            addObject(new Interrupteur(235*16, 85*16, 0, scene->getCoffre(9, 34), map, false)); map->setSol(235*16, 85*16, scene->getCoffre(9, 34) ? 2546 : 2545, PIERRE);
            addObject(new Interrupteur(248*16, 70*16, 0, scene->getCoffre(9, 35), map));

            addObject(new Caisse(88*16, 81*16, 5, 5)); addObject(new Caisse(90*16, 81*16, 5, 3));
            addObject(new Caisse(91*16, 84*16, 5, 3)); addObject(new Caisse(247*16, 39*16, 5));
            addObject(new Caisse(249*16, 35*16, 5)); addObject(new Caisse(250*16, 39*16, 5));
            addObject(new Caisse(130*16, 76*16, 5)); addObject(new Caisse(130*16, 77*16, 5));
            addObject(new Caisse(224*16, 79*16, 5)); addObject(new Caisse(230*16, 52*16, 5, 3));
            addObject(new Caisse(224*16, 85*16, 5)); addObject(new Caisse(235*16, 79*16, 5));
            addObject(new Caisse(235*16, 85*16, 5)); addObject(new Caisse(229*16, 51*16, 5, 1));
            addObject(new Caisse(230*16, 51*16, 5, 4)); addObject(new Caisse(229*16, 52*16, 5, 2));

            addEnnemi(new Ennemi002(109*16-3+8,36*16+6)); addEnnemi(new Ennemi002(67*16-3+8,65*16+6));
            addEnnemi(new Ennemi002(71*16-3+8,68*16+6)); addEnnemi(new Ennemi002(50*16-3+8,51*16+6));
            addEnnemi(new Ennemi002(147*16-3+8,26*16+6)); addEnnemi(new Ennemi002(149*16-3+8,34*16+6));
            addEnnemi(new Ennemi002(152*16-3+8,30*16+6)); addEnnemi(new Ennemi002(209*16-3+8,65*16+6));
            addEnnemi(new Ennemi002(209*16-3+8,81*16+6)); addEnnemi(new Ennemi002(228*16-3+8,36*16+6));

            addEnnemi(new Ennemi041(69*16,42*16-8)); addEnnemi(new Ennemi041(76*16,50*16-8));
            addEnnemi(new Ennemi041(91*16,48*16-8)); addEnnemi(new Ennemi041(127*16,52*16-8));
            addEnnemi(new Ennemi041(130*16,10*16-8));

            addEnnemi(new Ennemi042(111*16-5,77*16-3)); addEnnemi(new Ennemi042(117*16-5,67*16-3));
            addEnnemi(new Ennemi042(121*16-5,75*16-3)); addEnnemi(new Ennemi042(109*16-5,52*16-3));
            addEnnemi(new Ennemi042(30*16-5,82*16-3)); addEnnemi(new Ennemi042(42*16-5,73*16-3));
            addEnnemi(new Ennemi042(31*16-5,33*16-3)); addEnnemi(new Ennemi042(39*16-5,37*16-3));
            addEnnemi(new Ennemi042(46*16-5,26*16-3)); addEnnemi(new Ennemi042(169*16-5,22*16-3));
            addEnnemi(new Ennemi042(191*16-5,40*16-3)); addEnnemi(new Ennemi042(203*16-5,45*16-3));
            addEnnemi(new Ennemi042(249*16-5+8,51*16-3)); addEnnemi(new Ennemi042(89*16-5,67*16-3));

            addEnnemi(new Ennemi062(249*16+4, 81*16, false)); addEnnemi(new Ennemi062(189*16+4, 66*16, false));

            addEnnemi(new Ennemi112(26*16, 6*16)); addEnnemi(new Ennemi112(31*16, 4*16));
            addEnnemi(new Ennemi112(32*16, 9*16)); addEnnemi(new Ennemi112(126*16, 35*16));
            addEnnemi(new Ennemi112(71*16, 36*16)); addEnnemi(new Ennemi112(85*16, 33*16));
            addEnnemi(new Ennemi112(134*16, 69*16)); addEnnemi(new Ennemi112(53*16, 66*16));
            addEnnemi(new Ennemi112(50*16, 79*16)); addEnnemi(new Ennemi112(54*16, 7*16));
            addEnnemi(new Ennemi112(106*16, 7*16)); addEnnemi(new Ennemi112(114*16, 8*16));
            addEnnemi(new Ennemi112(147*16, 6*16)); addEnnemi(new Ennemi112(149*16, 9*16));
            addEnnemi(new Ennemi112(152*16, 7*16)); addEnnemi(new Ennemi112(166*16, 38*16));
            addEnnemi(new Ennemi112(173*16, 37*16)); addEnnemi(new Ennemi112(186*16, 52*16));
            addEnnemi(new Ennemi112(213*16, 36*16)); addEnnemi(new Ennemi112(215*16, 49*16));
            addEnnemi(new Ennemi112(185*16, 82*16)); addEnnemi(new Ennemi112(191*16, 80*16));
            addEnnemi(new Ennemi112(147*16, 75*16)); addEnnemi(new Ennemi112(158*16, 69*16));
            addEnnemi(new Ennemi112(160*16, 81*16)); addEnnemi(new Ennemi112(171*16, 68*16));
            addEnnemi(new Ennemi112(227*16, 80*16)); addEnnemi(new Ennemi112(233*16, 82*16));
            addEnnemi(new Ennemi112(249*16, 24*16)); addEnnemi(new Ennemi112(102*16, 66*16));
            addEnnemi(new Ennemi112(225*16, 67*16));

            addObject(new Jarre(46*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(46*16, 10*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(52*16, 83*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(52*16, 84*16, 0, TI_FLECHE, map));
            addObject(new Jarre(62*16, 45*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(64*16, 45*16, 0, TI_FLECHE, map));
            addObject(new Jarre(84*16, 37*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(113*16, 21*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(122*16, 2*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(136*16, 15*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(137*16, 2*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(137*16, 15*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(144*16, 41*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(149*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(149*16, 63*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(150*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(150*16, 63*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(159*16, 87*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(171*16, 75*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(174*16, 78*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(197*16, 32*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(202*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(215*16, 48*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(216*16, 48*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(217*16, 48*16, 0, TI_BOMBE, map));
            addObject(new Jarre(244*16, 25*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(249*16, 7*16, 0, TI_NO_ITEM, map));
            break;
        case 55 :
            // mini boss
            if (!scene->getCoffre(10, 56)) {
                addEnnemi(new Ennemi113(69*16+2,154*16+2));
                addObject(new PiegeFlamme(64*16, 154*16));
                addObject(new PiegeFlamme(75*16, 155*16));
                addObject(new PiegeFlamme(72*16, 159*16));
                addObject(new PiegeFlamme(66*16, 158*16));
                addObject(new PiegeFlamme(77*16, 159*16));
            } else {
                ouvrePorte(78, 156, 1);
            }
            //boss
            if (!inventory->hasCoeur(9)) {
                addEnnemi(new Ennemi115(66*16, 31*16));
                addEnnemi(new Ennemi116(64*16+1, 34*16-4));
                addEnnemi(new Ennemi117(71*16+1, 34*16-4));
            }
            if (!inventory->hasObject(TROC_GEMME_ROUGE)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_ROUGE, 70*16, 185*16+8));
            }

            if (scene->getCoffre(10, 51)) {
                addObject(new Coffre(9 * 16, 36 * 16, 0, scene->getCoffre(10, 0), TI_CARTE_DONJON));
            }
            if (scene->getCoffre(10, 55)) {
                addObject(new Coffre(110 * 16, 186 * 16, 0, scene->getCoffre(10, 1), TI_BOUSSOLE));
            }
            addObject(new Coffre(69 * 16 + 8, 82 * 16, 0, scene->getCoffre(10, 2), TI_CLE_BOSS));

            if (scene->getCoffre(10, 2) == 2) ouvrePorte(69, 58, 0);

            addObject(new Coffre(89 * 16 + 8, 156 * 16 + 8, 1, link->getInventory()->hasObject(BAGUETTE_FEU), TI_BAGUETTE_FEU));

            if (scene->getCoffre(10, 52)) {
                addObject(new Coffre(50 * 16, 6 * 16, 0, scene->getCoffre(10, 4), TI_CLE, 4));
            }
            if (scene->getCoffre(10, 53)) {
                addObject(new Coffre(69 * 16, 6 * 16, 0, scene->getCoffre(10, 5), TI_CLE, 5));
            }
            if (scene->getCoffre(10, 54)) {
                addObject(new Coffre(89 * 16, 6 * 16, 0, scene->getCoffre(10, 6), TI_CLE, 6));
            }
            addObject(new Coffre(132 * 16, 61 * 16, 0, scene->getCoffre(10, 7), TI_CLE, 7));

            if (scene->getCoffre(10, 8)) ouvrePorte(29, 43, 0);
            if (scene->getCoffre(10, 9)) ouvrePorte(38, 111, 1);
            if (scene->getCoffre(10, 10)) ouvrePorte(58, 156, 1);
            if (scene->getCoffre(10, 11)) ouvrePorte(118, 81, 1);
            if (scene->getCoffre(10, 12)) ouvrePorte(69, 13, 2);
            if (scene->getCoffre(10, 13)) ouvrePorte(18, 141, 1);
            if (scene->getCoffre(10, 14)) ouvrePorte(29, 28, 0);
            if (scene->getCoffre(10, 15)) ouvrePorte(58, 216, 1);
            if (scene->getCoffre(10, 16)) ouvrePorte(78, 216, 1);
            if (scene->getCoffre(10, 17)) ouvrePorte(129, 28, 0);
            if (scene->getCoffre(10, 18)) ouvrePorte(118, 141, 1);
            if (scene->getCoffre(10, 19)) map->setSol(47*16, 57*16, 1936);
            if (scene->getCoffre(10, 20)) map->setSol(52*16, 57*16, 1936);
            if (scene->getCoffre(10, 21)) map->setSol(106*16, 15*16, 1936);
            if (scene->getCoffre(10, 22)) map->setSol(115*16, 2*16, 1936);
            if (scene->getCoffre(10, 23)) map->setSol(119*16, 10*16, 1936);
            if (scene->getCoffre(10, 24)) map->setSol(119*16, 22*16, 1936);
            if (scene->getCoffre(10, 25)) map->setSol(136*16, 4*16, 1936);
            if (scene->getCoffre(10, 26)) map->setSol(134*16, 17*16, 1936);
            if (scene->getCoffre(10, 27)) map->setSol(24*16, 102*16, 1936);
            if (scene->getCoffre(10, 28)) map->setSol(35*16, 102*16, 1936);
            if (scene->getCoffre(10, 29)) map->setSol(55*16, 104*16, 1936);
            if (scene->getCoffre(10, 30)) map->setSol(66*16, 104*16, 1936);
            if (scene->getCoffre(10, 31)) map->setSol(73*16, 104*16, 1936);
            if (scene->getCoffre(10, 32)) map->setSol(84*16, 104*16, 1936);
            if (scene->getCoffre(10, 33)) map->setSol(58*16, 112*16, 1936);
            if (scene->getCoffre(10, 34)) map->setSol(81*16, 112*16, 1936);
            if (scene->getCoffre(10, 35)) map->setSol(55*16, 119*16, 1936);
            if (scene->getCoffre(10, 36)) map->setSol(66*16, 119*16, 1936);
            if (scene->getCoffre(10, 37)) map->setSol(73*16, 119*16, 1936);
            if (scene->getCoffre(10, 38)) map->setSol(84*16, 119*16, 1936);
            if (scene->getCoffre(10, 39)) map->setSol(108*16, 122*16, 1936);
            if (scene->getCoffre(10, 40)) map->setSol(111*16, 122*16, 1936);
            if (scene->getCoffre(10, 41)) map->setSol(108*16, 132*16, 1936);
            if (scene->getCoffre(10, 42)) map->setSol(111*16, 132*16, 1936);
            if (scene->getCoffre(10, 43)) map->setSol(97*16, 152*16, 1936);
            if (scene->getCoffre(10, 44)) map->setSol(97*16, 162*16, 1936);
            if (scene->getCoffre(10, 45)) map->setSol(6*16, 201*16, 1936);
            if (scene->getCoffre(10, 46)) map->setSol(27*16, 201*16, 1936);
            if (scene->getCoffre(10, 47)) map->setSol(30*16, 201*16, 1936);
            if (scene->getCoffre(10, 48)) map->setSol(14*16, 219*16, 1936);
            if (scene->getCoffre(10, 49)) map->setSol(23*16, 213*16, 1936);
            if (scene->getCoffre(10, 50)) map->setSol(27*16, 220*16, 1936);

            if (scene->getCoffre(10, 19) && scene->getCoffre(10, 20)) ouvrePorte(49, 58, 0);
            if (scene->getCoffre(10, 21) && scene->getCoffre(10, 22) && scene->getCoffre(10, 23)
                && scene->getCoffre(10, 20) && scene->getCoffre(10, 25) && scene->getCoffre(10, 26)) ouvrePorte(98, 6, 1);
            if (scene->getCoffre(10, 27) && scene->getCoffre(10, 28)) ouvrePorte(29, 103, 0);
            if (scene->getCoffre(10, 29) && scene->getCoffre(10, 30) && scene->getCoffre(10, 31) && scene->getCoffre(10, 32)
                && scene->getCoffre(10, 33) && scene->getCoffre(10, 34) && scene->getCoffre(10, 35) && scene->getCoffre(10, 36)
                && scene->getCoffre(10, 37) && scene->getCoffre(10, 38)) ouvrePorte(69, 88, 0);
            if (scene->getCoffre(10, 39) && scene->getCoffre(10, 40) && scene->getCoffre(10, 41) && scene->getCoffre(10, 42)) ouvrePorte(98, 126, 1);
            if (scene->getCoffre(10, 43) && scene->getCoffre(10, 44)) ouvrePorte(98, 156, 1);
            if (scene->getCoffre(10, 45) && scene->getCoffre(10, 46) && scene->getCoffre(10, 47)
                && scene->getCoffre(10, 48) && scene->getCoffre(10, 49) && scene->getCoffre(10, 50)) ouvrePorte(38, 201, 1);

            addObject(new Interrupteur(17*16, 145*16, 0, scene->getCoffre(10, 13), map));
            addObject(new Interrupteur(27*16, 27*16, 0, scene->getCoffre(10, 14), map));
            addObject(new Interrupteur(57*16, 220*16, 0, scene->getCoffre(10, 15), map));
            addObject(new Interrupteur(82*16, 220*16, 0, scene->getCoffre(10, 16), map));
            addObject(new Interrupteur(123*16, 37*16, 0, scene->getCoffre(10, 17), map));
            addObject(new Interrupteur(122*16, 145*16, 0, scene->getCoffre(10, 18), map));

            addObject(new InterrupteurStar(69*16, 42*16, false, map));
            addObject(new InterrupteurStar(70*16, 42*16, false, map));

            addObject(new Caisse(118*16, 154*16, 4)); addObject(new Caisse(118*16, 155*16, 4));
            addObject(new Caisse(118*16, 156*16, 4));

            addEnnemi(new Ennemi038(67*16-3,66*16+7)); addEnnemi(new Ennemi038(29*16-3,37*16+7));
            addEnnemi(new Ennemi038(45*16-3,3*16+7)); addEnnemi(new Ennemi038(47*16-3,9*16+7));
            addEnnemi(new Ennemi038(53*16-3,5*16+7)); addEnnemi(new Ennemi038(107*16-3,21*16+7));
            addEnnemi(new Ennemi038(89*16-3,66*16+7)); addEnnemi(new Ennemi038(45*16-3,54*16+7));
            addEnnemi(new Ennemi038(125*16-3,111*16+7)); addEnnemi(new Ennemi038(69*16-3,125*16+7));
            addEnnemi(new Ennemi038(92*16-3,114*16+7)); addEnnemi(new Ennemi038(89*16-3,141*16+7));
            addEnnemi(new Ennemi038(29*16-3,111*16+7)); addEnnemi(new Ennemi038(27*16-3,140*16+7));
            addEnnemi(new Ennemi038(107*16-3,94*16+7)); addEnnemi(new Ennemi038(112*16-3,99*16+7));
            addEnnemi(new Ennemi038(107*16-3,84*16+7)); addEnnemi(new Ennemi038(112*16-3,81*16+7));
            addEnnemi(new Ennemi038(49*16-3,216*16+7)); addEnnemi(new Ennemi038(89*16-3,216*16+7));
            addEnnemi(new Ennemi038(27*16-3,185*16+7)); addEnnemi(new Ennemi038(32*16-3,187*16+7));
            addEnnemi(new Ennemi038(49*16-3,155*16+7)); addEnnemi(new Ennemi038(107*16-3,172*16+7));
            addEnnemi(new Ennemi038(105*16-3,217*16+7)); addEnnemi(new Ennemi038(109*16-3,198*16+7));
            addEnnemi(new Ennemi038(86*16-3,4*16+7)); addEnnemi(new Ennemi038(89*16-3,9*16+7));

            addEnnemi(new Ennemi039(5*16+4,34*16+7)); addEnnemi(new Ennemi039(13*16+4,34*16+7));
            addEnnemi(new Ennemi039(129*16+4,36*16+7)); addEnnemi(new Ennemi039(129*16+4,125*16+7));
            addEnnemi(new Ennemi039(47*16+4,110*16+7)); addEnnemi(new Ennemi039(70*16+4,97*16+7));
            addEnnemi(new Ennemi039(89*16+4,126*16+7)); addEnnemi(new Ennemi039(29*16+4,96*16+7));
            addEnnemi(new Ennemi039(9*16+4,126*16+7)); addEnnemi(new Ennemi039(109*16+4,110*16+7));
            addEnnemi(new Ennemi039(89*16+4,81*16+7)); addEnnemi(new Ennemi039(49*16+4,81*16+7));
            addEnnemi(new Ennemi039(9*16+4,186*16+7)); addEnnemi(new Ennemi039(113*16+4,187*16+7));
            addEnnemi(new Ennemi039(129*16+4,186*16+7)); addEnnemi(new Ennemi039(91*16+4,5*16+7));

            addEnnemi(new Ennemi072(66*16,5*16-10));
            addEnnemi(new Ennemi072(73*16,4*16-10)); addEnnemi(new Ennemi072(17*16,12*16-10));
            addEnnemi(new Ennemi072(12*16,56*16-10)); addEnnemi(new Ennemi072(25*16,66*16-10));
            addEnnemi(new Ennemi072(25*16,53*16-10)); addEnnemi(new Ennemi072(31*16,55*16-10));
            addEnnemi(new Ennemi072(110*16,55*16-10)); addEnnemi(new Ennemi072(121*16,63*16-10));
            addEnnemi(new Ennemi072(122*16,53*16-10)); addEnnemi(new Ennemi072(132*16,65*16-10));

            addEnnemi(new Ennemi118(73*16, 215*16)); addEnnemi(new Ennemi118(5*16, 157*16));
            addEnnemi(new Ennemi118(9*16, 173*16)); addEnnemi(new Ennemi118(11*16, 162*16));
            addEnnemi(new Ennemi118(13*16, 156*16)); addEnnemi(new Ennemi118(17*16, 170*16));
            addEnnemi(new Ennemi118(22*16, 159*16)); addEnnemi(new Ennemi118(23*16, 166*16));
            addEnnemi(new Ennemi118(29*16, 172*16)); addEnnemi(new Ennemi118(31*16, 156*16));
            addEnnemi(new Ennemi118(43*16, 44*16)); addEnnemi(new Ennemi118(44*16, 18*16));
            addEnnemi(new Ennemi118(58*16, 56*16)); addEnnemi(new Ennemi118(83*16, 55*16));
            addEnnemi(new Ennemi118(93*16, 18*16)); addEnnemi(new Ennemi118(94*16, 39*16));
            addEnnemi(new Ennemi118(95*16, 56*16)); addEnnemi(new Ennemi118(9*16, 15*16));
            addEnnemi(new Ennemi118(16*16, 20*16)); addEnnemi(new Ennemi118(23*16, 9*16));
            addEnnemi(new Ennemi118(25*16, 14*16)); addEnnemi(new Ennemi118(27*16, 20*16));
            addEnnemi(new Ennemi118(31*16, 15*16)); addEnnemi(new Ennemi118(9*16, 38*16));
            addEnnemi(new Ennemi118(106*16, 37*16)); addEnnemi(new Ennemi118(107*16, 65*16));
            addEnnemi(new Ennemi118(115*16, 67*16)); addEnnemi(new Ennemi118(127*16, 51*16));
            addEnnemi(new Ennemi118(46*16, 66*16)); addEnnemi(new Ennemi118(52*16, 68*16));
            addEnnemi(new Ennemi118(6*16, 106*16)); addEnnemi(new Ennemi118(8*16, 112*16));
            addEnnemi(new Ennemi118(10*16, 96*16)); addEnnemi(new Ennemi118(11*16, 104*16));
            addEnnemi(new Ennemi118(13*16, 100*16)); addEnnemi(new Ennemi118(131*16, 105*16));
            addEnnemi(new Ennemi118(132*16, 97*16)); addEnnemi(new Ennemi118(132*16, 110*16));
            addEnnemi(new Ennemi118(105*16, 126*16)); addEnnemi(new Ennemi118(114*16, 127*16));
            addEnnemi(new Ennemi118(50*16, 96*16)); addEnnemi(new Ennemi118(50*16, 125*16));
            addEnnemi(new Ennemi118(79*16, 93*16)); addEnnemi(new Ennemi118(90*16, 101*16));
            addEnnemi(new Ennemi118(92*16, 95*16)); addEnnemi(new Ennemi118(28*16, 125*16));
            addEnnemi(new Ennemi118(33*16, 128*16)); addEnnemi(new Ennemi118(31*16, 143*16));
            addEnnemi(new Ennemi118(46*16, 141*16)); addEnnemi(new Ennemi118(51*16, 143*16));
            addEnnemi(new Ennemi118(54*16, 139*16)); addEnnemi(new Ennemi118(107*16, 141*16));
            addEnnemi(new Ennemi118(113*16, 144*16)); addEnnemi(new Ennemi118(26*16, 81*16));
            addEnnemi(new Ennemi118(33*16, 84*16)); addEnnemi(new Ennemi118(6*16, 205*16));
            addEnnemi(new Ennemi118(11*16, 212*16)); addEnnemi(new Ennemi118(17*16, 201*16));
            addEnnemi(new Ennemi118(20*16, 209*16)); addEnnemi(new Ennemi118(32*16, 210*16));
            addEnnemi(new Ennemi118(44*16, 194*16)); addEnnemi(new Ennemi118(45*16, 170*16));
            addEnnemi(new Ennemi118(56*16, 204*16)); addEnnemi(new Ennemi118(62*16, 169*16));
            addEnnemi(new Ennemi118(85*16, 170*16)); addEnnemi(new Ennemi118(87*16, 205*16));
            addEnnemi(new Ennemi118(93*16, 194*16)); addEnnemi(new Ennemi118(95*16, 180*16));
            addEnnemi(new Ennemi118(123*16, 155*16)); addEnnemi(new Ennemi118(130*16, 172*16));
            addEnnemi(new Ennemi118(106*16, 184*16)); addEnnemi(new Ennemi118(108*16, 190*16));
            addEnnemi(new Ennemi118(113*16, 205*16)); addEnnemi(new Ennemi118(117*16, 213*16));
            addEnnemi(new Ennemi118(125*16, 203*16));

            addObject(new Jarre(4*16, 117*16, 0, TI_FLECHE, map));
            addObject(new Jarre(21*16, 197*16, 0, TI_BOMBE, map));
            addObject(new Jarre(23*16, 154*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 87*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 94*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(33*16, 169*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(37*16, 154*16, 0, TI_FLECHE, map));
            addObject(new Jarre(42*16, 154*16, 0, TI_FLECHE, map));
            addObject(new Jarre(42*16, 160*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(44*16, 152*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(45*16, 115*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(55*16, 152*16, 0, TI_FLECHE, map));
            addObject(new Jarre(56*16, 95*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(56*16, 128*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(65*16, 65*16, 0, TI_FLECHE, map));
            addObject(new Jarre(66*16, 92*16, 0, TI_FLECHE, map));
            addObject(new Jarre(75*16, 132*16, 0, TI_BOMBE, map));
            addObject(new Jarre(76*16, 204*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(76*16, 205*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(81*16, 186*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(95*16, 116*16, 0, TI_FLECHE, map));
            addObject(new Jarre(104*16, 87*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(115*16, 87*16, 0, TI_FLECHE, map));
            addObject(new Jarre(116*16, 154*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(116*16, 155*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(116*16, 156*16, 0, TI_FLECHE, map));
            addObject(new Jarre(127*16, 94*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(133*16, 203*16, 0, TI_FLECHE, map));
            addObject(new Jarre(133*16, 204*16, 0, TI_NO_ITEM, map));
            break;
        case 56 :
            // mini boss
            if (!scene->getCoffre(11, 19)) {
                addEnnemi(new Ennemi076(106*16+2, 95*16));
                addObject(new PiegeDemi(104*16, 92*16));
                addObject(new PiegeDemi(104*16, 102*16));
            } else {
                ouvrePorte(98, 96, 1);
            }
            //boss
            if (!inventory->hasCoeur(10)) {
                addEnnemi(new Ennemi120(169*16, 17*16));
            } else if (link->getEpee() < 5) {
                addObject(new Pnj(16*169-2+8, 16*6+5-8, 90, 1277));
            }
            if (link->getEpee() < 5) {
                addItem(ItemHelper::getInstance()->createItem(TI_TRIFORCE, 170*16, 5*16+8, 0, false));
            }

            if (!inventory->hasGemmeForce(195)) {
                addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, 5*16 + 8, 83*16 + 8, 195, false));
            }

            if (scene->getCoffre(11, 15)) {
                addObject(new Coffre(90 * 16, 51 * 16, 0, scene->getCoffre(11, 0), TI_CARTE_DONJON));
            }
            if (scene->getCoffre(11, 17)) {
                addObject(new Coffre(149 * 16, 6 * 16, 0, scene->getCoffre(11, 1), TI_BOUSSOLE));
            }
            addObject(new Coffre(69 * 16 + 8, 6 * 16, 0, scene->getCoffre(11, 2), TI_CLE_BOSS));

            if (scene->getCoffre(11, 2) == 2) ouvrePorte(169, 28, 0);

            addObject(new Coffre(89 * 16 + 8, 96 * 16 + 8, 1, link->getBouclier() >= 3, TI_BOUCLIER_3));

            if (scene->getCoffre(11, 14)) {
                addObject(new Coffre(30 * 16, 21 * 16, 0, scene->getCoffre(11, 4), TI_CLE, 4));
            }
            if (scene->getCoffre(11, 16)) {
                addObject(new Coffre(109 * 16, 21 * 16, 0, scene->getCoffre(11, 5), TI_CLE, 5));
            }
            if (scene->getCoffre(11, 18)) {
                addObject(new Coffre(190 * 16, 6 * 16, 0, scene->getCoffre(11, 6), TI_CLE, 6));
            }

            if (scene->getCoffre(11, 7)) ouvrePorte(69, 13, 0);
            if (scene->getCoffre(11, 8)) ouvrePorte(69, 28, 0);
            if (scene->getCoffre(11, 9)) ouvrePorte(118, 96, 1);
            if (scene->getCoffre(11, 10)) ouvrePorte(38, 21, 1);
            if (scene->getCoffre(11, 11)) ouvrePorte(49, 28, 0);
            if (scene->getCoffre(11, 13)) ouvrePorte(118, 6, 1);

            addObject(new Interrupteur(37*16, 25*16, 0, scene->getCoffre(11, 10), map));
            addObject(new Interrupteur(43*16, 37*16, 0, scene->getCoffre(11, 11), map));
            addObject(new Interrupteur(54*16, 97*16, 0, scene->getCoffre(11, 12), map));
            addObject(new Interrupteur(103*16, 7*16, 0, scene->getCoffre(11, 13), map));

            if (scene->getCoffre(11, 12)) {
                addEnnemi(new Ennemi119(69*16-3+8,38*16+5)); addEnnemi(new Ennemi119(69*16-3+8,50*16+5));
                addEnnemi(new Ennemi119(48*16-3+8,96*16+5)); addEnnemi(new Ennemi119(86*16-3+8,49*16+5));
                addEnnemi(new Ennemi119(91*16-3+8,54*16+5)); addEnnemi(new Ennemi119(49*16-3+8,51*16+5));
                addEnnemi(new Ennemi119(9*16-3+8,38*16+5)); addEnnemi(new Ennemi119(27*16-3+8,38*16+5));
                addEnnemi(new Ennemi119(17*16-3+8,53*16+5)); addEnnemi(new Ennemi119(33*16-3+8,46*16+5));
                addEnnemi(new Ennemi119(49*16-3+8,37*16+5)); addEnnemi(new Ennemi119(9*16-3+8,68*16+5));
                addEnnemi(new Ennemi119(9*16-3+8,78*16+5)); addEnnemi(new Ennemi119(7*16-3+8,97*16+5));
                addEnnemi(new Ennemi119(19*16-3+8,95*16+5)); addEnnemi(new Ennemi119(29*16-3+8,98*16+5));
                addEnnemi(new Ennemi119(87*16-3+8,35*16+5)); addEnnemi(new Ennemi119(91*16-3+8,39*16+5));
                addEnnemi(new Ennemi119(129*16-3+8,97*16+5)); addEnnemi(new Ennemi119(109*16-3+8,34*16+5));
                addEnnemi(new Ennemi119(106*16-3+8,19*16+5)); addEnnemi(new Ennemi119(112*16-3+8,23*16+5));
                addEnnemi(new Ennemi119(110*16-3+8,53*16+5)); addEnnemi(new Ennemi119(127*16-3+8,51*16+5));
                addEnnemi(new Ennemi119(129*16-3+8,36*16+5)); addEnnemi(new Ennemi119(129*16-3+8,69*16+5));
                addEnnemi(new Ennemi119(129*16-3+8,78*16+5)); addEnnemi(new Ennemi119(129*16-3+8,14*16+5));
            } else {
                addObject(new StatueGarde(65*16+5, 31*16+5-8)); addObject(new StatueGarde(73*16+5, 31*16+5-8));
                addObject(new StatueGarde(45*16+5, 93*16+5-8)); addObject(new StatueGarde(85*16+5, 46*16+5-8));
                addObject(new StatueGarde(93*16+5, 46*16+5-8)); addObject(new StatueGarde(49*16+5, 46*16+5-8));
                addObject(new StatueGarde(7*16+5, 33*16+5-8)); addObject(new StatueGarde(23*16+5, 35*16+5-8));
                addObject(new StatueGarde(16*16+5, 50*16+5-8)); addObject(new StatueGarde(25*16+5, 50*16+5-8));
                addObject(new StatueGarde(53*16+5, 31*16+5-8)); addObject(new StatueGarde(7*16+5, 61*16+5-8));
                addObject(new StatueGarde(11*16+5, 61*16+5-8)); addObject(new StatueGarde(16*16+5, 93*16+5-8));
                addObject(new StatueGarde(25*16+5, 93*16+5-8)); addObject(new StatueGarde(34*16+5, 93*16+5-8));
                addObject(new StatueGarde(86*16+5, 31*16+5-8)); addObject(new StatueGarde(92*16+5, 31*16+5-8));
                addObject(new StatueGarde(126*16+5, 91*16+5-8)); addObject(new StatueGarde(113*16+5, 31*16+5-8));
                addObject(new StatueGarde(105*16+5, 16*16+5-8)); addObject(new StatueGarde(113*16+5, 16*16+5-8));
                addObject(new StatueGarde(115*16+5, 48*16+5-8)); addObject(new StatueGarde(123*16+5, 48*16+5-8));
                addObject(new StatueGarde(125*16+5-8, 33*16+5-8)); addObject(new StatueGarde(125*16+5, 61*16+5-8));
                addObject(new StatueGarde(133*16+5, 61*16+5-8)); addObject(new StatueGarde(129*16+5, 3*16+5-8));
            }
            addEnnemi(new Ennemi119(49*16-3+8,21*16+5)); addEnnemi(new Ennemi119(48*16-3+8,6*16+5));
            addEnnemi(new Ennemi119(7*16-3+8,23*16+5)); addEnnemi(new Ennemi119(19*16-3+8,20*16+5));
            addEnnemi(new Ennemi119(31*16-3+8,23*16+5)); addEnnemi(new Ennemi119(10*16-3+8,6*16+5));
            addEnnemi(new Ennemi119(27*16-3+8,6*16+5)); addEnnemi(new Ennemi119(89*16-3+8,21*16+5));
            addEnnemi(new Ennemi119(149*16-3+8,22*16+5)); addEnnemi(new Ennemi119(149*16-3+8,32*16+5));
            addEnnemi(new Ennemi119(189*16-3+8,22*16+5)); addEnnemi(new Ennemi119(189*16-3+8,32*16+5));
            addEnnemi(new Ennemi119(146*16-3+8,5*16+5)); addEnnemi(new Ennemi119(152*16-3+8,5*16+5));
            addEnnemi(new Ennemi119(187*16-3+8,5*16+5)); addEnnemi(new Ennemi119(193*16-3+8,5*16+5));
            addEnnemi(new Ennemi119(169*16-3+8,36*16+5)); addEnnemi(new Ennemi119(90*16-3+8,6*16+5));
            addEnnemi(new Ennemi119(69*16-3+8,21*16+5));

            addObject(new Jarre(4*16, 4*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(4*16, 34*16, 0, TI_FLECHE, map));
            addObject(new Jarre(44*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(55*16, 94*16, 0, TI_FLECHE, map));
            addObject(new Jarre(55*16, 100*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(86*16, 92*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(86*16, 102*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(104*16, 12*16, 0, TI_FLECHE, map));
            addObject(new Jarre(135*16, 102*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(164*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(175*16, 32*16, 0, TI_FLECHE, map));
            break;
        case 57 :
            //générique fin
            if (link->getY() == 25 * 16 + 8 && inventory->hasObject(TRIFORCE)) {
                addObject(new Pnj(16*69+8, 16*21+8+1, 15, 1663));
                addObject(new Pnj(16*75+8, 16*22+5, 90, 1660));
            }

            if (scene->getAvancement() >= AV_SPEECH_VINCENT) {
                ouvrePorte(146, 0, 5);
            }

            addObject(new Coffre(87 * 16, 6 * 16, 0, link->getBouclier() > 0, TI_BOUCLIER_1));
            addObject(new Coffre(92 * 16, 6 * 16, 0, link->getStatus()->getMaxRupees() > 0, TI_BOURSE_RUBIS_1));

            addObject(new Coffre(109 * 16, 170 * 16 + 8, 1, scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_UTILISE || inventory->hasObject(OCARINA), TI_OCARINA));

            addObject(new Coffre(4 * 16, 4 * 16, 0, scene->getCoffre(12, 12), TI_SAC_RIZ));
            addObject(new Coffre(6 * 16, 4 * 16, 0, scene->getCoffre(12, 13), TI_SAC_OLIVES));

            addObject(new Coffre(69 * 16 + 8, 156 * 16, 0, scene->getCoffre(12, 0), TI_CARTE_DONJON));
            addObject(new Coffre(105 * 16, 18 * 16, 0, scene->getCoffre(12, 1), TI_BOUSSOLE));
            addObject(new Coffre(72 * 16, 229 * 16, 0, scene->getCoffre(12, 2), TI_CLE_BOSS));

            if (scene->getCoffre(12, 2) == 2) ouvrePorte(169, 28, 0);
            if (scene->getMonsters(50)) {
                ouvrePorte(169, 13, 0);
                ouvrePorte(158, 21, 1);
                ouvrePorte(178, 21, 1);
                ouvrePorte(78, 156, 1);
                ouvrePorte(89, 178, 0);
            }

            addObject(new Coffre(89 * 16, 185 * 16 + 8, 1, link->getTunique() > 2, TI_TUNIQUE_ROUGE));

            addObject(new Coffre(51 * 16, 97 * 16, 0, scene->getCoffre(12, 4), TI_CLE, 4));
            addObject(new Coffre(87 * 16, 94 * 16, 0, scene->getCoffre(12, 5), TI_CLE, 5));
            addObject(new Coffre(189 * 16 + 8, 6 * 16, 0, scene->getCoffre(12, 6), TI_CLE, 6));

            if (scene->getCoffre(12, 7)) ouvrePorte(49, 238, 0);
            if (scene->getCoffre(12, 8)) ouvrePorte(5, 233, 4);
            if (scene->getCoffre(12, 9)) ouvrePorte(72, 233, 4);

            if ((scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_UTILISE || scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_FERME)) {
                if (scene->getAvancement() >= AV_PARLE_GARDE_SOUS_SOL) ouvrePorte(98, 171, 1);
                if (scene->getAvancement() >= AV_PASSAGE_TROUVE) ouvrePorte(109, 163, 2);
            } else {
                if (scene->getCoffre(12, 10)) ouvrePorte(109, 163, 2);
            }

            if (link->getInventory()->getTrocGemme(2) > TGJ_MIROIR) {
                map->setSol(62*16, 5*16, 6225);
                map->setSol(63*16, 5*16, 6226);
            }

            if (scene->getAvancement() < AV_TELE_ZELDA) {

                addObject(new Pnj(82*16+5-8, 156*16+5, 58, 1317, E));
                addObject(new Pnj(89*16+5, 176*16+5, 58, 1317, N));
                addObject(new Pnj(169*16+5, 31*16+5, 58, 1362, S));
                addObject(new Pnj(162*16+5-8, 36*16+5, 58, 1362, E));
                addObject(new Pnj(177*16+5-8, 36*16+5, 58, 1362, W));

                if (link->getEpee() == 0 && !inventory->hasObject(OCARINA)) {
                    if (scene->getAvancement() < AV_ZELDA_SOUS_SOL) {
                        addObject(new Pnj(16*69+8, 16*21+1+8, 15, 1312));
                    } else {
                        addObject(new Pnj(16*102+8, 16*171+1+8, 15, 1321, E));
                    }
                    addObject(new Pnj(62*16+5-8, 36*16+5, 58, 1300, E));
                    addObject(new Pnj(62*16+5-8, 51*16+5, 58, 1300, E));
                    if (scene->getAvancement() < AV_PARLE_GARDE_RESERVE) {
                        addObject(new Pnj(77*16+5-8, 36*16+5, 58, 1304, W));
                    } else {
                        addObject(new Pnj(77*16+5-8, 34*16+5, 58, 1305, W));
                    }
                    if (scene->getAvancement() < AV_PARLE_GARDE_CH_FORTE) {
                        addObject(new Pnj(77*16+5-8, 51*16+5, 58, 1316, W));
                    } else {
                        addObject(new Pnj(77*16+5-8, 49*16+5, 58, 1306, W));
                    }
                    if (scene->getAvancement() < AV_RESERVE_VIDE) {
                        addObject(new Pnj(69*16+5, 31*16+5, 58, 1301));
                    } else {
                        addObject(new Pnj(67*16+5, 31*16+5, 58, 1309));
                    }
                    addObject(new Pnj(97*16+5-8, 36*16+5, 58, 1306, W));
                    if (scene->getAvancement() < AV_PARLE_GARDE_SOUS_SOL) {
                        addObject(new Pnj(97*16+5-8, 171*16+5, 58, 1318, W));
                    } else {
                        addObject(new Pnj(97*16+5-8, 169*16+5, 58, 1319, W));
                    }
                    if (scene->getAvancement() < AV_PASSAGE_TROUVE) {
                        addObject(new TalkableArea(16*113, 16*167, 1322));
                        addObject(new TalkableArea(16*113, 16*175, 1322));
                        addObject(new TalkableArea(16*109, 16*170+8, 1323));
                        addObject(new TalkableArea(16*110, 16*170+8, 1323));
                        addObject(new TalkableArea(16*109, 16*171, 1323));
                        addObject(new TalkableArea(16*110, 16*171, 1323));
                        addObject(new TalkableArea(16*109, 16*166, 1324));
                        addObject(new TalkableArea(16*110, 16*166, 1324));
                        addObject(new TalkableArea(16*107, 16*173, 1325));
                    }
                } else {
                    if (scene->getAvancement() >= AV_RETOUR_PRESENT) {
                        addObject(new Pnj(16*69+8, 16*21+1+8, 15, 1355));
                    }
                    addObject(new Pnj(97*16+5-8, 169*16+5, 58, 1328, W));
                    addObject(new Pnj(49*16+5, 49*16+5, 58, 1333, N));
                    addObject(new Pnj(122*16+5-8, 6*16+5, 58, 1334, E));
                    addObject(new Pnj(117*16+5-8, 6*16+5, 58, 1335, W));
                    addObject(new Pnj(85*16+5, 48*16+5, 58, 1336));
                    addObject(new Pnj(66*16+5, 31*16+5, 58, 1337));
                    addObject(new Pnj(72*16+5, 31*16+5, 58, 1338));
                    addObject(new Pnj(45*16+5, 31*16+5, 58, 1339));
                    addObject(new Pnj(9*16+5, 57*16+5-8, 58, 1350, N));
                    addObject(new Pnj(129*16+5, 57*16+5-8, 58, 1351, N));
                    addObject(new Pnj(86*16+5, 31*16+5, 58, 1352));
                    addObject(new Pnj(107*16+5, 18*16+5, 58, 1353));

                    addObject(new Pnj(7*16+2, 35*16+6, 102, 1340));
                    addObject(new Pnj(6*16, 37*16+6, 103, 1341));
                    addObject(new Pnj(10*16, 35*16, 104, 1342));
                    addObject(new Pnj(12*16, 5*16, 106, 1346));
                    addObject(new Pnj(6*16, 8*16, 107, 1347));
                    addObject(new Pnj(21*16, 5*16, 108, 1348));
                    addObject(new Pnj(11*16, 22*16, 36, 1349));
                }
            } else {
                // mini boss
                if (!scene->getCoffre(12, 11)) {
                    addEnnemi(new Ennemi031(49*16, 227*16));
                } else {
                    ouvrePorte(38, 231, 1);
                    ouvrePorte(58, 231, 1);
                }
                //boss
                if (!scene->getMonsters(50)) {
                    addEnnemi(new Ennemi050(169*16-10, 17*16-4+8));
                    addObject(new Pnj(16*5, 16*228+1+8, 15, 1355));

                    addEnnemi(new Ennemi046(67*16-3+8,35*16+5)); addEnnemi(new Ennemi046(68*16-3+8,48*16+5));
                    addEnnemi(new Ennemi046(72*16-3+8,42*16+5)); addEnnemi(new Ennemi046(8*16-3+8,7*16+5));
                    addEnnemi(new Ennemi046(20*16-3+8,4*16+5)); addEnnemi(new Ennemi046(30*16-3+8,8*16+5));
                    addEnnemi(new Ennemi046(8*16-3+8,21*16+5)); addEnnemi(new Ennemi046(14*16-3+8,25*16+5));
                    addEnnemi(new Ennemi046(26*16-3+8,26*16+5)); addEnnemi(new Ennemi046(33*16-3+8,19*16+5));
                    addEnnemi(new Ennemi046(4*16-3+8,96*16+5)); addEnnemi(new Ennemi046(9*16-3+8,99*16+5));
                    addEnnemi(new Ennemi046(17*16-3+8,94*16+5)); addEnnemi(new Ennemi046(22*16-3+8,99*16+5));
                    addEnnemi(new Ennemi046(28*16-3+8,95*16+5)); addEnnemi(new Ennemi046(89*16-3+8,21*16+5));
                    addEnnemi(new Ennemi046(105*16-3+8,5*16+5));
                    addEnnemi(new Ennemi046(109*16-3+8,52*16+5)); addEnnemi(new Ennemi046(117*16-3+8,53*16+5));
                    addEnnemi(new Ennemi046(126*16-3+8,50*16+5)); addEnnemi(new Ennemi046(127*16-3+8,81*16+5));
                    addEnnemi(new Ennemi046(128*16-3+8,71*16+5)); addEnnemi(new Ennemi046(133*16-3+8,76*16+5));

                    addEnnemi(new Ennemi047(85*16-3+8,48*16+5));
                    addEnnemi(new Ennemi047(47*16-3+8,47*16+5)); addEnnemi(new Ennemi047(51*16-3+8,55*16+5));
                    addEnnemi(new Ennemi047(47*16-3+8,6*16+5));
                    addEnnemi(new Ennemi047(47*16-3+8,22*16+5)); addEnnemi(new Ennemi047(46*16-3+8,34*16+5));
                    addEnnemi(new Ennemi047(53*16-3+8,39*16+5)); addEnnemi(new Ennemi047(32*16-3+8,97*16+5));
                    addEnnemi(new Ennemi047(86*16-3+8,34*16+5)); addEnnemi(new Ennemi047(92*16-3+8,40*16+5));
                    addEnnemi(new Ennemi047(106*16-3+8,26*16+5)); addEnnemi(new Ennemi047(110*16-3+8,18*16+5));
                    addEnnemi(new Ennemi047(125*16-3+8,35*16+5));
                    addEnnemi(new Ennemi047(133*16-3+8,38*16+5));
                    addEnnemi(new Ennemi047(110*16-3+8,99*16+5));
                    addEnnemi(new Ennemi047(129*16-3+8,99*16+5));

                    addEnnemi(new Ennemi048(86*16-3+8,171*16+5)); addEnnemi(new Ennemi048(93*16-3+8,173*16+5));
                    addEnnemi(new Ennemi048(86*16-3+8,156*16+5)); addEnnemi(new Ennemi048(11*16-3+8,236*16+5));
                    addEnnemi(new Ennemi048(21*16-3+8,235*16+5)); addEnnemi(new Ennemi048(30*16-3+8,236*16+5));
                    addEnnemi(new Ennemi048(71*16-3+8,235*16+5)); addEnnemi(new Ennemi048(17*16-3+8,40*16+5, true));
                    addEnnemi(new Ennemi048(21*16-3+8,48*16+5, true)); addEnnemi(new Ennemi048(27*16-3+8,43*16+5, true));
                    addEnnemi(new Ennemi048(7*16-3+8,69*16+5)); addEnnemi(new Ennemi048(9*16-3+8,81*16+5));
                    addEnnemi(new Ennemi048(11*16-3+8,75*16+5)); addEnnemi(new Ennemi048(47*16-3+8,95*16+5));
                    addEnnemi(new Ennemi048(69*16-3+8,22*16+5)); addEnnemi(new Ennemi048(127*16-3+8,21*16+5));
                    addEnnemi(new Ennemi048(129*16-3+8,7*16+5)); addEnnemi(new Ennemi048(132*16-3+8,16*16+5));
                    addEnnemi(new Ennemi048(109*16-3+8,35*16+5)); addEnnemi(new Ennemi048(91*16-3+8,98*16+5));
                    addEnnemi(new Ennemi048(147*16-3+8,26*16+5)); addEnnemi(new Ennemi048(149*16-3+8,34*16+5));
                    addEnnemi(new Ennemi048(152*16-3+8,21*16+5)); addEnnemi(new Ennemi048(167*16-3+8,36*16+5));
                    addEnnemi(new Ennemi048(171*16-3+8,36*16+5)); addEnnemi(new Ennemi048(187*16-3+8,21*16+5));
                    addEnnemi(new Ennemi048(189*16-3+8,7*16+5)); addEnnemi(new Ennemi048(189*16-3+8,34*16+5));
                    addEnnemi(new Ennemi048(192*16-3+8,27*16+5)); addEnnemi(new Ennemi048(45*16-3+8,245*16+5));
                } else {
                    addObject(new Pnj(16*169+8, 16*19+1, 15, 1355));
                    if (GlobalSave::getInstance()->is9Ranks() && scene->getMonsters(141)) {
                        ouvrePorte(149, 13, 0);
                        addObject(new Pnj(147*16+5+8, 16*16+5, 58, 1389));
                        addObject(new Pnj(149*16+8, 4*16, 112, 1390));
                        addObject(new Pnj(154*16+2, 8*16+6, 113, 1392));
                        addObject(new Pnj(145*16, 8*16, 114, 1393));
                    } else {
                        addObject(new Pnj(147*16+5+8, 16*16+5, 58, 1388));
                    }
                }
                addEnnemi(new Ennemi089(169*16+6, 4*16, 1));
            }

            addObject(new Pnj(16*6, 16*48-8, 105, 1344)); addObject(new TalkableArea(16*6, 16*50, 1344));

            addEnnemi(new Ennemi121(113*16,157*16)); addEnnemi(new Ennemi121(126*16,158*16));
            addEnnemi(new Ennemi121(129*16,172*16)); addEnnemi(new Ennemi121(144*16,171*16));
            addEnnemi(new Ennemi121(146*16,185*16)); addEnnemi(new Ennemi121(151*16,189*16));
            addEnnemi(new Ennemi121(154*16,186*16)); addEnnemi(new Ennemi121(119*16,156*16));
            addEnnemi(new Ennemi121(138*16,173*16)); addEnnemi(new Ennemi121(145*16,200*16));
            addEnnemi(new Ennemi121(153*16,205*16));

            addObject(new Jarre(4*16, 27*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(88*16, 17*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(88*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(89*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(90*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(91*16, 18*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(91*16, 17*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(115*16, 32*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(164*16, 32*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(175*16, 32*16, 0, TI_MAGIE_PEU, map));
            break;
        case 58 :
            //boss
            if (!inventory->hasCoeur(11)) {
                addEnnemi(new Ennemi127(67*16+9, 32*16+1));
            }

            addObject(new Coffre(69 * 16 + 8, 6 * 16, 0, scene->getCoffre(13, 2), TI_CLE_BOSS));

            if (scene->getCoffre(13, 2) == 2) ouvrePorte(69, 43, 0);

            addObject(new Coffre(65 * 16 + 8, 20 * 16 + 8, 1, link->getBouclier() >= 4, TI_BOUCLIER_4));

            if (scene->getCoffre(13, 9)) ouvrePorte(38, 96, 1);
            if (scene->getCoffre(13, 10)) ouvrePorte(69, 58, 0);
            if (scene->getCoffre(13, 11)) ouvrePorte(78, 6, 1);
            if (scene->getCoffre(13, 12)) ouvrePorte(98, 6, 1);
            if (scene->getCoffre(13, 13)) ouvrePorte(118, 6, 1);
            if (scene->getCoffre(13, 14)) ouvrePorte(18, 66, 3);
            if (scene->getCoffre(13, 15)) ouvrePorte(118, 66, 3);
            if (scene->getCoffre(13, 16)) ouvrePorte(18, 36, 1);
            if (scene->getCoffre(13, 17)) ouvrePorte(129, 43, 0);

            addObject(new Interrupteur(11*16, 41*16, 0, scene->getCoffre(13, 16), map));
            addObject(new Interrupteur(123*16, 37*16, 0, scene->getCoffre(13, 17), map));

            addObject(new Stele(16*72, 16*20, 1628, false));

            if (!link->getInventory()->hasObject(TRIFORCE)) {
                addObject(new Pnj(16*73, 16*94+8, 6, 1429));
                break;
            }
            addObject(new Pnj(16*73, 16*94+8, 6, 1430));
            addObject(new Pnj(16*64, 16*92+8, 6, 1424, N)); addObject(new TalkableArea(16*64, 16*94, 1425));
            addObject(new Pnj(16*29+8, 16*66, 6, 1435, N));
            addObject(new Pnj(16*49+8, 16*6, 6, 1441, N));
            addObject(new Pnj(16*30+8, 16*5, 6, 1445, W));
            addObject(new Pnj(16*130+8, 16*95, 6, 1447, W));
            addObject(new Pnj(16*13+8, 16*81, 6, 1448, N));
            addObject(new Pnj(16*109+8, 16*66, 6, 1449, W));
            addObject(new Pnj(16*126+8, 16*83, 6, 1454, N));
            addObject(new Pnj(16*91+8, 16*21, 6, 1455, N));
            addObject(new Pnj(16*129+8, 16*6, 6, 1458));

            addObject(new Dices(16*25, 16*63, true)); addObject(new Dices(16*28, 16*63, true));
            addObject(new Dices(16*31, 16*63, true)); addObject(new Dices(16*34, 16*63, true));

            addObject(new Dices(16*46, 16*3, false)); addObject(new Dices(16*49, 16*3, false)); addObject(new Dices(16*52, 16*3, false));

            addObject(new Dices(16*3, 16*78, false)); addObject(new Dices(16*5, 16*78, false)); addObject(new Dices(16*7, 16*78, false));
            addObject(new Dices(16*12, 16*78, false)); addObject(new Dices(16*15, 16*78, false));

            addObject(new Dices(16*103, 16*63, false)); addObject(new Dices(16*116, 16*63, false));
            addObject(new Dices(16*103, 16*71, false)); addObject(new Dices(16*116, 16*71, false));

            addObject(new Dices(16*123, 16*86, false, false, false, map, new Caisse(134*16, 83*16, 4, 0)));
            addObject(new Dices(16*126, 16*86, false, false, false, map, new Caisse(134*16, 84*16, 4, 0)));
            addObject(new Dices(16*129, 16*86, false, false, false, map, new Caisse(134*16, 85*16, 4, 0)));

            addObject(new Dices(16*83, 16*18, false)); addObject(new Dices(16*87, 16*18, false)); addObject(new Dices(16*90, 16*18, false));
            addObject(new Dices(16*93, 16*18, false)); addObject(new Dices(16*96, 16*18, false));

            addEnnemi(new Ennemi123(69*16+5,69*16)); addEnnemi(new Ennemi123(69*16+5,78*16));
            addEnnemi(new Ennemi123(49*16+5,66*16)); addEnnemi(new Ennemi123(49*16+5,81*16));
            addEnnemi(new Ennemi123(89*16+5,66*16)); addEnnemi(new Ennemi123(89*16+5,81*16));
            addEnnemi(new Ennemi123(129*16+5,21*16)); addEnnemi(new Ennemi123(69*16+5,51*16));
            addEnnemi(new Ennemi123(49*16+5,36*16)); addEnnemi(new Ennemi123(89*16+5,36*16));
            addEnnemi(new Ennemi123(109*16+5,36*16)); addEnnemi(new Ennemi123(89*16+5,96*16));
            addEnnemi(new Ennemi123(99*16+5,100*16)); addEnnemi(new Ennemi123(109*16+5,94*16));
            addEnnemi(new Ennemi123(29*16+5,36*16)); addEnnemi(new Ennemi123(45*16+5,21*16));
            addEnnemi(new Ennemi123(53*16+5,21*16)); addEnnemi(new Ennemi123(49*16+5,96*16));
            addEnnemi(new Ennemi123(9*16+5,6*16)); addEnnemi(new Ennemi123(9*16+5,18*16));
            addEnnemi(new Ennemi123(9*16+5,51*16)); addEnnemi(new Ennemi123(6*16+5,67*16));
            addEnnemi(new Ennemi123(129*16+5,51*16)); addEnnemi(new Ennemi123(133*16+5,66*16));
            addEnnemi(new Ennemi123(6*16+5,97*16)); addEnnemi(new Ennemi123(18*16+5,100*16));
            addEnnemi(new Ennemi123(27*16+5,94*16));

            addEnnemi(new Ennemi126(49*16+8, 52*16)); addEnnemi(new Ennemi126(89*16+8, 52*16));
            addEnnemi(new Ennemi126(86*16, 3*16)); addEnnemi(new Ennemi126(93*16, 3*16));
            addEnnemi(new Ennemi126(106*16, 3*16)); addEnnemi(new Ennemi126(113*16, 3*16));
            addEnnemi(new Ennemi126(86*16, 11*16)); addEnnemi(new Ennemi126(93*16, 11*16));
            addEnnemi(new Ennemi126(106*16, 11*16)); addEnnemi(new Ennemi126(113*16, 11*16));
            addEnnemi(new Ennemi126(127*16, 36*16)); addEnnemi(new Ennemi126(133*16, 37*16));
            addEnnemi(new Ennemi126(9*16, 37*16));

            addObject(new Jarre(62*16, 27*16, 0, TI_RUBIS_ROUGE, map));
            addObject(new Jarre(77*16, 27*16, 0, TI_NO_ITEM, map));
            break;
        case 59 :
            //boss
            if (!inventory->hasCoeur(12)) {
                addEnnemi(new Ennemi128(278*16-3, 31*16));
            }

            addObject(new Coffre(113 * 16, 28 * 16, 0, scene->getCoffre(14, 0), TI_CARTE_DONJON));

            addObject(new Coffre(186 * 16, 33 * 16, 0, scene->getCoffre(14, 1), TI_BOUSSOLE));

            addObject(new Coffre(249 * 16 + 8, 21 * 16, 0, scene->getCoffre(14, 2), TI_CLE_BOSS));

            if (scene->getCoffre(14, 2) == 2) ouvrePorte(279, 43, 0);

            addObject(new Coffre(276 * 16, 21 * 16 + 8, 1, link->getTunique() >= 4, TI_TUNIQUE_BLANCHE));

            addObject(new Coffre(69 * 16 + 8, 6 * 16, 0, scene->getCoffre(14, 4), TI_CLE, 4));
            addObject(new Coffre(149 * 16 + 8, 36 * 16, 0, scene->getCoffre(14, 5), TI_CLE, 5));

            if (scene->getCoffre(14, 6)) ouvrePorte(109, 43, 0);
            if (scene->getCoffre(14, 7)) ouvrePorte(249, 43, 0);
            if (scene->getCoffre(14, 8)) ouvrePorte(9, 13, 0);
            if (scene->getCoffre(14, 9)) ouvrePorte(18, 6, 1);
            if (scene->getCoffre(14, 10)) ouvrePorte(29, 43, 0);
            if (scene->getCoffre(14, 11)) ouvrePorte(38, 51, 1);
            if (scene->getCoffre(14, 12)) ouvrePorte(69, 13, 0);
            if (scene->getCoffre(14, 13)) ouvrePorte(69, 43, 0);
            if (scene->getCoffre(14, 14)) ouvrePorte(98, 51, 1);

            addObject(new Stele(16*282, 16*21, 1633, false));

            addObject(new Interrupteur(7*16, 12*16, 0, scene->getCoffre(14, 8), map));
            addObject(new Interrupteur(22*16, 10*16, 0, scene->getCoffre(14, 9), map));
            addObject(new Interrupteur(27*16, 42*16, 0, scene->getCoffre(14, 10), map));
            addObject(new Interrupteur(42*16, 55*16, 0, scene->getCoffre(14, 11), map));
            addObject(new Interrupteur(67*16, 12*16, 0, scene->getCoffre(14, 12), map));
            addObject(new Interrupteur(67*16, 42*16, 0, scene->getCoffre(14, 13), map));
            addObject(new Interrupteur(95*16, 52*16, 0, scene->getCoffre(14, 14), map));

            addObject(new PiegePics(174*16, 48*16, S)); addObject(new PiegePics(185*16, 48*16, S));
            addObject(new PiegePics(189*16, 48*16, S)); addObject(new PiegePics(193*16, 48*16, S));

            addObject(new PiegeLong(207*16, 48*16, S)); addObject(new PiegeLong(217*16, 48*16, S));
            addObject(new PiegeLong(204*16, 34*16, S)); addObject(new PiegeLong(266*16, 48*16, S));
            addObject(new PiegeLong(286*16, 48*16, S)); addObject(new PiegeLong(266*16, 3*16, S));
            addObject(new PiegeLong(276*16, 11*16, S)); addObject(new PiegeLong(286*16, 3*16, S));
            addObject(new PiegeLong(306*16, 29*16, S));

            addEnnemi(new Ennemi026(129*16,56*16)); addEnnemi(new Ennemi026(135*16,48*16));
            addEnnemi(new Ennemi026(142*16,53*16)); addEnnemi(new Ennemi026(103*16,29*16));
            addEnnemi(new Ennemi026(112*16,35*16)); addEnnemi(new Ennemi026(116*16,21*16));
            addEnnemi(new Ennemi026(119*16,41*16)); addEnnemi(new Ennemi026(124*16,29*16));
            addEnnemi(new Ennemi026(130*16,23*16)); addEnnemi(new Ennemi026(135*16,33*16));
            addEnnemi(new Ennemi026(144*16,39*16));
            addEnnemi(new Ennemi026(145*16,18*16)); addEnnemi(new Ennemi026(145*16,30*16));
            addEnnemi(new Ennemi026(153*16,27*16)); addEnnemi(new Ennemi026(155*16,37*16));
            addEnnemi(new Ennemi026(152*16,4*16)); addEnnemi(new Ennemi026(124*16,5*16));
            addEnnemi(new Ennemi026(114*16,9*16)); addEnnemi(new Ennemi026(86*16,4*16));
            addEnnemi(new Ennemi026(85*16,40*16)); addEnnemi(new Ennemi026(88*16,25*16));
            addEnnemi(new Ennemi026(95*16,30*16)); addEnnemi(new Ennemi026(245*16,25*16));
            addEnnemi(new Ennemi026(245*16,38*16)); addEnnemi(new Ennemi026(252*16,29*16));
            addEnnemi(new Ennemi026(256*16,21*16)); addEnnemi(new Ennemi026(245*16,55*16));
            addEnnemi(new Ennemi026(313*16,55*16)); addEnnemi(new Ennemi026(313*16,4*16));
            addEnnemi(new Ennemi026(190*16,33*16)); addEnnemi(new Ennemi026(194*16,20*16));
            addEnnemi(new Ennemi026(209*16,26*16)); addEnnemi(new Ennemi026(185*16,3*16));
            addEnnemi(new Ennemi026(198*16,4*16)); addEnnemi(new Ennemi026(205*16,11*16));
            addEnnemi(new Ennemi026(213*16,3*16)); addEnnemi(new Ennemi026(234*16,4*16));
            addEnnemi(new Ennemi026(224*16,32*16)); addEnnemi(new Ennemi026(230*16,25*16));
            addEnnemi(new Ennemi026(234*16,39*16)); addEnnemi(new Ennemi026(232*16,55*16));
            addEnnemi(new Ennemi026(166*16,53*16)); addEnnemi(new Ennemi026(165*16,30*16));
            addEnnemi(new Ennemi026(170*16,23*16)); addEnnemi(new Ennemi026(176*16,34*16));

            addEnnemi(new Ennemi042(6*16-5,34*16-3)); addEnnemi(new Ennemi042(8*16-5,6*16-3));
            addEnnemi(new Ennemi042(14*16-5,24*16-3)); addEnnemi(new Ennemi042(27*16-5,35*16-3));
            addEnnemi(new Ennemi042(29*16-5,52*16-3)); addEnnemi(new Ennemi042(32*16-5,4*16-3));
            addEnnemi(new Ennemi042(33*16-5,21*16-3)); addEnnemi(new Ennemi042(44*16-5,31*16-3));
            addEnnemi(new Ennemi042(48*16-5,8*16-3)); addEnnemi(new Ennemi042(54*16-5,22*16-3));
            addEnnemi(new Ennemi042(54*16-5,49*16-3)); addEnnemi(new Ennemi042(55*16-5,39*16-3));
            addEnnemi(new Ennemi042(66*16-5,21*16-3)); addEnnemi(new Ennemi042(69*16-5,55*16-3));
            addEnnemi(new Ennemi042(73*16-5,33*16-3));
            break;
        case 60 :
            //boss
            addObject(new Pnj(16*69+8, 16*79, 8, 1654));

            addObject(new Coffre(49 * 16 + 8, 82 * 16, 0, scene->getCoffre(15, 0), TI_CARTE_DONJON));

            addObject(new Coffre(109 * 16 + 8, 82 * 16, 0, scene->getCoffre(15, 1), TI_BOUSSOLE));

            addObject(new Coffre(29 * 16 + 8, 82 * 16, 0, scene->getCoffre(15, 2), TI_CLE_BOSS));

            if (scene->getCoffre(15, 2) == 2) ouvrePorte(69, 118, 0);

            addObject(new Coffre(69 * 16, 4 * 16 + 8, 1, link->getInventory()->hasObject(MASQUE), TI_MASQUE));

            addObject(new Coffre(89 * 16 + 8, 142 * 16, 0, scene->getCoffre(15, 4), TI_CLE, 4));

            if (scene->getCoffre(15, 5)) ouvrePorte(18, 66, 1);
            if (scene->getCoffre(15, 6)) ouvrePorte(9, 58, 0);
            if (scene->getCoffre(15, 7)) ouvrePorte(29, 58, 0);
            if (scene->getCoffre(15, 8)) ouvrePorte(58, 36, 1);
            if (scene->getCoffre(15, 9)) ouvrePorte(49, 43, 0);
            if (scene->getCoffre(15, 10)) ouvrePorte(49, 133, 0);
            if (scene->getCoffre(15, 11)) ouvrePorte(129, 58, 0);
            if (scene->getCoffre(15, 12)) ouvrePorte(129, 103, 0);
            if (scene->getCoffre(15, 13)) ouvrePorte(9, 88, 0);
            if (scene->getCoffre(15, 14)) ouvrePorte(29, 88, 0);
            if (scene->getCoffre(15, 15)) ouvrePorte(49, 88, 0);
            if (scene->getCoffre(15, 16)) ouvrePorte(69, 13, 0);
            if (scene->getCoffre(15, 17)) ouvrePorte(69, 88, 0);
            if (scene->getCoffre(15, 18)) ouvrePorte(89, 88, 0);
            if (scene->getCoffre(15, 19)) ouvrePorte(129, 88, 0);

            addObject(new Interrupteur(7*16, 57*16, 0, scene->getCoffre(15, 6), map));
            addObject(new Interrupteur(32*16, 62*16, 0, scene->getCoffre(15, 7), map));
            addObject(new Interrupteur(52*16, 38*16, 0, scene->getCoffre(15, 8), map));
            addObject(new Interrupteur(47*16, 47*16, 0, scene->getCoffre(15, 9), map));
            addObject(new Interrupteur(44*16, 128*16, 0, scene->getCoffre(15, 10), map));
            addObject(new Interrupteur(127*16, 62*16, 0, scene->getCoffre(15, 11), map));
            addObject(new Interrupteur(122*16, 100*16, 0, scene->getCoffre(15, 12), map));

            addObject(new Pnj(16*67+2, 16*137-10, 111, 1638));
            addObject(new Pnj(16*7+2, 16*92-10, 111, 1644));
            addObject(new Pnj(16*27+2, 16*92-10, 111, 1647));
            addObject(new Pnj(16*47+2, 16*92-10, 111, 1648));
            addObject(new Pnj(16*67+2, 16*17-10, 111, 1649));
            addObject(new Pnj(16*67+2, 16*92-10, 111, 1650));
            addObject(new Pnj(16*87+2, 16*92-10, 111, 1651));
            addObject(new Pnj(16*127+2, 16*92-10, 111, 1652));

            addEnnemi(new Ennemi129(36*16,138*16-5)); addEnnemi(new Ennemi129(43*16,138*16-5));
            addEnnemi(new Ennemi129(29*16+8,141*16-5));

            addEnnemi(new Ennemi130(66*16+4,49*16));
            addEnnemi(new Ennemi130(109*16+4,140*16));
            addEnnemi(new Ennemi130(126*16+4,23*16));
            addEnnemi(new Ennemi130(89*16+4,65*16));

            addEnnemi(new Ennemi131(29*16+8, 7*16-8)); addEnnemi(new Ennemi131(49*16+8, 7*16-8));
            addEnnemi(new Ennemi131(9*16+8, 22*16-8)); addEnnemi(new Ennemi131(9*16+8, 37*16-8));
            addEnnemi(new Ennemi131(9*16+8, 52*16-8)); addEnnemi(new Ennemi131(29*16+8, 52*16-8));

            addEnnemi(new Ennemi132(32*16, 120*16+6)); addEnnemi(new Ennemi132(40*16, 125*16+6));
            addEnnemi(new Ennemi132(44*16, 116*16+6));

            addEnnemi(new Ennemi133(89*16-4+8,5*16+7)); addEnnemi(new Ennemi133(99*16-4+8,8*16+7));
            addEnnemi(new Ennemi133(109*16-4+8,5*16+7));

            addEnnemi(new Ennemi134(66*16-3+8,125*16+6)); addEnnemi(new Ennemi134(72*16-3+8,125*16+6));
            addEnnemi(new Ennemi134(26*16-3+8,127*16+6)); addEnnemi(new Ennemi134(39*16-3+8,110*16+6));
            addEnnemi(new Ennemi134(50*16-3+8,126*16+6)); addEnnemi(new Ennemi134(39*16-3+8,141*16+6));
            addEnnemi(new Ennemi134(9*16-3+8,126*16+6)); addEnnemi(new Ennemi134(9*16-3+8,111*16+6));

            addEnnemi(new Ennemi135(128*16+4, 38*16)); addEnnemi(new Ennemi135(128*16+4, 51*16));
            addEnnemi(new Ennemi135(133*16+4, 44*16));

            addEnnemi(new Ennemi136(88*16-4, 126*16-4)); addEnnemi(new Ennemi136(96*16-4, 128*16-4));
            addEnnemi(new Ennemi136(104*16-4, 125*16-4)); addEnnemi(new Ennemi136(112*16-4, 127*16-4));
            addEnnemi(new Ennemi136(129*16-4, 126*16-4)); addEnnemi(new Ennemi136(126*16-4, 110*16-4));
            addEnnemi(new Ennemi136(132*16-4, 112*16-4));

            addEnnemi(new Ennemi137(34*16,30*16+6)); addEnnemi(new Ennemi137(42*16,22*16+6));
            addEnnemi(new Ennemi137(49*16,36*16+6));

            addEnnemi(new Ennemi138(69*16+3, 40*16+4));
            addEnnemi(new Ennemi138(89*16+3, 22*16+4));
            addEnnemi(new Ennemi138(109*16+3, 22*16+4)); addEnnemi(new Ennemi138(66*16+3, 67*16+4));
            addEnnemi(new Ennemi138(106*16+3, 68*16+4));

            addEnnemi(new Ennemi139(45*16+5, 51*16)); addEnnemi(new Ennemi139(54*16+5, 54*16));
            addEnnemi(new Ennemi139(30*16+5, 67*16)); addEnnemi(new Ennemi139(40*16+5, 65*16));
            addEnnemi(new Ennemi139(50*16+5, 68*16));

            addEnnemi(new Ennemi140(97*16, 101*16)); addEnnemi(new Ennemi140(99*16, 111*16));
            addEnnemi(new Ennemi140(108*16, 107*16)); addEnnemi(new Ennemi140(85*16, 83*16));
            addEnnemi(new Ennemi140(88*16, 80*16)); addEnnemi(new Ennemi140(92*16, 82*16));
            addEnnemi(new Ennemi140(91*16, 42*16)); addEnnemi(new Ennemi140(92*16, 52*16));
            addEnnemi(new Ennemi140(100*16, 48*16)); addEnnemi(new Ennemi140(101*16, 38*16));
            break;
        case 61 :
            addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, true, TI_NO_ITEM));
            break;
        case 62 :
            if (link->getEpee() == 0 && !inventory->hasObject(OCARINA)) {
                addItem(ItemHelper::getInstance()->createItem(TI_EPEE_1, 10*16+8, 3*16));
            }

            addObject(new Pancarte(16*6, 16*8, 557, map));

            addObject(new Sphere(14*16, 7*16));
            break;
        case 63 :
            if (scene->getCoffre(0, 7)) {
                ouvrePorte(78, 6, 1);
            }

            addObject(new Interrupteur(84*16, 5*16, 0, scene->getCoffre(0, 7), map));

            addObject(new Pancarte(16*5, 16*5, 559, map));
            addObject(new Pancarte(16*34, 16*5, 560, map));


            addObject(new Jarre(33*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(34*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(35*16, 12*16, 1, TI_NO_ITEM, map));
            break;
        case 64 :
            addObject(new Stele(16*9, 16*6, 561, scene->getAvancement() >= AV_PORTAIL_F_OUVERT));

            if (scene->getAvancement() >= AV_PORTAIL_F_OUVERT && scene->getAvancement() < AV_RETOUR_PRESENT) {
                ouvrePorte(9, 3, 0);
            }

            if (scene->getAvancement() < AV_PORTAIL_F_UTILISE) {
                if (link->getEpee() == 2) {
                    addObject(new Pnj(16*12, 16*7+1+8, 15, 569, scene->getAvancement() == AV_PORTAIL_F_OUVERT ? N : S));
                } else if (inventory->hasObject(CARTE)) {
                    addObject(new Pnj(16*9+8, 16*7+1+8, 15, 569));
                }
            }
            break;
        case 65 :
            addObject(new Pnj(16*9, 16*4+8, 16, 577));
            break;
        case 66 :
            addObject(new Jarre(5*16, 8*16, 1, TI_NO_ITEM, map));

            addObject(new Coffre(7 * 16, 6 * 16, 0, scene->getCoffre(0, 8), TI_SAC_RIZ_10));
            addObject(new Coffre(9 * 16+8, 6 * 16, 0, scene->getCoffre(0, 9), TI_BOCAL_EPICES_10));
            addObject(new Coffre(12 * 16, 6 * 16, 0, scene->getCoffre(0, 10), TI_SAC_OLIVES_10));
            break;
        case 67 :
            if (scene->getCoffre(0, 11)) {
                ouvrePorte(58, 21, 1);
            }

            addObject(new Interrupteur(53*16, 19*16, 0, scene->getCoffre(0, 11), map));

            addObject(new Pancarte(16*70, 16*22, 584, map));

            addObject(new Jarre(13*16, 25*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(14*16, 25*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 25*16, 1, TI_NO_ITEM, map));
            break;
        case 68 :
            if (scene->getCoffre(0, 12)) {
                ouvrePorte(9, 13, 0);
            }

            addObject(new Interrupteur(7*16, 11*16, 0, scene->getCoffre(0, 12), map));

            levier = new Switch(36*16, 23*16);
            addObject(levier);
            if (scene->getCoffre(0, 13)) {
                levier->setLeft(false);
                map->activateInter(36*16, 23*16);
            }

            addObject(new Pancarte(16*43, 16*22, scene->getAvancement() >= AV_GARS_MINE_AIDE ? 586 : 585, map));

            map->addWagon();

            addObject(new Jarre(15*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(16*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(17*16, 4*16, 0, TI_NO_ITEM, map));

            addObject(new Jarre(5*16, 19*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(5*16, 20*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 21*16, 0, TI_FLECHE, map));

            addObject(new Jarre(4*16, 35*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 35*16, 0, TI_NO_ITEM, map));

            addObject(new Jarre(35*16, 21*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(35*16, 22*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(35*16, 23*16, 0, TI_NO_ITEM, map));

            addObject(new Jarre(43*16, 16*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(44*16, 16*16, 0, TI_NO_ITEM, map));

            if (scene->getAvancement() >= AV_GARS_MINE_AIDE) {
                addObject(new Pnj(16*37, 16*22+7, 78, 587));
            }
            break;
        case 69 :
            addObject(new Stele(16*9, 16*6, 561, false));
            if (scene->getCoffre(0, 25)) {
                ouvrePorte(9, 13, 0);
            }
            break;
        case 70 :
            if (scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_OUVERT
                && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                ouvrePorte(9, 3, 0);
            }
            addObject(new TalkableArea(16*9+8, 16*7, 588));
            if (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME) {
                if (inventory->getTroc(TT_POIVRON) > -1) {
                    addObject(new Pnj(16*15, 16*4, 60, 591));
                }
                if (scene->getCoffre(4, 30)) {
                    addObject(new Pnj(16*4, 16*4, 62, 593));
                }
                if (scene->getAvancement() >= AV_SAGES_GROTTE) {
                    addObject(new Pnj(16*9+3, 16*8, 29, 595));
                }
            }
            break;
        case 71 :
            addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, true, TI_NO_ITEM));
            break;
        case 72 :
            addObject(new Coffre(9 * 16 + 8, 6 * 16, 0, inventory->getTroc(TT_JAUGE) > -1, TI_JAUGE));
            break;
        case 73 :
            addObject(new Pnj(16*9, 16*4+8, 48, 600));
            break;
        case 74 :
            addObject(new Pnj(16*9+4, 16*5+5+8, 79, 610));
            break;
        case 75 :
            addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, inventory->hasCristal(2), TI_CRISTAL, 2));
            break;
        case 76 :
            addObject(new Jarre(3*16, 6*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(3*16, 7*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(3*16, 8*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(9*16, 4*16, 1, TI_FLECHE, map));
            addObject(new Jarre(10*16, 4*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(11*16, 4*16, 1, TI_BOMBE, map));
            break;
        case 77 :
            addObject(new Jarre(8*16, 2*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(9*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(10*16, 2*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(11*16, 2*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(12*16, 2*16, 1, TI_NO_ITEM, map));
            break;
        case 78 :
            addObject(new Jarre(27*16, 7*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(32*16, 7*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(84*16, 6*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(84*16, 7*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(84*16, 8*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(95*16, 6*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(95*16, 7*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(95*16, 8*16, 1, TI_MAGIE_PEU, map));
            break;
        case 79 :
            addObject(new Jarre(4*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(4*16, 5*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(4*16, 6*16, 0, TI_PETIT_COEUR, map));
            break;
        case 80 :
            addObject(new Jarre(4*16, 2*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(4*16, 3*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(4*16, 4*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(4*16, 27*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(5*16, 27*16, 0, TI_RUBIS_BLEU, map));

            addObject(new Pnj(16*9+8, 16*3, 18, 612));
            addObject(new TalkableArea(16*9+8, 16*6, 612));
            addObject(new Pnj(16*14, 16*6+8, 41, 613));
            addObject(new Pnj(5*16+5+8, 17*16+5+8, 57, 614));
            addObject(new Pnj(16*12, 16*12, 52, 615));
            break;
        case 81 :
            addObject(new Pnj(16*13, 16*9, 10, 616));
            addObject(new TalkableArea(16*7, 16*6, 617));
            addObject(new TalkableArea(16*10, 16*6, 619));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 82 :
            addObject(new Pnj(16*13, 16*9, 12, 616, N));
            addObject(new TalkableArea(16*5, 16*6, 625));
            addObject(new TalkableArea(16*8, 16*6, 627));
            addObject(new TalkableArea(16*11, 16*6, 629));
            break;
        case 83 :
            addObject(new Coffre(6 * 16, 5 * 16, 0, scene->getCoffre(0, 15), TI_BOCAL_EPICES));
            break;
        case 84 :
            if (link->getInventory()->getTroc(TT_ROC_GIVRE) > -1) {
                addObject(new Pnj(16*13, 16*9, 7, 658, N));
                map->setSol(5*16, 5*16, inventory->hasObject(FLACON_1) && inventory->hasObject(FLACON_2) ? 3317 : 3313);
                map->setSol(8*16, 5*16, inventory->hasObject(BONUS_FORCE_1) && inventory->hasObject(BONUS_FORCE_2) ? 3317 : 3314);
                map->setSol(11*16, 5*16, inventory->hasObject(BONUS_DEFENSE_1) && inventory->hasObject(BONUS_DEFENSE_2) ? 3317 : 3315);
                map->setSol(14*16, 5*16, inventory->hasObject(DETECTEUR) ? 3317 : 3316);

                if (!inventory->hasObject(FLACON_1)) {
                    addObject(new TalkableArea(16*5, 16*6, 643));
                } else if (!inventory->hasObject(FLACON_2)) {
                    addObject(new TalkableArea(16*5, 16*6, 646));
                }
                if (!inventory->hasObject(BONUS_FORCE_1)) {
                    addObject(new TalkableArea(16*8, 16*6, 648));
                } else if (!inventory->hasObject(BONUS_FORCE_2)) {
                    addObject(new TalkableArea(16*8, 16*6, 651));
                }
                if (!inventory->hasObject(BONUS_DEFENSE_1)) {
                    addObject(new TalkableArea(16*11, 16*6, 653));
                } else if (!inventory->hasObject(BONUS_DEFENSE_2)) {
                    addObject(new TalkableArea(16*11, 16*6, 656));
                }
                if (!inventory->hasObject(DETECTEUR)) {
                    addObject(new TalkableArea(16*14, 16*6, 638));
                }
            } else {
                addObject(new Pnj(16*13, 16*9, 7, 631, N));
            }
            break;
        case 85 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Pnj(16*9+7, 16*6, 17, 661));
            break;
        case 86 :
            addObject(new Pnj(16*9+8, 16*4, 43, 673, N));
            break;
        case 87 :
            addObject(new Jarre(14*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Coffre(9 * 16, 5 * 16, 0, scene->getCoffre(0, 16), TI_SAC_RIZ));
            addObject(new Coffre(11 * 16, 5 * 16, 0, scene->getCoffre(0, 17), TI_SAC_OLIVES));
            break;
        case 88 :
            addObject(new Coffre(4 * 16, 11 * 16, 0, scene->getCoffre(0, 18), TI_BOCAL_EPICES));
            addObject(new Jarre(4*16, 8*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(12*16, 12*16, 0, TI_RUBIS_VERT, map));
            break;
        case 89 :
            // coeurs 15, gemmes 160, 161 et 162
            addObject(new Pnj(16*14, 16*11-10, 20, 682, N));
            addObject(new Coffre(6 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(6 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(6 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            break;
        case 90 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_PETIT_COEUR, map));

            addObject(new Pnj(12*16+5, 8*16+5, 46, 688));

            levier = new Switch(14*16, 9*16);
            addObject(levier);
            if (inventory->getTroc(TT_ROUAGE) == 0) {
                levier->setLeft(false);
            }
            break;
        case 91 :
            addObject(new Jarre(6*16, 6*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(7*16, 6*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(8*16, 6*16, 0, TI_MAGIE_PEU, map));
            addObject(new Pnj(16*9+8, 16*8-3, 28, 698));
            break;
        case 92 :
            addObject(new Jarre(4*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(4*16, 5*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(4*16, 6*16, 0, TI_RUBIS_VERT, map));
            addObject(new Pnj(9*16, 7*16, 56, 700));
            break;
        case 93 :
            addObject(new Jarre(4*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Pnj(9*16+5, 6*16+5, 57, 709));
            break;
        case 94 :
            addObject(new Pnj(16*9+8, 16*4+6, 80, 711)); //scene->getCoffre(0, 19) si encyclopedie finie
            break;
        case 95 :
            addObject(new Jarre(13*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(14*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Pnj(16*6+8, 16*6, 21, 752));
            break;
        case 96 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Coffre(8 * 16, 5 * 16, 0, scene->getCoffre(0, 20), TI_SAC_RIZ));
            addObject(new Coffre(10 * 16, 5 * 16, 0, scene->getCoffre(0, 21), TI_BOCAL_EPICES));
            addObject(new Coffre(12 * 16, 5 * 16, 0, scene->getCoffre(0, 22), TI_SAC_OLIVES));
            addObject(new Pnj(16*13, 16*7, 10, 755));
            break;
        case 97 :
            addObject(new Jarre(13*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(14*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*7, 16*8, 70, 765));
            break;
        case 98 :
            addObject(new Pnj(16*13, 16*9, 12, 616, N));
            addObject(new TalkableArea(16*7, 16*6, 617));
            addObject(new TalkableArea(16*10, 16*6, 619));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 99 :
            addObject(new Pnj(16*13, 16*9, 2, 616, N));
            addObject(new TalkableArea(16*5, 16*6, 625));
            addObject(new TalkableArea(16*8, 16*6, 627));
            addObject(new TalkableArea(16*11, 16*6, 629));
            break;
        case 100 :
            addObject(new Pnj(16*11+8, 16*8, 41, 775));
            break;
        case 101 :
            addObject(new Jarre(14*16, 4*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(15*16, 4*16, 0, TI_NO_ITEM, map));
            break;
        case 102 :
            addObject(new Jarre(4*16, 10*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(4*16, 11*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));

            addObject(new Pnj(16*8, 16*4, 25, 612));
            addObject(new TalkableArea(16*8, 16*6, 612));

            if (scene->getAvancement() < AV_GARS_MINE_AIDE) {
                addObject(new Pnj(16*28, 16*6 + 5, 19, 789));
            }
            addObject(new Pnj(16*33, 16*8+8, 14, 799));
            addObject(new Pnj(16*21, 16*3+8, 40, 800));
            break;
        case 103 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Pnj(16*6, 16*7, 14, 801));
            break;
        case 104 :
            addObject(new Jarre(14*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Coffre(13 * 16, 9 * 16, 0, scene->getCoffre(0, 23), TI_BOCAL_EPICES));
            addObject(new Pnj(16*10, 16*5, 24, 803, N));
            break;
        case 105 :
            addObject(new Pnj(16*5, 16*6, 51, 804));
            break;
        case 106 :
            addObject(new Jarre(4*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*9, 16*5, 55, 805));
            break;
        case 107 :
            addObject(new Pnj(16*13, 16*9, 41, 616, N));
            addObject(new TalkableArea(16*7, 16*6, 617));
            addObject(new TalkableArea(16*10, 16*6, 619));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 108 :
            addObject(new Pnj(16*13, 16*9, 45, 616, N));
            addObject(new TalkableArea(16*5, 16*6, 625));
            addObject(new TalkableArea(16*8, 16*6, 627));
            addObject(new TalkableArea(16*11, 16*6, 629));
            break;
        case 109 :
            addObject(new Pnj(4*16+5, 6*16+5, 46, 806));
            addObject(new Pnj(14*16+5, 6*16+5, 46, 806));
            addObject(new Pnj(16*9 + 8, 16*3 + 8 + 4, 20, 807, N));
            addObject(new TalkableArea(16*9+8, 16*6, 807));
            break;
        case 110 :
            addObject(new Jarre(14*16, 12*16, 0, TI_FLECHE, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*7+8, 16*6, 22, 822));
            break;
        case 111 : case 114 : case 124 :
            if (scene->getTotalMonsters() < 87) {
                addObject(new Pnj(16*9+8, 16*4+8, 8, 845)); // scene->getCoffre(0, 24) pour le deja paye
            } else {
                ouvrePorte(9, 5, 0);
            }
            break;
        case 112 :
            addObject(new Pnj(4*16+5, 6*16+5, 65, 806));
            addObject(new Pnj(14*16+5, 6*16+5, 65, 806));
            addObject(new Pnj(16*9 + 8, 16*4 + 4, 59, 807, N));
            addObject(new TalkableArea(16*9+8, 16*6, 807));
            break;
        case 113 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_NO_ITEM, map));
            if (link->getInventory()->getTrocGemme(1) >= TGB_PLAN) {
                addObject(new Pnj(16*7-4, 16*6-11, 81, 871));
            } else {
                addObject(new Pnj(16*7, 16*6-1, 64, 872));
            }
            break;
        case 115 :
            addObject(new Jarre(4*16, 12*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_RUBIS_BLEU, map));
            if (link->getInventory()->getTroc(TT_POIVRON) == -1) {
                addObject(new Pnj(16*14, 16*4, 60, 881));
            }
            break;
        case 116 :
            addObject(new Jarre(14*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_NO_ITEM, map));
            if (scene->getAvancement() < AV_SAGES_GROTTE || scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_FERME) {
                addObject(new Pnj(16*9+3, 16*5, 29, 886));
            }
            break;
        case 117 :
            addObject(new Pnj(16*13, 16*9, 30, 616, N));
            addObject(new TalkableArea(16*7, 16*6, 902));
            addObject(new TalkableArea(16*10, 16*6, 904));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 118 :
            addObject(new Pnj(16*13, 16*9, 50, 616));
            addObject(new TalkableArea(16*5, 16*6, 906));
            addObject(new TalkableArea(16*8, 16*6, 908));
            addObject(new TalkableArea(16*11, 16*6, 910));
            break;
        case 119 :
            addObject(new Jarre(14*16, 4*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(15*16, 4*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Interrupteur(6*16, 8*16, 0, scene->getCoffre(0, 27) != -1, map));
            addObject(new Pnj(16*11+8, 16*5, 82, 912));
            // scene->getCoffre(0, 26) quete demarree + nb cafes payes
            // scene->getCoffre(0, 27) cafe courrant, -1 bouton up, -2 anim, 0 pret a etre rejoue, >0 reste a faire
            break;
        case 120 :
            addObject(new Jarre(4*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 4*16, 0, TI_RUBIS_VERT, map));
            addObject(new Pnj(9*16+8, 6*16, 31, 661, N));
            break;
        case 121 :
            addObject(new Pnj(16*9, 16*5, 53, 939, N));
            break;
        case 122 :
            addObject(new Pnj(16*9, 16*6, 83, 944));
            break;
        case 123 :
            addObject(new Jarre(15*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Pnj(16*9, 16*6, 27, 953, N));
            break;
        case 125 :
            addObject(new Pnj(16*4+8, 16*6+8, 41, 806, N));
            addObject(new Pnj(16*14+8, 16*6+8, 42, 806, N));
            addObject(new Pnj(16*9 + 8, 16*3+8, 10, 807));
            addObject(new TalkableArea(16*9+8, 16*6, 807));
            break;
        case 126 :
            addObject(new Jarre(15*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*7, 16*6, 21, 967));
            //scene->getCoffre(0, 28) si deja parle
            break;
        case 127 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_PETIT_COEUR, map));
            if (inventory->getTrocGemme(0) >= TGR_FER_CHEVAL
                && inventory->getTrocGemme(1) >= TGB_CLOCHE
                && inventory->getTrocGemme(2) >= TGJ_MIROIR) {
                addObject(new Pnj(16*6+4, 16*6+8, 26, link->getEpee() == 0 ? 1003 : 996));
            } else {
                map->setSol(8*16, 7*16, 2, 2, 3190, SOL_BOIS);
                addObject(new Pnj(16*6, 16*6, 38, 974));
            }
            break;
        case 128 :
            addObject(new Pnj(16*13, 16*9, 20, 616, N));
            addObject(new TalkableArea(16*7, 16*6, 1006));
            addObject(new TalkableArea(16*10, 16*6, 1008));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 129 :
            addObject(new Pnj(16*13, 16*9, 2, 616, N));
            addObject(new TalkableArea(16*5, 16*6, 1010));
            addObject(new TalkableArea(16*8, 16*6, 1012));
            addObject(new TalkableArea(16*11, 16*6, 1014));
            break;
        case 130 :
            addObject(new Jarre(14*16, 12*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_NO_ITEM, map));
            if (scene->getAvancement() < AV_INFO_PASSE_OK) {
                addObject(new Pnj(16*12+8, 16*5+8, 10, 388));
                addObject(new Poule(16*4, 16*9));
                addObject(new Poule(16*14, 16*10));
                addObject(new Poule(16*6, 16*11));
                addObject(new Poule(16*9, 16*6));
                addObject(new Poule(16*15, 16*6));
            }
            break;
        case 131 :
            addObject(new Jarre(15*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*12+8, 16*5+8, 84, 1016));
            break;
        case 132 :
            addObject(new Pnj(16*9+8, 16*6, 25, 661));
            break;
        case 133 :
            if (scene->getAvancement() < AV_INFO_PASSE_OK) {
                addObject(new Pnj(6*16+8, 9*16, 9, 391, N));
            }
            break;
        case 134 :
            addObject(new Coffre(11 * 16, 5 * 16, 0, inventory->hasObject(LIVRE), TI_LIVRE));
            if (scene->getAvancement() < AV_INFO_PASSE_OK) {
                addObject(new Pnj(16*14, 16*9, 51, 390));
                addObject(new Pnj(16*9, 16*5, 55, 1024));
            }
            break;
        case 135 :
            addObject(new Jarre(15*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 5*16, 0, TI_MAGIE_PEU, map));
            if (scene->getAvancement() < AV_INFO_PASSE_OK) {
                addObject(new Pnj(16*7, 16*5, 14, 386));
            }
            break;
        case 136 :
            addObject(new Pnj(16*10, 16*3, 18, 1027));
            addObject(new TalkableArea(16*10, 16*6, 1027));
            if (scene->getAvancement() < AV_INFO_PASSE_OK) {
                addObject(new Pnj(16*5-2, 16*6+5, 90, 1036));
                addObject(new Pnj(6*16, 18*16+10, 35, 387));
                addObject(new Pnj(16*12, 16*17, 23, 389));
            }
            if (inventory->nbCristaux() < 3 || inventory->getTrocGemme(3) < TGV_BIERE) {
                addObject(new Pnj(16*8-2, 16*6+5, 89, 1037));
                addObject(new Pnj(16*11, 16*9+8, 88, 1038));
                addObject(new Pnj(16*11, 16*12+8, 87, 1039));
                addObject(new Pnj(16*13, 16*11+7, 86, 1048));
                addObject(new Pnj(16*9, 16*10+7, 85, 1047));
            }
            if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) > TGJ_GEMME) {
                map->setSol(5*16, 3*16, 1, 1, 3340, BOIS);
            }
            //scene->getCoffre(0, 29) pour les infos
            break;
        case 137 :
            if (inventory->nbCristaux() < 3 || link->getInventory()->getTrocGemme(3) < TGV_BIERE
                || inventory->hasCristal(3)) {
                for (int j = 0; j < 2; j++) {
                    for (int i = 0; i < 3; i++) {
                        map->setSol((9+i) * 16, (67+j) * 16, map->getSol((12+i) * 16, (67+j) * 16), BOIS);
                    }
                }
                map->setSol(12 * 16, 67 * 16, 3, 2, 3190, SOL_BOIS);
            } else {
                addObject(new Pnj(16*5+4, 16*68, 91, 1055));
                addObject(new Pnj(16*11+4, 16*66, 92, 1056));
                addObject(new Pnj(16*9+4, 16*70, 93, 1057));
                addObject(new Pnj(16*7+4, 16*64, 94, 1058));
                addObject(new Pnj(16*9+4, 16*37, 95, 1059));

                addEnnemi(new Ennemi089(9*16+6, 17*16, 0));

                addObject(new Jarre(5*16, 34*16, 0, TI_PETIT_COEUR, map));
                addObject(new Jarre(6*16, 34*16, 0, TI_NO_ITEM, map));
                addObject(new Jarre(4*16, 35*16, 0, TI_NO_ITEM, map));
                addObject(new Jarre(5*16, 40*16, 0, TI_FLECHE, map));
                addObject(new Jarre(13*16, 40*16, 0, TI_PETIT_COEUR, map));
                addObject(new Jarre(14*16, 40*16, 0, TI_NO_ITEM, map));
                addObject(new Jarre(14*16, 34*16, 0, TI_FLECHE, map));
                addObject(new Jarre(15*16, 35*16, 0, TI_PETIT_COEUR, map));
                addObject(new Jarre(15*16, 36*16, 0, TI_NO_ITEM, map));

                addObject(new Coffre(9 * 16 + 8, 7 * 16, 0, inventory->hasCristal(3), TI_CRISTAL, 3));
            }
            if (inventory->hasCristal(3)) {
                addObject(new Pnj(16*5-2, 16*64+5, 89, 1068));
                addObject(new Pnj(16*10, 16*65+8, 88, 1078));
                addObject(new Pnj(16*10, 16*68+8, 87, 1079));
                addObject(new Pnj(16*12, 16*67+7, 86, 1080));
                addObject(new Pnj(16*8, 16*66+7, 85, 1081));
            }
            break;
        case 138 :
            addObject(new Pnj(16*10, 16*5, 96, 1082));
            break;
        case 139 :
            addObject(new Jarre(15*16, 11*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Pnj(16*8+8, 16*4+7, 97, 1090));
            break;
        case 140 :
            addObject(new Jarre(34*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(34*16, 5*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(34*16, 6*16, 0, TI_FLECHE, map));
            addObject(new Jarre(34*16, 7*16, 0, TI_MAGIE_PEU, map));

            addObject(new Coffre(26 * 16, 5 * 16, 0, inventory->getTrocGemme(0) >= TGR_MARTEAU, TI_MARTEAU_PONT));
            addObject(new Coffre(26 * 16, 8 * 16, 0, scene->getCoffre(0, 30), TI_BOCAL_EPICES));
            addObject(new Coffre(26 * 16, 11 * 16, 0, scene->getCoffre(0, 31), TI_SAC_RIZ));

            if (link->getInventory()->getTrocGemme(0) < TGR_RIEN_2) {
                addObject(new Pnj(16*8, 16*4+7, 52, 1094, N));
            }
            break;
        case 141 :
            addObject(new Jarre(4*16, 4*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 4*16, 0, TI_RUBIS_VERT, map));
            addObject(new Pnj(16*8, 16*4+7, 17, 1103));
            break;
        case 142 :
            addObject(new Pnj(16*13, 16*9, 7, 616, N));
            addObject(new TalkableArea(16*5, 16*6, 1010));
            addObject(new TalkableArea(16*8, 16*6, 1012));
            addObject(new TalkableArea(16*11, 16*6, 1014));
            break;
        case 143 :
            addObject(new Pnj(16*13, 16*9, 20, 616, N));
            addObject(new TalkableArea(16*7, 16*6, 1006));
            addObject(new TalkableArea(16*10, 16*6, 1008));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 144 :
            addObject(new Pnj(16*5, 16*8, 21, 1105));
            addObject(new Pnj(16*12, 16*5, 55, 1106));
            addObject(new Pnj(16*15, 16*7, 98, 1107));
            addObject(new Pnj(16*23, 16*8, 99, 1110));
            addObject(new Pnj(16*26, 16*4, 55, 1113));
            addObject(new Pnj(16*33, 16*6, 98, 1115));
            break;
        case 145 :
            addObject(new Jarre(14*16, 12*16, 0, TI_RUBIS_VERT, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*11, 16*5, 24, 1116, N));
            break;
        case 146 :
            if (link->getInventory()->getTrocGemme(0) < TGR_RIEN_2) {
                addObject(new Pnj(16*11, 16*4, 45, 1120, N));
            }
            break;
        case 147 :
            addObject(new Jarre(4*16, 12*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 12*16, 0, TI_MAGIE_PEU, map));
            addObject(new Jarre(6*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Pnj(16*11, 16*5, 54, 1128));
            break;
        case 148 :
            addObject(new Pnj(16*13, 16*9, 10, 616));
            addObject(new TalkableArea(16*7, 16*6, 1006));
            addObject(new TalkableArea(16*10, 16*6, 1008));
            if (link->getInventory()->hasObject(ARC_FEE)) {
                map->setSol(7*16, 5*16, 3309);
            }
            break;
        case 149 :
            addObject(new Pnj(16*13, 16*9, 35, 616));
            addObject(new TalkableArea(16*5, 16*6, 1010));
            addObject(new TalkableArea(16*8, 16*6, 1012));
            addObject(new TalkableArea(16*11, 16*6, 1014));
            break;
        case 150 :
            if (scene->getCoffre(0, 32) < 9) {
                addObject(new Pnj(16*89+8, 16*17, 67, 1129));
            }
            addObject(new Pnj(16*209+8, 16*4, 67, 1150));
            addObject(new Animal(16*66-4, 16*21-3, 6));

            addObject(new TalkableArea(16*9, 16*37, 1132));
            addObject(new TalkableArea(16*114, 16*17+8, 1134));
            addObject(new TalkableArea(16*72, 16*35, 1135));
            addObject(new TalkableArea(16*49, 16*23, 1137));
            addObject(new TalkableArea(16*112, 16*35, 1138));
            addObject(new TalkableArea(16*5, 16*17+8, 1140));
            addObject(new TalkableArea(16*72, 16*21, 1142));
            addObject(new TalkableArea(16*49, 16*32+8, 1143));
            addObject(new TalkableArea(16*130+8, 16*21+8, 1144));
            addObject(new TalkableArea(16*168+8, 16*21+8, 1146));
            addObject(new TalkableArea(16*209+8, 16*21+8, 1148));

            if (scene->getCoffre(0, 32) >= 1) ouvrePorte(18, 36, 1);
            if (scene->getCoffre(0, 32) >= 2) ouvrePorte(98, 21, 1);
            if (scene->getCoffre(0, 32) >= 3) ouvrePorte(78, 36, 1);
            if (scene->getCoffre(0, 32) >= 4) ouvrePorte(38, 21, 1);
            if (scene->getCoffre(0, 32) >= 5) ouvrePorte(98, 36, 1);
            if (scene->getCoffre(0, 32) >= 6) ouvrePorte(18, 21, 1);
            if (scene->getCoffre(0, 32) >= 7) ouvrePorte(78, 21, 1);
            if (scene->getCoffre(0, 32) >= 8) ouvrePorte(38, 36, 1);
            if (scene->getCoffre(0, 32) >= 10) ouvrePorte(158, 21, 3);
            if (scene->getCoffre(0, 32) >= 11) ouvrePorte(149, 28, 2);
            if (scene->getCoffre(0, 32) == 12) ouvrePorte(209, 13, 2);
            break;
        case 151 :
            addObject(new Stele(16*29, 16*5, inventory->hasObject(OCARINA) ? 1159 : 1163, inventory->hasObject(CHANT_1)));
            break;
        case 152 :
            addObject(new Stele(16*49, 16*19, inventory->hasObject(OCARINA) ? 1159 : 1163, inventory->hasObject(CHANT_2)));
            break;
        case 153 :
            addObject(new Stele(16*9, 16*19, inventory->hasObject(OCARINA) ? 1159 : 1163, inventory->hasObject(CHANT_3)));
            break;
        case 154 :
            addObject(new Jarre(4*16, 19*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(5*16, 19*16, 0, TI_FLECHE, map));

            addObject(new Switch(44*16+8, 3*16));

            levier = new Switch(44*16+8, 18*16);
            if (link->getX() > 320 * 3) {
                levier->setLeft(false);
                map->activateInter(44*16+8, 18*16, false);
            }
            addObject(levier);

            if (inventory->getTrocGemme(0) < TGR_ALLIANCE) {
                addObject(new Pnj(9*16+5, 18*16+5, 46, 1164));
            }
            addObject(new Pnj(54*16, 2*16 + 4, 100, 1173));

            if (scene->getAvancement() == AV_GANON_CAPTURE && link->getInventory()->nbCristaux() < 6) {
                addObject(new Pnj(54*16-2, 17*16 + 5, 90, 1181));
            }
            if (scene->getAvancement() >= AV_GANON_SORTI) {
                ouvrePorte(58, 19, 1);
            }
            break;
        case 155 :
            addObject(new Jarre(144*16, 34*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(145*16, 34*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(146*16, 34*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(47*16, 92*16, 1, TI_NO_ITEM, map));

            if (scene->getCoffre(0, 33)) {
                ouvrePorte(9, 58, 0);
            }
            if (scene->getCoffre(0, 34)) {
                ouvrePorte(9, 88, 0);
            }
            if (scene->getAvancement() >= AV_BOWSER_AIDE) {
                ouvrePorte(89, 94, 1);
            }

            addObject(new Coffre(11 * 16, 2 * 16, 0, scene->getAvancement() >= AV_CLE_PRISON_F_TROUVEE, TI_CLE));
            addObject(new Coffre(109 * 16, 21 * 16, 0, inventory->getTroc(TT_SOURCE_NRJ) > -1, TI_SOURCE_NRJ));

            addObject(new Pnj(16*68+10, 16*21, 110, 1199));

            if (scene->getAvancement() < AV_MOT_DE_PASSE_CONNU) {
                addObject(new Pnj(16*89, 16*91, 109, 1189));
            }

            if (scene->getAvancement() < AV_MOT_DE_PASSE_DONNE) {
                addObject(new Pnj(68*16+5+4, 31*16+5, 65, 1184));
                addObject(new Pnj(70*16+5-4, 31*16+5, 65, 1184));
            } else {
                addObject(new Pnj(66*16+5+4, 31*16+5, 65, 1187));
                addObject(new Pnj(72*16+5-4, 31*16+5, 65, 1187));
            }

            if (scene->getAvancement() < AV_MULTIPASSE_UTILISE) {
                addObject(new Pnj(129*16+5, 31*16+5, 65, 1185));
            } else {
                addObject(new Pnj(127*16+5, 31*16+5, 65, 1187));
            }
            break;
        case 156 :
            if (!scene->getCoffre(17, 43)) {
                addEnnemi(new Ennemi115(206*16, 226*16));
                addEnnemi(new Ennemi116(204*16+1, 229*16-4));
                addEnnemi(new Ennemi117(211*16+1, 229*16-4));
            } else {
                ouvrePorte(218, 231, 1);
                map->setSol(216*16, 232*16, 2, 1, 4002, PIERRE);
            }
            if (!scene->getCoffre(17, 44)) {
                addEnnemi(new Ennemi107(207*16+9, 270*16));
                map->setAir(209 * 16, 270 * 16, -1);
                map->setAir(210 * 16, 270 * 16, -1);
            } else {
                map->setSol(208*16, 272*16, 1, 1, 6960, BOIS);
                ouvrePorte(209, 268, 0);
            }
            if (!scene->getCoffre(17, 45)) {
                addEnnemi(new Ennemi097(208*16+5, 287*16));
            } else {
                ouvrePorte(209, 283, 0);
            }
            if (!scene->getCoffre(17, 46)) {
                addEnnemi(new Ennemi105(247*16+8, 227*16));
                addObject(new PiegeUltime(242*16, 227*16));
                addObject(new PiegeUltime(257*16, 227*16));
            } else {
                ouvrePorte(258, 231, 1);
            }
            if (!scene->getCoffre(17, 47)) {
                addEnnemi(new Ennemi104(249*16,243*16));
            } else {
                ouvrePorte(249, 238, 0);
            }
            if (!scene->getCoffre(17, 48)) {
                addEnnemi(new Ennemi092(249*16-52, 272*16-8));
            }
            if (!scene->getCoffre(17, 49)) {
                addEnnemi(new Ennemi113(259*16+2,287*16+2));
                addObject(new PiegeFlamme(247*16, 290*16));
                addObject(new PiegeFlamme(251*16, 292*16));
                addObject(new PiegeFlamme(255*16, 291*16));
                addObject(new PiegeFlamme(260*16, 290*16));
                addObject(new PiegeFlamme(264*16, 292*16));
                addObject(new PiegeFlamme(267*16, 290*16));
                addObject(new PiegeFlamme(271*16, 291*16));
            } else {
                ouvrePorte(278, 291, 1);
            }
            if (!scene->getCoffre(17, 50)) {
                addEnnemi(new Ennemi109(280*16, 225*16));
            } else {
                ouvrePorte(289, 238, 0);
            }
            if (!scene->getCoffre(17, 51)) {
                addEnnemi(new Ennemi111(288*16, 274*16));
            } else {
                ouvrePorte(289, 268, 0);
            }
            if (!scene->getCoffre(17, 52)) {
                addEnnemi(new Ennemi110(289*16+2,291*16));
            } else {
                ouvrePorte(289, 283, 0);
            }

            //boss
            addObject(new PouleBig(188 * 16 + 8, 35 * 16 + 8));

            addObject(new Coffre(129 * 16 + 8, 280 * 16, 0, scene->getCoffre(16, 0), TI_CARTE_DONJON));
            addObject(new Coffre(89 * 16 + 8, 171 * 16, 0, scene->getCoffre(16, 1), TI_BOUSSOLE));
            addObject(new Coffre(49 * 16 + 8, 6 * 16, 0, scene->getCoffre(16, 2), TI_CLE_BOSS));
            if (scene->getCoffre(16, 2) == 2) ouvrePorte(149, 13, 0);

            addObject(new Coffre(109 * 16 + 8, 247 * 16, 0, scene->getCoffre(16, 4), TI_CLE, 4));
            addObject(new Coffre(130 * 16 + 8, 185 * 16, 0, scene->getCoffre(16, 5), TI_CLE, 5));
            addObject(new Coffre(149 * 16, 172 * 16, 0, scene->getCoffre(16, 6), TI_CLE, 6));
            addObject(new Coffre(169 * 16 + 8, 187 * 16, 0, scene->getCoffre(16, 7), TI_CLE, 7));
            addObject(new Coffre(169 * 16 + 8, 277 * 16, 0, scene->getCoffre(16, 8), TI_CLE, 8));
            addObject(new Coffre(189 * 16 + 8, 82 * 16, 0, scene->getCoffre(16, 9), TI_CLE, 9));
            addObject(new Coffre(189 * 16 + 8, 231 * 16, 0, scene->getCoffre(16, 10), TI_CLE, 10));
            addObject(new Coffre(209 * 16 + 8, 82 * 16, 0, scene->getCoffre(16, 11), TI_CLE, 11));
            addObject(new Coffre(209 * 16 + 8, 262 * 16, 0, scene->getCoffre(16, 12), TI_CLE, 12));
            addObject(new Coffre(229 * 16 + 8, 232 * 16, 0, scene->getCoffre(16, 13), TI_CLE, 13));
            addObject(new Coffre(269 * 16 + 8, 232 * 16, 0, scene->getCoffre(16, 14), TI_CLE, 14));
            addObject(new Coffre(289 * 16, 101 * 16, 0, scene->getCoffre(16, 15), TI_CLE, 15));
            addObject(new Coffre(289 * 16 + 8, 171 * 16, 0, scene->getCoffre(16, 16), TI_CLE, 16));
            addObject(new Coffre(289 * 16 + 8, 247 * 16, 0, scene->getCoffre(16, 17), TI_CLE, 17));
            addObject(new Coffre(289 * 16 + 8, 262 * 16, 0, scene->getCoffre(16, 18), TI_CLE, 18));

            if (scene->getCoffre(16, 19)) ouvrePorte(29, 13, 0);
            if (scene->getCoffre(16, 20)) ouvrePorte(38, 6, 1);
            if (scene->getCoffre(16, 21)) ouvrePorte(49, 103, 0);
            if (scene->getCoffre(16, 22)) ouvrePorte(38, 201, 1);
            if (scene->getCoffre(16, 23)) ouvrePorte(29, 193, 0);
            if (scene->getCoffre(16, 24)) ouvrePorte(29, 178, 0);
            if (scene->getCoffre(16, 25)) ouvrePorte(18, 171, 1);
            if (scene->getCoffre(16, 26)) ouvrePorte(9, 163, 0);
            if (scene->getCoffre(16, 27)) ouvrePorte(18, 156, 1);
            if (scene->getCoffre(16, 28)) ouvrePorte(38, 156, 1);
            if (scene->getCoffre(16, 29)) ouvrePorte(49, 163, 0);
            if (scene->getCoffre(16, 30)) ouvrePorte(58, 171, 1);
            if (scene->getCoffre(16, 31)) ouvrePorte(69, 178, 0);
            if (scene->getCoffre(16, 32)) ouvrePorte(58, 186, 1);
            if (scene->getCoffre(16, 33)) ouvrePorte(118, 291, 1);
            if (scene->getCoffre(16, 34)) ouvrePorte(129, 283, 2);
            if (scene->getCoffre(16, 35)) ouvrePorte(158, 171, 3);
            if (scene->getCoffre(16, 36)) ouvrePorte(169, 268, 2);
            if (scene->getCoffre(16, 37)) ouvrePorte(218, 81, 3);
            if (scene->getCoffre(16, 38)) ouvrePorte(209, 157, 4);
            if (scene->getCoffre(16, 39)) ouvrePorte(289, 157, 4);

            addObject(new Interrupteur(23*16, 82*16, 0, scene->getCoffre(17, 4), map));
            addObject(new Interrupteur(43*16, 7*16, 0, scene->getCoffre(17, 5), map));
            addObject(new Interrupteur(47*16, 192*16, 0, scene->getCoffre(17, 6), map));
            addObject(new Interrupteur(47*16, 252*16, 0, scene->getCoffre(17, 7), map));
            addObject(new Interrupteur(63*16, 82*16, 0, scene->getCoffre(17, 8), map));
            addObject(new Interrupteur(76*16, 232*16, 0, scene->getCoffre(17, 9), map));
            addObject(new Interrupteur(63*16, 247*16, 0, scene->getCoffre(17, 10), map));
            addObject(new Interrupteur(71*16, 267*16, 0, scene->getCoffre(17, 11), map));
            addObject(new Interrupteur(113*16, 171*16, 0, scene->getCoffre(17, 12), map));
            addObject(new Interrupteur(127*16, 102*16, 0, scene->getCoffre(17, 13), map));
            addObject(new Interrupteur(137*16, 115*16, 0, scene->getCoffre(17, 14), map));
            addObject(new Interrupteur(122*16, 160*16, 0, scene->getCoffre(17, 15), map));
            addObject(new Interrupteur(127*16, 192*16, 0, scene->getCoffre(17, 16), map));
            addObject(new Interrupteur(147*16, 102*16, 0, scene->getCoffre(17, 17), map));
            addObject(new Interrupteur(152*16, 272*16, 0, scene->getCoffre(17, 18), map));
            addObject(new Interrupteur(147*16, 282*16, 0, scene->getCoffre(17, 19), map));
            addObject(new Interrupteur(167*16, 154*16, 0, scene->getCoffre(17, 20), map));
            addObject(new Interrupteur(167*16, 237*16, 0, scene->getCoffre(17, 21), map));
            addObject(new Interrupteur(177*16, 250*16, 0, scene->getCoffre(17, 22), map));
            addObject(new Interrupteur(183*16, 82*16, 0, scene->getCoffre(17, 23), map));
            addObject(new Interrupteur(217*16, 265*16, 0, scene->getCoffre(17, 24), map));
            addObject(new Interrupteur(236*16, 157*16, 0, scene->getCoffre(17, 25), map));
            addObject(new Interrupteur(232*16, 237*16, 0, scene->getCoffre(17, 26), map));
            addObject(new Interrupteur(256*16, 7*16, 0, scene->getCoffre(17, 27), map));
            addObject(new Interrupteur(249*16, 168*16, 0, scene->getCoffre(17, 28), map));
            addObject(new Interrupteur(269*16, 108*16, 0, scene->getCoffre(17, 29), map));
            addObject(new Interrupteur(263*16, 157*16, 0, scene->getCoffre(17, 30), map));
            addObject(new Interrupteur(267*16, 237*16, 0, scene->getCoffre(17, 31), map));
            addObject(new Interrupteur(292*16, 94*16, 0, scene->getCoffre(17, 32), map));
            addObject(new Interrupteur(282*16, 169*16, 0, scene->getCoffre(17, 33), map));
            addObject(new Interrupteur(287*16, 192*16, 0, scene->getCoffre(17, 34), map));
            addObject(new Interrupteur(282*16, 244*16, 0, scene->getCoffre(17, 35), map));
            addObject(new Interrupteur(282*16, 265*16, 0, scene->getCoffre(17, 36), map));
            addObject(new Interrupteur(162*16, 115*16, 0, scene->getCoffre(17, 42), map));

            if (scene->getCoffre(17, 4)) ouvrePorte(29, 88, 0);
            if (scene->getCoffre(17, 5)) ouvrePorte(49, 13, 0);
            if (scene->getCoffre(17, 6)) ouvrePorte(49, 193, 0);
            if (scene->getCoffre(17, 7)) ouvrePorte(49, 253, 0);
            if (scene->getCoffre(17, 8)) ouvrePorte(69, 88, 0);
            if (scene->getCoffre(17, 9)) ouvrePorte(69, 238, 0);
            if (scene->getCoffre(17, 10)) ouvrePorte(69, 253, 0);
            if (scene->getCoffre(17, 11)) ouvrePorte(78, 261, 1);
            if (scene->getCoffre(17, 12)) ouvrePorte(109, 163, 0);
            if (scene->getCoffre(17, 13)) ouvrePorte(129, 103, 0);
            if (scene->getCoffre(17, 14)) ouvrePorte(138, 111, 1);
            if (scene->getCoffre(17, 15)) ouvrePorte(118, 156, 1);
            if (scene->getCoffre(17, 16)) ouvrePorte(129, 193, 0);
            if (scene->getCoffre(17, 17)) ouvrePorte(149, 103, 0);
            if (scene->getCoffre(17, 18)) ouvrePorte(149, 268, 0);
            if (scene->getCoffre(17, 19)) ouvrePorte(149, 283, 0);
            if (scene->getCoffre(17, 20)) ouvrePorte(158, 156, 1);
            if (scene->getCoffre(17, 21)) ouvrePorte(169, 238, 0);
            if (scene->getCoffre(17, 22)) ouvrePorte(178, 246, 1);
            if (scene->getCoffre(17, 23)) ouvrePorte(189, 88, 0);
            if (scene->getCoffre(17, 24)) ouvrePorte(218, 261, 1);
            if (scene->getCoffre(17, 25)) ouvrePorte(218, 156, 1);
            if (scene->getCoffre(17, 26)) ouvrePorte(229, 238, 0);
            if (scene->getCoffre(17, 27)) ouvrePorte(249, 13, 0);
            if (scene->getCoffre(17, 28)) ouvrePorte(249, 178, 0);
            if (scene->getCoffre(17, 29)) ouvrePorte(278, 111, 1);
            if (scene->getCoffre(17, 30)) ouvrePorte(278, 156, 1);
            if (scene->getCoffre(17, 31)) ouvrePorte(269, 238, 0);
            if (scene->getCoffre(17, 32)) ouvrePorte(289, 88, 0);
            if (scene->getCoffre(17, 33)) ouvrePorte(278, 171, 1);
            if (scene->getCoffre(17, 34)) ouvrePorte(289, 178, 0);
            if (scene->getCoffre(17, 35)) ouvrePorte(278, 246, 1);
            if (scene->getCoffre(17, 36)) ouvrePorte(278, 261, 1);
            if (scene->getCoffre(17, 42)) ouvrePorte(158, 111, 1);

            addObject(new TasDePierres(202*16, 281*16, 1)); addObject(new TasDePierres(216*16, 281*16, 1));

            addObject(new Sphere(129*16+8, 288*16));
            addObject(new Sphere(139*16+8, 232*16));
            addObject(new Sphere(164*16+8, 288*16));

            addObject(new InterrupteurStar(130*16, 7*16, scene->getCoffre(16, 40), map));
            addObject(new InterrupteurStar(170*16, 7*16, !scene->getCoffre(16, 40), map));
            if (scene->getCoffre(16, 40)) {
                map->activateInterStar(130*16, 7*16, false);
            }

            addObject(new Caisse(30*16, 260*16, 2, 3)); addObject(new Caisse(27*16, 261*16, 2, 4));
            addObject(new Caisse(29*16, 261*16, 2, 3)); addObject(new Caisse(31*16, 262*16, 2, 2));
            addObject(new Caisse(29*16, 263*16, 2, 2)); addObject(new Caisse(30*16, 263*16, 2, 2));
            addObject(new Caisse(27*16, 264*16, 2, 1)); addObject(new Caisse(31*16, 264*16, 2, 1));

            addObject(new Caisse(8*16, 80*16, 5, 1)); addObject(new Caisse(8*16, 81*16, 2, 2));
            addObject(new Caisse(9*16, 81*16, 5, 2)); addObject(new Caisse(10*16, 81*16, 2, 2));
            addObject(new Caisse(8*16, 82*16, 5, 1)); addObject(new Caisse(9*16, 83*16, 2, 1));
            addObject(new Caisse(11*16, 83*16, 5, 2));

            addObject(new Caisse(88*16, 245*16, 5, 5)); addObject(new Caisse(92*16, 245*16, 5, 5));
            addObject(new Caisse(88*16, 249*16, 5, 5)); addObject(new Caisse(92*16, 249*16, 5, 5));

            addObject(new Pnj(95*16, 205*16, 71, 1727));

            addEnnemi(new Ennemi015(249*16+4,37*16)); addEnnemi(new Ennemi015(219*16+4,127*16));
            addEnnemi(new Ennemi015(281*16+4,130*16)); addEnnemi(new Ennemi015(219*16+4,220*16));
            addEnnemi(new Ennemi015(276*16+4,219*16));

            addEnnemi(new Ennemi018(9*16, 203*16+2)); addEnnemi(new Ennemi018(34*16, 3*16+2));
            addEnnemi(new Ennemi018(66*16, 86*16+2)); addEnnemi(new Ennemi018(15*16, 92*16+2));
            addEnnemi(new Ennemi018(57*16, 86*16+2)); addEnnemi(new Ennemi018(26*16, 189*16+2));
            addEnnemi(new Ennemi018(33*16, 185*16+2)); addEnnemi(new Ennemi018(26*16, 176*16+2));
            addEnnemi(new Ennemi018(13*16, 161*16+2)); addEnnemi(new Ennemi018(46*16, 153*16+2));
            addEnnemi(new Ennemi018(53*16, 159*16+2)); addEnnemi(new Ennemi018(52*16, 176*16+2));
            addEnnemi(new Ennemi018(66*16, 183*16+2)); addEnnemi(new Ennemi018(68*16, 191*16+2));
            addEnnemi(new Ennemi018(73*16, 186*16+2)); addEnnemi(new Ennemi018(18*16, 286*16+2));
            addEnnemi(new Ennemi018(27*16, 281*16+2)); addEnnemi(new Ennemi018(46*16, 293*16+2));
            addEnnemi(new Ennemi018(53*16, 276*16+2)); addEnnemi(new Ennemi018(23*16, 237*16+2));
            addEnnemi(new Ennemi018(14*16, 241*16+2)); addEnnemi(new Ennemi018(31*16, 234*16+2));
            addEnnemi(new Ennemi018(92*16, 293*16+2)); addEnnemi(new Ennemi018(72*16, 281*16+2));

            addEnnemi(new Ennemi026(155*16,261*16)); addEnnemi(new Ennemi026(152*16,252*16));
            addEnnemi(new Ennemi026(138*16,253*16)); addEnnemi(new Ennemi026(132*16,260*16));
            addEnnemi(new Ennemi026(186*16,273*16)); addEnnemi(new Ennemi026(193*16,278*16));
            addEnnemi(new Ennemi026(128*16,226*16)); addEnnemi(new Ennemi026(151*16,226*16));
            addEnnemi(new Ennemi026(115*16,253*16)); addEnnemi(new Ennemi026(126*16,288*16));
            addEnnemi(new Ennemi026(168*16,288*16)); addEnnemi(new Ennemi026(132*16,296*16));
            addEnnemi(new Ennemi026(124*16,151*16)); addEnnemi(new Ennemi026(135*16,151*16));
            addEnnemi(new Ennemi026(124*16,163*16)); addEnnemi(new Ennemi026(135*16,163*16));
            addEnnemi(new Ennemi026(103*16,185*16)); addEnnemi(new Ennemi026(116*16,193*16));
            addEnnemi(new Ennemi026(152*16,168*16)); addEnnemi(new Ennemi026(191*16,157*16));
            addEnnemi(new Ennemi026(198*16,166*16)); addEnnemi(new Ennemi026(175*16,178*16));
            addEnnemi(new Ennemi026(165*16,106*16)); addEnnemi(new Ennemi026(174*16,118*16));
            addEnnemi(new Ennemi026(146*16,86*16)); addEnnemi(new Ennemi026(154*16,78*16));
            addEnnemi(new Ennemi026(104*16,110*16)); addEnnemi(new Ennemi026(124*16,268*16));
            addEnnemi(new Ennemi026(186*16,198*16));

            addEnnemi(new Ennemi044(249*16-3+8, 200*16-10)); addEnnemi(new Ennemi044(218*16-3, 186*16-10));
            addEnnemi(new Ennemi044(223*16-3, 200*16-10)); addEnnemi(new Ennemi044(275*16-3, 200*16-10));
            addEnnemi(new Ennemi044(283*16-3, 186*16-10)); addEnnemi(new Ennemi044(269*16+8-3, 172*16-10));
            addEnnemi(new Ennemi044(229*16+8-3, 172*16-10)); addEnnemi(new Ennemi044(229*16+8-3, 157*16-10));
            addEnnemi(new Ennemi044(269*16+8-3, 112*16-10)); addEnnemi(new Ennemi044(249*16+8-3, 110*16-10));
            addEnnemi(new Ennemi044(226*16-3, 96*16-10)); addEnnemi(new Ennemi044(211*16-3, 108*16-10));
            addEnnemi(new Ennemi044(206*16+8-3, 101*16-10)); addEnnemi(new Ennemi044(289*16+8-3, 82*16-10));
            addEnnemi(new Ennemi044(249*16+8-3, 7*16-10)); addEnnemi(new Ennemi044(229*16+8-3, 22*16-10));
            addEnnemi(new Ennemi044(269*16+8-3, 22*16-10));

            addEnnemi(new Ennemi053(116*16, 127*16)); addEnnemi(new Ennemi053(135*16, 131*16));
            addEnnemi(new Ennemi053(158*16, 128*16)); addEnnemi(new Ennemi053(176*16, 131*16));
            addEnnemi(new Ennemi053(195*16, 129*16)); addEnnemi(new Ennemi053(107*16, 217*16));
            addEnnemi(new Ennemi053(124*16, 220*16)); addEnnemi(new Ennemi053(146*16, 217*16));
            addEnnemi(new Ennemi053(161*16, 221*16)); addEnnemi(new Ennemi053(180*16, 217*16));
            addEnnemi(new Ennemi053(139*16, 38*16)); addEnnemi(new Ennemi053(159*16, 41*16));

            addEnnemi(new Ennemi056(274*16-1, 275*16-1)); addEnnemi(new Ennemi056(229*16+8-1, 277*16-1));
            addEnnemi(new Ennemi056(226*16-1, 254*16-1)); addEnnemi(new Ennemi056(266*16-1, 251*16-1));
            addEnnemi(new Ennemi056(273*16-1, 257*16-1)); addEnnemi(new Ennemi056(227*16-1, 295*16-1));
            addEnnemi(new Ennemi056(269*16-1+8, 97*16-1));

            addEnnemi(new Ennemi064(29*16-4, 6*16-4)); addEnnemi(new Ennemi064(89*16-4, 102*16-4));
            addEnnemi(new Ennemi064(69*16-4, 96*16-4)); addEnnemi(new Ennemi064(29*16-4, 96*16-4));
            addEnnemi(new Ennemi064(36*16-4, 81*16-4)); addEnnemi(new Ennemi064(69*16-4, 111*16-4));
            addEnnemi(new Ennemi064(49*16-4, 201*16-4)); addEnnemi(new Ennemi064(69*16-4, 246*16-4));
            addEnnemi(new Ennemi064(49*16-4, 261*16-4)); addEnnemi(new Ennemi064(49*16-4, 246*16-4));
            addEnnemi(new Ennemi064(77*16-4, 291*16-4)); addEnnemi(new Ennemi064(29*16-4, 201*16-4));
            addEnnemi(new Ennemi064(29*16-4, 21*16-4)); addEnnemi(new Ennemi064(69*16-4, 21*16-4));
            addEnnemi(new Ennemi064(9*16-4, 171*16-4)); addEnnemi(new Ennemi064(29*16-4, 156*16-4));
            addEnnemi(new Ennemi064(69*16-4, 171*16-4)); addEnnemi(new Ennemi064(89*16-4, 231*16-4));

            addEnnemi(new Ennemi077(15*16-13, 127*16-12)); addEnnemi(new Ennemi077(43*16-13, 130*16-12));
            addEnnemi(new Ennemi077(88*16-13, 128*16-12)); addEnnemi(new Ennemi077(48*16-13, 40*16-12));
            addEnnemi(new Ennemi077(27*16-13, 217*16-12)); addEnnemi(new Ennemi077(73*16-13, 220*16-12));

            addEnnemi(new Ennemi119(147*16-3,291*16+5)); addEnnemi(new Ennemi119(152*16-3,291*16+5));
            addEnnemi(new Ennemi119(189*16-3+8,261*16+5)); addEnnemi(new Ennemi119(169*16-3+8,231*16+5));
            addEnnemi(new Ennemi119(109*16-3+8,261*16+5)); addEnnemi(new Ennemi119(109*16-3+8,291*16+5));
            addEnnemi(new Ennemi119(189*16-3+8,246*16+5)); addEnnemi(new Ennemi119(149*16-3+8,156*16+5));
            addEnnemi(new Ennemi119(129*16-3+8,201*16+5)); addEnnemi(new Ennemi119(169*16-3+8,201*16+5));
            addEnnemi(new Ennemi119(189*16-3+8,186*16+5)); addEnnemi(new Ennemi119(109*16-3+8,171*16+5));
            addEnnemi(new Ennemi119(189*16-3+8,111*16+5)); addEnnemi(new Ennemi119(187*16-3,96*16+5));
            addEnnemi(new Ennemi119(192*16-3,96*16+5)); addEnnemi(new Ennemi119(149*16-3+8,96*16+5));
            addEnnemi(new Ennemi119(109*16-3+8,96*16+5)); addEnnemi(new Ennemi119(169*16-3+8,81*16+5));
            addEnnemi(new Ennemi119(119*16-3+8,81*16+5)); addEnnemi(new Ennemi119(147*16-3,21*16+5));
            addEnnemi(new Ennemi119(152*16-3,21*16+5));

            addObject(new Jarre(15*16, 102*16, 0, TI_BOMBE, map));
            addObject(new Jarre(7*16, 289*16, 0, TI_BOMBE, map));
            addObject(new Jarre(12*16, 289*16, 0, TI_BOMBE, map));
            addObject(new Jarre(7*16, 294*16, 0, TI_BOMBE, map));
            addObject(new Jarre(12*16, 294*16, 0, TI_BOMBE, map));
            break;
    }
}
