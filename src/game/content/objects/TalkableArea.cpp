#include "TalkableArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

TalkableArea::TalkableArea(int i, int j, int txt) : texte(txt)
{
    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

TalkableArea::~TalkableArea()
{
}

void TalkableArea::loop() {}

void TalkableArea::draw(int offsetX, int offsetY) {}

bool TalkableArea::action(Direction dir)
{
    int txt = getDynamicText();
    if (txt == -1)
        return false;
    MainController::getInstance()->getGameController()->displayText(txt);
    return true;
}

int TalkableArea::getDynamicText()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    switch (texte)
    {
    case 372:
        if (link->getStatus()->getMaxPieceOr() == 999)
        {
            return 285;
        }
        else if (link->getStatus()->getMaxPieceOr() == 500)
        {
            return 378;
        }
        else if (link->getStatus()->getMaxPieceOr() == 200)
        {
            return 375;
        }
        break;
    case 612:
        if (scene->getMap()->getId() == 102 && scene->getAvancement() < AV_DETTE_PAYEE)
        {
            if (scene->getAvancement() == AV_PARLE_GARS_MINE_SALOON)
            {
                return 777;
            }
            if (scene->getAvancement() >= AV_PARLE_BARMAN_SALOON)
            {
                if (link->getInventory()->getTroc(TT_ROC_GIVRE) < 1)
                {
                    return 783;
                }
                return 784;
            }
        }
        break;
    case 617:
    case 902:
    case 1006:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (!link->getInventory()->hasObject(ARC))
        {
            return 622;
        }
        if (link->getStatus()->getArrows() == link->getStatus()->getMaxArrows())
        {
            return 623;
        }
        break;
    case 619:
    case 904:
    case 1008:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (!link->getInventory()->hasObject(BOMBES))
        {
            return 621;
        }
        if (link->getStatus()->getBombs() == link->getStatus()->getMaxBombs())
        {
            return 623;
        }
        break;
    case 625:
    case 906:
    case 1010:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (link->getStatus()->getVirtualLife() == link->getStatus()->getMaxLife())
        {
            return 623;
        }
        break;
    case 627:
    case 629:
    case 908:
    case 910:
    case 1012:
    case 1014:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (!link->getInventory()->hasObject(LANTERNE) || link->getStatus()->getVirtualMagic() == link->getStatus()->getMaxMagic())
        {
            return 623;
        }
        break;
    case 638:
        if (link->getInventory()->hasObject(DETECTEUR))
            return -1;
        break;
    case 643:
        if (link->getInventory()->hasObject(FLACON_1))
        {
            texte = 646;
            return getDynamicText();
        }
        break;
    case 646:
        if (link->getInventory()->hasObject(FLACON_2))
            return -1;
        break;
    case 648:
        if (link->getInventory()->hasObject(BONUS_FORCE_1))
        {
            texte = 651;
            return getDynamicText();
        }
        break;
    case 651:
        if (link->getInventory()->hasObject(BONUS_FORCE_2))
            return -1;
        break;
    case 653:
        if (link->getInventory()->hasObject(BONUS_DEFENSE_1))
        {
            texte = 656;
            return getDynamicText();
        }
        break;
    case 656:
        if (link->getInventory()->hasObject(BONUS_DEFENSE_2))
            return -1;
        break;
    case 1027:
        if (scene->getMap()->getEpoque() == EP_PASSE && !link->getInventory()->hasObject(LIVRE))
        {
            return 561;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_GEMME && link->getInventory()->getCurrent() == TROC_GEMME_JAUNE)
        {
            return 1029;
        }
        if (link->getInventory()->hasObject(TROC_GEMME_JAUNE) && link->getInventory()->getTrocGemme(2) == TGJ_VIN)
        {
            return 1035;
        }
        break;
    case 1322:
    case 1323:
    case 1325:
        if (scene->getAvancement() >= AV_PASSAGE_TROUVE)
        {
            return -1;
        }
        break;
    case 1324:
        if (scene->getAvancement() == AV_RIDEAUX_REPERES)
        {
            return 1326;
        }
        if (scene->getAvancement() >= AV_PASSAGE_TROUVE)
        {
            return -1;
        }
        break;
    case 1425:
        if (scene->getMap()->getMur(69 * 16 + 8, 88 * 16 + 8) != MUR)
        {
            return 1424;
        }
        break;
    default:
        break;
    }
    return texte;
}
