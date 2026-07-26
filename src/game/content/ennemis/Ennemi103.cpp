#include "Ennemi103.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi103::Ennemi103(int i, int j) : anim(0), animMax(5), vanim(180), cooldown(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi103.png", true);
    SDL_SetTextureBlendMode(image->getImage(), SDL_BLENDMODE_BLEND);

    chrono.reset();

    type = 103;

    x = i;
    y = j;

    // for quadtree operations:
    width = 83;
    height = 83;

    box.setX(x+26);
    box.setY(y+51);
    box.setW(32);
    box.setH(32);

    life = 40;
    maxLife = 40;
    recul = 0;
    vitesseRecul = 0;

    step = 0;
    alpha = 0;
    SDL_SetTextureAlphaMod(image->getImage(), alpha);

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi103::~Ennemi103() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi103::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
    step = 0;
    alpha = 0;
    animMax = 5;
    direction = S;
}

bool Ennemi103::isResetable() {
    return alive;
}

void Ennemi103::ennLoop() {

    if (step == 6 && anim > 0) {
        switch (direction) {
            case N : break;
            case S : if (y < 22*16-3) moveY(4); break;
            case W : if (x > 242*16+6) moveX(-4); break;
            case E : if (x < 252*16+6) moveX(4); break;
        }
    }
    if (step == 3) {
        alpha += 4;
        if (alpha >= 255) {
            alpha = 255;
            step = life > 20 ? 1 : 5;
            cooldown = 0;
        }
        SDL_SetTextureAlphaMod(image->getImage(), alpha);
    }
    if (step == 2) {
        alpha -= 4;
        if (alpha <= 0) {
            alpha = 0;
            step = 3;
            cooldown = 0;
            int randomValue = (int)((float)rand() / RAND_MAX * 3);
            if (randomValue == 0) direction = E;
            if (randomValue == 1) direction = S;
            if (randomValue == 2) direction = W;
            x = (242 + randomValue * 5) * 16 + 6;
            y = randomValue == 1 ? 17*16-3 : 20*16-3;
            getBoundingBox();
            checkPosition();
        }
        SDL_SetTextureAlphaMod(image->getImage(), alpha);
    }
    if (step == 1) {
        Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        if (map->getSol(242*16, 17*16) == 1936 && map->getSol(257*16, 17*16) == 1936 && map->getSol(242*16, 27*16) == 1936 && map->getSol(257*16, 27*16) == 1936) {
            step = 4;
            cooldown = 0;
            chrono.reset();
        }
    }

    if  (step != 0 && step != 2 && step != 3) {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 5) {
                step = 6;
                animMax = 4;
            } else if (step == 6) {
                step = 2;
                cooldown = 0;
                animMax = 5;
            }
        }
        if (step == 1) {
            if (++cooldown == 12) {

                // retrieve target position ( = link ^^)
                Link* link = getLink();

                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;

                // throw proj and play sound
                double anglx = 0;
                double angly = 0;
                int origx = x + 41;
                int origy = y + 19;
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

                ProjectileHelper::getInstance()->addProjectile(TP_BIG_FEU, origx, origy, anglx, angly);
                AudioManager::getInstance()->playSound(TS_THROW);
                cooldown = 0;
            }
        } else if (step == 0 || step == 4) {
            cooldown++;
            Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            if (cooldown == 8) {
                map->setSol(242*16, 17*16, 1935);
            } else if (cooldown == 12) {
                map->setSol(257*16, 17*16, 1935);
            } else if (cooldown == 16) {
                map->setSol(242*16, 27*16, 1935);
            } else if (cooldown == 20) {
                map->setSol(257*16, 27*16, 1935);
                step = step == 0 ? 3 : 2;
                cooldown = 0;
            }
        }
        chrono.reset();
    }
}

void Ennemi103::draw(int offsetX, int offsetY) {
    if (!alive || step == 0) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;


    if (step == 4) {
        WindowManager::getInstance()->draw(image, 249, 0, width, height, dstX, dstY);
    } else if (step == 6) {
        WindowManager::getInstance()->draw(image, 249, (1 + anim) * height, 95, height, dstX - 6, dstY);
    } else {
        int srcX = 0;
        if (getLink()->getX() + 16 <= x) srcX = 83;
        if (getLink()->getX() >= x + 83) srcX = 166;
        WindowManager::getInstance()->draw(image, srcX, anim * height, width, height, dstX, dstY);
    }

}

void Ennemi103::drawEncyclopedie() {
    SDL_SetTextureAlphaMod(image->getImage(), 255);
    WindowManager::getInstance()->draw(image, 166, 0, width, height, x, y);
    SDL_SetTextureAlphaMod(image->getImage(), alpha);
}

void Ennemi103::moveX(int dx) {
    x += dx;
    getBoundingBox();
    checkPosition();
}

void Ennemi103::moveY(int dy) {
    y += dy;
    getBoundingBox();
    checkPosition();
}

int Ennemi103::getX() {
    return x;
}

int Ennemi103::getY() {
    return y;
}

BoundingBox* Ennemi103::getBoundingBox() {
    box.setX(x+26);
    box.setY(y+51);
    return &box;
}

bool Ennemi103::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    Link* link = getLink();
    if (step == 1 || step == 5) {
        step = 2;
    }
    return (step == 4 || step == 6) &&
        (((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 2) || (type == TA_ARROW && link->getInventory()->hasObject(ARC_FEE)));
}

void Ennemi103::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    AudioManager::getInstance()->playMusic(20);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 4));
    map->killEnnemis(map->getBounds());
}
