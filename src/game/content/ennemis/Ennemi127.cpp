#include "Ennemi127.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi127::Ennemi127(int i, int j) : anim(0), animMax(3), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi127.png", true);
    chrono.reset();

    type = 127;

    x = i;
    y = j;

    // for quadtree operations:
    width = 79;
    height = 63;

    box.setX(x + 23);
    box.setY(y + 31);
    box.setW(32);
    box.setH(32);

    life = 10;
    maxLife = 10;
    recul = 0;

    isBoss = true;
    stunnable = false;

    forceEnn = 1;
}

Ennemi127::~Ennemi127()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi127::reset()
{
    Ennemi::reset();
    chrono.reset();
    anim = 0;
}

bool Ennemi127::isResetable()
{
    return alive;
}

void Ennemi127::ennLoop()
{

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

void Ennemi127::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

int Ennemi127::getX()
{
    return x;
}

int Ennemi127::getY()
{
    return y;
}

BoundingBox *Ennemi127::getBoundingBox()
{
    box.setX(x + 23);
    box.setY(y + 31);
    return &box;
}

bool Ennemi127::hasEffect(TypeAttack type, TypeEffect effect, Direction dir)
{
    return effect == TE_ARGENT;
}

bool Ennemi127::canDie(TypeEffect effect)
{
    return effect == TE_MORT;
}

void Ennemi127::giveItem(int i, int j)
{
    Ennemi::giveItem(i, j);
    AudioManager::getInstance()->playMusic(20);
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addItem(ItemHelper::getInstance()->createItem(TI_COEUR, i + 1, j, 11));
}
