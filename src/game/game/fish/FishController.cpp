#include "FishController.h"

FishController::FishController()
{
}

FishController::~FishController()
{
}

void FishController::launch()
{
    fish.init();
}

void FishController::handleActions(Action *action)
{
    fish.handleActions(action);
}

void FishController::loop()
{
}

void FishController::draw()
{
    fish.draw();
}
