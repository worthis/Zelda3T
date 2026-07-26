#include "ItemHelper.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../MainController.h"

#include "../items/PetitCoeur.h"
#include "../items/RubisVert.h"
#include "../items/RubisBleu.h"
#include "../items/RubisRouge.h"
#include "../items/GanonOrUn.h"
#include "../items/GanonOrDeux.h"
#include "../items/GanonOrCinq.h"
#include "../items/PieceOrUn.h"
#include "../items/PieceOrDeux.h"
#include "../items/PieceOrTrois.h"
#include "../items/Arrow.h"
#include "../items/Bomb.h"
#include "../items/MagiePetit.h"
#include "../items/MagieGrand.h"
#include "../items/QuartCoeur.h"
#include "../items/Coeur.h"
#include "../items/PetiteCle.h"
#include "../items/Triforce.h"
#include "../items/GemmeForce.h"
#include "../items/Planches.h"
#include "../items/PetiteEpee.h"
#include "../items/Medaillon.h"
#include "../items/CleTemps.h"
#include "../items/Gemme.h"

ItemHelper ItemHelper::instance=ItemHelper();

ItemHelper::ItemHelper() : image(0) {
}

ItemHelper::~ItemHelper() {
}

void ItemHelper::close() {
    ResourceManager::getInstance()->free(image);
}

ItemHelper* ItemHelper::getInstance() {
    return &instance;
}

Item* ItemHelper::createItem(TypeItem type, int x, int y, int id, bool withAnim) {

    TypeItem typeCorrige = type;

    Epoque epoque = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getEpoque();
    if (type == TI_RUBIS_VERT && epoque == EP_PASSE) typeCorrige = TI_PIECE_OR_1;
    if (type == TI_RUBIS_BLEU && epoque == EP_PASSE) typeCorrige = TI_PIECE_OR_2;
    if (type == TI_RUBIS_ROUGE && epoque == EP_PASSE) typeCorrige = TI_PIECE_OR_3;
    if (type == TI_RUBIS_VERT && epoque == EP_FUTUR) typeCorrige = TI_GANON_OR_1;
    if (type == TI_RUBIS_BLEU && epoque == EP_FUTUR) typeCorrige = TI_GANON_OR_2;
    if (type == TI_RUBIS_ROUGE && epoque == EP_FUTUR) typeCorrige = TI_GANON_OR_5;

    y -= 8;
    switch (typeCorrige) {
        case TI_EPEE_1 : return new PetiteEpee(x - 4, y);
        case TI_BOMBE : return new Bomb(x - 6, y);
        case TI_FLECHE : return new Arrow(x - 2, y);
        case TI_MAGIE_BEAUCOUP : return new MagieGrand(x - 4, y);
        case TI_MAGIE_PEU : return new MagiePetit(x - 4, y);
        case TI_PETIT_COEUR : return new PetitCoeur(x - 4, y);
        case TI_QUART_COEUR : return new QuartCoeur(x - 8, y, id);
        case TI_COEUR : return new Coeur(x - 8, y, id, withAnim);
        case TI_RUBIS_VERT : return new RubisVert(x - 4, y);
        case TI_RUBIS_BLEU : return new RubisBleu(x - 4, y);
        case TI_RUBIS_ROUGE : return new RubisRouge(x - 4, y);
        case TI_GANON_OR_1 : return new GanonOrUn(x - 8, y);
        case TI_GANON_OR_2 : return new GanonOrDeux(x - 8, y);
        case TI_GANON_OR_5 : return new GanonOrCinq(x - 8, y);
        case TI_PIECE_OR_1 : return new PieceOrUn(x - 8, y);
        case TI_PIECE_OR_2 : return new PieceOrDeux(x - 8, y);
        case TI_PIECE_OR_3 : return new PieceOrTrois(x - 8, y);
        case TI_CLE : return new PetiteCle(x - 4, y, id, withAnim);
        case TI_TRIFORCE : return new Triforce(x - 13, y - 5, withAnim);
        case TI_GEMME_FORCE : return new GemmeForce(x - 8, y, id, withAnim);
        case TI_PLANCHES : return new Planches(x, y + 8);
        case TI_MEDAILLON_1 : return new Medaillon(x - 8, y, 0);
        case TI_MEDAILLON_2 : return new Medaillon(x - 8, y, 1);
        case TI_MEDAILLON_3 : return new Medaillon(x - 8, y, 2);
        case TI_GEMME_ROUGE : return new Gemme(x - 8, y, 0);
        case TI_GEMME_BLEUE : return new Gemme(x - 8, y, 1);
        case TI_GEMME_JAUNE : return new Gemme(x - 8, y, 2);
        case TI_GEMME_VERTE : return new Gemme(x - 8, y, 3);
        case TI_CLE_TEMPS : return new CleTemps(x - 8, y);
        default : return 0;
    }
}

TypeItem ItemHelper::getFish(Equipment e, int mapId) {
    int max;
    if (mapId == 16 || mapId == 17) {
        max = e == CANNE_A_PECHE_3 ? 5 : e == CANNE_A_PECHE_2 ? 4 : 2;
        switch (rand()%max) {
            case 0 : return TI_CARASSIN_DORE;
            case 1 : return TI_EPINOCHE;
            case 2 : return TI_AYU;
            case 3 : return TI_POISSON_CHAT;
            case 4 : return TI_CARPE;
        }
    } else if (mapId == 19 || mapId == 20 || mapId == 24) {
        max = e == CANNE_A_PECHE_3 ? 5 : e == CANNE_A_PECHE_2 ? 4 : 2;
        switch (rand()%max) {
            case 0 : return TI_ABLETTE;
            case 1 : return TI_GREMILLE;
            case 2 : return TI_BLACK_BASS;
            case 3 : return TI_LAMPROIE;
            case 4 : return TI_SILURE;
        }
    } else if (mapId == 21) {
        max = e == CANNE_A_PECHE_3 || e == CANNE_A_PECHE_2 ? 5 : 3;
        switch (rand()%max) {
            case 0 : return TI_ECREVISSE;
            case 1 : return TI_POISSON_ZEBRE;
            case 2 : return TI_MAGICARPE;
            case 3 : return TI_BARBEAU;
            case 4 : return TI_HOTU;
        }
    } else if (mapId == 22) {
        max = e == CANNE_A_PECHE_3 ? 5 : e == CANNE_A_PECHE_2 ? 4 : 3;
        switch (rand()%max) {
            case 0 : return TI_PIBALE;
            case 1 : return TI_GOUJON;
            case 2 : return TI_BLENNIE;
            case 3 : return TI_TRUITE;
            case 4 : return TI_SAUMON;
        }
    } else if (mapId == 25 || mapId == 26 || mapId == 27) {
        max = e == CANNE_A_PECHE_3 ? 6 : e == CANNE_A_PECHE_2 ? 5 : 3;
        switch (rand()%max) {
            case 0 : return TI_GOBIE;
            case 1 : return TI_CRABE;
            case 2 : return TI_LOCHE;
            case 3 : return TI_PERCHE_NOIRE;
            case 4 : return TI_HUCHON;
            case 5 : return TI_ESTURGEON;
        }
    } else if (mapId == 30) {
        max = e == CANNE_A_PECHE_3 ? 4 : e == CANNE_A_PECHE_2 ? 3 : 2;
        switch (rand()%max) {
            case 0 : return TI_EPERLAN;
            case 1 : return TI_VAIRON;
            case 2 : return TI_ANGUILLE;
            case 3 : return TI_OMBLE_CHEVALIER;
        }
    }
    return TI_NO_ITEM;
}

void ItemHelper::drawItem(TypeItem type, int x, int y) {
    if (image == 0) {
        image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    }

    switch (type) {
        case TI_QUART_COEUR : WindowManager::getInstance()->draw(image, 45, 0, 16, 14, x - 8, y - 7); break;
        case TI_COEUR : WindowManager::getInstance()->draw(image, 30, 0, 14, 13, x - 7, y - 7); break;
        case TI_CRISTAL : WindowManager::getInstance()->draw(image, 32, 30, 12, 16, x - 6, y - 8); break;
        case TI_GEMME_FORCE : WindowManager::getInstance()->draw(image, 16, 63, 16, 16, x - 8, y - 8); break;
        case TI_MEDAILLON_1 : WindowManager::getInstance()->draw(image, 144, 0, 16, 16, x - 8, y - 8); break;
        case TI_MEDAILLON_2 : WindowManager::getInstance()->draw(image, 144, 16, 16, 16, x - 8, y - 8); break;
        case TI_MEDAILLON_3 : WindowManager::getInstance()->draw(image, 144, 32, 16, 16, x - 8, y - 8); break;
        case TI_CLE_TEMPS : WindowManager::getInstance()->draw(image, 240, 176, 16, 16, x - 8, y - 8); break;
        case TI_FLACON_1 : case TI_FLACON_2 : case TI_FLACON_3 : case TI_FLACON_4 :
            WindowManager::getInstance()->draw(image, 30, 14, 16, 16, x - 8, y - 8); break;
        case TI_FLECHE_FEU : WindowManager::getInstance()->draw(image, 224, 160, 16, 16, x - 8, y - 8); break;
        case TI_FLECHE_GLACE : WindowManager::getInstance()->draw(image, 240, 160, 16, 16, x - 8, y - 8); break;
        case TI_FLECHE_LUMIERE : WindowManager::getInstance()->draw(image, 224, 176, 16, 16, x - 8, y - 8); break;
        case TI_CANNE_A_PECHE_1 : WindowManager::getInstance()->draw(image, 240, 112, 16, 16, x - 8, y - 8); break;
        case TI_CANNE_A_PECHE_2 : WindowManager::getInstance()->draw(image, 240, 128, 16, 16, x - 8, y - 8); break;
        case TI_CANNE_A_PECHE_3 : WindowManager::getInstance()->draw(image, 240, 144, 16, 16, x - 8, y - 8); break;
        case TI_BOUCLIER_1 : WindowManager::getInstance()->draw(image, 0, 95, 8, 10, x - 4, y - 5); break;
        case TI_BOUCLIER_2 : WindowManager::getInstance()->draw(image, 8, 95, 14, 16, x - 7, y - 8); break;
        case TI_BOUCLIER_3 : WindowManager::getInstance()->draw(image, 22, 95, 14, 16, x - 7, y - 8); break;
        case TI_BOUCLIER_4 : WindowManager::getInstance()->draw(image, 272, 64, 16, 16, x - 8, y - 8); break;
        case TI_TUNIQUE_BLEUE : WindowManager::getInstance()->draw(image, 80, 48, 16, 16, x - 8, y - 8); break;
        case TI_TUNIQUE_ROUGE : WindowManager::getInstance()->draw(image, 80, 64, 16, 16, x - 8, y - 8); break;
        case TI_TUNIQUE_BLANCHE : WindowManager::getInstance()->draw(image, 288, 64, 16, 16, x - 8, y - 8); break;
        case TI_CHANT_1 : WindowManager::getInstance()->draw(image, 48, 16, 16, 16, x - 8, y - 8); break;
        case TI_CHANT_2 : WindowManager::getInstance()->draw(image, 48, 32, 16, 16, x - 8, y - 8); break;
        case TI_CHANT_3 : WindowManager::getInstance()->draw(image, 48, 48, 16, 16, x - 8, y - 8); break;
        case TI_EPEE_1 : WindowManager::getInstance()->draw(image, 36, 95, 6, 16, x - 3, y - 8); break;
        case TI_EPEE_2 : WindowManager::getInstance()->draw(image, 48, 95, 7, 16, x - 3, y - 8); break;
        case TI_EPEE_3 : WindowManager::getInstance()->draw(image, 145, 48, 7, 16, x - 3, y - 8); break;
        case TI_EPEE_5 : WindowManager::getInstance()->draw(image, 152, 48, 7, 16, x - 3, y - 8); break;
        case TI_CARTE : case TI_CARTE_DONJON : WindowManager::getInstance()->draw(image, 32, 63, 16, 16, x - 8, y - 8); break;
        case TI_SAC_BOMBES : WindowManager::getInstance()->draw(image, 96, 0, 16, 16, x - 8, y - 8); break;
        case TI_GANT : WindowManager::getInstance()->draw(image, 64, 0, 16, 16, x - 8, y - 8); break;
        case TI_GANT2 : WindowManager::getInstance()->draw(image, 64, 16, 16, 16, x - 8, y - 8); break;
        case TI_ARC : WindowManager::getInstance()->draw(image, 64, 32, 16, 16, x - 8, y - 8); break;
        case TI_ARC_FEE : WindowManager::getInstance()->draw(image, 64, 48, 16, 16, x - 8, y - 8); break;
        case TI_ARC_OR : WindowManager::getInstance()->draw(image, 256, 64, 16, 16, x - 8, y - 8); break;
        case TI_PALMES : WindowManager::getInstance()->draw(image, 30, 46, 16, 17, x - 8, y - 9); break;
        case TI_OCARINA : WindowManager::getInstance()->draw(image, 49, 65, 14, 14, x - 7, y - 7); break;
        case TI_MARTEAU : WindowManager::getInstance()->draw(image, 64, 96, 16, 16, x - 8, y - 8); break;
        case TI_LANTERNE : WindowManager::getInstance()->draw(image, 80, 0, 16, 16, x - 8, y - 8); break;
        case TI_BOTTES : WindowManager::getInstance()->draw(image, 80, 96, 16, 16, x - 8, y - 8); break;
        case TI_PERLE_LUNE : WindowManager::getInstance()->draw(image, 80, 16, 16, 16, x - 8, y - 8); break;
        case TI_LIVRE : WindowManager::getInstance()->draw(image, 128, 70, 16, 16, x - 8, y - 8); break;
        case TI_POTION_ROUGE : WindowManager::getInstance()->draw(image, 112, 0, 16, 16, x - 8, y - 8); break;
        case TI_POTION_VERTE : WindowManager::getInstance()->draw(image, 112, 16, 16, 16, x - 8, y - 8); break;
        case TI_POTION_BLEUE : WindowManager::getInstance()->draw(image, 112, 48, 16, 16, x - 8, y - 8); break;
        case TI_BOUSSOLE : WindowManager::getInstance()->draw(image, 96, 16, 16, 16, x - 8, y - 8); break;
        case TI_CLE_BOSS : WindowManager::getInstance()->draw(image, 96, 32, 16, 16, x - 8, y - 8); break;
        case TI_CLE : WindowManager::getInstance()->draw(image, 96, 48, 16, 16, x - 8, y - 8); break;
        case TI_GRAPPIN : WindowManager::getInstance()->draw(image, 96, 64, 16, 16, x - 8, y - 8); break;
        case TI_BAGUETTE_FEU : WindowManager::getInstance()->draw(image, 96, 96, 16, 16, x - 8, y - 8); break;
        case TI_RUBIS_ROUGE : WindowManager::getInstance()->draw(image, 0, 35, 8, 14, x - 4, y - 7); break;
        case TI_BAGUETTE_GLACE : WindowManager::getInstance()->draw(image, 128, 16, 16, 16, x - 8, y - 8); break;
        case TI_MASQUE : WindowManager::getInstance()->draw(image, 144, 112, 16, 16, x - 8, y - 8); break;
        case TI_TRIFORCE : WindowManager::getInstance()->draw(image, 128, 86, 26, 26, x - 13, y - 16); break;
        case TI_ECREVISSE : WindowManager::getInstance()->draw(image, 0, 128, 16, 16, x - 8, y - 8); break;
        case TI_EPERLAN : WindowManager::getInstance()->draw(image, 16, 128, 16, 16, x - 8, y - 8); break;
        case TI_POISSON_ZEBRE : WindowManager::getInstance()->draw(image, 32, 128, 16, 16, x - 8, y - 8); break;
        case TI_GOBIE : WindowManager::getInstance()->draw(image, 48, 128, 16, 16, x - 8, y - 8); break;
        case TI_CRABE : WindowManager::getInstance()->draw(image, 64, 128, 16, 16, x - 8, y - 8); break;
        case TI_PIBALE : WindowManager::getInstance()->draw(image, 80, 128, 16, 16, x - 8, y - 8); break;
        case TI_VAIRON : WindowManager::getInstance()->draw(image, 96, 128, 16, 16, x - 8, y - 8); break;
        case TI_CARASSIN_DORE : WindowManager::getInstance()->draw(image, 112, 128, 16, 16, x - 8, y - 8); break;
        case TI_ABLETTE : WindowManager::getInstance()->draw(image, 128, 128, 16, 16, x - 8, y - 8); break;
        case TI_GOUJON : WindowManager::getInstance()->draw(image, 144, 128, 16, 16, x - 8, y - 8); break;
        case TI_LOCHE : WindowManager::getInstance()->draw(image, 0, 144, 16, 16, x - 8, y - 8); break;
        case TI_EPINOCHE : WindowManager::getInstance()->draw(image, 16, 144, 16, 16, x - 8, y - 8); break;
        case TI_GREMILLE : WindowManager::getInstance()->draw(image, 32, 144, 16, 16, x - 8, y - 8); break;
        case TI_BLENNIE : WindowManager::getInstance()->draw(image, 48, 144, 16, 16, x - 8, y - 8); break;
        case TI_MAGICARPE : WindowManager::getInstance()->draw(image, 144, 160, 16, 16, x - 8, y - 8); break;
        case TI_TRUITE : WindowManager::getInstance()->draw(image, 64, 144, 24, 16, x - 12, y - 8); break;
        case TI_AYU : WindowManager::getInstance()->draw(image, 88, 144, 24, 16, x - 12, y - 8); break;
        case TI_PERCHE_NOIRE : WindowManager::getInstance()->draw(image, 112, 144, 24, 16, x - 12, y - 8); break;
        case TI_ANGUILLE : WindowManager::getInstance()->draw(image, 136, 144, 24, 16, x - 12, y - 8); break;
        case TI_POISSON_CHAT : WindowManager::getInstance()->draw(image, 0, 160, 24, 16, x - 12, y - 8); break;
        case TI_BLACK_BASS : WindowManager::getInstance()->draw(image, 24, 160, 24, 16, x - 12, y - 8); break;
        case TI_HUCHON : WindowManager::getInstance()->draw(image, 48, 160, 24, 16, x - 12, y - 8); break;
        case TI_BARBEAU : WindowManager::getInstance()->draw(image, 72, 160, 24, 16, x - 12, y - 8); break;
        case TI_LAMPROIE : WindowManager::getInstance()->draw(image, 96, 160, 24, 16, x - 12, y - 8); break;
        case TI_HOTU : WindowManager::getInstance()->draw(image, 120, 160, 24, 16, x - 12, y - 8); break;
        case TI_SAUMON : WindowManager::getInstance()->draw(image, 0, 176, 32, 16, x - 16, y - 8); break;
        case TI_ESTURGEON : WindowManager::getInstance()->draw(image, 32, 176, 32, 16, x - 16, y - 8); break;
        case TI_OMBLE_CHEVALIER : WindowManager::getInstance()->draw(image, 64, 176, 32, 16, x - 16, y - 8); break;
        case TI_CARPE : WindowManager::getInstance()->draw(image, 96, 176, 32, 16, x - 16, y - 8); break;
        case TI_SILURE : WindowManager::getInstance()->draw(image, 128, 176, 32, 16, x - 16, y - 8); break;
        case TI_GEMME_ROUGE : WindowManager::getInstance()->draw(image, 192, 0, 16, 16, x - 8, y - 8); break;
        case TI_ENCLUME : WindowManager::getInstance()->draw(image, 192, 16, 16, 16, x - 8, y - 8); break;
        case TI_FER_CHEVAL : WindowManager::getInstance()->draw(image, 192, 32, 16, 16, x - 8, y - 8); break;
        case TI_BIJOU : WindowManager::getInstance()->draw(image, 192, 48, 16, 16, x - 8, y - 8); break;
        case TI_LETTRE : WindowManager::getInstance()->draw(image, 192, 64, 16, 16, x - 8, y - 8); break;
        case TI_ALLIANCE : WindowManager::getInstance()->draw(image, 192, 80, 16, 16, x - 8, y - 8); break;
        case TI_MARTEAU_PONT : WindowManager::getInstance()->draw(image, 192, 96, 16, 16, x - 8, y - 8); break;
        case TI_GEMME_BLEUE : WindowManager::getInstance()->draw(image, 208, 0, 16, 16, x - 8, y - 8); break;
        case TI_VIEILLE_BOTTE : WindowManager::getInstance()->draw(image, 208, 16, 16, 16, x - 8, y - 8); break;
        case TI_MARTEAU_LOURD : WindowManager::getInstance()->draw(image, 208, 32, 16, 16, x - 8, y - 8); break;
        case TI_CLOCHE : WindowManager::getInstance()->draw(image, 208, 48, 16, 16, x - 8, y - 8); break;
        case TI_HACHE : WindowManager::getInstance()->draw(image, 208, 64, 16, 16, x - 8, y - 8); break;
        case TI_CORDE : WindowManager::getInstance()->draw(image, 208, 80, 16, 16, x - 8, y - 8); break;
        case TI_PLAN : WindowManager::getInstance()->draw(image, 208, 96, 16, 16, x - 8, y - 8); break;
        case TI_GEMME_JAUNE : WindowManager::getInstance()->draw(image, 224, 0, 16, 16, x - 8, y - 8); break;
        case TI_VIN : WindowManager::getInstance()->draw(image, 224, 16, 16, 16, x - 8, y - 8); break;
        case TI_POUDRE_OR : WindowManager::getInstance()->draw(image, 224, 32, 16, 16, x - 8, y - 8); break;
        case TI_MIROIR : WindowManager::getInstance()->draw(image, 224, 48, 16, 16, x - 8, y - 8); break;
        case TI_CUILLERE : WindowManager::getInstance()->draw(image, 224, 64, 16, 16, x - 8, y - 8); break;
        case TI_CRANE : WindowManager::getInstance()->draw(image, 224, 80, 16, 16, x - 8, y - 8); break;
        case TI_REC_DETTE : WindowManager::getInstance()->draw(image, 224, 96, 16, 16, x - 8, y - 8); break;
        case TI_SCIE : WindowManager::getInstance()->draw(image, 224, 112, 16, 16, x - 8, y - 8); break;
        case TI_GEMME_VERTE : WindowManager::getInstance()->draw(image, 240, 0, 16, 16, x - 8, y - 8); break;
        case TI_CARTE_VOYAGE : WindowManager::getInstance()->draw(image, 240, 16, 16, 16, x - 8, y - 8); break;
        case TI_BALAIS : WindowManager::getInstance()->draw(image, 240, 32, 16, 16, x - 8, y - 8); break;
        case TI_CONFITURE : WindowManager::getInstance()->draw(image, 240, 48, 16, 16, x - 8, y - 8); break;
        case TI_CROISSANT : WindowManager::getInstance()->draw(image, 240, 64, 16, 16, x - 8, y - 8); break;
        case TI_BIERE : WindowManager::getInstance()->draw(image, 240, 80, 16, 16, x - 8, y - 8); break;
        case TI_CLOU : WindowManager::getInstance()->draw(image, 240, 96, 16, 16, x - 8, y - 8); break;
        case TI_SAC_RIZ : case TI_SAC_RIZ_10 : WindowManager::getInstance()->draw(image, 160, 128, 16, 16, x - 8, y - 8); break;
        case TI_BOCAL_EPICES : case TI_BOCAL_EPICES_10 : WindowManager::getInstance()->draw(image, 192, 128, 16, 16, x - 8, y - 8); break;
        case TI_SAC_OLIVES : case TI_SAC_OLIVES_10 : WindowManager::getInstance()->draw(image, 176, 128, 16, 16, x - 8, y - 8); break;
        case TI_PERLES : WindowManager::getInstance()->draw(image, 208, 128, 16, 16, x - 8, y - 8); break;
        case TI_PLUME : WindowManager::getInstance()->draw(image, 160, 144, 16, 16, x - 8, y - 8); break;
        case TI_POULET : WindowManager::getInstance()->draw(image, 176, 144, 16, 16, x - 8, y - 8); break;
        case TI_TAPISSERIE : WindowManager::getInstance()->draw(image, 192, 144, 16, 16, x - 8, y - 8); break;
        case TI_AMULETTE : WindowManager::getInstance()->draw(image, 208, 144, 16, 16, x - 8, y - 8); break;
        case TI_PARFUM : WindowManager::getInstance()->draw(image, 160, 160, 16, 16, x - 8, y - 8); break;
        case TI_ROC_MAGMA : WindowManager::getInstance()->draw(image, 176, 160, 16, 16, x - 8, y - 8); break;
        case TI_ROC_GIVRE : WindowManager::getInstance()->draw(image, 192, 160, 16, 16, x - 8, y - 8); break;
        case TI_POIVRON : WindowManager::getInstance()->draw(image, 208, 160, 16, 16, x - 8, y - 8); break;
        case TI_ROUAGE : WindowManager::getInstance()->draw(image, 160, 176, 16, 16, x - 8, y - 8); break;
        case TI_JAUGE : WindowManager::getInstance()->draw(image, 176, 176, 16, 16, x - 8, y - 8); break;
        case TI_ROUE : WindowManager::getInstance()->draw(image, 192, 176, 16, 16, x - 8, y - 8); break;
        case TI_SOURCE_NRJ : WindowManager::getInstance()->draw(image, 208, 176, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_RUBIS_1 : WindowManager::getInstance()->draw(image, 0, 79, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_RUBIS_2 : WindowManager::getInstance()->draw(image, 16, 79, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_RUBIS_3 : WindowManager::getInstance()->draw(image, 32, 79, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_RUBIS_4 : WindowManager::getInstance()->draw(image, 48, 79, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_GANON_OR_1 : WindowManager::getInstance()->draw(image, 160, 0, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_GANON_OR_2 : WindowManager::getInstance()->draw(image, 160, 16, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_GANON_OR_3 : WindowManager::getInstance()->draw(image, 160, 32, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_GANON_OR_4 : WindowManager::getInstance()->draw(image, 160, 48, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_PIECE_OR_1 : WindowManager::getInstance()->draw(image, 176, 0, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_PIECE_OR_2 : WindowManager::getInstance()->draw(image, 176, 16, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_PIECE_OR_3 : WindowManager::getInstance()->draw(image, 176, 32, 16, 16, x - 8, y - 8); break;
        case TI_BOURSE_PIECE_OR_4 : WindowManager::getInstance()->draw(image, 176, 48, 16, 16, x - 8, y - 8); break;
        case TI_PLANCHES : WindowManager::getInstance()->draw(image, 176, 112, 48, 16, x - 24, y - 8); break;
        case TI_DETECTEUR : WindowManager::getInstance()->draw(image, 80, 32, 16, 16, x - 8, y - 8); break;
        case TI_BONUS_FORCE_1 : case TI_BONUS_FORCE_2 : WindowManager::getInstance()->draw(image, 224, 128, 16, 16, x - 8, y - 8); break;
        case TI_BONUS_DEFENSE_1 : case TI_BONUS_DEFENSE_2 : WindowManager::getInstance()->draw(image, 224, 144, 16, 16, x - 8, y - 8); break;
        default : return;
    }
}
