#include "FinalController.h"

FinalController::FinalController() {
}

FinalController::~FinalController() {
}

void FinalController::launch(int id) {
    final.init(id);
}

void FinalController::handleActions(Action* action) {
    final.handleActions(action);
}

void FinalController::loop() {
    final.loop();
}

void FinalController::draw() {
    final.draw();
}
