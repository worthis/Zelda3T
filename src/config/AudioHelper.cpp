#include "AudioHelper.h"

AudioHelper::AudioHelper() : sounds(0) {
}

AudioHelper::~AudioHelper() {
    if (sounds != 0) deleteSounds();
}

string AudioHelper::getMusicName(int id) {
    switch (id) {
        case 0 : return "data/musics/Titre.mid";
        case 1 : return "data/musics/Fee.mid";
        case 2 : return "data/musics/Opening.mid";
        case 3 : return "data/musics/Mort.mid";
        case 4 : return "data/musics/Foret.mid";
        case 5 : return "data/musics/Plaine.mid";
        case 6 : return "data/musics/villageest.mid";
        case 7 : return "data/musics/Vallee.mid";
        case 8 : return "data/musics/Desert.mid";
        case 9 : return "data/musics/Lac.mid";
        case 10 : return "data/musics/Cite.mid";
        case 11 : return "data/musics/Chateau.mid";
        case 12 : return "data/musics/PlaineO.mid";
        case 13 : return "data/musics/Marais.mid";
        case 14 : return "data/musics/Ombre.mid";
        case 15 : return "data/musics/Secret.mid";
        case 16 : return "data/musics/Mido.mid";
        case 17 : return "data/musics/Mont.mid";
        case 18 : return "data/musics/Boss.mid";
        case 19 : return "data/musics/Donjon1.mid";
        case 20 : return "data/musics/Epee.mid";
        case 21 : return "data/musics/Cave.mid";
        case 22 : return "data/musics/Manoir.mid";
        case 23 : return "data/musics/BossM.mid";
        case 24 : return "data/musics/Ordinn.mid";
        case 25 : return "data/musics/Colisee.mid";
        case 26 : return "data/musics/Lanelle.mid";
        case 27 : return "data/musics/DFinal.mid";
        case 28 : return "data/musics/BossF.mid";
        case 29 : return "data/musics/DDesert.mid";
        case 30 : return "data/musics/Glace.mid";
        case 31 : return "data/musics/Farore.mid";
        case 32 : return "data/musics/Area81.mid";
        case 33 : return "data/musics/Xanto.mid";
        case 34 : return "data/musics/OniLink.mid";
        case 35 : return "data/musics/DSecret.mid";
        case 36 : return "data/musics/TourD.mid";
        case 37 : return "data/musics/End.mid";
        case 38 : return "data/musics/Pit.mid";
        case 39 : return "data/musics/Maison.mid";
        case 40 : return "data/musics/Jeu.mid";
        case 41 : return "data/musics/Bar.mid";
        case 42 : return "data/musics/Maire.mid";
        case 43 : return "data/musics/Magasin.mid";
        case 44 : return "data/musics/Potion.mid";
        case 45 : return "data/musics/Triste.mid";
        case 46 : return "data/musics/PlaineP.mid";
        case 47 : return "data/musics/Nuit.mid";
        case 48 : return "data/musics/Probleme.mid";
        case 49 : return "data/musics/VilleF.mid";
        case 50 : return "data/musics/VilleCP.mid";
        case 51 : return "data/musics/TerreS.mid";
        case 52 : return "data/musics/BoisPerdusF.mid";
        case 53 : return "data/musics/BoisPerdus.mid";
        case 54 : return "data/musics/Cascades.mid";
        case 55 : return "data/musics/Cimetiere.mid";
        case 56 : return "data/musics/CimetiereF.mid";
        case 57 : return "data/musics/CimetiereP.mid";
        case 58 : return "data/musics/VillageM.mid";
        case 59 : return "data/musics/VillageMF.mid";
        case 60 : return "data/musics/VillageMP.mid";
        case 61 : return "data/musics/LacF.mid";
        case 62 : return "data/musics/LacP.mid";
        case 63 : return "data/musics/DesertF.mid";
        case 64 : return "data/musics/DesertP.mid";
        case 65 : return "data/musics/VillageO.mid";
        case 66 : return "data/musics/VillageOF.mid";
        case 67 : return "data/musics/Cocorico.mid";
        case 68 : return "data/musics/MontF.mid";
        case 69 : return "data/musics/MontP.mid";
        case 70 : return "data/musics/Home.mid";
        case 71 : return "data/musics/Cafe.mid";
        case 72 : return "data/musics/Sages.mid";
        case 73 : return "data/musics/Opera.mid";
        case 74 : return "data/musics/Prison.mid";
        case 75 : return "data/musics/ChateauF.mid";
        case 76 : return "data/musics/Courage.mid";
        case 77 : return "data/musics/Harpie.mid";
        case 78 : return "data/musics/Sagesse.mid";
        case 79 : return "data/musics/Crabe.mid";
        case 80 : return "data/musics/Force.mid";
        case 81 : return "data/musics/Imp.mid";
        case 82 : return "data/musics/Masamune.mid";
        case 83 : return "data/musics/Abysses.mid";
        case 84 : return "data/musics/ZoraS.mid";
        case 85 : return "data/musics/Marlag.mid";
        case 86 : return "data/musics/PyramideF.mid";
        case 87 : return "data/musics/Fantomas.mid";
        case 88 : return "data/musics/Vampire.mid";
        case 89 : return "data/musics/PyramideP.mid";
        case 90 : return "data/musics/Araignee.mid";
        case 91 : return "data/musics/Air.mid";
        case 92 : return "data/musics/Plumes.mid";
        case 93 : return "data/musics/Garuda.mid";
        case 94 : return "data/musics/Heckran.mid";
        case 95 : return "data/musics/Feu.mid";
        case 96 : return "data/musics/Sun.mid";
        case 97 : return "data/musics/Orcus.mid";
        case 98 : return "data/musics/Agahnim.mid";
        case 99 : return "data/musics/AgahnimFinal.mid";
        case 100 : return "data/musics/GanondorfFinal.mid";
        case 101 : return "data/musics/Zelda.mid";
        case 102 : return "data/musics/Casino.mid";
        case 103 : return "data/musics/Quizz.mid";
        case 104 : return "data/musics/Gemme.mid";
        case 105 : return "data/musics/DestinationF.mid";
        case 106 : return "data/musics/FinalBattle.mid";
        case 107 : return "data/musics/Frog.mid";
        case 108 : return "data/musics/Terreur.mid";
        default : return "";
    }
}

WSound* AudioHelper::getSound(int id) {
    return sounds[id];
}

void AudioHelper::loadSounds() {
    sounds = new WSound*[TS_NB_MAX];
    sounds[TS_MENU1] = new WSound("data/sounds/menu/menu1.wav");
    sounds[TS_MENU2] = new WSound("data/sounds/menu/menu2.wav");
    sounds[TS_MENU3] = new WSound("data/sounds/menu/menu3.wav");

    sounds[TS_STEP_GRASS1] = new WSound("data/sounds/steps/Steps_Grass1.wav");
    sounds[TS_STEP_GRASS2] = new WSound("data/sounds/steps/Steps_Grass2.wav");
    sounds[TS_STEP_DIRT1] = new WSound("data/sounds/steps/Steps_Dirt1.wav");
    sounds[TS_STEP_DIRT2] = new WSound("data/sounds/steps/Steps_Dirt2.wav");
    sounds[TS_STEP_TALLGRASS1] = new WSound("data/sounds/steps/Steps_TallGrass1.wav");
    sounds[TS_STEP_TALLGRASS2] = new WSound("data/sounds/steps/Steps_TallGrass2.wav");
    sounds[TS_STEP_ICE1] = new WSound("data/sounds/steps/Steps_Ice1.wav");
    sounds[TS_STEP_ICE2] = new WSound("data/sounds/steps/Steps_Ice2.wav");
    sounds[TS_STEP_WATER1] = new WSound("data/sounds/steps/Steps_Water1.wav");
    sounds[TS_STEP_WATER2] = new WSound("data/sounds/steps/Steps_Water2.wav");
    sounds[TS_STEP_SAND1] = new WSound("data/sounds/steps/Steps_Sand1.wav");
    sounds[TS_STEP_SAND2] = new WSound("data/sounds/steps/Steps_Sand2.wav");
    sounds[TS_STEP_STONE1] = new WSound("data/sounds/steps/Steps_Stone1.wav");
    sounds[TS_STEP_STONE2] = new WSound("data/sounds/steps/Steps_Stone2.wav");
    sounds[TS_STEP_WOOD1] = new WSound("data/sounds/steps/Steps_Wood1.wav");
    sounds[TS_STEP_WOOD2] = new WSound("data/sounds/steps/Steps_Wood2.wav");
    sounds[TS_STEP_CARPET1] = new WSound("data/sounds/steps/Steps_Carpet1.wav");
    sounds[TS_STEP_CARPET2] = new WSound("data/sounds/steps/Steps_Carpet2.wav");
    sounds[TS_STEP_SNOW1] = new WSound("data/sounds/steps/Steps_Snow1.wav");
    sounds[TS_STEP_SNOW2] = new WSound("data/sounds/steps/Steps_Snow2.wav");


    sounds[TS_JUMP] = new WSound("data/sounds/link/jump.wav");
    sounds[TS_NAGE] = new WSound("data/sounds/link/nage.wav");
    sounds[TS_ATTACK1] = new WSound("data/sounds/link/attack1.wav");
    sounds[TS_ATTACK2] = new WSound("data/sounds/link/attack2.wav");
    sounds[TS_ATTACK3] = new WSound("data/sounds/link/attack3.wav");
    sounds[TS_ATTACK4] = new WSound("data/sounds/link/attack4.wav");
    sounds[TS_HURT] = new WSound("data/sounds/link/hurt.wav");
    sounds[TS_DANGER] = new WSound("data/sounds/link/danger.wav");
    sounds[TS_HEART] = new WSound("data/sounds/link/heart.wav");
    sounds[TS_RUPEE] = new WSound("data/sounds/link/rupee.wav");
    sounds[TS_SPIN] = new WSound("data/sounds/link/spin.wav");
    sounds[TS_ITEM] = new WSound("data/sounds/link/item.wav");
    sounds[TS_FALL] = new WSound("data/sounds/link/fall.wav");
    sounds[TS_MAGICCHARGE] = new WSound("data/sounds/link/charge.wav");
    sounds[TS_HAPPY] = new WSound("data/sounds/link/happy.wav");
    sounds[TS_SHOOT] = new WSound("data/sounds/link/shoot.wav");
    sounds[TS_THROW] = new WSound("data/sounds/link/lance.wav");
    sounds[TS_PORTE] = new WSound("data/sounds/link/porte.wav");
    sounds[TS_GRAPPIN] = new WSound("data/sounds/link/hookshot.wav");
    sounds[TS_MAGIC] = new WSound("data/sounds/link/magic.wav");
    sounds[TS_MARTEAU] = new WSound("data/sounds/link/hammer.wav");
    sounds[TS_PLOT] = new WSound("data/sounds/link/plot.wav");
    sounds[TS_CAPE_ON] = new WSound("data/sounds/link/capeon.wav");
    sounds[TS_CAPE_OFF] = new WSound("data/sounds/link/capeoff.wav");
    sounds[TS_CANE] = new WSound("data/sounds/link/cane.wav");
    sounds[TS_BYRNA] = new WSound("data/sounds/link/byrna.wav");
    sounds[TS_SHOCK] = new WSound("data/sounds/link/shock.wav");
    sounds[TS_BOOMERANG] = new WSound("data/sounds/link/boomerang.wav");
    sounds[TS_BAGUETTE_FEU] = new WSound("data/sounds/link/baguetteFeu.wav");
    sounds[TS_BAGUETTE_GLACE] = new WSound("data/sounds/link/baguetteGlace.wav");


    sounds[TS_NAVY_HEY] = new WSound("data/sounds/link/hey.wav");
    sounds[TS_NAVY_LISTEN] = new WSound("data/sounds/link/listen.wav");
    sounds[TS_NAVY_HELLO] = new WSound("data/sounds/link/hello.wav");
    sounds[TS_NAVY_LOOK] = new WSound("data/sounds/link/look.wav");

    sounds[TS_SONG_1] = new WSound("data/sounds/ocarina/envol.wav");
    sounds[TS_SONG_2] = new WSound("data/sounds/ocarina/inverse.wav");
    sounds[TS_SONG_3] = new WSound("data/sounds/ocarina/accelere.wav");

    sounds[TS_SWORD] = new WSound("data/sounds/items/sword.wav");
    sounds[TS_SWORDCHARGING] = new WSound("data/sounds/items/SwordCharging.wav");

    sounds[TS_HITENNEMY] = new WSound("data/sounds/others/hitenemy.wav");
    sounds[TS_KILLENNEMY] = new WSound("data/sounds/others/killenemy.wav");
    sounds[TS_PLOUF] = new WSound("data/sounds/others/plouf.wav");
    sounds[TS_SOL] = new WSound("data/sounds/others/stamp.wav");
    sounds[TS_BOOM] = new WSound("data/sounds/others/bomb.wav");
    sounds[TS_TOMBE] = new WSound("data/sounds/others/tombe.wav");
    sounds[TS_BURN] = new WSound("data/sounds/others/burn.wav");
    sounds[TS_BUISSON] = new WSound("data/sounds/others/buisson.wav");
    sounds[TS_DOOR] = new WSound("data/sounds/others/door.wav");
    sounds[TS_SURPRISE] = new WSound("data/sounds/others/surprise.wav");
    sounds[TS_ERROR] = new WSound("data/sounds/others/error.wav");
    sounds[TS_ESCALIERS_DOWN] = new WSound("data/sounds/others/descend.wav");
    sounds[TS_ESCALIERS_UP] = new WSound("data/sounds/others/monte.wav");
    sounds[TS_TELEPORT] = new WSound("data/sounds/others/timewarp.wav");
    sounds[TS_SPLASH] = new WSound("data/sounds/others/splash.wav");

    sounds[TS_PUSH] = new WSound("data/sounds/objects/push.wav");
    sounds[TS_BREAK] = new WSound("data/sounds/objects/casse.wav");
    sounds[TS_COFFRE] = new WSound("data/sounds/objects/coffre.wav");
    sounds[TS_POULE] = new WSound("data/sounds/objects/poule.wav");
    sounds[TS_PICS] = new WSound("data/sounds/objects/pics.wav");

    sounds[TS_TEXT] = new WSound("data/sounds/texts/text.wav");
    sounds[TS_TEXTNEXT] = new WSound("data/sounds/texts/textnext.wav");
    sounds[TS_TEXTEND] = new WSound("data/sounds/texts/textend.wav");


}

void AudioHelper::deleteSounds() {
    if (sounds != 0) {
        for (int i = 0; i < TS_NB_MAX; i++) {
            delete sounds[i];
        }
        delete[] sounds;
    }
}

int AudioHelper::getNbSounds() {
    return TS_NB_MAX;
}
