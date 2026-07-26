#include "Naufrage.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Naufrage::Naufrage(int x, int y) : x(x - 16), y(y - 16), anim(0), animMax(2), vanim(60), step(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/effects/naufrage.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 32;
    height = 32;
}

Naufrage::~Naufrage()
{
    ResourceManager::getInstance()->free(image);
}

void Naufrage::loop()
{
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            if (step == 0)
            {
                step = 1;
                animMax = 1;
                vanim = 240;
            }
            anim = 0;
        }
        chrono.reset();
    }
}

void Naufrage::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (step == 0)
    {
        WindowManager::getInstance()->draw(image, width * anim, 0, width, height, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(image, 96 + width * anim, 0, width, height, dstX, dstY);
    }
}

int Naufrage::getX() { return x; }
int Naufrage::getY() { return y; }
