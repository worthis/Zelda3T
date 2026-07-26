#include "Ennemi101.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi101::Ennemi101(int i, int j, Direction dir) : cooldown(16) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi101.png");

    type = 101;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    direction = dir;

    box.setX(x + (direction == E ? 8 : 0));
    box.setY(y + (direction == S ? 8 : 0));
    box.setW(width - ((direction == W || direction == E) ? 8 : 0));
    box.setH(height - ((direction == N || direction == S) ? 8 : 0));

    startX = x;
    startY = y;
    startDir = direction;

    life = 1;
    maxLife = 1;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    special = false;

    forceEnn = 4;
}

Ennemi101::~Ennemi101() {
    ResourceManager::getInstance()->free(image);
}

bool Ennemi101::isResetable() {
    return alive;
}

void Ennemi101::reset() {
    Ennemi::reset();
    x = startX;
    y = startY;
    direction = startDir;
    cooldown = 16;
    special = false;
    checkPosition();
}

void Ennemi101::ennLoop() {
    if (!special) return;

    if (cooldown) cooldown--;

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    if (!cooldown) {
        // throw proj and play sound
        double anglx = 0;
        double angly = 0;

        int origx = (direction == N || direction == S) ? x + 16 : direction == W ? x + 32 : x;
        int origy = (direction == W || direction == E) ? y + 16 : direction == N ? y + 32 : y;
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
        cooldown = 64;
    }
}

void Ennemi101::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }
    int dstX = x - offsetX;
    int dstY = y - offsetY;
    WindowManager::getInstance()->draw(image, direction * width, special ? height : 0, width, height, dstX, dstY);
}

void Ennemi101::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, direction * width, height, width, height, x, y);
}

int Ennemi101::getX() {
    return x;
}

int Ennemi101::getY() {
    return y;
}

BoundingBox* Ennemi101::getBoundingBox() {
    return &box;
}

bool Ennemi101::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    bool result = special && type == TA_EXPLO;
    special = true;
    return result;
}

int Ennemi101::getDown() {
    return -1;
}
