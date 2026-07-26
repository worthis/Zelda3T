#include "TransitionTimesController.h"

TransitionTimesController::TransitionTimesController() {
}

TransitionTimesController::~TransitionTimesController() {
}

void TransitionTimesController::launch() {
    transitionTimes.init();
}

void TransitionTimesController::loop() {
    transitionTimes.loop();
}

void TransitionTimesController::draw() {
    transitionTimes.draw();
}

void TransitionTimesController::setSens(int s) {
    transitionTimes.setSens(s);
}
