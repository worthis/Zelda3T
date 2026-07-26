#include "Pnj.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

#include "../../algo/AStar.h"

#include "../effects/Plouf.h"

#include "../helper/ProjectileHelper.h"

Pnj::Pnj(int i, int j, int tp, int txt, Direction dir) : type(tp), texte(txt), anim(0), animMax(0), vanim(480), w(0), h(0),
                                                         displayW(0), displayH(0), idle(true), direction(dir), stop(false)
{
    x = i;
    y = j;

    image = 0;

    ostringstream os;
    os << type;
    image = ResourceManager::getInstance()->loadImage("data/images/npcs/personnage" + os.str() + ".png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    w = width;
    h = height;

    displayW = w;
    displayH = h;

    init();

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    x0 = x;
    y0 = y;
    dir0 = direction;

    cooldown = 0;

    chrono.reset();
}

Pnj::~Pnj()
{
    ResourceManager::getInstance()->free(image);
}

bool Pnj::isResetable()
{
    return type == 6 && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getId() == 58;
}

void Pnj::reset()
{
    x = x0;
    y = y0;
    direction = dir0;
}

void Pnj::init()
{
    switch (type)
    {
    case 1:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 2:
        height = 16 * 3 - 6;
        h = 24;
        displayH = height - 25;
        animMax = 1;
        break;
    case 3:
        idle = false;
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 4:
        idle = false;
        height = 17;
        h = height;
        displayH = h;
        animMax = 3;
        vanim = 240;
        break;
    case 5:
        idle = false;
        width = 13;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 6:
        idle = false;
        width = 15;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 7:
        height = 16 * 3 - 5;
        h = 25;
        displayH = height - 25;
        animMax = 1;
        break;
    case 8:
        height = 56;
        h = 23;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 9:
        height = 27;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 10:
        height = 26;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 11:
        idle = false;
        height = 24;
        animMax = 1;
        vanim = 240;
        break;
    case 12:
        height = 16 * 3 - 5;
        h = 25;
        displayH = height - 25;
        animMax = 1;
        break;
    case 13:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 14:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 15:
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 16:
        height = 48;
        h = height;
        displayH = h;
        width = 32;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 17:
        height = 25;
        h = height;
        displayH = h;
        width = 18;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 18:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 19:
        height = 16 * 3 - 5;
        h = 25;
        displayH = h;
        animMax = 1;
        break;
    case 20:
        height = 16 * 3 - 4;
        h = 26;
        displayH = height - 25;
        animMax = 3;
        break;
    case 21:
        height = 25;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 22:
        height = 29;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 23:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 24:
        height = 16 * 3 - 9;
        h = 21;
        displayH = height - 25;
        animMax = 1;
        break;
    case 25:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 26:
        height = 30;
        h = height;
        displayH = h;
        width = 39;
        w = width;
        displayW = w;
        animMax = 3;
        vanim = 240;
        break;
    case 27:
        height = 16 * 3 - 11;
        h = 17;
        displayH = height - 25;
        animMax = 1;
        break;
    case 28:
        height = 35;
        h = height;
        displayH = h;
        width = 25;
        w = width;
        displayW = w;
        animMax = 4;
        vanim = 240;
        break;
    case 29:
        height = 27;
        h = height;
        displayH = h;
        width = 21;
        w = width;
        displayW = w;
        animMax = 4;
        vanim = 240;
        break;
    case 30:
        height = 16 * 3 - 11;
        h = 17;
        displayH = height - 25;
        animMax = 1;
        break;
    case 31:
        height = 16 * 3 - 11;
        h = 17;
        displayH = height - 25;
        animMax = 1;
        break;
    case 33:
        idle = false;
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 34:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 35:
        height = 22;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 36:
        idle = false;
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 37:
        idle = false;
        height = 22;
        h = height;
        displayH = h;
        width = 19;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 38:
        idle = false;
        animMax = 1;
        vanim = 240;
        break;
    case 39:
        height = 16 * 3 - 12;
        width = 24;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 40:
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 41:
        height = 16 * 3 - 7;
        h = 23;
        displayH = h;
        animMax = 1;
        break;
    case 42:
        height = 16 * 3 - 7;
        h = 23;
        displayH = h;
        animMax = 1;
        break;
    case 43:
        height = 16 * 3 - 6;
        h = 24;
        displayH = h;
        animMax = 1;
        break;
    case 44:
        height = 28;
        h = height;
        displayH = h;
        width = 28;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 45:
        height = 16 * 3 - 6;
        h = 24;
        displayH = height - 25;
        animMax = 1;
        break;
    case 46:
        height = 27;
        h = height;
        displayH = h;
        width = 22;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 47:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 48:
        height = 48;
        h = height;
        displayH = h;
        width = 32;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 49:
        height = 16 * 3 - 11;
        h = 16;
        displayH = height - 25;
        animMax = 1;
        break;
    case 50:
        animMax = 1;
        vanim = 240;
        break;
    case 51:
        idle = false;
        height = 27;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 52:
        idle = false;
        height = 24;
        animMax = 1;
        vanim = 240;
        break;
    case 53:
        height = 16 * 3 - 11;
        h = 17;
        displayH = height - 25;
        animMax = 1;
        break;
    case 54:
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 55:
        height = 25;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 56:
        idle = false;
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        vanim = 240;
        break;
    case 57:
        height = 27;
        h = height;
        displayH = h;
        width = 22;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 58:
        height = 27;
        h = height;
        displayH = h;
        width = 22;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 59:
        height = 16 * 3 - 11;
        h = 17;
        displayH = height - 25;
        animMax = 1;
        break;
    case 60:
        height = 22;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 61:
        idle = false;
        height = 19;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 62:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 63:
        height = 24;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 64:
        height = 17;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 65:
        height = 27;
        h = height;
        displayH = h;
        width = 22;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 66:
        height = 29;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 67:
        height = 32;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 68:
        width = 22;
        w = width;
        displayW = w;
        height = 27;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 69:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 70:
        width = 23;
        w = 16;
        displayW = width;
        height = 25;
        h = height;
        displayH = h;
        animMax = 2;
        break;
    case 71:
        height = 32;
        h = height;
        displayH = h;
        width = 32;
        w = width;
        displayW = w;
        animMax = 3;
        break;
    case 73:
        height = 29;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 74:
        height = 25;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 75:
        idle = false;
        height = 32;
        h = height;
        displayH = h;
        width = 26;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 76:
        idle = false;
        height = 32;
        h = height;
        displayH = h;
        width = 26;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 77:
        idle = false;
        height = 32;
        h = height;
        displayH = h;
        width = 26;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 78:
        height = 25;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 79:
        height = 27;
        h = height;
        displayH = h;
        width = 24;
        w = width;
        displayW = w;
        animMax = 2;
        break;
    case 80:
        height = 26 + 32;
        h = 26;
        displayH = h;
        animMax = 0;
        break;
    case 81:
        height = 27;
        h = height;
        displayH = h;
        width = 24;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 82:
        height = 25;
        h = height;
        displayH = h;
        animMax = 0;
        vanim = 960;
        break;
    case 83:
        idle = false;
        width = 13;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 84:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 85:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 86:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 87:
        height = 24;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 88:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 89:
        height = 27;
        h = height;
        displayH = h;
        width = 20;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 90:
        width = 20;
        w = width;
        displayW = w;
        height = 27;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 91:
        width = 23;
        w = width;
        displayW = w;
        height = 13;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 92:
        width = 23;
        w = width;
        displayW = w;
        height = 13;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 93:
        width = 23;
        w = width;
        displayW = w;
        height = 14;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 94:
        width = 23;
        w = width;
        displayW = w;
        height = 13;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 95:
        width = 23;
        w = width;
        displayW = w;
        height = 14;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 96:
        height = 29;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 97:
        height = 25;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 98:
        height = 25;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 99:
        height = 25;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 100:
        height = 28;
        h = height;
        displayH = h;
        width = 28;
        w = 16;
        displayW = 28;
        animMax = 0;
        break;
    case 101:
        width = 30;
        w = width;
        displayW = w;
        height = 32;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 102:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 103:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 104:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 105:
        width = 23;
        w = width;
        displayW = w;
        height = 27;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 106:
        width = 18;
        w = width;
        displayW = w;
        height = 32;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 107:
        width = 20;
        w = width;
        displayW = w;
        height = 32;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 108:
        height = 32;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 109:
        width = 35;
        w = width;
        displayW = w;
        height = 30;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 110:
        height = 40;
        h = height;
        displayH = h;
        width = 44;
        w = width;
        displayW = w;
        animMax = 0;
        break;
    case 111:
        height = 26;
        h = height;
        displayH = h;
        width = 12;
        w = width;
        displayW = w;
        animMax = 3;
        vanim = 120;
        break;
    case 112:
        height = 28;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 113:
        width = 12;
        w = width;
        displayW = w;
        height = 22;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    case 114:
        height = 28;
        h = height;
        displayH = h;
        animMax = 0;
        break;
    }
    /*if (type == 47 && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAvancement() == AV_TUTO_OK) {
        direction = N;
    }*/

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    if ((type == 36 || type == 37) && direction == W)
    {
        idle = true;
        direction = W;
        animMax = 0;
    }
    else if (type == 63 && link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_ENCLUME)
    {
        animMax = 1;
    }
    else if (type == 73 && !link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS))
    {
        height = 34;
    }
    else if ((type == 2 || type == 7 || type == 12 || type == 19 || type == 20 || type == 24 || type == 27 || type == 30 || type == 31 || type == 41 || type == 42 || type == 43 || type == 45 || type == 53 || type == 59) && direction == N)
    {
        direction = S;
        height = h;
        displayH = h;
    }
    else if (type == 82 && scene->getCoffre(0, 27) == -2)
    {
        animMax = 1;
    }
    else if (type == 52 && direction == N)
    {
        direction = S;
        h = height;
        displayH = h;
        idle = true;
    }
    else if (type == 12 && direction == W)
    {
        direction = S;
        displayH = h;
    }
    else if (type == 6 && direction == N)
    {
        direction = S;
        idle = true;
    }
    else if (type == 6 && direction == W)
    {
        idle = true;
    }
}

void Pnj::setAnimMax(int i)
{
    animMax = i;
}

void Pnj::loop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    if (type == 71)
    {
        BoundingBox bb(x - 32, y - 32, width + 32 * 2, height + 32 * 2);
        Direction old = direction;
        direction = scene->checkCollisionsWithLink(&bb) ? S : N;
        if (direction != old)
        {
            AudioManager::getInstance()->playSound(TS_PLOUF);
            scene->getMap()->addEffect(new Plouf(x + 8, y - 8));
        }
    }

    switch (type)
    {
    case 6:
        if (scene->getMap()->getId() == 58 && scene->getMap()->isJeuCasinoStarted())
        {
            if (scene->getMap()->getBounds()->getX() == 320 && scene->getMap()->getBounds()->getY() == 240 * 4)
            {
                if (y < 67 * 16)
                {
                    direction = S;
                    moveY(1);
                }
                else if (x > 28 * 16)
                {
                    direction = W;
                    moveX(-1);
                    if (x == 28 * 16)
                        direction = S;
                }
            }
            else if (scene->getMap()->getBounds()->getX() == 320 * 2 && scene->getMap()->getBounds()->getY() == 0)
            {
                if (y < 7 * 16)
                {
                    direction = S;
                    moveY(1);
                }
                else if (x > 48 * 16)
                {
                    direction = W;
                    moveX(-1);
                    if (x == 48 * 16)
                        direction = S;
                }
            }
            else if (scene->getMap()->getBounds()->getX() == 0 && scene->getMap()->getBounds()->getY() == 240 * 5)
            {
                if (!scene->getMap()->isJeuCasinoFini())
                {
                    if (y < 82 * 16)
                    {
                        direction = S;
                        moveY(1);
                    }
                    else if (x > 12 * 16)
                    {
                        direction = W;
                        moveX(-1);
                        if (x == 12 * 16)
                            direction = S;
                    }
                }
            }
            else if (scene->getMap()->getBounds()->getX() == 320 * 6 && scene->getMap()->getBounds()->getY() == 240 * 5)
            {
                if (y > 82 * 16)
                {
                    direction = S;
                    moveY(-1);
                }
                else if (x > 125 * 16)
                {
                    direction = W;
                    moveX(-1);
                    if (x == 125 * 16)
                        direction = S;
                }
            }
            else if (scene->getMap()->getBounds()->getX() == 320 * 4 && scene->getMap()->getBounds()->getY() == 240)
            {
                if (y < 22 * 16)
                {
                    direction = S;
                    moveY(1);
                }
                else if (x > 90 * 16)
                {
                    direction = W;
                    moveX(-1);
                    if (x == 90 * 16)
                        direction = S;
                }
            }
        }
        break;
    case 7:
        if (link->getInventory()->hasObject(PERLE) && scene->getMap()->getId() == 33)
        {
            scene->getMap()->addObject(new Pnj(32 * 16 + 8, 30 * 16 + 11, 53, 337));
            alive = false;
        }
        break;
    case 9:
        if (scene->getMap()->getEpoque() == EP_PASSE)
        {
            direction = !link->getInventory()->hasObject(TROC_GEMME_VERTE) || link->getInventory()->getTrocGemme(3) < TGV_CONFITURE ? N : S;
        }
        else
        {
            direction = !link->getInventory()->hasObject(TROC_GEMME_VERTE) || link->getInventory()->getTrocGemme(3) < TGV_BALAIS ? S : N;
        }
        break;
    case 15:
        if (scene->getMap()->getId() == 57 && scene->getMap()->getBounds()->getX() == 320 * 8 && !scene->getMonsters(50))
        {
            if (x < 162 * 16 + 8)
            {
                direction = E;
                moveX(1);
            }
            else if (y > 19 * 16 + 8)
            {
                direction = N;
                moveY(-1);
            }
            else if (direction == N)
            {
                direction = E;
                AudioManager::getInstance()->playSound(TS_SHOOT);
                ProjectileHelper::getInstance()->addProjectile(TP_ARROW_GOLD, x + 16, y + 7, E);
            }
        }
        else if (scene->getMap()->getId() == 60)
        {
            if (x < 62 * 16)
            {
                direction = E;
                moveX(1);
                if (x == 62 * 16)
                {
                    cooldown = 2;
                    AudioManager::getInstance()->playSound(TS_SHOOT);
                    ProjectileHelper::getInstance()->addProjectile(TP_ARROW_GOLD, x + 16, y + 7, E);
                }
            }
        }
        else if (scene->getMap()->getId() == 64 && scene->getAvancement() > AV_PARLE_ZELDA_GROTTE)
        {
            if (link->getEpee() == 2 && scene->getAvancement() < AV_ZELDA_POUSSEE)
            {
                MainController::getInstance()->getGameController()->displayText(575);
            }
            else if (scene->getAvancement() == AV_ZELDA_POUSSEE && x < 16 * 12)
            {
                direction = E;
                moveX(1);
            }
            else
            {
                direction = scene->getAvancement() == AV_PORTAIL_F_OUVERT ? N : S;
            }
        }
        break;
    case 46:
        if (scene->getMap()->getId() == 154 && link->getInventory()->getTrocGemme(0) >= TGR_ALLIANCE)
        {
            animMax = 1;
            if (y < 28 * 16)
            {
                moveY(1);
            }
            else
            {
                alive = false;
            }
        }
        break;
    case 52:
        if (scene->getMap()->getId() == 140 && link->getInventory()->getTrocGemme(0) >= TGR_RIEN_2)
        {
            if (y < 12 * 16)
            {
                direction = S;
                moveY(1);
            }
            else if (x < 9 * 16 + 8)
            {
                direction = E;
                moveX(1);
            }
            else if (y < 13 * 16 + 8)
            {
                direction = S;
                moveY(1);
            }
            else
            {
                alive = false;
            }
        }
        break;
    case 58:
        if (texte == 1301 && scene->getAvancement() == AV_RESERVE_VIDE && x > 67 * 16 + 5)
        {
            direction = W;
            animMax = 1;
            vanim = 240;
            moveX(-1);
            if (x == 67 * 16 + 5)
            {
                direction = S;
                animMax = 0;
            }
        }
        if (texte == 1304 && scene->getAvancement() == AV_PARLE_GARDE_RESERVE && y > 34 * 16 + 5)
        {
            direction = N;
            animMax = 1;
            vanim = 240;
            moveY(-1);
            if (y == 34 * 16 + 5)
            {
                direction = W;
                animMax = 0;
            }
        }
        if (texte == 1316 && scene->getAvancement() == AV_PARLE_GARDE_CH_FORTE && y > 49 * 16 + 5)
        {
            direction = N;
            animMax = 1;
            vanim = 240;
            moveY(-1);
            if (y == 49 * 16 + 5)
            {
                direction = W;
                animMax = 0;
            }
        }
        if (texte == 1318 && scene->getAvancement() == AV_PARLE_GARDE_SOUS_SOL && y > 169 * 16 + 5)
        {
            direction = N;
            animMax = 1;
            vanim = 240;
            moveY(-1);
            if (y == 169 * 16 + 5)
            {
                direction = W;
                animMax = 0;
                AudioManager::getInstance()->playSound(TS_DOOR);
                scene->getMap()->ouvrePorte(98, 171, 1);
            }
        }

        break;
    case 63:
        if (animMax == 0 && link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_ENCLUME)
        {
            animMax = 1;
        }
        break;
    case 65:
        if (scene->getMap()->getId() == 34 && scene->getAvancement() == AV_GARDES_F_ACHETES)
        {
            if (x < 39 * 16)
            {
                if (x > 37 * 16 + 5)
                {
                    animMax = 1;
                    moveX(-1);
                }
                else
                {
                    animMax = 0;
                }
            }
            else
            {
                if (x < 41 * 16 + 5)
                {
                    animMax = 1;
                    moveX(1);
                }
                else
                {
                    animMax = 0;
                }
            }
        }
        else if (scene->getMap()->getId() == 155 && scene->getAvancement() == AV_MOT_DE_PASSE_DONNE && x < 320 * 4)
        {
            if (x < 69 * 16)
            {
                if (x > 66 * 16 + 5 + 4)
                {
                    animMax = 1;
                    moveX(-1);
                }
                else
                {
                    animMax = 0;
                }
            }
            else
            {
                if (x < 72 * 16 + 5 - 4)
                {
                    animMax = 1;
                    moveX(1);
                }
                else
                {
                    animMax = 0;
                }
            }
        }
        else if (scene->getMap()->getId() == 155 && scene->getAvancement() == AV_MULTIPASSE_UTILISE && x > 320 * 4)
        {
            if (x > 127 * 16 + 5)
            {
                animMax = 1;
                moveX(-1);
            }
            else
            {
                animMax = 0;
            }
        }
        break;
    case 67:
        if (x == 89 * 16 + 8 && scene->getCoffre(0, 32) == 9)
        {
            alive = false;
        }
        break;
    case 76:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_HACHE)
        {
            type = 77;
            ResourceManager::getInstance()->free(image);
            image = ResourceManager::getInstance()->loadImage("data/images/npcs/personnage77.png", true);
        }
        break;
    case 90:
        if (scene->getMap()->getId() == 56 && direction == S && scene->getCoffre(11, 20))
        {
            direction = N;
        }
        else if (scene->getMap()->getId() == 60 && x > 72 * 16)
        {
            moveX(-4);
            if (x <= 72 * 16 + 8)
            {
                animMax = 3;
                vanim = 60;
            }
        }
        break;
    }

    if (!idle)
    {

        BoundingBox bb(x - 16 * 2, y - 16 * 2, width + 32 * 2, height + 32 * 2);
        stop = !scene->checkCollisionsWithLink(&bb);

        if (stop)
        {
            BoundingBox *bblink = scene->getLink()->getBoundingBox();
            int dN = y - (bblink->getY() + bblink->getH());
            int dS = bblink->getY() - (y + height);
            int dW = x - (bblink->getX() + bblink->getW());
            int dE = bblink->getX() - (x + width);
            if (dN >= dS && dN >= dW && dN >= dE)
                direction = N;
            if (dS >= dN && dS >= dW && dS >= dE)
                direction = S;
            if (dW >= dS && dW >= dN && dW >= dE)
                direction = W;
            if (dE >= dS && dE >= dW && dE >= dN)
                direction = E;
        }
        else
        {
            // move
            int randomValue = (int)((float)rand() / RAND_MAX * (100));
            switch (randomValue)
            {
            case 1:
                moveX(-1);
                direction = W;
                break;
            case 2:
                moveX(1);
                direction = E;
                break;
            case 3:
                moveY(-1);
                direction = N;
                break;
            case 4:
                moveY(1);
                direction = S;
                break;
            default:
                if (randomValue < 8)
                    break;
                switch (direction)
                {
                case N:
                    moveY(-1);
                    break;
                case S:
                    moveY(1);
                    break;
                case W:
                    moveX(-1);
                    break;
                case E:
                    moveX(1);
                    break;
                }
                break;
            }
        }
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (type == 90 && animMax > 0)
            {
                animMax = 0;
                BoundingBox bb = BoundingBox(69 * 16 + 8, 82 * 16, 16, 16);
                scene->getMap()->testDegat(&bb, W, 20, TA_PHYSIC, TE_MORT, true);
                MainController::getInstance()->getGameController()->displayText(1657);
            }
        }
        if (cooldown)
            cooldown--;
        chrono.reset();
    }
}

void Pnj::draw(int offsetX, int offsetY)
{
    if (idle)
    {
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        switch (type)
        {
        case 6:
            WindowManager::getInstance()->draw(image, width * (direction % 2), h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        case 9:
        case 33:
        case 36:
        case 37:
        case 47:
        case 52:
        case 57:
        case 71:
            WindowManager::getInstance()->draw(image, width * direction, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        case 15:
            if (scene->getMap()->getId() == 57 && x == 162 * 16 + 8 && y == 19 * 16 + 8 && direction == E && !scene->getMonsters(50))
            {
                WindowManager::getInstance()->draw(image, 64, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else if (scene->getMap()->getId() == 60 && x == 62 * 16 && cooldown)
            {
                WindowManager::getInstance()->draw(image, 64, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else
            {
                WindowManager::getInstance()->draw(image, width * direction, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        case 46:
        case 65:
            if (animMax == 0)
            {
                WindowManager::getInstance()->draw(image, 0, h * 2, displayW, displayH, x - offsetX, y - offsetY);
            }
            else
            {
                WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        case 58:
            if (animMax == 0)
            {
                WindowManager::getInstance()->draw(image, width * direction, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else
            {
                WindowManager::getInstance()->draw(image, width * direction, h * (anim + 1), displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        case 67:
            if (x == 89 * 16 + 8 && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCoffre(0, 32) >= 9)
            {
                return;
            }
            WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        case 73:
            if (height == 34)
            {
                WindowManager::getInstance()->draw(image, 0, 29, displayW, displayH, x - offsetX, y - offsetY);
                WindowManager::getInstance()->draw(image, 16, 0, 16, 32, x - offsetX, y - offsetY + 2);
            }
            else
            {
                WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        case 82:
            if (animMax == 0)
            {
                WindowManager::getInstance()->draw(image, 0, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else
            {
                WindowManager::getInstance()->draw(image, 0, h * (anim + 1), displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        case 90:
            if (direction == S)
            {
                WindowManager::getInstance()->draw(image, 0, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else if (direction == W)
            {
                if (x > 72 * 16 + 8 || (anim == 0 && animMax > 0))
                    WindowManager::getInstance()->draw(image, 60, 0, 31, displayH, x - offsetX + 3, y - offsetY);
                else if (anim == 1)
                    WindowManager::getInstance()->draw(image, 91, 0, 31, displayH, x - offsetX - 15, y - offsetY);
                else if (anim == 2)
                    WindowManager::getInstance()->draw(image, 122, 0, 36, displayH, x - offsetX - 20, y - offsetY);
                else if (anim == 3)
                    WindowManager::getInstance()->draw(image, 158, 0, 41, displayH, x - offsetX - 25, y - offsetY);
                else if (animMax == 0)
                    WindowManager::getInstance()->draw(image, 40, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            else
            {
                WindowManager::getInstance()->draw(image, w, 0, displayW, displayH, x - offsetX, y - offsetY);
            }
            break;
        default:
            WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        }
    }
    else
    {
        switch (type)
        {
        case 3:
        case 6:
        case 51:
        case 75:
        case 76:
        case 77:
            WindowManager::getInstance()->draw(image, width * (direction % 2), h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        case 4:
            WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        default:
            WindowManager::getInstance()->draw(image, width * direction, height * anim, width, height, x - offsetX, y - offsetY);
            break;
        }
    }
}

bool Pnj::action(Direction dir)
{
    MainController::getInstance()->getGameController()->displayText(getDynamicText());
    return true;
}

BoundingBox *Pnj::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    if (idle)
    {
        box.setW(w);
        box.setH(h);
    }
    if (type == 15)
    {
        box.setY(y + 7);
        box.setH(16);
    }
    if (type == 28)
    {
        box.setX(x + 9);
        box.setW(16);
    }
    if (type == 29)
    {
        box.setX(x + 5);
        box.setW(16);
    }
    if (type == 33)
    {
        box.setY(y + 9);
        box.setH(16);
    }
    if (type == 46 || type == 65)
    {
        box.setY(y + 11);
        box.setH(16);
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link *link = scene->getLink();
        if (scene->getMap()->getId() == 154 && link->getInventory()->getTrocGemme(0) >= TGR_ALLIANCE)
        {
            box.setX(x + 3);
            box.setW(16);
        }
    }
    if (type == 58)
    {
        box.setX(x + 3);
        box.setY(y + 3);
        box.setH(24);
        box.setW(16);
    }
    if (type == 90)
    {
        box.setX(x + 2);
        box.setY(y + 11);
        box.setW(16);
        box.setH(16);
    }
    return &box;
}

int Pnj::getDown()
{
    if (idle)
    {
        return y + displayH;
    }
    else
    {
        return y + height;
    }
}

int Pnj::getDynamicText()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    // int tmp = 0;
    switch (texte)
    {
    case 231:
        if (scene->getAvancement() >= AV_GARDE_VU)
        {
            return 235;
        }
        break;
    case 270:
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_CARTE && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 271;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_BALAIS)
        {
            return 277;
        }
        break;
    case 280:
        if (link->getInventory()->getTroc(TT_ROUAGE) > -1)
        {
            if (link->getInventory()->hasQuartCoeur(2))
            {
                return 285;
            }
            else
            {
                return 283;
            }
        }
        break;
    case 283:
        if (link->getInventory()->hasQuartCoeur(4))
        {
            return 285;
        }
        break;
    case 286:
        if (link->getStatus()->getMaxRupees() == 999)
        {
            return 285;
        }
        else if (link->getStatus()->getMaxRupees() == 500)
        {
            return 292;
        }
        else if (link->getStatus()->getMaxRupees() == 200)
        {
            return 289;
        }
        break;
    case 337:
        if (link->getInventory()->hasObject(PERLE))
        {
            return 285;
        }
        break;
    case 340:
        if (link->getStatus()->getMaxGanonOr() == 999)
        {
            return 285;
        }
        else if (link->getStatus()->getMaxGanonOr() == 500)
        {
            return 346;
        }
        else if (link->getStatus()->getMaxGanonOr() == 200)
        {
            return 343;
        }
        break;
    case 349:
        if (link->getInventory()->getTroc(TT_ROUE) > -1)
        {
            if (link->getInventory()->hasObject(BOMBES))
            {
                return 285;
            }
            else
            {
                return 352;
            }
        }
        break;
    case 369:
        if (!link->getInventory()->hasObject(PERLE))
        {
            return 370;
        }
        break;
    case 372:
        if (link->getStatus()->getMaxPieceOr() == 999)
        {
            return 285;
        }
        else if (link->getStatus()->getMaxPieceOr() == 500)
        {
            return 378;
        }
        else if (link->getStatus()->getMaxPieceOr() == 200)
        {
            return 375;
        }
        break;
    case 386:
    case 387:
    case 388:
    case 389:
    case 390:
    case 616:
    case 1016:
    case 1024:
    case 1036:
    case 1037:
    case 1038:
    case 1047:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        break;
    case 391:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (scene->getMap()->getEpoque() == EP_PASSE && link->getStatus()->getMaxPieceOr() == 0)
        {
            return 1021;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_BALAIS && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 392;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) >= TGV_CONFITURE)
        {
            return 398;
        }
        break;
    case 404:
        if (scene->getAvancement() == AV_GARDES_F_ACHETES)
        {
            return 406;
        }
        break;
    case 420:
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_CRANE && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 422;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) >= TGJ_REC_DETTE)
        {
            return 429;
        }
        break;
    case 433:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_BOTTES && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 434;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_MARTEAU)
        {
            return 440;
        }
        break;
    case 460:
        if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS))
        {
            return 463;
        }
        if (link->getInventory()->hasObject(CANNE_A_PECHE_1))
        {
            return 461;
        }
        break;
    case 465:
        if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS))
        {
            return 467;
        }
        if (link->getInventory()->hasObject(CANNE_A_PECHE_1))
        {
            return 466;
        }
        break;
    case 471:
        if (link->getInventory()->hasGemmeForce(93))
        {
            return 285;
        }
        if (link->getInventory()->hasGemmeForce(92))
        {
            return 475;
        }
        if (link->getInventory()->hasGemmeForce(91))
        {
            return 473;
        }
        break;
    case 488:
        if (!link->getInventory()->hasObject(PALMES))
        {
            if (scene->getAvancement() >= AV_BARQUE_LOUEE)
            {
                return 491;
            }
            return 489;
        }
        break;
    case 503:
        if (link->getInventory()->hasObject(BOTTES))
        {
            return 285;
        }
        break;
    case 527:
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_VIN && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 529;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) >= TGJ_POUDRE_OR)
        {
            return 535;
        }
        break;
    case 537:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_GEMME && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 538;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_ENCLUME)
        {
            return 544;
        }
        break;
    case 547:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_CLOCHE && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 549;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_HACHE)
        {
            return 555;
        }
        break;
    case 569:
        if (scene->getAvancement() == AV_PORTAIL_F_OUVERT)
        {
            return 574;
        }
        if (link->getInventory()->hasMedaillon(0))
        {
            if (link->getInventory()->hasMedaillon(1))
            {
                if (link->getInventory()->hasMedaillon(2))
                {
                    return link->getEpee() == 2 ? 575 : 572;
                }
                else
                {
                    return 571;
                }
            }
            else
            {
                return 570;
            }
        }
        break;
    case 591:
        if (scene->getAvancement() < AV_SAGES_GROTTE)
        {
            return 597;
        }
        else if (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            return 590;
        }
        break;
    case 593:
        if (scene->getAvancement() < AV_SAGES_GROTTE)
        {
            return 597;
        }
        else if (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            return 592;
        }
        break;
    case 595:
        if (scene->getAvancement() < AV_PORTAIL_PRE_PRESENT_FERME)
        {
            return 594;
        }
        break;
    case 600:
        if ((link->getStatus()->getMaxBombs() < 30 && link->getInventory()->hasObject(BOMBES)) || link->getStatus()->getMaxArrows() < 70)
        {
            return 601;
        }
        if (!link->getInventory()->hasObject(RECUP_FLECHE) || !link->getInventory()->hasObject(RECUP_BOMBE))
        {
            return 606;
        }
        break;
    case 610:
        if (link->getStatus()->getMaxMagic() > 32)
        {
            return 580;
        }
        break;
    case 631:
        if (scene->getAvancement() == AV_APPREND_POUR_ROC_GIVRE)
        {
            if (link->getInventory()->getTroc(TT_ROC_GIVRE) == -1)
            {
                return 632;
            }
            return 633;
        }
        break;
    case 658:
        if (link->getInventory()->totalGemmeForce() < 200 || link->getInventory()->nbGemmeForce() > 0)
        {
            return 616;
        }
        break;
    case 661:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0) || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0) || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0) || (link->getInventory()->hasObject(FLACON_4) && link->getInventory()->getFlacon(3) == 0))
        {
            return 662;
        }
        break;
    case 673:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_FER_CHEVAL && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 674;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_RIEN)
        {
            return 681;
        }
        break;
    case 682:
        if (scene->getMap()->areChestsClosed())
        {
            return 586;
        }
        if (!link->getInventory()->hasQuartCoeur(15) || !link->getInventory()->hasGemmeForce(160) || !link->getInventory()->hasGemmeForce(161) || !link->getInventory()->hasGemmeForce(162))
        {
            return 683;
        }
        break;
    case 688:
        if (link->getInventory()->getTroc(TT_ROUAGE) == 0)
        {
            return 697;
        }
        if (link->getInventory()->getTroc(TT_ROUAGE) == 1)
        {
            return 696;
        }
        if (link->getInventory()->hasObject(SAC_TROC))
        {
            return 695;
        }
        break;
    case 698:
        if ((!link->getInventory()->hasObject(FLACON_1) || link->getInventory()->getFlacon(0) != 0) && (!link->getInventory()->hasObject(FLACON_2) || link->getInventory()->getFlacon(1) != 0) && (!link->getInventory()->hasObject(FLACON_3) || link->getInventory()->getFlacon(2) != 0) && (!link->getInventory()->hasObject(FLACON_4) || link->getInventory()->getFlacon(3) != 0))
        {
            return 661;
        }
        break;
    case 700:
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_GEMME && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 702;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) >= TGV_CARTE)
        {
            return 708;
        }
        break;
    case 711:
        if (scene->getCoffre(0, 19))
        {
            return 750;
        }
        if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS))
        {
            if (scene->getTotalPoissons() >= 10 && !link->getInventory()->hasObject(CANNE_A_PECHE_2))
            {
                return 742;
            }
            if (scene->getTotalPoissons() >= 15 && !link->getInventory()->hasObject(FLACON_3))
            {
                return 744;
            }
            if (scene->getTotalPoissons() >= 20 && !link->getInventory()->hasObject(CANNE_A_PECHE_3))
            {
                return 745;
            }
            if (scene->getTotalPoissons() >= 25 && !link->getInventory()->hasQuartCoeur(14))
            {
                return 747;
            }
            if (scene->getTotalPoissons() >= 30)
            {
                return 748;
            }
            if (scene->getTotalPoissons() % 5 == 4)
            {
                return 751;
            }
            return 741;
        }
        if (link->getInventory()->hasObject(CANNE_A_PECHE_1))
        {
            if (scene->getTotalPoissons() >= 5)
            {
                return 733;
            }
            if (scene->getTotalPoissons() == 4)
            {
                return 732;
            }
            return 731;
        }
        if (scene->getAvancement() == AV_PARLE_PECHE)
        {
            return 713;
        }
        break;
    case 755:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_GEMME && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 757;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_BOTTES)
        {
            return 764;
        }
        break;
    case 775:
        if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS))
        {
            return 776;
        }
        break;
    case 789:
        if (scene->getAvancement() == AV_PANCARTE_MINE_LUE)
        {
            return 790;
        }
        if (scene->getAvancement() == AV_PARLE_GARS_MINE_SALOON)
        {
            return 792;
        }
        if (scene->getAvancement() == AV_PARLE_BARMAN_SALOON)
        {
            return 793;
        }
        if (scene->getAvancement() > AV_PARLE_BARMAN_SALOON && link->getInventory()->getTroc(TT_ROC_GIVRE) == -1)
        {
            return 795;
        }
        if (scene->getAvancement() < AV_DETTE_PAYEE && link->getInventory()->getTroc(TT_ROC_GIVRE) > 0)
        {
            return 796;
        }
        if (scene->getAvancement() == AV_DETTE_PAYEE)
        {
            return 797;
        }
        if (scene->getAvancement() == AV_GARS_MINE_AIDE)
        {
            return 798;
        }
        break;
    case 822:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_MARTEAU && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 824;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_PLAN && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 831;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_SCIE && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 836;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_CLOU && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 841;
        }
        if (link->getInventory()->hasObject(FLECHE_FEU) && link->getInventory()->hasObject(FLECHE_GLACE) && link->getInventory()->hasObject(FLECHE_LUMIERE) && link->getInventory()->hasObject(FLACON_4))
        {
            return 830;
        }
        break;
    case 845:
        if (link->getInventory()->hasObject(ENCYCLOPEDIE))
        {
            if (scene->getMonstersSolde() == 0)
            {
                return 857;
            }
            if (scene->getMap()->getEpoque() == EP_FUTUR && link->getStatus()->getMaxGanonOr() == 0)
            {
                return 858;
            }
            if (scene->getMap()->getEpoque() == EP_PASSE && scene->getMonstersSolde() / 4 == 1)
            {
                return 851;
            }
            if (scene->getMap()->getEpoque() == EP_PASSE)
            {
                return 852;
            }
            if (scene->getMap()->getEpoque() == EP_PRESENT)
            {
                return 853;
            }
            return 854;
        }
        break;
    case 872:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_CORDE && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 874;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_PLAN)
        {
            return 880;
        }
        break;
    case 881:
        if (link->getInventory()->getTroc(TT_POIVRON) > -1)
        {
            return 885;
        }
        break;
    case 886:
        if (link->getInventory()->hasObject(CHANT_2))
        {
            return 901;
        }
        if (scene->getAvancement() > AV_SAGES_GROTTE)
        {
            return 900;
        }
        if (link->getInventory()->hasObject(CLE_TEMPS))
        {
            return 899;
        }
        if (link->getInventory()->getTroc(TT_POIVRON) > -1)
        {
            return 898;
        }
        if (scene->getCoffre(4, 30))
        {
            return 897;
        }
        if (link->getInventory()->hasObject(GRAPPIN))
        {
            return 896;
        }
        break;
    case 912:
        if (link->getInventory()->hasGemmeForce(173))
        {
            return 934;
        }
        if (scene->getCoffre(0, 26) == 18)
        {
            return 933;
        }
        if (scene->getCoffre(0, 27) == -2)
        {
            return 916 + scene->getCoffre(0, 26) - 1;
        }

        if (scene->getCoffre(0, 26))
        {
            return 914;
        }
        if (link->getStatus()->getMaxGanonOr() > 0)
        {
            return 913;
        }
        break;
    case 939:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_RIEN)
        {
            return 940;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_BIJOU)
        {
            return 943;
        }
        break;
    case 944:
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_CONFITURE && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 946;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) >= TGV_CROISSANT)
        {
            return 952;
        }
        break;
    case 953:
        if (link->getStatus()->getMaxGanonOr() > 0)
        {
            return 956;
        }
        break;
    case 967:
        if (scene->getCoffre(0, 28))
        {
            return 972;
        }
        break;
    case 974:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_ENCLUME && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 976;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_MARTEAU && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 984;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_POUDRE_OR && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 990;
        }
        if (link->getInventory()->getTrocGemme(0) > TGR_ENCLUME && link->getInventory()->getTrocGemme(1) > TGB_MARTEAU && link->getInventory()->getTrocGemme(2) > TGJ_POUDRE_OR)
        {
            return 983;
        }
        break;
    case 996:
        if (link->getEpee() > 2)
        {
            return 1005;
        }
        if (link->getEpee() == 0)
        {
            return 1002;
        }
        break;
    case 1003:
        if (link->getEpee() > 0)
        {
            return 1005;
        }
        break;
    case 1039:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_CROISSANT && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 1040;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) >= TGV_BIERE)
        {
            return 1046;
        }
        break;
    case 1048:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (scene->getCoffre(0, 29) < 3)
        {
            return 1049;
        }
        break;
    case 1068:
        if (link->getInventory()->hasGemmeForce(178))
        {
            return 1077;
        }
        break;
    case 1082:
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) == TGB_HACHE && link->getInventory()->getCurrent() == TROC_GEMME_BLEUE)
        {
            return 1083;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_BLEUE) && link->getInventory()->getTrocGemme(1) >= TGB_CORDE)
        {
            return 1089;
        }
        break;
    case 1094:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_ALLIANCE && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 1095;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_RIEN_2)
        {
            return 1101;
        }
        break;
    case 1116:
        if (link->getInventory()->hasGemmeForce(182))
        {
            return 1117;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE))
        {
            return 1118;
        }
        break;
    case 1120:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_BIJOU && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 1121;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_LETTRE)
        {
            return 1127;
        }
        break;
    case 1129:
        if (scene->getCoffre(0, 32))
        {
            return 1131;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_REC_DETTE && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 1130;
        }
        break;
    case 1150:
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_REC_DETTE && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 1151;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) >= TGJ_SCIE)
        {
            return 1158;
        }
        break;
    case 1164:
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) == TGR_LETTRE && link->getInventory()->getCurrent() == TROC_GEMME_ROUGE)
        {
            return 1165;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_ROUGE) && link->getInventory()->getTrocGemme(0) >= TGR_ALLIANCE)
        {
            return 1172;
        }
        break;
    case 1173:
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_CUILLERE && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 1174;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) >= TGJ_CRANE)
        {
            return 1180;
        }
        break;
    case 1184:
        if (scene->getAvancement() == AV_MOT_DE_PASSE_CONNU)
        {
            return 1186;
        }
        if (scene->getAvancement() >= AV_MOT_DE_PASSE_DONNE)
        {
            return 1187;
        }
        break;
    case 1185:
        if (scene->getAvancement() == AV_MULTIPASS)
        {
            return 1188;
        }
        if (scene->getAvancement() >= AV_MULTIPASSE_UTILISE)
        {
            return 1187;
        }
        break;
    case 1189:
        if (scene->getAvancement() >= AV_MOT_DE_PASSE_CONNU)
        {
            return 1195;
        }
        break;
    case 1199:
        if (!link->getInventory()->hasObject(PERLE))
        {
            return 1198;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) == TGV_BIERE && link->getInventory()->getCurrent() == TROC_GEMME_VERTE)
        {
            return 1200;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_VERTE) && link->getInventory()->getTrocGemme(3) >= TGV_CLOU)
        {
            return 1203;
        }
        break;
    case 1247:
        if (link->getInventory()->hasObject(GANTS))
        {
            return 1249;
        }
        if (scene->getRooms(1, 16, 4))
        {
            return 1248;
        }
        break;
    case 1252:
        if (scene->getCoffre(4, 30))
        {
            return 1255;
        }
        break;
    case 1300:
        if (scene->getAvancement() >= AV_PARLE_GARDE_PALAIS)
        {
            return 1306;
        }
        break;
    case 1301:
        if (scene->getAvancement() >= AV_PARLE_ZELDA_PALAIS)
        {
            return 1306;
        }
        if (link->getStatus()->getMaxRupees() > 0)
        {
            return 1309;
        }
        if (scene->getAvancement() >= AV_PARLE_GARDE_PALAIS)
        {
            return 1303;
        }
        break;
    case 1304:
        if (link->getStatus()->getMaxRupees() > 0)
        {
            return 1306;
        }
        if (scene->getAvancement() < AV_PARLE_GARDE_PALAIS)
        {
            return 1300;
        }
        if (scene->getAvancement() >= AV_PARLE_GARDE_RESERVE)
        {
            return 1305;
        }
        break;
    case 1305:
        if (link->getStatus()->getMaxRupees() > 0)
        {
            return 1306;
        }
        break;
    case 1309:
        if (scene->getAvancement() >= AV_PARLE_ZELDA_PALAIS)
        {
            return 1306;
        }
        break;
    case 1312:
        if (scene->getAvancement() >= AV_PARLE_ZELDA_PALAIS)
        {
            return 1315;
        }
        break;
    case 1316:
        if (scene->getAvancement() < AV_PARLE_GARDE_PALAIS)
        {
            return 1300;
        }
        if (scene->getAvancement() != AV_PARLE_ZELDA_PALAIS)
        {
            return 1306;
        }
        break;
    case 1318:
        if (scene->getAvancement() >= AV_PARLE_GARDE_SOUS_SOL)
        {
            return 1319;
        }
        break;
    case 1321:
        if (scene->getAvancement() >= AV_PASSAGE_TROUVE)
        {
            return 1327;
        }
        break;
    case 1355:
        if (link->getInventory()->hasObject(ARC_OR) && !scene->getCoffre(12, 14))
        {
            return 1364;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_MIROIR && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 1356;
        }
        if (scene->getMonsters(50))
        {
            return 1383;
        }
        if (scene->getCoffre(12, 14))
        {
            return 1367;
        }
        break;
    case 1390:
        if (scene->getAvancement() < AV_SPEECH_VINCENT && scene->getCoffre(12, 15) && scene->getCoffre(12, 16) && scene->getCoffre(12, 17))
        {
            return 1721;
        }
        break;
    case 1435:
        if (scene->getCoffre(13, 4))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoGagne())
        {
            return 1439;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1440;
        }
        break;
    case 1441:
        if (scene->getCoffre(13, 5))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoGagne())
        {
            return 1439;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1443;
        }
        break;
    case 1445:
        if (scene->getCoffre(13, 8))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoStarted())
        {
            return 1446;
        }
        break;
    case 1447:
        if (scene->getCoffre(13, 8))
        {
            return 1438;
        }
        break;
    case 1448:
        if (scene->getCoffre(13, 0))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoGagne())
        {
            return 1439;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1440;
        }
        break;
    case 1449:
        if (scene->getCoffre(13, 7))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1440;
        }
        break;
    case 1454:
        if (scene->getCoffre(13, 1))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoGagne())
        {
            return 1439;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1440;
        }
        break;
    case 1455:
        if (scene->getCoffre(13, 6))
        {
            return 1438;
        }
        if (scene->getMap()->isJeuCasinoFini())
        {
            return 1456;
        }
        break;
    case 1458:
        if (link->getInventory()->hasCoeur(11))
        {
            return 1460;
        }
        if (scene->getCoffre(13, 2))
        {
            return 1459;
        }
        break;
    case 1644:
        if (scene->getCoffre(15, 13))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 4 && scene->getMap()->getDestFinalNbEnn() >= 30)
        {
            return 1646;
        }
        break;
    case 1647:
        if (scene->getCoffre(15, 14))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 10 && scene->getMap()->getDestFinalNbEnn() >= 60)
        {
            return 1646;
        }
        break;
    case 1648:
        if (scene->getCoffre(15, 15))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 3 && scene->getMap()->getDestFinalNbEnn() >= 20)
        {
            return 1646;
        }
        break;
    case 1649:
        if (scene->getCoffre(15, 16))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 12 && scene->getMap()->getDestFinalNbEnn() >= 99)
        {
            return 1646;
        }
        break;
    case 1650:
        if (scene->getCoffre(15, 17))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 12 && scene->getMap()->getDestFinalNbEnn() >= 30)
        {
            return 1646;
        }
        break;
    case 1651:
        if (scene->getCoffre(15, 18))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 6 && scene->getMap()->getDestFinalNbEnn() >= 40)
        {
            return 1646;
        }
        break;
    case 1652:
        if (scene->getCoffre(15, 19))
        {
            return 1645;
        }
        if (scene->getMap()->getDestFinalTypeEnn() >= 7 && scene->getMap()->getDestFinalNbEnn() >= 50)
        {
            return 1646;
        }
        break;
    case 1657:
        if (!scene->getMap()->nbEnnemis())
        {
            return 1659;
        }
        break;
    case 1658:
        if (!scene->getMap()->nbEnnemis())
        {
            return 1660;
        }
        if (x > 72 * 16 + 8)
        {
            return 1661;
        }
        break;
    default:
        break;
    }
    return texte;
}

void Pnj::setDirection(Direction dir)
{
    direction = dir;
}

void Pnj::moveX(int dx)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(bb->getX() + dx);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Pnj::moveY(int dy)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(bb->getY() + dy);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

void Pnj::moveTo(int i, int j, Direction dir)
{
    x = i;
    y = j;
    direction = dir;
    checkPosition();
}

int Pnj::getType()
{
    return type;
}
