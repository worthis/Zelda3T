#include "Ennemi102.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi102::Ennemi102(int i, int j) : anim(0), animMax(1), vanim(180), cooldown(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi102.png", true);
    SDL_SetTextureBlendMode(image->getImage(), SDL_BLENDMODE_BLEND);

    chrono.reset();

    type = 102;

    x = i;
    y = j;

    // for quadtree operations:
    width = 24;
    height = 27;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    life = 20;
    maxLife = 20;
    recul = 32;
    vitesseRecul = 4;

    step = 0;
    alpha = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 3;
}

Ennemi102::~Ennemi102() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi102::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
    step = 0;
    alpha = 0;
}

bool Ennemi102::isResetable() {
    return alive;
}

void Ennemi102::ennLoop() {

    // check light
    if (step == 0) {
        computeAlpha();
        if (alpha == 255) {
            step = 1;
            cooldown = 0;
            chrono.reset();
        }
    }

    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue) {
        case 1 : moveX(-1);direction=W; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1);direction=N; break;
        case 4 : moveY(1); direction=S; break;
        default :
            if (randomValue < 10) break;
            switch (direction) {
                case N : moveY(-1); break;
                case S : moveY(1); break;
                case W : moveX(-1); break;
                case E : moveX(1); break;
            }
            break;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        cooldown++;
        if (step == 0) {
            if (cooldown == 16) {

                // retrieve target position ( = link ^^)
                Link* link = getLink();

                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;

                // throw proj and play sound
                double anglx = 0;
                double angly = 0;
                int origx = x + ((direction % 2) == 0 ? 8 : 16) ;
                int origy = y + 11;
                int destx = dstX;
                int desty = dstY - 8;

                double coef1 = 0;
                double coef2 = 0;

                if ((destx-origx) == 0) {anglx=0; angly=12;}
                else if ((desty-origy) == 0) {anglx=12; angly=0;}
                else {
                    coef1=((double)(desty-origy))/((double)(destx-origx));
                    coef2=((double)(destx-origx))/((double)(desty-origy));
                    anglx=(sqrt(12/(1+(coef1*coef1))));
                    angly=(sqrt(12/(1+(coef2*coef2))));
                }
                if (destx - origx < 0) anglx = -anglx;
                if (desty - origy < 0) angly = -angly;

                if (anglx>4) anglx=4;
                if (angly>4) angly=4;
                if (anglx<-4) anglx=-4;
                if (angly<-4) angly=-4;

                ProjectileHelper::getInstance()->addProjectile(TP_BOULE_FEU, origx, origy, anglx, angly);
                AudioManager::getInstance()->playSound(TS_THROW);
                cooldown = 0;
            }
        } else {
            Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            if (cooldown == 8) {
                map->setSol(162*16, 47*16, 1935);
                alpha = 192;
            } else if (cooldown == 12) {
                map->setSol(177*16, 47*16, 1935);
                alpha = 128;
            } else if (cooldown == 16) {
                map->setSol(162*16, 57*16, 1935);
                alpha = 64;
            } else if (cooldown == 20) {
                map->setSol(177*16, 57*16, 1935);
                alpha = 0;
                step = 0;
                cooldown = 0;
            }
        }
        chrono.reset();
    }
}

void Ennemi102::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    SDL_SetTextureAlphaMod(image->getImage(), alpha);
    WindowManager::getInstance()->draw(image, (direction % 2) * 24, anim * 21, 24, 21, dstX, dstY);

    // shadow
    SDL_SetTextureAlphaMod(image->getImage(), 255);
    WindowManager::getInstance()->draw(image, 0, 42, 24, 6, dstX, dstY + 21);

}

void Ennemi102::drawEncyclopedie() {
    SDL_SetTextureAlphaMod(image->getImage(), 255);
    WindowManager::getInstance()->draw(image, (direction % 2) * 24, anim * 21, 24, 21, x, y);
    WindowManager::getInstance()->draw(image, 0, 42, 24, 6, x, y + 21);
}

void Ennemi102::moveX(int dx) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + dx);

    if (map->checkCollisions(bb, this, true, false, true, false)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Ennemi102::moveY(int dy) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY(y + dy);

    if (map->checkCollisions(bb, this, false, false, true, false)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

int Ennemi102::getX() {
    return x;
}

int Ennemi102::getY() {
    return y;
}

BoundingBox* Ennemi102::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

bool Ennemi102::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    Link* link = getLink();
    return step == 1 &&
        (((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 2)
        || (type == TA_ARROW && link->getInventory()->hasObject(ARC_FEE)));
}

void Ennemi102::computeAlpha() {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    int nbLight = 0;
    if (map->getSol(162*16, 47*16) == 1936) nbLight++;
    if (map->getSol(177*16, 47*16) == 1936) nbLight++;
    if (map->getSol(162*16, 57*16) == 1936) nbLight++;
    if (map->getSol(177*16, 57*16) == 1936) nbLight++;
    alpha = 64 * nbLight;
    if (alpha > 255) alpha = 255;
}
