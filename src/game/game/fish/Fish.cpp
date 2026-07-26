#include "Fish.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

Fish::Fish() : page(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    for (int i = 0; i < 37; i++)
    {
        texts[i] = 0;
    }
}

Fish::~Fish()
{
    ResourceManager::getInstance()->free(image);
    for (int i = 0; i < 37; i++)
    {
        delete texts[i];
    }
}

void Fish::init()
{
    page = 0;
    if (isPageEmpty(page))
    {
        page = getNextPageFrom(page);
    }

    for (int i = 0; i < 37; i++)
    {
        delete texts[i];
    }

    for (int i = 0; i < 37; i++)
    {
        texts[i] = TextManager::getInstance()->getText(191 + i);
    }
}

void Fish::fish(int x, int y, int type)
{

    // cadre
    int categorie = type > 24 ? 2 : type > 14 ? 1
                                              : 0;
    int w = 32 + categorie * 8;
    WindowManager::getInstance()->draw(image, 48, categorie * 32, w, 32, x, y);

    // fish

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->getPoissons(type))
    {
        ItemHelper::getInstance()->drawItem((TypeItem)(TI_ECREVISSE + type), x + w / 2, y + 16);
    }
}

void Fish::cadre(int x, int y, int a, int b, int type)
{

    int w = 88;
    int h = 32;

    int letterSize = TextManager::getInstance()->getWSpace();
    Text *text = texts[6 + type];
    int size = text->getLength() * letterSize;

    while (size + 14 > w)
    {
        w += 8;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    if (!scene->getPoissons(type))
    {
        text = texts[36];
    }
    size = text->getLength() * letterSize;

    // center
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        for (int i = x + 16; i < x + w - 16; i += 16)
        {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    // top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    // left and right
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    // top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    // top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    // bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    // bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);

    text->display(x + w / 2 - size / 2 - 1, y + 8);
}

void Fish::handleActions(Action *action)
{
    if (action->isAction(POISSONS))
    {
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
    int old = page;
    if (action->isAction(PUSH_LEFT))
    {
        page = getPreviousPageFrom(page);
    }
    else if (action->isAction(PUSH_RIGHT))
    {
        page = getNextPageFrom(page);
    }
    if (page != old)
    {
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Fish::draw()
{
    int letterSize = TextManager::getInstance()->getWSpace();

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    // title

    Text *title = texts[page];
    int size = title->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++)
    {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    title->display(32 + 8 + ((blocs * 16) - size) / 2, 16);

    // fish

    switch (page)
    {
    case 0:
        // cadre(152,8,32,32,4);
        fish(16, 48, 0);
        cadre(64, 48, 88, 32, 0);
        fish(168, 48, 2);
        cadre(216, 48, 96, 32, 2);
        fish(16, 96, 14);
        cadre(64, 96, 88, 32, 14);
        fish(16, 144, 22);
        cadre(64, 144, 88, 32, 22);
        fish(168, 144, 24);
        cadre(216, 144, 88, 32, 24);
        break;
    case 1:
        fish(16, 48, 11);
        cadre(64, 48, 88, 32, 11);
        fish(168, 48, 7);
        cadre(216, 48, 96, 32, 7);
        fish(16, 144, 16);
        cadre(64, 144, 88, 32, 16);
        fish(168, 144, 19);
        cadre(216, 144, 88, 32, 19);
        fish(16, 192, 28);
        cadre(64 + 8, 192, 88, 32, 28);
        break;
    case 2:
        fish(16, 48, 3);
        cadre(64, 48, 88, 32, 3);
        fish(168, 48, 4);
        cadre(216, 48, 88, 32, 4);
        fish(16, 96, 10);
        cadre(64, 96, 88, 32, 10);
        fish(16, 144, 17);
        cadre(64, 144, 88, 32, 17);
        fish(168, 144, 21);
        cadre(216, 144, 88, 32, 21);
        fish(16, 192, 26);
        cadre(64 + 8, 192, 88, 32, 26);
        break;
    case 3:
        fish(16, 48, 8);
        cadre(64, 48, 88, 32, 8);
        fish(168, 48, 12);
        cadre(216, 48, 88, 32, 12);
        fish(16, 144, 20);
        cadre(64, 144, 88, 32, 20);
        fish(168, 144, 23);
        cadre(216, 144, 88, 32, 23);
        fish(16, 192, 29);
        cadre(64 + 8, 192, 88, 32, 29);
        break;
    case 4:
        fish(16, 48, 5);
        cadre(64, 48, 88, 32, 5);
        fish(168, 48, 9);
        cadre(216, 48, 88, 32, 9);
        fish(16, 96, 13);
        cadre(64, 96, 88, 32, 13);
        fish(16, 144, 15);
        cadre(64, 144, 88, 32, 15);
        fish(16, 192, 25);
        cadre(64 + 8, 192, 88, 32, 25);
        break;
    case 5:
        fish(16, 48, 1);
        cadre(64, 48, 88, 32, 1);
        fish(168, 48, 6);
        cadre(216, 48, 88, 32, 6);
        fish(16, 144, 18);
        cadre(64, 144, 88, 32, 18);
        fish(16, 192, 27);
        cadre(64 + 8, 192, 104, 32, 27);
        break;
    }
}

int Fish::getNextPageFrom(int p)
{
    int next = p + 1;

    for (int i = 0; i < 6; i++)
    {
        if (next > 5)
        {
            next = 0;
        }
        if (!isPageEmpty(next))
        {
            return next;
        }
        next++;
    }

    return p;
}

int Fish::getPreviousPageFrom(int p)
{
    int previous = p - 1;

    for (int i = 0; i < 6; i++)
    {
        if (previous < 0)
        {
            previous = 5;
        }
        if (!isPageEmpty(previous))
        {
            return previous;
        }
        previous--;
    }

    return p;
}

bool Fish::isPageEmpty(int p)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (p)
    {
    case 0:
        if (scene->getPoissons(0) || scene->getPoissons(2) || scene->getPoissons(14) || scene->getPoissons(22) || scene->getPoissons(24))
        {
            return false;
        }
        break;
    case 1:
        if (scene->getPoissons(11) || scene->getPoissons(7) || scene->getPoissons(16) || scene->getPoissons(19) || scene->getPoissons(28))
        {
            return false;
        }
        break;
    case 2:
        if (scene->getPoissons(3) || scene->getPoissons(4) || scene->getPoissons(10) || scene->getPoissons(17) || scene->getPoissons(21) || scene->getPoissons(26))
        {
            return false;
        }
        break;
    case 3:
        if (scene->getPoissons(8) || scene->getPoissons(12) || scene->getPoissons(20) || scene->getPoissons(23) || scene->getPoissons(29))
        {
            return false;
        }
        break;
    case 4:
        if (scene->getPoissons(5) || scene->getPoissons(9) || scene->getPoissons(13) || scene->getPoissons(15) || scene->getPoissons(25))
        {
            return false;
        }
        break;
    case 5:
        if (scene->getPoissons(1) || scene->getPoissons(6) || scene->getPoissons(18) || scene->getPoissons(27))
        {
            return false;
        }
        break;
    }
    return true;
}
