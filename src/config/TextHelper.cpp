#include "TextHelper.h"

#include "../engine/resources/ResourceManager.h"

#include "../game/MainController.h"
#include "../game/keys/KeyBinder.h"

TextHelper::TextHelper()
{
    setWSpace(6);
    setWSize(8);
    setHSize(16);
    image = ResourceManager::getInstance()->loadImage("data/images/texts/font.png", true);
    setImage(image);
}

TextHelper::~TextHelper()
{
    ResourceManager::getInstance()->free(image);
}

void TextHelper::setLanguage(int i)
{
    switch (i)
    {
    case 0:
        setTextfile("data/texts/french.txt");
        break;
    case 1:
        setTextfile("data/texts/english.txt");
        break;
    case 2:
        setTextfile("data/texts/spanish.txt");
        break;
    default:
        setTextfile("data/texts/english.txt");
        break;
    }
}

string TextHelper::getVariableValue(int textId, int varId)
{
    ostringstream os;
    int tmp = 0;
    int tmp2 = 0;
    int tmp3 = 0;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    Inventory *inventory = link->getInventory();
    Status *status = link->getStatus();

    switch (textId)
    {
    case 101:
        tmp = 4 - inventory->nbQuartCoeur();
        os << tmp;
        return os.str();
    case 309:
    case 310:
        tmp = inventory->getTroc(TT_SAC_RIZ);
        os << tmp;
        return os.str();
    case 311:
    case 312:
        tmp = inventory->getTroc(TT_SAC_OLIVES);
        os << tmp;
        return os.str();
    case 313:
    case 314:
        tmp = inventory->getTroc(TT_BOCAL_EPICES);
        os << tmp;
        return os.str();
    case 315:
    case 316:
        tmp = inventory->getTroc(TT_PERLES);
        os << tmp;
        return os.str();
    case 317:
    case 318:
        tmp = inventory->getTroc(TT_PLUME);
        os << tmp;
        return os.str();
    case 319:
    case 320:
        tmp = inventory->getTroc(TT_POULET);
        os << tmp;
        return os.str();
    case 321:
    case 322:
        tmp = inventory->getTroc(TT_TAPISSERIE);
        os << tmp;
        return os.str();
    case 323:
    case 324:
        tmp = inventory->getTroc(TT_AMULETTE);
        os << tmp;
        return os.str();
    case 325:
    case 326:
        tmp = inventory->getTroc(TT_PARFUM);
        os << tmp;
        return os.str();
    case 327:
    case 328:
        tmp = inventory->getTroc(TT_ROC_MAGMA);
        os << tmp;
        return os.str();
    case 329:
    case 330:
        tmp = inventory->getTroc(TT_ROC_GIVRE);
        os << tmp;
        return os.str();
    case 331:
        tmp = inventory->getTroc(TT_POIVRON);
        os << tmp;
        return os.str();
    case 332:
        tmp = inventory->getTroc(TT_ROUAGE);
        os << tmp;
        return os.str();
    case 333:
        tmp = inventory->getTroc(TT_JAUGE);
        os << tmp;
        return os.str();
    case 334:
        tmp = inventory->getTroc(TT_ROUE);
        os << tmp;
        return os.str();
    case 335:
        tmp = inventory->getTroc(TT_SOURCE_NRJ);
        os << tmp;
        return os.str();
    case 415:
        tmp = 7 - inventory->nbCristaux();
        os << tmp;
        return os.str();
    case 683:
        tmp = (inventory->hasQuartCoeur(15) ? 0 : 1) + (inventory->hasGemmeForce(160) ? 0 : 1) + (inventory->hasGemmeForce(161) ? 0 : 1) + (inventory->hasGemmeForce(162) ? 0 : 1);
        if (varId == 2)
        {
            tmp = (4 - tmp + 1) * 5;
        }
        os << tmp;
        return os.str();
    case 731:
        tmp = 5 - scene->getTotalPoissons();
        os << tmp;
        return os.str();
    case 741:
        tmp = 5 - (scene->getTotalPoissons() % 5);
        os << tmp;
        return os.str();
    case 811:
    case 812:
        tmp = (status->getMaxRupees() - status->getVirtualRupees()) / 2;
        if (tmp > status->getVirtualGanonOr())
            tmp = status->getVirtualGanonOr();
        tmp2 = tmp * 2;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 817:
    case 818:
        tmp = (status->getMaxRupees() - status->getVirtualRupees()) / 4;
        if (tmp > status->getVirtualPieceOr())
            tmp = status->getVirtualPieceOr();
        tmp2 = tmp * 4;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 852:
        os << scene->getMonstersSolde() / 4;
        return os.str();
    case 853:
        os << scene->getMonstersSolde();
        return os.str();
    case 854:
        os << scene->getMonstersSolde() / 2;
        return os.str();
    case 862:
    case 863:
        tmp2 = link->getStatus()->getVirtualRupees() / 2;
        if (tmp2 > (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr()))
        {
            tmp2 = (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr());
        }
        tmp = tmp2 * 2;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 866:
    case 867:
        tmp = (status->getMaxGanonOr() - status->getVirtualGanonOr()) / 2;
        if (tmp > status->getVirtualPieceOr())
            tmp = status->getVirtualPieceOr();
        tmp2 = tmp * 2;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 960:
    case 961:
        tmp2 = link->getStatus()->getVirtualRupees() / 4;
        if (tmp2 > (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr()))
        {
            tmp2 = (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr());
        }
        tmp = tmp2 * 4;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 962:
    case 963:
        tmp2 = link->getStatus()->getVirtualGanonOr() / 2;
        if (tmp2 > (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr()))
        {
            tmp2 = (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr());
        }
        tmp = tmp2 * 2;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            os << tmp2;
        }
        else if (varId == 3)
        {
            tmp3 = 9;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            if (tmp2 < 100)
                tmp3++;
            if (tmp2 < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 1071:
    case 1072:
    case 1073:
        os << scene->getCoffre(0, 1);
        return os.str();
    case 1396:
    case 1397:
        tmp = status->getNbDeaths();
        os << tmp;
        return os.str();
    case 1398:
        tmp = inventory->totalQuartCoeur();
        os << tmp;
        return os.str();
    case 1399:
        tmp = inventory->totalGemmeForce();
        os << tmp;
        return os.str();
    case 1400:
        tmp = 14; // cristals + medaillons + swords
        for (int i = 0; i < NB_EQPMT; i++)
            if (inventory->hasObject((Equipment)i))
                tmp++;                 // 47 -> 61
        tmp += link->getBouclier();    // 4 -> 65
        tmp += link->getTunique() - 1; // 3 -> 68
        if (status->getMaxMagic() == 64)
            tmp++; // 1 -> 69
        for (int i = 1; i < 16; i++)
            for (int j = 0; j < 3; j++)
                if (scene->getCoffre(i, j))
                    tmp++; // 45 -> 114
        if (status->getMaxRupees() > 0)
            tmp++;
        if (status->getMaxRupees() > 99)
            tmp++;
        if (status->getMaxRupees() > 200)
            tmp++;
        if (status->getMaxRupees() > 500)
            tmp++;
        if (status->getMaxGanonOr() > 0)
            tmp++;
        if (status->getMaxGanonOr() > 99)
            tmp++;
        if (status->getMaxGanonOr() > 200)
            tmp++;
        if (status->getMaxGanonOr() > 500)
            tmp++;
        if (status->getMaxPieceOr() > 0)
            tmp++;
        if (status->getMaxPieceOr() > 99)
            tmp++;
        if (status->getMaxPieceOr() > 200)
            tmp++;
        if (status->getMaxPieceOr() > 500)
            tmp++;                                // 12 -> 126
        tmp += (status->getMaxArrows() - 30) / 5; // 8 -> 134
        tmp += (status->getMaxBombs() - 10) / 2;  // 10 -> 144
        os << tmp;
        return os.str();
    case 1401:
        for (int i = 0; i < NB_TROC; i++)
            if (inventory->getTroc(i) > -1)
                tmp++;
        for (int i = 0; i < NB_TROC_GEMME; i++)
            tmp += inventory->getTrocGemme(i);
        if (inventory->getTrocGemme(0) >= TGR_RIEN)
            tmp--;
        if (inventory->getTrocGemme(0) >= TGR_RIEN_2)
            tmp--;
        os << tmp;
        return os.str();
    case 1402:
        for (int i = 0; i < NB_POISSONS; i++)
            if (scene->getPoissons(i))
                tmp++;
        os << tmp;
        return os.str();
    case 1403:
        for (int i = 0; i < NB_MONSTERS; i++)
            if (scene->getMonsters(i))
                tmp++;
        os << tmp;
        return os.str();
    case 1404:
        tmp = MainController::getInstance()->getGameController()->getSave()->getCompletion();
        os << tmp;
        return os.str();
    case 1456:
    case 1457:
        tmp = scene->getMap()->getPriceCasino();
        os << tmp;
        return os.str();
    case 1481:
    case 1482:
        tmp = link->getStatus()->getNbDeaths() + 1;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            tmp3 = 5;
            if (tmp < 1000)
                tmp3++;
            if (tmp < 100)
                tmp3++;
            if (tmp < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 1483:
    case 1484:
        tmp = link->getStatus()->getNbDeaths();
        os << tmp;
        return os.str();
    case 1505:
    case 1506:
        tmp = scene->getCoffre(13, 18) + 1;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            tmp3 = 2;
            if (tmp < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    case 1577:
    case 1578:
        tmp = MainController::getInstance()->getGameController()->getTime() / 3600;
        if (varId == 1)
        {
            os << tmp;
        }
        else if (varId == 2)
        {
            tmp3 = 8;
            if (tmp < 10)
                tmp3++;
            for (int i = 0; i < tmp3; i++)
                os << " ";
        }
        return os.str();
    }
    return "";
}

string TextHelper::getCommonValue(string tag)
{
    if (tag == "EPEE")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_EPEE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "CARTE")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_CARTE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "ACTION")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_ACTION);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "MONSTERS")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_MONSTERS);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "TROC")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_TROC);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "POISSONS")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_POISSONS);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "COURSE")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_COURSE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "INVENTAIRE")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_INVENTAIRE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "OBJECT")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_OBJET);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "ONILINK")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_ONILINK);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "TELEPORT")
    {
        Text *tmp = JoystickBinder::getInstance()->getTextForType(BT_TELEPORT);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "center")
    {
        return "[center]";
    }
    else if (tag == "/center")
    {
        return "[/center]";
    }
    return "";
}
