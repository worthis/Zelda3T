#include "GenericController.h"

GenericController::GenericController() {
}

GenericController::~GenericController() {
}

void GenericController::setId(int id) {
    generic.setId(id);
}

void GenericController::draw() {
    generic.draw();
}
