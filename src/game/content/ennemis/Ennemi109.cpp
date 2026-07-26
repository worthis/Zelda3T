#include "Ennemi109.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

Ennemi109::Ennemi109(int i, int j) : anim(0), animMax(3), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi109.png", true);
    chrono.reset();

    type = 109;

    cooldown = 95;

    x = i;
    y = j;
    direction = E;

    // for quadtree operations:
    width = 123;
    height = 96;

    box.setX(x + 32);
    box.setY(y + 32);
    box.setW(48);
    box.setH(48);

    startX = x;
    startY = y;
    startDir = direction;

    life = 60;
    maxLife = 60;
    recul = 0;
    vitesseRecul = 0;
    step = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 8;
}

Ennemi109::~Ennemi109() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi109::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animMax = 3;
    cooldown = 95;
    step = 0;
    checkPosition();
}

bool Ennemi109::isResetable() {
    return alive;
}

void Ennemi109::ennLoop() {
    if (step == 0) {
        cooldown--;
        if (cooldown <= 0) {
            cooldown = 0;
            step = 1;
        }
    } else if (step == 2) {
        int vitesse = 1 + ((maxLife - life) / 20);
        if (direction == W) {
            if (x > startX) {
                moveX(-vitesse);
            } else {
                step = 1;
                direction = E;
            }
        } else if (direction == E) {
            if (x < startX + 13 * 16 + 5) {
                moveX(vitesse);
            } else {
                step = 1;
                direction = W;
            }
        }
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if ((int)((float)rand() / RAND_MAX * 5) == 0) {
                step = 2;
            }
        }
        if (step == 1 && anim == 2) {
            snipe();
        }
        chrono.reset();
    }
}

void Ennemi109::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;
    int srcX = (direction % 2) * width;
    int srcY = anim * height;
    int srcH = height;

    if (step == 0) {
        srcY += cooldown;
        srcH -= cooldown;
    }

    WindowManager::getInstance()->draw(image, srcX, srcY, width, srcH, dstX, dstY);
}

void Ennemi109::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, width, 0, width, height, x, y);
}

void Ennemi109::moveX(int dx) {
    x += dx;
    getBoundingBox();
    checkPosition();
}

int Ennemi109::getX() {
    return x;
}

int Ennemi109::getY() {
    return y;
}

BoundingBox* Ennemi109::getBoundingBox() {
    box.setX(x + 32);
    box.setY(y + 32);
    return &box;
}

void Ennemi109::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156) {
        AudioManager::getInstance()->playMusic(20);
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 190 * 16, 85 * 16 + 8, 7));
    }
}

void Ennemi109::snipe() {
    int offset = ((int)((float)rand() / RAND_MAX * 3)) * 8;
    for (int i = 0; i < 4; i++) {
        int dstX = startX + (5 + 3 * i) * 16 + offset;
        int dstY = y + 10 * 16 + 8;
        snipeInternal(dstX, dstY);
    }
    AudioManager::getInstance()->playSound(TS_THROW);
}

void Ennemi109::snipeInternal(int destx, int desty) {
    double anglx = 0;
    double angly = 0;

    int origx = x + 61;
    int origy = y + 48;

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
}

bool Ennemi109::isToAvoid(Collision c) {
    return false;
}

bool Ennemi109::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return effect != TE_FEU;
}
