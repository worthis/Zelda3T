#include "Ennemi098.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi098::Ennemi098(int i, int j) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi98.png", true);
    chrono.reset();

    type = 98;

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

    life = 14;
    maxLife = 14;
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

Ennemi098::~Ennemi098() {
    ResourceManager::getInstance()->free(image);
}

bool Ennemi098::isResetable() {
    return alive;
}

void Ennemi098::reset() {
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

void Ennemi098::ennLoop() {
    if (step == 2 || step == 3) testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 0) {
                if (life <= 8) special = 1;
                if (life <= 4) special = 2;

                int randomValue = (int)((float)rand() / RAND_MAX * 3);
                x = startX + randomValue * 6 * 16;
                getBoundingBox();
                checkPosition();
                animMax = 3;
                step = 1;
            } else if (step == 1) {
                animMax = 1;
                AudioManager::getInstance()->playSound(TS_PLOUF);
                MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8, y-8));
                if (special) {
                    int oppositeDX = (x%320) == 15*16 ? -12*16 : 6*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8));
                }
                if (special == 2) {
                    int oppositeDX = (x%320) == 3*16 ? 12*16 : -6*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8));
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
                    int oppositeDX = (x%320) == 15*16 ? -12*16 : 6*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8));
                }
                if (special == 2) {
                    int oppositeDX = (x%320) == 3*16 ? 12*16 : -6*16;
                    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEffect(new Plouf(x+8+oppositeDX, y-8));
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

void Ennemi098::draw(int offsetX, int offsetY) {
    if (!alive || step == 0) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int oppositeDstX1 = dstX;
    int oppositeDstX2 = dstX;
    if (special) {
        oppositeDstX1 += 6*16;
        if (oppositeDstX1 > 15*16) oppositeDstX1 = 3*16;
    }
    if (special == 2) {
        oppositeDstX2 -= 6*16;
        if (oppositeDstX2 < 3*16) oppositeDstX2 = 15*16;
    }

    if (step == 1 || step == 4) {
        if (special == 1 && step == 1) {
            WindowManager::getInstance()->draw(image, 32, anim * height, width, height, oppositeDstX1, dstY);
        } else if (special == 2 && step == 1) {
            WindowManager::getInstance()->draw(image, 32, anim * height, width, height, oppositeDstX2, dstY);
        } else {
            WindowManager::getInstance()->draw(image, 32, anim * height, width, height, dstX, dstY);
        }
    } else if (step == 2 || step == 3) {
        WindowManager::getInstance()->draw(image, 0, (step - 2) * height, width, height, dstX, dstY);
        if (special == 1) {
            WindowManager::getInstance()->draw(image, 0, 64, 32, 32, oppositeDstX1, dstY);
        }
        if (special == 2) {
            WindowManager::getInstance()->draw(image, 0, 64, 32, 32, oppositeDstX2, dstY);
            WindowManager::getInstance()->draw(image, 0, 96, 32, 32, oppositeDstX1, dstY);
        }
    }
}

void Ennemi098::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, 0, 0, width, height, x, y);
}

int Ennemi098::getX() {
    return x;
}

int Ennemi098::getY() {
    return y;
}

BoundingBox* Ennemi098::getBoundingBox() {
    box.setX(x);
    box.setY(y);
    return &box;
}

void Ennemi098::snipe() {

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

bool Ennemi098::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return step == 2 || step == 3;
}

bool Ennemi098::isToAvoid(Collision c) {
    return c != EAU_PROF;
}
