#include "MapController.h"

#include "../../../engine/util/geometry/BoundingBox.h"
#include "../../MainController.h"

MapController::MapController()
{
}

MapController::~MapController()
{
}

void MapController::launch()
{
    switch (step)
    {
    case MAP_OVERWORLD:
        overworld.launch();
        break;
    case MAP_OCARINA:
        ocarina.launch();
        break;
    case MAP_DONJON:
        donjon.launch();
        break;
    }
}

void MapController::handleActions(Action *action)
{
    switch (step)
    {
    case MAP_OVERWORLD:
        overworld.handleActions(action);
        break;
    case MAP_OCARINA:
        ocarina.handleActions(action);
        break;
    case MAP_DONJON:
        donjon.handleActions(action);
        break;
    }
}

void MapController::loop()
{
    switch (step)
    {
    case MAP_OVERWORLD:
        overworld.loop();
        break;
    case MAP_OCARINA:
        ocarina.loop();
        break;
    case MAP_DONJON:
        donjon.loop();
        break;
    }
}

void MapController::draw()
{
    switch (step)
    {
    case MAP_OVERWORLD:
        overworld.draw();
        break;
    case MAP_OCARINA:
        ocarina.draw();
        break;
    case MAP_DONJON:
        donjon.draw();
        break;
    }
}

void MapController::setStep(int mapId, bool withTp)
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    BoundingBox *bb = map->getBounds();
    if (mapId < 46 || (mapId == 46 && bb->getX() == 320 * 17 && bb->getY() == 240) || (mapId == 53 && bb->getX() == 320 * 9 && bb->getY() == 240 * 5))
    {
        step = withTp ? MAP_OCARINA : MAP_OVERWORLD;
    }
    else if (mapId == 156)
    {
        step = map->isIndoor() ? MAP_DONJON : withTp ? MAP_OCARINA
                                                     : MAP_OVERWORLD;
    }
    else
    {
        step = MAP_DONJON;
    }
}
