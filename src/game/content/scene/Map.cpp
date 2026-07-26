#include "Map.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../helper/MapHelper.h"
#include "../helper/ProjectileHelper.h"

#include "../types/Poussable.h"

#include "../effects/Feuilles.h"
#include "../effects/Debris.h"
#include "../effects/FumeeBlanche.h"
#include "../effects/Plouf.h"
#include "../objects/Interrupteur.h"
#include "../objects/Pnj.h"
#include "../objects/TalkableArea.h"
#include "../objects/Interrupteur.h"
#include "../objects/InterrupteurStar.h"
#include "../objects/Dices.h"
#include "../objects/Coffre.h"
#include "../objects/Caisse.h"
#include "../objects/Poule.h"
#include "../objects/PouleBig.h"
#include "../objects/Sphere.h"
#include "../objects/PiegeFeu.h"
#include "../objects/PiegeDemi.h"
#include "../objects/PiegeColere.h"
#include "../objects/PiegeUltime.h"
#include "../objects/PiegeLong.h"
#include "../objects/PiegePics.h"
#include "../objects/PiegeFlamme.h"
#include "../objects/PiegeFlammeVerte.h"
#include "../objects/Barriere.h"
#include "../objects/Stele.h"
#include "../objects/Jarre.h"
#include "../objects/ObjBomb.h"
#include "../objects/StatueGarde.h"
#include "../objects/Switch.h"
#include "../objects/Wagon.h"
#include "../ennemis/Ennemi010.h"
#include "../ennemis/Ennemi042.h"
#include "../ennemis/Ennemi106.h"
#include "../ennemis/Ennemi119.h"
#include "../ennemis/Ennemi141.h"

Map::Map(int level, Metronome *metronome) : metronome(metronome), map(level),
                                            w(0), h(0), music(0), stones(0), oldBarque(0), casino(10), jeuCasinoStarted(0), effects(0),
                                            ennemis(0), items(0), projectiles(0), objects(0), oldMetronomeValue(0)
{

    ostringstream os;
    for (int i = 0; i < NB_IMAGES; i++)
    {
        os << (i + 1);
        string filename = "data/images/tileset/image" + os.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename, true);
        os.str("");
    }

    initializer = new MapInitializer(this);
}

Map::~Map()
{
    for (int i = 0; i < NB_IMAGES; i++)
    {
        ResourceManager::getInstance()->free(images[i]);
    }
    delete effects;
    delete ennemis;
    delete items;
    delete projectiles;
    delete objects;
    delete initializer;
}

void Map::load()
{

    for (int j = 0; j < MAX_CASE_Y; j++)
    {
        for (int i = 0; i < MAX_CASE_X; i++)
        {
            sol[i][j] = -1;
            air[i][j] = -1;
            mur[i * 2][j * 2] = HERBE;
            mur[i * 2 + 1][j * 2] = HERBE;
            mur[i * 2][j * 2 + 1] = HERBE;
            mur[i * 2 + 1][j * 2 + 1] = HERBE;
        }
    }

    loadFromFile();

    bounds.setX(0);
    bounds.setY(0);
    bounds.setW(w);
    bounds.setH(h);

    delete effects;
    effects = new Quadtree();
    effects->setBox(0, 0, w, h);

    delete ennemis;
    ennemis = new Quadtree();
    ennemis->setBox(0, 0, w, h);

    delete items;
    items = new Quadtree();
    items->setBox(0, 0, w, h);

    delete projectiles;
    projectiles = new Quadtree();
    projectiles->setBox(0, 0, w, h);

    delete objects;
    objects = new Quadtree();
    objects->setBox(0, 0, w, h);

    init();
}

void Map::loadFromFile()
{
    ostringstream oss;
    oss << map;
    string result = "data/maps/map" + oss.str() + ".dat";
    ifstream file(result.c_str());

    file >> w;
    file >> h;
    file >> music;

    for (int i = 0; i < w / 16; i++)
    {
        for (int j = 0; j < h / 16; j++)
        {
            file >> sol[i][j];
            file >> mur[i * 2][j * 2];
            file >> mur[i * 2 + 1][j * 2];
            file >> mur[i * 2][j * 2 + 1];
            file >> mur[i * 2 + 1][j * 2 + 1];
        }
    }

    int cpt = 0;
    int a;
    int b;

    file >> cpt;
    for (int i = 0; i < cpt; i++)
    {
        file >> a;
        file >> b;
        file >> air[a][b];
    }

    file.close();
}

int Map::getW()
{
    return w;
}

int Map::getH()
{
    return h;
}

int Map::getId()
{
    return map;
}

void Map::launch()
{

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    scene->getHud()->reset();

    if (scene->getAvancement() != AV_START)
    {
        Link *link = scene->getLink();
        testAnim(link->getX(), link->getY(), N, false); // BUG FIX: link bloqu� si il revit sur une porte de maison

        if (getEpoque() == EP_FUTUR && !link->getInventory()->hasObject(PERLE))
        {
            link->setLapin(true);
        }

        int musicToPlay = music;

        int special = scene->getAnimationInGame()->getSpecialMusicId();

        if (special > 0)
        {
            musicToPlay = special;
        }

        if (link->getStatus()->getLife() <= 0)
        {
            musicToPlay = 3;
        }
        else if (map == 9 && scene->getAvancement() == AV_GANON_SORTI && link->getX() > 120 * 16)
        {
            musicToPlay = 48;
        }
        else if ((map == 10 || map == 137) && link->getInventory()->nbCristaux() >= 3 && link->getInventory()->getTrocGemme(3) >= TGV_BIERE && !link->getInventory()->hasCristal(3))
        {
            musicToPlay = 48;
        }
        else if (((map >= 15 && map < 31) || map == 57) && scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            musicToPlay = 47;
        }
        else if ((map == 18 || map == 19) && link->getEpee() == 0 && !link->getInventory()->hasObject(OCARINA))
        {
            musicToPlay = 48;
        }
        else if (map == 19 && link->getEpee() == 5 && !scene->getMonsters(50))
        {
            musicToPlay = 48;
        }
        else if ((map == 111 || map == 114 || map == 124) && scene->getTotalMonsters() >= 87)
        {
            musicToPlay = 48;
        }
        else if (map == 154 && scene->getAvancement() == AV_GANON_SORTI)
        {
            musicToPlay = 48;
        }
        else if (map == 57 && link->getY() == 25 * 16 + 8 && link->getInventory()->hasObject(TRIFORCE))
        {
            musicToPlay = 37; // generique fin
        }

        if (map == 21 && !scene->getCoffre(0, 2) && link->getInventory()->getTrocGemme(2) == TGJ_SCIE)
        {
            AudioManager::getInstance()->stopMusic();
        }
        else
        {
            AudioManager::getInstance()->playMusic(musicToPlay);
        }
    }

    if (map == 26)
        oldBarque = scene->getCoffre(0, 5);
    if (map == 68)
        oldBarque = scene->getCoffre(0, 14);

    launchRoom();
}

void Map::launchRoom()
{
    if (map >= 46)
    { // indoor only
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();

        bounds.setX(320 * (link->getX() / 320));
        bounds.setY(240 * (link->getY() / 240));
        bounds.setW(320);
        bounds.setH(240);

        // handle big rooms
        switch (map)
        {
        case 46:
            if (bounds.getX() == 0 && bounds.getY() == 240 * 2)
            {
                reactiveInterruptor(4 * 16, 42 * 16, true);
            }
            if (bounds.getX() == 320 * 17)
            {
                reactiveInterruptor(357 * 16, 27 * 16, true);
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(76);
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 && link->getInventory()->hasCoeur(0))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 5);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 9);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 13);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 9);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 2) && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            break;
        case 47:
            if (bounds.getX() == 320 * 17 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(78);
            }
            if (bounds.getX() == 320 * 17 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(1))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 13);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 14);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320 * 14);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 5)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 12 && bounds.getX() <= 320 * 13 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320 * 12);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 17 && bounds.getY() >= 240 * 4)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 48:
            if (bounds.getX() == 0 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(80);
            }
            if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(2))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 9);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240)
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() == 240 * 4)
            {
                bounds.setX(320 * 8);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 12 && bounds.getX() <= 320 * 13 && (bounds.getY() == 240 || bounds.getY() == 240 * 3))
            {
                bounds.setX(320 * 12);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 8 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 49:
            if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(83);
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() == 240 && link->getInventory()->hasCoeur(3))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() <= 240)
            {
                bounds.setX(320);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 5);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 7);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(320 * 7);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 9);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && (bounds.getY() == 240 * 3 || bounds.getY() == 240 * 5))
            {
                bounds.setX(320 * 9);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 12 && (bounds.getY() == 240 * 2 || bounds.getY() == 240 * 3))
            {
                bounds.setX(320 * 11);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 11 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() == 0)
            {
                bounds.setX(320 * 9 + 160);
                break;
            }
            break;
        case 50:
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(86);
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 && link->getInventory()->hasCoeur(4))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 9);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 9);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 14);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 14);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 7 && bounds.getY() == 240)
            {
                bounds.setX(320 * 5);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 10);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 51:
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(89);
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(5))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 9);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 9);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 14);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 14 && bounds.getX() <= 320 * 15 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 14);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 13 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 11 + 160);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 4 || bounds.getX() == 320 * 8) && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            break;
        case 52:
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(24);
                scene->getHud()->reset(); // remove mini boss life
            }
            if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(6))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 53:
            if (bounds.getX() == 0 && bounds.getY() == 240 && !scene->getCoffre(8, 27) && scene->getCoffre(8, 9))
            {
                AudioManager::getInstance()->playMusic(91);
                scene->getHud()->reset(); // remove mini boss life
                ouvrePorte(98, 21, 1);
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() == 240)
            {
                AudioManager::getInstance()->playMusic(91);
            }
            if (bounds.getX() == 320 * 9 && bounds.getY() == 0 && link->getInventory()->hasCoeur(7))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 5);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 5 && bounds.getY() <= 240 * 6)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 5);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 9);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            break;
        case 54:
            if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(30);
            }
            if (bounds.getX() == 320 * 9 + 160 && bounds.getY() == 240 && link->getInventory()->hasCoeur(8))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 3);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 7 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setX(320 * 7);
                bounds.setY(240 * 4);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 9);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 6 || bounds.getX() == 320 * 12) && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 7 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() == 240)
            {
                bounds.setX(320 * 3 + 160);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 9 + 160);
                break;
            }
            break;
        case 55:
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 14 && scene->getCoffre(10, 2) == 2 && mur[69 * 2][44 * 2] == TROU)
            {
                AudioManager::getInstance()->playMusic(95);
                ouvrePorte(69, 58, 0);
                ouvrePorte(68, 43, 5);
                switchStar();
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 2);
                bounds.setY(240);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 8)
            {
                bounds.setX(320 * 2);
                bounds.setY(240 * 6);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 11 && bounds.getY() <= 240 * 13)
            {
                bounds.setX(320 * 2);
                bounds.setY(240 * 11);
                bounds.setW(960);
                bounds.setH(720);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() <= 240)
            {
                bounds.setX(0);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(0);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setX(320 * 5);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 3);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 10 && bounds.getY() <= 240 * 11)
            {
                bounds.setX(0);
                bounds.setY(240 * 10);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 13 && bounds.getY() <= 240 * 14)
            {
                bounds.setX(0);
                bounds.setY(240 * 13);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 10 && bounds.getY() <= 240 * 11)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 10);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 * 13 && bounds.getY() <= 240 * 14)
            {
                bounds.setX(320 * 5);
                bounds.setY(240 * 13);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 6) && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setY(240 * 6);
                bounds.setH(480);
                break;
            }
            break;
        case 56:
            if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(0);
            }
            if (bounds.getX() == 320 * 8 && bounds.getY() == 240 && link->getInventory()->hasCoeur(10))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(0);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && (bounds.getY() <= 240 || bounds.getY() == 240 * 6))
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 6) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 7 || bounds.getX() == 320 * 9) && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            break;
        case 57:
            if (bounds.getX() == 320 * 7 && bounds.getY() == 0)
            {
                AudioManager::getInstance()->playMusic(107);
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
            {
                AudioManager::getInstance()->playMusic(27);
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(0);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && (bounds.getY() <= 240 || bounds.getY() == 240 * 6 || bounds.getY() == 240 * 15))
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && (bounds.getY() == 240 * 3 || bounds.getY() == 240 * 10))
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 11)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 6) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 7 || bounds.getX() == 320 * 9) && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                if (bounds.getX() == 320 * 7)
                    AudioManager::getInstance()->playMusic(27);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            break;
        case 58:
            if (jeuCasinoStarted != 3)
                jeuCasinoStarted = 0;
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3)
            {
                AudioManager::getInstance()->playMusic(102);
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2 && link->getInventory()->hasCoeur(11))
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240 * 6)
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && bounds.getY() == 240 * 6)
            {
                bounds.setX(320 * 4);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 0 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            break;
        case 59:
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 5);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320 * 9);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                if (scene->getCoffre(14, 2) == 2)
                {
                    AudioManager::getInstance()->playMusic(104);
                    scene->getHud()->reset(); // remove mini boss life
                    ouvrePorte(279, 43, 0);
                }
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() == 0)
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 2 && bounds.getX() <= 320 * 3 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 2);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 0)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 8);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 9 && bounds.getX() <= 320 * 10 && bounds.getY() == 0)
            {
                bounds.setX(320 * 9);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 10);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && (bounds.getY() == 0 || bounds.getY() == 240 * 3))
            {
                bounds.setX(320 * 13);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 3 || bounds.getX() == 320 * 4 || bounds.getX() == 320 * 7 || bounds.getX() == 320 * 8 || bounds.getX() == 320 * 11 || bounds.getX() == 320 * 12 || bounds.getX() == 320 * 15) && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && (bounds.getY() == 240 || bounds.getY() == 240 * 2))
            {
                bounds.setX(320 * 13 + 160);
                break;
            }
            break;
        case 60:
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2)
            {
                bounds.setX(320);
                bounds.setY(240);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() >= 240 * 7 && bounds.getY() <= 240 * 8)
            {
                bounds.setX(320);
                bounds.setY(240 * 7);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(320 * 4);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setX(320 * 4);
                bounds.setY(240 * 6);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && (bounds.getY() == 240 * 4 || bounds.getY() == 240 * 9))
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 4 && bounds.getX() <= 320 * 5 && (bounds.getY() == 0 || bounds.getY() == 240 * 8))
            {
                bounds.setX(320 * 4);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setY(240 * 6);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            break;
        case 63:
            if (bounds.getX() < 320 * 3)
            {
                bounds.setX(0);
                bounds.setW(960);
            }
            break;
        case 68:
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 4) && bounds.getY() >= 240)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() <= 240)
            {
                bounds.setX(320);
                bounds.setY(0);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2)
            {
                bounds.setX(320 + 160);
                break;
            }
            break;
        case 78:
            if (bounds.getX() < 320 * 3)
            {
                bounds.setX(0);
                bounds.setW(960);
            }
            if (bounds.getX() >= 320 * 3)
            {
                bounds.setX(960);
                bounds.setW(960);
            }
            break;
        case 80:
        case 136:
            bounds.setY(0);
            bounds.setH(480);
            break;
        case 102:
        case 144:
            bounds.setX(0);
            bounds.setW(640);
            break;
        case 150:
            if ((bounds.getX() == 320 || bounds.getX() == 320 * 4) && bounds.getY() >= 240)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 151:
        case 152:
        case 153:
            if (bounds.getX() == 320 && bounds.getY() >= 240)
            {
                bounds.setY(240);
                bounds.setH(480);
                break;
            }
            break;
        case 155:
            if (bounds.getX() <= 320 && (bounds.getY() == 0 || bounds.getY() == 240 || bounds.getY() == 240 * 6))
            {
                bounds.setX(0);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 3)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if ((bounds.getX() == 0 || bounds.getX() == 320 * 6) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setY(240 * 2);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() <= 240)
            {
                bounds.setY(0);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() == 320 * 6 && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5)
            {
                bounds.setY(240 * 4);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3)
            {
                bounds.setX(0);
                bounds.setY(240 * 2);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            break;
        case 156:
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 15 && bounds.getY() <= 240 * 16)
            {
                bounds.setX(0);
                bounds.setY(240 * 15);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() <= 320 && bounds.getY() >= 240 * 18)
            {
                bounds.setX(0);
                bounds.setY(240 * 18);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 3 && bounds.getX() <= 320 * 4 && bounds.getY() >= 240 * 18)
            {
                bounds.setX(320 * 3);
                bounds.setY(240 * 18);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() >= 240 * 10 && bounds.getY() <= 240 * 11)
            {
                bounds.setX(320 * 8);
                bounds.setY(240 * 10);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 8 && bounds.getY() >= 240 * 16 && bounds.getY() <= 240 * 17)
            {
                bounds.setX(320 * 6);
                bounds.setY(240 * 16);
                bounds.setW(960);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setX(320 * 10);
                bounds.setY(240 * 6);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 11 && bounds.getY() >= 240 * 12 && bounds.getY() <= 240 * 13)
            {
                bounds.setX(320 * 10);
                bounds.setY(240 * 12);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 * 13 && bounds.getX() <= 320 * 14 && bounds.getY() >= 240 * 12 && bounds.getY() <= 240 * 13)
            {
                bounds.setX(320 * 13);
                bounds.setY(240 * 12);
                bounds.setW(640);
                bounds.setH(480);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 3 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 8 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320 * 6);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 * 11 && bounds.getX() <= 320 * 13 && bounds.getY() == 240 * 2)
            {
                bounds.setX(320 * 11);
                bounds.setW(960);
                break;
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320 * 2 && bounds.getY() == 240 * 5)
            {
                bounds.setX(320);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 5)
            {
                bounds.setX(320 * 5);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() <= 320 * 4 && (bounds.getY() == 240 * 8 || bounds.getY() == 240 * 14))
            {
                bounds.setX(0);
                bounds.setW(1600);
                break;
            }
            if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 9 && (bounds.getY() == 240 * 8 || bounds.getY() == 240 * 14))
            {
                bounds.setX(320 * 5);
                bounds.setW(1600);
                break;
            }
            if (bounds.getX() >= 320 * 10 && bounds.getX() <= 320 * 14 && (bounds.getY() == 240 * 8 || bounds.getY() == 240 * 14))
            {
                bounds.setX(320 * 10);
                bounds.setW(1600);
                break;
            }
            if (bounds.getX() >= 320 * 6 && bounds.getX() <= 320 * 7 && bounds.getY() == 240 * 15)
            {
                bounds.setX(320 * 6);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 8 && bounds.getX() <= 320 * 9 && bounds.getY() == 240 * 19)
            {
                bounds.setX(320 * 8);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() >= 320 * 12 && bounds.getX() <= 320 * 13 && bounds.getY() == 240 * 19)
            {
                bounds.setX(320 * 12);
                bounds.setW(640);
                break;
            }
            if (bounds.getX() == 320 * 2 && bounds.getY() >= 240 * 18)
            {
                bounds.setY(240 * 18);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 4 || bounds.getX() == 320 * 14) && bounds.getY() >= 240 * 6 && bounds.getY() <= 240 * 7)
            {
                bounds.setY(240 * 6);
                bounds.setH(480);
                break;
            }
            if ((bounds.getX() == 320 * 11 || bounds.getX() == 320 * 13) && bounds.getY() >= 240 * 16 && bounds.getY() <= 240 * 17)
            {
                bounds.setY(240 * 16);
                bounds.setH(480);
                break;
            }
            break;
        default:
            break;
        }

        if (map > 45 && map < 61)
        {
            for (int j = bounds.getY() / 240; j < (bounds.getY() + bounds.getH()) / 240; j++)
            {
                for (int i = bounds.getX() / 320; i < (bounds.getX() + bounds.getW()) / 320; i++)
                {
                    scene->setRooms(map - 46, i, j, 1);
                    if (bounds.getX() % 320 != 0)
                    {
                        scene->setRooms(map - 46, i + 1, j, 1);
                    }
                }
            }
        }
        else if (map == 156)
        {
            for (int j = bounds.getY() / 240; j < (bounds.getY() + bounds.getH()) / 240; j++)
            {
                for (int i = bounds.getX() / 320; i < (bounds.getX() + bounds.getW()) / 320; i++)
                {
                    scene->setRooms(15, i, j, 1);
                    if (bounds.getX() % 320 != 0)
                    {
                        scene->setRooms(15, i + 1, j, 1);
                    }
                }
            }
        }

        testAnimRoom();
    }
}

void Map::resetRoom()
{
    if (map >= 46)
    {

        objects->resetNodes(&bounds);
        ennemis->resetNodes(&bounds);

        List toKill;
        effects->get(&bounds, &toKill);
        items->get(&bounds, &toKill);
        projectiles->get(&bounds, &toKill);

        toKill.iterateOnFirst();
        while (toKill.hasNext())
        {
            Node *n = (Node *)toKill.getNext();
            if (!n->isResetable())
            {
                n->killNode();
            }
        }
    }
}

BoundingBox *Map::getBounds()
{
    return &bounds;
}

void Map::reset()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (map == 26)
        scene->setCoffre(0, 5, oldBarque);
    if (map == 68)
        scene->setCoffre(0, 14, oldBarque);
    load();
    launch();
    Link *link = scene->getLink();
    testAnim(link->getX(), link->getY(), N, false); // BUG FIX: link bloqu� si il revit sur une porte de maison
}

void Map::init()
{
    initializer->init();
    if (map == 27)
    {
        stones = 0;
    }
}

void Map::activateInter(int x, int y, bool sound)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map)
    {
    case 46:
        if (x == 33 * 16 && y == 34 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 28, 0);
        }
        if (x == 33 * 16 && y == 40 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 43, 0);
        }
        if (x == 73 * 16 && y == 11 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 13, 0);
        }
        if (x == 64 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 43, 0);
        }
        if (x == 104 * 16 && y == 26 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 21, 1);
        }
        if (x == 113 * 16 && y == 41 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 43, 0);
        }
        if (x == 123 * 16 && y == 7 * 16)
        {
            scene->setCoffre(map - 45, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 6, 1);
        }
        if (x == 166 * 16 && y == 34 * 16)
        {
            scene->setCoffre(map - 45, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 28, 0);
        }
        if (x == 212 * 16 && y == 41 * 16)
        {
            scene->setCoffre(map - 45, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 43, 0);
        }
        if (x == 310 * 16 && y == 40 * 16)
        {
            scene->setCoffre(map - 45, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(298, 36, 1);
        }
        if (x == 304 * 16 && y == 17 * 16)
        {
            scene->setCoffre(map - 45, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(298, 21, 1);
        }
        if (x == 4 * 16 && y == 42 * 16)
        {
            resetRandomJarre(3);
        }
        if (x == 357 * 16 && y == 27 * 16)
        {
            resetRandomJarre(6);
        }
        break;
    case 47:
        if (x == 283 * 16 && y == 24 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 28, 0);
        }
        if (x == 314 * 16 && y == 33 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(318, 36, 1);
        }
        if (x == 336 * 16 && y == 69 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(338, 66, 1);
        }
        if (x == 257 * 16 && y == 49 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(258, 51, 1);
        }
        break;
    case 48:
        if (x == 57 * 16 && y == 3 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 6, 1);
        }
        if (x == 75 * 16 && y == 12 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 13, 0);
        }
        if (x == 67 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 58, 0);
        }
        if (x == 250 * 16 && y == 11 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(258, 6, 1);
        }
        if (x == 103 * 16 && y == 52 * 16)
        {
            scene->setCoffre(map - 45, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 58, 0);
        }
        if (x == 147 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 58, 0);
        }
        if (x == 195 * 16 && y == 12 * 16)
        {
            scene->setCoffre(map - 45, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 13, 0);
        }
        if (x == 189 * 16 && y == 20 * 16)
        {
            scene->setCoffre(map - 45, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 21, 1);
        }
        if (x == 184 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 51, 1);
        }
        if (x == 207 * 16 && y == 56 * 16)
        {
            scene->setCoffre(map - 45, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 58, 0);
        }
        if (x == 236 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 36, 1);
        }
        // mini boss
        if ((x == 124 * 16 || x == 129 * 16 || x == 135 * 16) && y == 33 * 16)
        {
            impFire(x, 35 * 16);
            if (sol[124][33] == 2546 && sol[129][33] == 2546 && sol[135][33] == 2546)
            {
                reactiveInterruptor(126 * 16, 42 * 16, false);
                reactiveInterruptor(133 * 16, 42 * 16, false);
            }
        }
        if ((x == 126 * 16 || x == 133 * 16) && y == 42 * 16)
        {
            if (x == 126 * 16)
            {
                impFire(124 * 16, 39 * 16);
                if (sol[133][42] == 2546)
                {
                    reactiveInterruptor(124 * 16, 33 * 16, false);
                    reactiveInterruptor(129 * 16, 33 * 16, false);
                    reactiveInterruptor(135 * 16, 33 * 16, false);
                }
            }
            else
            {
                impFire(135 * 16, 39 * 16);
                if (sol[126][42] == 2546)
                {
                    reactiveInterruptor(124 * 16, 33 * 16, false);
                    reactiveInterruptor(129 * 16, 33 * 16, false);
                    reactiveInterruptor(135 * 16, 33 * 16, false);
                }
            }
        }
        break;
    case 49:
        if (x == 30 * 16 && y == 21 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 28, 0);
        }
        if (x == 62 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 51, 1);
        }
        if (x == 82 * 16 && y == 32 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 28, 0);
        }
        if (x == 88 * 16 && y == 71 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 66, 1);
        }
        if (x == 155 * 16 && y == 69 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 73, 0);
        }
        if (x == 157 * 16 && y == 85 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 81, 1);
        }
        if (x == 162 * 16 && y == 5 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 6, 1);
        }
        if (x == 228 * 16 && y == 62 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 73, 0);
        }
        break;
    case 50:
        if (x == 43 * 16 && y == 67 * 16)
        {
            scene->setCoffre(map - 45, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 66, 1);
        }
        if (x == 89 * 16 && y == 56 * 16)
        {
            scene->setCoffre(map - 45, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(84 * 16, 49 * 16, TI_CLE, 4);
        }
        if (x == 134 * 16 && y == 34 * 16)
        {
            scene->setCoffre(map - 45, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 28, 0);
        }
        if (x == 150 * 16 && y == 63 * 16)
        {
            scene->setCoffre(map - 45, 29, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 66, 1);
        }
        if (x == 167 * 16 && y == 32 * 16)
        {
            scene->setCoffre(map - 45, 30, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 28, 0);
        }
        if (x == 162 * 16 && y == 79 * 16)
        {
            scene->setCoffre(map - 45, 31, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 81, 1);
        }
        if (x == 196 * 16 && y == 67 * 16)
        {
            scene->setCoffre(map - 45, 32, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 73, 0);
        }
        if (x == 204 * 16 && y == 81 * 16)
        {
            scene->setCoffre(map - 45, 33, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 73, 0);
        }
        if (x == 243 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 34, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(258, 36, 1);
        }
        if (x == 247 * 16 && y == 79 * 16)
        {
            scene->setCoffre(map - 45, 35, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 73, 0);
        }
        if (x == 256 * 16 && y == 97 * 16)
        {
            scene->setCoffre(map - 45, 36, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 88, 0);
        }
        if (x == 283 * 16 && y == 52 * 16)
        {
            scene->setCoffre(map - 45, 37, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 58, 0);
        }
        break;
    case 51:
        if ((x == 240 * 16 || x == 259 * 16) && (y == 23 * 16 || y == 40 * 16))
        {
            tigreFire(x, y);
        }
        if (x == 37 * 16 && y == 70 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 66, 1);
        }
        if (x == 67 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 58, 0);
        }
        if (x == 97 * 16 && y == 64 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 66, 1);
        }
        if (x == 108 * 16 && y == 21 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 28, 0);
        }
        if (x == 127 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 58, 0);
        }
        if (x == 136 * 16 && y == 82 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 73, 0);
        }
        if (x == 149 * 16 && y == 72 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 66, 1);
        }
        if (x == 217 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 58, 0);
        }
        if (x == 216 * 16 && y == 52 * 16)
        {
            scene->setCoffre(map - 45, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 51, 1);
        }
        if (x == 229 * 16 && y == 85 * 16)
        {
            scene->setCoffre(map - 45, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 73, 0);
        }
        if (x == 246 * 16 && y == 92 * 16)
        {
            scene->setCoffre(map - 45, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 88, 0);
        }
        if (x == 263 * 16 && y == 67 * 16)
        {
            scene->setCoffre(map - 45, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(269, 58, 0);
        }
        if (x == 295 * 16 && y == 25 * 16)
        {
            scene->setCoffre(map - 45, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 28, 0);
        }
        if (x == 285 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 58, 0);
        }
        if (x == 302 * 16 && y == 64 * 16)
        {
            scene->setCoffre(map - 45, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(298, 66, 1);
        }
        break;
    case 52:
        if (x == 28 * 16 && y == 68 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 66, 1);
        }
        if (x == 48 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 58, 0);
        }
        if (x == 63 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 43, 0);
        }
        if (x == 71 * 16 && y == 68 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 66, 1);
        }
        if (x == 103 * 16 && y == 22 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 21, 1);
        }
        if (x == 127 * 16 && y == 32 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 28, 0);
        }
        if (x == 156 * 16 && y == 22 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 21, 1);
        }
        if (x == 167 * 16 && y == 33 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 43, 0);
        }
        if (x == 216 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 36, 1);
        }
        break;
    case 53:
        if (x == 12 * 16 && y == 27 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 28, 0);
        }
        if (x == 23 * 16 && y == 7 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 13, 0);
        }
        if (x == 32 * 16 && y == 42 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 43, 0);
        }
        if (x == 50 * 16 && y == 41 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 36, 1);
        }
        if (x == 72 * 16 && y == 27 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 28, 0);
        }
        if (x == 68 * 16 && y == 92 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 103, 0);
        }
        if (x == 97 * 16 && y == 5 * 16)
        {
            scene->setCoffre(map - 45, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 6, 1);
        }
        if (x == 87 * 16 && y == 72 * 16)
        {
            scene->setCoffre(map - 45, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 73, 0);
        }
        if (x == 107 * 16 && y == 77 * 16)
        {
            scene->setCoffre(map - 45, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 73, 0);
        }
        if (x == 132 * 16 && y == 47 * 16)
        {
            scene->setCoffre(map - 45, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 43, 0);
        }
        if (x == 134 * 16 && y == 102 * 16)
        {
            scene->setCoffre(map - 45, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 103, 0);
        }
        if (x == 197 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(198, 51, 1);
        }
        break;
    case 54:
        if (x == 36 * 16 && y == 21 * 16)
        {
            scene->setCoffre(map - 45, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 13, 0);
        }
        if (x == 72 * 16 && y == 77 * 16)
        {
            scene->setCoffre(map - 45, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 73, 0);
        }
        if (x == 108 * 16 && y == 17 * 16)
        {
            scene->setCoffre(map - 45, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 28, 0);
        }
        if (x == 112 * 16 && y == 47 * 16)
        {
            scene->setCoffre(map - 45, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 43, 0);
        }
        if (x == 117 * 16 && y == 10 * 16)
        {
            scene->setCoffre(map - 45, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 6, 1);
        }
        if (x == 122 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 51, 1);
        }
        if (x == 148 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 29, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 51, 1);
        }
        if (x == 171 * 16 && y == 40 * 16)
        {
            scene->setCoffre(map - 45, 30, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 28, 0);
        }
        if (x == 196 * 16 && y == 82 * 16)
        {
            scene->setCoffre(map - 45, 31, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 81, 1);
        }
        if (x == 236 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 32, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(218, 36, 1);
        }
        if (x == 233 * 16 && y == 67 * 16)
        {
            scene->setCoffre(map - 45, 33, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 73, 0);
        }
        if (x == 235 * 16 && y == 85 * 16)
        {
            scene->setCoffre(map - 45, 34, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 81, 1);
        }
        if (x == 248 * 16 && y == 70 * 16)
        {
            scene->setCoffre(map - 45, 35, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 58, 0);
        }
        break;
    case 55:
        if (x == 17 * 16 && y == 145 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 141, 1);
        }
        if (x == 27 * 16 && y == 27 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 28, 0);
        }
        if (x == 57 * 16 && y == 220 * 16)
        {
            scene->setCoffre(map - 45, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 216, 1);
        }
        if (x == 82 * 16 && y == 220 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 216, 1);
        }
        if (x == 123 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 28, 0);
        }
        if (x == 122 * 16 && y == 145 * 16)
        {
            scene->setCoffre(map - 45, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 141, 1);
        }
        break;
    case 56:
        if (x == 37 * 16 && y == 25 * 16)
        {
            scene->setCoffre(map - 45, 10, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 21, 1);
        }
        if (x == 43 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 11, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 28, 0);
        }
        if (x == 54 * 16 && y == 97 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_PLOT);
            activateStatue();
        }
        if (x == 103 * 16 && y == 7 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 6, 1);
        }
        break;
    case 58:
        if (x == 11 * 16 && y == 41 * 16)
        {
            scene->setCoffre(map - 45, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 36, 1);
        }
        if (x == 123 * 16 && y == 37 * 16)
        {
            scene->setCoffre(map - 45, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 43, 0);
        }
        break;
    case 59:
        if (x == 7 * 16 && y == 12 * 16)
        {
            scene->setCoffre(map - 45, 8, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 13, 0);
        }
        if (x == 22 * 16 && y == 10 * 16)
        {
            scene->setCoffre(map - 45, 9, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 6, 1);
        }
        if (x == 27 * 16 && y == 42 * 16)
        {
            scene->setCoffre(map - 45, 10, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 43, 0);
        }
        if (x == 42 * 16 && y == 55 * 16)
        {
            scene->setCoffre(map - 45, 11, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 51, 1);
        }
        if (x == 67 * 16 && y == 12 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 13, 0);
        }
        if (x == 67 * 16 && y == 42 * 16)
        {
            scene->setCoffre(map - 45, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 43, 0);
        }
        if (x == 95 * 16 && y == 52 * 16)
        {
            scene->setCoffre(map - 45, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 51, 1);
        }
        break;
    case 60:
        if (x == 7 * 16 && y == 57 * 16)
        {
            scene->setCoffre(map - 45, 6, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 58, 0);
        }
        if (x == 32 * 16 && y == 62 * 16)
        {
            scene->setCoffre(map - 45, 7, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 58, 0);
        }
        if (x == 52 * 16 && y == 38 * 16)
        {
            scene->setCoffre(map - 45, 8, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 36, 1);
        }
        if (x == 47 * 16 && y == 47 * 16)
        {
            scene->setCoffre(map - 45, 9, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 43, 0);
        }
        if (x == 44 * 16 && y == 128 * 16)
        {
            scene->setCoffre(map - 45, 10, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 133, 0);
        }
        if (x == 127 * 16 && y == 62 * 16)
        {
            scene->setCoffre(map - 45, 11, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 58, 0);
        }
        if (x == 122 * 16 && y == 100 * 16)
        {
            scene->setCoffre(map - 45, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 103, 0);
        }
        break;
    case 63:
        scene->setCoffre(0, 7, 1);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
        ouvrePorte(78, 6, 1);
        break;
    case 67:
        scene->setCoffre(0, 11, 1);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
        ouvrePorte(58, 21, 1);
        break;
    case 68:
        if (x == 7 * 16)
        {
            scene->setCoffre(0, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 13, 0);
        }
        else
        {
            if (sol[34][13] == 3097)
            {
                scene->setCoffre(0, 13, 1);
                sol[34][13] = 3098;
                sol[45][13] = 3099;
                sol[41][9] = 3097;
            }
            else
            {
                scene->setCoffre(0, 13, 0);
                sol[34][13] = 3097;
                sol[45][13] = 3097;
                sol[41][9] = 3098;
            }
        }
        break;
    case 119:
        if (sound)
            AudioManager::getInstance()->playSound(TS_PLOT);
        scene->setCoffre(0, 27, -2);
        scene->getAnimationInGame()->startAnim(5);
        break;
    case 154:
        if (sound)
            AudioManager::getInstance()->playSound(TS_PLOT);
        if (y == 3 * 16)
        {
            if (mur[41 * 2][7 * 2] == MUR)
            {
                ouvrePorte(38, 6, 0);
                fermePorte(54, 8, 1);
            }
            else
            {
                fermePorte(38, 6, 0);
                ouvrePorte(54, 8, 2);
            }
        }
        else
        {
            if (mur[41 * 2][22 * 2] == MUR)
            {
                ouvrePorte(38, 21, 0);
                fermePorte(54, 23, 1);
            }
            else
            {
                fermePorte(38, 21, 0);
                ouvrePorte(54, 23, 2);
            }
        }
        break;
    case 156:
        if (x == 23 * 16 && y == 82 * 16)
        {
            scene->setCoffre(17, 4, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 88, 0);
        }
        if (x == 43 * 16 && y == 7 * 16)
        {
            scene->setCoffre(17, 5, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 13, 0);
        }
        if (x == 47 * 16 && y == 192 * 16)
        {
            scene->setCoffre(17, 6, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 193, 0);
        }
        if (x == 47 * 16 && y == 252 * 16)
        {
            scene->setCoffre(17, 7, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 253, 0);
        }
        if (x == 63 * 16 && y == 82 * 16)
        {
            scene->setCoffre(17, 8, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 88, 0);
        }
        if (x == 76 * 16 && y == 232 * 16)
        {
            scene->setCoffre(17, 9, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 238, 0);
        }
        if (x == 63 * 16 && y == 247 * 16)
        {
            scene->setCoffre(17, 10, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 253, 0);
        }
        if (x == 71 * 16 && y == 267 * 16)
        {
            scene->setCoffre(17, 11, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 261, 1);
        }
        if (x == 113 * 16 && y == 171 * 16)
        {
            scene->setCoffre(17, 12, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 163, 0);
        }
        if (x == 127 * 16 && y == 102 * 16)
        {
            scene->setCoffre(17, 13, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 103, 0);
        }
        if (x == 137 * 16 && y == 115 * 16)
        {
            scene->setCoffre(17, 14, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(138, 111, 1);
        }
        if (x == 122 * 16 && y == 160 * 16)
        {
            scene->setCoffre(17, 15, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 156, 1);
        }
        if (x == 127 * 16 && y == 192 * 16)
        {
            scene->setCoffre(17, 16, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 193, 0);
        }
        if (x == 147 * 16 && y == 102 * 16)
        {
            scene->setCoffre(17, 17, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 103, 0);
        }
        if (x == 152 * 16 && y == 272 * 16)
        {
            scene->setCoffre(17, 18, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 268, 0);
        }
        if (x == 147 * 16 && y == 282 * 16)
        {
            scene->setCoffre(17, 19, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 283, 0);
        }
        if (x == 167 * 16 && y == 154 * 16)
        {
            scene->setCoffre(17, 20, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 156, 1);
        }
        if (x == 167 * 16 && y == 237 * 16)
        {
            scene->setCoffre(17, 21, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 238, 0);
        }
        if (x == 177 * 16 && y == 250 * 16)
        {
            scene->setCoffre(17, 22, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 246, 1);
        }
        if (x == 183 * 16 && y == 82 * 16)
        {
            scene->setCoffre(17, 23, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 88, 0);
        }
        if (x == 217 * 16 && y == 265 * 16)
        {
            scene->setCoffre(17, 24, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(218, 261, 1);
        }
        if (x == 236 * 16 && y == 157 * 16)
        {
            scene->setCoffre(17, 25, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(218, 156, 1);
        }
        if (x == 232 * 16 && y == 237 * 16)
        {
            scene->setCoffre(17, 26, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 238, 0);
        }
        if (x == 256 * 16 && y == 7 * 16)
        {
            scene->setCoffre(17, 27, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 13, 0);
        }
        if (x == 249 * 16 && y == 168 * 16)
        {
            scene->setCoffre(17, 28, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 178, 0);
        }
        if (x == 269 * 16 && y == 108 * 16)
        {
            scene->setCoffre(17, 29, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 111, 1);
        }
        if (x == 263 * 16 && y == 157 * 16)
        {
            scene->setCoffre(17, 30, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 156, 1);
        }
        if (x == 267 * 16 && y == 237 * 16)
        {
            scene->setCoffre(17, 31, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(269, 238, 0);
        }
        if (x == 292 * 16 && y == 94 * 16)
        {
            scene->setCoffre(17, 32, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 88, 0);
        }
        if (x == 282 * 16 && y == 169 * 16)
        {
            scene->setCoffre(17, 33, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 171, 1);
        }
        if (x == 287 * 16 && y == 192 * 16)
        {
            scene->setCoffre(17, 34, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(289, 178, 0);
        }
        if (x == 282 * 16 && y == 244 * 16)
        {
            scene->setCoffre(17, 35, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 246, 1);
        }
        if (x == 282 * 16 && y == 265 * 16)
        {
            scene->setCoffre(17, 36, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(278, 261, 1);
        }
        if (x == 162 * 16 && y == 115 * 16)
        {
            scene->setCoffre(17, 42, 1);
            if (sound)
                AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(158, 111, 1);
        }
        break;
    }
}

bool Map::desactivateInter(int x, int y, bool sound)
{
    /*if (map == 15 && sol[84][17] == 1817 && sol[84][27] == 1817 && sol[95][17] == 1817) {
        if (sound) AudioManager::getInstance()->playSound(TS_PLOT);
        return true;
    }*/
    return false;
}

void Map::allumeTorche(int x, int y)
{ // 1935 -> 1936
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map)
    {
    case 48:
        if (x == 37 && y == 50)
            scene->setCoffre(map - 45, 29, 1);
        if (x == 37 && y == 54)
            scene->setCoffre(map - 45, 30, 1);
        if (x == 68 && y == 27)
            scene->setCoffre(map - 45, 31, 1);
        if (x == 71 && y == 27)
            scene->setCoffre(map - 45, 32, 1);
        if (x == 69 && y == 41)
            scene->setCoffre(map - 45, 33, 1);
        if (x == 70 && y == 41)
            scene->setCoffre(map - 45, 34, 1);
        if (x == 109 && y == 7)
            scene->setCoffre(map - 45, 35, 1);
        if (x == 102 && y == 35)
            scene->setCoffre(map - 45, 36, 1);
        if (x == 102 && y == 39)
            scene->setCoffre(map - 45, 37, 1);
        if (x == 127 && y == 17)
            scene->setCoffre(map - 45, 38, 1);
        if (x == 132 && y == 17)
            scene->setCoffre(map - 45, 39, 1);
        if (x == 186 && y == 26)
            scene->setCoffre(map - 45, 40, 1);
        if (x == 191 && y == 49)
            scene->setCoffre(map - 45, 41, 1);
        if (x == 191 && y == 34)
            scene->setCoffre(map - 45, 42, 1);
        if (x == 196 && y == 34)
            scene->setCoffre(map - 45, 43, 1);
        if (x == 207 && y == 24)
            scene->setCoffre(map - 45, 44, 1);
        if (x == 212 && y == 24)
            scene->setCoffre(map - 45, 45, 1);
        if (x == 204 && y == 35)
            scene->setCoffre(map - 45, 46, 1);
        if (x == 215 && y == 35)
            scene->setCoffre(map - 45, 47, 1);
        if (x == 206 && y == 51)
            scene->setCoffre(map - 45, 48, 1);
        if (x == 213 && y == 51)
            scene->setCoffre(map - 45, 49, 1);
        if (x == 224 && y == 20)
            scene->setCoffre(map - 45, 50, 1);
        if (x == 234 && y == 26)
            scene->setCoffre(map - 45, 51, 1);
        if (x == 229 && y == 37)
            scene->setCoffre(map - 45, 52, 1);
        if (x == 234 && y == 53)
            scene->setCoffre(map - 45, 53, 1);
        if (x == 227 && y == 56)
            scene->setCoffre(map - 45, 54, 1);
        if (x == 242 && y == 49)
            scene->setCoffre(map - 45, 55, 1);
        if (x == 242 && y == 55)
            scene->setCoffre(map - 45, 56, 1);
        if (x == 247 && y == 57)
            scene->setCoffre(map - 45, 57, 1);
        if (x == 252 && y == 57)
            scene->setCoffre(map - 45, 58, 1);

        if (x == 37 && (y == 50 || y == 54) && scene->getCoffre(map - 45, 29) && scene->getCoffre(map - 45, 30) && mur[40 * 2][52 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 51, 1);
        }
        if ((x == 68 || x == 71) && y == 27 && scene->getCoffre(map - 45, 31) && scene->getCoffre(map - 45, 32) && mur[69 * 2 + 1][28 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 28, 0);
        }
        if ((x == 69 || x == 70) && y == 41 && scene->getCoffre(map - 45, 33) && scene->getCoffre(map - 45, 34) && !nbCoffres())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(75 * 16, 40 * 16, TI_CLE, 6);
        }
        if (x == 109 && y == 7 && mur[100 * 2][7 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 6, 1);
        }
        if (x == 102 && (y == 35 || y == 39) && scene->getCoffre(map - 45, 36) && scene->getCoffre(map - 45, 37) && mur[100 * 2][37 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 36, 1);
        }
        if ((x == 127 || x == 132) && y == 17 && scene->getCoffre(map - 45, 38) && scene->getCoffre(map - 45, 39) && mur[129 * 2 + 1][13 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 13, 0);
        }
        if (((x == 186 && y == 26) || (x == 191 && (y == 49 || y == 34)) || (x == 196 && y == 34) || ((x == 207 || x == 212) && y == 24) || ((x == 204 || x == 215) && y == 35) || ((x == 206 || x == 213) && y == 51) || (x == 224 && y == 20) || (x == 234 && y == 26) || (x == 229 && y == 37) || (x == 234 && y == 53) || (x == 227 && y == 56)) && scene->getCoffre(map - 45, 40) && scene->getCoffre(map - 45, 41) && scene->getCoffre(map - 45, 42) && scene->getCoffre(map - 45, 43) && scene->getCoffre(map - 45, 44) && scene->getCoffre(map - 45, 45) && scene->getCoffre(map - 45, 46) && scene->getCoffre(map - 45, 47) && scene->getCoffre(map - 45, 48) && scene->getCoffre(map - 45, 49) && scene->getCoffre(map - 45, 50) && scene->getCoffre(map - 45, 51) && scene->getCoffre(map - 45, 52) && scene->getCoffre(map - 45, 53) && scene->getCoffre(map - 45, 54) && mur[209 * 2 + 1][13 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(209, 13, 0);
        }
        if (x == 242 && (y == 49 || y == 55) && scene->getCoffre(map - 45, 55) && scene->getCoffre(map - 45, 56) && mur[240 * 2][52 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 51, 1);
        }
        if ((x == 247 || x == 252) && y == 57 && scene->getCoffre(map - 45, 57) && scene->getCoffre(map - 45, 58) && mur[249 * 2 + 1][58 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 58, 0);
        }
        break;
    case 49:
        if (x == 222 && y == 21)
            scene->setCoffre(map - 45, 22, 1);
        if (x == 228 && y == 27)
            scene->setCoffre(map - 45, 23, 1);
        if (x == 231 && y == 27)
            scene->setCoffre(map - 45, 24, 1);
        if (x == 237 && y == 19)
            scene->setCoffre(map - 45, 25, 1);
        if (x == 222 && y == 9)
            scene->setCoffre(map - 45, 26, 1);
        if (x == 230 && y == 2)
            scene->setCoffre(map - 45, 27, 1);
        if (x == 237 && y == 5)
            scene->setCoffre(map - 45, 28, 1);
        if (x == 237 && y == 9)
            scene->setCoffre(map - 45, 29, 1);
        if (x == 117 && y == 35)
            scene->setCoffre(map - 45, 31, 1);
        if (x == 117 && y == 39)
            scene->setCoffre(map - 45, 32, 1);
        if (scene->getCoffre(map - 45, 22) && scene->getCoffre(map - 45, 23) && scene->getCoffre(map - 45, 24) && scene->getCoffre(map - 45, 25) && scene->getCoffre(map - 45, 26) && scene->getCoffre(map - 45, 27) && scene->getCoffre(map - 45, 28) && scene->getCoffre(map - 45, 29) && mur[240 * 2][7 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 6, 1);
        }
        if (scene->getCoffre(map - 45, 31) && scene->getCoffre(map - 45, 32) && mur[120 * 2][37 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 36, 1);
        }
        break;
    case 54:
        if (x == 102 && y == 71)
            scene->setCoffre(map - 45, 36, 1);
        if (x == 115 && y == 62)
            scene->setCoffre(map - 45, 37, 1);
        if (x == 127 && y == 62)
            scene->setCoffre(map - 45, 38, 1);
        if (x == 135 && y == 62)
            scene->setCoffre(map - 45, 39, 1);
        if (x == 133 && y == 76)
            scene->setCoffre(map - 45, 40, 1);
        if (x == 107 && y == 80)
            scene->setCoffre(map - 45, 41, 1);
        if (x == 102 && y == 86)
            scene->setCoffre(map - 45, 42, 1);
        if (x == 107 && y == 86)
            scene->setCoffre(map - 45, 43, 1);
        if (x == 130 && y == 86)
            scene->setCoffre(map - 45, 44, 1);
        if (x == 135 && y == 83)
            scene->setCoffre(map - 45, 45, 1);
        if (scene->getCoffre(map - 45, 36) && scene->getCoffre(map - 45, 37) && scene->getCoffre(map - 45, 38) && scene->getCoffre(map - 45, 39) && scene->getCoffre(map - 45, 40) && scene->getCoffre(map - 45, 41) && scene->getCoffre(map - 45, 42) && scene->getCoffre(map - 45, 43) && scene->getCoffre(map - 45, 44) && scene->getCoffre(map - 45, 45) && mur[129 * 2 + 1][58 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 58, 0);
        }
        break;
    case 55:
        if (x == 47 && y == 57)
            scene->setCoffre(map - 45, 19, 1);
        if (x == 52 && y == 57)
            scene->setCoffre(map - 45, 20, 1);
        if (x == 106 && y == 15)
            scene->setCoffre(map - 45, 21, 1);
        if (x == 115 && y == 2)
            scene->setCoffre(map - 45, 22, 1);
        if (x == 119 && y == 10)
            scene->setCoffre(map - 45, 23, 1);
        if (x == 119 && y == 22)
            scene->setCoffre(map - 45, 24, 1);
        if (x == 136 && y == 4)
            scene->setCoffre(map - 45, 25, 1);
        if (x == 134 && y == 17)
            scene->setCoffre(map - 45, 26, 1);
        if (x == 24 && y == 102)
            scene->setCoffre(map - 45, 27, 1);
        if (x == 35 && y == 102)
            scene->setCoffre(map - 45, 28, 1);
        if (x == 55 && y == 104)
            scene->setCoffre(map - 45, 29, 1);
        if (x == 66 && y == 104)
            scene->setCoffre(map - 45, 30, 1);
        if (x == 73 && y == 104)
            scene->setCoffre(map - 45, 31, 1);
        if (x == 84 && y == 104)
            scene->setCoffre(map - 45, 32, 1);
        if (x == 58 && y == 112)
            scene->setCoffre(map - 45, 33, 1);
        if (x == 81 && y == 112)
            scene->setCoffre(map - 45, 34, 1);
        if (x == 55 && y == 119)
            scene->setCoffre(map - 45, 35, 1);
        if (x == 66 && y == 119)
            scene->setCoffre(map - 45, 36, 1);
        if (x == 73 && y == 119)
            scene->setCoffre(map - 45, 37, 1);
        if (x == 84 && y == 119)
            scene->setCoffre(map - 45, 38, 1);
        if (x == 108 && y == 122)
            scene->setCoffre(map - 45, 39, 1);
        if (x == 111 && y == 122)
            scene->setCoffre(map - 45, 40, 1);
        if (x == 108 && y == 132)
            scene->setCoffre(map - 45, 41, 1);
        if (x == 111 && y == 132)
            scene->setCoffre(map - 45, 42, 1);
        if (x == 97 && y == 152)
            scene->setCoffre(map - 45, 43, 1);
        if (x == 97 && y == 162)
            scene->setCoffre(map - 45, 44, 1);
        if (x == 6 && y == 201)
            scene->setCoffre(map - 45, 45, 1);
        if (x == 27 && y == 201)
            scene->setCoffre(map - 45, 46, 1);
        if (x == 30 && y == 201)
            scene->setCoffre(map - 45, 47, 1);
        if (x == 14 && y == 219)
            scene->setCoffre(map - 45, 48, 1);
        if (x == 23 && y == 213)
            scene->setCoffre(map - 45, 49, 1);
        if (x == 27 && y == 220)
            scene->setCoffre(map - 45, 50, 1);
        if (scene->getCoffre(map - 45, 19) && scene->getCoffre(map - 45, 20) && mur[49 * 2 + 1][58 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(49, 58, 0);
        }
        if (scene->getCoffre(map - 45, 21) && scene->getCoffre(map - 45, 22) && scene->getCoffre(map - 45, 23) && scene->getCoffre(map - 45, 24) && scene->getCoffre(map - 45, 25) && scene->getCoffre(map - 45, 26) && mur[100 * 2][7 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 6, 1);
        }
        if (scene->getCoffre(map - 45, 27) && scene->getCoffre(map - 45, 28) && mur[29 * 2 + 1][103 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 103, 0);
        }
        if (scene->getCoffre(map - 45, 29) && scene->getCoffre(map - 45, 30) && scene->getCoffre(map - 45, 31) && scene->getCoffre(map - 45, 32) && scene->getCoffre(map - 45, 33) && scene->getCoffre(map - 45, 34) && scene->getCoffre(map - 45, 35) && scene->getCoffre(map - 45, 36) && scene->getCoffre(map - 45, 37) && scene->getCoffre(map - 45, 38) && mur[69 * 2 + 1][88 * 2 + 1] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 88, 0);
        }
        if (scene->getCoffre(map - 45, 39) && scene->getCoffre(map - 45, 40) && scene->getCoffre(map - 45, 41) && scene->getCoffre(map - 45, 42) && mur[100 * 2][127 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 126, 1);
        }
        if (scene->getCoffre(map - 45, 43) && scene->getCoffre(map - 45, 44) && mur[100 * 2][157 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 156, 1);
        }
        if (scene->getCoffre(map - 45, 45) && scene->getCoffre(map - 45, 46) && scene->getCoffre(map - 45, 47) && scene->getCoffre(map - 45, 48) && scene->getCoffre(map - 45, 49) && scene->getCoffre(map - 45, 50) && mur[40 * 2][202 * 2] == MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 201, 1);
        }
        break;
    }
}

void Map::eteintTorche(int x, int y)
{ // 1936 -> 1935
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map)
    {
    case 54:
        if ((x == 47 || x == 53) && y == 20 && sol[47][20] == 1935 && sol[53][20] == 1935 && !scene->getCoffre(map - 45, 46))
        {
            scene->setCoffre(map - 45, 46, 1);
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(50 * 16, 20 * 16, TI_CLE, 5);
        }
        if (x == 80 && y == 45 && mur[79 * 2 + 1][28 * 2 + 1] == MUR)
        {
            scene->setCoffre(map - 45, 47, 1);
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(79, 28, 0);
        }
        if (x == 182 && (y == 50 || y == 54) && sol[182][50] == 1935 && sol[182][54] == 1935 && mur[180 * 2][52 * 2] == MUR)
        {
            scene->setCoffre(map - 45, 48, 1);
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 51, 1);
        }
        if ((x == 247 || x == 251) && y == 17 && sol[247][17] == 1935 && sol[251][17] == 1935 && !scene->getCoffre(map - 45, 49))
        {
            scene->setCoffre(map - 45, 49, 1);
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(249 * 16, 17 * 16, TI_CLE, 12);
        }
        if ((x == 248 || x == 251) && y == 37 && sol[248][37] == 1935 && sol[251][37] == 1935 && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
        {
            scene->setCoffre(map - 45, 50, 1);
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 28, 0);
        }
        if (x == 97 && (y == 2 || y == 12) && sol[97][2] == 1935 && sol[97][12] == 1935 && mur[100 * 2][7 * 2] == MUR)
        {
            scene->setCoffre(map - 45, 57, 1);
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 6, 1);
        }
        break;
    case 156:
        if (y == 97 && (x == 2 || x == 17) && sol[2][97] == 1935 && sol[17][97] == 1935 && mur[9 * 2 + 1][88 * 2 + 1] == MUR)
        {
            scene->setCoffre(17, 38, 1);
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(9, 88, 0);
        }
        break;
    }
}

void Map::activateInterStar(int x, int y, bool sound)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (sound)
        AudioManager::getInstance()->playSound(TS_MAGIC);
    switch (map)
    {
    case 51:
        holeStar(7, 51, 2, 2);
        holeStar(28, 66, 4, 3);
        holeStar(45, 51, 2, 2);
        holeStar(49, 36, 2, 2);
        holeStar(89, 35, 2, 2);
        holeStar(82, 47, 16, 10);
        holeStar(128, 51, 4, 4);
        holeStar(169, 35, 2, 2);

        fullStar(42, 64, 4, 7);
        fullStar(62, 62, 15, 11);
        fullStar(64, 35, 2, 5);
        fullStar(84, 37, 12, 4);
        fullStar(149, 63, 2, 2);
        fullStar(164, 37, 12, 4);
        fullStar(214, 48, 4, 9);
        fullStar(282, 62, 4, 11);

        scene->setCoffre(6, 29, 1);
        break;
    case 55:
        ouvrePorte(68, 43, 4);
        scene->getAnimationInGame()->startAnim(11);
        break;
    case 156:
        if (x == 130 * 16)
        {
            holeStar(114, 109, 3, 7);
            holeStar(125, 17, 10, 4);
            holeStar(165, 23, 10, 5);
            holeStar(183, 228, 14, 8);

            fullStar(106, 228, 8, 9);
            fullStar(125, 92, 10, 4);
            fullStar(130, 175, 2, 2);
            fullStar(133, 246, 34, 16);
            fullStar(163, 81, 2, 3);

            scene->setCoffre(16, 40, 1);
        }
        else
        {
            fullStar(114, 109, 3, 7);
            fullStar(125, 17, 10, 4);
            fullStar(165, 23, 10, 5);
            fullStar(183, 228, 14, 8);

            holeStar(106, 228, 8, 9);
            holeStar(125, 92, 10, 4);
            holeStar(130, 175, 2, 2);
            holeStar(133, 246, 34, 16);
            holeStar(163, 81, 2, 3);

            scene->setCoffre(16, 40, 0);
        }
        break;
    }
}

void Map::holeStar(int x, int y, int w, int h)
{
    int offset = map == 156 ? 1851 : 0;
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (sol[i][j] == 4886)
            {
                setSol(i * 16, j * 16, 4886, TROU);
            }
        }
    }
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (mur[i * 2][j * 2] == TROU)
            {
                if (mur[(i - 1) * 2][(j - 1) * 2] == TROU && mur[i * 2][(j - 1) * 2] == TROU && mur[(i + 1) * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[(i - 1) * 2][(j + 1) * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU && mur[(i + 1) * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5084 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5073 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5075 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5076 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 5078 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5072 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] != TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    setSol(i * 16, j * 16, 5074 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] != TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 5077 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] != TROU && mur[i * 2][(j + 1) * 2] != TROU)
                {
                    setSol(i * 16, j * 16, 5079 + offset);
                }
                else if (mur[i * 2][(j - 1) * 2] == TROU && mur[(i - 1) * 2][j * 2] == TROU && mur[(i + 1) * 2][j * 2] == TROU && mur[i * 2][(j + 1) * 2] == TROU)
                {
                    if (mur[(i + 1) * 2][(j + 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 5080 + offset);
                    if (mur[(i - 1) * 2][(j + 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 5081 + offset);
                    if (mur[(i + 1) * 2][(j - 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 5082 + offset);
                    if (mur[(i - 1) * 2][(j - 1) * 2] != TROU)
                        setSol(i * 16, j * 16, 5083 + offset);
                }
            }
        }
    }
}

void Map::fullStar(int x, int y, int w, int h)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            if (mur[i * 2][j * 2] == TROU)
            {
                setSol(i * 16, j * 16, 4886, PIERRE);
            }
        }
    }
}

void Map::loop()
{
    effects->removeDeadNodes();
    ennemis->removeDeadNodes();
    items->removeDeadNodes();
    projectiles->removeDeadNodes();
    objects->removeDeadNodes();

    List toLoop;
    effects->get(&bounds, &toLoop);
    ennemis->get(&bounds, &toLoop);
    items->get(&bounds, &toLoop);
    projectiles->get(&bounds, &toLoop);
    objects->get(&bounds, &toLoop);

    toLoop.iterateOnFirst();
    while (toLoop.hasNext())
    {
        Loopable *l = (Loopable *)toLoop.getNext();
        l->loop();
    }

    if (map == 58 && jeuCasinoStarted == 3)
    {
        tempsCasinoEcoule += 0.0166667;
        if (tempsCasinoEcoule >= 12)
        {
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->hideTime();
            AudioManager::getInstance()->playSound(TS_ERROR);
            jeuCasinoStarted = 0;
        }
    }

    // test tapis
    int metronomeValue = metronome->getValue();
    if ((map == 52 || map == 156) && oldMetronomeValue != metronomeValue)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();
        // on link
        if (link->getAnimation() != CHUTE && link->getAnimation() != SOULEVE && link->getAnimation() != TOUCHE)
        {
            int val = getSol(link->getX() + 8, link->getY() + 16);
            int val1 = getSol(link->getX() + 2, link->getY() + 10);
            int val2 = getSol(link->getX() + 13, link->getY() + 10);
            int val3 = getSol(link->getX() + 2, link->getY() + 21);
            int val4 = getSol(link->getX() + 13, link->getY() + 21);
            if ((val1 == 5299 || val2 == 5299 || val3 == 5299 || val4 == 5299) && val != 5303 && val != 5307 && val != 5311)
            {
                link->pousseY(-1);
            }
            else if ((val1 == 5303 || val2 == 5303 || val3 == 5303 || val4 == 5303) && val != 5299 && val != 5307 && val != 5311)
            {
                link->pousseY(1);
            }
            else if ((val1 == 5307 || val2 == 5307 || val3 == 5307 || val4 == 5307) && val != 5299 && val != 5303 && val != 5311)
            {
                link->pousseX(-1);
            }
            else if ((val1 == 5311 || val2 == 5311 || val3 == 5311 || val4 == 5311) && val != 5299 && val != 5303 && val != 5307)
            {
                link->pousseX(1);
            }
        }
        // on ennemi
        List toMove;
        ennemis->get(&bounds, &toMove);
        toMove.iterateOnFirst();
        while (toMove.hasNext())
        {
            Ennemi *e = (Ennemi *)toMove.getNext();
            Ennemi042 *enn = dynamic_cast<Ennemi042 *>(e);
            if (enn != 0)
            {
                int val = getSol(enn->getX() + 8 + 5, enn->getY() + 11);
                int val1 = getSol(enn->getX() + 2 + 5, enn->getY() + 3);
                int val2 = getSol(enn->getX() + 13 + 5, enn->getY() + 3);
                int val3 = getSol(enn->getX() + 2 + 5, enn->getY() + 18);
                int val4 = getSol(enn->getX() + 13 + 5, enn->getY() + 18);
                if ((val1 == 5299 || val2 == 5299 || val3 == 5299 || val4 == 5299) && val != 5303 && val != 5307 && val != 5311)
                {
                    enn->pousseY(-2);
                }
                else if ((val1 == 5303 || val2 == 5303 || val3 == 5303 || val4 == 5303) && val != 5299 && val != 5307 && val != 5311)
                {
                    enn->pousseY(2);
                }
                else if ((val1 == 5307 || val2 == 5307 || val3 == 5307 || val4 == 5307) && val != 5299 && val != 5303 && val != 5311)
                {
                    enn->pousseX(-2);
                }
                else if ((val1 == 5311 || val2 == 5311 || val3 == 5311 || val4 == 5311) && val != 5299 && val != 5303 && val != 5307)
                {
                    enn->pousseX(2);
                }
            }
            else
            {
                Ennemi106 *enn106 = dynamic_cast<Ennemi106 *>(e);
                if (enn106 != 0)
                {
                    int val = getSol(enn106->getX() + 15, enn106->getY() + 24);
                    if (val == 5307)
                    {
                        enn106->pousseX(-1);
                    }
                }
            }
        }
        // on items
        List itemsToMove;
        items->get(&bounds, &itemsToMove);
        itemsToMove.iterateOnFirst();
        while (itemsToMove.hasNext())
        {
            Item *item = dynamic_cast<Item *>(itemsToMove.getNext());
            BoundingBox *itemBox = item->getBoundingBox();
            int val = getSol(itemBox->getX() + (itemBox->getW() / 2), itemBox->getY() + (itemBox->getH() / 2));
            int val1 = getSol(itemBox->getX() + 2, itemBox->getY() + 2);
            int val2 = getSol(itemBox->getX() + itemBox->getW() - 3, itemBox->getY() + 2);
            int val3 = getSol(itemBox->getX() + 2, itemBox->getY() + itemBox->getH() - 3);
            int val4 = getSol(itemBox->getX() + itemBox->getW() - 3, itemBox->getY() + itemBox->getH() - 3);
            if ((val1 == 5299 || val2 == 5299 || val3 == 5299 || val4 == 5299) && val != 5303 && val != 5307 && val != 5311)
            {
                item->pousseY(-2);
            }
            else if ((val1 == 5303 || val2 == 5303 || val3 == 5303 || val4 == 5303) && val != 5299 && val != 5307 && val != 5311)
            {
                item->pousseY(2);
            }
            else if ((val1 == 5307 || val2 == 5307 || val3 == 5307 || val4 == 5307) && val != 5299 && val != 5303 && val != 5311)
            {
                item->pousseX(-2);
            }
            else if ((val1 == 5311 || val2 == 5311 || val3 == 5311 || val4 == 5311) && val != 5299 && val != 5303 && val != 5307)
            {
                item->pousseX(2);
            }
        }
        // on objects
        List objectsToMove;
        objects->get(&bounds, &objectsToMove);
        objectsToMove.iterateOnFirst();
        while (objectsToMove.hasNext())
        {
            ObjBomb *bomb = dynamic_cast<ObjBomb *>(objectsToMove.getNext());
            if (bomb != 0)
            {
                int val = getSol(bomb->getX() + 8, bomb->getY() + 8);
                int val1 = getSol(bomb->getX() + 2, bomb->getY() + 2);
                int val2 = getSol(bomb->getX() + 13, bomb->getY() + 2);
                int val3 = getSol(bomb->getX() + 2, bomb->getY() + 13);
                int val4 = getSol(bomb->getX() + 13, bomb->getY() + 13);
                if ((val1 == 5299 || val2 == 5299 || val3 == 5299 || val4 == 5299) && val != 5303 && val != 5307 && val != 5311)
                {
                    bomb->pousseY(-2);
                }
                else if ((val1 == 5303 || val2 == 5303 || val3 == 5303 || val4 == 5303) && val != 5299 && val != 5307 && val != 5311)
                {
                    bomb->pousseY(2);
                }
                else if ((val1 == 5307 || val2 == 5307 || val3 == 5307 || val4 == 5307) && val != 5299 && val != 5303 && val != 5311)
                {
                    bomb->pousseX(-2);
                }
                else if ((val1 == 5311 || val2 == 5311 || val3 == 5311 || val4 == 5311) && val != 5299 && val != 5303 && val != 5307)
                {
                    bomb->pousseX(2);
                }
            }
        }
    }
    oldMetronomeValue = metronomeValue;
}

void Map::draw(List *toDraw, BoundingBox *box, int dstX, int dstY)
{

    int srcX = box->getX();
    int srcY = box->getY();
    int srcW = box->getW();
    int srcH = box->getH();

    drawSol(srcX, srcY, srcW, srcH, dstX, dstY);

    effects->get(box, toDraw);
    ennemis->get(box, toDraw);
    items->get(box, toDraw);
    projectiles->get(box, toDraw);
    objects->get(box, toDraw);

    if (toDraw != 0)
    {
        toDraw->iterateOnFirst();
        while (toDraw->hasNext())
        {
            Drawable *d = (Drawable *)toDraw->getNext();
            d->draw(srcX - dstX, srcY - dstY);
        }
    }

    drawAir(srcX, srcY, srcW, srcH, dstX, dstY);
}

void Map::drawSol(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE)
    {
        for (int i = srcX; i < srcX + srcW; i += CASE)
        {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(sol[i / CASE][j / CASE]);

            if (motif >= 0)
            {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW)
                {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH)
                {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                    images[im],
                    (motif % 40) * CASE + diffX,
                    (motif / 40) * CASE + diffY, w, h,
                    dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }
}

void Map::drawAir(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE)
    {
        for (int i = srcX; i < srcX + srcW; i += CASE)
        {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(air[i / CASE][j / CASE]);

            if (motif >= 0)
            {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW)
                {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH)
                {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                    images[im],
                    (motif % 40) * CASE + diffX, (motif / 40) * CASE + diffY, w, h,
                    dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }
}

int Map::getMotif(int value)
{
    int tmp = metronome->getValue();
    switch (value)
    {
    case 1: // fleurs
        switch (tmp % 4)
        {
        case 0:
            return 2;
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 1;
        }
        break;
    case 329:
    case 330:
    case 331:
    case 332:
    case 333:
    case 334:
    case 335:
    case 336:
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 8;
        case 2:
            return value + 8 * 2;
        case 3:
            return value + 8;
        }
        break;
    case 67:
    case 70:
    case 379:
    case 382:
    case 385:
    case 388:
    case 391:
    case 394:
    case 401:
    case 404:
    case 407:
    case 410:
    case 415:
    case 418:
    case 1626:
    case 1629:
    case 1632:
    case 1635:
    case 1638:
    case 1641:
    case 1644:
    case 1647:
    case 1650:
    case 1653:
    case 1656:
    case 1659:
    case 1794:
    case 1797:
    case 2309:
    case 2312:
    case 2315:
    case 2334:
    case 2337:
    case 2340:
    case 2397:
    case 2400:
    case 2403:
    case 2406:
    case 2420:
    case 2423:
    case 2426:
    case 2429:
    case 2432:
    case 2435:
    case 2438:
    case 2441:
    case 2624:
    case 2627:
    case 2875:
    case 2878:
    case 2881:
    case 2884:
    case 2887:
    case 2890:
    case 2893:
    case 2896:
    case 2899:
    case 2902:
    case 2905:
    case 2908:
        switch (tmp / 2 % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        }
        break;
    case 353:
    case 356:
    case 1662:
    case 1665:
    case 1936:
    case 4876:
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 1;
        }
        break;
    case 613:
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 3;
        case 2:
            return value + 5;
        }
        break;
    case 615:
        return value + 2 * (tmp % 3);
    case 1463:
    case 1471:
    case 1473: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 25;
        case 2:
            return value + 26;
        }
        break;
    case 1466:
    case 1468:
    case 1470: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 24;
        case 2:
            return value + 25;
        }
        break;
    case 1474:
    case 1476: // clouds
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 26;
        case 2:
            return value + 27;
        }
        break;
    case 1477: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1477;
        case 1:
            return 1504;
        case 2:
            return 1505;
        }
        break;
    case 1486: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1486;
        case 1:
            return 1506;
        case 2:
            return 1507;
        }
        break;
    case 1487: // clouds
        switch (tmp % 3)
        {
        case 0:
            return 1487;
        case 1:
            return 1508;
        case 2:
            return 1509;
        }
        break;
    case 2634:
    case 2635:
        switch (tmp / 2 % 2)
        {
        case 0:
            return value;
        case 1:
            return value + 2;
        }
        break;
    case 2912:
    case 3079:
    case 3082:
    case 3085:
    case 3088:
    case 3091:
    case 3094:
        switch (tmp / 2 % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 1;
        }
        break;
    case 3144: // teleport
        switch (tmp % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        }
        break;
    // eau donjon
    case 3147:
    case 3148:
    case 3149:
    case 3150:
    case 3151:
    case 3152:
    case 3153:
    case 3154:
    case 3155:
    case 3156:
    case 3157:
    case 3158:
    case 3159:
    case 4589:
    case 4590:
    case 4591:
    case 4592:
    case 4593:
    case 4594:
    case 4595:
    case 4596:
    case 4597:
    case 4598:
    case 4599:
    case 4600:
    case 4601:
        switch (tmp / 2 % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 13;
        case 2:
            return value + 26;
        }
        break;
    case 3100:
    case 3101:
    case 3102:
    case 3103:
    case 3104:
    case 3105:
    case 3106:
    case 3107:
    case 3108:
    case 3109:
    case 3110:
    case 3111:
    case 3112:

    case 3727:
    case 3728:
    case 3729:
    case 3730:
    case 3731:
    case 3732:
    case 3733:
    case 3734:
    case 3735:
    case 3736:
    case 3737:
    case 3738:
    case 3739:

    case 4339:
    case 4340:
    case 4341:
    case 4342:
    case 4343:
    case 4344:
    case 4345:
    case 4346:
    case 4347:
    case 4348:
    case 4349:
    case 4350:
    case 4351:

    case 5883:
    case 5884:
    case 5885:
    case 5886:
    case 5887:
    case 5888:
    case 5889:
    case 5890:
    case 5891:
    case 5892:
    case 5893:
    case 5894:
    case 5895:
        switch (tmp / 2 % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 13;
        case 2:
            return value + 26;
        case 3:
            return value + 13;
        }
        break;
    case 3333:
        switch (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCoffre(0, 27) / 8 % 3)
        {
        case 0:
            return value;
        case 1:
            return value + 2;
        case 2:
            return value + 1;
        }
        break;
    case 4156: // pics
        switch (tmp % 6)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 3;
        case 4:
            return value + 2;
        case 5:
            return value + 1;
        }
        break;
    case 5299:
    case 5303:
    case 5307:
    case 5311: // tapis roulant
        switch (tmp % 4)
        {
        case 0:
            return value;
        case 1:
            return value + 1;
        case 2:
            return value + 2;
        case 3:
            return value + 3;
        }
        break;
    default:
        break;
    }
    return value;
}

short Map::getMur(int x, int y)
{
    return mur[x / 8][y / 8];
}

short Map::getSol(int x, int y)
{
    return sol[x / CASE][y / CASE];
}

void Map::setSol(int x, int y, short s)
{
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
}

void Map::setSol(int x, int y, short s, Collision c)
{
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
    mur[i * 2][j * 2] = c;
    mur[i * 2 + 1][j * 2] = c;
    mur[i * 2][j * 2 + 1] = c;
    mur[i * 2 + 1][j * 2 + 1] = c;
}

void Map::setSol(int x, int y, int w, int h, short s, Collision c)
{
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            setSol(x + i * 16, y + j * 16, s, c);
        }
    }
}

void Map::setAir(int x, int y, short s)
{
    int i = x / CASE;
    int j = y / CASE;
    air[i][j] = s;
}

void Map::setMur(int x, int y, Collision c)
{
    setMur(x, y, c, c, c, c);
}

void Map::setMur(int x, int y, Collision c1, Collision c2, Collision c3, Collision c4)
{
    int i = x / CASE;
    int j = y / CASE;
    mur[i * 2][j * 2] = c1;
    mur[i * 2 + 1][j * 2] = c2;
    mur[i * 2][j * 2 + 1] = c3;
    mur[i * 2 + 1][j * 2 + 1] = c4;
}

void Map::addEffect(Effect *effect)
{
    effects->add((Node *)effect);
}

void Map::addEnnemi(Ennemi *ennemi)
{
    ennemis->add((Node *)ennemi);
}

void Map::addItem(Item *item)
{
    items->add((Node *)item);
}

void Map::addProjectile(Projectile *projectile)
{
    projectiles->add((Node *)projectile);
}

void Map::addObject(Object *object)
{
    objects->add((Node *)object);
}

void Map::removeObject(Object *object)
{
    objects->remove((Node *)object);
}

bool Map::isOnWater(BoundingBox *bb)
{
    int x = bb->getX();
    int y = bb->getY();
    int w = bb->getW();
    int h = bb->getH();

    for (int j = (y / 8) * 8; j < y + h; j += 8)
    {
        for (int i = (x / 8) * 8; i < x + w; i += 8)
        {
            if (getMur(i, j) != EAU_PROF)
                return false;
        }
    }
    return true;
}

bool Map::checkCollisions(BoundingBox *box, Collisionable *object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox, bool checkObjects,
                          int safeX, int safeY, int safeW, int safeH, bool checkDanger)
{

    if (box->getX() < bounds.getX() || box->getX() + box->getW() > bounds.getX() + bounds.getW() ||
        box->getY() < bounds.getY() || box->getY() + box->getH() > bounds.getY() + bounds.getH())
    {
        return false;
    }

    if (onlyBox)
    {

        for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8)
        {
            for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8)
            {
                Collision c = (Collision)getMur(i, j);
                if (c == GRAND_MUR)
                {
                    return false;
                }
            }
        }

        return true;
    }

    Link *lk = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8)
    {
        for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8)
        {
            Collision c = (Collision)getMur(i, j);
            if (!object->isCollision(c) || (withAvoid && object->isToAvoid(c)))
            {
                if (c == DANGER && checkDanger)
                {
                    if ((Collisionable *)lk == object)
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
                return false;
            }
            else
            {
                if (c == DANGER_BAS && checkDanger)
                {
                    if ((Collisionable *)lk == object)
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
            }
        }
    }

    if (checkEnnemis)
    {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext())
        {
            Ennemi *e = (Ennemi *)enn.getNext();
            if (ignoreNotIdle && !e->isIdle())
                continue;
            if (e != object && e->getBoundingBox()->intersect(box))
            {
                return false;
            }
        }
    }

    if (checkObjects)
    {
        List obj;
        objects->get(box, &obj);
        obj.iterateOnFirst();
        while (obj.hasNext())
        {
            Object *o = (Object *)obj.getNext();
            TalkableArea *talkableArea = dynamic_cast<TalkableArea *>(o);
            if (talkableArea == 0)
            { // pas de collision avec les TalkableArea

                if ((Collisionable *)lk == object)
                {
                    PiegePics *pics = dynamic_cast<PiegePics *>(o);
                    PiegeLong *plong = dynamic_cast<PiegeLong *>(o);
                    Barriere *barriere = dynamic_cast<Barriere *>(o);
                    PiegeFlamme *flamme = dynamic_cast<PiegeFlamme *>(o);
                    PiegeFlammeVerte *flammeVerte = dynamic_cast<PiegeFlammeVerte *>(o);
                    Dices *dices = dynamic_cast<Dices *>(o);
                    if (pics != 0)
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                    else if (plong != 0)
                    {
                        lk->underAttack(plong->getDirection(), 1, TA_PHYSIC, TE_NORMAL);
                    }
                    else if (barriere != 0)
                    {
                        lk->underAttack(S, 1, TA_PHYSIC, TE_ELECTRIC);
                    }
                    else if (flamme != 0 && lk->getBoundingBox()->intersect(flamme->getBoundingBox()))
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 8, TA_MAGIC, TE_FEU);
                    }
                    else if (flammeVerte != 0 && lk->getBoundingBox()->intersect(flammeVerte->getBoundingBox()))
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_MAGIC, TE_MORT);
                    }
                    else if (dices != 0 && lk->getBoundingBox()->intersect(dices->getBoundingBox()))
                    {
                        Direction dir = N;
                        switch (lk->getDirection())
                        {
                        case N:
                            dir = S;
                            break;
                        case S:
                            dir = N;
                            break;
                        case W:
                            dir = E;
                            break;
                        case E:
                            dir = W;
                            break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_ARGENT);
                    }
                }

                if (o != object && o->getBoundingBox()->intersect(box))
                {
                    BoundingBox safeBox;
                    safeBox.setX(safeX);
                    safeBox.setY(safeY);
                    safeBox.setW(safeW);
                    safeBox.setH(safeH);
                    if (!o->getBoundingBox()->intersect(&safeBox))
                    {
                        return false;
                    }
                }
                if (o != object && o->getSecondBoundingBox() != 0 && o->getSecondBoundingBox()->intersect(box))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Map::testDegat(BoundingBox *box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis, bool onObjects)
{

    bool result = false;

    // on ennemi :
    if (onEnnemis)
    {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext())
        {
            Ennemi *e = (Ennemi *)enn.getNext();
            if (e->getBoundingBox()->intersect(box) && e->isHittable())
            {
                e->underAttack(dir, force, type, effect, box);
                result = true;
            }
        }
    }

    // on objects :
    if (onObjects)
    {
        List obj;
        objects->get(box, &obj);

        obj.iterateOnFirst();
        while (obj.hasNext())
        {
            Object *o = (Object *)obj.getNext();
            if (o->isAttackable() && o->getBoundingBox()->intersect(box))
            {
                o->underAttack(dir, force, type, effect);
                result = true;
            }
        }
    }

    // on projectiles :

    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    if ((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 2)
    {
        List proj;
        projectiles->get(box, &proj);

        proj.iterateOnFirst();
        while (proj.hasNext())
        {
            Projectile *p = (Projectile *)proj.getNext();
            if (p->getBoundingBox()->intersect(box))
            {
                p->renvoie(dir);
                result = true;
            }
        }
    }

    // on map :

    int x0 = box->getX();
    int beginX = x0 - (x0 % CASE);
    int x1 = box->getX() + box->getW() - 1;
    int endX = x1 - (x1 % CASE);

    int y0 = box->getY();
    int beginY = y0 - (y0 % CASE);
    int y1 = box->getY() + box->getH() - 1;
    int endY = y1 - (y1 % CASE);

    if (beginX < 0)
        beginX = 0;
    if (beginY < 0)
        beginY = 0;
    if (endX > getW())
        endX = getW();
    if (endY > getH())
        endY = getH();

    for (int j = beginY; j <= endY; j += CASE)
    {
        for (int i = beginX; i <= endX; i += CASE)
        {

            int x = i / CASE;
            int y = j / CASE;
            int val = sol[x][y];

            if (type == TA_SWORD || effect == TE_FEU || type == TA_SWORD_HOLD)
            {
                if (val == 185 || val == 187 || val == 189 || val == 553)
                {
                    // buissons
                    Collision c;
                    TypeDons td;
                    int tb;
                    switch (val)
                    {
                    case 185:
                        c = HERBE;
                        td = TD_BUISSON_VERT;
                        tb = 0;
                        break;
                    case 187:
                        c = HERBE;
                        td = TD_BUISSON_ROSE;
                        tb = 1;
                        break;
                    case 189:
                        c = SABLE;
                        td = TD_BUISSON_OCRE;
                        tb = 2;
                        break;
                    case 553:
                        c = NEIGE;
                        td = TD_BUISSON_NEIGE;
                        tb = 3;
                        break;
                    default:
                        c = HERBE;
                        td = TD_BUISSON_VERT;
                        tb = 0;
                        break;
                    }

                    if (map == 21 && x == 10 && y == 4)
                    {
                        sol[x][y] = 1212;
                        mur[x * 2][y * 2] = TROU;
                        mur[(x * 2) + 1][y * 2] = TROU;
                        mur[x * 2][(y * 2) + 1] = TROU;
                        mur[(x * 2) + 1][(y * 2) + 1] = TROU;
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                    }
                    else
                    {
                        sol[x][y] = val + 1;
                        mur[x * 2][y * 2] = c;
                        mur[(x * 2) + 1][y * 2] = c;
                        mur[x * 2][(y * 2) + 1] = c;
                        mur[(x * 2) + 1][(y * 2) + 1] = c;

                        if (!testGemmeForce(x, y))
                        {
                            TypeItem t = MapHelper::getInstance()->getItemRandomizer(td)->selectType();
                            if (t != TI_NO_ITEM)
                            {
                                addItem(ItemHelper::getInstance()->createItem(t, i + 8, j + 8));
                            }
                        }
                    }

                    addEffect(new Feuilles(x * 16 + 8 - 14, y * 16 + 8 - 22 - 8, tb));
                    AudioManager::getInstance()->playSound(TS_BUISSON);

                    result = (type == TA_SWORD || type == TA_SWORD_HOLD);
                }
                else if (val == 6186)
                {
                    // rideaux
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    ouvrePorte(69, 13, 0);
                }
                else if (val == 6397)
                {
                    // rideaux
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    ouvrePorte(109, 163, 2);
                }
            }
            if (effect == TE_GLACE)
            {
                if ((getMur(i, j) == EAU || getMur(i, j) == EAU_PROF) && (getMur(i + 8, j) == EAU || getMur(i + 8, j) == EAU_PROF) && (getMur(i, j + 8) == EAU || getMur(i, j + 8) == EAU_PROF) && (getMur(i + 8, j + 8) == EAU || getMur(i + 8, j + 8) == EAU_PROF))
                {

                    sol[x][y] = 359;
                    mur[x * 2][y * 2] = GLACE;
                    mur[(x * 2) + 1][y * 2] = GLACE;
                    mur[x * 2][(y * 2) + 1] = GLACE;
                    mur[(x * 2) + 1][(y * 2) + 1] = GLACE;
                }
                switch (val)
                {
                case 67:
                    sol[x][y] = 73;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 70:
                    sol[x][y] = 74;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 313:
                    sol[x][y] = 360;
                    break;
                case 314:
                    sol[x][y] = 361;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 315:
                    sol[x][y] = 362;
                    break;
                case 316:
                    sol[x][y] = 363;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 318:
                    sol[x][y] = 364;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 319:
                    sol[x][y] = 365;
                    break;
                case 320:
                    sol[x][y] = 366;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    break;
                case 321:
                    sol[x][y] = 367;
                    break;
                case 322:
                    sol[x][y] = 368;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 323:
                    sol[x][y] = 369;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 324:
                    sol[x][y] = 370;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 325:
                    sol[x][y] = 371;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 391:
                    sol[x][y] = 421;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    break;
                case 401:
                    sol[x][y] = 422;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 407:
                    sol[x][y] = 423;
                    mur[x * 2][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 415:
                    sol[x][y] = 424;
                    mur[x * 2 + 1][y * 2] = GLACE;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 1794:
                    sol[x][y] = 73;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 1797:
                    sol[x][y] = 74;
                    mur[x * 2][y * 2 + 1] = GLACE;
                    mur[x * 2 + 1][y * 2 + 1] = GLACE;
                    break;
                case 1936:
                    sol[x][y] = 1935;
                    break; // torche
                default:
                    break;
                }
                if (val == 1936)
                    eteintTorche(x, y);
            }
            if (effect == TE_EAU && val == 1936)
            {
                sol[x][y] = 1935;
                eteintTorche(x, y);
            }
            if (type == TA_EXPLO || type == TA_MARTEAU)
            {
                if (val == 1686 || val == 2766)
                {
                    addEffect(new Debris(x * 16 + 8, y * 16 + 8, N, 2));
                    AudioManager::getInstance()->playSound(TS_BREAK);

                    mur[x * 2][y * 2] = HERBE;
                    mur[(x * 2) + 1][y * 2] = HERBE;
                    mur[x * 2][(y * 2) + 1] = HERBE;
                    mur[(x * 2) + 1][(y * 2) + 1] = HERBE;

                    sol[x][y] = val == 1686 ? 275 : 7;

                    testGemmeForce(x, y);
                }
                else if (val == 2493 || val == 2494)
                {
                    addEffect(new Debris(x * 16 + 8, y * 16 + 8, N, 2));
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    scene->setCoffre(0, 3, 1);
                    ouvrePorte(88, 10, 0);
                }
                else if (val == 2767)
                {
                    addEffect(new Debris(x * 16 + 8, y * 16 + 8, N, 2));
                    AudioManager::getInstance()->playSound(TS_BREAK);

                    mur[x * 2][y * 2] = NEIGE;
                    mur[(x * 2) + 1][y * 2] = NEIGE;
                    mur[x * 2][(y * 2) + 1] = NEIGE;
                    mur[(x * 2) + 1][(y * 2) + 1] = NEIGE;

                    sol[x][y] = 771;

                    testGemmeForce(x, y);
                }
            }
            if (type == TA_EXPLO)
            {
                if (val == 173 || val == 174 /*|| val == 1615*/ || val == 1772)
                { // plaine
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 0, 1);
                    ouvrePorte(59, 10, 0);
                }
                else if (val == 1204 || val == 1205)
                { // herbe ocre
                    // fissure
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 4, 1);
                    ouvrePorte(58, 18, 0);
                }
                else if (val == 3055 || val == 3056 || val == 3057 || val == 3058)
                { // grottes
                    switch (map)
                    {
                    case 69:
                        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                        scene->setCoffre(0, 25, 1);
                        ouvrePorte(9, 13, 0);
                        break;
                    }
                }
                else if (map > 45 && map < 61)
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    // donjon
                    switch (map)
                    {
                    case 48:
                        if (val == 4380 || val == 4381)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 27, 1);
                            ouvrePorte(289, 13, 2);
                        }
                        break;
                    case 50:
                        if (val == 4801 || val == 4802)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (x < 220)
                            {
                                scene->setCoffre(map - 45, 13, 1);
                                ouvrePorte(209, 28, 2);
                            }
                            else
                            {
                                scene->setCoffre(map - 45, 15, 1);
                                ouvrePorte(289, 73, 2);
                            }
                        }
                        else if (val == 4803 || val == 4804)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (x < 220)
                            {
                                scene->setCoffre(map - 45, 12, 1);
                                ouvrePorte(98, 66, 3);
                            }
                            else
                            {
                                scene->setCoffre(map - 45, 14, 1);
                                ouvrePorte(278, 21, 3);
                            }
                        }
                        else if (val == 4853)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (x == 24 || x == 25)
                            {
                                scene->setCoffre(map - 45, 17, 1);
                                ouvrePorte(24, 54, 4);
                            }
                            else if (x == 28 || x == 29)
                            {
                                scene->setCoffre(map - 45, 18, 1);
                                ouvrePorte(28, 51, 4);
                            }
                            else if (x == 33 || x == 34)
                            {
                                scene->setCoffre(map - 45, 19, 1);
                                ouvrePorte(33, 49, 4);
                            }
                            else if (x == 35 || x == 36)
                            {
                                scene->setCoffre(map - 45, 20, 1);
                                ouvrePorte(35, 53, 4);
                            }
                            else if (x == 64 || x == 65)
                            {
                                scene->setCoffre(map - 45, 21, 1);
                                ouvrePorte(64, 53, 4);
                            }
                            else if (x == 69 || x == 70)
                            {
                                scene->setCoffre(map - 45, 22, 1);
                                ouvrePorte(69, 52, 4);
                            }
                            else if ((x == 73 || x == 74) && y < 52)
                            {
                                scene->setCoffre(map - 45, 23, 1);
                                ouvrePorte(73, 49, 4);
                            }
                            else if (x == 74 || x == 75)
                            {
                                scene->setCoffre(map - 45, 24, 1);
                                ouvrePorte(74, 53, 4);
                            }
                        }
                        else if (val == 4854)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 16, 1);
                            ouvrePorte(6, 51, 4);
                        }
                        else if (val == 4855)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 25, 1);
                            ouvrePorte(269, 6, 4);
                        }
                        break;
                    case 51:
                        if (val == 5030 || val == 5031)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 11, 1);
                            ouvrePorte(309, 73, 2);
                        }
                        if (val == 5032 || val == 5033)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 10, 1);
                            ouvrePorte(118, 81, 3);
                        }
                        break;
                    case 53:
                        if (val == 5503)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 12, 1);
                            ouvrePorte(229, 6, 4);
                        }
                        break;
                    case 55:
                        if (val == 5922)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 12, 1);
                            ouvrePorte(69, 13, 2);
                        }
                        break;
                    case 57:
                        if (val == 6364 || val == 6365)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            scene->setCoffre(map - 45, 10, 1);
                            ouvrePorte(109, 163, 2);
                        }
                        break;
                    case 58:
                        if (val == 6537 || val == 6538)
                        {
                            AudioManager::getInstance()->playSound(TS_SURPRISE);
                            if (x < 70)
                            {
                                scene->setCoffre(map - 45, 14, 1);
                                ouvrePorte(18, 66, 3);
                            }
                            else
                            {
                                scene->setCoffre(map - 45, 15, 1);
                                ouvrePorte(118, 66, 3);
                            }
                        }
                        break;
                    }
                }
                else if (map == 155 && (val == 3696 || val == 3697))
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    if (y < 75)
                    {
                        scene->setCoffre(0, 33, 1);
                        ouvrePorte(9, 58, 0);
                    }
                    else
                    {
                        scene->setCoffre(0, 34, 1);
                        ouvrePorte(9, 88, 0);
                    }
                }
                else if (map == 156)
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    if (val == 6936 || val == 6937)
                    {
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                        if (x < 140)
                        {
                            scene->setCoffre(16, 34, 1);
                            ouvrePorte(129, 283, 2);
                        }
                        else
                        {
                            scene->setCoffre(16, 36, 1);
                            ouvrePorte(169, 268, 2);
                        }
                    }
                    else if (val == 6938 || val == 6939)
                    {
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                        if (x < 180)
                        {
                            scene->setCoffre(16, 35, 1);
                            ouvrePorte(158, 171, 3);
                        }
                        else
                        {
                            scene->setCoffre(16, 37, 1);
                            ouvrePorte(218, 81, 3);
                        }
                    }
                    else if (val == 6989)
                    {
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                        if (x < 220)
                        {
                            scene->setCoffre(16, 38, 1);
                            ouvrePorte(209, 157, 4);
                        }
                        else
                        {
                            scene->setCoffre(16, 39, 1);
                            ouvrePorte(289, 157, 4);
                        }
                    }
                }
            }
            if (type == TA_MARTEAU)
            {
                if (val == 311)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 312, HERBE);
                }
                else if (val == 705)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 706, SABLE);
                }
                else if (val == 905)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 906, HERBE);
                }
                else if (val == 2551)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 2552, NEIGE);
                }
                else if (val == 2930 || val == 2931 || val == 2932)
                {
                    addEffect(new Debris(121 * 16 + 8, 34 * 16 + 8, N, 2));
                    addEffect(new Debris(122 * 16 + 8, 35 * 16 + 8, N, 2));
                    addEffect(new Debris(123 * 16 + 8, 34 * 16 + 8, N, 2));
                    AudioManager::getInstance()->playSound(TS_BREAK);
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    scene->setCoffre(0, 6, 1);
                    ouvrePorte(120, 33, 0);
                }
                else if (val == 4876)
                {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 4875, PIERRE);
                }
            }
            if (effect == TE_FEU)
            {
                if (val == 1935)
                {
                    sol[x][y] = 1936;
                    allumeTorche(x, y);
                }
                else if (val == 5694 && map == 54)
                {
                    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(map - 45, 22, 1);
                    ouvrePorte(109, 21, 4);
                    AudioManager::getInstance()->playSound(TS_PLOUF);
                    addEffect(new Plouf(109 * 16 + 8, 21 * 16 + 8));
                }
            }
        }
    }
    return result;
}

bool Map::testGemmeForce(int x, int y)
{
    if (map == 26 && x == 46 && y == 31)
    {
        AudioManager::getInstance()->playSound(TS_SURPRISE);
        ouvrePorte(46, 31, 0);
    }
    if (map == 27)
    {
        // stones
        if ((x == 42 && y == 25 && stones == 0) || (x == 68 && y == 32 && stones == 1) || (x == 48 && y == 25 && stones == 2) || (x == 58 && y == 32 && stones == 3) || (x == 41 && y == 41 && stones == 4))
        {
            stones++;
            return true;
        }
        if (x == 51 && y == 49 && stones == 5)
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            ouvrePorte(51, 49, 0);
            return true;
        }
    }

    Inventory *inventory = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getInventory();

    switch (map)
    {
    case 1:
        if (x == 7 && y == 54 && !inventory->hasGemmeForce(6))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 6));
            return true;
        }
        if (x == 18 && y == 15 && !inventory->hasGemmeForce(7))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 7));
            return true;
        }
        if (x == 66 && y == 5 && !inventory->hasGemmeForce(8))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 8));
            return true;
        }
        break;
    case 2:
        if (x == 53 && y == 41 && !inventory->hasGemmeForce(16))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 16));
            return true;
        }
        if (x == 7 && y == 53 && !inventory->hasGemmeForce(17))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 17));
            return true;
        }
        break;
    case 3:
        if (x == 65 && y == 7 && !inventory->hasGemmeForce(21))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 21));
            return true;
        }
        if (x == 76 && y == 82 && !inventory->hasGemmeForce(22))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 22));
            return true;
        }
        if (x == 24 && y == 30 && !inventory->hasGemmeForce(23))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 23));
            return true;
        }
        break;
    case 4:
        if (x == 3 && y == 44 && !inventory->hasGemmeForce(32))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 32));
            return true;
        }
        if (x == 62 && y == 5 && !inventory->hasGemmeForce(33))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 33));
            return true;
        }
        break;
    case 5:
        if (x == 35 && y == 42 && !inventory->hasGemmeForce(40))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 40));
            return true;
        }
        if (x == 56 && y == 50 && !inventory->hasGemmeForce(41))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 41));
            return true;
        }
        break;
    case 6:
        if (x == 55 && y == 55 && !inventory->hasGemmeForce(54))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 54));
            return true;
        }
        break;
    case 7:
        if (x == 120 && y == 39 && !inventory->hasGemmeForce(62))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 62));
            return true;
        }
        if (x == 10 && y == 21 && !inventory->hasGemmeForce(63))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 63));
            return true;
        }
        if (x == 134 && y == 17 && !inventory->hasGemmeForce(64))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 64));
            return true;
        }
        break;
    case 8:
        if (x == 48 && y == 7 && !inventory->hasGemmeForce(71))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 71));
            return true;
        }
        if (x == 26 && y == 16 && !inventory->hasGemmeForce(72))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 72));
            return true;
        }
        if (x == 20 && y == 36 && !inventory->hasGemmeForce(73))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 73));
            return true;
        }
        break;
    case 9:
        if (x == 57 && y == 3 && !inventory->hasGemmeForce(82))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 82));
            return true;
        }
        if (x == 43 && y == 52 && !inventory->hasGemmeForce(83))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 83));
            return true;
        }
        if (x == 97 && y == 21 && !inventory->hasGemmeForce(84))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 84));
            return true;
        }
        break;
    case 10:
        if (x == 49 && y == 55 && !inventory->hasGemmeForce(89))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 89));
            return true;
        }
        if (x == 66 && y == 28 && !inventory->hasGemmeForce(90))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 90));
            return true;
        }
        break;
    case 11:
        if (x == 46 && y == 25 && !inventory->hasGemmeForce(102))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 102));
            return true;
        }
        if (x == 115 && y == 31 && !inventory->hasGemmeForce(103))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 103));
            return true;
        }
        if (x == 86 && y == 5 && !inventory->hasGemmeForce(104))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 104));
            return true;
        }
        break;
    case 12:
        if (x == 135 && y == 56 && !inventory->hasGemmeForce(111))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 111));
            return true;
        }
        if (x == 111 && y == 72 && !inventory->hasGemmeForce(112))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 112));
            return true;
        }
        if (x == 27 && y == 66 && !inventory->hasGemmeForce(113))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 113));
            return true;
        }
        break;
    case 13:
        if (x == 9 && y == 18 && !inventory->hasGemmeForce(119))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 119));
            return true;
        }
        if (x == 28 && y == 10 && !inventory->hasGemmeForce(120))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 120));
            return true;
        }
        if (x == 58 && y == 53 && !inventory->hasGemmeForce(121))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 121));
            return true;
        }
        break;
    case 14:
        if (x == 26 && y == 39 && !inventory->hasGemmeForce(128))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 128));
            return true;
        }
        if (x == 34 && y == 17 && !inventory->hasGemmeForce(129))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 129));
            return true;
        }
        if (x == 40 && y == 28 && !inventory->hasGemmeForce(130))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 130));
            return true;
        }
        break;
    case 15:
        if (x == 6 && y == 9 && !inventory->hasGemmeForce(141))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 141));
            return true;
        }
        if (x == 9 && y == 39 && !inventory->hasGemmeForce(142))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 142));
            return true;
        }
        if (x == 20 && y == 46 && !inventory->hasGemmeForce(143))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 143));
            return true;
        }
        if (x == 22 && y == 18 && !inventory->hasGemmeForce(144))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 144));
            return true;
        }
        if (x == 110 && y == 33 && !inventory->hasGemmeForce(145))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 145));
            return true;
        }
        break;
    case 16:
        if (x == 75 && y == 30 && !inventory->hasGemmeForce(0))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 0));
            return true;
        }
        if (x == 27 && y == 34 && !inventory->hasGemmeForce(1))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 1));
            return true;
        }
        if (x == 24 && y == 44 && !inventory->hasGemmeForce(2))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 2));
            return true;
        }
        break;
    case 17:
        if (x == 57 && y == 4 && !inventory->hasGemmeForce(9))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 9));
            return true;
        }
        if (x == 4 && y == 52 && !inventory->hasGemmeForce(10))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 10));
            return true;
        }
        break;
    case 18:
        if (x == 66 && y == 14 && !inventory->hasGemmeForce(18))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 18));
            return true;
        }
        if (x == 11 && y == 36 && !inventory->hasGemmeForce(24))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 24));
            return true;
        }
        break;
    case 19:
        if (x == 9 && y == 27 && !inventory->hasGemmeForce(26))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 26));
            return true;
        }
        if (x == 71 && y == 18 && !inventory->hasGemmeForce(27))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 27));
            return true;
        }
        if (x == 26 && y == 33 && !inventory->hasGemmeForce(28))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 28));
            return true;
        }
        break;
    case 20:
        if (x == 2 && y == 77 && !inventory->hasGemmeForce(34))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 34));
            return true;
        }
        if (x == 44 && y == 4 && !inventory->hasGemmeForce(35))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 35));
            return true;
        }
        if (x == 10 && y == 16 && !inventory->hasGemmeForce(36))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 36));
            return true;
        }
        break;
    case 21:
        if (x == 25 && y == 58 && !inventory->hasGemmeForce(42))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 42));
            return true;
        }
        if (x == 50 && y == 55 && !inventory->hasGemmeForce(43))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 43));
            return true;
        }
        if (x == 54 && y == 23 && !inventory->hasGemmeForce(44))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 44));
            return true;
        }
        if (x == 23 && y == 43 && !inventory->hasGemmeForce(45))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 45));
            return true;
        }
        if (x == 9 && y == 66 && !inventory->hasGemmeForce(46))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 46));
            return true;
        }
        break;
    case 22:
        if (x == 10 && y == 29 && !inventory->hasGemmeForce(55))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 55));
            return true;
        }
        if (x == 53 && y == 3 && !inventory->hasGemmeForce(56))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 56));
            return true;
        }
        if (x == 118 && y == 22 && !inventory->hasGemmeForce(57))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 57));
            return true;
        }
        break;
    case 23:
        if (x == 69 && y == 30 && !inventory->hasGemmeForce(65))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 65));
            return true;
        }
        if (x == 15 && y == 16 && !inventory->hasGemmeForce(66))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 66));
            return true;
        }
        if (x == 51 && y == 26 && !inventory->hasGemmeForce(67))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 67));
            return true;
        }
        break;
    case 24:
        if (x == 13 && y == 56 && !inventory->hasGemmeForce(74))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 74));
            return true;
        }
        if (x == 59 && y == 3 && !inventory->hasGemmeForce(75))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 75));
            return true;
        }
        if (x == 58 && y == 40 && !inventory->hasGemmeForce(76))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 76));
            return true;
        }
        if (x == 109 && y == 38 && !inventory->hasGemmeForce(77))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 77));
            return true;
        }
        break;
    case 25:
        if (x == 72 && y == 36 && !inventory->hasGemmeForce(85))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 85));
            return true;
        }
        if (x == 24 && y == 72 && !inventory->hasGemmeForce(86))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 86));
            return true;
        }
        break;
    case 26:
        if (x == 4 && y == 32 && !inventory->hasGemmeForce(94))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 94));
            return true;
        }
        if (x == 50 && y == 68 && !inventory->hasGemmeForce(95))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 95));
            return true;
        }
        break;
    case 27:
        if (x == 124 && y == 29 && !inventory->hasGemmeForce(105))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 105));
            return true;
        }
        if (x == 103 && y == 65 && !inventory->hasGemmeForce(106))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 106));
            return true;
        }
        if (x == 70 && y == 55 && !inventory->hasGemmeForce(107))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 107));
            return true;
        }
        break;
    case 28:
        if (x == 6 && y == 65 && !inventory->hasGemmeForce(114))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 114));
            return true;
        }
        if (x == 69 && y == 10 && !inventory->hasGemmeForce(115))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 115));
            return true;
        }
        if (x == 10 && y == 5 && !inventory->hasGemmeForce(116))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 116));
            return true;
        }
        break;
    case 29:
        if (x == 39 && y == 28 && !inventory->hasGemmeForce(122))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 122));
            return true;
        }
        if (x == 46 && y == 12 && !inventory->hasGemmeForce(123))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 123));
            return true;
        }
        if (x == 40 && y == 65 && !inventory->hasGemmeForce(124))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 124));
            return true;
        }
        break;
    case 30:
        if (x == 71 && y == 45 && !inventory->hasGemmeForce(131))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 131));
            return true;
        }
        if (x == 97 && y == 29 && !inventory->hasGemmeForce(132))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 132));
            return true;
        }
        if (x == 101 && y == 41 && !inventory->hasGemmeForce(133))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 133));
            return true;
        }
        if (x == 40 && y == 46 && !inventory->hasGemmeForce(134))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 134));
            return true;
        }
        if (x == 19 && y == 28 && !inventory->hasGemmeForce(135))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 135));
            return true;
        }
        break;
    case 31:
        if (x == 22 && y == 17 && !inventory->hasGemmeForce(4))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 4));
            return true;
        }
        if (x == 65 && y == 36 && !inventory->hasGemmeForce(5))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 5));
            return true;
        }
        break;
    case 32:
        if (x == 18 && y == 5 && !inventory->hasGemmeForce(12))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 12));
            return true;
        }
        if (x == 57 && y == 3 && !inventory->hasGemmeForce(13))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 13));
            return true;
        }
        if (x == 7 && y == 21 && !inventory->hasGemmeForce(14))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 14));
            return true;
        }
        break;
    case 33:
        if (x == 24 && y == 59 && !inventory->hasGemmeForce(20))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 20));
            return true;
        }
        break;
    case 34:
        if (x == 70 && y == 54 && !inventory->hasGemmeForce(29))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 29));
            return true;
        }
        if (x == 76 && y == 39 && !inventory->hasGemmeForce(30))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 30));
            return true;
        }
        if (x == 9 && y == 21 && !inventory->hasGemmeForce(31))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 31));
            return true;
        }
        break;
    case 35:
        if (x == 4 && y == 78 && !inventory->hasGemmeForce(37))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 37));
            return true;
        }
        if (x == 26 && y == 46 && !inventory->hasGemmeForce(38))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 38));
            return true;
        }
        break;
    case 36:
        if (x == 30 && y == 54 && !inventory->hasGemmeForce(48))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 48));
            return true;
        }
        if (x == 28 && y == 79 && !inventory->hasGemmeForce(49))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 49));
            return true;
        }
        if (x == 77 && y == 76 && !inventory->hasGemmeForce(50))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 50));
            return true;
        }
        if (x == 37 && y == 45 && !inventory->hasGemmeForce(51))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 51));
            return true;
        }
        if (x == 26 && y == 15 && !inventory->hasGemmeForce(52))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 52));
            return true;
        }
        break;
    case 37:
        if (x == 79 && y == 7 && !inventory->hasGemmeForce(58))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 58));
            return true;
        }
        if (x == 10 && y == 29 && !inventory->hasGemmeForce(59))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 59));
            return true;
        }
        if (x == 119 && y == 13 && !inventory->hasGemmeForce(60))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 60));
            return true;
        }
        if (x == 51 && y == 40 && !inventory->hasGemmeForce(61))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 61));
            return true;
        }
        break;
    case 38:
        if (x == 71 && y == 38 && !inventory->hasGemmeForce(68))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 68));
            return true;
        }
        if (x == 66 && y == 17 && !inventory->hasGemmeForce(69))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 69));
            return true;
        }
        if (x == 36 && y == 19 && !inventory->hasGemmeForce(70))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 70));
            return true;
        }
        break;
    case 39:
        if (x == 5 && y == 11 && !inventory->hasGemmeForce(78))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 78));
            return true;
        }
        if (x == 61 && y == 3 && !inventory->hasGemmeForce(79))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 79));
            return true;
        }
        if (x == 65 && y == 36 && !inventory->hasGemmeForce(80))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 80));
            return true;
        }
        if (x == 114 && y == 5 && !inventory->hasGemmeForce(81))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 81));
            return true;
        }
        break;
    case 40:
        if (x == 38 && y == 28 && !inventory->hasGemmeForce(88))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 88));
            return true;
        }
        break;
    case 41:
        if (x == 85 && y == 19 && !inventory->hasGemmeForce(97))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 97));
            return true;
        }
        if (x == 10 && y == 42 && !inventory->hasGemmeForce(98))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 98));
            return true;
        }
        if (x == 14 && y == 72 && !inventory->hasGemmeForce(99))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 99));
            return true;
        }
        if (x == 55 && y == 25 && !inventory->hasGemmeForce(101))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 101));
            return true;
        }
        break;
    case 42:
        if (x == 106 && y == 65 && !inventory->hasGemmeForce(108))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 108));
            return true;
        }
        if (x == 22 && y == 51 && !inventory->hasGemmeForce(109))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 109));
            return true;
        }
        if (x == 85 && y == 68 && !inventory->hasGemmeForce(110))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 110));
            return true;
        }
        break;
    case 43:
        if (x == 70 && y == 61 && !inventory->hasGemmeForce(117))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 117));
            return true;
        }
        if (x == 9 && y == 20 && !inventory->hasGemmeForce(118))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 118));
            return true;
        }
        break;
    case 44:
        if (x == 57 && y == 69 && !inventory->hasGemmeForce(125))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 125));
            return true;
        }
        if (x == 7 && y == 61 && !inventory->hasGemmeForce(126))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 126));
            return true;
        }
        if (x == 14 && y == 69 && !inventory->hasGemmeForce(127))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 127));
            return true;
        }
        break;
    case 45:
        if (x == 130 && y == 47 && !inventory->hasGemmeForce(136))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 136));
            return true;
        }
        if (x == 104 && y == 41 && !inventory->hasGemmeForce(137))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 137));
            return true;
        }
        if (x == 13 && y == 28 && !inventory->hasGemmeForce(139))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 139));
            return true;
        }
        if (x == 26 && y == 27 && !inventory->hasGemmeForce(140))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 140));
            return true;
        }
        break;
    case 46:
        if (x == 280 && y == 19 && !inventory->hasGemmeForce(185))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 185));
            return true;
        }
        break;
    case 47:
        if (x == 296 && y == 55 && !inventory->hasGemmeForce(186))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 186));
            return true;
        }
        break;
    case 48:
        if (x == 290 && y == 6 && !inventory->hasGemmeForce(187))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 187));
            return true;
        }
        break;
    case 49:
        if (x == 106 && y == 74 && !inventory->hasGemmeForce(188))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 188));
            return true;
        }
        break;
    case 50:
        if (x == 194 && y == 81 && !inventory->hasGemmeForce(189))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 189));
            return true;
        }
        break;
    case 51:
        if (x == 284 && y == 20 && !inventory->hasGemmeForce(190))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 190));
            return true;
        }
        break;
    case 52:
        if (x == 263 && y == 51 && !inventory->hasGemmeForce(191))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 191));
            return true;
        }
        break;
    case 53:
        if (x == 148 && y == 6 && !inventory->hasGemmeForce(192))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 192));
            return true;
        }
        break;
    case 54:
        if (x == 159 && y == 87 && !inventory->hasGemmeForce(193))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 193));
            return true;
        }
        break;
    case 55:
        if (x == 81 && y == 186 && !inventory->hasGemmeForce(194))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 194));
            return true;
        }
        break;
    case 57:
        if (x == 4 && y == 27 && !inventory->hasGemmeForce(197))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 197));
            return true;
        }
        if (x == 115 && y == 32 && !inventory->hasGemmeForce(198))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 198));
            return true;
        }
        break;
    case 58:
        if (x == 77 && y == 27 && !inventory->hasGemmeForce(199))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 199));
            return true;
        }
        break;
    case 63:
        if (x == 35 && y == 12 && !inventory->hasGemmeForce(146))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 146));
            return true;
        }
        break;
    case 66:
        if (x == 5 && y == 8 && !inventory->hasGemmeForce(148))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 148));
            return true;
        }
        break;
    case 67:
        if (x == 15 && y == 25 && !inventory->hasGemmeForce(149))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 149));
            return true;
        }
        break;
    case 68:
        if (x == 43 && y == 16 && !inventory->hasGemmeForce(150))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 150));
            return true;
        }
        if (x == 15 && y == 4 && !inventory->hasGemmeForce(151))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 151));
            return true;
        }
        if (x == 4 && y == 35 && !inventory->hasGemmeForce(152))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 152));
            return true;
        }
        break;
    case 76:
        if (x == 10 && y == 4 && !inventory->hasGemmeForce(153))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 153));
            return true;
        }
        break;
    case 77:
        if (x == 8 && y == 2 && !inventory->hasGemmeForce(154))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 154));
            return true;
        }
        break;
    case 78:
        if (x == 27 && y == 7 && !inventory->hasGemmeForce(155))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 155));
            return true;
        }
        if (x == 32 && y == 7 && !inventory->hasGemmeForce(156))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 156));
            return true;
        }
        break;
    case 80:
        if (x == 4 && y == 2 && !inventory->hasGemmeForce(157))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 157));
            return true;
        }
        break;
    case 85:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(158))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 158));
            return true;
        }
        break;
    case 88:
        if (x == 4 && y == 8 && !inventory->hasGemmeForce(159))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 159));
            return true;
        }
        break;
    case 90:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(163))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 163));
            return true;
        }
        break;
    case 91:
        if (x == 6 && y == 6 && !inventory->hasGemmeForce(164))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 164));
            return true;
        }
        break;
    case 92:
        if (x == 4 && y == 4 && !inventory->hasGemmeForce(165))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 165));
            return true;
        }
        break;
    case 95:
        if (x == 15 && y == 12 && !inventory->hasGemmeForce(166))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 166));
            return true;
        }
        break;
    case 101:
        if (x == 15 && y == 4 && !inventory->hasGemmeForce(167))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 167));
            return true;
        }
        break;
    case 102:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(168))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 168));
            return true;
        }
        break;
    case 103:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(169))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 169));
            return true;
        }
        break;
    case 113:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(170))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 170));
            return true;
        }
        break;
    case 116:
        if (x == 15 && y == 12 && !inventory->hasGemmeForce(172))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 172));
            return true;
        }
        break;
    case 120:
        if (x == 4 && y == 4 && !inventory->hasGemmeForce(174))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 174));
            return true;
        }
        break;
    case 127:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(175))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 175));
            return true;
        }
        break;
    case 130:
        if (x == 15 && y == 12 && !inventory->hasGemmeForce(176))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 176));
            return true;
        }
        break;
    case 135:
        if (x == 15 && y == 4 && !inventory->hasGemmeForce(177))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 177));
            return true;
        }
        break;
    case 139:
        if (x == 15 && y == 12 && !inventory->hasGemmeForce(179))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 179));
            return true;
        }
        break;
    case 140:
        if (x == 34 && y == 5 && !inventory->hasGemmeForce(180))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 180));
            return true;
        }
        break;
    case 141:
        if (x == 4 && y == 4 && !inventory->hasGemmeForce(181))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 181));
            return true;
        }
        break;
    case 147:
        if (x == 4 && y == 12 && !inventory->hasGemmeForce(183))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 183));
            return true;
        }
        break;
    case 154:
        if (x == 4 && y == 19 && !inventory->hasGemmeForce(184))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 184));
            return true;
        }
        break;
    case 155:
        if (x == 47 && y == 92 && !inventory->hasGemmeForce(196))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 196));
            return true;
        }
        if (x == 144 && y == 34 && !inventory->hasGemmeForce(147))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 147));
            return true;
        }
        if (x == 146 && y == 34 && !inventory->hasGemmeForce(171))
        {
            addItem(ItemHelper::getInstance()->createItem(TI_GEMME_FORCE, x * 16 + 8, y * 16 + 8, 171));
            return true;
        }
        break;
    }

    return false;
}

int Map::nbJarres()
{
    List toList;
    objects->get(&bounds, &toList);

    int i = 0;

    toList.iterateOnFirst();
    while (toList.hasNext())
    {
        Jarre *jarre = dynamic_cast<Jarre *>(toList.getNext());
        if (jarre != 0)
        {
            i++;
        }
    }
    return i;
}

void Map::persistJarres(int nb)
{
    if (nb > 6)
        nb = 6;
    List toList;
    objects->get(&bounds, &toList);

    int i = 0;

    toList.iterateOnFirst();
    while (toList.hasNext() && i < nb)
    {
        Jarre *jarre = dynamic_cast<Jarre *>(toList.getNext());
        if (jarre != 0)
        {
            jarres[i++] = jarre;
        }
    }
}

void Map::resetRandomJarre(int nb)
{
    if (nb > 6)
        nb = 6;
    int randomValue = ((int)rand()) % nb;
    Jarre *jarre = dynamic_cast<Jarre *>(jarres[randomValue]);
    if (jarre != 0)
    {
        jarre->reset();
        addEffect(new FumeeBlanche(jarre->getX() + 8, jarre->getY() + 8, 4));
        AudioManager::getInstance()->playSound(TS_CAPE_ON);
    }
}

void Map::pickUpItems(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive())
        {
            i->action();
        }
    }
}

Item *Map::getItem(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isReady() && i->isAlive() && i->isPickable())
        {
            return i;
        }
    }
    return 0;
}

void Map::killItems(BoundingBox *box)
{
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Item *i = (Item *)toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive())
        {
            i->killNode();
        }
    }
}

void Map::killEnnemis(BoundingBox *box, bool withEffect)
{
    List toKill;
    ennemis->get(box, &toKill);

    toKill.iterateOnFirst();
    while (toKill.hasNext())
    {
        Ennemi *e = (Ennemi *)toKill.getNext();
        if (e->getBoundingBox()->intersect(box) && e->isAlive() && e->getType() != 141)
        {
            e->killNode();
            if (withEffect)
            {
                BoundingBox *bb = e->getBoundingBox();
                addEffect(new FumeeBlanche(bb->getX() + bb->getW() / 2, bb->getY() + bb->getH() / 2));
            }
        }
    }
}

Portable *Map::pickUpObject(BoundingBox *box)
{

    List toPickUp;
    objects->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext())
    {
        Portable *p = dynamic_cast<Portable *>(toPickUp.getNext());
        if (p != 0 && p->isCarriable() && p->getHandableBox()->intersect(box))
        {
            return p;
        }
    }

    return 0;
}

void Map::pushObject(BoundingBox *box, Direction dir)
{
    List toPush;
    objects->get(box, &toPush);

    toPush.iterateOnFirst();
    while (toPush.hasNext())
    {
        Poussable *p = dynamic_cast<Poussable *>(toPush.getNext());
        if (p != 0)
        {
            p->pousse(dir);
            return;
        }
    }
}

bool Map::tryToTalk(BoundingBox *box, Direction dir)
{
    List toTalk;

    // try to interact with objects or npcs
    objects->get(box, &toTalk);

    toTalk.iterateOnFirst();
    while (toTalk.hasNext())
    {
        Object *p = dynamic_cast<Object *>(toTalk.getNext());
        if (p != 0 && p->action(dir))
        {
            return true;
        }
    }
    return false;
}

bool Map::testTransition(int x, int y)
{
    if (map > 45)
        return false;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    if (map == 3 && scene->getAvancement() < AV_INFO_PASSE_OK)
    {
        if (x <= 8)
        {
            link->setX(link->getX() + 4);
            link->setDirection(E);
            MainController::getInstance()->getGameController()->displayText(407);
            return false;
        }
        else if (y <= 0)
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(407);
            return false;
        }
        else if (x >= w - 24)
        {
            link->setX(link->getX() - 4);
            link->setDirection(W);
            MainController::getInstance()->getGameController()->displayText(407);
            return false;
        }
        else if (y >= h - 32)
        {
            link->setY(link->getY() - 4);
            link->setDirection(N);
            MainController::getInstance()->getGameController()->displayText(407);
            return false;
        }
    }
    else if (map == 4)
    {
        if ((x / 16 == 39 || x / 16 == 40) && y / 16 == 36 && link->getInventory()->nbCristaux() == 7 && scene->getAvancement() < AV_TEMPLE_DEESSES_APPARU)
        {
            AudioManager::getInstance()->stopMusic();
            MainController::getInstance()->getGameController()->displayText(409);
            return false;
        }
    }
    else if (map == 16 && y >= 44 * 16 + 8 && scene->getAvancement() < AV_GARDE_VU)
    {
        link->setY(link->getY() - 4);
        link->setDirection(N);
        MainController::getInstance()->getGameController()->displayText(236);
        return false;
    }
    else if (map == 18 && y <= 5 * 16 + 8 && scene->getAvancement() == AV_PLANCHES_TROUVEES)
    {
        MainController::getInstance()->getGameController()->displayText(253);
        return false;
    }
    else if (map == 21 && x <= 8 && scene->getAvancement() < AV_STELE_LUE)
    {
        link->setX(link->getX() + 4);
        link->setDirection(E);
        MainController::getInstance()->getGameController()->displayText(413);
        return false;
    }
    else if (map == 26 && !link->getInventory()->hasObject(PALMES) && !testBarque(x, y))
    {
        return false;
    }
    return ((x <= 8 && map != 1 && map != 16 && map != 31 && map != 12 && map != 27 && map != 42 && map != 13 && map != 28 && map != 43 && map != 15 && map != 30 && map != 45) ||
            (y <= 0 && map != 7 && map != 22 && map != 37 && map != 8 && map != 23 && map != 38 && map != 15 && map != 30 && map != 45) ||
            (x >= w - 24 && map != 6 && map != 21 && map != 36 && map != 7 && map != 22 && map != 37 && map != 9 && map != 24 && map != 39 && map != 10 && map != 25 && map != 40) ||
            (y >= h - 32 && map != 1 && map != 16 && map != 31 && map != 10 && map != 25 && map != 40 && map != 11 && map != 26 && map != 41 && map != 12 && map != 27 && map != 42));
}

bool Map::testBarque(int x, int y)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (scene->getAvancement() < AV_BARQUE_LOUEE)
    {
        return true;
    }
    int b = scene->getCoffre(0, 5);

    Link *link = scene->getLink();
    if (link->getAnimation() == BARQUE)
    {
        if (x <= 8)
        {
            link->setX(link->getX() + 4);
            link->setDirection(E);
            MainController::getInstance()->getGameController()->displayText(492);
            return false;
        }
        if (y <= 0)
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(492);
            return false;
        }
        if (x >= w - 24)
        {
            link->setX(link->getX() - 4);
            link->setDirection(W);
            MainController::getInstance()->getGameController()->displayText(492);
            return false;
        }
    }
    else if (link->getAnimation() != BARQUE_IDLE)
    {
        if ((x == 13 * 16 + 8 && y == 17 * 16 + 8 && b == 5) || (x == 32 * 16 + 8 && y == 56 * 16 + 8 && b == 4) || (x == 50 * 16 + 8 && y == 35 * 16 + 8 && b == 3) || (x == 76 * 16 + 8 && y == 53 * 16 + 8 && b == 2) || (x == 105 * 16 + 8 && y == 28 * 16 + 8 && b == 1) || (x == 118 * 16 + 8 && y == 47 * 16 + 8 && b == 0))
        {
            link->setAnimation(BARQUE);
            barque(false);
        }
    }

    return true;
}

bool Map::testInnerTransition(int x, int y)
{
    if (map < 46)
        return false;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (map == 55 && bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
        return false;
    if (map == 57 && scene->getAvancement() < AV_PARLE_ZELDA_PALAIS && bounds.getX() == 320 * 3 && bounds.getY() == 240 && y >= bounds.getY() + bounds.getH() - 32)
    {
        Link *link = scene->getLink();
        link->setY(link->getY() - 4);
        link->setDirection(N);
        MainController::getInstance()->getGameController()->displayText(1311);
        return false;
    }
    if (map == 60 && bounds.getX() == 320 * 3 && bounds.getY() == 240 * 5 && x >= bounds.getX() + bounds.getW() - 24)
    {
        Link *link = scene->getLink();
        link->setX(link->getX() - 4);
        link->setDirection(W);
        MainController::getInstance()->getGameController()->displayText(1662);
        return false;
    }
    return ((x <= bounds.getX() + 8 && bounds.getX() > 0) ||
            (y <= bounds.getY() && bounds.getY() > 0) ||
            (x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) ||
            (y >= bounds.getY() + bounds.getH() - 32 && bounds.getY() + bounds.getH() < h));
}

bool Map::testTeleport(int x, int y)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    TeleportController *teleport = MainController::getInstance()->getGameController()->getTeleportController();

    switch (map)
    {
    case 1:
        if (x == 59 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(75, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 40 * 16 + 8)
        {
            teleport->setTeleport(126, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 3:
        if (x == 63 * 16 + 8 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(128, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 43 * 16 + 8)
        {
            teleport->setTeleport(129, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(130, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(131, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(132, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(133, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(134, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(135, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 17 * 16 + 8 && y == 37 * 16 + 8)
        {
            teleport->setTeleport(136, 9 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        break;
    case 4:
        if (scene->getAvancement() >= AV_TEMPLE_DEESSES_APPARU)
        {
            if (x >= 39 * 16 && x <= 40 * 16 && y == 34 * 16 + 8)
            {
                teleport->setTeleport(56, 69 * 16 + 8, 57 * 16, N, false, true);
                return true;
            }
            if (x >= 39 * 16 && x <= 40 * 16 && y == 29 * 16 + 8)
            {
                teleport->setTeleport(56, 169 * 16 + 8, 42 * 16, N, false, true);
                return true;
            }
            // escaliers
            if (x == 53 * 16 + 8 && y == 26 * 16)
            {
                teleport->setTeleport(56, 109 * 16 + 8, 7 * 16 + 8, S, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
        }
        break;
    case 6:
        if (x == 65 * 16 + 8 && y == 80 * 16 + 8)
        {
            teleport->setTeleport(77, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(78, 69 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 27 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(78, 109 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 7:
        if (x == 84 * 16 && y == 7 * 16 + 8)
        {
            teleport->setTeleport(53, 29 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x == 10 * 16 + 8 && y == 4 * 16 + 8)
        {
            teleport->setTeleport(74, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 8:
        if (x == 39 * 16 + 8 && y == 11 * 16 + 8)
        {
            teleport->setTeleport(124, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 9:
        if (x == 113 * 16 + 8 && y == 35 * 16 + 8)
        {
            teleport->setTeleport(154, 9 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        if (x == 129 * 16 + 8 && y == 38 * 16)
        {
            teleport->setTeleport(154, 69 * 16 + 8, 22 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 10:
        if (x == 37 * 16 + 8 && y == 8 * 16 + 8)
        {
            teleport->setTeleport(137, 9 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        if (x == 31 * 16 + 8 && y == 23 * 16 + 8)
        {
            teleport->setTeleport(138, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 43 * 16 + 8 && y == 25 * 16 + 8)
        {
            teleport->setTeleport(139, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 30 * 16 + 8 && y == 38 * 16 + 8)
        {
            teleport->setTeleport(140, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 47 * 16 + 8 && y == 41 * 16 + 8)
        {
            teleport->setTeleport(141, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 62 * 16 + 8 && y == 33 * 16 + 8)
        {
            teleport->setTeleport(142, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 65 * 16 + 8 && y == 48 * 16 + 8)
        {
            teleport->setTeleport(143, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 11:
        if (x == 72 * 16 + 8 && y == 52 * 16)
        {
            teleport->setTeleport(54, 9 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 72 * 16 + 8 && y == 42 * 16 + 8)
        {
            teleport->setTeleport(127, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 12:
        if (x >= 15 * 16 && x <= 16 * 16 && y == 21 * 16 + 8)
        {
            teleport->setTeleport(52, 129 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        if (x == 84 * 16 + 8 && y == 56 * 16 + 8)
        {
            teleport->setTeleport(76, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 13:
        if (x == 15 * 16 + 8 && y == 15 * 16 + 8)
        {
            teleport->setTeleport(144, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 21 * 16 + 8 && y == 15 * 16 + 8)
        {
            teleport->setTeleport(144, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 18 * 16 + 8 && y == 35 * 16 + 8)
        {
            teleport->setTeleport(145, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 13 * 16 + 8 && y == 47 * 16 + 8)
        {
            teleport->setTeleport(146, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 42 * 16 + 8 && y == 21 * 16 + 8)
        {
            teleport->setTeleport(147, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 61 * 16 + 8 && y == 34 * 16 + 8)
        {
            teleport->setTeleport(148, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 61 * 16 + 8 && y == 44 * 16 + 8)
        {
            teleport->setTeleport(149, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 14:
        if (x == 18 * 16 + 8 && y == 41 * 16 + 8)
        {
            teleport->setTeleport(125, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x >= 34 * 16 && x <= 35 * 16 && y == 52 * 16 + 8)
        {
            teleport->setTeleport(153, 29 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        break;
    case 15:
        if (x == 122 * 16 && y == 34 * 16)
        {
            teleport->setTeleport(55, 69 * 16 + 8, 222 * 16, N, false, true);
            return true;
        }
        break;
    case 16:
        if (x == 59 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(61, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 40 * 16 + 8)
        {
            teleport->setTeleport(79, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 18:
        if (x == 17 * 16 + 8 && y == 37 * 16 + 8)
        {
            teleport->setTeleport(80, 9 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        if (x == 17 * 16 + 8 && y == 31 * 16 + 8)
        {
            teleport->setTeleport(80, 9 * 16 + 8, 16, S, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(81, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 43 * 16 + 8)
        {
            teleport->setTeleport(82, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(83, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(84, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(85, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(86, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(87, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(88, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(89, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 19:
        if (x >= 39 * 16 && x <= 40 * 16 && y == 34 * 16 + 8)
        {
            teleport->setTeleport(57, 69 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x >= 39 * 16 && x <= 40 * 16 && y == 29 * 16 + 8)
        {
            teleport->setTeleport(57, 169 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 53 * 16 + 8 && y == 26 * 16)
        {
            teleport->setTeleport(57, 109 * 16 + 8, 7 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 68 * 16 + 8 && y == 48 * 16)
        {
            teleport->setTeleport(57, 149 * 16 + 8, 202 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 21:
        if (x == 65 * 16 + 8 && y == 80 * 16 + 8)
        {
            teleport->setTeleport(62, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(63, 69 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 27 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(63, 89 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 62 * 16 + 8 && y == 13 * 16 + 8)
        {
            if (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_UTILISE || scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_FERME)
            {
                teleport->setTeleport(64, 9 * 16 + 8, 12 * 16, N, false, true);
            }
            else
            {
                teleport->setTeleport(69, 9 * 16 + 8, 12 * 16, N, false, true);
            }
            return true;
        }
        if (x >= 16 * 16 && x <= 17 * 16 && y == 68 * 16 + 8 && !scene->getCoffre(0, 2))
        {
            teleport->setTeleport(150, 89 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        break;
    case 22:
        if (((x == 18 * 16 + 8 && y == 29 * 16 + 8) || (x == 50 * 16 + 8 && y == 34 * 16)) && scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_UTILISE && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            link->setY(link->getY() + 4);
            link->setDirection(S);
            MainController::getInstance()->getGameController()->displayText(443);
            return false;
        }
        if (x == 10 * 16 + 8 && y == 4 * 16 + 8)
        {
            teleport->setTeleport(65, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 18 * 16 + 8 && y == 29 * 16 + 8)
        {
            teleport->setTeleport(90, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 50 * 16 + 8 && y == 34 * 16)
        {
            teleport->setTeleport(91, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 112 * 16 + 8 && y == 17 * 16 + 8)
        {
            teleport->setTeleport(92, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 84 * 16 && y == 7 * 16 + 8)
        {
            teleport->setTeleport(46, 109 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        break;
    case 23:
        if (x == 58 * 16 + 8 && y == 18 * 16 + 8)
        {
            teleport->setTeleport(66, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 11 * 16 + 8)
        {
            teleport->setTeleport(111, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 25:
        if (x == 37 * 16 + 8 && y == 9 * 16 + 8)
        {
            teleport->setTeleport(93, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 31 * 16 + 8 && y == 24 * 16 + 8)
        {
            teleport->setTeleport(94, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 43 * 16 + 8 && y == 26 * 16 + 8)
        {
            teleport->setTeleport(95, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 30 * 16 + 8 && y == 39 * 16 + 8)
        {
            teleport->setTeleport(96, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 47 * 16 + 8 && y == 42 * 16 + 8)
        {
            teleport->setTeleport(97, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 65 * 16 + 8 && y == 22 * 16 + 8)
        {
            teleport->setTeleport(98, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 62 * 16 + 8 && y == 34 * 16 + 8)
        {
            teleport->setTeleport(99, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 65 * 16 + 8 && y == 49 * 16 + 8)
        {
            teleport->setTeleport(100, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 26:
        if (x == 120 * 16 + 8 && y == 36 * 16 + 8)
        {
            teleport->setTeleport(101, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 72 * 16 + 8 && y == 41 * 16 + 8)
        {
            teleport->setTeleport(47, 109 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 50 * 16 + 8 && y == 26 * 16 + 8)
        {
            teleport->setTeleport(47, 69 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 32 * 16 + 8 && y == 47 * 16 + 8)
        {
            teleport->setTeleport(47, 29 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        break;
    case 27:
        if (x == 84 * 16 + 8 && y == 56 * 16 + 8)
        {
            teleport->setTeleport(67, 69 * 16 + 8, 27 * 16, N, false, true);
            return true;
        }
        if (x >= 15 * 16 && x <= 16 * 16 && y == 21 * 16 + 8)
        {
            teleport->setTeleport(51, 129 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        break;
    case 28:
        if (x == 15 * 16 + 8 && y == 16 * 16 + 8)
        {
            teleport->setTeleport(102, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 21 * 16 + 8 && y == 16 * 16 + 8)
        {
            teleport->setTeleport(102, 29 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 24 * 16 + 8 && y == 25 * 16 + 8)
        {
            teleport->setTeleport(103, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 18 * 16 + 8 && y == 35 * 16 + 8)
        {
            teleport->setTeleport(104, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 13 * 16 + 8 && y == 47 * 16 + 8)
        {
            teleport->setTeleport(105, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 42 * 16 + 8 && y == 21 * 16 + 8)
        {
            teleport->setTeleport(106, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 61 * 16 + 8 && y == 34 * 16 + 8)
        {
            teleport->setTeleport(107, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 61 * 16 + 8 && y == 44 * 16 + 8)
        {
            teleport->setTeleport(108, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 29:
        if (x == 18 * 16 + 8 && y == 42 * 16 + 8)
        {
            teleport->setTeleport(109, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 45 * 16 + 8 && y == 43 * 16 + 8)
        {
            teleport->setTeleport(110, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x >= 34 * 16 && x <= 35 * 16 && y == 52 * 16 + 8)
        {
            teleport->setTeleport(151, 29 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        break;
    case 30:
        if (x == 25 * 16 + 8 && y == 40 * 16 + 8)
        {
            teleport->setTeleport(68, 9 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 45 * 16 + 8 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(68, 39 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 23 * 16 + 8 && y == 33 * 16 + 8)
        {
            teleport->setTeleport(68, 89 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 53 * 16 + 8 && y == 31 * 16)
        {
            teleport->setTeleport(68, 69 * 16 + 8, 22 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 122 * 16 && y == 35 * 16 + 8)
        {
            teleport->setTeleport(48, 69 * 16 + 8, 72 * 16, N, false, true);
            return true;
        }
        break;
    case 31:
        if (x == 59 * 16 + 8 && y == 10 * 16 + 8)
        {
            teleport->setTeleport(71, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 40 * 16 + 8)
        {
            teleport->setTeleport(116, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 33:
        if (x == 63 * 16 + 8 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(117, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 43 * 16 + 8)
        {
            teleport->setTeleport(118, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(119, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 59 * 16 + 8)
        {
            teleport->setTeleport(120, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 15 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(121, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(122, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 63 * 16 + 8 && y == 75 * 16 + 8)
        {
            teleport->setTeleport(123, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 34:
        if (x >= 39 * 16 && x <= 40 * 16 && y == 34 * 16 + 8)
        {
            teleport->setTeleport(155, 69 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        if (x >= 39 * 16 && x <= 40 * 16 && y == 29 * 16 + 8)
        {
            teleport->setTeleport(155, 149 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        // escaliers
        if (x == 53 * 16 + 8 && y == 26 * 16)
        {
            teleport->setTeleport(155, 109 * 16 + 8, 7 * 16 + 8, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        break;
    case 36:
        if (x == 62 * 16 + 8 && y == 13 * 16 + 8)
        {
            teleport->setTeleport(70, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 37:
        if (x == 10 * 16 + 8 && y == 4 * 16 + 8)
        {
            teleport->setTeleport(73, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 112 * 16 + 8 && y == 16 * 16 + 8)
        {
            teleport->setTeleport(115, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 38:
        if (x == 58 * 16 + 8 && y == 18 * 16 + 8)
        {
            teleport->setTeleport(72, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 11 * 16 + 8)
        {
            teleport->setTeleport(114, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        break;
    case 41:
        if (x == 72 * 16 + 8 && y == 43 * 16 + 8)
        {
            teleport->setTeleport(49, 9 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        break;
    case 42:
        if (x >= 15 * 16 && x <= 16 * 16 && y == 21 * 16 + 8)
        {
            teleport->setTeleport(50, 129 * 16 + 8, 87 * 16, N, false, true);
            return true;
        }
        break;
    case 44:
        if (x == 18 * 16 + 8 && y == 41 * 16 + 8)
        {
            teleport->setTeleport(112, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x == 45 * 16 + 8 && y == 42 * 16 + 8)
        {
            teleport->setTeleport(113, 9 * 16 + 8, 12 * 16, N, false, true);
            return true;
        }
        if (x >= 34 * 16 && x <= 35 * 16 && y == 52 * 16 + 8)
        {
            teleport->setTeleport(152, 29 * 16 + 8, 42 * 16, N, false, true);
            return true;
        }
        if (x == 34 * 16 + 8 && y == 24 * 16 + 8)
        {
            teleport->setTeleport(58, 69 * 16 + 8, 102 * 16, N, false, true);
            return true;
        }
        break;
    case 45:
        if (x == 108 * 16 + 8 && y == 3 * 16 + 8)
        {
            teleport->setTeleport(59, 109 * 16 + 8, 57 * 16, N, false, true);
            return true;
        }
        break;
    case 46:
        if (y >= h - 32)
        {
            teleport->setTeleport(22, 84 * 16, 8 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 89 * 16 + 8 && y == 51 * 16) || (x == 109 * 16 + 8 && y == 21 * 16) || (x == 129 * 16 + 8 && y == 36 * 16) || (x == 146 * 16 + 8 && y == 21 * 16) || (x == 149 * 16 + 8 && y == 6 * 16) || (x == 169 * 16 + 8 && y == 6 * 16) || (x == 197 * 16 + 8 && y == 29 * 16) || (x == 229 * 16 + 8 && y == 36 * 16) || (x == 229 * 16 + 8 && y == 51 * 16) || (x == 232 * 16 + 8 && y == 21 * 16) || (x == 249 * 16 + 8 && y == 51 * 16) || (x == 281 * 16 + 8 && y == 29 * 16) || (x == 309 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(46, x - 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 51 * 16) || (x == 29 * 16 + 8 && y == 21 * 16) || (x == 49 * 16 + 8 && y == 36 * 16) || (x == 66 * 16 + 8 && y == 21 * 16) || (x == 69 * 16 + 8 && y == 6 * 16) || (x == 89 * 16 + 8 && y == 6 * 16) || (x == 117 * 16 + 8 && y == 29 * 16) || (x == 149 * 16 + 8 && y == 36 * 16) || (x == 149 * 16 + 8 && y == 51 * 16) || (x == 152 * 16 + 8 && y == 21 * 16) || (x == 169 * 16 + 8 && y == 51 * 16) || (x == 201 * 16 + 8 && y == 29 * 16) || (x == 229 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(46, x + 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 == 248 && (y + 16) / 16 == 22 && sol[248][22] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(46, 347 * 16, 25 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if ((x + 8) / 16 == 352 && (y + 16) / 16 == 25 && sol[352][25] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(46, 251 * 16, 22 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 47:
        if (x > 100 * 16 && x < 120 * 16 && y >= 45 * 16 - 32)
        {
            teleport->setTeleport(26, 72 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        if (x > 60 * 16 && x < 80 * 16 && y >= 15 * 16 - 32)
        {
            teleport->setTeleport(26, 50 * 16 + 8, 27 * 16, S, false, true);
            return true;
        }
        if (x > 20 * 16 && x < 40 * 16 && y >= 75 * 16 - 32)
        {
            teleport->setTeleport(26, 32 * 16 + 8, 48 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 29 * 16 + 8 && y == 65 * 16) || (x == 69 * 16 + 8 && y == 5 * 16) || (x == 109 * 16 + 8 && y == 35 * 16) || (x == 129 * 16 + 8 && y == 66 * 16) || (x == 189 * 16 + 8 && y == 21 * 16) || (x == 229 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(47, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 149 * 16 + 8 && y == 65 * 16) || (x == 189 * 16 + 8 && y == 5 * 16) || (x == 229 * 16 + 8 && y == 35 * 16) || (x == 249 * 16 + 8 && y == 66 * 16) || (x == 309 * 16 + 8 && y == 21 * 16) || (x == 349 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(47, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 48:
        if (y >= h - 32)
        {
            teleport->setTeleport(30, 122 * 16, 36 * 16, S, false, true);
            return true;
        }
        if (x >= 289 * 16 - 4 && x <= 289 * 16 + 4 && y >= 39 * 16 + 4 && y <= 40 * 16 - 4 && link->getInventory()->hasMedaillon(2))
        {
            teleport->setTeleport(48, 9 * 16, 16 * 31 + 8, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 9 * 16 + 8 && y == 66 * 16) || (x == 95 * 16 + 8 && y == 22 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 66 * 16))
        {
            teleport->setTeleport(48, x + 140 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 149 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 66 * 16) || (x == 235 * 16 + 8 && y == 22 * 16) || (x == 269 * 16 + 8 && y == 6 * 16) || (x == 269 * 16 + 8 && y == 66 * 16))
        {
            teleport->setTeleport(48, x - 140 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 49:
        if (x < 20 * 16 && y >= 45 * 16 - 32)
        {
            teleport->setTeleport(41, 72 * 16 + 8, 44 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 35 * 16) || (x == 29 * 16 + 8 && y == 6 * 16) || (x == 29 * 16 + 8 && y == 81 * 16) || (x == 49 * 16 + 8 && y == 6 * 16) || (x == 69 * 16 + 8 && y == 51 * 16) || (x == 69 * 16 + 8 && y == 66 * 16) || (x == 89 * 16 + 8 && y == 51 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 23 * 16) || (x == 130 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(49, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 129 * 16 + 8 && y == 35 * 16) || (x == 149 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 81 * 16) || (x == 169 * 16 + 8 && y == 6 * 16) || (x == 189 * 16 + 8 && y == 51 * 16) || (x == 189 * 16 + 8 && y == 66 * 16) || (x == 209 * 16 + 8 && y == 51 * 16) || (x == 249 * 16 + 8 && y == 6 * 16) || (x == 249 * 16 + 8 && y == 23 * 16) || (x == 250 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(49, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 50:
        if (x < 180 * 16 && y >= 90 * 16 - 32)
        {
            teleport->setTeleport(42, 15 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 12 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(50, x + 40 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 36 * 16) || (x == 69 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(50, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 21 * 16) || (x == 89 * 16 + 8 && y == 81 * 16) || (x == 129 * 16 + 8 && y == 66 * 16) || (x == 169 * 16 + 8 && y == 21 * 16) || (x == 169 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(50, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 52 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(50, x - 40 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 36 * 16) || (x == 149 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(50, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 209 * 16 + 8 && y == 21 * 16) || (x == 209 * 16 + 8 && y == 81 * 16) || (x == 249 * 16 + 8 && y == 66 * 16) || (x == 289 * 16 + 8 && y == 21 * 16) || (x == 289 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(50, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 51:
        if (x < 180 * 16 && y >= 90 * 16 - 32)
        {
            teleport->setTeleport(27, 15 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        if (x >= w - 24)
        {
            teleport->setTeleport(67, 16 + 8, 6 * 16 + 8, E, false, true);
            return true;
        }
        // escaliers
        if (x == 11 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(51, x + 40 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 36 * 16) || (x == 49 * 16 + 8 && y == 66 * 16) || (x == 69 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(51, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 81 * 16) || (x == 169 * 16 + 8 && y == 66 * 16) || (x == 169 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(51, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 51 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(51, x - 40 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 36 * 16) || (x == 129 * 16 + 8 && y == 66 * 16) || (x == 149 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(51, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 209 * 16 + 8 && y == 81 * 16) || (x == 289 * 16 + 8 && y == 66 * 16) || (x == 289 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(51, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 52:
        if (x < 180 * 16 && y >= 90 * 16 - 32)
        {
            teleport->setTeleport(12, 15 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 12 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(52, x + 40 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 36 * 16) || (x == 29 * 16 + 8 && y == 51 * 16) || (x == 49 * 16 + 8 && y == 66 * 16) || (x == 69 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(52, x + 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 89 * 16 + 8 && y == 51 * 16) || (x == 89 * 16 + 8 && y == 81 * 16) || (x == 109 * 16 + 8 && y == 21 * 16) || (x == 129 * 16 + 8 && y == 81 * 16) || (x == 149 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 21 * 16) || (x == 169 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 66 * 16))
        {
            teleport->setTeleport(52, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 52 * 16 + 8 && y == 51 * 16)
        {
            teleport->setTeleport(52, x - 40 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 36 * 16) || (x == 109 * 16 + 8 && y == 51 * 16) || (x == 129 * 16 + 8 && y == 66 * 16) || (x == 149 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(52, x - 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 209 * 16 + 8 && y == 51 * 16) || (x == 209 * 16 + 8 && y == 81 * 16) || (x == 229 * 16 + 8 && y == 21 * 16) || (x == 249 * 16 + 8 && y == 81 * 16) || (x == 269 * 16 + 8 && y == 51 * 16) || (x == 289 * 16 + 8 && y == 21 * 16) || (x == 289 * 16 + 8 && y == 51 * 16) || (x == 289 * 16 + 8 && y == 66 * 16))
        {
            teleport->setTeleport(52, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 53:
        if (bounds.getX() == 320 && bounds.getY() == 240 * 3 && y >= 60 * 16 - 32)
        {
            teleport->setTeleport(7, 84 * 16, 8 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && (y == 21 * 16 || y == 51 * 16))
        {
            teleport->setTeleport(53, x + 80 * 16, y + 60 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 109 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 21 * 16) || (x == 149 * 16 + 8 && y == 81 * 16) || (x == 169 * 16 + 8 && y == 6 * 16) || (x == 169 * 16 + 8 && y == 36 * 16) || (x == 199 * 16 + 8 && y == 29 * 16) || (x == 229 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(53, x - 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 89 * 16 + 8 && (y == 81 * 16 || y == 111 * 16))
        {
            teleport->setTeleport(53, x - 80 * 16, y - 60 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 29 * 16 + 8 && y == 6 * 16) || (x == 69 * 16 + 8 && y == 21 * 16) || (x == 69 * 16 + 8 && y == 81 * 16) || (x == 89 * 16 + 8 && y == 6 * 16) || (x == 89 * 16 + 8 && y == 36 * 16) || (x == 119 * 16 + 8 && y == 29 * 16) || (x == 149 * 16 + 8 && y == 51 * 16))
        {
            teleport->setTeleport(53, x + 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 == 187 && (y + 16) / 16 == 7 && sol[187][7] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, 187 * 16, 85 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if ((x + 8) / 16 == 192 && (y + 16) / 16 == 85 && sol[192][85] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, 192 * 16, 7 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 54:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && y >= 45 * 16 - 32)
        {
            teleport->setTeleport(11, 72 * 16 + 8, 52 * 16 + 8, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 35 * 16) || (x == 29 * 16 + 8 && y == 51 * 16) || (x == 49 * 16 + 8 && y == 6 * 16) || (x == 89 * 16 + 8 && y == 36 * 16) || (x == 109 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(54, x + 120 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 129 * 16 + 8 && y == 35 * 16) || (x == 149 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 6 * 16) || (x == 209 * 16 + 8 && y == 36 * 16) || (x == 229 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(54, x - 120 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 55:
        if (y >= h - 32)
        {
            teleport->setTeleport(15, 122 * 16, 35 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 81 * 16) || (x == 9 * 16 + 8 && y == 216 * 16) || (x == 66 * 16 + 8 && y == 216 * 16) || (x == 72 * 16 + 8 && y == 141 * 16) || (x == 129 * 16 + 8 && y == 81 * 16) || (x == 129 * 16 + 8 && y == 216 * 16))
        {
            teleport->setTeleport(55, x, y - 75 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 9 * 16 + 8 && y == 141 * 16) || (x == 66 * 16 + 8 && y == 141 * 16) || (x == 72 * 16 + 8 && y == 66 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 141 * 16))
        {
            teleport->setTeleport(55, x, y + 75 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 == 65 && (y + 16) / 16 == 38 && sol[65][38] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(55, 69 * 16 + 8, 178 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 56:
        if (x > 60 * 16 && x < 80 * 16 && y >= 60 * 16 - 32)
        {
            teleport->setTeleport(4, 39 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        if (x > 140 * 16 && y >= 45 * 16 - 32 && y < 60 * 16)
        {
            teleport->setTeleport(4, 39 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        if (x == 109 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(4, 53 * 16 + 8, 25 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 57:
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 11 && scene->getAvancement() < AV_ZELDA_SOUS_SOL && link->getX() >= 104 * 16)
        {
            scene->getAnimationInGame()->startAnim(13);
        }
        if (x > 60 * 16 && x < 80 * 16 && y >= 60 * 16 - 32 && y < 75 * 16)
        {
            teleport->setTeleport(19, 39 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        if (x > 140 * 16 && y >= 45 * 16 - 32 && y < 60 * 16)
        {
            teleport->setTeleport(19, 39 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        if (y <= 0)
        {
            teleport->setTeleport(156, 149 * 16 + 8, 297 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 109 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(19, 53 * 16 + 8, 25 * 16, N, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 149 * 16 + 8 && y == 201 * 16)
        {
            teleport->setTeleport(19, 68 * 16 + 8, 49 * 16, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // escaliers
        if ((x == 49 * 16 + 8 && y == 51 * 16) || (x == 89 * 16 + 8 && y == 51 * 16) || (x == 49 * 16 + 8 && y == 156 * 16))
        {
            teleport->setTeleport(57, x, y + 90 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 49 * 16 + 8 && y == 141 * 16) || (x == 89 * 16 + 8 && y == 141 * 16) || (x == 49 * 16 + 8 && y == 246 * 16))
        {
            teleport->setTeleport(57, x, y - 90 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 58:
        if (x >= 125 * 16 + 8 && y > 90 * 16 && jeuCasinoStarted == 3)
        {
            scene->getHud()->hideTime();
            MainController::getInstance()->getGameController()->displayText(1439);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2 && y <= 37 * 16 + 8 && nbEnnemis())
        {
            MainController::getInstance()->getGameController()->displayText(1461);
            scene->getHud()->instantBoss();
        }
        if (y >= h - 32)
        {
            scene->getHud()->hideTime();
            scene->getHud()->hideCasino();
            teleport->setTeleport(44, 34 * 16 + 8, 25 * 16, S, false, true);
            return true;
        }
        break;
    case 59:
        if (y >= h - 32)
        {
            teleport->setTeleport(45, 108 * 16 + 8, 4 * 16, S, false, true);
            return true;
        }
        // escaliers
        if ((x == 89 * 16 + 8 && y == 51 * 16) || (x == 169 * 16 + 8 && y == 36 * 16) || (x == 249 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(59, x - 80 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 51 * 16) || (x == 89 * 16 + 8 && y == 36 * 16) || (x == 169 * 16 + 8 && y == 6 * 16))
        {
            teleport->setTeleport(59, x + 80 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 60:
        // teleport
        if ((x + 8) / 16 >= 69 && (x - 8) / 16 <= 69 && (y + 16) / 16 == 146)
        {
            scene->getHud()->hideDestFinal();
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(111, 9 * 16 + 8, 10 * 16 - 8, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 81 * 16) || (x == 129 * 16 + 8 && y == 81 * 16) || (x == 9 * 16 + 8 && y == 141 * 16) || (x == 129 * 16 + 8 && y == 141 * 16))
        {
            teleport->setTeleport(60, x, y - 75 * 16 + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 6 * 16) || (x == 129 * 16 + 8 && y == 6 * 16) || (x == 9 * 16 + 8 && y == 66 * 16) || (x == 129 * 16 + 8 && y == 66 * 16))
        {
            teleport->setTeleport(60, x, y + 75 * 16 - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 61:
        if (y >= h - 32)
        {
            teleport->setTeleport(16, 59 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        break;
    case 62:
        if (y >= h - 32)
        {
            teleport->setTeleport(21, 65 * 16 + 8, 81 * 16, S, false, true);
            return true;
        }
        break;
    case 63:
        if (y >= h - 32 && x < 80 * 16)
        {
            teleport->setTeleport(21, 15 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 80 * 16)
        {
            teleport->setTeleport(21, 27 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 89 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(63, x - 40 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 49 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(63, x + 40 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 64:
        if (y == 10 * 16 + 8 && scene->getAvancement() == AV_STELE_LUE)
        {
            scene->getAnimationInGame()->testAnim();
        }
        if (x >= 9 * 16 - 4 && x <= 10 * 16 + 4 && y <= 2 * 16 + 8 && scene->getAvancement() >= AV_PORTAIL_F_OUVERT && scene->getAvancement() < AV_PORTAIL_F_UTILISE)
        {
            teleport->setTeleport(70, 9 * 16 + 8, 16 * 3 + 8, S, false, false, true);
            scene->setAvancement(AV_PORTAIL_F_UTILISE);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if (y >= h - 32)
        {
            teleport->setTeleport(21, 62 * 16 + 8, 14 * 16, S, false, true);
            return true;
        }
        break;
    case 65:
        if (y >= h - 32)
        {
            teleport->setTeleport(22, 10 * 16 + 8, 5 * 16, S, false, true);
            return true;
        }
        break;
    case 66:
        if (y >= h - 32)
        {
            teleport->setTeleport(23, 58 * 16 + 8, 19 * 16, S, false, true);
            return true;
        }
        break;
    case 67:
        if (y >= h - 32)
        {
            teleport->setTeleport(27, 84 * 16 + 8, 57 * 16, S, false, true);
            return true;
        }
        if (x <= 8)
        {
            teleport->setTeleport(51, 317 * 16 + 8, 96 * 16 + 8, W, false, true);
            return true;
        }
        // escaliers
        if (x == 49 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(67, x - 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(67, x + 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 68:
        if (y >= h - 32 && x < 320)
        {
            teleport->setTeleport(30, 25 * 16 + 8, 41 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 320 && x < 320 * 3)
        {
            teleport->setTeleport(30, 45 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 320 * 3)
        {
            teleport->setTeleport(30, 23 * 16 + 8, 34 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 89 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(68, x - 80 * 16, y + 24 - 15 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 38 * 16)
        {
            teleport->setTeleport(68, x, y + 24 - 15 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 69 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(30, 53 * 16 + 8, 32 * 16, S, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 9 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(68, x + 80 * 16, y - 24 + 15 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 39 * 16 + 8 && y == 23 * 16)
        {
            teleport->setTeleport(68, x, y - 24 + 15 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 69:
        if (y >= h - 32)
        {
            teleport->setTeleport(21, 62 * 16 + 8, 14 * 16, S, false, true);
            return true;
        }
        if (x >= 9 * 16 - 4 && x <= 10 * 16 + 4 && y <= 2 * 16 + 8)
        {
            teleport->setTeleport(70, 9 * 16 + 8, 16 * 3 + 8, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    case 70:
        if (y >= h - 32)
        {
            teleport->setTeleport(36, 62 * 16 + 8, 14 * 16, S, false, true);
            return true;
        }
        if (x >= 9 * 16 - 4 && x <= 10 * 16 + 4 && y <= 2 * 16 + 8 && scene->getAvancement() >= AV_PORTAIL_PRE_PRESENT_OUVERT && scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            teleport->setTeleport(69, 9 * 16 + 8, 16 * 3 + 8, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            scene->setAvancement(AV_PORTAIL_PRE_PRESENT_UTILISE);
            return true;
        }
        break;
    case 71:
        if (y >= h - 32)
        {
            teleport->setTeleport(31, 59 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        break;
    case 72:
        if (y >= h - 32)
        {
            teleport->setTeleport(38, 58 * 16 + 8, 19 * 16, S, false, true);
            return true;
        }
        break;
    case 73:
        if (y >= h - 32)
        {
            teleport->setTeleport(37, 10 * 16 + 8, 5 * 16, S, false, true);
            return true;
        }
        break;
    case 74:
        if (y >= h - 32)
        {
            teleport->setTeleport(7, 10 * 16 + 8, 5 * 16, S, false, true);
            return true;
        }
        break;
    case 75:
        if (y >= h - 32)
        {
            teleport->setTeleport(1, 59 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        break;
    case 76:
        if (y >= h - 32)
        {
            teleport->setTeleport(12, 84 * 16 + 8, 57 * 16, S, false, true);
            return true;
        }
        break;
    case 77:
        if (y >= h - 32)
        {
            teleport->setTeleport(6, 65 * 16 + 8, 81 * 16, S, false, true);
            return true;
        }
        break;
    case 78:
        if (y >= h - 32 && x < 320 * 4)
        {
            teleport->setTeleport(6, 15 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 320 * 5)
        {
            teleport->setTeleport(6, 27 * 16 + 8, 11 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 89 * 16 + 8 && y == 7 * 16)
        {
            teleport->setTeleport(78, x - 60 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 7 * 16)
        {
            teleport->setTeleport(78, x + 60 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 79:
        if (y >= h - 32)
        {
            teleport->setTeleport(16, 39 * 16 + 8, 41 * 16, S, false, true);
            return true;
        }
        break;
    case 80:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 17 * 16 + 8, 38 * 16, S, false, true);
            return true;
        }
        if (y <= 0)
        {
            teleport->setTeleport(18, 17 * 16 + 8, 29 * 16 + 8, N, false, true);
            return true;
        }
        break;
    case 81:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 63 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        break;
    case 82:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 63 * 16 + 8, 44 * 16, S, false, true);
            return true;
        }
        break;
    case 83:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 15 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 84:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 49 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 85:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 63 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 86:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 15 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 87:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 29 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 88:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 49 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 89:
        if (y >= h - 32)
        {
            teleport->setTeleport(18, 63 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 90:
        if (y >= h - 32)
        {
            teleport->setTeleport(22, 18 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        break;
    case 91:
        if (y >= h - 32)
        {
            teleport->setTeleport(22, 50 * 16 + 8, 34 * 16 + 8, S, false, true);
            return true;
        }
        break;
    case 92:
        if (y >= h - 32)
        {
            teleport->setTeleport(22, 112 * 16 + 8, 18 * 16, S, false, true);
            return true;
        }
        break;
    case 93:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 37 * 16 + 8, 10 * 16, S, false, true);
            return true;
        }
        break;
    case 94:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 31 * 16 + 8, 25 * 16, S, false, true);
            return true;
        }
        break;
    case 95:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 43 * 16 + 8, 27 * 16, S, false, true);
            return true;
        }
        break;
    case 96:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 30 * 16 + 8, 40 * 16, S, false, true);
            return true;
        }
        break;
    case 97:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 47 * 16 + 8, 43 * 16, S, false, true);
            return true;
        }
        break;
    case 98:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 65 * 16 + 8, 23 * 16, S, false, true);
            return true;
        }
        break;
    case 99:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 62 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        break;
    case 100:
        if (y >= h - 32)
        {
            teleport->setTeleport(25, 65 * 16 + 8, 50 * 16, S, false, true);
            return true;
        }
        break;
    case 101:
        if (y >= h - 32)
        {
            teleport->setTeleport(26, 120 * 16 + 8, 37 * 16, S, false, true);
            return true;
        }
        break;
    case 102:
        if (y >= h - 32 && x < 320)
        {
            teleport->setTeleport(28, 15 * 16 + 8, 17 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 320)
        {
            teleport->setTeleport(28, 21 * 16 + 8, 17 * 16, S, false, true);
            return true;
        }
        break;
    case 103:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 24 * 16 + 8, 26 * 16, S, false, true);
            return true;
        }
        break;
    case 104:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 18 * 16 + 8, 36 * 16, S, false, true);
            return true;
        }
        break;
    case 105:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 13 * 16 + 8, 48 * 16, S, false, true);
            return true;
        }
        break;
    case 106:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 42 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        break;
    case 107:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 61 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        break;
    case 108:
        if (y >= h - 32)
        {
            teleport->setTeleport(28, 61 * 16 + 8, 45 * 16, S, false, true);
            return true;
        }
        break;
    case 109:
        if (y >= h - 32)
        {
            teleport->setTeleport(29, 18 * 16 + 8, 43 * 16, S, false, true);
            return true;
        }
        break;
    case 110:
        if (y >= h - 32)
        {
            teleport->setTeleport(29, 45 * 16 + 8, 44 * 16, S, false, true);
            return true;
        }
        break;
    case 111:
        // teleport
        if ((x + 8) / 16 >= 9 && (x - 8) / 16 <= 9 && (y + 16) / 16 == 4 && sol[9][4] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(60, 69 * 16 + 8, 145 * 16 - 8, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if (y >= h - 32)
        {
            teleport->setTeleport(23, 39 * 16 + 8, 12 * 16, S, false, true);
            return true;
        }
        break;
    case 112:
        if (y >= h - 32)
        {
            teleport->setTeleport(44, 18 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 113:
        if (y >= h - 32)
        {
            teleport->setTeleport(44, 45 * 16 + 8, 43 * 16, S, false, true);
            return true;
        }
        break;
    case 114:
        // teleport
        if ((x + 8) / 16 >= 9 && (x - 8) / 16 <= 9 && (y + 16) / 16 == 4 && sol[9][4] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(60, 69 * 16 + 8, 145 * 16 - 8, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if (y >= h - 32)
        {
            teleport->setTeleport(38, 39 * 16 + 8, 12 * 16, S, false, true);
            return true;
        }
        break;
    case 115:
        if (y >= h - 32)
        {
            teleport->setTeleport(37, 112 * 16 + 8, 17 * 16, S, false, true);
            return true;
        }
        break;
    case 116:
        if (y >= h - 32)
        {
            teleport->setTeleport(31, 39 * 16 + 8, 41 * 16, S, false, true);
            return true;
        }
        break;
    case 117:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 63 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        break;
    case 118:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 63 * 16 + 8, 44 * 16, S, false, true);
            return true;
        }
        break;
    case 119:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 49 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        if (y == 4 * 16 + 8 && x > 6 * 16 + 8 && x < 9 * 16 && scene->getCoffre(0, 27) > 0)
        {
            link->setX(6 * 16 + 8);
            scene->setCoffre(0, 27, scene->getCoffre(0, 27) - link->getSpeed());
            if (scene->getCoffre(0, 27) <= 0)
            {
                scene->setCoffre(0, 27, -1);
                AudioManager::getInstance()->playSound(TS_PLOT);
                reactiveInterruptor(6 * 16, 8 * 16);
            }
        }
        break;
    case 120:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 63 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 121:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 15 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 122:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 29 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 123:
        if (y >= h - 32)
        {
            teleport->setTeleport(33, 63 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 124:
        // teleport
        if ((x + 8) / 16 >= 9 && (x - 8) / 16 <= 9 && (y + 16) / 16 == 4 && sol[9][4] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(60, 69 * 16 + 8, 145 * 16 - 8, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if (y >= h - 32)
        {
            teleport->setTeleport(8, 39 * 16 + 8, 12 * 16, S, false, true);
            return true;
        }
        break;
    case 125:
        if (y >= h - 32)
        {
            teleport->setTeleport(14, 18 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 126:
        if (y >= h - 32)
        {
            teleport->setTeleport(1, 39 * 16 + 8, 41 * 16, S, false, true);
            return true;
        }
        break;
    case 127:
        if (y >= h - 32)
        {
            teleport->setTeleport(11, 72 * 16 + 8, 43 * 16, S, false, true);
            return true;
        }
        break;
    case 128:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 63 * 16 + 8, 33 * 16, S, false, true);
            return true;
        }
        break;
    case 129:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 63 * 16 + 8, 44 * 16, S, false, true);
            return true;
        }
        break;
    case 130:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 15 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 131:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 49 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 132:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 63 * 16 + 8, 60 * 16, S, false, true);
            return true;
        }
        break;
    case 133:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 29 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 134:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 49 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 135:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 63 * 16 + 8, 76 * 16, S, false, true);
            return true;
        }
        break;
    case 136:
        if (y >= h - 32)
        {
            teleport->setTeleport(3, 17 * 16 + 8, 38 * 16, S, false, true);
            return true;
        }
        break;
    case 137:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 37 * 16 + 8, 9 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 67 * 16)
        {
            teleport->setTeleport(137, x, y + 24 - 15 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 9 * 16 + 8 && y == 52 * 16)
        {
            teleport->setTeleport(137, x, y - 24 + 15 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 138:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 31 * 16 + 8, 24 * 16, S, false, true);
            return true;
        }
        break;
    case 139:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 43 * 16 + 8, 26 * 16, S, false, true);
            return true;
        }
        break;
    case 140:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 30 * 16 + 8, 39 * 16, S, false, true);
            return true;
        }

        if (x == 9 * 16 + 8 && y == 7 * 16 && link->getInventory()->getTrocGemme(0) < TGR_RIEN_2)
        {
            link->setY(link->getY() - 4);
            link->setDirection(N);
            MainController::getInstance()->getGameController()->displayText(1102);
            return false;
        }
        // escaliers
        if (x == 9 * 16 + 8 && y == 7 * 16)
        {
            teleport->setTeleport(140, x + 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 29 * 16 + 8 && y == 7 * 16)
        {
            teleport->setTeleport(140, x - 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 141:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 47 * 16 + 8, 42 * 16, S, false, true);
            return true;
        }
        break;
    case 142:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 62 * 16 + 8, 34 * 16, S, false, true);
            return true;
        }
        break;
    case 143:
        if (y >= h - 32)
        {
            teleport->setTeleport(10, 65 * 16 + 8, 49 * 16, S, false, true);
            return true;
        }
        break;
    case 144:
        if (y >= h - 32 && x < 320)
        {
            teleport->setTeleport(13, 15 * 16 + 8, 16 * 16, S, false, true);
            return true;
        }
        if (y >= h - 32 && x > 320)
        {
            teleport->setTeleport(13, 21 * 16 + 8, 16 * 16, S, false, true);
            return true;
        }
        break;
    case 145:
        if (y >= h - 32)
        {
            teleport->setTeleport(13, 18 * 16 + 8, 36 * 16, S, false, true);
            return true;
        }
        break;
    case 146:
        if (y >= h - 32)
        {
            teleport->setTeleport(13, 13 * 16 + 8, 48 * 16, S, false, true);
            return true;
        }
        break;
    case 147:
        if (y >= h - 32)
        {
            teleport->setTeleport(13, 42 * 16 + 8, 22 * 16, S, false, true);
            return true;
        }
        break;
    case 148:
        if (y >= h - 32)
        {
            teleport->setTeleport(13, 61 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        break;
    case 149:
        if (y >= h - 32)
        {
            teleport->setTeleport(13, 61 * 16 + 8, 45 * 16, S, false, true);
            return true;
        }
        break;
    case 150:
        if (y >= h - 32)
        {
            teleport->setTeleport(21, 16 * 16 + 8, 69 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (((x == 23 * 16 + 8 || x == 35 * 16 + 8) && y == 18 * 16) || (x == 89 * 16 + 8 && y == 6 * 16) || (x == 149 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(150, x + 60 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (((x == 83 * 16 + 8 || x == 95 * 16 + 8) && y == 18 * 16) || (x == 149 * 16 + 8 && y == 6 * 16) || (x == 209 * 16 + 8 && y == 36 * 16))
        {
            teleport->setTeleport(150, x - 60 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 151:
        if (y >= h - 32)
        {
            teleport->setTeleport(29, 34 * 16 + 8, 53 * 16, S, false, true);
            return true;
        }
        break;
    case 152:
        if (y >= h - 32)
        {
            teleport->setTeleport(44, 34 * 16 + 8, 53 * 16, S, false, true);
            return true;
        }
        break;
    case 153:
        if (y >= h - 32)
        {
            teleport->setTeleport(14, 34 * 16 + 8, 53 * 16, S, false, true);
            return true;
        }
        break;
    case 154:
        if (x >= 36 * 16 && y >= 15 * 16 && link->getInventory()->nbCristaux() >= 6 && scene->getAvancement() < AV_GANON_SORTI)
        {
            scene->getAnimationInGame()->startAnim(9);
        }
        if (y >= h - 32)
        {
            teleport->setTeleport(9, 113 * 16 + 8, 36 * 16, S, false, true);
            return true;
        }
        // escaliers
        if (x == 6 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(154, x + 20 * 16, y + 24, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 32 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(154, x, y + 24 + 15 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if (x == 26 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(154, x - 20 * 16, y - 24, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 32 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(154, x, y - 24 - 15 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if (x == 69 * 16 + 8 && y == 21 * 16)
        {
            teleport->setTeleport(9, 129 * 16 + 8, 39 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 155:
        if (x > 60 * 16 && x < 80 * 16 && y >= 60 * 16 - 32)
        {
            teleport->setTeleport(34, 39 * 16 + 8, 35 * 16, S, false, true);
            return true;
        }
        if (x > 140 * 16 && y >= 45 * 16 - 32)
        {
            teleport->setTeleport(34, 39 * 16 + 8, 30 * 16, S, false, true);
            return true;
        }
        if (x == 109 * 16 + 8 && y == 6 * 16)
        {
            teleport->setTeleport(34, 53 * 16 + 8, 25 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        break;
    case 156:
        if (y >= h - 32)
        {
            teleport->setTeleport(57, 149 * 16 + 8, 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 20 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 32 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 60 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 67 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 120 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 132 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 140 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 149 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 160 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 167 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 220 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 232 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 260 * 16 && bounds.getY() == 15 * 16 && y >= 28 * 16)
        {
            teleport->setTeleport(156, 267 * 16, 33 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 60 * 16 && bounds.getY() == 105 * 16 && y >= 118 * 16)
        {
            teleport->setTeleport(156, 67 * 16, 123 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 100 * 16 && bounds.getY() == 105 * 16 && y >= 118 * 16)
        {
            teleport->setTeleport(156, 112 * 16, 123 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 180 * 16 && bounds.getY() == 105 * 16 && y >= 118 * 16)
        {
            teleport->setTeleport(156, 187 * 16, 123 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 240 * 16 && bounds.getY() == 105 * 16 && y >= 118 * 16)
        {
            teleport->setTeleport(156, 249 * 16, 123 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 40 * 16 && bounds.getY() == 195 * 16 && y >= 208 * 16)
        {
            teleport->setTeleport(156, 49 * 16, 213 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 120 * 16 && bounds.getY() == 195 * 16 && y >= 208 * 16)
        {
            teleport->setTeleport(156, 132 * 16, 213 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 160 * 16 && bounds.getY() == 195 * 16 && y >= 208 * 16)
        {
            teleport->setTeleport(156, 167 * 16, 213 * 16, S, false, true);
            return true;
        }
        if (bounds.getX() == 240 * 16 && bounds.getY() == 195 * 16 && y >= 208 * 16)
        {
            teleport->setTeleport(156, 249 * 16, 213 * 16, S, false, true);
            return true;
        }
        if (x == 32 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 29 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 67 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 69 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 132 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 129 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 149 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 149 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 167 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 169 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 232 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 229 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 267 * 16 && y == 32 * 16 + 8)
        {
            teleport->setTeleport(156, 269 * 16 + 8, 27 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 67 * 16 && y == 122 * 16 + 8)
        {
            teleport->setTeleport(156, 69 * 16 + 8, 117 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 112 * 16 && y == 122 * 16 + 8)
        {
            teleport->setTeleport(156, 109 * 16 + 8, 117 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 187 * 16 && y == 122 * 16 + 8)
        {
            teleport->setTeleport(156, 189 * 16 + 8, 117 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 249 * 16 && y == 122 * 16 + 8)
        {
            teleport->setTeleport(156, 249 * 16 + 8, 117 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 49 * 16 && y == 212 * 16 + 8)
        {
            teleport->setTeleport(156, 49 * 16 + 8, 207 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 132 * 16 && y == 212 * 16 + 8)
        {
            teleport->setTeleport(156, 129 * 16 + 8, 207 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 167 * 16 && y == 212 * 16 + 8)
        {
            teleport->setTeleport(156, 169 * 16 + 8, 207 * 16 + 8, N, false, true);
            return true;
        }
        if (x == 249 * 16 && y == 212 * 16 + 8)
        {
            teleport->setTeleport(156, 249 * 16 + 8, 207 * 16 + 8, N, false, true);
            return true;
        }
        // escaliers
        if ((x == 9 * 16 + 8 && y == 219 * 16) || (x == 29 * 16 + 8 && y == 39 * 16) || (x == 129 * 16 + 8 && y == 39 * 16))
        {
            teleport->setTeleport(156, x, y + 24 + 72 * 16, S, false, true, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 111 * 16) || (x == 49 * 16 + 8 && y == 21 * 16) || (x == 49 * 16 + 8 && y == 111 * 16) || (x == 69 * 16 + 8 && y == 6 * 16) || (x == 69 * 16 + 8 && y == 156 * 16) || (x == 89 * 16 + 8 && y == 81 * 16) || (x == 89 * 16 + 8 && y == 186 * 16) || (x == 109 * 16 + 8 && y == 156 * 16) || (x == 109 * 16 + 8 && y == 201 * 16) || (x == 149 * 16 + 8 && y == 111 * 16) || (x == 149 * 16 + 8 && y == 201 * 16) || (x == 169 * 16 + 8 && y == 21 * 16) || (x == 209 * 16 + 8 && y == 171 * 16) || (x == 229 * 16 + 8 && y == 6 * 16) || (x == 249 * 16 + 8 && y == 21 * 16) || (x == 249 * 16 + 8 && y == 81 * 16) || (x == 249 * 16 + 8 && y == 186 * 16) || (x == 269 * 16 + 8 && y == 81 * 16))
        {
            teleport->setTeleport(156, x, y + 24 + 75 * 16, S, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
            return true;
        }

        if ((x == 9 * 16 + 8 && y == 291 * 16) || (x == 29 * 16 + 8 && y == 111 * 16) || (x == 129 * 16 + 8 && y == 111 * 16))
        {
            teleport->setTeleport(156, x, y - 24 - 72 * 16, N, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        if ((x == 9 * 16 + 8 && y == 186 * 16) || (x == 49 * 16 + 8 && y == 96 * 16) || (x == 49 * 16 + 8 && y == 186 * 16) || (x == 69 * 16 + 8 && y == 81 * 16) || (x == 69 * 16 + 8 && y == 231 * 16) || (x == 89 * 16 + 8 && y == 156 * 16) || (x == 89 * 16 + 8 && y == 261 * 16) || (x == 109 * 16 + 8 && y == 231 * 16) || (x == 109 * 16 + 8 && y == 276 * 16) || (x == 149 * 16 + 8 && y == 186 * 16) || (x == 149 * 16 + 8 && y == 276 * 16) || (x == 169 * 16 + 8 && y == 96 * 16) || (x == 209 * 16 + 8 && y == 246 * 16) || (x == 229 * 16 + 8 && y == 81 * 16) || (x == 249 * 16 + 8 && y == 96 * 16) || (x == 249 * 16 + 8 && y == 156 * 16) || (x == 249 * 16 + 8 && y == 261 * 16) || (x == 269 * 16 + 8 && y == 156 * 16))
        {
            teleport->setTeleport(156, x, y - 24 - 75 * 16, N, false, false, true);
            AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
            return true;
        }
        // teleport
        if ((x + 8) / 16 == 148 && (y + 16) / 16 == 7 && sol[148][7] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(156, 187 * 16, 40 * 16 - 8, link->getDirection(), false, false);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        if ((x + 8) / 16 == 192 && (y + 16) / 16 == 40 && sol[192][40] == 3144)
        {
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(156, 151 * 16, 7 * 16 - 8, link->getDirection(), false, false, true);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

void Map::testAnim(int x, int y, Direction dir, bool sound)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    // open door
    if ((getSol(x, y + 8 - 1) == 468 || getSol(x, y + 8 - 1) == 789 || getSol(x, y + 8 - 1) == 790 || getSol(x, y + 8 - 1) == 1903 || getSol(x, y + 8 - 1) == 1904 || getSol(x, y + 8 - 1) == 2276 || getSol(x, y + 8 - 1) == 2277) && dir == N)
    {
        ouvrePorteMaison(x, y);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
    }
    // open door dungeon
    if ((getSol(x, y + 8 - 1) == 1362 || getSol(x, y + 8 - 1) == 1363 || getSol(x, y + 8 - 1) == 2826 || getSol(x, y + 8 - 1) == 2827) && dir == N)
    {
        ouvrePorte(x, y, 0);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
    }

    // use key
    if (map == 155 && scene->getAvancement() == AV_CLE_PRISON_F_TROUVEE && getSol(x, y + 7) == 3721 && dir == N)
    {
        ouvrePorte(89, 94, 1);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
        scene->setAvancement(AV_BOWSER_AIDE);
    }
    if (map == 57 && getSol(x, y + 7) == 6389 && dir == N && scene->getCoffre(map - 45, 3))
    {
        if (bounds.getX() == 0)
        {
            ouvrePorte(5, 233, 4);
            scene->setCoffre(map - 45, 8, 1);
        }
        else
        {
            ouvrePorte(72, 233, 4);
            scene->setCoffre(map - 45, 9, 1);
        }
        scene->setCoffre(map - 45, 3, scene->getCoffre(map - 45, 3) - 1);
        if (sound)
            AudioManager::getInstance()->playSound(TS_DOOR);
    }
    if (map >= 46 && map < 61)
    {

        // doors with keys
        if (scene->getCoffre(map - 45, 3))
        {
            int i = 0;
            int j = 0;

            switch (map)
            {
            case 46:
                if (getSol(x, y + 7) == 3895 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 3897 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 3904 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 3909 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 47:
                if (getSol(x, y + 7) == 4102 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4104 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4111 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 4116 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 48:
                if (getSol(x, y + 7) == 4272 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4274 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4281 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 4286 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 49:
                if (getSol(x, y + 7) == 4512 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4514 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4521 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 4526 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 50:
                if (getSol(x, y + 7) == 4759 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4761 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4768 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 4773 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 51:
                if (getSol(x, y + 7) == 4988 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 4990 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 4997 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 5002 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 52:
                if (getSol(x, y + 7) == 5217 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 5219 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 5226 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 5231 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 53:
                if (getSol(x, y + 7) == 5420 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 5422 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 5429 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 5434 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 54:
                if (getSol(x, y + 7) == 5611 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 5613 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 5620 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 5625 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 55:
                if (getSol(x, y + 7) == 5802 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 5804 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 5811 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 5816 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 56:
                if (getSol(x, y + 7) == 6022 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 6024 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 6031 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 6036 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 57:
                if (getSol(x, y + 7) == 6326 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 6328 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                break;
            case 58:
                if (getSol(x, y + 7) == 6495 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 6497 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                if (getSol(x - 1, y + 16) == 6504 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 6509 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            case 59:
                if (getSol(x, y + 7) == 6652 && dir == N)
                {
                    i = x / 16;
                    j = ((y + 7) / 16) - 3;
                }
                if (getSol(x, y + 24) == 6654 && dir == S)
                {
                    i = x / 16;
                    j = (y + 24) / 16;
                }
                break;
            case 60:
                if (getSol(x - 1, y + 16) == 6794 && dir == W)
                {
                    i = ((x - 1) / 16) - 3;
                    j = y / 16;
                }
                if (getSol(x + 16, y + 16) == 6799 && dir == E)
                {
                    i = (x + 16) / 16;
                    j = y / 16;
                }
                break;
            }

            if (i != 0)
            {
                int k = 0;
                switch (map)
                {
                case 46:
                    if (bounds.getX() == 320 * 4 && bounds.getY() >= 240 * 2)
                        k = 9;
                    else if (bounds.getX() <= 320 * 5 && bounds.getY() == 0)
                        k = 10;
                    else if (bounds.getX() == 320 * 6)
                        k = 11;
                    else if (bounds.getX() == 320 * 10)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 47:
                    if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 5)
                        k = 10;
                    else if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 4)
                        k = 11;
                    else if (bounds.getX() == 320 * 9)
                        k = 12;
                    else if (bounds.getX() == 320 * 10)
                        k = 13;
                    else if (bounds.getX() == 320 * 13)
                        k = 14;
                    else
                        k = 15;
                    break;
                case 48:
                    if (x <= 70 * 16)
                        k = 10;
                    else if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 4)
                        k = 11;
                    else if (bounds.getX() == 320 * 5)
                        k = 12;
                    else if (bounds.getX() == 320 * 8)
                        k = 13;
                    else if (bounds.getX() == 320 * 11)
                        k = 14;
                    else
                        k = 15;
                    break;
                case 49:
                    if (bounds.getX() <= 320 * 2)
                        k = 8;
                    else if (bounds.getX() == 320 * 3)
                        k = 9;
                    else if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 3)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 50:
                    if (bounds.getX() == 320 * 2)
                        k = 8;
                    else if (bounds.getY() == 240 * 2)
                        k = 9;
                    else if (bounds.getY() == 240 * 5)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 51:
                    if (bounds.getX() == 320 * 4)
                        k = 7;
                    else if (bounds.getX() == 320 * 5)
                        k = 8;
                    else
                        k = 9;
                    break;
                case 52:
                    if (bounds.getX() == 320 * 3)
                        k = 8;
                    else if (bounds.getX() == 320 * 6 && x < 320 * 6 + 160)
                        k = 9;
                    else if (bounds.getX() == 320 * 6 && x > 320 * 6 + 160)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 53:
                    if (bounds.getY() == 240 * 3)
                        k = 8;
                    else if (bounds.getX() == 320 * 5)
                        k = 9;
                    else if (bounds.getX() == 320 * 7)
                        k = 10;
                    else
                        k = 11;
                    break;
                case 54:
                    if (bounds.getX() == 320)
                        k = 13;
                    else if (bounds.getX() == 320 * 2 && bounds.getY() == 0)
                        k = 14;
                    else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 3)
                        k = 15;
                    else if (bounds.getX() == 320 * 7)
                        k = 16;
                    else if (bounds.getX() == 320 * 8)
                        k = 17;
                    else if (bounds.getX() == 320 * 9 && x < 320 * 9 + 4 * 16)
                        k = 18;
                    else if (bounds.getX() == 320 * 9 && x < 320 * 10)
                        k = 19;
                    else if (bounds.getX() == 320 * 9 && x < 320 * 10 + 16 * 16)
                        k = 20;
                    else
                        k = 21;
                    break;
                case 55:
                    if (bounds.getY() < 240 * 5)
                        k = 8;
                    else if (bounds.getY() == 240 * 5)
                        k = 11;
                    else if (bounds.getY() < 240 * 10)
                        k = 9;
                    else
                        k = 10;
                    break;
                case 56:
                    if (bounds.getY() == 240)
                        k = 7;
                    else if (bounds.getY() == 240 * 2)
                        k = 8;
                    else
                        k = 9;
                    break;
                case 57:
                    k = 7;
                    break;
                case 58:
                    if (bounds.getY() == 240 * 6)
                        k = 9;
                    else if (bounds.getY() == 240 * 4)
                        k = 10;
                    else if (bounds.getX() == 320 * 4)
                        k = 11;
                    else if (bounds.getX() == 320 * 5)
                        k = 12;
                    else
                        k = 13;
                    break;
                case 59:
                    if (bounds.getX() == 320 * 5)
                        k = 6;
                    else
                        k = 7;
                    break;
                case 60:
                    k = 5;
                    break;
                }
                if (k != 0)
                {
                    scene->setCoffre(map - 45, k, 1);
                }

                ouvrePorte(i, j, (dir == N || dir == S) ? 0 : 1);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 45, 3, scene->getCoffre(map - 45, 3) - 1);
            }
        }
        // boss
        if (scene->getCoffre(map - 45, 2) == 1 && dir == N)
        {
            int value = false;
            switch (map)
            {
            case 46:
                value = 3915;
                break;
            case 47:
                value = 4122;
                break;
            case 48:
                value = 4292;
                break;
            case 49:
                value = 4552;
                break;
            case 50:
                value = 4799;
                break;
            case 51:
                value = 5028;
                break;
            case 52:
                value = 5257;
                break;
            case 53:
                value = 5460;
                break;
            case 54:
                value = 5651;
                break;
            case 55:
                value = 5842;
                break;
            case 56:
                value = 6062;
                break;
            case 57:
                value = 6175;
                break;
            case 58:
                value = 6535;
                break;
            case 59:
                value = 6680;
                break;
            case 60:
                value = 6825;
                break;
            }
            if (getSol(x, y + 7) == value)
            {
                ouvrePorte(x / 16, ((y + 7) / 16) - 3, 0);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 45, 2, 2);
            }
        }
    }
    else if (map == 156)
    {

        // doors with keys
        if (scene->getCoffre(16, 3))
        {
            int i = 0;
            int j = 0;

            if (getSol(x, y + 7) == 6135 && dir == N)
            {
                i = x / 16;
                j = ((y + 7) / 16) - 3;
            }
            if (getSol(x, y + 24) == 6137 && dir == S)
            {
                i = x / 16;
                j = (y + 24) / 16;
            }
            if (getSol(x - 1, y + 16) == 6144 && dir == W)
            {
                i = ((x - 1) / 16) - 3;
                j = y / 16;
            }
            if (getSol(x + 16, y + 16) == 6149 && dir == E)
            {
                i = (x + 16) / 16;
                j = y / 16;
            }

            if (i != 0)
            {
                int k = 0;

                if (bounds.getY() == 240)
                    k = 19;
                else if (bounds.getY() == 0)
                    k = 20;
                else if (bounds.getY() == 240 * 7)
                    k = 21;
                else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 13)
                    k = 22;
                else if (bounds.getX() == 320 && bounds.getY() == 240 * 13)
                    k = 23;
                else if (bounds.getX() == 320 && bounds.getY() == 240 * 12)
                    k = 24;
                else if (bounds.getX() == 320 && bounds.getY() == 240 * 11)
                    k = 25;
                else if (bounds.getX() == 0 && bounds.getY() == 240 * 11)
                    k = 26;
                else if (bounds.getX() == 0 && bounds.getY() == 240 * 10)
                    k = 27;
                else if (bounds.getX() == 320 && bounds.getY() == 240 * 10)
                    k = 28;
                else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 10)
                    k = 29;
                else if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 11)
                    k = 30;
                else if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 11)
                    k = 31;
                else if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 12)
                    k = 32;
                else
                    k = 33;

                if (k != 0)
                {
                    scene->setCoffre(16, k, 1);
                }

                ouvrePorte(i, j, (dir == N || dir == S) ? 0 : 1);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(16, 3, scene->getCoffre(16, 3) - 1);
            }
        }
        // boss
        if (scene->getCoffre(16, 2) == 1 && dir == N)
        {
            int value = 6175;
            if (getSol(x, y + 7) == value)
            {
                ouvrePorte(x / 16, ((y + 7) / 16) - 3, 0);
                if (sound)
                    AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(16, 2, 2);
            }
        }
    }
}

void Map::ouvrePorteMaison(int x, int y)
{
    // int i = x / 16;
    int j = (y + 8) / 16;

    if (map == 4)
    {
        setSol(39 * 16, y + 8 - 1 - 16, 2281, MUR);
        setSol(40 * 16, y + 8 - 1 - 16, 2282, MUR);
        setSol(39 * 16, y + 8 - 1, 2283, PIERRE);
        setSol(40 * 16, y + 8 - 1, 2284, PIERRE);
        mur[39 * 2][j * 2 - 3] = PIERRE;
        mur[39 * 2 + 1][j * 2 - 3] = PIERRE;
        mur[40 * 2][j * 2 - 3] = PIERRE;
        mur[40 * 2 + 1][j * 2 - 3] = PIERRE;
    }
    else if (map == 19)
    {
        setSol(39 * 16, y + 8 - 1 - 16, 794, MUR);
        setSol(40 * 16, y + 8 - 1 - 16, 795, MUR);
        setSol(39 * 16, y + 8 - 1, 796, PIERRE);
        setSol(40 * 16, y + 8 - 1, 797, PIERRE);
        mur[39 * 2][j * 2 - 3] = PIERRE;
        mur[39 * 2 + 1][j * 2 - 3] = PIERRE;
        mur[40 * 2][j * 2 - 3] = PIERRE;
        mur[40 * 2 + 1][j * 2 - 3] = PIERRE;
    }
    else if (map == 34)
    {
        setSol(39 * 16, y + 8 - 1 - 16, 1908, MUR);
        setSol(40 * 16, y + 8 - 1 - 16, 1909, MUR);
        setSol(39 * 16, y + 8 - 1, 1910, PIERRE);
        setSol(40 * 16, y + 8 - 1, 1911, PIERRE);
        mur[39 * 2][j * 2 - 3] = PIERRE;
        mur[39 * 2 + 1][j * 2 - 3] = PIERRE;
        mur[40 * 2][j * 2 - 3] = PIERRE;
        mur[40 * 2 + 1][j * 2 - 3] = PIERRE;
    }
    else
    {
        setSol(x, y + 8 - 1, 474);
        setMur(x, y + 8 - 1, MUR, SOL_BOIS, MUR, SOL_BOIS);
        setSol(x + 16, y + 8 - 1, 475);
        setMur(x + 16, y + 8 - 1, SOL_BOIS, MUR, SOL_BOIS, MUR);
    }
}

void Map::testAnimRoom()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    switch (map)
    {
    case 46:
        if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 3 && mur[129 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 43, 0);
        }
        if (bounds.getX() <= 320 && bounds.getY() == 0 && mur[20 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 6, 1);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 3 && mur[180 * 2][52 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 51, 1);
        }
        if (bounds.getX() == 320 * 15 && bounds.getY() == 0 && mur[300 * 2][7 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(298, 6, 1);
        }
        if (bounds.getX() == 320 * 17)
        {
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(77);
                persistJarres(6);
            }
            else
            {
                AudioManager::getInstance()->playMusic(20);
            }
            if (link->getInventory()->hasCoeur(0) && sol[352][25] != 3144)
            {
                sol[352][25] = 3144;
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(0) && mur[249 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                fermePorte(249, 28, 0);
            }
            else if (link->getInventory()->hasCoeur(0) && mur[249 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 13, 0);
            }
            else if (link->getInventory()->hasMedaillon(0) && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 28, 0);
            }
        }
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2)
        {
            if (!scene->getCoffre(1, 25) && mur[9 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                persistJarres(3);
                fermePorte(9, 28, 0);
            }
            else if (!scene->getCoffre(1, 25) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(76);
                scene->setCoffre(1, 25, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(18, 36, 1);
                ouvrePorte(9, 28, 0);
            }
        }
        break;
    case 47:
        if (bounds.getX() == 320 * 16 && bounds.getY() == 240 * 4 && !nbCoffres() && isCaisse(326 * 16, 71 * 16) && isCaisse(328 * 16, 70 * 16) && isCaisse(330 * 16, 72 * 16) && isCaisse(332 * 16, 64 * 16) && isCaisse(334 * 16, 66 * 16))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addObject(new Coffre(322 * 16, 62 * 16 + 8, 1, false, TI_GANT));
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 2 && !nbCoffres() && !nbCaissesMovable())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(204 * 16, 34 * 16, TI_CLE, 5);
        }
        if (bounds.getX() == 320 * 16 && bounds.getY() == 240 * 2 && !nbCoffres() && !nbCaissesMovable() && isCaisse(329 * 16, 38 * 16) && isCaisse(330 * 16, 37 * 16) && isCaisse(330 * 16, 35 * 16) && isCaisse(331 * 16, 35 * 16) && isCaisse(332 * 16, 35 * 16) && isCaisse(332 * 16, 36 * 16) && isCaisse(332 * 16, 37 * 16))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(334 * 16, 33 * 16, TI_CLE, 8);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 && mur[180 * 2][22 * 2] == MUR && scene->getCoffre(2, 4))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(178, 21, 1);
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 4)
        {
            if (mur[280 * 2][82 * 2] == MUR && isCaisse(299 * 16, 75 * 16))
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(278, 81, 1);
                fermePorte(278, 66, 1);
                fermePorte(309, 58, 0);
                fermePorte(318, 81, 1);
            }
            else if (mur[280 * 2][67 * 2] == MUR && isCaisse(299 * 16, 74 * 16))
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(278, 66, 1);
                fermePorte(278, 81, 1);
                fermePorte(309, 58, 0);
                fermePorte(318, 81, 1);
            }
            else if (mur[309 * 2 + 1][58 * 2 + 1] == MUR && isCaisse(300 * 16, 74 * 16))
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(309, 58, 0);
                fermePorte(278, 81, 1);
                fermePorte(278, 66, 1);
                fermePorte(318, 81, 1);
            }
            else if (mur[320 * 2][82 * 2] == MUR && isCaisse(300 * 16, 75 * 16))
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(318, 81, 1);
                fermePorte(278, 81, 1);
                fermePorte(278, 66, 1);
                fermePorte(309, 58, 0);
            }
        }
        if (bounds.getX() == 320 * 13 && bounds.getY() == 240 * 5 && mur[260 * 2][82 * 2] == MUR && !nbCaissesMovable() && isCaisse(268 * 16, 80 * 16) && isCaisse(268 * 16, 83 * 16) && isCaisse(269 * 16, 84 * 16) && isCaisse(270 * 16, 82 * 16) && isCaisse(270 * 16, 84 * 16) && isCaisse(271 * 16, 84 * 16) && isCaisse(272 * 16, 80 * 16) && isCaisse(272 * 16, 83 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(258, 81, 1);
        }
        if (bounds.getX() == 320 * 16 && bounds.getY() == 0 && mur[340 * 2][7 * 2] == MUR && !nbCaissesMovable() && isCaisse(329 * 16, 6 * 16) && isCaisse(330 * 16, 6 * 16) && isCaisse(329 * 16, 7 * 16) && isCaisse(330 * 16, 7 * 16) && isCaisse(328 * 16, 5 * 16) && isCaisse(331 * 16, 5 * 16) && isCaisse(328 * 16, 8 * 16) && isCaisse(331 * 16, 8 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(338, 6, 1);
        }
        if (bounds.getX() == 320 * 17 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(1) && mur[349 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(79);
                fermePorte(349, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(1) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(1) && mur[349 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(349, 28, 0);
            }
            else if (link->getInventory()->hasMedaillon(1) && mur[349 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(349, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 16 && bounds.getY() == 240 * 3)
        {
            if (!scene->getCoffre(2, 20) && mur[329 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(18);
                fermePorte(329, 43, 0);
            }
            else if (!scene->getCoffre(2, 20) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(78);
                scene->setCoffre(2, 20, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(329, 58, 0);
                ouvrePorte(329, 43, 0);
            }
        }
        break;
    case 48:
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 4 && !nbEnnemis() && !nbCoffres())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(69 * 16, 66 * 16, TI_CLE, 4);
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 4 && !nbEnnemis() && !nbCoffres())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(216 * 16, 62 * 16, TI_CLE, 5);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 0 && !nbEnnemis() && sol[57][3] == 4002)
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addObject(new Interrupteur(57 * 16, 3 * 16, 0, false, this));
        }
        if (bounds.getX() == 320 && bounds.getY() == 240 * 2 && !nbEnnemis() && !nbCoffres())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(36 * 16, 33 * 16, TI_CARTE_DONJON, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 0 && !nbEnnemis() && sol[195][12] == 4002)
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addObject(new Interrupteur(195 * 16, 12 * 16, 0, false, this));
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2 && !nbEnnemis() && !nbCoffres())
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(244 * 16, 33 * 16, TI_BOUSSOLE, 0);
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(2) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(2) && mur[289 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(289, 28, 0);
            }
            else if (link->getInventory()->hasMedaillon(2) && sol[289][40] == 4172)
            {
                AudioManager::getInstance()->playSound(TS_SURPRISE);
                ouvrePorte(289, 40, 4);
            }
        }
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(2) && mur[9 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(82);
                fermePorte(9, 43, 0);
            }
            else if (link->getInventory()->hasMedaillon(2) && mur[9 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 2)
        {
            if (!scene->getCoffre(3, 28) && mur[129 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(81);
                fermePorte(129, 43, 0);
            }
            else if (!scene->getCoffre(3, 28) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(80);
                scene->setCoffre(3, 28, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(129, 28, 0);
                ouvrePorte(129, 43, 0);
                ouvrePorte(128, 34, 3);
                cleanImp();
            }
        }
        break;
    case 49:
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 4 && !nbEnnemis() && !scene->getCoffre(4, 21))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(103 * 16, 83 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(4, 21, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 && mur[169 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 13, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(3) && mur[199 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(85);
                fermePorte(199, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(3) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(3) && mur[199 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(199, 13, 0);
            }
            else if (scene->getCoffre(4, 30) && mur[199 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(199, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
        {
            if (!scene->getCoffre(4, 20) && mur[89 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(84);
                fermePorte(89, 28, 0);
            }
            else if (!scene->getCoffre(4, 20) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(83);
                scene->setCoffre(4, 20, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
                ouvrePorte(89, 28, 0);
            }
        }
        break;
    case 50:
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 2 && !nbEnnemis() && !scene->getCoffre(5, 38))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(49 * 16, 37 * 16, TI_BOUSSOLE, 0);
            scene->setCoffre(5, 38, 1);
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 2 && !nbEnnemis() && !scene->getCoffre(5, 39))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(290 * 16, 37 * 16, TI_CLE, 6);
            scene->setCoffre(5, 39, 1);
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 5 && !nbEnnemis() && !scene->getCoffre(5, 40))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(300 * 16, 90 * 16, TI_CLE, 7);
            scene->setCoffre(5, 40, 1);
        }
        if (bounds.getX() == 320 && bounds.getY() == 240 * 3 && mur[29 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(29, 58, 0);
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 4 && mur[109 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 58, 0);
        }
        if (bounds.getX() == 320 * 9 && (bounds.getY() == 240 * 2 || bounds.getY() == 240 * 3) && mur[189 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(189, 43, 0);
        }
        if (bounds.getX() == 320 * 11 && bounds.getY() == 240 && mur[220 * 2][22 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(218, 21, 1);
        }
        if (bounds.getX() == 320 * 11 && bounds.getY() == 240 * 2 && mur[240 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(238, 36, 1);
        }
        if (bounds.getX() == 320 * 11 && (bounds.getY() == 240 * 5 || bounds.getY() == 240 * 6) && mur[229 * 2 + 1][88 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 88, 0);
        }
        if (bounds.getX() == 320 * 13 && bounds.getY() == 240 * 5 && mur[269 * 2 + 1][88 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(269, 88, 0);
        }
        if (bounds.getX() == 320 * 15 && (bounds.getY() == 240 * 3 || bounds.getY() == 240 * 4) && mur[309 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(309, 58, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(4) && mur[249 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(88);
                fermePorte(249, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(4) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(4) && mur[249 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 13, 0);
            }
            else if (link->getInventory()->hasObject(CLE_TEMPS) && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 28, 0);
            }
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 3)
        {
            if (!scene->getCoffre(5, 41) && mur[169 * 2 + 1][58 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(87);
                fermePorte(169, 58, 0);
            }
            else if (!scene->getCoffre(5, 41) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(86);
                scene->setCoffre(5, 41, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(169, 43, 0);
                ouvrePorte(169, 58, 0);
            }
        }
        break;
    case 51:
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 && !nbEnnemis() && !scene->getCoffre(6, 27))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(150 * 16, 21 * 16, TI_BOUSSOLE, 0);
            scene->setCoffre(6, 27, 1);
        }
        if (bounds.getX() == 320 * 5 && (bounds.getY() == 240 * 2 || bounds.getY() == 240 * 3) && mur[109 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(109, 43, 0);
        }
        if ((bounds.getX() == 320 * 2 || bounds.getX() == 320 * 3) && bounds.getY() == 240 * 2 && mur[60 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(58, 36, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && mur[89 * 2 + 1][58 * 2 + 1] != MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            fermePorte(89, 58, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 2 && mur[169 * 2 + 1][58 * 2 + 1] != MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            fermePorte(169, 58, 0);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 4 && mur[89 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            ouvrePorte(89, 58, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 4 && mur[169 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            ouvrePorte(169, 58, 0);
        }
        if (bounds.getX() == 320 * 11 + 160 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(5) && mur[249 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(87);
                fermePorte(249, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(5) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(5) && mur[249 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 13, 0);
            }
            else if (link->getInventory()->hasObject(MARTEAU) && mur[249 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 2)
        {
            if (!scene->getCoffre(6, 28) && mur[140 * 2][37 * 2] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(77);
                fermePorte(138, 36, 1);
            }
            else if (!scene->getCoffre(6, 28) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(89);
                scene->setCoffre(6, 28, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(129, 28, 0);
                ouvrePorte(138, 36, 1);
                disablePiege();
            }
        }
        break;
    case 52:
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 4 && !nbEnnemis() && !scene->getCoffre(7, 21))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(90 * 16, 66 * 16, TI_CLE, 4);
            scene->setCoffre(7, 21, 1);
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 5 && !nbEnnemis() && !scene->getCoffre(7, 22))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(109 * 16, 82 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(7, 22, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 5 && !nbEnnemis() && !scene->getCoffre(7, 23))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(150 * 16, 82 * 16, TI_BOUSSOLE, 0);
            scene->setCoffre(7, 23, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && mur[100 * 2][22 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(98, 21, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 4 && mur[149 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(149, 58, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 5 && mur[169 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(169, 73, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(6) && mur[249 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(90);
                fermePorte(249, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(6) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
                addEffect(new FumeeBlanche(248 * 16 + 8, 32 * 16 + 8));
                ouvrePorte(248, 32, 3);
            }
            else if (link->getInventory()->hasCoeur(6) && mur[249 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 28, 0);
            }
            else if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && mur[249 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(249, 43, 0);
            }
        }
        if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 3)
        {
            if (!scene->getCoffre(7, 24) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playMusic(79);
            }
            else if (!scene->getCoffre(7, 24) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(24);
                scene->setCoffre(7, 24, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                addEffect(new FumeeBlanche(130 * 16 + 8, 52 * 16 + 8));
                ouvrePorte(130, 52, 2);
                ouvrePorte(129, 43, 0);
            }
        }
        break;
    case 53:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && !nbEnnemis() && !scene->getCoffre(8, 25))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(9 * 16, 37 * 16, TI_CLE, 4);
            scene->setCoffre(8, 25, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 4 && !nbEnnemis() && !scene->getCoffre(8, 26))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(89 * 16, 67 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(8, 26, 1);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3 && mur[69 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(69, 43, 0);
        }
        if (bounds.getX() >= 320 * 5 && bounds.getX() <= 320 * 6 && bounds.getY() == 240 * 7 && mur[120 * 2][112 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(118, 111, 1);
        }
        if (bounds.getX() == 320 * 11 && bounds.getY() == 240 * 3 && mur[229 * 2 + 1][43 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(229, 43, 0);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 5)
        {
            AudioManager::getInstance()->playMusic(nbEnnemis() ? 93 : 20);
            if (link->getInventory()->hasCoeur(7) && sol[192][85] != 3144)
            {
                sol[192][85] = 3144;
            }
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 0)
        {
            if (!link->getInventory()->hasCoeur(7) && mur[189 * 2 + 1][13 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                fermePorte(189, 13, 0);
            }
            else if (link->getInventory()->hasCoeur(7) && mur[200 * 2][7 * 2] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(198, 6, 1);
            }
            else if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && mur[189 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(189, 13, 0);
            }
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
        {
            if (!scene->getCoffre(8, 27) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(92);
                fermePorte(98, 21, 1);
            }
            else if (!scene->getCoffre(8, 27) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(91);
                scene->setCoffre(8, 27, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
                ouvrePorte(98, 21, 1);
            }
        }
        break;
    case 54:
        if (bounds.getX() == 320 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(9, 51))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(29 * 16, 7 * 16, TI_CLE, 4);
            scene->setCoffre(9, 51, 1);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2 && !nbEnnemis() && !scene->getCoffre(9, 52))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(71 * 16, 45 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(9, 52, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(9, 53))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(150 * 16, 6 * 16, TI_CLE, 10);
            scene->setCoffre(9, 53, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 5 && mur[100 * 2][82 * 2] == MUR && !nbCaissesMovable() && isCaisse(88 * 16, 83 * 16) && isCaisse(89 * 16, 84 * 16) && isCaisse(91 * 16, 82 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            scene->setCoffre(9, 54, 1);
            ouvrePorte(98, 81, 1);
        }
        if (bounds.getX() == 320 * 11 && bounds.getY() == 240 * 3 && mur[229 * 2 + 1][58 * 2 + 1] == MUR && !nbCaissesMovable() && isCaisse(228 * 16, 51 * 16) && isCaisse(228 * 16, 53 * 16) && isCaisse(231 * 16, 51 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            scene->setCoffre(9, 55, 1);
            ouvrePorte(229, 58, 0);
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 5 && mur[249 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(249, 73, 0);
        }
        if (bounds.getX() == 320 * 9 + 160 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(8) && mur[199 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(94);
                fermePorte(199, 28, 0);
            }
            else if (!link->getInventory()->hasCoeur(8) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
                disablePiege();
            }
            else if (link->getInventory()->hasCoeur(8) && mur[199 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(199, 13, 0);
            }
            else if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && mur[199 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(199, 28, 0);
            }
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 0)
        {
            if (!scene->getCoffre(9, 56) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(81);
                fermePorte(58, 6, 1);
            }
            else if (!scene->getCoffre(9, 56) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(30);
                scene->setCoffre(9, 56, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(58, 6, 1);
                ouvrePorte(78, 6, 1);
            }
        }
        break;
    case 55:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && !nbEnnemis() && !scene->getCoffre(10, 51))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(9 * 16, 36 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(10, 51, 1);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(10, 52))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(50 * 16, 6 * 16, TI_CLE, 4);
            scene->setCoffre(10, 52, 1);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(10, 53))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(69 * 16, 6 * 16, TI_CLE, 5);
            scene->setCoffre(10, 53, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(10, 54))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(89 * 16, 6 * 16, TI_CLE, 6);
            scene->setCoffre(10, 54, 1);
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 12 && !nbEnnemis() && !scene->getCoffre(10, 55))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(110 * 16, 186 * 16, TI_BOUSSOLE, 0);
            scene->setCoffre(10, 55, 1);
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 && link->getX() >= 68 * 16 && link->getY() > 55 * 16 && !link->getInventory()->hasCoeur(9) && mur[69 * 2 + 1][58 * 2 + 1] != MUR)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            fermePorte(69, 58, 0);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
        {
            AudioManager::getInstance()->playMusic(nbEnnemis() ? 97 : 20);
            if (link->getInventory()->hasCoeur(9) && sol[65][38] != 3144)
            {
                sol[65][38] = 3144;
                setSol(70 * 16, 197 * 16, 1, 1, 5942, BOIS);
            }
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 10)
        {
            if (!scene->getCoffre(10, 56) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(96);
                fermePorte(58, 156, 1);
            }
            else if (!scene->getCoffre(10, 56) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(95);
                scene->setCoffre(10, 56, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(58, 156, 1);
                ouvrePorte(78, 156, 1);
                cleanFlamme();
            }
        }
        break;
    case 56:
        if (!scene->getCoffre(11, 12))
            break;
        if (bounds.getX() == 0 && bounds.getY() == 240 && !nbEnnemis() && !scene->getCoffre(11, 14))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(30 * 16, 21 * 16, TI_CLE, 4);
            scene->setCoffre(11, 14, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 3 && !nbEnnemis() && !scene->getCoffre(11, 15))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(90 * 16, 51 * 16, TI_CARTE_DONJON, 0);
            scene->setCoffre(11, 15, 1);
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 && !nbEnnemis() && !scene->getCoffre(11, 16))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(109 * 16, 21 * 16, TI_CLE, 5);
            scene->setCoffre(11, 16, 1);
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(11, 17))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(149 * 16, 6 * 16, TI_BOUSSOLE, 0);
            scene->setCoffre(11, 17, 1);
        }
        if (bounds.getX() == 320 * 9 && bounds.getY() == 0 && !nbEnnemis() && !scene->getCoffre(11, 18))
        {
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            addCoffre(190 * 16, 6 * 16, TI_CLE, 6);
            scene->setCoffre(11, 18, 1);
        }
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && mur[40 * 2][37 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(38, 36, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 2 && mur[89 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 28, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 0 && link->getInventory()->hasCoeur(10) && link->getEpee() < 5)
        {
            AudioManager::getInstance()->playMusic(28);
            MainController::getInstance()->getGameController()->displayText(1277);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240)
        {
            if (!link->getInventory()->hasCoeur(10) && mur[169 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(98);
                fermePorte(169, 28, 0);
                if (scene->getAvancement() < AV_SPEECH_AGAHNIM)
                {
                    MainController::getInstance()->getGameController()->displayText(1269);
                }
            }
            else if (!link->getInventory()->hasCoeur(10) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
                addObject(new Pnj(16 * 169 - 2 + 8, 16 * 6 + 5 - 8, 90, 1277));
            }
            else if (link->getInventory()->hasCoeur(10) && mur[169 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(169, 13, 0);
            }
        }
        if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 6)
        {
            if (!scene->getCoffre(11, 19) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(92);
                fermePorte(118, 96, 1);
            }
            else if (!scene->getCoffre(11, 19) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(0);
                scene->setCoffre(11, 19, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(98, 96, 1);
                ouvrePorte(118, 96, 1);
                disablePiege();
            }
        }
        break;
    case 57:
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 && link->getStatus()->getMaxRupees() == 0 && link->getBouclier() == 0 && link->getY() > 20 * 16)
        {
            MainController::getInstance()->getGameController()->displayText(1330);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 0 && link->getStatus()->getMaxRupees() == 0 && link->getBouclier() == 0)
        {
            MainController::getInstance()->getGameController()->displayText(1331);
        }
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 && scene->getAvancement() < AV_PARLE_ZELDA_PALAIS)
        {
            AudioManager::getInstance()->playMusic(101);
            MainController::getInstance()->getGameController()->displayText(1310);
        }
        if (scene->getAvancement() < AV_TELE_ZELDA)
            break;
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 10 && mur[80 * 2][157 * 2] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(78, 156, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 11 && mur[89 * 2 + 1][178 * 2 + 1] == MUR && !nbEnnemis())
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 178, 0);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 0 && mur[169 * 2 + 1][13 * 2 + 1] != MUR)
        {
            MainController::getInstance()->getGameController()->displayText(scene->getAvancement() < AV_SPEECH_GANONDORF ? 1372 : 1384);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 0 && !nbEnnemis())
        {
            AudioManager::getInstance()->playMusic(20);
        }
        if (bounds.getX() == 320 * 8 && bounds.getY() == 240)
        {
            if (!scene->getMonsters(50) && mur[169 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(28);
                fermePorte(169, 28, 0);
                if (scene->getAvancement() < AV_SPEECH_GANON)
                {
                    MainController::getInstance()->getGameController()->displayText(1371);
                }
            }
            else if (scene->getMonsters(50) && mur[169 * 2 + 1][13 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playMusic(27);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(169, 13, 0);
            }
        }
        if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 15)
        {
            if (!scene->getCoffre(12, 11) && nbEnnemis() > 0)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(99);
                fermePorte(49, 238, 0);
            }
            else if (!scene->getCoffre(12, 11) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(27);
                scene->setCoffre(12, 11, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 231, 1);
                ouvrePorte(58, 231, 1);
                ouvrePorte(49, 238, 0);
                disablePiege();
            }
        }
        break;
    case 58:
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(11) && mur[69 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(103);
                fermePorte(69, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(11) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(11) && mur[69 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(69, 28, 0);
            }
            else if (link->getBouclier() == 4 && mur[69 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(69, 43, 0);
            }
        }
        break;
    case 59:
        if (bounds.getX() == 320 * 13 + 160 && bounds.getY() == 240 * 2)
        {
            if (!link->getInventory()->hasCoeur(12) && mur[279 * 2 + 1][43 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(92);
                fermePorte(279, 43, 0);
            }
            else if (!link->getInventory()->hasCoeur(12) && nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
            else if (link->getInventory()->hasCoeur(12) && mur[279 * 2 + 1][28 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(279, 28, 0);
            }
            else if (link->getTunique() == 4 && mur[279 * 2 + 1][43 * 2 + 1] == MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(279, 43, 0);
            }
        }
        break;
    case 60:
        if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 5)
        {
            if (mur[69 * 2 + 1][88 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->stopMusic();
                MainController::getInstance()->getGameController()->displayText(1654);
                AudioManager::getInstance()->playSound(TS_DOOR);
                fermePorte(69, 88, 0);
            }
            else if (nbEnnemis() == 0)
            {
                AudioManager::getInstance()->playMusic(20);
            }
        }
        break;
    case 68:
        if (bounds.getX() == 320 && bounds.getY() == 0 && scene->getAvancement() == AV_GARS_MINE_AIDE && link->getX() < 25 * 16)
        {
            MainController::getInstance()->getGameController()->displayText(587);
        }
        break;
    case 137:
        if (bounds.getY() == 240)
        {
            if (mur[9 * 2 + 1][28 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                AudioManager::getInstance()->playMusic(28);
                fermePorte(9, 28, 0);
                MainController::getInstance()->getGameController()->displayText(1060);
            }
        }
        break;
    case 156:
        if (bounds.getX() == 0 && bounds.getY() == 240 * 5 && mur[20 * 2][82 * 2] != PIERRE && !nbCaissesMovable() && isCaisse(8 * 16, 83 * 16) && isCaisse(9 * 16, 82 * 16) && isCaisse(9 * 16, 80 * 16) && isCaisse(10 * 16, 80 * 16) && isCaisse(11 * 16, 80 * 16) && isCaisse(11 * 16, 81 * 16) && isCaisse(11 * 16, 82 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 81, 1);
            scene->setCoffre(17, 37, 1);
        }
        if (bounds.getX() == 320 && bounds.getY() == 240 * 17 && mur[20 * 2][262 * 2] != PIERRE && !nbCaissesMovable() && isCaisse(27 * 16, 260 * 16) && isCaisse(27 * 16, 263 * 16) && isCaisse(28 * 16, 264 * 16) && isCaisse(29 * 16, 262 * 16) && isCaisse(29 * 16, 264 * 16) && isCaisse(30 * 16, 264 * 16) && isCaisse(31 * 16, 260 * 16) && isCaisse(31 * 16, 263 * 16))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 261, 1);
            scene->setCoffre(17, 40, 1);
        }
        if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 16 && mur[89 * 2 + 1][238 * 2 + 1] != PIERRE && !nbCaissesMovable() && isCaisse(90 * 16, 247 * 16) && nbCaisses() == 1)
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(89, 238, 0);
            scene->setCoffre(17, 41, 1);
        }

        if (bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2)
        {
            if (nbObjects() || nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(108);
            }
            else
            {
                MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->setBossLife(0, 1);
                AudioManager::getInstance()->playMusic(107);
                if (sol[192][40] != 3144)
                {
                    sol[192][40] = 3144;
                    addObject(new Pnj(149 * 16 + 8, 4 * 16, 112, 1725));
                }
            }
        }
        if (bounds.getX() == 320 * 7 && bounds.getY() == 0)
        {
            if (mur[149 * 2 + 1][13 * 2 + 1] != MUR)
            {
                AudioManager::getInstance()->playSound(TS_DOOR);
                fermePorte(149, 13, 0);
            }
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 15 && !scene->getCoffre(17, 43))
        {
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(97);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 43, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(218, 231, 1);
                setSol(216 * 16, 232 * 16, 2, 1, 4002, PIERRE);
                addEffect(new FumeeBlanche(217 * 16, 232 * 16 + 8));
            }
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 18 && !scene->getCoffre(17, 44))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(90);
                fermePorte(209, 283, 0);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 44, 1);
                addEffect(new FumeeBlanche(208 * 16 + 8, 272 * 16 + 8));
                setSol(208 * 16, 272 * 16, 1, 1, 6960, BOIS);
                ouvrePorte(209, 283, 0);
                ouvrePorte(209, 268, 0);
            }
        }
        if (bounds.getX() == 320 * 10 && bounds.getY() == 240 * 19 && !scene->getCoffre(17, 45))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(82);
                fermePorte(218, 291, 1);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 45, 1);
                ouvrePorte(218, 291, 1);
                ouvrePorte(209, 283, 0);
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 15 && !scene->getCoffre(17, 46))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(87);
                fermePorte(249, 238, 0);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 46, 1);
                ouvrePorte(249, 238, 0);
                ouvrePorte(258, 231, 1);
                disablePiege();
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 16 && !scene->getCoffre(17, 47))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(77);
                fermePorte(249, 253, 0);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 47, 1);
                ouvrePorte(249, 253, 0);
                ouvrePorte(249, 238, 0);
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 18 && !scene->getCoffre(17, 48))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(77);
                fermePorte(238, 276, 1);
                fermePorte(258, 276, 1);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 48, 1);
                ouvrePorte(238, 276, 1);
                ouvrePorte(258, 276, 1);
            }
        }
        if (bounds.getX() == 320 * 12 && bounds.getY() == 240 * 19 && !scene->getCoffre(17, 49))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(96);
                fermePorte(238, 291, 1);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 49, 1);
                ouvrePorte(238, 291, 1);
                ouvrePorte(278, 291, 1);
                cleanFlamme();
            }
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 15 && !scene->getCoffre(17, 50))
        {
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(93);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 50, 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(289, 238, 0);
            }
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 18 && !scene->getCoffre(17, 51))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(94);
                fermePorte(289, 283, 0);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 51, 1);
                ouvrePorte(289, 283, 0);
                ouvrePorte(289, 268, 0);
            }
        }
        if (bounds.getX() == 320 * 14 && bounds.getY() == 240 * 19 && !scene->getCoffre(17, 52))
        {
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (nbEnnemis())
            {
                AudioManager::getInstance()->playMusic(81);
                fermePorte(278, 291, 1);
            }
            else
            {
                AudioManager::getInstance()->playMusic(36);
                scene->setCoffre(17, 52, 1);
                ouvrePorte(278, 291, 1);
                ouvrePorte(289, 283, 0);
            }
        }
        break;
    }
}

void Map::addCoffre(int x, int y, TypeItem type, int id)
{
    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    addObject(new Coffre(x, y, 0, false, type, id));
    BoundingBox b(x, y, 16, 16);
    if (b.intersect(link->getBoundingBox()))
    {
        link->setY(y + 8);
    }
}

void Map::permuteBlocs(int step)
{
    // 1 = orange up - blue down
    switch (map)
    { // orange = 624, blue = 625, +2 = up
    case 24:
        if (step == 0)
        {
            setSol(17 * 16, 31 * 16, 1, 5, 627, MURRET);
        }
        else
        {
            setSol(17 * 16, 31 * 16, 1, 5, 625, PIERRE);
        }
        break;
    case 47:
        if (step == 0)
        {
            setSol(307 * 16, 82 * 16, 1, 1, 627, MURRET);
            setSol(269 * 16, 82 * 16, 1, 1, 627, MURRET);
            setSol(271 * 16, 82 * 16, 1, 1, 627, MURRET);
            setSol(307 * 16, 43 * 16, 1, 4, 627, MURRET);
            setSol(312 * 16, 35 * 16, 4, 1, 627, MURRET);
            setSol(187 * 16, 11 * 16, 6, 1, 627, MURRET);
            setSol(187 * 16, 12 * 16, 1, 1, 627, MURRET);
            setSol(192 * 16, 12 * 16, 1, 1, 627, MURRET);
            setSol(288 * 16, 26 * 16, 4, 1, 627, MURRET);
            setSol(263 * 16, 6 * 16, 1, 3, 627, MURRET);
            setSol(328 * 16, 41 * 16, 4, 1, 627, MURRET);
            setSol(175 * 16, 21 * 16, 1, 3, 627, MURRET);

            setSol(229 * 16, 37 * 16, 2, 1, 624, PIERRE);
            setSol(345 * 16, 66 * 16, 1, 3, 624, PIERRE);
            setSol(315 * 16, 76 * 16, 1, 1, 624, PIERRE);
            setSol(299 * 16, 45 * 16, 1, 1, 624, PIERRE);
            setSol(310 * 16, 46 * 16, 2, 1, 624, PIERRE);
            setSol(189 * 16, 7 * 16, 2, 1, 624, PIERRE);
            setSol(279 * 16, 22 * 16, 1, 2, 624, PIERRE);
            setSol(149 * 16, 67 * 16, 2, 1, 624, PIERRE);
            setSol(323 * 16, 36 * 16, 1, 3, 624, PIERRE);
            setSol(328 * 16, 24 * 16, 4, 1, 624, PIERRE);
        }
        else
        {
            setSol(307 * 16, 82 * 16, 1, 1, 625, PIERRE);
            setSol(269 * 16, 82 * 16, 1, 1, 625, PIERRE);
            setSol(271 * 16, 82 * 16, 1, 1, 625, PIERRE);
            setSol(307 * 16, 43 * 16, 1, 4, 625, PIERRE);
            setSol(312 * 16, 35 * 16, 4, 1, 625, PIERRE);
            setSol(187 * 16, 11 * 16, 6, 1, 625, PIERRE);
            setSol(187 * 16, 12 * 16, 1, 1, 625, PIERRE);
            setSol(192 * 16, 12 * 16, 1, 1, 625, PIERRE);
            setSol(288 * 16, 26 * 16, 4, 1, 625, PIERRE);
            setSol(263 * 16, 6 * 16, 1, 3, 625, PIERRE);
            setSol(328 * 16, 41 * 16, 4, 1, 625, PIERRE);
            setSol(175 * 16, 21 * 16, 1, 3, 625, PIERRE);

            setSol(229 * 16, 37 * 16, 2, 1, 626, MURRET);
            setSol(345 * 16, 66 * 16, 1, 3, 626, MURRET);
            setSol(315 * 16, 76 * 16, 1, 1, 626, MURRET);
            setSol(299 * 16, 45 * 16, 1, 1, 626, MURRET);
            setSol(310 * 16, 46 * 16, 2, 1, 626, MURRET);
            setSol(189 * 16, 7 * 16, 2, 1, 626, MURRET);
            setSol(279 * 16, 22 * 16, 1, 2, 626, MURRET);
            setSol(149 * 16, 67 * 16, 2, 1, 626, MURRET);
            setSol(323 * 16, 36 * 16, 1, 3, 626, MURRET);
            setSol(328 * 16, 24 * 16, 4, 1, 626, MURRET);
        }
        break;
    case 62:
        if (step == 0)
        {
            setSol(8 * 16, 5 * 16, 5, 1, 627, MURRET);

            setSol(7 * 16, 11 * 16, 6, 1, 624, PIERRE);
            setSol(7 * 16, 12 * 16, 1, 1, 624, PIERRE);
            setSol(12 * 16, 12 * 16, 1, 1, 624, PIERRE);
        }
        else
        {
            setSol(8 * 16, 5 * 16, 5, 1, 625, PIERRE);

            setSol(7 * 16, 11 * 16, 6, 1, 626, MURRET);
            setSol(7 * 16, 12 * 16, 1, 1, 626, MURRET);
            setSol(12 * 16, 12 * 16, 1, 1, 626, MURRET);
        }
        break;
    case 156:
        if (step == 0)
        {
            setSol(176 * 16, 81 * 16, 1, 3, 627, MURRET);
            setSol(128 * 16, 184 * 16, 1, 4, 627, MURRET);
            setSol(128 * 16, 187 * 16, 5, 1, 627, MURRET);
            setSol(166 * 16, 185 * 16, 8, 1, 627, MURRET);
            setSol(166 * 16, 185 * 16, 1, 4, 627, MURRET);
            setSol(173 * 16, 185 * 16, 1, 4, 627, MURRET);
            setSol(166 * 16, 189 * 16, 8, 1, 627, MURRET);
            setSol(126 * 16, 242 * 16, 1, 2, 627, MURRET);
            setSol(127 * 16, 275 * 16, 6, 1, 627, MURRET);
            setSol(143 * 16, 291 * 16, 1, 3, 627, MURRET);
            setSol(148 * 16, 236 * 16, 1, 2, 627, MURRET);
            setSol(169 * 16, 291 * 16, 1, 3, 627, MURRET);
            setSol(177 * 16, 291 * 16, 1, 3, 627, MURRET);
            setSol(185 * 16, 291 * 16, 1, 3, 627, MURRET);
            setSol(189 * 16, 279 * 16, 2, 1, 627, MURRET);
            setSol(176 * 16, 249 * 16, 2, 1, 627, MURRET);
            setSol(176 * 16, 250 * 16, 1, 1, 627, MURRET);
            setSol(169 * 16, 254 * 16, 2, 1, 627, MURRET);
            setSol(183 * 16, 261 * 16, 1, 3, 627, MURRET);

            setSol(106 * 16, 245 * 16, 8, 1, 624, PIERRE);
            setSol(106 * 16, 245 * 16, 1, 4, 624, PIERRE);
            setSol(113 * 16, 245 * 16, 1, 4, 624, PIERRE);
            setSol(106 * 16, 249 * 16, 8, 1, 624, PIERRE);
            setSol(116 * 16, 291 * 16, 1, 3, 624, PIERRE);
            setSol(126 * 16, 251 * 16, 2, 1, 624, PIERRE);
            setSol(131 * 16, 236 * 16, 1, 2, 624, PIERRE);
            setSol(135 * 16, 276 * 16, 1, 3, 624, PIERRE);
            setSol(150 * 16, 257 * 16, 1, 2, 624, PIERRE);
            setSol(155 * 16, 253 * 16, 2, 1, 624, PIERRE);
            setSol(156 * 16, 291 * 16, 1, 3, 624, PIERRE);
            setSol(166 * 16, 275 * 16, 8, 1, 624, PIERRE);
            setSol(166 * 16, 275 * 16, 1, 4, 624, PIERRE);
            setSol(173 * 16, 275 * 16, 1, 4, 624, PIERRE);
            setSol(166 * 16, 279 * 16, 8, 1, 624, PIERRE);
            setSol(173 * 16, 291 * 16, 1, 3, 624, PIERRE);
            setSol(181 * 16, 291 * 16, 1, 3, 624, PIERRE);
            setSol(187 * 16, 243 * 16, 6, 1, 624, PIERRE);
        }
        else
        {
            setSol(176 * 16, 81 * 16, 1, 3, 625, PIERRE);
            setSol(128 * 16, 184 * 16, 1, 4, 625, PIERRE);
            setSol(128 * 16, 187 * 16, 5, 1, 625, PIERRE);
            setSol(166 * 16, 185 * 16, 8, 1, 625, PIERRE);
            setSol(166 * 16, 185 * 16, 1, 4, 625, PIERRE);
            setSol(173 * 16, 185 * 16, 1, 4, 625, PIERRE);
            setSol(166 * 16, 189 * 16, 8, 1, 625, PIERRE);
            setSol(126 * 16, 242 * 16, 1, 2, 625, PIERRE);
            setSol(127 * 16, 275 * 16, 6, 1, 625, PIERRE);
            setSol(143 * 16, 291 * 16, 1, 3, 625, PIERRE);
            setSol(148 * 16, 236 * 16, 1, 2, 625, PIERRE);
            setSol(169 * 16, 291 * 16, 1, 3, 625, PIERRE);
            setSol(177 * 16, 291 * 16, 1, 3, 625, PIERRE);
            setSol(185 * 16, 291 * 16, 1, 3, 625, PIERRE);
            setSol(189 * 16, 279 * 16, 2, 1, 625, PIERRE);
            setSol(176 * 16, 249 * 16, 2, 1, 625, PIERRE);
            setSol(176 * 16, 250 * 16, 1, 1, 625, PIERRE);
            setSol(169 * 16, 254 * 16, 2, 1, 625, PIERRE);
            setSol(183 * 16, 261 * 16, 1, 3, 625, PIERRE);

            setSol(106 * 16, 245 * 16, 8, 1, 626, MURRET);
            setSol(106 * 16, 245 * 16, 1, 4, 626, MURRET);
            setSol(113 * 16, 245 * 16, 1, 4, 626, MURRET);
            setSol(106 * 16, 249 * 16, 8, 1, 626, MURRET);
            setSol(116 * 16, 291 * 16, 1, 3, 626, MURRET);
            setSol(126 * 16, 251 * 16, 2, 1, 626, MURRET);
            setSol(131 * 16, 236 * 16, 1, 2, 626, MURRET);
            setSol(135 * 16, 276 * 16, 1, 3, 626, MURRET);
            setSol(150 * 16, 257 * 16, 1, 2, 626, MURRET);
            setSol(155 * 16, 253 * 16, 2, 1, 626, MURRET);
            setSol(156 * 16, 291 * 16, 1, 3, 626, MURRET);
            setSol(166 * 16, 275 * 16, 8, 1, 626, MURRET);
            setSol(166 * 16, 275 * 16, 1, 4, 626, MURRET);
            setSol(173 * 16, 275 * 16, 1, 4, 626, MURRET);
            setSol(166 * 16, 279 * 16, 8, 1, 626, MURRET);
            setSol(173 * 16, 291 * 16, 1, 3, 626, MURRET);
            setSol(181 * 16, 291 * 16, 1, 3, 626, MURRET);
            setSol(187 * 16, 243 * 16, 6, 1, 626, MURRET);
        }
        break;
    }
}

void Map::switchSphere(bool blue)
{
    List list;
    BoundingBox *box = new BoundingBox(0, 0, w, h);
    objects->get(box, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Sphere *sphere = dynamic_cast<Sphere *>(list.getNext());
        if (sphere != 0)
        {
            sphere->setBlue(blue);
        }
    }
    delete box;
}

void Map::switchStar()
{
    List list;
    BoundingBox *box = new BoundingBox(0, 0, w, h);
    objects->get(box, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        InterrupteurStar *star = dynamic_cast<InterrupteurStar *>(list.getNext());
        if (star != 0)
        {
            star->switchMode();
        }
    }
    delete box;
}

void Map::disablePiege()
{
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PiegeDemi *demi = dynamic_cast<PiegeDemi *>(element);
        PiegeColere *colere = dynamic_cast<PiegeColere *>(element);
        PiegeUltime *ultime = dynamic_cast<PiegeUltime *>(element);
        if (demi != 0)
        {
            demi->disable();
        }
        else if (colere != 0)
        {
            colere->disable();
        }
        else if (ultime != 0)
        {
            ultime->disable();
        }
    }
}

int Map::nbObjects()
{
    List list;
    objects->get(&bounds, &list);
    return list.size();
}

int Map::nbEnnemis()
{
    List list;
    ennemis->get(&bounds, &list);
    return list.size();
}

int Map::nbCoffres()
{
    List list;
    objects->get(&bounds, &list);
    int total = 0;
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
        if (coffre != 0)
        {
            total++;
        }
    }
    return total;
}

void Map::closeChests()
{
    if (map == 89)
    {
        Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
        int nbCoeur = (link->getInventory()->hasQuartCoeur(15) ? 0 : 1);
        int nbGemmes = (link->getInventory()->hasGemmeForce(160) ? 0 : 1) + (link->getInventory()->hasGemmeForce(161) ? 0 : 1) + (link->getInventory()->hasGemmeForce(162) ? 0 : 1);

        int chests[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        for (int i = 0; i < nbCoeur + nbGemmes; i++)
        {
            int randomValue = (int)((float)rand() / RAND_MAX * (9 - i));
            if (i > 0)
            {
                for (int j = 0; j <= randomValue; j++)
                {
                    if (chests[j])
                    {
                        randomValue++;
                    }
                }
            }

            chests[randomValue] = (nbCoeur && i == 0) ? 1 : 2;
        }

        BoundingBox b(6 * 16, 6 * 16, 5 * 16, 5 * 16);
        List list;
        objects->get(&b, &list);

        int num = 0;
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
            if (coffre != 0)
            {
                if (chests[num] == 1)
                {
                    coffre->close(TI_QUART_COEUR, 15);
                }
                else if (chests[num] == 2)
                {
                    coffre->close(TI_GEMME_FORCE, 160 + 3 - nbGemmes);
                }
                else
                {
                    coffre->close(TI_NO_ITEM);
                }
                num++;
            }
        }
    }
}

void Map::openChests(int x, int y)
{
    if (map != 89)
        return;

    List list;
    BoundingBox b(6 * 16, 6 * 16, 5 * 16, 5 * 16);
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
        if (coffre != 0)
        {
            coffre->open(true);
        }
    }
}

bool Map::areChestsClosed()
{
    if (map != 89)
        return false;

    BoundingBox b(6 * 16, 6 * 16, 16, 16);
    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Coffre *coffre = dynamic_cast<Coffre *>(list.getNext());
        if (coffre != 0)
        {
            return !coffre->isOpened();
        }
    }

    return false;
}

void Map::pnjBoitCafe(bool boit)
{
    if (map != 119)
        return;

    BoundingBox b(16 * 11 + 8, 16 * 5, 16, 16);
    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Pnj *pnj = dynamic_cast<Pnj *>(list.getNext());
        if (pnj != 0)
        {
            pnj->setAnimMax(boit ? 1 : 0);
            return;
        }
    }
}

int Map::nbCaissesMovable()
{
    List list;
    objects->get(&bounds, &list);
    int total = 0;

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Caisse *caisse = dynamic_cast<Caisse *>(list.getNext());
        if (caisse != 0 && caisse->getNbMoves() != 0)
        {
            total++;
        }
    }
    return total;
}

int Map::nbCaisses()
{
    List list;
    objects->get(&bounds, &list);
    int total = 0;

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Caisse *caisse = dynamic_cast<Caisse *>(list.getNext());
        if (caisse != 0)
        {
            total++;
        }
    }
    return total;
}

bool Map::isCaisse(int x, int y)
{
    List list;
    BoundingBox b(x, y, 16, 16);
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Caisse *caisse = dynamic_cast<Caisse *>(list.getNext());
        if (caisse != 0)
        {
            return true;
        }
    }
    return false;
}

void Map::enervePoules()
{
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Poule *poule = dynamic_cast<Poule *>(element);
        PouleBig *big = dynamic_cast<PouleBig *>(element);
        if (poule != 0)
        {
            poule->enerve();
        }
        else if (big != 0)
        {
            big->enerve();
        }
    }
}

void Map::cachetteZora(bool cache)
{
    List list;
    ennemis->get(&bounds, &list, false);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Ennemi010 *zora = dynamic_cast<Ennemi010 *>(list.getNext());
        if (zora != 0)
        {
            zora->cachette(cache, true);
        }
    }
}

int Map::getOldBarque()
{
    return oldBarque;
}

void Map::updatePonton(int x, int y)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (x / 16 == 118 && y / 16 == 46)
    {
        scene->setCoffre(0, 5, 0);
    }
    else if (x / 16 == 105 && y / 16 == 27)
    {
        scene->setCoffre(0, 5, 1);
    }
    else if (x / 16 == 76 && y / 16 == 52)
    {
        scene->setCoffre(0, 5, 2);
    }
    else if (x / 16 == 50 && y / 16 == 34)
    {
        scene->setCoffre(0, 5, 3);
    }
    else if (x / 16 == 32 && y / 16 == 55)
    {
        scene->setCoffre(0, 5, 4);
    }
    else if (x / 16 == 13 && y / 16 == 16)
    {
        scene->setCoffre(0, 5, 5);
    }
}

void Map::barque(bool visible)
{
    if (map != 26)
        return;
    int a;
    int b;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (scene->getCoffre(0, 5))
    {
    case 0:
        a = 118;
        b = 48;
        break;
    case 1:
        a = 105;
        b = 29;
        break;
    case 2:
        a = 76;
        b = 54;
        break;
    case 3:
        a = 50;
        b = 36;
        break;
    case 4:
        a = 32;
        b = 57;
        break;
    case 5:
        a = 13;
        b = 18;
        break;
    default:
        a = 118;
        b = 48;
        break;
    }

    if (visible)
    {
        setSol(a * 16, (b - 1) * 16, 2624);
        setMur(a * 16, (b - 1) * 16, MURRET, PIERRE, MURRET, SOL_BOIS);
        setSol((a + 1) * 16, (b - 1) * 16, 2627);
        setMur((a + 1) * 16, (b - 1) * 16, PIERRE, MURRET, SOL_BOIS, MURRET);

        setSol(a * 16, b * 16, 2630);
        setMur(a * 16, b * 16, MURRET, SOL_BOIS, MURRET, SOL_BOIS);
        setSol((a + 1) * 16, b * 16, 2631);
        setMur((a + 1) * 16, b * 16, SOL_BOIS, MURRET, SOL_BOIS, MURRET);
        setAir(a * 16, b * 16, 2632);
        setAir((a + 1) * 16, b * 16, 2633);

        setSol(a * 16, (b + 1) * 16, 2634);
        setMur(a * 16, (b + 1) * 16, MURRET, MURRET, EAU_PROF, EAU_PROF);
        setSol((a + 1) * 16, (b + 1) * 16, 2635);
        setMur((a + 1) * 16, (b + 1) * 16, MURRET, MURRET, EAU_PROF, EAU_PROF);
    }
    else
    {
        setSol(a * 16, (b - 1) * 16, 67);
        setMur(a * 16, (b - 1) * 16, MURRET, PIERRE, EAU_PROF, EAU_PROF);
        setSol((a + 1) * 16, (b - 1) * 16, 70);
        setMur((a + 1) * 16, (b - 1) * 16, PIERRE, MURRET, EAU_PROF, EAU_PROF);
        setSol(a * 16, b * 16, 328, EAU_PROF);
        setAir(a * 16, b * 16, -1);
        setSol((a + 1) * 16, b * 16, 328, EAU_PROF);
        setAir((a + 1) * 16, b * 16, -1);
        setSol(a * 16, (b + 1) * 16, 328, EAU_PROF);
        setSol((a + 1) * 16, (b + 1) * 16, 328, EAU_PROF);
    }
}

void Map::addWagon()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (scene->getCoffre(0, 14))
    {
    case 0:
        addObject(new Wagon(29 * 16, 23 * 16, E));
        break;
    case 1:
        addObject(new Wagon(50 * 16, 22 * 16, W));
        break;
    case 2:
        addObject(new Wagon(30 * 16, 5 * 16, E));
        break;
    }
}

void Map::switchLevier()
{
    BoundingBox bb;
    if (map == 68)
    {
        bb = BoundingBox(36 * 16, 23 * 16, 16, 16);
    }
    else
    {
        bb = BoundingBox(14 * 16, 9 * 16, 16, 16);
    }
    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Switch *levier = dynamic_cast<Switch *>(element);
        if (levier != 0)
        {
            levier->switchLeft();
        }
    }
}

void Map::displayInterruptor(int x, int y)
{
    BoundingBox bb = BoundingBox(x, y, 16, 16);
    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Interrupteur *inter = dynamic_cast<Interrupteur *>(element);
        InterrupteurStar *star = dynamic_cast<InterrupteurStar *>(element);
        if (inter != 0)
        {
            inter->displayOnMap();
        }
        if (star != 0)
        {
            star->displayOnMap();
        }
    }
}

void Map::onJarreBroken()
{
    if (map == 46)
    {
        if (bounds.getX() == 0 && bounds.getY() == 240 * 2 && nbJarres() == 0)
        {
            reactiveInterruptor(4 * 16, 42 * 16);
        }
        if (bounds.getX() == 320 * 17 && nbJarres() == 0)
        {
            reactiveInterruptor(357 * 16, 27 * 16);
        }
    }
    else if (map == 156 && bounds.getX() == 180 * 16 && bounds.getY() == 30 * 16)
    {
        testFinBoss();
        testAnimRoom();
    }
}

void Map::reactiveInterruptor(int x, int y, bool used)
{
    BoundingBox bb = BoundingBox(x, y, 16, 16);
    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Interrupteur *inter = dynamic_cast<Interrupteur *>(element);
        if (inter != 0)
        {
            inter->setUsed(used);
        }
    }
}

void Map::tigreFire(int x, int y)
{
    // 1 -> selectionner un piege parmis les 3 oppos�s
    int current = (x == 240 * 16 ? 0 : 1) + (y == 23 * 16 ? 0 : 2);
    int randomValue = ((int)rand()) % 3;
    if (current <= randomValue)
        randomValue++;

    // 2 -> fire
    piegeFire(randomValue % 2 == 0 ? 236 * 16 : 263 * 16, randomValue < 2 ? 19 * 16 : 40 * 16);

    // 3 -> si aucun inter up, reactiver un inter oppose
    int nb = 0;
    BoundingBox bb = BoundingBox(240 * 16, 23 * 16, 20 * 16, 18 * 16);
    List list;
    objects->get(&bb, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Interrupteur *inter = dynamic_cast<Interrupteur *>(element);
        if (inter != 0 && !inter->isUsed())
        {
            nb++;
        }
    }
    if (nb == 0)
    {
        reactiveInterruptor(randomValue % 2 == 0 ? 240 * 16 : 259 * 16, randomValue < 2 ? 23 * 16 : 40 * 16);
    }
}

void Map::piegeFire(int x, int y)
{
    BoundingBox bb = BoundingBox(x, y, 16, 16);
    List list;
    objects->get(&bb, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PiegeUltime *ultime = dynamic_cast<PiegeUltime *>(element);
        if (ultime != 0)
        {
            ultime->snipe();
        }
    }
}

void Map::impFire(int x, int y)
{
    BoundingBox bb = BoundingBox(x, y, 16, 16);

    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PiegeFeu *feu = dynamic_cast<PiegeFeu *>(element);
        if (feu != 0)
        {
            if (y == 35 * 16)
            {
                feu->snipe();
            }
            else
            {
                List listEnn;
                ennemis->get(&bounds, &listEnn);
                listEnn.iterateOnFirst();
                if (listEnn.hasNext())
                {
                    Ennemi *ennemi = dynamic_cast<Ennemi *>(listEnn.getNext());
                    if (ennemi != 0)
                    {
                        feu->snipeEnnemi(ennemi->getX() + 10, ennemi->getY() + 22);
                    }
                }
            }
        }
    }
}

void Map::cleanImp()
{
    List list;
    objects->get(&bounds, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Interrupteur *inter = dynamic_cast<Interrupteur *>(element);
        if (inter != 0)
        {
            addEffect(new FumeeBlanche(inter->getX() + 8, inter->getY() + 8, 4));
            inter->killNode();
        }
        PiegeFeu *feu = dynamic_cast<PiegeFeu *>(element);
        if (feu != 0)
        {
            addEffect(new FumeeBlanche(feu->getX() + 8, feu->getY() + 8, 4));
            feu->killNode();
        }
    }
    sol[124][33] = 4002;
    sol[129][33] = 4002;
    sol[135][33] = 4002;
    sol[126][42] = 4002;
    sol[133][42] = 4002;
}

void Map::cleanFlamme()
{
    List list;
    objects->get(&bounds, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PiegeFlamme *flamme = dynamic_cast<PiegeFlamme *>(element);
        PiegeFlammeVerte *flammeVerte = dynamic_cast<PiegeFlammeVerte *>(element);
        if (flamme != 0)
        {
            addEffect(new FumeeBlanche(flamme->getX() + 8, flamme->getY() + 24, 4));
            flamme->killNode();
        }
        if (flammeVerte != 0)
        {
            addEffect(new FumeeBlanche(flammeVerte->getX() + 8, flammeVerte->getY() + 24, 0));
            flammeVerte->killNode();
        }
    }
}

void Map::activateStatue()
{
    List list;
    objects->getAll(&list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        StatueGarde *statue = dynamic_cast<StatueGarde *>(element);
        if (statue != 0)
        {
            statue->killNode();
        }
    }
    addEnnemi(new Ennemi119(69 * 16 - 3 + 8, 38 * 16 + 5));
    addEnnemi(new Ennemi119(69 * 16 - 3 + 8, 50 * 16 + 5));
    addEnnemi(new Ennemi119(45 * 16 - 3 + 8, 93 * 16 + 5 - 8));
    addEnnemi(new Ennemi119(86 * 16 - 3 + 8, 49 * 16 + 5));
    addEnnemi(new Ennemi119(91 * 16 - 3 + 8, 54 * 16 + 5));
    addEnnemi(new Ennemi119(49 * 16 - 3 + 8, 51 * 16 + 5));
    addEnnemi(new Ennemi119(9 * 16 - 3 + 8, 38 * 16 + 5));
    addEnnemi(new Ennemi119(27 * 16 - 3 + 8, 38 * 16 + 5));
    addEnnemi(new Ennemi119(17 * 16 - 3 + 8, 53 * 16 + 5));
    addEnnemi(new Ennemi119(33 * 16 - 3 + 8, 46 * 16 + 5));
    addEnnemi(new Ennemi119(49 * 16 - 3 + 8, 37 * 16 + 5));
    addEnnemi(new Ennemi119(9 * 16 - 3 + 8, 68 * 16 + 5));
    addEnnemi(new Ennemi119(9 * 16 - 3 + 8, 78 * 16 + 5));
    addEnnemi(new Ennemi119(7 * 16 - 3 + 8, 97 * 16 + 5));
    addEnnemi(new Ennemi119(19 * 16 - 3 + 8, 95 * 16 + 5));
    addEnnemi(new Ennemi119(29 * 16 - 3 + 8, 98 * 16 + 5));
    addEnnemi(new Ennemi119(87 * 16 - 3 + 8, 35 * 16 + 5));
    addEnnemi(new Ennemi119(91 * 16 - 3 + 8, 39 * 16 + 5));
    addEnnemi(new Ennemi119(129 * 16 - 3 + 8, 97 * 16 + 5));
    addEnnemi(new Ennemi119(109 * 16 - 3 + 8, 34 * 16 + 5));
    addEnnemi(new Ennemi119(106 * 16 - 3 + 8, 19 * 16 + 5));
    addEnnemi(new Ennemi119(112 * 16 - 3 + 8, 23 * 16 + 5));
    addEnnemi(new Ennemi119(110 * 16 - 3 + 8, 53 * 16 + 5));
    addEnnemi(new Ennemi119(127 * 16 - 3 + 8, 51 * 16 + 5));
    addEnnemi(new Ennemi119(129 * 16 - 3 + 8, 36 * 16 + 5));
    addEnnemi(new Ennemi119(129 * 16 - 3 + 8, 69 * 16 + 5));
    addEnnemi(new Ennemi119(129 * 16 - 3 + 8, 78 * 16 + 5));
    addEnnemi(new Ennemi119(129 * 16 - 3 + 8, 14 * 16 + 5));
}

void Map::ouvrePorte(int x, int y, int type)
{
    switch (map)
    {
    case 1:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        sol[x][y + 1] = 1773;
        sol[x + 1][y + 1] = 1774;
        mur[x * 2 + 1][y * 2 + 1] = NEIGE;
        mur[x * 2 + 2][y * 2 + 1] = NEIGE;
        mur[x * 2 + 1][y * 2 + 2] = NEIGE;
        mur[x * 2 + 2][y * 2 + 2] = NEIGE;
        mur[x * 2 + 1][y * 2 + 3] = NEIGE;
        mur[x * 2 + 2][y * 2 + 3] = NEIGE;
        break;
    case 14:
    case 29:
        setSol(34 * 16, 53 * 16, 2, 1, 2825, PIERRE);
        break;
    case 15:
        sol[121][34] = 2941;
        setSol(122 * 16, 34 * 16, 1, 1, 2942, PIERRE);
        sol[123][34] = 2943;

        sol[121][35] = 2944;
        setSol(122 * 16, 35 * 16, 1, 1, 2945, PIERRE);
        sol[123][35] = 2946;

        sol[121][36] = 2947;
        sol[122][36] = 2948;
        mur[122 * 2][36 * 2] = PIERRE;
        mur[122 * 2 + 1][36 * 2] = PIERRE;
        sol[123][36] = 2949;
        break;
    case 18:
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                sol[66 + i][j] = sol[79][j + 5];
                mur[(66 + i) * 2][j * 2] = mur[79 * 2][(j + 5) * 2];
                mur[(66 + i) * 2 + 1][j * 2] = mur[79 * 2 + 1][(j + 5) * 2];
                mur[(66 + i) * 2][j * 2 + 1] = mur[79 * 2][(j + 5) * 2 + 1];
                mur[(66 + i) * 2 + 1][j * 2 + 1] = mur[79 * 2 + 1][(j + 5) * 2 + 1];
            }
        }
        break;
    case 21:
        setSol(16 * 16, 69 * 16, 2, 1, 1374, PIERRE);
        break;
    case 23:
        sol[x][y] = 181;
        sol[x + 1][y] = 182;
        sol[x][y + 1] = 1206;
        sol[x + 1][y + 1] = 1207;
        mur[x * 2 + 1][y * 2 + 1] = HERBE;
        mur[x * 2 + 2][y * 2 + 1] = HERBE;
        mur[x * 2 + 1][y * 2 + 2] = HERBE;
        mur[x * 2 + 2][y * 2 + 2] = HERBE;
        mur[x * 2 + 1][y * 2 + 3] = HERBE;
        mur[x * 2 + 2][y * 2 + 3] = HERBE;
        break;
    case 26:
        setSol(x * 16, y * 16, 1212, TROU);
        break;
    case 27:
        setSol(x * 16, y * 16, 1298, TROU);
        break;
    case 37:
        setMur(88 * 16, 8 * 16, HERBE);
        setMur(88 * 16, 9 * 16, HERBE);
        setSol(88 * 16, 10 * 16, 1, 1, 2495, HERBE);
        setAir(88 * 16, 10 * 16, 2497);
        setSol(88 * 16, 11 * 16, 1, 1, 2496, HERBE);
        break;
    case 44:
        if (type == 0)
        {
            setSol(34 * 16, 53 * 16, 2, 1, 2825, PIERRE);
        }
        else
        {
            for (int i = 31; i < 39; i++)
            {
                for (int j = 29; j < 39; j++)
                {
                    sol[i][j] = sol[30][j];
                    mur[i * 2][j * 2] = mur[30 * 2][j * 2];
                    mur[i * 2 + 1][j * 2] = mur[30 * 2 + 1][j * 2];
                    mur[i * 2][j * 2 + 1] = mur[30 * 2][j * 2 + 1];
                    mur[i * 2 + 1][j * 2 + 1] = mur[30 * 2 + 1][j * 2 + 1];
                }
            }
            sol[31][33] = sol[40][34];
            sol[35][35] = sol[44][33];
        }
        break;
    case 45:
        sol[99 + 9][4] = sol[99 + 11][4];
        sol[99 + 10][4] = sol[99 + 8][4];
        sol[99 + 8][5] = sol[99 + 6][5];
        sol[99 + 9][5] = sol[99 + 13][5];
        sol[99 + 10][5] = sol[99 + 6][5];
        sol[99 + 11][5] = sol[99 + 13][5];
        for (int i = 0; i < 4; i++)
        {
            setSol((99 + 8 + i) * 16, 6 * 16, 1, 1, -1, MUR);
            air[99 + 8 + i][6] = sol[99 + 6][6];
        }
        for (int i = 0; i < 16; i++)
        {
            mur[(99 + 9) * 2 + 1][i] = MUR;
            mur[(99 + 9) * 2 + 2][i] = MUR;
        }
        break;
    case 46:
        if (type == 0)
        {
            sol[x][y] = 3873;
            sol[x + 1][y] = 3874;
            sol[x][y + 1] = 3875;
            sol[x + 1][y + 1] = 3876;
            sol[x][y + 2] = 3867;
            sol[x + 1][y + 2] = 3868;
            sol[x][y + 3] = 3869;
            sol[x + 1][y + 3] = 3870;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3886;
            sol[x][y + 1] = 3888;
            sol[x][y + 2] = 3890;
            sol[x + 1][y] = 3887;
            sol[x + 1][y + 1] = 3889;
            sol[x + 1][y + 2] = 3891;

            sol[x + 2][y] = 3879;
            sol[x + 2][y + 1] = 3881;
            sol[x + 2][y + 2] = 3883;
            sol[x + 3][y] = 3880;
            sol[x + 3][y + 1] = 3882;
            sol[x + 3][y + 2] = 3884;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 47:
        if (type == 0)
        {
            sol[x][y] = 4080;
            sol[x + 1][y] = 4081;
            sol[x][y + 1] = 4082;
            sol[x + 1][y + 1] = 4083;
            sol[x][y + 2] = 4074;
            sol[x + 1][y + 2] = 4075;
            sol[x][y + 3] = 4076;
            sol[x + 1][y + 3] = 4077;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4093;
            sol[x][y + 1] = 4095;
            sol[x][y + 2] = 4097;
            sol[x + 1][y] = 4094;
            sol[x + 1][y + 1] = 4096;
            sol[x + 1][y + 2] = 4098;

            sol[x + 2][y] = 4086;
            sol[x + 2][y + 1] = 4088;
            sol[x + 2][y + 2] = 4090;
            sol[x + 3][y] = 4087;
            sol[x + 3][y + 1] = 4089;
            sol[x + 3][y + 2] = 4091;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 48:
        if (type == 0)
        {
            sol[x][y] = 4250;
            sol[x + 1][y] = 4251;
            sol[x][y + 1] = 4252;
            sol[x + 1][y + 1] = 4253;
            sol[x][y + 2] = 4244;
            sol[x + 1][y + 2] = 4245;
            sol[x][y + 3] = 4246;
            sol[x + 1][y + 3] = 4247;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4263;
            sol[x][y + 1] = 4265;
            sol[x][y + 2] = 4267;
            sol[x + 1][y] = 4264;
            sol[x + 1][y + 1] = 4266;
            sol[x + 1][y + 2] = 4268;

            sol[x + 2][y] = 4256;
            sol[x + 2][y + 1] = 4258;
            sol[x + 2][y + 2] = 4260;
            sol[x + 3][y] = 4257;
            sol[x + 3][y + 1] = 4259;
            sol[x + 3][y + 2] = 4261;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 4392;
            sol[x + 1][y] = 4393;
            sol[x][y + 1] = 4394;
            sol[x + 1][y + 1] = 4395;
            air[x][y + 1] = 4396;
            air[x + 1][y + 1] = 4397;
            sol[x][y + 2] = 4386;
            sol[x + 1][y + 2] = 4387;
            air[x][y + 2] = 4390;
            air[x + 1][y + 2] = 4391;
            sol[x][y + 3] = 4388;
            sol[x + 1][y + 3] = 4389;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[128][34] = 4406;
            setSol(129 * 16, 34 * 16, 2, 1, 4169, PIERRE);
            sol[131][34] = 4404;
            sol[128][40] = 4406;
            setSol(129 * 16, 40 * 16, 2, 1, 4169, PIERRE);
            sol[131][40] = 4404;
        }
        else if (type == 4)
        {
            setSol(289 * 16, 40 * 16, 1, 1, 3144, PIERRE);
            setSol(9 * 16, 32 * 16, 1, 1, 3143, PIERRE);
        }
        else if (type == 5)
        {
            setSol(3 * 16, 33 * 16, 1, 1, 4326, TROU);
            setSol(4 * 16, 33 * 16, 12, 1, 4327, TROU);
            setSol(16 * 16, 33 * 16, 1, 1, 4328, TROU);
            setSol(3 * 16, 34 * 16, 1, 7, 4329, TROU);
            setSol(4 * 16, 34 * 16, 12, 7, 4338, TROU);
            setSol(16 * 16, 34 * 16, 1, 7, 4330, TROU);
            setSol(3 * 16, 41 * 16, 1, 1, 4331, TROU);
            setSol(4 * 16, 41 * 16, 12, 1, 4332, TROU);
            setSol(16 * 16, 41 * 16, 1, 1, 4333, TROU);
        }
        else if (type == 6)
        {
            setSol(144 * 16, 34 * 16, 1, 1, 4326, TROU);
            setSol(145 * 16, 34 * 16, 10, 1, 4327, TROU);
            setSol(155 * 16, 34 * 16, 1, 1, 4328, TROU);
            setSol(144 * 16, 35 * 16, 1, 5, 4329, TROU);
            setSol(145 * 16, 35 * 16, 10, 5, 4338, TROU);
            setSol(155 * 16, 35 * 16, 1, 5, 4330, TROU);
            setSol(144 * 16, 40 * 16, 1, 1, 4331, TROU);
            setSol(145 * 16, 40 * 16, 10, 1, 4332, TROU);
            setSol(155 * 16, 40 * 16, 1, 1, 4333, TROU);
        }
        else if (type == 7)
        {
            setSol(288 * 16, 35 * 16, 1, 1, 4339, TROU);
            setSol(289 * 16, 35 * 16, 2, 1, 4340, TROU);
            setSol(291 * 16, 35 * 16, 1, 1, 4341, TROU);
            setSol(288 * 16, 36 * 16, 1, 2, 4342, TROU);
            setSol(289 * 16, 36 * 16, 2, 2, 4351, TROU);
            setSol(291 * 16, 36 * 16, 1, 2, 4343, TROU);
            setSol(288 * 16, 38 * 16, 1, 1, 4344, TROU);
            setSol(289 * 16, 38 * 16, 2, 1, 4345, TROU);
            setSol(291 * 16, 38 * 16, 1, 1, 4346, TROU);
        }
        break;
    case 49:
        if (type == 0)
        {
            sol[x][y] = 4491;
            sol[x + 1][y] = 4492;
            sol[x][y + 1] = 4493;
            sol[x + 1][y + 1] = 4494;
            air[x][y + 1] = 4556;
            air[x + 1][y + 1] = 4557;
            sol[x][y + 2] = 4486;
            sol[x + 1][y + 2] = 4487;
            air[x][y + 2] = 4554;
            air[x + 1][y + 2] = 4555;
            sol[x][y + 3] = 4488;
            sol[x + 1][y + 3] = 4489;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4503;
            sol[x][y + 1] = 4505;
            sol[x][y + 2] = 4507;
            sol[x + 1][y] = 4561;
            sol[x + 1][y + 1] = 4506;
            air[x + 1][y + 1] = 4562;
            sol[x + 1][y + 2] = 4563;

            sol[x + 2][y] = 4558;
            sol[x + 2][y + 1] = 4498;
            air[x + 2][y + 1] = 4559;
            sol[x + 2][y + 2] = 4560;
            sol[x + 3][y] = 4497;
            sol[x + 3][y + 1] = 4499;
            sol[x + 3][y + 2] = 4501;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 50:
        if (type == 0)
        {
            sol[x][y] = 4737;
            sol[x + 1][y] = 4738;
            sol[x][y + 1] = 4739;
            sol[x + 1][y + 1] = 4740;
            air[x][y + 1] = 4741;
            air[x + 1][y + 1] = 4742;
            sol[x][y + 2] = 4731;
            sol[x + 1][y + 2] = 4732;
            air[x][y + 2] = 4735;
            air[x + 1][y + 2] = 4736;
            sol[x][y + 3] = 4733;
            sol[x + 1][y + 3] = 4734;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4750;
            sol[x][y + 1] = 4752;
            sol[x][y + 2] = 4754;
            sol[x + 1][y] = 4751;
            sol[x + 1][y + 1] = 4753;
            air[x + 1][y + 1] = 4756;
            sol[x + 1][y + 2] = 4755;

            sol[x + 2][y] = 4743;
            sol[x + 2][y + 1] = 4745;
            air[x + 2][y + 1] = 4749;
            sol[x + 2][y + 2] = 4747;
            sol[x + 3][y] = 4744;
            sol[x + 3][y + 1] = 4746;
            sol[x + 3][y + 2] = 4748;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 4811;
            sol[x + 1][y] = 4812;
            sol[x][y + 1] = 4813;
            sol[x + 1][y + 1] = 4814;
            air[x][y + 1] = 4815;
            air[x + 1][y + 1] = 4816;
            sol[x][y + 2] = 4805;
            sol[x + 1][y + 2] = 4806;
            air[x][y + 2] = 4809;
            air[x + 1][y + 2] = 4810;
            sol[x][y + 3] = 4807;
            sol[x + 1][y + 3] = 4808;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 4824;
            sol[x][y + 1] = 4826;
            sol[x][y + 2] = 4828;
            sol[x + 1][y] = 4825;
            sol[x + 1][y + 1] = 4827;
            air[x + 1][y + 1] = 4830;
            sol[x + 1][y + 2] = 4829;

            sol[x + 2][y] = 4817;
            sol[x + 2][y + 1] = 4819;
            air[x + 2][y + 1] = 4823;
            sol[x + 2][y + 2] = 4821;
            sol[x + 3][y] = 4818;
            sol[x + 3][y + 1] = 4820;
            sol[x + 3][y + 2] = 4822;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(x * 16, y * 16, 1, 1, 4856, TROU);
            setSol((x + 1) * 16, y * 16, 1, 1, 4858, TROU);
            setSol(x * 16, (y + 1) * 16, 1, 1, 4861, TROU);
            setSol((x + 1) * 16, (y + 1) * 16, 1, 1, 4863, TROU);
        }
        break;
    case 51:
        if (type == 0)
        {
            sol[x][y] = 4966;
            sol[x + 1][y] = 4967;
            sol[x][y + 1] = 4968;
            sol[x + 1][y + 1] = 4969;
            air[x][y + 1] = 4970;
            air[x + 1][y + 1] = 4971;
            sol[x][y + 2] = 4960;
            sol[x + 1][y + 2] = 4961;
            air[x][y + 2] = 4964;
            air[x + 1][y + 2] = 4965;
            sol[x][y + 3] = 4962;
            sol[x + 1][y + 3] = 4963;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 4979;
            sol[x][y + 1] = 4981;
            sol[x][y + 2] = 4983;
            sol[x + 1][y] = 4980;
            sol[x + 1][y + 1] = 4982;
            air[x + 1][y + 1] = 4985;
            sol[x + 1][y + 2] = 4984;

            sol[x + 2][y] = 4972;
            sol[x + 2][y + 1] = 4974;
            air[x + 2][y + 1] = 4978;
            sol[x + 2][y + 2] = 4976;
            sol[x + 3][y] = 4973;
            sol[x + 3][y + 1] = 4975;
            sol[x + 3][y + 2] = 4977;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 5040;
            sol[x + 1][y] = 5041;
            sol[x][y + 1] = 5042;
            sol[x + 1][y + 1] = 5043;
            air[x][y + 1] = 5044;
            air[x + 1][y + 1] = 5045;
            sol[x][y + 2] = 5034;
            sol[x + 1][y + 2] = 5035;
            air[x][y + 2] = 5038;
            air[x + 1][y + 2] = 5039;
            sol[x][y + 3] = 5036;
            sol[x + 1][y + 3] = 5037;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 5053;
            sol[x][y + 1] = 5055;
            sol[x][y + 2] = 5057;
            sol[x + 1][y] = 5054;
            sol[x + 1][y + 1] = 5056;
            air[x + 1][y + 1] = 5059;
            sol[x + 1][y + 2] = 5058;

            sol[x + 2][y] = 5046;
            sol[x + 2][y + 1] = 5048;
            air[x + 2][y + 1] = 5052;
            sol[x + 2][y + 2] = 5050;
            sol[x + 3][y] = 5047;
            sol[x + 3][y + 1] = 5049;
            sol[x + 3][y + 2] = 5051;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 52:
        if (type == 0)
        {
            sol[x][y] = 5195;
            sol[x + 1][y] = 5196;
            sol[x][y + 1] = 5197;
            sol[x + 1][y + 1] = 5198;
            air[x][y + 1] = 5199;
            air[x + 1][y + 1] = 5200;
            sol[x][y + 2] = 5189;
            sol[x + 1][y + 2] = 5190;
            air[x][y + 2] = 5193;
            air[x + 1][y + 2] = 5194;
            sol[x][y + 3] = 5191;
            sol[x + 1][y + 3] = 5192;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 5208;
            sol[x][y + 1] = 5210;
            sol[x][y + 2] = 5212;
            sol[x + 1][y] = 5209;
            sol[x + 1][y + 1] = 5211;
            air[x + 1][y + 1] = 5214;
            sol[x + 1][y + 2] = 5213;

            sol[x + 2][y] = 5201;
            sol[x + 2][y + 1] = 5203;
            air[x + 2][y + 1] = 5207;
            sol[x + 2][y + 2] = 5205;
            sol[x + 3][y] = 5202;
            sol[x + 3][y + 1] = 5204;
            sol[x + 3][y + 2] = 5206;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            setSol(130 * 16, 52 * 16, 1, 1, 5291, BOIS);
        }
        else if (type == 3)
        {
            setSol(248 * 16, 32 * 16, 1, 1, 5290, BOIS);
        }
        break;
    case 53:
        if (type == 0)
        {
            sol[x][y] = 5398;
            sol[x + 1][y] = 5399;
            sol[x][y + 1] = 5400;
            sol[x + 1][y + 1] = 5401;
            air[x][y + 1] = 5402;
            air[x + 1][y + 1] = 5403;
            sol[x][y + 2] = 5392;
            sol[x + 1][y + 2] = 5393;
            air[x][y + 2] = 5396;
            air[x + 1][y + 2] = 5397;
            sol[x][y + 3] = 5394;
            sol[x + 1][y + 3] = 5395;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 5411;
            sol[x][y + 1] = 5413;
            sol[x][y + 2] = 5415;
            sol[x + 1][y] = 5412;
            sol[x + 1][y + 1] = 5414;
            air[x + 1][y + 1] = 5417;
            sol[x + 1][y + 2] = 5416;

            sol[x + 2][y] = 5404;
            sol[x + 2][y + 1] = 5406;
            air[x + 2][y + 1] = 5410;
            sol[x + 2][y + 2] = 5408;
            sol[x + 3][y] = 5405;
            sol[x + 3][y + 1] = 5407;
            sol[x + 3][y + 2] = 5409;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(x * 16, y * 16, 1, 1, 5484, TROU);
            setSol((x + 1) * 16, y * 16, 1, 1, 5486, TROU);
            setSol(x * 16, (y + 1) * 16, 1, 1, 5489, TROU);
            setSol((x + 1) * 16, (y + 1) * 16, 1, 1, 5491, TROU);
        }
        break;
    case 54:
        if (type == 0)
        {
            sol[x][y] = 5589;
            sol[x + 1][y] = 5590;
            sol[x][y + 1] = 5591;
            sol[x + 1][y + 1] = 5592;
            air[x][y + 1] = 5593;
            air[x + 1][y + 1] = 5594;
            sol[x][y + 2] = 5583;
            sol[x + 1][y + 2] = 5584;
            air[x][y + 2] = 5587;
            air[x + 1][y + 2] = 5588;
            sol[x][y + 3] = 5585;
            sol[x + 1][y + 3] = 5586;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 5602;
            sol[x][y + 1] = 5604;
            sol[x][y + 2] = 5606;
            sol[x + 1][y] = 5603;
            sol[x + 1][y + 1] = 5605;
            air[x + 1][y + 1] = 5608;
            sol[x + 1][y + 2] = 5607;

            sol[x + 2][y] = 5595;
            sol[x + 2][y + 1] = 5597;
            air[x + 2][y + 1] = 5601;
            sol[x + 2][y + 2] = 5599;
            sol[x + 3][y] = 5596;
            sol[x + 3][y + 1] = 5598;
            sol[x + 3][y + 2] = 5600;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(x * 16, y * 16, 1, 1, 5675, TROU);
            setSol((x + 1) * 16, y * 16, 1, 1, 5677, TROU);
            setSol(x * 16, (y + 1) * 16, 1, 1, 5680, TROU);
            setSol((x + 1) * 16, (y + 1) * 16, 1, 1, 5682, TROU);
        }
        break;
    case 55:
        if (type == 0)
        {
            sol[x][y] = 5780;
            sol[x + 1][y] = 5781;
            sol[x][y + 1] = 5782;
            sol[x + 1][y + 1] = 5783;
            air[x][y + 1] = 5784;
            air[x + 1][y + 1] = 5785;
            sol[x][y + 2] = 5774;
            sol[x + 1][y + 2] = 5775;
            air[x][y + 2] = 5778;
            air[x + 1][y + 2] = 5779;
            sol[x][y + 3] = 5776;
            sol[x + 1][y + 3] = 5777;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 5793;
            sol[x][y + 1] = 5795;
            sol[x][y + 2] = 5797;
            sol[x + 1][y] = 5794;
            sol[x + 1][y + 1] = 5796;
            air[x + 1][y + 1] = 5799;
            sol[x + 1][y + 2] = 5798;

            sol[x + 2][y] = 5786;
            sol[x + 2][y + 1] = 5788;
            air[x + 2][y + 1] = 5792;
            sol[x + 2][y + 2] = 5790;
            sol[x + 3][y] = 5787;
            sol[x + 3][y + 1] = 5789;
            sol[x + 3][y + 2] = 5791;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 5930;
            sol[x + 1][y] = 5931;
            sol[x][y + 1] = 5932;
            sol[x + 1][y + 1] = 5933;
            air[x][y + 1] = 5934;
            air[x + 1][y + 1] = 5935;
            sol[x][y + 2] = 5924;
            sol[x + 1][y + 2] = 5925;
            air[x][y + 2] = 5928;
            air[x + 1][y + 2] = 5929;
            sol[x][y + 3] = 5926;
            sol[x + 1][y + 3] = 5927;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(68 * 16, 43 * 16, 4, 1, 5884, TROU);
            setSol(68 * 16, 44 * 16, 4, 1, 5895, TROU);
            setSol(68 * 16, 45 * 16, 1, 1, 5891, TROU);
            setSol(69 * 16, 45 * 16, 2, 1, 5889, TROU);
            setSol(71 * 16, 45 * 16, 1, 1, 5892, TROU);
        }
        else if (type == 5)
        {
            setSol(68 * 16, 43 * 16, 1, 1, 5885, TROU);
            setSol(68 * 16, 44 * 16, 1, 2, 5887, TROU);
            setSol(69 * 16, 43 * 16, 2, 3, 5701, PIERRE);
            setSol(71 * 16, 43 * 16, 1, 1, 5883, TROU);
            setSol(71 * 16, 44 * 16, 1, 2, 5886, TROU);
        }
        break;
    case 56:
        if (type == 0)
        {
            sol[x][y] = 6000;
            sol[x + 1][y] = 6001;
            sol[x][y + 1] = 6002;
            sol[x + 1][y + 1] = 6003;
            air[x][y + 1] = 6004;
            air[x + 1][y + 1] = 6005;
            sol[x][y + 2] = 5994;
            sol[x + 1][y + 2] = 5995;
            air[x][y + 2] = 5998;
            air[x + 1][y + 2] = 5999;
            sol[x][y + 3] = 5996;
            sol[x + 1][y + 3] = 5997;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 6013;
            sol[x][y + 1] = 6015;
            sol[x][y + 2] = 6017;
            sol[x + 1][y] = 6014;
            sol[x + 1][y + 1] = 6016;
            air[x + 1][y + 1] = 6019;
            sol[x + 1][y + 2] = 6018;

            sol[x + 2][y] = 6006;
            sol[x + 2][y + 1] = 6008;
            air[x + 2][y + 1] = 6012;
            sol[x + 2][y + 2] = 6010;
            sol[x + 3][y] = 6007;
            sol[x + 3][y + 1] = 6009;
            sol[x + 3][y + 2] = 6011;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 57:
        if (type == 0)
        {
            if (y < 105)
            {
                sol[x][y] = 6113;
                sol[x + 1][y] = 6114;
                sol[x][y + 1] = 6115;
                sol[x + 1][y + 1] = 6116;
                air[x][y + 1] = 6117;
                air[x + 1][y + 1] = 6118;
                sol[x][y + 2] = 6107;
                sol[x + 1][y + 2] = 6108;
                air[x][y + 2] = 6111;
                air[x + 1][y + 2] = 6112;
                sol[x][y + 3] = 6109;
                sol[x + 1][y + 3] = 6110;
            }
            else
            {
                sol[x][y] = 6304;
                sol[x + 1][y] = 6305;
                sol[x][y + 1] = 6306;
                sol[x + 1][y + 1] = 6307;
                air[x][y + 1] = 6308;
                air[x + 1][y + 1] = 6309;
                sol[x][y + 2] = 6298;
                sol[x + 1][y + 2] = 6299;
                air[x][y + 2] = 6302;
                air[x + 1][y + 2] = 6303;
                sol[x][y + 3] = 6300;
                sol[x + 1][y + 3] = 6301;
            }
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            if (y < 105)
            {
                sol[x][y] = 6126;
                sol[x][y + 1] = 6128;
                sol[x][y + 2] = 6130;
                sol[x + 1][y] = 6127;
                sol[x + 1][y + 1] = 6129;
                air[x + 1][y + 1] = 6132;
                sol[x + 1][y + 2] = 6131;

                sol[x + 2][y] = 6119;
                sol[x + 2][y + 1] = 6121;
                air[x + 2][y + 1] = 6125;
                sol[x + 2][y + 2] = 6123;
                sol[x + 3][y] = 6120;
                sol[x + 3][y + 1] = 6122;
                sol[x + 3][y + 2] = 6124;
            }
            else
            {
                sol[x][y] = 6317;
                sol[x][y + 1] = 6319;
                sol[x][y + 2] = 6321;
                sol[x + 1][y] = 6318;
                sol[x + 1][y + 1] = 6320;
                air[x + 1][y + 1] = 6323;
                sol[x + 1][y + 2] = 6322;

                sol[x + 2][y] = 6310;
                sol[x + 2][y + 1] = 6312;
                air[x + 2][y + 1] = 6316;
                sol[x + 2][y + 2] = 6314;
                sol[x + 3][y] = 6311;
                sol[x + 3][y + 1] = 6313;
                sol[x + 3][y + 2] = 6315;
            }

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 6374;
            sol[x + 1][y] = 6375;
            sol[x][y + 1] = 6376;
            sol[x + 1][y + 1] = 6377;
            air[x][y + 1] = 6378;
            air[x + 1][y + 1] = 6379;
            sol[x][y + 2] = 6368;
            sol[x + 1][y + 2] = 6369;
            air[x][y + 2] = 6372;
            air[x + 1][y + 2] = 6373;
            sol[x][y + 3] = 6370;
            sol[x + 1][y + 3] = 6371;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(x * 16, y * 16, 1, 1, 6272, PIERRE);
        }
        else if (type == 5)
        {
            setSol(148 * 16, 2 * 16, 4, 2, 5946, PIERRE);
            setSol(146 * 16, 16 * 2, 6105);
            setSol(147 * 16, 16 * 2, 6088);
            setSol(146 * 16, 16 * 3, 6084);
            setSol(147 * 16, 16 * 3, 6106);
            setMur(147 * 16, 16 * 2, MUR, PIERRE, MUR, PIERRE);
            setMur(147 * 16, 16 * 3, MUR, PIERRE, PIERRE, PIERRE);
            setSol(146 * 16, 0, 6091);
            setSol(147 * 16, 0, 6083);
            setSol(146 * 16, 16, 6087);
            setSol(147 * 16, 16, 6092);
            setMur(147 * 16, 16, MUR, MUR, MUR, PIERRE);
            setSol(148 * 16, 0, 6083);
            setSol(148 * 16, 16, 6084);
            setMur(148 * 16, 16, MUR, MUR, PIERRE, PIERRE);
            sol[149][0] = 6107;
            sol[150][0] = 6108;
            air[149][0] = 6111;
            air[150][0] = 6112;
            sol[149][1] = 6109;
            sol[150][1] = 6110;
            setMur(149 * 16, 0, MUR, PIERRE, MUR, PIERRE);
            setMur(150 * 16, 0, PIERRE, MUR, PIERRE, MUR);
            setMur(149 * 16, 16, MUR, PIERRE, PIERRE, PIERRE);
            setMur(150 * 16, 16, PIERRE, MUR, PIERRE, PIERRE);
            setSol(151 * 16, 0, 6083);
            setSol(151 * 16, 16, 6084);
            setMur(151 * 16, 16, MUR, MUR, PIERRE, PIERRE);
            setSol(152 * 16, 0, 6083);
            setSol(153 * 16, 0, 6094);
            setSol(152 * 16, 16, 6093);
            setSol(153 * 16, 16, 6090);
            setMur(152 * 16, 16, MUR, MUR, PIERRE, MUR);
            setSol(152 * 16, 16 * 2, 6089);
            setSol(153 * 16, 16 * 2, 6104);
            setSol(152 * 16, 16 * 3, 6103);
            setSol(153 * 16, 16 * 3, 6084);
            setMur(152 * 16, 16 * 2, PIERRE, MUR, PIERRE, MUR);
            setMur(152 * 16, 16 * 3, PIERRE, MUR, PIERRE, PIERRE);
        }
        break;
    case 58:
        if (type == 0)
        {
            sol[x][y] = 6473;
            sol[x + 1][y] = 6474;
            sol[x][y + 1] = 6475;
            sol[x + 1][y + 1] = 6476;
            air[x][y + 1] = 6477;
            air[x + 1][y + 1] = 6478;
            sol[x][y + 2] = 6467;
            sol[x + 1][y + 2] = 6468;
            air[x][y + 2] = 6471;
            air[x + 1][y + 2] = 6472;
            sol[x][y + 3] = 6469;
            sol[x + 1][y + 3] = 6470;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 6486;
            sol[x][y + 1] = 6488;
            sol[x][y + 2] = 6490;
            sol[x + 1][y] = 6487;
            sol[x + 1][y + 1] = 6489;
            air[x + 1][y + 1] = 6492;
            sol[x + 1][y + 2] = 6491;

            sol[x + 2][y] = 6479;
            sol[x + 2][y + 1] = 6481;
            air[x + 2][y + 1] = 6485;
            sol[x + 2][y + 2] = 6483;
            sol[x + 3][y] = 6480;
            sol[x + 3][y + 1] = 6482;
            sol[x + 3][y + 2] = 6484;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 6546;
            sol[x][y + 1] = 6548;
            sol[x][y + 2] = 6550;
            sol[x + 1][y] = 6547;
            sol[x + 1][y + 1] = 6549;
            air[x + 1][y + 1] = 6552;
            sol[x + 1][y + 2] = 6551;

            sol[x + 2][y] = 6539;
            sol[x + 2][y + 1] = 6541;
            air[x + 2][y + 1] = 6545;
            sol[x + 2][y + 2] = 6543;
            sol[x + 3][y] = 6540;
            sol[x + 3][y + 1] = 6542;
            sol[x + 3][y + 2] = 6544;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 59:
        if (type == 0)
        {
            sol[x][y] = 6630;
            sol[x + 1][y] = 6631;
            sol[x][y + 1] = 6632;
            sol[x + 1][y + 1] = 6633;
            air[x][y + 1] = 6634;
            air[x + 1][y + 1] = 6635;
            sol[x][y + 2] = 6624;
            sol[x + 1][y + 2] = 6625;
            air[x][y + 2] = 6628;
            air[x + 1][y + 2] = 6629;
            sol[x][y + 3] = 6626;
            sol[x + 1][y + 3] = 6627;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 6643;
            sol[x][y + 1] = 6645;
            sol[x][y + 2] = 6647;
            sol[x + 1][y] = 6644;
            sol[x + 1][y + 1] = 6646;
            air[x + 1][y + 1] = 6649;
            sol[x + 1][y + 2] = 6648;

            sol[x + 2][y] = 6636;
            sol[x + 2][y + 1] = 6638;
            air[x + 2][y + 1] = 6642;
            sol[x + 2][y + 2] = 6640;
            sol[x + 3][y] = 6637;
            sol[x + 3][y + 1] = 6639;
            sol[x + 3][y + 2] = 6641;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 60:
        if (type == 0)
        {
            sol[x][y] = 6763;
            sol[x + 1][y] = 6764;
            sol[x][y + 1] = 6765;
            sol[x + 1][y + 1] = 6766;
            air[x][y + 1] = 6767;
            air[x + 1][y + 1] = 6768;
            sol[x][y + 2] = 6757;
            sol[x + 1][y + 2] = 6758;
            air[x][y + 2] = 6761;
            air[x + 1][y + 2] = 6762;
            sol[x][y + 3] = 6759;
            sol[x + 1][y + 3] = 6760;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 6776;
            sol[x][y + 1] = 6778;
            sol[x][y + 2] = 6780;
            sol[x + 1][y] = 6777;
            sol[x + 1][y + 1] = 6779;
            air[x + 1][y + 1] = 6782;
            sol[x + 1][y + 2] = 6781;

            sol[x + 2][y] = 6769;
            sol[x + 2][y + 1] = 6771;
            air[x + 2][y + 1] = 6775;
            sol[x + 2][y + 2] = 6773;
            sol[x + 3][y] = 6770;
            sol[x + 3][y + 1] = 6772;
            sol[x + 3][y + 2] = 6774;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        break;
    case 63:
    case 67:
    case 68:
    case 137: // grottes
        if (type == 0)
        {
            sol[x][y] = 2981;
            sol[x + 1][y] = 2982;
            sol[x][y + 1] = 2983;
            sol[x + 1][y + 1] = 2984;
            sol[x][y + 2] = 2975;
            sol[x + 1][y + 2] = 2976;
            sol[x][y + 3] = 2977;
            sol[x + 1][y + 3] = 2978;
            mur[x * 2 + 1][y * 2 + 1] = TERRE;
            mur[x * 2 + 2][y * 2 + 1] = TERRE;
            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
            mur[x * 2 + 1][y * 2 + 4] = TERRE;
            mur[x * 2 + 2][y * 2 + 4] = TERRE;
            mur[x * 2 + 1][y * 2 + 5] = TERRE;
            mur[x * 2 + 2][y * 2 + 5] = TERRE;
            mur[x * 2 + 1][y * 2 + 6] = TERRE;
            mur[x * 2 + 2][y * 2 + 6] = TERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 2994;
            sol[x][y + 1] = 2996;
            sol[x][y + 2] = 2998;
            sol[x + 1][y] = 2995;
            sol[x + 1][y + 1] = 2997;
            sol[x + 1][y + 2] = 2999;

            sol[x + 2][y] = 2987;
            sol[x + 2][y + 1] = 2989;
            sol[x + 2][y + 2] = 2991;
            sol[x + 3][y] = 2988;
            sol[x + 3][y + 1] = 2990;
            sol[x + 3][y + 2] = 2992;

            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
            mur[x * 2 + 3][y * 2 + 2] = TERRE;
            mur[x * 2 + 4][y * 2 + 2] = TERRE;
            mur[x * 2 + 3][y * 2 + 3] = TERRE;
            mur[x * 2 + 4][y * 2 + 3] = TERRE;
            mur[x * 2 + 5][y * 2 + 2] = TERRE;
            mur[x * 2 + 6][y * 2 + 2] = TERRE;
            mur[x * 2 + 5][y * 2 + 3] = TERRE;
            mur[x * 2 + 6][y * 2 + 3] = TERRE;
        }
        break;
    case 64:
        setSol(9 * 16, 3 * 16, 2, 1, 3144, PIERRE);
        break;
    case 69: // grottes
        if (type == 0)
        {
            sol[x][y] = 2981;
            sol[x + 1][y] = 2982;
            sol[x][y + 1] = 2983;
            sol[x + 1][y + 1] = 2984;
            mur[x * 2 + 1][y * 2 + 1] = TERRE;
            mur[x * 2 + 2][y * 2 + 1] = TERRE;
            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
        }
        break;
    case 70:
        if (type == 0)
        {
            setSol(9 * 16, 3 * 16, 2, 1, 3144, PIERRE);
        }
        else
        {
            setSol(9 * 16, 3 * 16, 2, 1, 3143, PIERRE);
        }
        break;
    case 111:
    case 114:
    case 124:
        setSol(9 * 16, 4 * 16, 2, 1, 3144, PIERRE);
        break;
    case 150:
        if (type == 1)
        {
            sol[x][y] = 3386;
            sol[x][y + 1] = 3388;
            sol[x][y + 2] = 3390;
            sol[x + 1][y] = 3387;
            sol[x + 1][y + 1] = 3389;
            sol[x + 1][y + 2] = 3391;

            sol[x + 2][y] = 3379;
            sol[x + 2][y + 1] = 3381;
            sol[x + 2][y + 2] = 3383;
            sol[x + 3][y] = 3380;
            sol[x + 3][y + 1] = 3382;
            sol[x + 3][y + 2] = 3384;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 2981;
            sol[x + 1][y] = 2982;
            sol[x][y + 1] = 2983;
            sol[x + 1][y + 1] = 2984;
            sol[x][y + 2] = 2975;
            sol[x + 1][y + 2] = 2976;
            sol[x][y + 3] = 2977;
            sol[x + 1][y + 3] = 2978;
            mur[x * 2 + 1][y * 2 + 1] = TERRE;
            mur[x * 2 + 2][y * 2 + 1] = TERRE;
            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
            mur[x * 2 + 1][y * 2 + 4] = TERRE;
            mur[x * 2 + 2][y * 2 + 4] = TERRE;
            mur[x * 2 + 1][y * 2 + 5] = TERRE;
            mur[x * 2 + 2][y * 2 + 5] = TERRE;
            mur[x * 2 + 1][y * 2 + 6] = TERRE;
            mur[x * 2 + 2][y * 2 + 6] = TERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 2994;
            sol[x][y + 1] = 2996;
            sol[x][y + 2] = 2998;
            sol[x + 1][y] = 2995;
            sol[x + 1][y + 1] = 2997;
            sol[x + 1][y + 2] = 2999;

            sol[x + 2][y] = 2987;
            sol[x + 2][y + 1] = 2989;
            sol[x + 2][y + 2] = 2991;
            sol[x + 3][y] = 2988;
            sol[x + 3][y + 1] = 2990;
            sol[x + 3][y + 2] = 2992;

            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
            mur[x * 2 + 3][y * 2 + 2] = TERRE;
            mur[x * 2 + 4][y * 2 + 2] = TERRE;
            mur[x * 2 + 3][y * 2 + 3] = TERRE;
            mur[x * 2 + 4][y * 2 + 3] = TERRE;
            mur[x * 2 + 5][y * 2 + 2] = TERRE;
            mur[x * 2 + 6][y * 2 + 2] = TERRE;
            mur[x * 2 + 5][y * 2 + 3] = TERRE;
            mur[x * 2 + 6][y * 2 + 3] = TERRE;
        }
        break;
    case 154:
        if (type == 0)
        {
            sol[x][y] = 3589;
            sol[x][y + 1] = 3591;
            sol[x][y + 2] = 3593;
            sol[x + 1][y] = 3590;
            sol[x + 1][y + 1] = 3592;
            sol[x + 1][y + 2] = 3594;

            sol[x + 2][y] = 3582;
            sol[x + 2][y + 1] = 3584;
            sol[x + 2][y + 2] = 3586;
            sol[x + 3][y] = 3583;
            sol[x + 3][y + 1] = 3585;
            sol[x + 3][y + 2] = 3587;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 3604;
            sol[x][y + 1] = 3606;
            sol[x][y + 2] = 3608;
            sol[x + 1][y] = 3605;
            sol[x + 1][y + 1] = 3607;
            air[x + 1][y + 1] = 3610;
            sol[x + 1][y + 2] = 3609;

            sol[x + 2][y] = 2987;
            sol[x + 2][y + 1] = 2989;
            air[x + 2][y + 1] = 2993;
            sol[x + 2][y + 2] = 2991;
            sol[x + 3][y] = 2988;
            sol[x + 3][y + 1] = 2990;
            sol[x + 3][y + 2] = 2992;

            mur[x * 2 + 1][y * 2 + 2] = TERRE;
            mur[x * 2 + 2][y * 2 + 2] = TERRE;
            mur[x * 2 + 1][y * 2 + 3] = TERRE;
            mur[x * 2 + 2][y * 2 + 3] = TERRE;
            mur[x * 2 + 3][y * 2 + 2] = TERRE;
            mur[x * 2 + 4][y * 2 + 2] = TERRE;
            mur[x * 2 + 3][y * 2 + 3] = TERRE;
            mur[x * 2 + 4][y * 2 + 3] = TERRE;
            mur[x * 2 + 5][y * 2 + 2] = TERRE;
            mur[x * 2 + 6][y * 2 + 2] = TERRE;
            mur[x * 2 + 5][y * 2 + 3] = TERRE;
            mur[x * 2 + 6][y * 2 + 3] = TERRE;
        }
        else if (type == 2)
        {
            setSol(x * 16, y * 16, 1, 1, 3544, PIERRE);
        }
        break;
    case 155:
        if (type == 0)
        {
            sol[x][y] = 3706;
            sol[x + 1][y] = 3707;
            sol[x][y + 1] = 3708;
            sol[x + 1][y + 1] = 3709;
            air[x][y + 1] = 3710;
            air[x + 1][y + 1] = 3711;
            sol[x][y + 2] = 3700;
            sol[x + 1][y + 2] = 3701;
            air[x][y + 2] = 3704;
            air[x + 1][y + 2] = 3705;
            sol[x][y + 3] = 3702;
            sol[x + 1][y + 3] = 3703;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            setSol(89 * 16, 94 * 16, 1, 1, 3544, PIERRE);
        }
        break;
    case 156:
        if (type == 0)
        {
            sol[x][y] = 6113;
            sol[x + 1][y] = 6114;
            sol[x][y + 1] = 6115;
            sol[x + 1][y + 1] = 6116;
            air[x][y + 1] = 6117;
            air[x + 1][y + 1] = 6118;
            sol[x][y + 2] = 6107;
            sol[x + 1][y + 2] = 6108;
            air[x][y + 2] = 6111;
            air[x + 1][y + 2] = 6112;
            sol[x][y + 3] = 6109;
            sol[x + 1][y + 3] = 6110;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 1)
        {
            sol[x][y] = 6126;
            sol[x][y + 1] = 6128;
            sol[x][y + 2] = 6130;
            sol[x + 1][y] = 6127;
            sol[x + 1][y + 1] = 6129;
            air[x + 1][y + 1] = 6132;
            sol[x + 1][y + 2] = 6131;

            sol[x + 2][y] = 6119;
            sol[x + 2][y + 1] = 6121;
            air[x + 2][y + 1] = 6125;
            sol[x + 2][y + 2] = 6123;
            sol[x + 3][y] = 6120;
            sol[x + 3][y + 1] = 6122;
            sol[x + 3][y + 2] = 6124;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 2)
        {
            sol[x][y] = 6967;
            sol[x + 1][y] = 6968;
            sol[x][y + 1] = 6969;
            sol[x + 1][y + 1] = 6970;
            air[x][y + 1] = 6971;
            air[x + 1][y + 1] = 6972;
            sol[x][y + 2] = 6961;
            sol[x + 1][y + 2] = 6962;
            air[x][y + 2] = 6965;
            air[x + 1][y + 2] = 6966;
            sol[x][y + 3] = 6963;
            sol[x + 1][y + 3] = 6964;
            mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            mur[x * 2 + 2][y * 2 + 1] = PIERRE;
            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 1][y * 2 + 4] = PIERRE;
            mur[x * 2 + 2][y * 2 + 4] = PIERRE;
            mur[x * 2 + 1][y * 2 + 5] = PIERRE;
            mur[x * 2 + 2][y * 2 + 5] = PIERRE;
            mur[x * 2 + 1][y * 2 + 6] = PIERRE;
            mur[x * 2 + 2][y * 2 + 6] = PIERRE;
        }
        else if (type == 3)
        {
            sol[x][y] = 6980;
            sol[x][y + 1] = 6982;
            sol[x][y + 2] = 6984;
            sol[x + 1][y] = 6981;
            sol[x + 1][y + 1] = 6983;
            air[x + 1][y + 1] = 6986;
            sol[x + 1][y + 2] = 6985;

            sol[x + 2][y] = 6973;
            sol[x + 2][y + 1] = 6975;
            air[x + 2][y + 1] = 6979;
            sol[x + 2][y + 2] = 6977;
            sol[x + 3][y] = 6974;
            sol[x + 3][y + 1] = 6976;
            sol[x + 3][y + 2] = 6978;

            mur[x * 2 + 1][y * 2 + 2] = PIERRE;
            mur[x * 2 + 2][y * 2 + 2] = PIERRE;
            mur[x * 2 + 1][y * 2 + 3] = PIERRE;
            mur[x * 2 + 2][y * 2 + 3] = PIERRE;
            mur[x * 2 + 3][y * 2 + 2] = PIERRE;
            mur[x * 2 + 4][y * 2 + 2] = PIERRE;
            mur[x * 2 + 3][y * 2 + 3] = PIERRE;
            mur[x * 2 + 4][y * 2 + 3] = PIERRE;
            mur[x * 2 + 5][y * 2 + 2] = PIERRE;
            mur[x * 2 + 6][y * 2 + 2] = PIERRE;
            mur[x * 2 + 5][y * 2 + 3] = PIERRE;
            mur[x * 2 + 6][y * 2 + 3] = PIERRE;
        }
        else if (type == 4)
        {
            setSol(x * 16, y * 16, 1, 1, 6923, TROU);
            setSol((x + 1) * 16, y * 16, 1, 1, 6925, TROU);
            setSol(x * 16, (y + 1) * 16, 1, 1, 6928, TROU);
            setSol((x + 1) * 16, (y + 1) * 16, 1, 1, 6930, TROU);
        }
        break;
    }
}

void Map::fermePorte(int x, int y, int type)
{
    switch (map)
    {
    case 46:
        if (type == 0)
        {
            sol[x][y] = 3921;
            sol[x + 1][y] = 3922;
            sol[x][y + 1] = 3923;
            sol[x + 1][y + 1] = 3924;
            sol[x][y + 2] = 3917;
            sol[x + 1][y + 2] = 3918;
            sol[x][y + 3] = 3919;
            sol[x + 1][y + 3] = 3920;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 47:
        if (type == 0)
        {
            sol[x][y] = 4128;
            sol[x + 1][y] = 4129;
            sol[x][y + 1] = 4130;
            sol[x + 1][y + 1] = 4131;
            sol[x][y + 2] = 4124;
            sol[x + 1][y + 2] = 4125;
            sol[x][y + 3] = 4126;
            sol[x + 1][y + 3] = 4127;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x][y] = 4138;
            sol[x + 1][y] = 4139;
            sol[x][y + 1] = 4140;
            sol[x + 1][y + 1] = 4141;
            sol[x][y + 2] = 4142;
            sol[x + 1][y + 2] = 4143;
            sol[x + 2][y] = 4132;
            sol[x + 3][y] = 4133;
            sol[x + 2][y + 1] = 4134;
            sol[x + 3][y + 1] = 4135;
            sol[x + 2][y + 2] = 4136;
            sol[x + 3][y + 2] = 4137;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 48:
        if (type == 0)
        {
            sol[x][y] = 4298;
            sol[x + 1][y] = 4299;
            sol[x][y + 1] = 4300;
            sol[x + 1][y + 1] = 4301;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 49:
        if (type == 0)
        {
            sol[x][y] = 4534;
            sol[x + 1][y] = 4535;
            sol[x][y + 1] = 4536;
            sol[x + 1][y + 1] = 4537;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 50:
        if (type == 0)
        {
            sol[x][y] = 4781;
            sol[x + 1][y] = 4782;
            sol[x][y + 1] = 4783;
            sol[x + 1][y + 1] = 4784;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 51:
        if (type == 0)
        {
            sol[x][y] = 5010;
            sol[x + 1][y] = 5011;
            sol[x][y + 1] = 5012;
            sol[x + 1][y + 1] = 5013;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x][y] = 5020;
            sol[x + 1][y] = 5021;
            sol[x][y + 1] = 5022;
            sol[x + 1][y + 1] = 5023;
            sol[x][y + 2] = 5024;
            sol[x + 1][y + 2] = 5025;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 52:
        if (type == 0)
        {
            sol[x][y] = 5239;
            sol[x + 1][y] = 5240;
            sol[x][y + 1] = 5241;
            sol[x + 1][y + 1] = 5242;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 53:
        if (type == 0)
        {
            sol[x][y] = 5442;
            sol[x + 1][y] = 5443;
            sol[x][y + 1] = 5444;
            sol[x + 1][y + 1] = 5445;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x][y] = 5452;
            sol[x + 1][y] = 5453;
            sol[x][y + 1] = 5454;
            sol[x + 1][y + 1] = 5455;
            sol[x][y + 2] = 5456;
            sol[x + 1][y + 2] = 5457;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 54:
        if (type == 0)
        {
            sol[x][y] = 5633;
            sol[x + 1][y] = 5634;
            sol[x][y + 1] = 5635;
            sol[x + 1][y + 1] = 5636;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x + 2][y] = 5637;
            sol[x + 3][y] = 5638;
            sol[x + 2][y + 1] = 5639;
            sol[x + 3][y + 1] = 5640;
            sol[x + 2][y + 2] = 5641;
            sol[x + 3][y + 2] = 5642;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 55:
        if (type == 0)
        {
            sol[x][y] = 5824;
            sol[x + 1][y] = 5825;
            sol[x][y + 1] = 5826;
            sol[x + 1][y + 1] = 5827;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x + 2][y] = 5828;
            sol[x + 3][y] = 5829;
            sol[x + 2][y + 1] = 5830;
            sol[x + 3][y + 1] = 5831;
            sol[x + 2][y + 2] = 5832;
            sol[x + 3][y + 2] = 5833;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 56:
        if (type == 0)
        {
            sol[x][y] = 6044;
            sol[x + 1][y] = 6045;
            sol[x][y + 1] = 6046;
            sol[x + 1][y + 1] = 6047;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x][y] = 6054;
            sol[x + 1][y] = 6055;
            sol[x][y + 1] = 6056;
            sol[x + 1][y + 1] = 6057;
            sol[x][y + 2] = 6058;
            sol[x + 1][y + 2] = 6059;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    case 57:
        if (y < 105)
        {
            sol[x][y] = 6157;
            sol[x + 1][y] = 6158;
            sol[x][y + 1] = 6159;
            sol[x + 1][y + 1] = 6160;
        }
        else
        {
            sol[x][y] = 6336;
            sol[x + 1][y] = 6337;
            sol[x][y + 1] = 6338;
            sol[x + 1][y + 1] = 6339;
        }
        mur[x * 2 + 1][y * 2 + 1] = MUR;
        mur[x * 2 + 2][y * 2 + 1] = MUR;
        mur[x * 2 + 1][y * 2 + 2] = MUR;
        mur[x * 2 + 2][y * 2 + 2] = MUR;
        mur[x * 2 + 1][y * 2 + 3] = MUR;
        mur[x * 2 + 2][y * 2 + 3] = MUR;
        mur[x * 2 + 1][y * 2 + 4] = MUR;
        mur[x * 2 + 2][y * 2 + 4] = MUR;
        mur[x * 2 + 1][y * 2 + 5] = MUR;
        mur[x * 2 + 2][y * 2 + 5] = MUR;
        mur[x * 2 + 1][y * 2 + 6] = MUR;
        mur[x * 2 + 2][y * 2 + 6] = MUR;
        break;
    case 58:
        if (type == 0)
        {
            sol[x][y] = 6517;
            sol[x + 1][y] = 6518;
            sol[x][y + 1] = 6519;
            sol[x + 1][y + 1] = 6520;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 59:
        if (type == 0)
        {
            sol[x][y] = 6662;
            sol[x + 1][y] = 6663;
            sol[x][y + 1] = 6664;
            sol[x + 1][y + 1] = 6665;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 60:
        if (type == 0)
        {
            sol[x][y] = 6807;
            sol[x + 1][y] = 6808;
            sol[x][y + 1] = 6809;
            sol[x + 1][y + 1] = 6810;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 137:
        if (type == 0)
        {
            sol[x][y] = 3025;
            sol[x + 1][y] = 3026;
            sol[x][y + 1] = 3027;
            sol[x + 1][y + 1] = 3028;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        break;
    case 154:
        if (type == 0)
        {
            sol[x + 2][y] = 3626;
            sol[x + 3][y] = 3627;
            sol[x + 2][y + 1] = 3628;
            sol[x + 3][y + 1] = 3629;
            sol[x + 2][y + 2] = 3630;
            sol[x + 3][y + 2] = 3631;
            mur[(x + 2) * 2][(y + 1) * 2] = MUR;
            mur[(x + 2) * 2 + 1][(y + 1) * 2] = MUR;
            mur[(x + 2) * 2 + 2][(y + 1) * 2] = MUR;
            mur[(x + 2) * 2][(y + 1) * 2 + 1] = MUR;
            mur[(x + 2) * 2 + 1][(y + 1) * 2 + 1] = MUR;
            mur[(x + 2) * 2 + 2][(y + 1) * 2 + 1] = MUR;
        }
        else if (type == 1)
        {
            setSol(x * 16, y * 16, 1, 1, 3620, MUR);
        }
        break;
    case 156:
        if (type == 0)
        {
            sol[x][y] = 6157;
            sol[x + 1][y] = 6158;
            sol[x][y + 1] = 6159;
            sol[x + 1][y + 1] = 6160;
            sol[x][y + 2] = 6153;
            sol[x + 1][y + 2] = 6154;
            sol[x][y + 3] = 6155;
            sol[x + 1][y + 3] = 6156;
            mur[x * 2 + 1][y * 2 + 1] = MUR;
            mur[x * 2 + 2][y * 2 + 1] = MUR;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 1][y * 2 + 4] = MUR;
            mur[x * 2 + 2][y * 2 + 4] = MUR;
            mur[x * 2 + 1][y * 2 + 5] = MUR;
            mur[x * 2 + 2][y * 2 + 5] = MUR;
            mur[x * 2 + 1][y * 2 + 6] = MUR;
            mur[x * 2 + 2][y * 2 + 6] = MUR;
        }
        else
        {
            sol[x][y] = 6167;
            sol[x + 1][y] = 6168;
            sol[x][y + 1] = 6169;
            sol[x + 1][y + 1] = 6170;
            sol[x][y + 2] = 6171;
            sol[x + 1][y + 2] = 6172;
            sol[x + 2][y] = 6161;
            sol[x + 3][y] = 6162;
            sol[x + 2][y + 1] = 6163;
            sol[x + 3][y + 1] = 6164;
            sol[x + 2][y + 2] = 6165;
            sol[x + 3][y + 2] = 6166;
            mur[x * 2 + 1][y * 2 + 2] = MUR;
            mur[x * 2 + 2][y * 2 + 2] = MUR;
            mur[x * 2 + 1][y * 2 + 3] = MUR;
            mur[x * 2 + 2][y * 2 + 3] = MUR;
            mur[x * 2 + 3][y * 2 + 2] = MUR;
            mur[x * 2 + 4][y * 2 + 2] = MUR;
            mur[x * 2 + 3][y * 2 + 3] = MUR;
            mur[x * 2 + 4][y * 2 + 3] = MUR;
            mur[x * 2 + 5][y * 2 + 2] = MUR;
            mur[x * 2 + 6][y * 2 + 2] = MUR;
            mur[x * 2 + 5][y * 2 + 3] = MUR;
            mur[x * 2 + 6][y * 2 + 3] = MUR;
        }
        break;
    }
}

void Map::removeZelda()
{
    if (map != 57)
        return;

    BoundingBox b(0, 0, w, h);

    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Pnj *pnj = dynamic_cast<Pnj *>(list.getNext());
        if (pnj != 0 && pnj->getType() == 15)
        {
            pnj->killNode();
        }
    }
}

void Map::removeStele()
{
    if ((map != 64 && map < 151) || map > 153)
        return;

    BoundingBox b(0, 0, w, h);

    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Stele *stele = dynamic_cast<Stele *>(list.getNext());
        if (stele != 0)
        {
            stele->explose();
        }
    }
}

void Map::songPlayed(int id)
{
    if (isIndoor() || (map == 156 && bounds.getX() == 320 * 9 && bounds.getY() == 240 * 2))
    {
        AudioManager::getInstance()->replayMusic();
        MainController::getInstance()->getGameController()->displayText(249);
        return;
    }
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (id)
    {
    case 0:
        MainController::getInstance()->getGameController()->displayMap(map, true);
        AudioManager::getInstance()->playSound(TS_MENU1);
        break;
    case 1:
        if (getEpoque() == EP_FUTUR && scene->getAvancement() < AV_RETOUR_PRESENT)
        {
            MainController::getInstance()->getGameController()->displayGeneric(0);
            break;
        }
        else if (getEpoque() == EP_PRESENT && scene->getAvancement() < AV_ARRIVE_PASSE)
        {
            MainController::getInstance()->getGameController()->displayGeneric(1);
            break;
        }
    case 2:
        MainController::getInstance()->getGameController()->getTransitionTimesController()->setSens(id - 1);
        MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_TIME);
        break;
    default:
        break;
    }
}

void Map::increaseCasino()
{
    casino += 10;
    if (casino > 150)
    {
        casino = 150;
    }
}

int Map::getCasino()
{
    return casino;
}

bool Map::isJeuCasinoStarted()
{
    return jeuCasinoStarted != 0;
}

void Map::startJeuCasino()
{
    if (map != 58)
        return;
    if (bounds.getX() == 320 && bounds.getY() == 240 * 4)
    {
        jeuCasinoStarted = 1;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
                dices->activer(true);
        }
    }
    else if (bounds.getX() == 320 * 2 && bounds.getY() == 0)
    {
        if (jeuCasinoStarted == 2)
        { // retry 421 en gardant ceux ok
            bool value4 = false;
            bool value2 = false;
            bool value1 = false;
            List list;
            objects->get(&bounds, &list);
            list.iterateOnFirst();
            while (list.hasNext())
            {
                Dices *dices = dynamic_cast<Dices *>(list.getNext());
                if (dices != 0 && !dices->isActif())
                {
                    if (dices->getValue() == 3)
                    {
                        if (value4)
                            dices->activer(true);
                        else
                            value4 = true;
                    }
                    else if (dices->getValue() == 1)
                    {
                        if (value2)
                            dices->activer(true);
                        else
                            value2 = true;
                    }
                    else if (dices->getValue() == 0)
                    {
                        if (value1)
                            dices->activer(true);
                        else
                            value1 = true;
                    }
                    else
                    {
                        dices->activer(true);
                    }
                }
            }
        }
        else
        {
            jeuCasinoStarted = 2;
            List list;
            objects->get(&bounds, &list);
            list.iterateOnFirst();
            while (list.hasNext())
            {
                Dices *dices = dynamic_cast<Dices *>(list.getNext());
                if (dices != 0)
                    dices->activer(true);
            }
        }
    }
    else if (bounds.getX() == 320 && bounds.getY() == 0)
    {
        jeuCasinoStarted = 3;
        tempsCasinoEcoule = 0;
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->displayTime();
    }
    else if (bounds.getX() == 0 && bounds.getY() == 240 * 5)
    {
        BoundingBox b(3 * 16, 78 * 16, 80, 16);
        List list;
        objects->get(&b, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
            {
                dices->activer(false);
            }
        }
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAnimationInGame()->startAnim(15);
    }
    else if (bounds.getX() == 320 * 5 && bounds.getY() == 240 * 4)
    {
        jeuCasinoStarted = 5;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
            {
                dices->activer(false);
            }
        }
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAnimationInGame()->startAnim(16);
    }
    else if (bounds.getX() == 320 * 6 && bounds.getY() == 240 * 5)
    {
        jeuCasinoStarted = 6;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
                dices->activer(true);
        }
    }
    else if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
    {
        BoundingBox b(83 * 16, 18 * 16, 16, 16);
        List list;
        objects->get(&b, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
            {
                dices->activer(false);
            }
        }
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAnimationInGame()->startAnim(17);
    }
}

bool Map::isJeuCasinoGagne()
{
    if (map != 58)
        return false;
    if (jeuCasinoStarted == 1)
    { // jeu 1 : 4 signes differents
        bool signe[4];
        for (int i = 0; i < 4; i++)
            signe[i] = false;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
            {
                if (dices->isActif())
                    return false;
                signe[dices->getValue()] = true;
            }
        }
        for (int i = 0; i < 4; i++)
            if (!signe[i])
                return false;
        return true;
    }
    if (jeuCasinoStarted == 2)
    { // jeu 2 : 421
        bool value4 = false;
        bool value2 = false;
        bool value1 = false;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0)
            {
                if (dices->isActif())
                    return false;
                if (dices->getValue() == 3)
                    value4 = true;
                else if (dices->getValue() == 1)
                    value2 = true;
                else if (dices->getValue() == 0)
                    value1 = true;
                else
                    return false;
            }
        }
        return value4 && value2 && value1;
    }
    if (jeuCasinoStarted == 4)
    { // jeu 4 : risk
        int totalBanque = getTotalDices(3 * 16, 78 * 16, 80, 16);
        int totalJoueur = getTotalDices(0, 75 * 16, 320, 240) - totalBanque;
        return totalJoueur > totalBanque;
    }
    if (jeuCasinoStarted == 5)
    { // jeu 5 : 1 or 6
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0 && !dices->isActif())
            {
                if ((choixCasino && dices->getValue() == 0) || (!choixCasino && dices->getValue() == 5))
                    return true;
            }
        }
    }
    if (jeuCasinoStarted == 6)
    { // jeu caisses
        return !nbCaissesMovable() && isCaisse(135 * 16, 83 * 16) && isCaisse(135 * 16, 84 * 16) && isCaisse(135 * 16, 85 * 16);
    }
    return false;
}

void Map::jeuCasinoPerdu()
{
    if (map != 58)
        return;
    if (jeuCasinoStarted == 5)
    {
        int min = 5;
        int max = 0;
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0 && !dices->isActif())
            {
                int tmp = dices->getValue();
                if (min > tmp)
                    min = tmp;
                if (max < tmp)
                    max = tmp;
            }
        }
        int price = 0;
        if (choixCasino)
        {
            price = 10 * min;
        }
        else
        {
            price = 10 * (5 - max);
        }
        Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
        link->getStatus()->updateGanonOr(-price);
    }
}

bool Map::isJeuCasinoFini()
{
    if (map != 58 || jeuCasinoStarted == 0)
        return false;
    if (jeuCasinoStarted == 1 || jeuCasinoStarted == 2 || jeuCasinoStarted == 4 || jeuCasinoStarted == 7)
    {
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0 && dices->isActif())
                return false;
        }
    }
    else if (jeuCasinoStarted == 6)
    {
        List list;
        objects->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Dices *dices = dynamic_cast<Dices *>(list.getNext());
            if (dices != 0 && dices->isActif())
                return false;
        }
        return !nbCaissesMovable();
    }
    return true;
}

void Map::recompenseJeuCasino()
{
    if (map != 58)
        return;
    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    if (jeuCasinoStarted == 1)
    {
        link->trouveObjet(TI_CLE, 4);
    }
    else if (jeuCasinoStarted == 2)
    {
        link->trouveObjet(TI_CLE, 5);
    }
    else if (jeuCasinoStarted == 3)
    {
        jeuCasinoStarted = 0;
        link->trouveObjet(TI_CLE, 8);
    }
    else if (jeuCasinoStarted == 4)
    {
        link->trouveObjet(TI_CARTE_DONJON);
    }
    else if (jeuCasinoStarted == 5)
    {
        link->trouveObjet(TI_CLE, 7);
    }
    else if (jeuCasinoStarted == 6)
    {
        link->trouveObjet(TI_BOUSSOLE);
    }
    else if (jeuCasinoStarted == 7)
    {
        link->trouveObjet(TI_CLE, 6);
    }
}

int Map::getTempsCasinoRestant()
{
    return 12 - ((int)tempsCasinoEcoule);
}

void Map::activateDices(int i, int j, bool gameReady)
{
    if (map != 58)
        return;

    BoundingBox b(i, j, 16, 16);

    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Dices *dices = dynamic_cast<Dices *>(list.getNext());
        if (dices != 0)
        {
            dices->stopper();
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
        }
    }
    if (gameReady)
    {
        if (bounds.getX() == 0 && bounds.getY() == 240 * 5)
        {
            int total = getTotalDices(3 * 16, 78 * 16, 80, 16);
            if (total < 12)
            {
                BoundingBox b(12 * 16, 78 * 16, 64, 16);
                List list;
                objects->get(&b, &list);
                list.iterateOnFirst();
                while (list.hasNext())
                {
                    Dices *dices = dynamic_cast<Dices *>(list.getNext());
                    if (dices != 0)
                        dices->activer(true);
                }
            }
            jeuCasinoStarted = 4;
        }
        else if (bounds.getX() == 320 * 4 && bounds.getY() == 240)
        {
            BoundingBox b(87 * 16, 18 * 16, 160, 16);
            List list;
            objects->get(&b, &list);
            list.iterateOnFirst();
            while (list.hasNext())
            {
                Dices *dices = dynamic_cast<Dices *>(list.getNext());
                if (dices != 0)
                    dices->activer(true);
            }
            jeuCasinoStarted = 7;
        }
    }
}

int Map::getPriceCasino()
{
    int mult = getTotalDices(83 * 16, 18 * 16, 16, 16);
    int sum = getTotalDices(80 * 16, 15 * 16, 320, 240) - mult;
    return mult * sum;
}

int Map::getTotalDices(int i, int j, int w, int h)
{
    int total = 0;
    BoundingBox b(i, j, w, h);
    List list;
    objects->get(&b, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Dices *dices = dynamic_cast<Dices *>(list.getNext());
        if (dices != 0 && !dices->isActif())
            total += (1 + dices->getValue());
    }
    return total;
}

void Map::choixCasinoUn(bool choix)
{
    choixCasino = choix;
}

bool Map::bossCasinoVaincu()
{
    if (map != 58)
        return false;
    if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 2)
    {
        List list;
        ennemis->get(&bounds, &list);
        list.iterateOnFirst();
        while (list.hasNext())
        {
            Ennemi *ennemi = dynamic_cast<Ennemi *>(list.getNext());
            if (ennemi != 0)
                return ennemi->getLife() <= 0;
        }
    }
    return false;
}

void Map::startDestFinal()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    scene->setCoffre(15, 20, 1);
    for (int i = 0; i < 12; i++)
        scene->setCoffre(15, 21 + i, 0);
    scene->setCoffre(15, 33, 0);
}

void Map::increaseDestFinal()
{
    if (map == 60)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        int value = scene->getCoffre(15, 20) * 2;
        if (value > 40)
            value = 40;
        scene->setCoffre(15, 20, value);
    }
}

int Map::getDestFinal()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    return scene->getCoffre(15, 20);
}

void Map::setDestFinalTypeEnn(int type)
{
    if (map == 60 && type >= 129 && type <= 140)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        scene->setCoffre(15, 21 + type - 129, 1);
        if (scene->getCoffre(15, 33) < 99)
            scene->setCoffre(15, 33, scene->getCoffre(15, 33) + 1);
    }
}

int Map::getDestFinalTypeEnn()
{
    int total = 0;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    for (int i = 0; i < 12; i++)
        if (scene->getCoffre(15, 21 + i))
            total++;
    return total;
}

int Map::getDestFinalNbEnn()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    return scene->getCoffre(15, 33);
}

void Map::startFinalBattle()
{
    List list;
    objects->get(&bounds, &list);
    list.iterateOnFirst();
    while (list.hasNext())
    {
        Pnj *pnj = dynamic_cast<Pnj *>(list.getNext());
        if (pnj != 0)
            pnj->killNode();
    }
    AudioManager::getInstance()->playMusic(106);
    addEnnemi(new Ennemi141(68 * 16 + 4, 76 * 16));
}

void Map::testFinBoss()
{
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        PouleBig *big = dynamic_cast<PouleBig *>(element);
        if (big != 0)
        {
            return;
        }
    }

    list.iterateOnFirst();
    while (list.hasNext())
    {
        Listable *element = list.getNext();
        Poule *poule = dynamic_cast<Poule *>(element);
        if (poule != 0)
        {
            poule->killNode();
            addEffect(new FumeeBlanche(poule->getX() + 8, poule->getY() + 8, 0));
        }
    }
}

int Map::getEtage()
{
    switch (map)
    {
    case 46:
        return (bounds.getX() / (80 * 16) - 1);
    case 47:
        return -(bounds.getX() / (120 * 16));
    case 48:
        return -(bounds.getX() / (140 * 16));
    case 49:
    case 54:
        return -((bounds.getX() + (100 * 16)) / (120 * 16));
    case 50:
    case 51:
    case 52:
        if (bounds.getX() >= 320 * 9)
            return -1;
        if (bounds.getX() >= 320 * 4)
            return 0;
        if (bounds.getX() >= 320)
            return 1;
        return 2;
    case 53:
        return ((bounds.getY() / (240 * 4)) * (-2)) + (bounds.getX() / (320 * 4));
    case 55:
        return (bounds.getY() / (75 * 16)) - 2;
    case 56:
        return (bounds.getX() / (140 * 16));
    case 57:
        if (bounds.getY() >= 240 * 14)
            return -2;
        if (bounds.getY() >= 240 * 7)
            return -1;
        if (bounds.getX() >= 320 * 7)
            return 1;
        return 0;
    case 58:
        return 0;
    case 59:
        return (bounds.getX() / (80 * 16) - 1);
    case 60:
        return (bounds.getY() / (75 * 16)) - 1;
    case 63:
        if (bounds.getX() >= 320 * 3)
            return 0;
        return -1;
    case 67:
        if (bounds.getX() >= 320 * 2)
            return 0;
        return -1;
    case 78:
        if (bounds.getX() >= 320 * 3)
            return 0;
        return -1;
    case 137:
        if (bounds.getY() == 240 * 4)
            return 0;
        return -1;
    case 140:
        if (bounds.getX() == 0)
            return 0;
        return -1;
    case 150:
        if (bounds.getX() >= 320 * 9)
            return -2;
        if (bounds.getX() >= 320 * 6)
            return -1;
        if (bounds.getX() >= 320 * 3)
            return 0;
        return 1;
    case 154:
        if (bounds.getX() == 0)
            return 0;
        if (bounds.getX() >= 320 && bounds.getY() == 0)
            return -1;
        return -2;
    case 156:
        return 2 - (bounds.getY() / (75 * 16));
    default:
        return 0;
    }
}

Epoque Map::getEpoque()
{
    // overworld
    if (map < 16)
        return EP_PASSE;
    if (map < 31)
        return EP_PRESENT;
    if (map < 46)
        return EP_FUTUR;
    // donjons
    if (map < 49)
        return EP_PRESENT;
    if (map < 51)
        return EP_FUTUR;
    if (map < 52)
        return EP_PRESENT;
    if (map < 57)
        return EP_PASSE;
    if (map < 58)
        return EP_PRESENT;
    if (map < 60)
        return EP_FUTUR;
    if (map == 60)
        return EP_RIEN;
    // grottes
    if (map < 70)
        return EP_PRESENT;
    if (map < 74)
        return EP_FUTUR;
    if (map < 79)
        return EP_PASSE;
    // maisons
    if (map < 112)
        return EP_PRESENT;
    if (map < 124)
        return EP_FUTUR;
    if (map < 150)
        return EP_PASSE;
    // autres
    if (map < 152)
        return EP_PRESENT;
    if (map < 153)
        return EP_FUTUR;
    if (map < 155)
        return EP_PASSE;
    if (map < 156)
        return EP_FUTUR;
    // donjon de trop
    if (bounds.getX() < 320 * 5)
        return EP_PASSE;
    if (bounds.getX() < 320 * 10)
        return EP_PRESENT;
    return EP_FUTUR;
}

bool Map::isIndoor()
{
    if (map < 46)
    {
        return false;
    }
    if (map == 156)
    {
        return bounds.getY() != 240 * 2 && bounds.getY() != 240 * 8 && bounds.getY() != 240 * 14;
    }
    return true;
}
