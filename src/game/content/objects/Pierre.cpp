#include "Pierre.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../effects/Debris.h"

#include "../../MainController.h"

Pierre::Pierre(int i, int j, int id, Map *mp, bool rst, bool ennemi) : type(id), map(mp), resetable(rst)
{
    x = i;
    y = j;
    x0 = x;
    y0 = y;

    poids = (((type - 1) % 2) + 1) * 2; // should be 2 or 4

    byEnnemi = ennemi;

    image = ResourceManager::getInstance()->loadImage("data/images/link/objets.png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    // rock has no collisions
    box.setX(0);
    box.setY(0);
    box.setW(-1);
    box.setH(-1);

    // init map with motif and collisions
    if (map->getId() != 156)
    {
        short s = map->getSol(x, y);
        if (type < 3)
        {
            map->setSol(x, y, s - type, MUR);
        }
        else if (type == 3)
        {
            map->setSol(x, y, 1126, MUR);
        }
        else if (type == 4)
        {
            map->setSol(x, y, 1800, MUR);
        }
        else if (type == 5)
        {
            map->setSol(x, y, 2683, MUR);
        }
        else if (type == 6)
        {
            map->setSol(x, y, 2684, MUR);
        }
        else if (type == 8)
        {
            map->setSol(x, y, 5298, MUR);
        }
    }
}

Pierre::~Pierre()
{
    ResourceManager::getInstance()->free(image);
}

void Pierre::portLoop()
{
    // nothing to do
}

void Pierre::draw(int offsetX, int offsetY)
{
    if (alive && (carried || moving))
    {
        // shadow
        if (moving)
        {
            WindowManager::getInstance()->draw(image, 100, 106, 12, 6, x - offsetX + 2, y - offsetY + height - 6);
        }

        int srcY = 0;
        int srcX = type == 8 ? 96 : 112;
        switch (type)
        {
        case 1:
            srcY = 32;
            break;
        case 2:
            srcY = 80;
            break;
        case 3:
        case 5:
            srcY = 64;
            break;
        case 4:
        case 6:
            srcY = 96;
            break;
        case 7:
        case 8:
            srcY = 112;
            break;
        default:
            srcY = 32;
            break;
        }

        WindowManager::getInstance()->draw(image, srcX, srcY, 16, 16, x - offsetX, y - offsetY);
    }
}

void Pierre::impact()
{
    AudioManager::getInstance()->playSound(TS_BREAK);
    map->addEffect(new Debris(x + 8, y + 8, direction, poids, byEnnemi));
    alive = false;
}

void Pierre::onLift()
{
    if (map->getId() != 156)
    {
        short s = map->getSol(x0, y0);
        if (type < 3)
        {
            Collision c = HERBE;
            switch (s)
            {
            case 944:
            case 945:
                c = SABLE;
                break;
            default:
                c = HERBE;
                break;
            }
            map->setSol(x0, y0, s + type, c);
        }
        else if (type < 5)
        {
            map->setSol(x, y, 275, HERBE);
        }
        else if (type < 7)
        {
            map->setSol(x, y, 946, SABLE);
        }
        else if (type == 8)
        {
            map->setSol(x, y, 5114, PIERRE);
        }
        map->testGemmeForce(x / 16, y / 16);
    }
}

bool Pierre::isResetable()
{
    return resetable;
}

void Pierre::reset()
{
    x = x0;
    y = y0;
    if (map->getMur(x, y) != MUR && map->getId() != 156)
    {
        short s = map->getSol(x, y);
        if (type < 3)
        {
            map->setSol(x, y, s - type, MUR);
        }
        else if (type == 3)
        {
            map->setSol(x, y, 1126, MUR);
        }
        else if (type == 4)
        {
            map->setSol(x, y, 1800, MUR);
        }
        else if (type == 5)
        {
            map->setSol(x, y, 2683, MUR);
        }
        else if (type == 6)
        {
            map->setSol(x, y, 2684, MUR);
        }
        else if (type == 8)
        {
            map->setSol(x, y, 5298, MUR);
        }
    }
    alive = true;
    carried = false;
    moving = false;
    carriable = true;
    air = 0;
    checkPosition();
}
