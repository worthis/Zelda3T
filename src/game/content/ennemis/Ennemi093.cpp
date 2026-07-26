#include "Ennemi093.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi093::Ennemi093(int i, int j) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi93.png", true);
    chrono.reset();

    type = 93;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = 32;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    startX = x;
    startY = y;
    startDir = direction;

    life = 10;
    maxLife = 10;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    step = 0;
    anim = 0;
    animMax = 8;
    vanim = 180;
    special = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi093::~Ennemi093() {
    ResourceManager::getInstance()->free(image);
}

bool Ennemi093::isResetable() {
    return alive;
}

void Ennemi093::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    step = 0;
    anim = 0;
    animMax = 8;
    vanim = 180;
    special = 0;
    checkPosition();
}

void Ennemi093::ennLoop() {
    if (step == 2 || step == 3) testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 0) {
                if (life < 4) special = 1;

                int randomValue = (int)((float)rand() / RAND_MAX * 4);
                x = startX + (randomValue % 2) * 6 * 16;
                y = startY - (randomValue / 2) * 5 * 16;
                getBoundingBox();
                checkPosition();
                animMax = 3;
                step = 1;
            } else if (step == 1) {
                animMax = 1;
                AudioManager::getInstance()->playSound(TS_PLOUF);
                MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8, y-8));
                if (special) {
                    int oppositeDX = ((x % 320) == 6*16) ? 6*16 : -6*16;
                    int oppositeDY = ((y % 240) == 9*16+8) ? -5*16 : 5*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8+oppositeDY));
                }
                step = 2;
            } else if (step == 2) {
                animMax = 5;
                step = 3;
            } else if (step == 3) {
                animMax = 3;
                AudioManager::getInstance()->playSound(TS_PLOUF);
                MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8, y-8));
                if (special) {
                    int oppositeDX = ((x % 320) == 6*16) ? 6*16 : -6*16;
                    int oppositeDY = ((y % 240) == 9*16+8) ? -5*16 : 5*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8+oppositeDY));
                }
                step = 4;
            } else if (step == 4) {
                animMax = 8;
                step = 0;
            }
        }
        if (step == 3 && anim % 2 == 0) {
            snipe();
        }
        chrono.reset();
    }

}

void Ennemi093::draw(int offsetX, int offsetY) {
    if (!alive || step == 0) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int oppositeDstX = (dstX == 6*16) ? 12*16 : 6*16;
    int oppositeDstY = (dstY == 9*16+8) ? 4*16+8 : 9*16+8;

    if (step == 1 || step == 4) {
        if (special == 1 && step == 1) {
            WindowManager::getInstance()->draw(image, 32, anim * height, width, height, oppositeDstX, oppositeDstY);
        } else {
            WindowManager::getInstance()->draw(image, 32, anim * height, width, height, dstX, dstY);
        }
    } else if (step == 2 || step == 3) {
        WindowManager::getInstance()->draw(image, 0, (step - 2) * height, width, height, dstX, dstY);
        if (special == 1) {
            WindowManager::getInstance()->draw(image, 0, 64, 32, 32, oppositeDstX, oppositeDstY);
        }
    }
}

void Ennemi093::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, 0, 0, width, height, x, y);
}

int Ennemi093::getX() {
    return x;
}

int Ennemi093::getY() {
    return y;
}

BoundingBox* Ennemi093::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

void Ennemi093::snipe() {

    // throw proj and play sound
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
    int origx = x + 16;
    int origy = y + 16;
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
}

bool Ennemi093::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return step == 2 || step == 3;
}

void Ennemi093::giveItem(int i, int j) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addObject(new Pnj(x, y, 71, 1247));
}

bool Ennemi093::isToAvoid(Collision c) {
    return c != EAU_PROF;
}
