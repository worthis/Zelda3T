#include "Jarre.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../effects/Debris.h"

#include "../../MainController.h"

Jarre::Jarre(int i, int j, int id, TypeItem it, Map *mp) : type(id), item(it), map(mp)
{
    x = i;
    y = j;
    x0 = x;
    y0 = y;
    poids = 1;

    image = ResourceManager::getInstance()->loadImage("data/images/link/objets.png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    // no collisions
    box.setX(0);
    box.setY(0);
    box.setW(-1);
    box.setH(-1);

    // init map with motif and collisions - type can be 0 or 1
    map->setSol(x, y, 3140 + type, MUR);
}

Jarre::~Jarre()
{
    ResourceManager::getInstance()->free(image);
}

void Jarre::portLoop()
{
    // nothing to do
}

void Jarre::draw(int offsetX, int offsetY)
{
    if (alive && (carried || moving))
    {
        // shadow
        if (moving)
        {
            WindowManager::getInstance()->draw(image, 100, 106, 12, 6, x - offsetX + 2, y - offsetY + height - 6);
        }
        WindowManager::getInstance()->draw(image, 112, 16 * type, 16, 16, x - offsetX, y - offsetY);
    }
}

void Jarre::impact()
{
    AudioManager::getInstance()->playSound(TS_BREAK);
    map->addEffect(new Debris(x + 8, y + 8, direction, 1));
    alive = false;
}

void Jarre::onLift()
{
    if (item == TI_INTERRUPTEUR)
    {
        map->displayInterruptor(x, y);
        return;
    }
    map->setSol(x0, y0, 3142, PIERRE);

    if (!map->testGemmeForce(x / 16, y / 16) && item != TI_NO_ITEM)
    {

        Epoque epoque = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getEpoque();

        if ((item != TI_RUBIS_VERT && item != TI_RUBIS_BLEU && item != TI_RUBIS_ROUGE) || (epoque == EP_PASSE && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getStatus()->getMaxPieceOr()) || (epoque == EP_PRESENT && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getStatus()->getMaxRupees()) || (epoque == EP_FUTUR && MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->getStatus()->getMaxGanonOr()))
        {
            map->addItem(ItemHelper::getInstance()->createItem(item, x + 8, y + 2));
            item = TI_NO_ITEM;
        }
    }
}

bool Jarre::isResetable()
{
    return true;
}

void Jarre::reset()
{
    x = x0;
    y = y0;
    map->setSol(x, y, 3140 + type, MUR);
    alive = true;
    carried = false;
    moving = false;
    carriable = true;
    air = 0;
    checkPosition();
}

void Jarre::removeItem()
{
    item = TI_NO_ITEM;
}
