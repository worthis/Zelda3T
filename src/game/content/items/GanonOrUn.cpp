#include "GanonOrUn.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

GanonOrUn::GanonOrUn(int i, int j)
{

    x = i;
    y = j - 10;
    persistent = false;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 16;
    height = 26;

    box.setX(x + 4);
    box.setY(y + 10 + 4);
    box.setW(8);
    box.setH(12);
}

GanonOrUn::~GanonOrUn()
{
    ResourceManager::getInstance()->free(image);
}

void GanonOrUn::loop()
{
    if (animMax > 0 && chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            if (!ready)
            {
                ready = true;
                animMax = 0;
            }
            anim = 0;
        }
        chrono.reset();
    }
}

void GanonOrUn::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (ready)
    {
        dstY += 10;
    }
    else
    {
        if (anim <= 10)
            dstY += anim;
        else if (anim <= 14)
            dstY += 10 - (anim - 10);
        else if (anim <= 18)
            dstY += 6 + (anim - 14);
        else
            dstY += 10;
    }

    WindowManager::getInstance()->draw(image, 24, 3, 6, 4, dstX + 5, y - offsetY + 22);
    WindowManager::getInstance()->draw(image, 160, 64, 16, 16, dstX, dstY);
}

void GanonOrUn::action()
{
    if (!ready)
        return;
    AudioManager::getInstance()->playSound(TS_RUPEE);
    getLink()->getStatus()->updateGanonOr(1);
    alive = false;
}
