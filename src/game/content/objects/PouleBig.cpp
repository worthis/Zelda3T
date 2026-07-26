#include "PouleBig.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../helper/ProjectileHelper.h"

#include "../ennemis/Ennemi142.h"

#include "Poule.h"

#include "../effects/FumeeBlanche.h"

#include "../../MainController.h"

PouleBig::PouleBig(int i, int j) : anim(0), animMax(1), vanim(180), stop(0), invul(0), tolerance(3)
{
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/pouleBig.png", true);

    // for quadtree operations:
    width = 48;
    height = 48;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    box2.setX(0);
    box2.setY(0);
    box2.setW(-1);
    box2.setH(-1);

    attackable = false;
    safeMode = true;
    carriable = false;

    step = 0;
    special = 160;

    chrono.reset();
}

PouleBig::~PouleBig()
{
    ResourceManager::getInstance()->free(image);
}

void PouleBig::portLoop()
{
    MainController::getInstance()->getGameController()->getSceneController()->getScene()->getHud()->setBossLife(1, 1);

    if (!alive)
        return;

    if (step == 0)
    {
        special--;
        if (special <= 0)
        {
            step = 1;
            special = 0;
            attackable = true;
            carriable = true;
        }
        return;
    }

    if (step == 1 && !moving && !carried && !stop)
    {
        special++;
        if (special >= 64)
        {
            Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
            Link *link = scene->getLink();
            Map *map = scene->getMap();

            int nbObjects = map->nbObjects() + ((link->getAnimation() == PORTE || link->getAnimation() == TRANSPORTE) ? 1 : 0);

            if (nbObjects < 5)
            {
                int options = 3;
                BoundingBox bb1 = BoundingBox(184 * 16, 36 * 16, 16, 16);
                BoundingBox bb2 = BoundingBox(195 * 16, 36 * 16, 16, 16);
                bool bb1Ok = !bb1.intersect(getBoundingBox()) && map->checkCollisions(&bb1, this, false, false, false, false, true);
                bool bb2Ok = !bb2.intersect(getBoundingBox()) && map->checkCollisions(&bb2, this, false, false, false, false, true);
                if (!bb1Ok)
                    options--;
                if (!bb2Ok)
                    options--;
                if (options == 1)
                {
                    snipe();
                }
                else
                {
                    int randomValue = (int)((float)rand() / RAND_MAX * (options));
                    if (randomValue == 1 && bb1Ok)
                    {
                        map->addObject(new Poule(184 * 16, 36 * 16));
                        map->addEffect(new FumeeBlanche(184 * 16 + 8, 36 * 16 + 8));
                        AudioManager::getInstance()->playSound(TS_POULE);
                    }
                    else if (randomValue > 0 && bb2Ok)
                    {
                        map->addObject(new Poule(195 * 16, 36 * 16));
                        map->addEffect(new FumeeBlanche(195 * 16 + 8, 36 * 16 + 8));
                        AudioManager::getInstance()->playSound(TS_POULE);
                    }
                    else
                    {
                        snipe();
                    }
                }
            }
            else
            {
                snipe();
            }
            special = 0;
        }
    }

    if (stop > 0)
        stop--;
    if (invul)
    {
        invul--;
        if (!invul)
            attackable = true;
    }

    if (!moving && !carried && !stop)
    {
        // move
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
    else if (carried)
    {
        direction = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getDirection();
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void PouleBig::draw(int offsetX, int offsetY)
{
    if (alive)
    {
        // shadow
        if (moving || !carried || step == 0)
        {
            WindowManager::getInstance()->draw(image, 6, 237, 36, 18, x - offsetX + 6, y - offsetY + height - 18);
            WindowManager::getInstance()->draw(image, 48 * (direction % 2), 51 * anim, 48, 48, x - offsetX, y - offsetY - 3 - (step == 0 ? special : 0));
        }
        else
        {
            WindowManager::getInstance()->draw(image, 48 * (direction % 2), 51 * anim, 48, 48, x - offsetX, y - offsetY);
        }
    }
}

void PouleBig::impact()
{
    AudioManager::getInstance()->playSound(TS_POULE);
}

void PouleBig::onLift()
{
    AudioManager::getInstance()->playSound(TS_POULE);
}

void PouleBig::stopBeforeUp()
{
    stop = 64;
}

void PouleBig::moveX(int dx)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(x + dx);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void PouleBig::moveY(int dy)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(y + dy);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

bool PouleBig::isCollision(Collision c)
{
    switch (c)
    {
    case TROU:
    case HERBE:
    case HERBE_HAUTE:
    case TERRE:
    case EAU:
    case GLACE:
    case SABLE:
    case NEIGE:
    case PIERRE:
    case SOL_BOIS:
    case TAPIS:
    case DANGER_BAS:
        return true;
    case MURRET:
        return moving;
    default:
        return false;
    }
}

BoundingBox *PouleBig::getBoundingBox()
{
    box.setX(x);
    box.setY(y + height - 48);
    return &box;
}

BoundingBox *PouleBig::getSecondBoundingBox()
{
    return &box2;
}

void PouleBig::underAttack(Direction dir, int force, TypeAttack t, TypeEffect effect)
{
    if (!moving && !carried && !stop)
    {
        AudioManager::getInstance()->playSound(TS_HITENNEMY);
        attackable = false;
        invul = 16;
        tolerance--;
        if (!tolerance)
        {
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->enervePoules();
        }
    }
}

void PouleBig::enerve()
{
    if (alive)
    {
        alive = false;
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addEnnemi(new Ennemi142(x, y));
    }
}

void PouleBig::snipe()
{

    int origx = x + (width / 2);
    int origy = y + (height / 2);

    // throw proj and play sound
    Link *link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    double anglx = 0;
    double angly = 0;
    int destx = dstX;
    int desty = dstY - 8;

    double coef1 = 0;
    double coef2 = 0;

    if ((destx - origx) == 0)
    {
        anglx = 0;
        angly = 12;
    }
    else if ((desty - origy) == 0)
    {
        anglx = 12;
        angly = 0;
    }
    else
    {
        coef1 = ((double)(desty - origy)) / ((double)(destx - origx));
        coef2 = ((double)(destx - origx)) / ((double)(desty - origy));
        anglx = (sqrt(12 / (1 + (coef1 * coef1))));
        angly = (sqrt(12 / (1 + (coef2 * coef2))));
    }
    if (destx - origx < 0)
        anglx = -anglx;
    if (desty - origy < 0)
        angly = -angly;

    if (anglx > 4)
        anglx = 4;
    if (angly > 4)
        angly = 4;
    if (anglx < -4)
        anglx = -4;
    if (angly < -4)
        angly = -4;

    ProjectileHelper::getInstance()->addProjectile(TP_FINAL, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_THROW);
}
