#include "Monsters.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../content/ennemis/Ennemi001.h"
#include "../../content/ennemis/Ennemi002.h"
#include "../../content/ennemis/Ennemi003.h"
#include "../../content/ennemis/Ennemi004.h"
#include "../../content/ennemis/Ennemi005.h"
#include "../../content/ennemis/Ennemi006.h"
#include "../../content/ennemis/Ennemi007.h"
#include "../../content/ennemis/Ennemi008.h"
#include "../../content/ennemis/Ennemi009.h"
#include "../../content/ennemis/Ennemi010.h"
#include "../../content/ennemis/Ennemi011.h"
#include "../../content/ennemis/Ennemi012.h"
#include "../../content/ennemis/Ennemi013.h"
#include "../../content/ennemis/Ennemi014.h"
#include "../../content/ennemis/Ennemi015.h"
#include "../../content/ennemis/Ennemi016.h"
#include "../../content/ennemis/Ennemi018.h"
#include "../../content/ennemis/Ennemi019.h"
#include "../../content/ennemis/Ennemi022.h"
#include "../../content/ennemis/Ennemi023.h"
#include "../../content/ennemis/Ennemi024.h"
#include "../../content/ennemis/Ennemi025.h"
#include "../../content/ennemis/Ennemi026.h"
#include "../../content/ennemis/Ennemi027.h"
#include "../../content/ennemis/Ennemi028.h"
#include "../../content/ennemis/Ennemi029.h"
#include "../../content/ennemis/Ennemi030.h"
#include "../../content/ennemis/Ennemi031.h"
#include "../../content/ennemis/Ennemi032.h"
#include "../../content/ennemis/Ennemi033.h"
#include "../../content/ennemis/Ennemi034.h"
#include "../../content/ennemis/Ennemi035.h"
#include "../../content/ennemis/Ennemi037.h"
#include "../../content/ennemis/Ennemi038.h"
#include "../../content/ennemis/Ennemi039.h"
#include "../../content/ennemis/Ennemi040.h"
#include "../../content/ennemis/Ennemi041.h"
#include "../../content/ennemis/Ennemi042.h"
#include "../../content/ennemis/Ennemi043.h"
#include "../../content/ennemis/Ennemi044.h"
#include "../../content/ennemis/Ennemi046.h"
#include "../../content/ennemis/Ennemi047.h"
#include "../../content/ennemis/Ennemi048.h"
#include "../../content/ennemis/Ennemi050.h"
#include "../../content/ennemis/Ennemi053.h"
#include "../../content/ennemis/Ennemi054.h"
#include "../../content/ennemis/Ennemi055.h"
#include "../../content/ennemis/Ennemi056.h"
#include "../../content/ennemis/Ennemi062.h"
#include "../../content/ennemis/Ennemi064.h"
#include "../../content/ennemis/Ennemi072.h"
#include "../../content/ennemis/Ennemi076.h"
#include "../../content/ennemis/Ennemi077.h"
#include "../../content/ennemis/Ennemi084.h"
#include "../../content/ennemis/Ennemi086.h"
#include "../../content/ennemis/Ennemi087.h"
#include "../../content/ennemis/Ennemi089.h"
#include "../../content/ennemis/Ennemi091.h"
#include "../../content/ennemis/Ennemi092.h"
#include "../../content/ennemis/Ennemi093.h"
#include "../../content/ennemis/Ennemi094.h"
#include "../../content/ennemis/Ennemi095.h"
#include "../../content/ennemis/Ennemi097.h"
#include "../../content/ennemis/Ennemi098.h"
#include "../../content/ennemis/Ennemi099.h"
#include "../../content/ennemis/Ennemi100.h"
#include "../../content/ennemis/Ennemi101.h"
#include "../../content/ennemis/Ennemi102.h"
#include "../../content/ennemis/Ennemi103.h"
#include "../../content/ennemis/Ennemi104.h"
#include "../../content/ennemis/Ennemi105.h"
#include "../../content/ennemis/Ennemi106.h"
#include "../../content/ennemis/Ennemi107.h"
#include "../../content/ennemis/Ennemi108.h"
#include "../../content/ennemis/Ennemi109.h"
#include "../../content/ennemis/Ennemi110.h"
#include "../../content/ennemis/Ennemi111.h"
#include "../../content/ennemis/Ennemi112.h"
#include "../../content/ennemis/Ennemi113.h"
#include "../../content/ennemis/Ennemi115.h"
#include "../../content/ennemis/Ennemi116.h"
#include "../../content/ennemis/Ennemi117.h"
#include "../../content/ennemis/Ennemi118.h"
#include "../../content/ennemis/Ennemi119.h"
#include "../../content/ennemis/Ennemi120.h"
#include "../../content/ennemis/Ennemi121.h"
#include "../../content/ennemis/Ennemi123.h"
#include "../../content/ennemis/Ennemi126.h"
#include "../../content/ennemis/Ennemi127.h"
#include "../../content/ennemis/Ennemi128.h"
#include "../../content/ennemis/Ennemi129.h"
#include "../../content/ennemis/Ennemi130.h"
#include "../../content/ennemis/Ennemi131.h"
#include "../../content/ennemis/Ennemi132.h"
#include "../../content/ennemis/Ennemi133.h"
#include "../../content/ennemis/Ennemi134.h"
#include "../../content/ennemis/Ennemi135.h"
#include "../../content/ennemis/Ennemi136.h"
#include "../../content/ennemis/Ennemi137.h"
#include "../../content/ennemis/Ennemi138.h"
#include "../../content/ennemis/Ennemi139.h"
#include "../../content/ennemis/Ennemi140.h"

Monsters::Monsters() : page(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    for (int i = 0; i < 12; i++) {
        texts[i] = 0;
    }
    for (int i = 0; i < NB_MONSTERS; i++) {
        ennemis[i] = 0;
    }
    pnj = 0;
}

Monsters::~Monsters() {
    ResourceManager::getInstance()->free(image);
    for (int i = 0; i < 12; i++) {
        delete texts[i];
    }
    for (int i = 0; i < NB_MONSTERS; i++) {
        delete ennemis[i];
    }
    delete pnj;
}

void Monsters::init() {
    page = 0;

    for (int i = 0; i < 12; i++) {
        delete texts[i];
    }

    for (int i = 0; i < 12; i++) {
        texts[i] = TextManager::getInstance()->getText(1692 + i);
    }
    initPage();
}

void Monsters::initPage() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (page) {
        case 0 :
            if (scene->getMonsters(4) && !ennemis[4]) ennemis[4] = (Ennemi*)(new Ennemi004(152 + 8, 8 + 7));
            if (scene->getMonsters(53) && !ennemis[53]) ennemis[53] = (Ennemi*)(new Ennemi053(208 + 8, 8 + 8));
            if (scene->getMonsters(54) && !ennemis[54]) ennemis[54] = (Ennemi*)(new Ennemi054(264 + 8, 8 + 8, S));
            if (scene->getMonsters(27) && !ennemis[27]) ennemis[27] = (Ennemi*)(new Ennemi027(16 + 16, 48 + 16));
            if (scene->getMonsters(10) && !ennemis[10]) ennemis[10] = (Ennemi*)(new Ennemi010(96 + 16, 48 + 16));
            if (scene->getMonsters(9) && !ennemis[9]) ennemis[9] = (Ennemi*)(new Ennemi009(176 + 16, 48 + 12));
            if (scene->getMonsters(8) && !ennemis[8]) ennemis[8] = (Ennemi*)(new Ennemi008(256 + 16, 48 + 12));
            if (scene->getMonsters(12) && !ennemis[12]) ennemis[12] = (Ennemi*)(new Ennemi012(16 + 17, 112 + 16));
            if (scene->getMonsters(6) && !ennemis[6]) ennemis[6] = (Ennemi*)(new Ennemi006(96 + 16, 112 + 2));
            if (scene->getMonsters(5) && !ennemis[5]) ennemis[5] = (Ennemi*)(new Ennemi005(176 + 16, 112 + 10));
            if (scene->getMonsters(1) && !ennemis[1]) ennemis[1] = (Ennemi*)(new Ennemi001(256 + 16, 112 + 11));
            if (scene->getMonsters(22) && !ennemis[22]) ennemis[22] = (Ennemi*)(new Ennemi022(16 + 16, 176 + 12));
            if (scene->getMonsters(3) && !ennemis[3]) ennemis[3] = (Ennemi*)(new Ennemi003(96 + 10, 176 + 16));
            if (scene->getMonsters(13) && !ennemis[13]) ennemis[13] = (Ennemi*)(new Ennemi013(176 + 16, 176 + 16));
            if (scene->getMonsters(14) && !ennemis[14]) ennemis[14] = (Ennemi*)(new Ennemi014(252 + 8, 176 + 16));
            break;
        case 1 :
            if (scene->getMonsters(18) && !ennemis[18]) ennemis[18] = (Ennemi*)(new Ennemi018(152 + 8, 8 + 9));
            if (scene->getMonsters(121) && !ennemis[121]) ennemis[121] = (Ennemi*)(new Ennemi121(208 + 8, 8 + 8));
            if (scene->getMonsters(7) && !ennemis[7]) ennemis[7] = (Ennemi*)(new Ennemi007(264 + 8, 8 + 8));
            if (scene->getMonsters(23) && !ennemis[23]) ennemis[23] = (Ennemi*)(new Ennemi023(16 + 11, 48 + 16));
            if (scene->getMonsters(25) && !ennemis[25]) ennemis[25] = (Ennemi*)(new Ennemi025(96 + 10, 48 + 9));
            if (scene->getMonsters(16) && !ennemis[16]) ennemis[16] = (Ennemi*)(new Ennemi016(176 + 16, 48 + 12));
            if (scene->getMonsters(29) && !ennemis[29]) ennemis[29] = (Ennemi*)(new Ennemi029(256 + 16, 48 + 11));
            if (scene->getMonsters(19) && !ennemis[19]) ennemis[19] = (Ennemi*)(new Ennemi019(16 + 8, 112 + 8));
            if (scene->getMonsters(28) && !ennemis[28]) ennemis[28] = (Ennemi*)(new Ennemi028(112 + 8, 112 + 4));
            if (scene->getMonsters(40) && !ennemis[40]) ennemis[40] = (Ennemi*)(new Ennemi040(176 + 5, 112 + 11));
            if (scene->getMonsters(24) && !ennemis[24]) ennemis[24] = (Ennemi*)(new Ennemi024(256 + 8, 112 + 8, false));
            if (scene->getMonsters(35) && !ennemis[35]) ennemis[35] = (Ennemi*)(new Ennemi035(16 + 8, 176 + 8));
            if (scene->getMonsters(43) && !ennemis[43]) ennemis[43] = (Ennemi*)(new Ennemi043(96 + 8, 176 + 8));
            break;
        case 2 :
            if (scene->getMonsters(91) && !ennemis[91]) ennemis[91] = (Ennemi*)(new Ennemi091(16 + 13, 48 + 16));
            if (scene->getMonsters(93) && !ennemis[93]) ennemis[93] = (Ennemi*)(new Ennemi093(88 + 8, 48 + 8));
            if (scene->getMonsters(95) && !ennemis[95]) ennemis[95] = (Ennemi*)(new Ennemi095(176 + 14, 8 + 12));
            if (scene->getMonsters(104) && !ennemis[104]) ennemis[104] = (Ennemi*)(new Ennemi104(256 + 8, 8 + 9));
            if (scene->getMonsters(105) && !ennemis[105]) ennemis[105] = (Ennemi*)(new Ennemi105(16 + 8, 128 + 6));
            if (scene->getMonsters(94) && !ennemis[94]) ennemis[94] = (Ennemi*)(new Ennemi094(152 + 8, 160 + 8));
            if (scene->getMonsters(97) && !ennemis[97]) ennemis[97] = (Ennemi*)(new Ennemi097(240 + 5, 152 + 5));
            if (scene->getMonsters(92) && !ennemis[92]) ennemis[92] = (Ennemi*)(new Ennemi092(160 + 11, 72 + 6));
            break;
        case 3 :
            if (scene->getMonsters(84) && !ennemis[84]) ennemis[84] = (Ennemi*)(new Ennemi084(152 + 8, 8 + 9, S));
            if (scene->getMonsters(56) && !ennemis[56]) ennemis[56] = (Ennemi*)(new Ennemi056(208 + 9, 8 + 8));
            if (scene->getMonsters(86) && !ennemis[86]) ennemis[86] = (Ennemi*)(new Ennemi086(264 + 8, 8 + 8));
            if (scene->getMonsters(32) && !ennemis[32]) ennemis[32] = (Ennemi*)(new Ennemi032(16 + 16, 48 + 11));
            if (scene->getMonsters(11) && !ennemis[11]) ennemis[11] = (Ennemi*)(new Ennemi011(96 + 16, 48 + 14, true));
            if (scene->getMonsters(55) && !ennemis[55]) ennemis[55] = (Ennemi*)(new Ennemi055(176 + 13, 48 + 9));
            if (scene->getMonsters(37) && !ennemis[37]) ennemis[37] = (Ennemi*)(new Ennemi037(256 + 16, 48 + 11));
            if (scene->getMonsters(15) && !ennemis[15]) ennemis[15] = (Ennemi*)(new Ennemi015(16 + 12, 112 + 6));
            if (scene->getMonsters(44) && !ennemis[44]) ennemis[44] = (Ennemi*)(new Ennemi044(96 + 13, 112 + 9));
            if (scene->getMonsters(26) && !ennemis[26]) ennemis[26] = (Ennemi*)(new Ennemi026(176 + 17, 112 + 14));
            if (scene->getMonsters(101) && !ennemis[101]) ennemis[101] = (Ennemi*)(new Ennemi101(256 + 8, 112 + 8, N));
            if (scene->getMonsters(62) && !ennemis[62]) ennemis[62] = (Ennemi*)(new Ennemi062(16 + 12, 176 + 5, false));
            if (scene->getMonsters(64) && !ennemis[64]) ennemis[64] = (Ennemi*)(new Ennemi064(96 + 4, 176 + 6));
            break;
        case 4 :
            if (scene->getMonsters(98) && !ennemis[98]) ennemis[98] = (Ennemi*)(new Ennemi098(16 + 8, 48 + 8));
            if (scene->getMonsters(102) && !ennemis[102]) ennemis[102] = (Ennemi*)(new Ennemi102(104 + 12, 48 + 11));
            if (scene->getMonsters(99) && !ennemis[99]) ennemis[99] = (Ennemi*)(new Ennemi099(184 + 14, 64 + 17));
            if (scene->getMonsters(103) && !ennemis[103]) ennemis[103] = (Ennemi*)(new Ennemi103(32 + 7, 112 + 7));
            break;
        case 5 :
            if (scene->getMonsters(112) && !ennemis[112]) ennemis[112] = (Ennemi*)(new Ennemi112(152 + 8, 8 + 8));
            if (scene->getMonsters(118) && !ennemis[118]) ennemis[118] = (Ennemi*)(new Ennemi118(208 + 8, 8 + 8));
            if (scene->getMonsters(77) && !ennemis[77]) ennemis[77] = (Ennemi*)(new Ennemi077(16 + 3, 48 + 9));
            if (scene->getMonsters(42) && !ennemis[42]) ennemis[42] = (Ennemi*)(new Ennemi042(96 + 11, 48 + 14));
            if (scene->getMonsters(41) && !ennemis[41]) ennemis[41] = (Ennemi*)(new Ennemi041(176 + 16, 48 + 12));
            if (scene->getMonsters(87) && !ennemis[87]) ennemis[87] = (Ennemi*)(new Ennemi087(256 - 5, 48 + 12));
            if (scene->getMonsters(30) && !ennemis[30]) ennemis[30] = (Ennemi*)(new Ennemi030(16 + 16, 112 + 12));
            if (scene->getMonsters(33) && !ennemis[33]) ennemis[33] = (Ennemi*)(new Ennemi033(96 + 13, 112 + 12));
            if (scene->getMonsters(34) && !ennemis[34]) ennemis[34] = (Ennemi*)(new Ennemi034(176 + 12, 112 + 12));
            if (scene->getMonsters(2) && !ennemis[2]) ennemis[2] = (Ennemi*)(new Ennemi002(256 + 14, 112 + 12));
            if (scene->getMonsters(72) && !ennemis[72]) ennemis[72] = (Ennemi*)(new Ennemi072(16 + 16, 176 + 11));
            if (scene->getMonsters(38) && !ennemis[38]) ennemis[38] = (Ennemi*)(new Ennemi038(96 + 13, 176 + 12));
            if (scene->getMonsters(39) && !ennemis[39]) ennemis[39] = (Ennemi*)(new Ennemi039(176 + 12, 176 + 12));
            if (scene->getMonsters(119) && !ennemis[119]) ennemis[119] = (Ennemi*)(new Ennemi119(256 + 13, 176 + 9));
            break;
        case 6 :
            if (scene->getMonsters(108) && !ennemis[108]) ennemis[108] = (Ennemi*)(new Ennemi108(16 + 3, 48 + 8));
            if (scene->getMonsters(110) && !ennemis[110]) ennemis[110] = (Ennemi*)(new Ennemi110(80 + 10, 48 + 8));
            if (scene->getMonsters(106) && !ennemis[106]) ennemis[106] = (Ennemi*)(new Ennemi106(152 + 6, 8 + 8));
            if (scene->getMonsters(76) && !ennemis[76]) ennemis[76] = (Ennemi*)(new Ennemi076(224 + 10, 8 + 6));
            if (scene->getMonsters(113) && !ennemis[113]) ennemis[113] = (Ennemi*)(new Ennemi113(16 + 10, 112 + 10));
            if (scene->getMonsters(107) && !ennemis[107]) ennemis[107] = (Ennemi*)(new Ennemi107(208 + 9, 88 + 7));
            if (scene->getMonsters(109) && !ennemis[109]) ennemis[109] = (Ennemi*)(new Ennemi109(80 - 5, 112 + 9));
            if (scene->getMonsters(111) && !ennemis[111]) ennemis[111] = (Ennemi*)(new Ennemi111(224 + 9, 168 + 8));
            break;
        case 7 :
            if (scene->getMonsters(115) && !ennemis[115]) ennemis[115] = (Ennemi*)(new Ennemi115(32 + 8, 64 + 10));
            if (scene->getMonsters(120) && !ennemis[120]) ennemis[120] = (Ennemi*)(new Ennemi120(208 + 8, 64 + 8));
            if (scene->getMonsters(89) && !ennemis[89]) ennemis[89] = (Ennemi*)(new Ennemi089(208 + 14, 127 + 11));
            break;
        case 8 :
            if (scene->getMonsters(46) && !ennemis[46]) ennemis[46] = (Ennemi*)(new Ennemi046(16 + 13, 48 + 9));
            if (scene->getMonsters(47) && !ennemis[47]) ennemis[47] = (Ennemi*)(new Ennemi047(96 + 13, 48 + 9));
            if (scene->getMonsters(48) && !ennemis[48]) ennemis[48] = (Ennemi*)(new Ennemi048(176 + 13, 48 + 9));
            if (scene->getMonsters(31) && !ennemis[31]) ennemis[31] = (Ennemi*)(new Ennemi031(16 + 8, 112 + 8));
            if (scene->getMonsters(50) && !ennemis[50]) ennemis[50] = (Ennemi*)(new Ennemi050(96 + 8, 112 + 6));
            break;
        case 9 :
            if (scene->getMonsters(123) && !ennemis[123]) ennemis[123] = (Ennemi*)(new Ennemi123(16 + 13, 48 + 9));
            if (scene->getMonsters(126) && !ennemis[126]) ennemis[126] = (Ennemi*)(new Ennemi126(96 + 16, 48 + 16));
            if (scene->getMonsters(127) && !ennemis[127]) ennemis[127] = (Ennemi*)(new Ennemi127(16 + 9, 112 + 8));
            if (scene->getMonsters(128) && !ennemis[128]) ennemis[128] = (Ennemi*)(new Ennemi128(144 + 6, 112 - 3));
            break;
        case 10 :
            if (scene->getMonsters(129) && !ennemis[129]) ennemis[129] = (Ennemi*)(new Ennemi129(16 + 16, 48 + 2));
            if (scene->getMonsters(130) && !ennemis[130]) ennemis[130] = (Ennemi*)(new Ennemi130(96 + 12, 48 + 6));
            if (scene->getMonsters(131) && !ennemis[131]) ennemis[131] = (Ennemi*)(new Ennemi131(176 + 16, 48 + 12));
            if (scene->getMonsters(139) && !ennemis[139]) ennemis[139] = (Ennemi*)(new Ennemi139(256 + 13, 32 + 16));
            if (scene->getMonsters(133) && !ennemis[133]) ennemis[133] = (Ennemi*)(new Ennemi133(16 + 12, 112 + 12));
            if (scene->getMonsters(134) && !ennemis[134]) ennemis[134] = (Ennemi*)(new Ennemi134(96 + 13, 112 + 9));
            if (scene->getMonsters(135) && !ennemis[135]) ennemis[135] = (Ennemi*)(new Ennemi135(176 + 12, 112 + 5));
            if (scene->getMonsters(136) && !ennemis[136]) ennemis[136] = (Ennemi*)(new Ennemi136(256 + 4, 112 + 6));
            if (scene->getMonsters(137) && !ennemis[137]) ennemis[137] = (Ennemi*)(new Ennemi137(16 + 16, 176 + 11));
            if (scene->getMonsters(138) && !ennemis[138]) ennemis[138] = (Ennemi*)(new Ennemi138(96 + 3, 176 + 9));
            if (scene->getMonsters(132) && !ennemis[132]) ennemis[132] = (Ennemi*)(new Ennemi132(176 + 16, 176 + 11));
            if (scene->getMonsters(140) && !ennemis[140]) ennemis[140] = (Ennemi*)(new Ennemi140(256 + 16, 176 + 16));
            break;
        case 11 :
            if (scene->getMonsters(141) && !pnj) pnj = new Pnj(136 + 16, 96 + 12, 8, 1654);
            break;
    }
}

void Monsters::cadre(int x, int y, int w, int h, int type) {

    // center
    for (int j = y + 16; j < y + h - 16; j += 16) {
        for (int i = x + 16; i < x + w - 16; i += 16) {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    //top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16) {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    //left and right
    for (int j = y + 16; j < y + h - 16; j += 16) {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    //top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    //top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    //bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    //bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);


    // monsters

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->getMonsters(type)) {
        if (type < 141) {
            ennemis[type]->drawEncyclopedie();
        } else {
            pnj->draw(0, 0);
        }
    }

}

void Monsters::handleActions(Action* action) {
    if (action->isAction(MONSTERS)) {
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
    int old = page;
    if (action->isAction(PUSH_LEFT)) {
        page = getPreviousPageFrom(page);
    } else if (action->isAction(PUSH_RIGHT)) {
        page = getNextPageFrom(page);
    }
    if (page != old) {
        initPage();
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Monsters::draw() {
    int letterSize = TextManager::getInstance()->getWSpace();

    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    // title

    Text* title = texts[page];
    int size = title->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++) {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    title->display(32 + 8 + ((blocs * 16) - size) / 2, 16);

    // monsters

    switch (page) {
        case 0 :
            cadre(152,8,32,32,4);
            cadre(208,8,32,32,53);
            cadre(264,8,32,32,54);
            cadre(16,48,48,48,27);
            cadre(96,48,48,48,10);
            cadre(176,48,48,48,9);
            cadre(256,48,48,48,8);
            cadre(16,112,48,48,12);
            cadre(96,112,48,48,6);
            cadre(176,112,48,48,5);
            cadre(256,112,48,48,1);
            cadre(16,176,48,48,22);
            cadre(96,176,48,48,3);
            cadre(176,176,48,48,13);
            cadre(252,176,56,48,14);
            break; // -> 15
        case 1 :
            cadre(152,8,32,32,18);
            cadre(208,8,32,32,121);
            cadre(264,8,32,32,7);
            cadre(16,48,48,48,23);
            cadre(96,48,48,48,25);
            cadre(176,48,48,48,16);
            cadre(256,48,48,48,29);
            cadre(16,112,80,48,19);
            cadre(96+32-16,112,48,48,28);
            cadre(176,112,64,64,40);
            cadre(256,112,48,64,24);
            cadre(16,176,48,48,35);
            cadre(96,176,48,48,43);
            break; // -> 28
        case 2 :
            cadre(16,48,48,64,91);
            cadre(96-8,48,48,48,93);
            cadre(176,8,48,48,95);
            cadre(256,8,48,48,104);
            cadre(16,128,96,96,105);
            cadre(144+8,160,48,48,94);
            cadre(240,160-8,64,80,97);
            cadre(256-96,112-32-8,144,64,92);
            break; // -> 36
        case 3 :
            cadre(152,8,32,32,84);
            cadre(208,8,32,32,56);
            cadre(264,8,32,32,86);
            cadre(16,48,48,48,32);
            cadre(96,48,48,48,11);
            cadre(176,48,48,48,55);
            cadre(256,48,48,48,37);
            cadre(16,112,48,48,15);
            cadre(96,112,48,48,44);
            cadre(176,112,48,48,26);
            cadre(256,112,48,48,101);
            cadre(16,176,48,48,62);
            cadre(96,176,48,48,64);
            break; // -> 49
        case 4 :
            cadre(16,48,48,48,98);
            cadre(104,48,48,48,102);
            cadre(184,64,96,128,99);
            cadre(32,112,96,96,103);
            break; // -> 53
        case 5 :
            cadre(152,8,32,32,112);
            cadre(208,8,32,32,118);
            cadre(16,48,48,48,77);
            cadre(96,48,48,48,42);
            cadre(176,48,48,48,41);
            cadre(256,48,48,48,87);
            cadre(16,112,48,48,30);
            cadre(96,112,48,48,33);
            cadre(176,112,48,48,34);
            cadre(256,112,48,48,2);
            cadre(16,176,48,48,72);
            cadre(96,176,48,48,38);
            cadre(176,176,48,48,39);
            cadre(256,176,48,48,119);
            break; // -> 67
        case 6 :
            cadre(16,48,48,48,108);
            cadre(96-16,48,48,48,110);
            cadre(160-8,8,48+8,64,106);
            cadre(240-16,8,80,64,76);
            cadre(16,112,48,48,113);
            cadre(240-32,112-16-8,96,64,107);
            cadre(80,112,112,112,109);
            cadre(240-16,176-8,80,64,111);
            break; // -> 75
        case 7 :
            cadre(32,64,144,112,115);
            cadre(176+32,64,48,48,120);
            cadre(176+32,128,48,48,89);
            break; // -> 78
        case 8 :
            cadre(16,48,48,48,46);
            cadre(96,48,48,48,47);
            cadre(176,48,48,48,48);
            cadre(16,112,48,48,31);
            cadre(96,112,64,48,50);
            break; // -> 83
        case 9 :
            cadre(16,48,48,48,123);
            cadre(96,48,48,48,126);
            cadre(16,112,96,80,127);
            cadre(144,112,80,80,128);
            break; // -> 87
        case 10 :
            cadre(16,48,48,48,129);
            cadre(96,48,48,48,130);
            cadre(176,48,48,48,131);
            cadre(256,32,48,64,139);
            cadre(16,112,48,48,133);
            cadre(96,112,48,48,134);
            cadre(176,112,48,48,135);
            cadre(256,112,48,48,136);
            cadre(16,176,48,48,137);
            cadre(96,176,48,48,138);
            cadre(176,176,48,48,132);
            cadre(256,176,48,48,140);
            break; // -> 99
        case 11 :
            cadre(128+8,112-16,48,48,141);
            break; // -> 100
    }
}

int Monsters::getNextPageFrom(int p) {
    int next = p + 1;

    for (int i = 0; i < 12; i ++) {
        if (next > 11) {
            next = 0;
        }
        if (!isPageEmpty(next)) {
            return next;
        }
        next++;
    }

    return p;
}

int Monsters::getPreviousPageFrom(int p) {
    int previous = p - 1;

    for (int i = 0; i < 12; i ++) {
        if (previous < 0) {
            previous = 11;
        }
        if (!isPageEmpty(previous)) {
            return previous;
        }
        previous--;
    }

    return p;
}

bool Monsters::isPageEmpty(int p) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (p) {
        case 0 :
            if (scene->getMonsters(4) || scene->getMonsters(53) || scene->getMonsters(54)
                 || scene->getMonsters(27) || scene->getMonsters(10) || scene->getMonsters(9)
                 || scene->getMonsters(8) || scene->getMonsters(12) || scene->getMonsters(6)
                 || scene->getMonsters(5) || scene->getMonsters(1) || scene->getMonsters(22)
                 || scene->getMonsters(3) || scene->getMonsters(13) || scene->getMonsters(14)) {
                return false;
            }
            break;
        case 1 :
            if (scene->getMonsters(18) || scene->getMonsters(121) || scene->getMonsters(7)
                 || scene->getMonsters(23) || scene->getMonsters(25) || scene->getMonsters(16)
                 || scene->getMonsters(29) || scene->getMonsters(19) || scene->getMonsters(28)
                 || scene->getMonsters(40) || scene->getMonsters(24) || scene->getMonsters(35)
                 || scene->getMonsters(43)) {
                return false;
            }
            break;
        case 2 :
            if (scene->getMonsters(91) || scene->getMonsters(93) || scene->getMonsters(95)
                 || scene->getMonsters(104) || scene->getMonsters(105) || scene->getMonsters(94)
                 || scene->getMonsters(97) || scene->getMonsters(92)) {
                return false;
            }
            break;
        case 3 :
            if (scene->getMonsters(84) || scene->getMonsters(56) || scene->getMonsters(86)
                 || scene->getMonsters(32) || scene->getMonsters(11) || scene->getMonsters(55)
                 || scene->getMonsters(37) || scene->getMonsters(15) || scene->getMonsters(44)
                 || scene->getMonsters(26) || scene->getMonsters(101) || scene->getMonsters(62)
                 || scene->getMonsters(64)) {
                return false;
            }
            break;
        case 4 :
            if (scene->getMonsters(98) || scene->getMonsters(102) || scene->getMonsters(99)
                 || scene->getMonsters(103)) {
                return false;
            }
            break;
        case 5 :
            if (scene->getMonsters(112) || scene->getMonsters(118) || scene->getMonsters(77)
                 || scene->getMonsters(42) || scene->getMonsters(41) || scene->getMonsters(87)
                 || scene->getMonsters(30) || scene->getMonsters(33) || scene->getMonsters(34)
                 || scene->getMonsters(2) || scene->getMonsters(72) || scene->getMonsters(38)
                 || scene->getMonsters(39) || scene->getMonsters(119)) {
                return false;
            }
            break;
        case 6 :
            if (scene->getMonsters(108) || scene->getMonsters(110) || scene->getMonsters(106)
                 || scene->getMonsters(76) || scene->getMonsters(113) || scene->getMonsters(107)
                 || scene->getMonsters(109) || scene->getMonsters(111)) {
                return false;
            }
            break;
        case 7 :
            if (scene->getMonsters(115) || scene->getMonsters(120) || scene->getMonsters(89)) {
                return false;
            }
            break;
        case 8 :
            if (scene->getMonsters(46) || scene->getMonsters(47) || scene->getMonsters(48)
                 || scene->getMonsters(31) || scene->getMonsters(50)) {
                return false;
            }
            break;
        case 9 :
            if (scene->getMonsters(123) || scene->getMonsters(126) || scene->getMonsters(127)
                 || scene->getMonsters(128)) {
                return false;
            }
            break;
        case 10 :
            if (scene->getMonsters(129) || scene->getMonsters(130) || scene->getMonsters(131)
                 || scene->getMonsters(139) || scene->getMonsters(133) || scene->getMonsters(134)
                 || scene->getMonsters(135) || scene->getMonsters(136) || scene->getMonsters(137)
                 || scene->getMonsters(138) || scene->getMonsters(132) || scene->getMonsters(140)) {
                return false;
            }
            break;
        case 11 :
            if (scene->getMonsters(141)) {
                return false;
            }
            break;
    }
    return true;
}
