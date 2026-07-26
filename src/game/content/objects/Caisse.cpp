#include "Caisse.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/Plouf.h"

Caisse::Caisse(int i, int j, int id, int nb, bool p) {
    x = i;
    y = j;
    x0 = x;
    y0 = y;
    type = id;
    nbMoves = nb;
    nbMovesDebut = nb;
    persist = p;

    attackable = type == 5;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/caisse.png", true);
    chiffres = nbMoves > -1 ? ResourceManager::getInstance()->loadImage("data/images/status/chiffres.png", true) : 0;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);
}

Caisse::~Caisse() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(chiffres);
}

void Caisse::loop() {
    if (moving) {

        if (dx != 0) {
            if (dx < 0) {
                width += dx;
            } else {
                x += dx;
                width -= dx;
            }
            box.setX(x);
            box.setW(width);
        } else if (dy != 0) {
            if (dy < 0) {
                height += dy;
            } else {
                y += dy;
                height -= dy;
            }
            box.setY(y);
            box.setH(height);
        }

        if (dx != 0 || dy != 0) {
            // quadtree operations:
            checkPosition();
            computeMaxSize();
        }

        if (height == 16 && width == 16) {
            moving = false;
            dx = 0;
            dy = 0;

            Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
            if (isOnWater(&box)) {
                AudioManager::getInstance()->playSound(TS_PLOUF);
                scene->getMap()->addEffect(new Plouf(x, y));
                alive = false;
            } else if (isOnGap(&box)) {
                AudioManager::getInstance()->playSound(TS_TOMBE);
                alive = false;
            }
            scene->getMap()->testAnimRoom();
        }
    }
}

void Caisse::draw(int offsetX, int offsetY) {

    int i = x - offsetX;
    int j = y - offsetY;

    if (moving) {
        if (dx < 0) {
            i += width - 16;
        } else if (dy < 0) {
            j += height - 16;
        }
    }

    WindowManager::getInstance()->draw(image, 16 * (type % 3), 16 * (type / 3), 16, 16, i, j);
    if (nbMoves != -1) WindowManager::getInstance()->draw(chiffres, (nbMoves%5)*8, ((int)(nbMoves/5))*8, 8, 8, i + 4, j + 4);
}

void Caisse::pousse(Direction d, int v) {
    if (!moving && nbMoves != 0) {
        BoundingBox dest;
        dest.setX(x);
        dest.setY(y);
        dest.setW(16);
        dest.setH(16);

        int moveToDo = 0;

        for (int i = 0; i < 1 || type == 5; i++) {
            switch (d) {
                case N : dest.setY(dest.getY() - 16); break;
                case S : dest.setY(dest.getY() + 16); break;
                case W : dest.setX(dest.getX() - 16); break;
                case E : dest.setX(dest.getX() + 16); break;
            }
            Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
            BoundingBox* bounds = scene->getMap()->getBounds();

            if (dest.getX() < bounds->getX() + 32 || dest.getX() + dest.getW() > bounds->getX() + bounds->getW() - 32 ||
                dest.getY() < bounds->getY() + 32 || dest.getY() + dest.getH() > bounds->getY() + bounds->getH() - 32) {
                break;
            }
            if ((scene->getMap()->getSol(x + 8, y + 8) == 3471 || scene->getMap()->getSol(x + 8, y + 8) == 4002)
                && (scene->getMap()->getSol(dest.getX() + 8, dest.getY() + 8) != 3471
                    && scene->getMap()->getSol(dest.getX() + 8, dest.getY() + 8) != 4002
                    && scene->getMap()->getSol(dest.getX() + 8, dest.getY() + 8) != 625)) {
                break;
            }
            if (!scene->checkCollisions(&dest, this, true)) {
                break;
            }
            moveToDo++;
        }

        if (moveToDo > 0) {
            if (nbMoves > 0) nbMoves--;
            AudioManager::getInstance()->playSound(TS_PUSH);
            moving = true;
            switch (d) {
                case N :
                    y -= 16 * moveToDo;
                    height += 16 * moveToDo;
                    dy = -v;
                    break;
                case S :
                    height += 16 * moveToDo;
                    dy = v;
                    break;
                case W :
                    x -= 16 * moveToDo;
                    width += 16 * moveToDo;
                    dx = -v;
                    break;
                case E :
                    width += 16 * moveToDo;
                    dx = v;
                    break;
            }
            box.setX(x);
            box.setY(y);
            box.setW(width);
            box.setH(height);

            // quadtree operations:
            checkPosition();
            computeMaxSize();
        }
    }
}

int Caisse::getDown() {
    return -1; // ^^
}

bool Caisse::isResetable() {
    return true;
}

void Caisse::reset() {
    alive = true;
    nbMoves = nbMovesDebut;
    if (!persist) {
        moving = false;
        dx = 0;
        dy = 0;
        x = x0;
        y = y0;
        width = 16;
        height = 16;
        box.setX(x);
        box.setY(y);
        box.setW(16);
        box.setH(16);
        checkPosition();
    }
}

int Caisse::getNbMoves() {
    return nbMoves;
}

void Caisse::setNbMoves(int value) {
    nbMoves = value;
}

void Caisse::underAttack(Direction dir, int f, TypeAttack ta, TypeEffect te) {
    if (type == 5 && te == TE_FEU) {
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        AudioManager::getInstance()->playSound(TS_PLOUF, 2);
        scene->getMap()->addEffect(new Plouf(x, y));
        alive = false;
        scene->getMap()->displayInterruptor(x, y);
        scene->getMap()->testAnimRoom();
    }
}
