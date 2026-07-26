#include "Ennemi107.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../helper/ProjectileHelper.h"

#include "../effects/Plouf.h"

Ennemi107::Ennemi107(int i, int j)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi107.png", true);
    chrono.reset();

    type = 107;

    x = i;
    y = j;

    // for quadtree operations:
    width = 78;
    height = 123;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(1);

    startX = x;
    startY = y;
    startDir = direction;

    life = 120;
    maxLife = 120;
    recul = 0;
    vitesseRecul = 0;
    idle = true;

    step = 0;
    anim = 0;
    animMax = 2;
    vanim = 180;
    special = 122;
    nbShots = 1;

    isBoss = true;
    stunnable = false;

    forceEnn = 1;
}

Ennemi107::~Ennemi107()
{
    ResourceManager::getInstance()->free(image);
}

bool Ennemi107::isResetable()
{
    return alive;
}

void Ennemi107::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    step = 0;
    anim = 0;
    animMax = 2;
    special = 122;
    nbShots = 1;
    checkPosition();
}

void Ennemi107::ennLoop()
{

    int vitesse = 1 + (maxLife - life) / 8;

    if (step == 1)
    {
        special -= vitesse;
        ;
        if (special <= 0)
        {
            step = 2;
            animMax = 2 + life / 20;
            nbShots = 1 + (maxLife - life) / 8;
            special = 0;
        }
        getBoundingBox();
        checkPosition();
    }
    else if (step == 4)
    {
        special += vitesse;
        if (special >= 123)
        {
            step = 0;
            animMax = 3;
            special = 123;
        }
        getBoundingBox();
        checkPosition();
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
            if (step == 0)
            {
                int randomValue = (int)((float)rand() / RAND_MAX * 3);
                x = startX + ((5 * 16 + 8) * (randomValue - 1));
                step = 1;
                animMax = 3;
                special = 123;
                getBoundingBox();
                checkPosition();
            }
            else if (step == 3 || (step == 2 && nbShots <= 0))
            {
                step = 4;
                animMax = 3;
            }
            else if (step == 2)
            {
                snipe();
                nbShots--;
            }
        }
        chrono.reset();
    }
}

void Ennemi107::draw(int offsetX, int offsetY)
{
    if (!alive || step == 0)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int srcX = 0;

    Link *link = getLink();
    if (step == 3)
        srcX = width * 3;
    else if (link->getX() + 16 <= x)
        srcX = width * 2;
    else if (link->getX() >= x + width)
        srcX = width;

    WindowManager::getInstance()->draw(image, srcX, special, width, height - special, dstX, dstY);
}

void Ennemi107::drawEncyclopedie()
{
    WindowManager::getInstance()->draw(image, 0, 64, width, height - 64, x, y);
}

int Ennemi107::getX()
{
    return x;
}

int Ennemi107::getY()
{
    return y;
}

BoundingBox *Ennemi107::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    box.setH(special >= 115 ? 1 : 115 - special);
    return &box;
}

void Ennemi107::snipe()
{
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    // throw proj and play sound
    double anglx = 0;
    double angly = 0;
    int origx = x + 39;
    int origy = y + 108;
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

    ProjectileHelper::getInstance()->addProjectile(TP_BIG_FEU, origx, origy, anglx, angly);
    AudioManager::getInstance()->playSound(TS_THROW);
}

bool Ennemi107::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return type == TA_MASSIF && effect == TE_NORMAL;
}

void Ennemi107::giveItem(int i, int j)
{
    Ennemi::giveItem(i, j);
    AudioManager::getInstance()->playMusic(20);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    if (map->getId() != 156)
    {
        map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, 250 * 16, 33 * 16, 6));
    }
    // map->killEnnemis(map->getBounds());
}

bool Ennemi107::isToAvoid(Collision c)
{
    return false;
}

void Ennemi107::afterHit()
{
    if (life > 0)
    {
        step = 3;
        animMax = 7;
    }
}
