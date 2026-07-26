#include "Ennemi128.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi128::Ennemi128(int i, int j) : anim(0), animMax(4), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi128.png", true);

    type = 128;
    chrono.reset();

    step = 0;

    x = i;
    y = j;

    // for quadtree operations:
    width = 69;
    height = 70;

    box.setX(x+18);
    box.setY(y+14);
    box.setW(32);
    box.setH(48);

    startX = x;
    startY = y;
    startDir = direction;

    life = 200;
    maxLife = 200;
    recul = 0;
    vitesseRecul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 30;
}

Ennemi128::~Ennemi128() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi128::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    animMax = 4;
    step = 0;
    checkPosition();
}

bool Ennemi128::isResetable() {
    return alive;
}

void Ennemi128::ennLoop() {

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_GLACE);

    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
            if (getLink()->getStatus()->getLife() > 0 && getLink()->getY() < 40 * 16) {
                if (step == 0) {
                    step = (int)((float)rand() / RAND_MAX * (3));
                } else {
                    step = 0;
                }
            } else {
                step = 0;
            }
        }

        if (step == 2 && anim == 3) {
            snipe(x+11, y+16);
            snipe(x+57, y+16);
        } else if (step == 1 && anim == 3) {
            ProjectileHelper::getInstance()->addProjectile(TP_SOUFFLE, x + 3, y + 48, S);
            AudioManager::getInstance()->playSound(TS_MAGIC);
        }
        chrono.reset();
    }
}

void Ennemi128::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int anim2 = step == 0 ? 0 : step == 1 ? 1 + ((anim - 1) / 2) : 3 + anim;

    WindowManager::getInstance()->draw(image, anim2 * width, 0, width, height, dstX, dstY);
}

void Ennemi128::snipe(int origx, int origy) {

    // throw proj and play sound
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
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

    ProjectileHelper::getInstance()->addProjectile(TP_BIG_GLACE, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_MAGIC);
}

int Ennemi128::getX() {
    return x;
}

int Ennemi128::getY() {
    return y;
}

BoundingBox* Ennemi128::getBoundingBox() {
    box.setX(x+18);
    box.setY(y+14);
    return &box;
}

void Ennemi128::giveItem(int x, int y) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, x, y, 12));
}
