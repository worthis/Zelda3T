#include "Ennemi099.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi099::Ennemi099(int i, int j) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi99.png", true);
    chrono.reset();

    type = 99;

    x = i;
    y = j;

    // for quadtree operations:
    width = 68;
    height = 95;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    startX = x;
    startY = y;
    startDir = direction;

    life = 49;
    maxLife = 49;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    step = 1;
    anim = 0;
    animMax = 2;
    vanim = 240;
    special = 94;

    isBoss = true;
    stunnable = false;

    forceEnn = 4;
}

Ennemi099::~Ennemi099() {
    ResourceManager::getInstance()->free(image);
}

bool Ennemi099::isResetable() {
    return alive;
}

void Ennemi099::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    step = 1;
    anim = 0;
    animMax = 2;
    special = 94;
    checkPosition();
}

void Ennemi099::ennLoop() {
    if (step != 0) {
        testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);
    }

    if (step == 1) {
        special--;
        if (special <= 0) {
            step = 2;
            animMax = 1;
            special = 0;
        }
        getBoundingBox();
        checkPosition();
    } else if (step == 5) {
        special++;
        if (special >= 94) {
            step = 0;
            animMax = 3;
            special = 94;
        }
        getBoundingBox();
        checkPosition();
    }

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
            if (step == 0) {
                int randomValue = (int)((float)rand() / RAND_MAX * 6);
                switch (randomValue) {
                    case 0 : x=184*16-2; y=26*16; break;
                    case 1 : x=190*16-2; y=17*16; break;
                    case 2 : x=198*16-2; y=32*16; break;
                    case 3 : x=201*16-2; y=23*16; break;
                    case 4 : x=211*16-2; y=35*16; break;
                    case 5 : x=212*16-2; y=19*16; break;
                    default : x=198*16-2; y=32*16; break;
                }
                step = 1;
                animMax = 3;
                special = 94;
                getBoundingBox();
                checkPosition();
            } else if (step == 2) {
                step = 3;
                animMax = 2 + life / 20; // 4 -> 2
            } else if (step == 4) {
                step = 5;
                animMax = 3;
            }

            if (step == 3) {
                snipe();
            }
        }
        chrono.reset();
    }

}

void Ennemi099::draw(int offsetX, int offsetY) {
    if (!alive || step == 0) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int srcX = step == 4 ? 68 : 0;
    int srcY = (step == 3 && anim == 0) || (step == 4 && anim == 3) ? 95 : 0;
    WindowManager::getInstance()->draw(image, srcX, srcY, width, height-special, dstX, dstY+special);
    if (step == 1 || step == 5) {
        srcY = 222 - anim * 16;
        if (srcY < 190) srcY += 32;
        WindowManager::getInstance()->draw(image, 72, srcY, 48, 16, dstX+2-16, dstY+height-16);
        WindowManager::getInstance()->draw(image, 72, srcY, 48, 16, dstX+2+32, dstY+height-16);
    }
}

void Ennemi099::drawEncyclopedie() {
    WindowManager::getInstance()->draw(image, 0, 0, width, height, x, y);
}

int Ennemi099::getX() {
    return x;
}

int Ennemi099::getY() {
    return y;
}

BoundingBox* Ennemi099::getBoundingBox() {
    box.setX(x);
    box.setY(y+special);
    box.setH(height-special);
    return &box;
}

void Ennemi099::snipe() {
    Link* link = getLink();
    int origx = x + 34;
    int origy = y + 44;
    ProjectileHelper::getInstance()->addProjectile(TP_BOULE_ULTIME, origx, origy, link);
    AudioManager::getInstance()->playSound(TS_THROW);
}

bool Ennemi099::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    return type == TA_MAGIC && effect == TE_NORMAL;
}

void Ennemi099::giveItem(int i, int j) {
    Ennemi::giveItem(i, j);
    AudioManager::getInstance()->playMusic(20);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i, j, 3));
    map->killEnnemis(map->getBounds());
}

bool Ennemi099::isToAvoid(Collision c) {
    return c != EAU_PROF;
}

void Ennemi099::afterHit() {
    if (life > 0) {
        step = 4;
        animMax = 7;
    }
}
