#include "Generic.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"

Generic::Generic() {
    id = -1;
    image = 0;
}

Generic::~Generic() {
    ResourceManager::getInstance()->free(image);
}

void Generic::draw() {
    if (image != 0) WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);
}

void Generic::setId(int i) {
    if (id != i) {
        id = i;
        ResourceManager::getInstance()->free(image);
        if (i == 0) image = ResourceManager::getInstance()->loadImage("data/images/generics/present.png");
        if (i == 1) image = ResourceManager::getInstance()->loadImage("data/images/generics/passe.png");
    }
}
