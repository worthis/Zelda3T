#include "Gemme.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Gemme::Gemme(int i, int j, int num) : id(num)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    vanim = 120;
    animMax = 7;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(16);
    box.setH(16);
}

Gemme::~Gemme()
{
    ResourceManager::getInstance()->free(image);
}

void Gemme::loop()
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

void Gemme::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }
    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int srcX = 0;
    int srcY = anim == 0 || anim == 4 ? 0 : 16 * id;

    switch (anim)
    {
    case 0:
    case 4:
        srcX = 192 + 16 * id;
        break;
    case 1:
    case 3:
        srcX = 256;
        break;
    case 2:
        srcX = 272;
        break;
    case 5:
    case 7:
        srcX = 288;
        break;
    case 6:
        srcX = 304;
        break;
    }

    WindowManager::getInstance()->draw(image, srcX, srcY, 16, 16, dstX, dstY);
}

void Gemme::action()
{
    switch (id)
    {
    case 0:
        getLink()->trouveObjet(TI_GEMME_ROUGE);
        break;
    case 1:
        getLink()->trouveObjet(TI_GEMME_BLEUE);
        break;
    case 2:
        getLink()->trouveObjet(TI_GEMME_JAUNE);
        break;
    case 3:
        getLink()->trouveObjet(TI_GEMME_VERTE);
        break;
    default:
        break;
    }
    alive = false;
}

bool Gemme::isPickable()
{
    return false;
}
