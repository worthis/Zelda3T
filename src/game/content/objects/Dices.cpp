#include "Dices.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

Dices::Dices(int i, int j, bool sign, bool rm, bool act, Map *map, Caisse *csse) : direction(S), anim(0), animMax(1), vanim(180)
{
    x = i;
    y = j;
    x0 = x;
    y0 = y;
    dir0 = direction;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/dices.png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);

    force = 1;
    signes = sign;
    randomMove = rm;
    actif = act;
    value = 0;
    caisse = csse;
    if (caisse != 0 && map != 0)
    {
        map->addObject(caisse);
    }

    randomMove0 = randomMove;
    actif0 = actif;

    attackable = true;

    chrono.reset();
}

Dices::~Dices()
{
    ResourceManager::getInstance()->free(image);
}

void Dices::loop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (actif)
    {
        BoundingBox *bb = getBoundingBox();
        scene->testDegatOnLink(bb, direction, force, TA_PHYSIC, TE_ARGENT);
    }

    if (randomMove && actif)
    {
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
            if (randomValue < 10)
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

    if (!signes && actif)
    {
        int randomValue = (int)((float)rand() / RAND_MAX * (5));
        if (randomValue >= value)
            randomValue++;
        value = randomValue;
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (signes && actif)
            {
                if (++value > 3)
                    value = 0;
            }
        }
        chrono.reset();
    }
}

void Dices::draw(int offsetX, int offsetY)
{
    WindowManager::getInstance()->draw(image, value * width, anim * height + (signes ? 32 : 0), width, height, x - offsetX, y - offsetY);
}

BoundingBox *Dices::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    return &box;
}

void Dices::moveX(int dx)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + dx);

    scene->testDegatOnLink(bb, direction, force, TA_PHYSIC, TE_ARGENT);

    if (scene->checkCollisions(bb, this, false))
    {
        x += dx;
    }

    if (x != oldX)
    {
        checkPosition();
    }
}

void Dices::moveY(int dy)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + dy);

    scene->testDegatOnLink(bb, direction, force, TA_PHYSIC, TE_ARGENT);

    if (scene->checkCollisions(bb, this, false))
    {
        y += dy;
    }

    if (y != oldY)
    {
        checkPosition();
    }
}

bool Dices::isResetable()
{
    return true;
}

void Dices::reset()
{
    x = x0;
    y = y0;
    direction = dir0;
    randomMove = randomMove0;
    actif = actif0;
    anim = 0;
    value = 0;
    chrono.reset();
    checkPosition();
}

void Dices::underAttack(Direction dir, int force, TypeAttack t, TypeEffect effect)
{
    if (actif)
    {
        AudioManager::getInstance()->playSound(TS_HITENNEMY);
        if (caisse != 0)
        {
            caisse->setNbMoves(value + 1);
        }
    }
    actif = false;
}

bool Dices::isActif()
{
    return actif;
}

int Dices::getValue()
{
    return value;
}

void Dices::activer(bool moving)
{
    actif = true;
    randomMove = moving;
}

void Dices::stopper()
{
    actif = false;
}
