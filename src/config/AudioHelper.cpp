#include "AudioHelper.h"

AudioHelper::AudioHelper() : sounds(0) {
}

AudioHelper::~AudioHelper() {
    if (sounds != 0) deleteSounds();
}

string AudioHelper::getMusicName(int id) {
    switch (id) {
        case 0 : return "data/musics/Titre.mp3";
        case 1 : return "data/musics/Fee.mp3";
        case 2 : return "data/musics/Opening.mp3";
        case 3 : return "data/musics/Mort.mp3";
        case 4 : return "data/musics/Foret.mp3";
        case 5 : return "data/musics/Plaine.mp3";
        case 6 : return "data/musics/villageest.mp3";
        case 7 : return "data/musics/Vallee.mp3";
        case 8 : return "data/musics/Desert.mp3";
        case 9 : return "data/musics/Lac.mp3";
        case 10 : return "data/musics/Cite.mp3";
        case 11 : return "data/musics/Chateau.mp3";
        case 12 : return "data/musics/PlaineO.mp3";
        case 13 : return "data/musics/Marais.mp3";
        case 14 : return "data/musics/Ombre.mp3";
        case 15 : return "data/musics/Secret.mp3";
        case 16 : return "data/musics/Mido.mp3";
        case 17 : return "data/musics/Mont.mp3";
        case 18 : return "data/musics/Boss.mp3";
        case 19 : return "data/musics/Donjon1.mp3";
        case 20 : return "data/musics/Epee.mp3";
        case 21 : return "data/musics/Cave.mp3";
        case 22 : return "data/musics/Manoir.mp3";
        case 23 : return "data/musics/BossM.mp3";
        case 24 : return "data/musics/Ordinn.mp3";
        case 25 : return "data/musics/Colisee.mp3";
        case 26 : return "data/musics/Lanelle.mp3";
        case 27 : return "data/musics/DFinal.mp3";
        case 28 : return "data/musics/BossF.mp3";
        case 29 : return "data/musics/DDesert.mp3";
        case 30 : return "data/musics/Glace.mp3";
        case 31 : return "data/musics/Farore.mp3";
        case 32 : return "data/musics/Area81.mp3";
        case 33 : return "data/musics/Xanto.mp3";
        case 34 : return "data/musics/OniLink.mp3";
        case 35 : return "data/musics/DSecret.mp3";
        case 36 : return "data/musics/TourD.mp3";
        case 37 : return "data/musics/End.mp3";
        case 38 : return "data/musics/Pit.mp3";
        case 39 : return "data/musics/Maison.mp3";
        case 40 : return "data/musics/Jeu.mp3";
        case 41 : return "data/musics/Bar.mp3";
        case 42 : return "data/musics/Maire.mp3";
        case 43 : return "data/musics/Magasin.mp3";
        case 44 : return "data/musics/Potion.mp3";
        case 45 : return "data/musics/Triste.mp3";
        case 46 : return "data/musics/PlaineP.mp3";
        case 47 : return "data/musics/Nuit.mp3";
        case 48 : return "data/musics/Probleme.mp3";
        case 49 : return "data/musics/VilleF.mp3";
        case 50 : return "data/musics/VilleCP.mp3";
        case 51 : return "data/musics/TerreS.mp3";
        case 52 : return "data/musics/BoisPerdusF.mp3";
        case 53 : return "data/musics/BoisPerdus.mp3";
        case 54 : return "data/musics/Cascades.mp3";
        case 55 : return "data/musics/Cimetiere.mp3";
        case 56 : return "data/musics/CimetiereF.mp3";
        case 57 : return "data/musics/CimetiereP.mp3";
        case 58 : return "data/musics/VillageM.mp3";
        case 59 : return "data/musics/VillageMF.mp3";
        case 60 : return "data/musics/VillageMP.mp3";
        case 61 : return "data/musics/LacF.mp3";
        case 62 : return "data/musics/LacP.mp3";
        case 63 : return "data/musics/DesertF.mp3";
        case 64 : return "data/musics/DesertP.mp3";
        case 65 : return "data/musics/VillageO.mp3";
        case 66 : return "data/musics/VillageOF.mp3";
        case 67 : return "data/musics/Cocorico.mp3";
        case 68 : return "data/musics/MontF.mp3";
        case 69 : return "data/musics/MontP.mp3";
        case 70 : return "data/musics/Home.mp3";
        case 71 : return "data/musics/Cafe.mp3";
        case 72 : return "data/musics/Sages.mp3";
        case 73 : return "data/musics/Opera.mp3";
        case 74 : return "data/musics/Prison.mp3";
        case 75 : return "data/musics/ChateauF.mp3";
        case 76 : return "data/musics/Courage.mp3";
        case 77 : return "data/musics/Harpie.mp3";
        case 78 : return "data/musics/Sagesse.mp3";
        case 79 : return "data/musics/Crabe.mp3";
        case 80 : return "data/musics/Force.mp3";
        case 81 : return "data/musics/Imp.mp3";
        case 82 : return "data/musics/Masamune.mp3";
        case 83 : return "data/musics/Abysses.mp3";
        case 84 : return "data/musics/ZoraS.mp3";
        case 85 : return "data/musics/Marlag.mp3";
        case 86 : return "data/musics/PyramideF.mp3";
        case 87 : return "data/musics/Fantomas.mp3";
        case 88 : return "data/musics/Vampire.mp3";
        case 89 : return "data/musics/PyramideP.mp3";
        case 90 : return "data/musics/Araignee.mp3";
        case 91 : return "data/musics/Air.mp3";
        case 92 : return "data/musics/Plumes.mp3";
        case 93 : return "data/musics/Garuda.mp3";
        case 94 : return "data/musics/Heckran.mp3";
        case 95 : return "data/musics/Feu.mp3";
        case 96 : return "data/musics/Sun.mp3";
        case 97 : return "data/musics/Orcus.mp3";
        case 98 : return "data/musics/Agahnim.mp3";
        case 99 : return "data/musics/AgahnimFinal.mp3";
        case 100 : return "data/musics/GanondorfFinal.mp3";
        case 101 : return "data/musics/Zelda.mp3";
        case 102 : return "data/musics/Casino.mp3";
        case 103 : return "data/musics/Quizz.mp3";
        case 104 : return "data/musics/Gemme.mp3";
        case 105 : return "data/musics/DestinationF.mp3";
        case 106 : return "data/musics/FinalBattle.mp3";
        case 107 : return "data/musics/Frog.mp3";
        case 108 : return "data/musics/Terreur.mp3";
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
