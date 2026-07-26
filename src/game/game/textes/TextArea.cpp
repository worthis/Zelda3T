#include "TextArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

#include "../../content/link/Link.h"
#include "../../content/effects/Debris.h"

TextArea::TextArea() : step(TEXT_OFF), anim(0), animMax(0), vanim(40), ready(false), text(0), id(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/texts/cadre.png", true);
    imageCoeur = ResourceManager::getInstance()->loadImage("data/images/status/coeur.png", true);
}

TextArea::~TextArea() {
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageCoeur);
    delete text;
}

void TextArea::handleActions(Action* action) {
    if (action->isAction(ACTION)) {
        if (ready) {
            if (text->hasNext()) {
                text->next();
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            } else if (hasLogicalNext()) {
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            } else {
                stop();
                AudioManager::getInstance()->playSound(TS_TEXTEND);
            }
        } else {
            anim = animMax;
            ready = true;
        }
        return;
    }
    if (ready) {
        if (action->isAction(PUSH_UP)) {
            int newId = -1;
            switch (id) {
            case 97 : case 242 : case 663 : case 819 : case 868 : case 964 :
                    newId = id + 2;
                    break;
                case 98 : case 99 : case 241 : case 243 : case 244 : case 246 : case 247 : case 248 : case 664 : case 665 :
                case 767 : case 768 : case 769 : case 820 : case 821 : case 869 : case 870 : case 965 : case 966 :
                    newId = id - 1;
                    break;
                case 240 :
                    newId = id + 1;
                    break;
                case 245 : case 766 :
                    newId = id + 3;
                    break;
                default : break;
            }
            if (newId != -1) {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_DOWN)) {
            int newId = -1;
            switch (id) {
                case 97 : case 98 : case 240 : case 242 : case 243 : case 245 : case 246 : case 247 : case 663 : case 664 :
                case 766 : case 767 : case 768 : case 819 : case 820 : case 868 : case 869 : case 964 : case 965 :
                    newId = id + 1;
                    break;
                case 99 : case 286 : case 244 : case 665 : case 821 : case 870 : case 966 :
                    newId = id - 2;
                    break;
                case 241 :
                    newId = id - 1;
                    break;
                case 248 : case 769 :
                    newId = id - 3;
                    break;
                default : break;
            }
            if (newId != -1) {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_LEFT)) {
            int newId = -1;
            switch (id) {
                case 272 : case 280 : case 283 : case 286 : case 289 : case 292 : case 295 : case 299 : case 302 : case 305 :
                case 337 : case 340 : case 343 : case 346 : case 349 : case 352 : case 355 : case 358 : case 361 : case 372 :
                case 375 : case 378 : case 381 : case 384 : case 393 : case 404 : case 417 : case 423 : case 435 : case 440 :
                case 451 : case 454 : case 456 : case 458 : case 471 : case 473 : case 475 : case 477 : case 489 : case 503 :
                case 506 : case 509 : case 511 : case 517 : case 520 : case 530 : case 539 : case 550 : case 601 : case 606 :
                case 617 : case 619 : case 625 : case 627 : case 629 : case 635 : case 639 : case 643 : case 646 : case 648 :
                case 651 : case 653 : case 656 : case 666 : case 668 : case 675 : case 684 : case 698 : case 703 : case 714 :
                case 717 : case 720 : case 723 : case 726 : case 758 : case 778 : case 785 : case 811 : case 817 : case 825 :
                case 832 : case 837 : case 842 : case 855 : case 862 : case 866 : case 875 : case 902 : case 904 : case 906 :
                case 908 : case 910 : case 935 : case 937 : case 947 : case 960 : case 962 : case 978 : case 985 : case 991 :
                case 997 : case 1006 : case 1008 : case 1010 : case 1012 : case 1014 : case 1017 : case 1019 : case 1030 : case 1041 :
                case 1050 : case 1084 : case 1096 : case 1122 : case 1152 : case 1166 : case 1175 : case 1245 : case 1344 : case 1356 :
                case 1425 : case 1430 : case 1436 : case 1443 : case 1450 : case 1452 : case 1456 : case 1465 : case 1469 : case 1473 :
                case 1477 : case 1481 : case 1485 : case 1489 : case 1493 : case 1497 : case 1501 : case 1505 : case 1509 : case 1513 :
                case 1517 : case 1521 : case 1525 : case 1529 : case 1533 : case 1537 : case 1541 : case 1545 : case 1549 : case 1553 :
                case 1557 : case 1561 : case 1565 : case 1569 : case 1573 : case 1577 : case 1581 : case 1585 : case 1589 : case 1593 :
                case 1597 : case 1601 : case 1605 : case 1609 : case 1613 : case 1617 : case 1621 : case 1625 : case 1638 :
                    newId = id + 1;
                    break;
                case 273 : case 281 : case 284 : case 287 : case 290 : case 293 : case 296 : case 300 : case 303 : case 306 :
                case 338 : case 341 : case 344 : case 347 : case 350 : case 353 : case 356 : case 359 : case 362 : case 373 :
                case 376 : case 379 : case 382 : case 385 : case 394 : case 405 : case 418 : case 424 : case 436 : case 441 :
                case 452 : case 455 : case 457 : case 459 : case 472 : case 474 : case 476 : case 478 : case 490 : case 504 :
                case 507 : case 510 : case 512 : case 518 : case 521 : case 531 : case 540 : case 551 : case 602 : case 607 :
                case 618 : case 620 : case 626 : case 628 : case 630 : case 636 : case 640 : case 644 : case 647 : case 649 :
                case 652 : case 654 : case 657 : case 667 : case 669 : case 676 : case 685 : case 699 : case 704 : case 715 :
                case 718 : case 721 : case 724 : case 727 : case 759 : case 779 : case 786 : case 812 : case 818 : case 826 :
                case 833 : case 838 : case 843 : case 856 : case 863 : case 867 : case 876 : case 903 : case 905 : case 907 :
                case 909 : case 911 : case 936 : case 938 : case 948 : case 961 : case 963 : case 979 : case 986 : case 992 :
                case 998 : case 1007 : case 1009 : case 1011 : case 1013 : case 1015 : case 1018 : case 1020 : case 1031 : case 1042 :
                case 1051 : case 1085 : case 1097 : case 1123 : case 1153 : case 1167 : case 1176 : case 1246 : case 1345 : case 1357 :
                case 1426 : case 1431 : case 1437 : case 1444 : case 1451 : case 1453 : case 1457 : case 1466 : case 1470 : case 1474 :
                case 1478 : case 1482 : case 1486 : case 1490 : case 1494 : case 1498 : case 1502 : case 1506 : case 1510 : case 1514 :
                case 1518 : case 1522 : case 1526 : case 1530 : case 1534 : case 1538 : case 1542 : case 1546 : case 1550 : case 1554 :
                case 1558 : case 1562 : case 1566 : case 1570 : case 1574 : case 1578 : case 1582 : case 1586 : case 1590 : case 1594 :
                case 1598 : case 1602 : case 1606 : case 1610 : case 1614 : case 1618 : case 1622 : case 1626 : case 1639 :
                    newId = id - 1;
                    break;
                default : break;
            }
            if (newId != -1) {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_RIGHT)) {
            int newId = -1;
            switch (id) {
                case 272 : case 280 : case 283 : case 286 : case 289 : case 292 : case 295 : case 299 : case 302 : case 305 :
                case 337 : case 340 : case 343 : case 346 : case 349 : case 352 : case 355 : case 358 : case 361 : case 372 :
                case 375 : case 378 : case 381 : case 384 : case 393 : case 404 : case 417 : case 423 : case 435 : case 440 :
                case 451 : case 454 : case 456 : case 458 : case 471 : case 473 : case 475 : case 477 : case 489 : case 503 :
                case 506 : case 509 : case 511 : case 517 : case 520 : case 530 : case 539 : case 550 : case 601 : case 606 :
                case 617 : case 619 : case 625 : case 627 : case 629 : case 635 : case 639 : case 643 : case 646 : case 648 :
                case 651 : case 653 : case 656 : case 666 : case 668 : case 675 : case 684 : case 698 : case 703 : case 714 :
                case 717 : case 720 : case 723 : case 726 : case 758 : case 778 : case 785 : case 811 : case 817 : case 825 :
                case 832 : case 837 : case 842 : case 855 : case 862 : case 866 : case 875 : case 902 : case 904 : case 906 :
                case 908 : case 910 : case 935 : case 937 : case 947 : case 960 : case 962 : case 978 : case 985 : case 991 :
                case 997 : case 1006 : case 1008 : case 1010 : case 1012 : case 1014 : case 1017 : case 1019 : case 1030 : case 1041 :
                case 1050 : case 1084 : case 1096 : case 1122 : case 1152 : case 1166 : case 1175 : case 1245 : case 1344 : case 1356 :
                case 1425 : case 1430 : case 1436 : case 1443 : case 1450 : case 1452 : case 1456 : case 1465 : case 1469 : case 1473 :
                case 1477 : case 1481 : case 1485 : case 1489 : case 1493 : case 1497 : case 1501 : case 1505 : case 1509 : case 1513 :
                case 1517 : case 1521 : case 1525 : case 1529 : case 1533 : case 1537 : case 1541 : case 1545 : case 1549 : case 1553 :
                case 1557 : case 1561 : case 1565 : case 1569 : case 1573 : case 1577 : case 1581 : case 1585 : case 1589 : case 1593 :
                case 1597 : case 1601 : case 1605 : case 1609 : case 1613 : case 1617 : case 1621 : case 1625 : case 1638 :
                    newId = id + 1;
                    break;
                case 273 : case 281 : case 284 : case 287 : case 290 : case 293 : case 296 : case 300 : case 303 : case 306 :
                case 338 : case 341 : case 344 : case 347 : case 350 : case 353 : case 356 : case 359 : case 362 : case 373 :
                case 376 : case 379 : case 382 : case 385 : case 394 : case 405 : case 418 : case 424 : case 436 : case 441 :
                case 452 : case 455 : case 457 : case 459 : case 472 : case 474 : case 476 : case 478 : case 490 : case 504 :
                case 507 : case 510 : case 512 : case 518 : case 521 : case 531 : case 540 : case 551 : case 602 : case 607 :
                case 618 : case 620 : case 626 : case 628 : case 630 : case 636 : case 640 : case 644 : case 647 : case 649 :
                case 652 : case 654 : case 657 : case 667 : case 669 : case 676 : case 685 : case 699 : case 704 : case 715 :
                case 718 : case 721 : case 724 : case 727 : case 759 : case 779 : case 786 : case 812 : case 818 : case 826 :
                case 833 : case 838 : case 843 : case 856 : case 863 : case 867 : case 876 : case 903 : case 905 : case 907 :
                case 909 : case 911 : case 936 : case 938 : case 948 : case 961 : case 963 : case 979 : case 986 : case 992 :
                case 998 : case 1007 : case 1009 : case 1011 : case 1013 : case 1015 : case 1018 : case 1020 : case 1031 : case 1042 :
                case 1051 : case 1085 : case 1097 : case 1123 : case 1153 : case 1167 : case 1176 : case 1246 : case 1345 : case 1357 :
                case 1426 : case 1431 : case 1437 : case 1444 : case 1451 : case 1453 : case 1457 : case 1466 : case 1470 : case 1474 :
                case 1478 : case 1482 : case 1486 : case 1490 : case 1494 : case 1498 : case 1502 : case 1506 : case 1510 : case 1514 :
                case 1518 : case 1522 : case 1526 : case 1530 : case 1534 : case 1538 : case 1542 : case 1546 : case 1550 : case 1554 :
                case 1558 : case 1562 : case 1566 : case 1570 : case 1574 : case 1578 : case 1582 : case 1586 : case 1590 : case 1594 :
                case 1598 : case 1602 : case 1606 : case 1610 : case 1614 : case 1618 : case 1622 : case 1626 : case 1639 :
                    newId = id - 1;
                    break;
                default : break;
            }
            if (newId != -1) {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
    }
}

void TextArea::loop() {
    if (!ready) {
        if (chrono.getElapsedTime() >= vanim) {
            do {
                ready = (++anim == animMax);
            } while (!ready && text->charAtInBox(anim) == ' ');
            AudioManager::getInstance()->playSound(TS_TEXT, 1);
            chrono.reset();
        }
    }
}

void TextArea::draw() {
    WindowManager::getInstance()->draw(image, 0, 0, 8, 8, 8, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 24, 0, 8, 8, 16 * 19, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 0, 24, 8, 8, 8, 16 * 14);
    WindowManager::getInstance()->draw(image, 24, 24, 8, 8, 16 * 19, 16 * 14);

    for (int i = 16; i < 16 * 19; i += 16) {
        WindowManager::getInstance()->draw(image, 8, 0, 16, 8, i, 16 * 9 + 8);
        WindowManager::getInstance()->draw(image, 8, 24, 16, 8, i, 16 * 14);
    }

    for (int j = 16 * 10; j < 16 * 14; j += 16) {
        WindowManager::getInstance()->draw(image, 0, 8, 8, 16, 8, j);
        WindowManager::getInstance()->draw(image, 24, 8, 8, 16, 16 * 19, j);
    }

    text->displayBox(16, 16 * 10, anim);

    drawAdditionalContent();
}

void TextArea::start() {
    chrono.reset();
    anim = 0;
    animMax = text->getLengthInBox();
    ready = false;
}

void TextArea::stop() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map* map = scene->getMap();
    Link* link = scene->getLink();
    if (link->getAnimation() == TROUVE_SIMPLE || link->getAnimation() == TROUVE_DOUBLE) {
        link->setAnimation(IDLE);
    }
    //int tmp = 0;

    switch (id) {
        case 98 :
            MainController::getInstance()->getGameController()->saveData();
        case 99 :
            AudioManager::getInstance()->stopMusic();
            MainController::getInstance()->setStep(LOGO);
            return;
        case 160 : case 161 : case 162 : case 163 : case 164 : case 165 : case 166 :
        case 167 : case 168 : case 169 : case 170 : case 171 : case 172 : case 173 :
            link->getStatus()->updateLife(4);
            break;
        case 175 : case 176 : case 177 : case 178 : case 179 :
        case 180 : case 181 : case 182 : case 183 : case 184 :
            link->getStatus()->updateLife(8);
            break;
        case 185 : case 186 : case 187 : case 188 : case 189 :
            link->getStatus()->updateLife(6);
            break;
        case 235 :
            scene->setAvancement(AV_GARDE_VU);
            break;
        case 239 : case 241 : case 244 : case 248 :
            link->setAnimation(IDLE);
            break;
        case 245 :
            link->setAnimation(JOUE_OCARINA);
            MainController::getInstance()->getGameController()->getOcarinaController()->setSong(0);
            MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
            return;
        case 240 : case 242 : case 246 :
            link->setAnimation(JOUE_OCARINA);
            MainController::getInstance()->getGameController()->getOcarinaController()->setSong(1);
            MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
            return;
        case 243 : case 247 :
            link->setAnimation(JOUE_OCARINA);
            MainController::getInstance()->getGameController()->getOcarinaController()->setSong(2);
            MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
            return;
        case 253 :
            scene->setAvancement(AV_PONT_CONSTRUIT);
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, link->getX(), link->getY(), link->getDirection(), false, true);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            return;
        case 274 :
            link->trouveObjet(TI_BALAIS);
            return;
        case 280 :
            link->getInventory()->removeTroc(TT_POULET, 1);
            link->getStatus()->updateRupees(-100);
            link->trouveObjet(TI_ROUAGE);
            map->setSol(31*16, 31*16, 1960);
            return;
        case 283 :
            link->getInventory()->removeTroc(TT_ROC_MAGMA, 1);
            link->getInventory()->removeTroc(TT_ROC_GIVRE, 1);
            link->trouveObjet(TI_QUART_COEUR, map->getId() == 18 ? 2 : 4);
            if (map->getId() == 18) {
                map->setSol(31*16, 31*16, 1959);
            } else {
                map->setSol(31*16, 45*16, 549);
                map->setSol(31*16, 46*16, 2173);
            }
            return;
        case 286 :
            link->getInventory()->removeTroc(TT_PLUME, 1);
            link->getStatus()->updateRupees(-10);
            link->trouveObjet(TI_BOURSE_RUBIS_2);
            map->setSol(45*16, 31*16, 1963);
            return;
        case 289 :
            link->getInventory()->removeTroc(TT_TAPISSERIE, 1);
            link->getStatus()->updateRupees(-100);
            link->trouveObjet(TI_BOURSE_RUBIS_3);
            map->setSol(45*16, 31*16, 1964);
            return;
        case 292 :
            link->getInventory()->removeTroc(TT_AMULETTE, 1);
            link->getInventory()->removeTroc(TT_ROC_MAGMA, 1);
            link->getStatus()->updateRupees(-250);
            link->trouveObjet(TI_BOURSE_RUBIS_4);
            map->setSol(45*16, 31*16, 1959);
            return;
        case 295 :
            link->getInventory()->removeTroc(TT_SAC_RIZ, 2);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 3);
            link->trouveObjet(TI_POULET);
            return;
        case 299 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 2);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 2);
            link->trouveObjet(TI_PLUME);
            return;
        case 302 :
            link->getStatus()->updateRupees(-15);
            link->trouveObjet(TI_SAC_RIZ);
            return;
        case 304 :
            if (map->getId() == 57) scene->setCoffre(12, 12, 1);
            if (map->getId() == 87) scene->setCoffre(0, 16, 1);
            if (map->getId() == 90) {
                link->trouveObjet(TI_SAC_OLIVES);
                return;
            }
            if (map->getId() == 96) scene->setCoffre(0, 20, 1);
            if (map->getId() == 140) scene->setCoffre(0, 31, 1);
            break;
        case 305 :
            link->getStatus()->updateRupees(-10);
            link->trouveObjet(TI_SAC_OLIVES);
            return;
        case 307 :
            if (map->getId() == 57) scene->setCoffre(12, 13, 1);
            if (map->getId() == 87) scene->setCoffre(0, 17, 1);
            if (map->getId() == 96) scene->setCoffre(0, 22, 1);
            break;
        case 337 :
            link->getInventory()->removeTroc(TT_ROUE, 1);
            link->getInventory()->removeTroc(TT_JAUGE, 1);
            link->getInventory()->removeTroc(TT_SOURCE_NRJ, 1);
            link->getStatus()->updateGanonOr(-100);
            link->setLapin(false);
            link->trouveObjet(TI_PERLE_LUNE);
            map->setSol(31*16, 31*16, 2089);
            return;
        case 340 :
            link->getInventory()->removeTroc(TT_PERLES, 1);
            link->getStatus()->updateGanonOr(-10);
            link->trouveObjet(TI_BOURSE_GANON_OR_2);
            map->setSol(45*16, 31*16, 2092);
            return;
        case 343 :
            link->getInventory()->removeTroc(TT_AMULETTE, 1);
            link->getStatus()->updateGanonOr(-100);
            link->trouveObjet(TI_BOURSE_GANON_OR_3);
            map->setSol(45*16, 31*16, 2093);
            return;
        case 346 :
            link->getInventory()->removeTroc(TT_PARFUM, 1);
            link->getInventory()->removeTroc(TT_ROC_GIVRE, 1);
            link->getStatus()->updateGanonOr(-250);
            link->trouveObjet(TI_BOURSE_GANON_OR_4);
            map->setSol(45*16, 31*16, 2089);
            return;
        case 349 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 3);
            link->trouveObjet(TI_ROUE);
            map->setSol(31*16, 38*16, 2098);
            return;
        case 352 :
            link->getInventory()->removeTroc(TT_POIVRON, 1);
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 3);
            link->trouveObjet(TI_SAC_BOMBES);
            map->setSol(31*16, 38*16, 2089);
            return;
        case 355 :
            link->getInventory()->removeTroc(TT_TAPISSERIE, 1);
            link->getInventory()->removeTroc(TT_AMULETTE, 1);
            link->getInventory()->removeTroc(TT_PARFUM, 1);
            link->trouveObjet(TI_ROC_MAGMA);
            return;
        case 358 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 5);
            link->getStatus()->updateGanonOr(-5);
            link->trouveObjet(TI_PERLES);
            return;
        case 361 :
            link->getStatus()->updateGanonOr(-10);
            link->trouveObjet(TI_BOCAL_EPICES);
            return;
        case 363 :
            if (map->getId() == 83) scene->setCoffre(0, 15, 1);
            if (map->getId() == 88) scene->setCoffre(0, 18, 1);
            if (map->getId() == 96) scene->setCoffre(0, 21, 1);
            if (map->getId() == 104) scene->setCoffre(0, 23, 1);
            if (map->getId() == 140) scene->setCoffre(0, 30, 1);
            break;
        case 364 :
            link->getStatus()->updateGanonOr(-5);
            break;
        case 372 :
            link->getInventory()->removeTroc(TT_POULET, 1);
            link->getStatus()->updatePieceOr(-10);
            link->trouveObjet(TI_BOURSE_PIECE_OR_2);
            map->setSol(45*16, 31*16, 2177);
            map->setSol(45*16, 32*16, 2176);
            return;
        case 375 :
            link->getInventory()->removeTroc(TT_PARFUM, 1);
            link->getStatus()->updatePieceOr(-100);
            link->trouveObjet(TI_BOURSE_PIECE_OR_3);
            map->setSol(45*16, 31*16, 2179);
            map->setSol(45*16, 32*16, 2178);
            return;
        case 378 :
            link->getInventory()->removeTroc(TT_TAPISSERIE, 1);
            link->getInventory()->removeTroc(TT_ROC_MAGMA, 1);
            link->getStatus()->updatePieceOr(-250);
            link->trouveObjet(TI_BOURSE_PIECE_OR_4);
            map->setSol(45*16, 31*16, 549);
            map->setSol(45*16, 32*16, 2173);
            return;
        case 381 :
            link->getInventory()->removeTroc(TT_POULET, 1);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 2);
            link->trouveObjet(TI_AMULETTE);
            return;
        case 384 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 1);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 1);
            link->trouveObjet(TI_PLUME);
            return;
        case 395 :
            link->trouveObjet(TI_CONFITURE);
            return;
        case 404 :
            scene->setAvancement(AV_GARDES_F_ACHETES);
            link->getStatus()->updateGanonOr(-5);
            break;
        case 408 :
            scene->setAvancement(AV_NEIGE_STOPPEE);
            break;
        case 409 :
            scene->setAvancement(AV_TEMPLE_DEESSES_APPARU);
            MainController::getInstance()->getGameController()->getTransitionTimesController()->setSens(2);
            MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_TIME);
            return;
        case 417 :
            MainController::getInstance()->getGameController()->saveData();
            MainController::getInstance()->getGameController()->displayText(419);
            return;
        case 418 : case 419 :
            if (map->getId() == 137) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(137, 9 * 16 + 8, 72 * 16 + 8, N, false, true);
                MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                return;
            }
            break;
        case 426 :
            link->trouveObjet(TI_REC_DETTE);
            return;
        case 437 :
            link->trouveObjet(TI_MARTEAU_LOURD);
            return;
        case 438 :
            map->cachetteZora(false);
            break;
        case 439 : case 442 :
            map->cachetteZora(true);
            break;
        case 444 :
            scene->setAvancement(AV_PLANCHES_TROUVEES);
            break;
        case 449 :
            scene->setAvancement(AV_GANON_DISPARU);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            MainController::getInstance()->getGameController()->getTransitionTimesController()->setSens(4);
            MainController::getInstance()->getGameController()->setStep(GAME_SWITCH_TIME);
            return;
        case 451 :
            link->getInventory()->removeTroc(TT_PERLES, 2);
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 5);
            link->trouveObjet(TI_TAPISSERIE);
            return;
        case 454 :
            link->getInventory()->removeTroc(TT_POULET, 5);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 5);
            link->trouveObjet(TI_AMULETTE);
            return;
        case 456 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 2);
            link->getInventory()->removeTroc(TT_SAC_RIZ, 2);
            link->trouveObjet(TI_PERLES);
            return;
        case 458 :
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 1);
            link->getStatus()->updateRupees(-2);
            link->trouveObjet(TI_SAC_RIZ);
            return;
        case 471 :
            link->getInventory()->removeTroc(TT_PERLES, 2);
            link->trouveObjet(TI_GEMME_FORCE, 91);
            return;
        case 473 :
            link->getInventory()->removeTroc(TT_PLUME, 2);
            link->trouveObjet(TI_GEMME_FORCE, 92);
            return;
        case 475 :
            link->getInventory()->removeTroc(TT_POULET, 2);
            link->trouveObjet(TI_GEMME_FORCE, 93);
            map->setSol(61*16, 41*16, 549);
            map->setSol(61*16, 42*16, 2173);
            return;
        case 477 :
            link->getInventory()->removeTroc(TT_SAC_RIZ, 1);
            link->getInventory()->removeTroc(TT_SAC_OLIVES, 2);
            link->trouveObjet(TI_POULET);
            return;
        case 491 :
            if (scene->getAvancement() < AV_BARQUE_LOUEE) {
                link->getStatus()->updateRupees(-15);
                scene->setAvancement(AV_BARQUE_LOUEE);
            }
            break;
        case 503 :
            link->getInventory()->removeTroc(TT_TAPISSERIE, 1);
            link->getInventory()->removeTroc(TT_PARFUM, 1);
            link->trouveObjet(TI_BOTTES);
            map->setSol(33*16, 35*16, 2772);
            return;
        case 506 :
            link->getInventory()->removeTroc(TT_PLUME, 3);
            link->getInventory()->removeTroc(TT_SAC_RIZ, 4);
            link->trouveObjet(TI_PARFUM);
            return;
        case 509 :
        link->getStatus()->updateRupees(-15);
            link->trouveObjet(TI_SAC_OLIVES);
            return;
        case 511 :
            link->getStatus()->updateRupees(-20);
            link->trouveObjet(TI_BOCAL_EPICES);
            return;
        case 517 :
            link->getInventory()->removeTroc(TT_TAPISSERIE, 1);
            link->getInventory()->removeTroc(TT_AMULETTE, 1);
            link->getInventory()->removeTroc(TT_PARFUM, 1);
            link->trouveObjet(TI_ROC_GIVRE);
            return;
        case 520 :
            link->getInventory()->removeTroc(TT_BOCAL_EPICES, 1);
            link->getInventory()->removeTroc(TT_SAC_RIZ, 1);
            link->trouveObjet(TI_PERLES);
            return;
        case 532 :
            link->trouveObjet(TI_POUDRE_OR);
            return;
        case 541 :
            link->trouveObjet(TI_ENCLUME);
            return;
        case 552 :
            link->trouveObjet(TI_HACHE);
            return;
        case 561 :
            if (map->getId() == 64) {
                if (scene->getAvancement() < AV_STELE_LUE) {
                    scene->setAvancement(AV_STELE_LUE);
                }  else if (scene->getAvancement() == AV_ZELDA_POUSSEE) {
                    scene->setAvancement(AV_PORTAIL_F_OUVERT);
                    map->ouvrePorte(9, 3, 0);
                    map->removeStele();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                }
            }
            break;
        case 567 :
            link->trouveObjet(TI_CARTE);
            return;
        case 572 :
            link->trouveObjet(TI_EPEE_2);
            return;
        case 575 :
            if (scene->getAvancement() < AV_ZELDA_POUSSEE) {
                scene->setAvancement(AV_ZELDA_POUSSEE);
            }
            break;
        case 578 :
            link->trouveObjet(TI_BOUCLIER_2);
            return;
        case 580 :
            link->getStatus()->updateLife(link->getStatus()->getMaxLife() - link->getStatus()->getVirtualLife());
            break;
        case 581 :
            scene->setCoffre(0, 8, 1);
            break;
        case 582 :
            scene->setCoffre(0, 9, 1);
            break;
        case 583 :
            scene->setCoffre(0, 10, 1);
            break;
        case 585 :
            if (scene->getAvancement() < AV_PANCARTE_MINE_LUE) {
                scene->setAvancement(AV_PANCARTE_MINE_LUE);
            }
            break;
        case 587 :
            if (scene->getAvancement() < AV_PARLE_GARS_MINE_MINE) {
                scene->setAvancement(AV_PARLE_GARS_MINE_MINE);
            }
            break;
        case 589 :
            scene->setAvancement(AV_PORTAIL_PRE_PRESENT_OUVERT);
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            map->ouvrePorte(9, 3, 0);
            break;
        case 598 :
            scene->setAvancement(AV_PORTAIL_PRE_PRESENT_FERME);
            map->ouvrePorte(9, 3, 1);
            break;
        case 601 :
            link->getStatus()->updateGanonOr(-100);
            AudioManager::getInstance()->playSound(TS_HAPPY, 2);
            if (link->getStatus()->getMaxBombs() < 30 && link->getInventory()->hasObject(BOMBES)
                && (link->getStatus()->getMaxArrows() == 70 || (int)(rand() % 2) == 1)) {
                link->getStatus()->setMaxBombs(link->getStatus()->getMaxBombs() + 2);
                link->getStatus()->setBombs(link->getStatus()->getMaxBombs());
                MainController::getInstance()->getGameController()->displayText(605);
            } else {
                link->getStatus()->setMaxArrows(link->getStatus()->getMaxArrows() + 5);
                link->getStatus()->setArrows(link->getStatus()->getMaxArrows());
                MainController::getInstance()->getGameController()->displayText(604);
            }
            return;
        case 606 :
            link->getStatus()->updateGanonOr(-999);
            AudioManager::getInstance()->playSound(TS_HAPPY, 2);
            if (!link->getInventory()->hasObject(RECUP_BOMBE) && (link->getInventory()->hasObject(RECUP_FLECHE) || (int)(rand() % 2) == 1)) {
                link->getInventory()->setObject(RECUP_BOMBE);
                link->getStatus()->setBombs(link->getStatus()->getMaxBombs());
                MainController::getInstance()->getGameController()->displayText(609);
            } else {
                link->getInventory()->setObject(RECUP_FLECHE);
                link->getStatus()->setArrows(link->getStatus()->getMaxArrows());
                MainController::getInstance()->getGameController()->displayText(608);
            }
            return;
        case 610 :
            AudioManager::getInstance()->playSound(TS_HAPPY, 2);
            link->getStatus()->setMaxMagic(64);
            link->getStatus()->setMagic(64);
            MainController::getInstance()->getGameController()->displayText(611);
            return;
        case 617 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateRupees(-20);
            link->getStatus()->setArrows(link->getStatus()->getArrows() + 10);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 619 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateRupees(-30);
            link->getStatus()->setBombs(link->getStatus()->getBombs() + 5);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 625 :
            link->getStatus()->updateRupees(-5);
            link->getStatus()->updateLife(2);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 627 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateRupees(-15);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 8);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 629 :
            AudioManager::getInstance()->playSound(TS_MAGICCHARGE, 2);
            link->getStatus()->updateRupees(-25);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 4);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 635 :
            link->getInventory()->removeGemme(30);
            link->trouveObjet(TI_ROC_GIVRE);
            return;
        case 639 :
            link->getInventory()->removeGemme(20);
            link->trouveObjet(TI_DETECTEUR);
            map->setSol(14*16, 5*16, 3317);
            return;
        case 643 :
            link->getInventory()->removeGemme(10);
            link->trouveObjet(TI_FLACON_1);
            return;
        case 646 :
            link->getInventory()->removeGemme(20);
            link->trouveObjet(TI_FLACON_2);
            map->setSol(5*16, 5*16, 3317);
            return;
        case 648 :
            link->getInventory()->removeGemme(20);
            link->trouveObjet(TI_BONUS_FORCE_1);
            return;
        case 651 :
            link->getInventory()->removeGemme(40);
            link->trouveObjet(TI_BONUS_FORCE_2);
            map->setSol(8*16, 5*16, 3317);
            return;
        case 653 :
            link->getInventory()->removeGemme(20);
            link->trouveObjet(TI_BONUS_DEFENSE_1);
            return;
        case 656 :
            link->getInventory()->removeGemme(40);
            link->trouveObjet(TI_BONUS_DEFENSE_2);
            map->setSol(11*16, 5*16, 3317);
            return;
        case 666 :
            link->getStatus()->updateRupees(-60);
            link->trouveObjet(TI_POTION_ROUGE);
            return;
        case 668 :
            link->getStatus()->updateRupees(-40);
            link->trouveObjet(TI_POTION_VERTE);
            return;
        case 678 :
            link->trouveObjet(TI_RIEN);
            return;
        case 684 :
            link->getStatus()->updateRupees(-(4 - ((link->getInventory()->hasQuartCoeur(15) ? 0 : 1) + (link->getInventory()->hasGemmeForce(160) ? 0 : 1)
                + (link->getInventory()->hasGemmeForce(161) ? 0 : 1) + (link->getInventory()->hasGemmeForce(162) ? 0 : 1)) + 1) * 5);
            map->closeChests();
            break;
        case 694 :
            link->getInventory()->setObject(SAC_TROC);
            link->trouveObjet(TI_SAC_RIZ);
            return;
        case 696 :
            AudioManager::getInstance()->playSound(TS_HITENNEMY);
            link->getInventory()->removeTroc(TT_ROUAGE, 1);
            map->switchLevier();
            break;
        case 698 :
            link->getStatus()->updateRupees(-160);
            link->trouveObjet(TI_POTION_BLEUE);
            return;
        case 705 :
            link->trouveObjet(TI_CARTE_VOYAGE);
            return;
        case 706 : case 708 :
            link->getStatus()->updateRupees(-5);
            break;
        case 716 : link->getStatus()->updateRupees(-5);
        case 719 : link->getStatus()->updateRupees(-3);
        case 722 : link->getStatus()->updateRupees(-1);
        case 725 : link->getStatus()->updateRupees(-1);
        case 728 :
            link->trouveObjet(TI_CANNE_A_PECHE_1);
            return;
        case 740 :
            link->getInventory()->setObject(ENCYCLOPEDIE_POISSONS);
            break;
        case 742 :
            link->trouveObjet(TI_CANNE_A_PECHE_2);
            return;
        case 744 :
            link->trouveObjet(TI_FLACON_3);
            return;
        case 745 :
            link->trouveObjet(TI_CANNE_A_PECHE_3);
            return;
        case 747 :
            link->trouveObjet(TI_QUART_COEUR, 14);
            return;
        case 750 :
            scene->setCoffre(0, 19, 1);
            break;
        case 761 :
            link->trouveObjet(TI_VIEILLE_BOTTE);
            return;
        case 782 :
            scene->setAvancement(AV_PARLE_BARMAN_SALOON);
            break;
        case 788 :
            scene->setAvancement(AV_DETTE_PAYEE);
            link->getInventory()->removeTroc(TT_ROC_GIVRE, 1);
            break;
        case 792 :
            if (scene->getAvancement() < AV_PARLE_GARS_MINE_SALOON) {
                scene->setAvancement(AV_PARLE_GARS_MINE_SALOON);
            }
            break;
        case 794 :
            scene->setAvancement(AV_APPREND_POUR_ROC_GIVRE);
            break;
        case 798 :
            if (scene->getAvancement() < AV_GARS_MINE_AIDE) {
                scene->setAvancement(AV_GARS_MINE_AIDE);
            }
            break;
        case 827 :
            link->trouveObjet(TI_FLECHE_FEU);
            link->getInventory()->setTrocGemme(0, TGR_FINI);
            return;
        case 834 :
            link->trouveObjet(TI_FLECHE_GLACE);
            link->getInventory()->setTrocGemme(1, TGB_FINI);
            return;
        case 839 :
            link->trouveObjet(TI_FLECHE_LUMIERE);
            link->getInventory()->setTrocGemme(2, TGJ_FINI);
            return;
        case 844 :
            link->trouveObjet(TI_FLACON_4);
            link->getInventory()->setTrocGemme(3, TGV_FINI);
            return;
        case 855 :
            scene->payForMonsters();
            break;
        case 877 :
            link->trouveObjet(TI_PLAN);
            return;
        case 883 :
            link->trouveObjet(TI_POIVRON);
            return;
        case 894 :
            link->trouveObjet(TI_GRAPPIN);
            return;
        case 899 :
            if (scene->getAvancement() < AV_SAGES_GROTTE) {
                scene->setAvancement(AV_SAGES_GROTTE);
            }
            break;
        case 902 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateGanonOr(-10);
            link->getStatus()->setArrows(link->getStatus()->getArrows() + 10);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 904 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateGanonOr(-15);
            link->getStatus()->setBombs(link->getStatus()->getBombs() + 5);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 906 :
            link->getStatus()->updateGanonOr(-4);
            link->getStatus()->updateLife(2);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 908 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updateGanonOr(-8);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 8);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 910 :
            AudioManager::getInstance()->playSound(TS_MAGICCHARGE, 2);
            link->getStatus()->updateGanonOr(-16);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 4);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 915 :
            if (scene->getCoffre(0, 26) == 0) {
                scene->setCoffre(0, 26, 1);
            }
            if (scene->getCoffre(0, 27) == 0) {
                scene->setCoffre(0, 27, 240+scene->getCoffre(0, 26)*240*7);
            }
            break;
        case 916 : case 917 : case 918 : case 919 : case 920 : case 921 : case 922 : case 923 : case 924 :
        case 925 : case 926 : case 927 : case 928 : case 929 : case 930 : case 931 : case 932 :
            link->getStatus()->updateGanonOr(25);
            scene->setCoffre(0, 26, scene->getCoffre(0, 26) + 1);
            scene->setCoffre(0, 27, 0);
            map->setAir(13*16,5*16,3329);
            map->pnjBoitCafe(false);
            if (scene->getCoffre(0, 26) < 18) {
                scene->setCoffre(0, 27, 240+scene->getCoffre(0, 26)*240*7); // 1s + 7s par cafe: 8s -> 120s
            }
            break;
        case 933 :
            link->trouveObjet(TI_GEMME_FORCE, 173);
            return;
        case 934 :
            link->getStatus()->updateGanonOr(5);
            break;
        case 935 :
            link->getStatus()->updateGanonOr(-40);
            link->trouveObjet(TI_POTION_ROUGE);
            return;
        case 937 :
            link->getStatus()->updateGanonOr(-25);
            link->trouveObjet(TI_POTION_VERTE);
            return;
        case 941 :
            link->trouveObjet(TI_BIJOU);
            return;
        case 949 :
            link->trouveObjet(TI_CROISSANT);
            return;
        case 954 :
            link->trouveObjet(TI_BOURSE_GANON_OR_1);
            return;
        case 973 :
            scene->setCoffre(0, 28, 1);
            break;
        case 980 :
            link->trouveObjet(TI_FER_CHEVAL);
            return;
        case 987 :
            link->trouveObjet(TI_CLOCHE);
            return;
        case 993 :
            link->trouveObjet(TI_MIROIR);
            return;
        case 1001 :
            link->setEpee(0);
            break;
        case 1003 :
            link->trouveObjet(TI_EPEE_3);
            return;
        case 1006 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updatePieceOr(-5);
            link->getStatus()->setArrows(link->getStatus()->getArrows() + 10);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 1008 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updatePieceOr(-10);
            link->getStatus()->setBombs(link->getStatus()->getBombs() + 5);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 1010 :
            link->getStatus()->updatePieceOr(-1);
            link->getStatus()->updateLife(2);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 1012 :
            AudioManager::getInstance()->playSound(TS_ITEM, 2);
            link->getStatus()->updatePieceOr(-3);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 8);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 1014 :
            AudioManager::getInstance()->playSound(TS_MAGICCHARGE, 2);
            link->getStatus()->updatePieceOr(-6);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 4);
            MainController::getInstance()->getGameController()->displayText(624);
            return;
        case 1017 :
            link->getStatus()->updatePieceOr(-15);
            link->trouveObjet(TI_POTION_ROUGE);
            return;
        case 1019 :
            link->getStatus()->updatePieceOr(-10);
            link->trouveObjet(TI_POTION_VERTE);
            return;
        case 1021 :
            link->trouveObjet(TI_BOURSE_PIECE_OR_1);
            return;
        case 1032 :
            link->trouveObjet(TI_VIN);
            map->setSol(5*16, 3*16, 1, 1, 3340, BOIS);
            return;
        case 1043 :
            link->trouveObjet(TI_BIERE);
            return;
        case 1067 :
            scene->setAvancement(AV_GANON_CAPTURE);
            break;
        case 1076 :
            link->trouveObjet(TI_GEMME_FORCE, 178);
            return;
        case 1086 :
            link->trouveObjet(TI_CORDE);
            return;
        case 1098 :
            link->trouveObjet(TI_RIEN_2);
            return;
        case 1119 :
            link->trouveObjet(TI_GEMME_FORCE, 182);
            return;
        case 1124 :
            link->trouveObjet(TI_LETTRE);
            return;
        case 1130 :
            if (scene->getCoffre(0, 32) == 0) {
                scene->setCoffre(0, 32, 1);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(18, 36, 1);
            }
            break;
        case 1133 :
            if (scene->getCoffre(0, 32) == 1) {
                scene->setCoffre(0, 32, 2);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(98, 21, 1);
            }
            break;
        case 1134 :
            if (scene->getCoffre(0, 32) == 2) {
                scene->setCoffre(0, 32, 3);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(78, 36, 1);
            }
            break;
        case 1136 :
            if (scene->getCoffre(0, 32) == 3) {
                scene->setCoffre(0, 32, 4);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(38, 21, 1);
            }
            break;
        case 1137 :
            if (scene->getCoffre(0, 32) == 4) {
                scene->setCoffre(0, 32, 5);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(98, 36, 1);
            }
            break;
        case 1139 :
            if (scene->getCoffre(0, 32) == 5) {
                scene->setCoffre(0, 32, 6);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(18, 21, 1);
            }
            break;
        case 1141 :
            if (scene->getCoffre(0, 32) == 6) {
                scene->setCoffre(0, 32, 7);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(78, 21, 1);
            }
            break;
        case 1142 :
            if (scene->getCoffre(0, 32) == 7) {
                scene->setCoffre(0, 32, 8);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(38, 36, 1);
            }
            break;
        case 1143 :
            if (scene->getCoffre(0, 32) == 8) {
                scene->setCoffre(0, 32, 9);
            }
            break;
        case 1145 :
            if (scene->getCoffre(0, 32) == 9) {
                scene->setCoffre(0, 32, 10);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(158, 21, 3);
            }
            break;
        case 1147 :
            if (scene->getCoffre(0, 32) == 10) {
                scene->setCoffre(0, 32, 11);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(149, 28, 2);
            }
            break;
        case 1149 :
            if (scene->getCoffre(0, 32) == 11) {
                scene->setCoffre(0, 32, 12);
                AudioManager::getInstance()->playSound(TS_DOOR, 2);
                map->ouvrePorte(209, 13, 2);
            }
            break;
        case 1155 :
            link->trouveObjet(TI_SCIE);
            return;
        case 1159 :
            link->setAnimation(JOUE_OCARINA);
            if (map->getEpoque() == EP_PRESENT) MainController::getInstance()->getGameController()->getOcarinaController()->setSong(0);
            else if (map->getEpoque() == EP_PASSE) MainController::getInstance()->getGameController()->getOcarinaController()->setSong(2);
            else MainController::getInstance()->getGameController()->getOcarinaController()->setSong(1);
            MainController::getInstance()->getGameController()->setStep(GAME_OCARINA);
            return;
        case 1160 : case 1161 : case 1162 :
            map->removeStele();
            break;
        case 1169 :
            link->trouveObjet(TI_ALLIANCE);
            return;
        case 1177 :
            link->trouveObjet(TI_CRANE);
            return;
        case 1187 :
            if (scene->getAvancement() < AV_MOT_DE_PASSE_DONNE) {
                scene->setAvancement(AV_MOT_DE_PASSE_DONNE);
            }
            break;
        case 1188 :
            scene->setAvancement(AV_MULTIPASSE_UTILISE);
            break;
        case 1195 :
            if (scene->getAvancement() < AV_MOT_DE_PASSE_CONNU) {
                scene->setAvancement(AV_MOT_DE_PASSE_CONNU);
            }
            break;
        case 1198 :
            if (scene->getAvancement() < AV_MULTIPASS) {
                scene->setAvancement(AV_MULTIPASS);
            }
            break;
        case 1201 :
            link->trouveObjet(TI_CLOU);
            return;
        case 1224 : // Coeur
            scene->getMap()->testAnimRoom();
            break;
        case 1245 :
            if (map->getId() == 46) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, 84 * 16, 8 * 16, S, false, true);
            else if (map->getId() == 47) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, 72 * 16 + 8, 42 * 16, S, false, true);
            else if (map->getId() == 48) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(30, 122 * 16, 36 * 16, S, false, true);
            else if (map->getId() == 49) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(41, 72 * 16 + 8, 44 * 16, S, false, true);
            else if (map->getId() == 50) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(42, 15 * 16 + 8, 22 * 16, S, false, true);
            else if (map->getId() == 51) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(27, 15 * 16 + 8, 22 * 16, S, false, true);
            else if (map->getId() == 52) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, 15 * 16 + 8, 22 * 16, S, false, true);
            else if (map->getId() == 53) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 84 * 16, 8 * 16, S, false, true);
            else if (map->getId() == 54) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 72 * 16 + 8, 52 * 16 + 8, S, false, true);
            else if (map->getId() == 55) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, 122 * 16, 35 * 16, S, false, true);
            else if (map->getId() == 58) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(44, 34 * 16 + 8, 25 * 16, S, false, true);
            else if (map->getId() == 59) MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(45, 108 * 16 + 8, 4 * 16, S, false, true);
            else break;
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            return;
        case 1256 :
            link->setTunique(2);
            break;
        case 1276 :
            scene->setAvancement(AV_SPEECH_AGAHNIM);
            break;
        case 1278 :
            scene->setCoffre(11, 20, 1);
            scene->getAnimationInGame()->startAnim(12);
            break;
        case 1294 :
            link->trouveObjet(TI_EPEE_5);
            return;
        case 1295 :
            link->trouveObjet(TI_ARC_OR);
            return;
        case 1296 :
            MainController::getInstance()->getGameController()->displayText(1297);
            return;
        case 1297 :
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(19, 39 * 16 + 8, 45 * 16 + 8, N, false, true);
            return;
        case 1299 :
            scene->setAvancement(AV_TELE_ZELDA);
            break;
        case 1302 :
            scene->setAvancement(AV_PARLE_GARDE_PALAIS);
            break;
        case 1304 :
            scene->setAvancement(AV_PARLE_GARDE_RESERVE);
            break;
        case 1309 :
            if (scene->getAvancement() < AV_RESERVE_VIDE) {
                scene->setAvancement(AV_RESERVE_VIDE);
            }
            break;
        case 1315 :
            if (scene->getAvancement() < AV_PARLE_ZELDA_PALAIS) {
                scene->setAvancement(AV_PARLE_ZELDA_PALAIS);
            }
            break;
        case 1316 :
            scene->setAvancement(AV_PARLE_GARDE_CH_FORTE);
            break;
        case 1318 :
            scene->setAvancement(AV_PARLE_GARDE_SOUS_SOL);
            break;
        case 1324 :
            scene->setAvancement(AV_RIDEAUX_REPERES);
            break;
        case 1326 :
            scene->setAvancement(AV_PASSAGE_TROUVE);
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            map->ouvrePorte(109, 163, 2);
            MainController::getInstance()->getGameController()->displayText(1327);
            return;
        case 1344 :
            link->getStatus()->updateLife(2);
            link->getStatus()->updateIvre(128);
            break;
        case 1359 :
            link->trouveObjet(TI_CUILLERE);
            map->setSol(62*16, 5*16, 6225);
            map->setSol(63*16, 5*16, 6226);
            return;
        case 1365 :
            AudioManager::getInstance()->playSound(TS_HAPPY);
            scene->setCoffre(12, 14, 1);
            MainController::getInstance()->getGameController()->displayText(1366);
            return;
        case 1371 :
            scene->setAvancement(AV_SPEECH_GANON);
            break;
        case 1381 :
            scene->setAvancement(AV_SPEECH_GANONDORF);
        case 1384 :
            AudioManager::getInstance()->playSound(TS_DOOR);
            map->fermePorte(169, 13, 0);
            AudioManager::getInstance()->playMusic(100);
            break;
        case 1363 :
            link->setTunique(3);
            break;
        case 1382 :
            MainController::getInstance()->getGameController()->saveData(true);
            MainController::getInstance()->getEndingController()->setId(0);
            MainController::getInstance()->setStep(ENDING);
            return;
        case 1385 :
            scene->setAvancement(AV_RETOUR_PRESENT);
            scene->instantTeleport(57, 69 * 16 + 8, 25 * 16 + 8, N);
            MainController::getInstance()->getGameController()->hideGeneric();
            return;
        case 1386 :
            scene->setAvancement(AV_ARRIVE_PASSE);
            scene->instantTeleport(9, 51 * 16 + 8, 42 * 16 + 8, N);
            MainController::getInstance()->getGameController()->hideGeneric();
            return;
        case 1391 :
            scene->setCoffre(12, 16, 1);
            break;
        case 1392 :
            scene->setCoffre(12, 17, 1);
            break;
        case 1393 :
            scene->setCoffre(12, 15, 1);
            break;
        case 1424 :
            if (map->getMur(69*16+8, 88*16+8) == MUR) {
                link->getStatus()->updateGanonOr(-10);
                AudioManager::getInstance()->playSound(TS_DOOR);
                map->ouvrePorte(69, 88, 0);
                scene->getHud()->displayCasino();
            }
            break;
        case 1433 :
            link->getStatus()->updateGanonOr(-5);
            break;
        case 1436 :
            link->getStatus()->updateGanonOr(-10);
            map->startJeuCasino();
            break;
        case 1439 :
            map->recompenseJeuCasino();
            return;
        case 1440 :
            if (map->getBounds()->getX() == 320 * 5 && map->getBounds()->getY() == 240 * 4 && link->getStatus()->getVirtualGanonOr() <= 0) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(58, 69 * 16 + 8, 102 * 16, N, false, true);
                MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                AudioManager::getInstance()->playSound(TS_TELEPORT);
                return;
            }
            break;
        case 1443 :
            link->getStatus()->updateGanonOr(-5);
            map->startJeuCasino();
            break;
        case 1452 :
            map->choixCasinoUn(true);
            map->startJeuCasino();
            break;
        case 1453 :
            map->choixCasinoUn(false);
            map->startJeuCasino();
            break;
        case 1456 :
            link->getStatus()->updateGanonOr(-map->getPriceCasino());
            map->recompenseJeuCasino();
            return;
        case 1468 : case 1472 : case 1476 : case 1480 : case 1484 : case 1488 : case 1492 : case 1496 : case 1500 : case 1504 :
        case 1508 : case 1512 : case 1516 : case 1520 : case 1524 : case 1528 : case 1532 : case 1536 : case 1540 : case 1544 :
        case 1548 : case 1552 : case 1556 : case 1560 : case 1564 : case 1568 : case 1572 : case 1576 : case 1580 : case 1584 :
        case 1588 : case 1592 : case 1596 : case 1600 : case 1604 : case 1608 : case 1612 : case 1616 : case 1620 : case 1624 :
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(58, 69 * 16 + 8, 102 * 16, N, false, true);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            AudioManager::getInstance()->playSound(TS_TELEPORT);
            return;
        case 1625 : case 1626 :
            scene->getMap()->testDegat(scene->getMap()->getBounds(), N, 1, TA_PHYSIC, TE_MORT, true);
            break;
        case 1632 :
            link->setTunique(4);
            break;
        case 1643 :
            if (map->getMur(69*16+8, 133*16+8) == MUR) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                map->ouvrePorte(69, 133, 0);
                scene->getMap()->startDestFinal();
                scene->getHud()->displayDestFinal();
            }
            break;
        case 1646 :
            AudioManager::getInstance()->playSound(TS_DOOR);
            if (map->getBounds()->getX() == 0) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                map->ouvrePorte(9, 88, 0);
                scene->setCoffre(15, 13, 1);
            } else if (map->getBounds()->getX() == 320) {
                map->ouvrePorte(29, 88, 0);
                scene->setCoffre(15, 14, 1);
            } else if (map->getBounds()->getX() == 320 * 2) {
                map->ouvrePorte(49, 88, 0);
                scene->setCoffre(15, 15, 1);
            } else if (map->getBounds()->getX() == 320 * 3 && map->getBounds()->getY() == 240) {
                map->ouvrePorte(69, 13, 0);
                scene->setCoffre(15, 16, 1);
            } else if (map->getBounds()->getX() == 320 * 3) {
                map->ouvrePorte(69, 88, 0);
                scene->setCoffre(15, 17, 1);
            } else if (map->getBounds()->getX() == 320 * 4) {
                map->ouvrePorte(89, 88, 0);
                scene->setCoffre(15, 18, 1);
            } else {
                map->ouvrePorte(129, 88, 0);
                scene->setCoffre(15, 19, 1);
            }
            break;
        case 1656 :
            map->startFinalBattle();
            break;
        case 1659 :
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(57, 69 * 16 + 8, 25 * 16 + 8, N, false, true);
            MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
            return;
        case 1669 :
            MainController::getInstance()->getGameController()->saveData(true);
            MainController::getInstance()->getEndingController()->setId(1);
            MainController::getInstance()->setStep(ENDING);
            return;
        case 1721 :
            scene->setAvancement(AV_SPEECH_VINCENT);
            AudioManager::getInstance()->playSound(TS_SURPRISE);
            AudioManager::getInstance()->playSound(TS_BREAK);
            map->addEffect(new Debris(147 * 16, 2 * 16 + 8, N, 2));
            map->addEffect(new Debris(150 * 16, 1 * 16 + 8, N, 2));
            map->addEffect(new Debris(153 * 16, 2 * 16 + 8, N, 2));
            map->ouvrePorte(146, 0, 5);
            break;
        case 1726 :
            MainController::getInstance()->getGameController()->saveData(true);
            MainController::getInstance()->getEndingController()->setId(2);
            MainController::getInstance()->setStep(ENDING);
            return;
        default : break;
    }

    MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
}

void TextArea::setTextId(int textId) {
    delete text;
    text = TextManager::getInstance()->getText(textId);
    text->setBox(16 * 18, 16 * 4);
    id = textId;
}

bool TextArea::hasLogicalNext() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    Inventory* inventory = link->getInventory();
    int tmp = 0;
    int next = 0;
    switch (id) {
        case 100 :
            next = link->getInventory()->nbQuartCoeur() ? 101 : 102;
            break;
        case 174 :
            next = 190;
            break;
        case 231 : case 232 : case 233 : case 234 : case 236 : case 267 : case 271 : case 366 : case 392 :
        case 416 : case 420 : case 422 : case 425 : case 429 : case 434 : case 447 : case 448 : case 461 :
        case 463 : case 479 : case 527 : case 529 : case 538 : case 547 : case 549 : case 555 : case 563 :
        case 565 : case 566 : case 595 : case 633 : case 638 : case 641 : case 658 : case 659 : case 662 :
        case 674 : case 677 : case 683 : case 688 : case 689 : case 690 : case 691 : case 692 : case 693 :
        case 700 : case 702 : case 709 : case 711 : case 712 : case 713 : case 733 : case 734 : case 736 :
        case 737 : case 738 : case 739 : case 749 : case 755 : case 757 : case 760 : case 765 : case 771 :
        case 777 : case 779 : case 780 : case 781 : case 784 : case 786 : case 790 : case 791 : case 793 :
        case 797 : case 801 : case 809 : case 815 : case 822 : case 824 : case 831 : case 836 : case 841 :
        case 845 : case 846 : case 860 : case 864 : case 872 : case 874 : case 881 : case 882 : case 886 :
        case 887 : case 888 : case 889 : case 890 : case 891 : case 892 : case 893 : case 913 : case 914 :
        case 940 : case 944 : case 946 : case 953 : case 958 : case 967 : case 968 : case 969 : case 970 :
        case 971 : case 972 : case 974 : case 976 : case 977 : case 984 : case 990 : case 996 : case 1024 :
        case 1025 : case 1027 : case 1029 : case 1040 : case 1049 : case 1062 : case 1063 : case 1064 : case 1065 :
        case 1066 : case 1075 : case 1083 : case 1090 : case 1091 : case 1095 : case 1103 : case 1107 : case 1108 :
        case 1110 : case 1111 : case 1113 : case 1118 : case 1121 : case 1132 : case 1135 : case 1138 : case 1140 :
        case 1144 : case 1146 : case 1148 : case 1151 : case 1154 : case 1165 : case 1168 : case 1174 : case 1186 :
        case 1189 : case 1190 : case 1191 : case 1192 : case 1193 : case 1194 : case 1197 : case 1200 : case 1252 :
        case 1253 : case 1254 : case 1269 : case 1270 : case 1271 : case 1272 : case 1273 : case 1274 : case 1275 :
        case 1277 : case 1279 : case 1280 : case 1281 : case 1282 : case 1283 : case 1284 : case 1285 : case 1286 :
        case 1287 : case 1288 : case 1289 : case 1290 : case 1291 : case 1292 : case 1293 : case 1298 : case 1301 :
        case 1312 : case 1313 : case 1314 : case 1320 : case 1342 : case 1354 : case 1358 : case 1364 : case 1367 :
        case 1372 : case 1373 : case 1374 : case 1375 : case 1376 : case 1377 : case 1378 : case 1379 : case 1380 :
        case 1390 : case 1432 : case 1441 : case 1449 : case 1461 : case 1462 : case 1628 : case 1629 : case 1630 :
        case 1633 : case 1634 : case 1635 : case 1636 : case 1640 : case 1641 : case 1642 : case 1654 : case 1655 :
        case 1663 : case 1664 : case 1665 : case 1666 : case 1667 : case 1668 : case 1725 :
            next = id + 1;
            break;
        case 272 : case 273 : case 393 : case 394 : case 415 : case 423 : case 435 : case 436 : case 440 :
        case 530 : case 531 : case 539 : case 540 : case 550 : case 551 : case 675 : case 703 : case 704 :
        case 758 : case 825 : case 826 : case 832 : case 837 : case 842 : case 875 : case 876 : case 947 :
        case 948 : case 978 : case 979 : case 985 : case 986 : case 991 : case 992 : case 997 : case 998 :
        case 999 : case 1030 : case 1031 : case 1041 : case 1042 : case 1084 : case 1085 : case 1096 : case 1097 :
        case 1122 : case 1123 : case 1152 : case 1166 : case 1175 : case 1176 : case 1356 : case 1450 : case 1638 :
            next = id + 2;
            break;
        case 280 :
            if (inventory->getTroc(TT_POULET) < 1 || link->getStatus()->getVirtualRupees() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 281 : case 284 : case 287 : case 290 : case 293 : case 296 : case 300 : case 303 : case 306 :
        case 338 : case 341 : case 344 : case 347 : case 350 : case 353 : case 356 : case 359 : case 362 :
        case 373 : case 376 : case 379 : case 382 : case 385 : case 405 : case 452 : case 455 : case 457 :
        case 459 : case 472 : case 474 : case 476 : case 478 : case 490 : case 504 : case 507 : case 510 :
        case 512 : case 518 : case 521 : case 618 : case 620 : case 626 : case 628 : case 630 : case 636 :
        case 640 : case 644 : case 647 : case 649 : case 652 : case 654 : case 657 : case 665 : case 667 :
        case 669 : case 685 : case 699 : case 812 : case 818 : case 821 : case 856 : case 863 : case 867 :
        case 870 : case 903 : case 905 : case 907 : case 909 : case 911 : case 936 : case 938 : case 961 :
        case 963 : case 966 : case 1007 : case 1009 : case 1011 : case 1013 : case 1015 : case 1018 : case 1020 :
        case 1051 :
            next = 279;
            break;
        case 283 :
            if (inventory->getTroc(TT_ROC_MAGMA) < 1 || inventory->getTroc(TT_ROC_GIVRE) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 286 :
            if (inventory->getTroc(TT_PLUME) < 1 || link->getStatus()->getVirtualRupees() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 289 :
            if (inventory->getTroc(TT_TAPISSERIE) < 1 || link->getStatus()->getVirtualRupees() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 292 :
            if (inventory->getTroc(TT_AMULETTE) < 1 || inventory->getTroc(TT_ROC_MAGMA) < 1 || link->getStatus()->getVirtualRupees() < 250) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 295 :
            if (inventory->getTroc(TT_POULET) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_SAC_RIZ) < 2 || inventory->getTroc(TT_SAC_OLIVES) < 3) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 299 :
            if (inventory->getTroc(TT_PLUME) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_BOCAL_EPICES) < 2 || inventory->getTroc(TT_SAC_OLIVES) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 302 :
            if (inventory->getTroc(TT_SAC_RIZ) >= 99) {
                next = 298;
            } else if (link->getStatus()->getVirtualRupees() < 15) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 305 :
            if (inventory->getTroc(TT_SAC_OLIVES) >= 99) {
                next = 298;
            } else if (link->getStatus()->getVirtualRupees() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 337 :
            if (inventory->getTroc(TT_ROUE) < 1 || inventory->getTroc(TT_JAUGE) < 1
                || inventory->getTroc(TT_SOURCE_NRJ) < 1 || link->getStatus()->getVirtualGanonOr() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 340 :
            if (inventory->getTroc(TT_PERLES) < 1 || link->getStatus()->getVirtualGanonOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 343 :
            if (inventory->getTroc(TT_AMULETTE) < 1 || link->getStatus()->getVirtualGanonOr() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 346 :
            if (inventory->getTroc(TT_PARFUM) < 1 || inventory->getTroc(TT_ROC_GIVRE) < 1 || link->getStatus()->getVirtualGanonOr() < 250) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 349 :
            if (inventory->getTroc(TT_BOCAL_EPICES) < 3) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 352 :
            if (inventory->getTroc(TT_POIVRON) < 1 || inventory->getTroc(TT_BOCAL_EPICES) < 3) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 355 :
            if (inventory->getTroc(TT_ROC_MAGMA) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_TAPISSERIE) < 1 || inventory->getTroc(TT_AMULETTE) < 1 || inventory->getTroc(TT_PARFUM) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 358 :
            if (inventory->getTroc(TT_PERLES) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_BOCAL_EPICES) < 5 || link->getStatus()->getVirtualGanonOr() < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 361 :
            if (inventory->getTroc(TT_BOCAL_EPICES) >= 99) {
                next = 298;
            } else if (link->getStatus()->getVirtualGanonOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 372 :
            if (inventory->getTroc(TT_POULET) < 1 || link->getStatus()->getVirtualPieceOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 375 :
            if (inventory->getTroc(TT_PARFUM) < 1 || link->getStatus()->getVirtualPieceOr() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 378 :
            if (inventory->getTroc(TT_TAPISSERIE) < 1 || inventory->getTroc(TT_ROC_MAGMA) < 1 || link->getStatus()->getVirtualPieceOr() < 250) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 381 :
            if (inventory->getTroc(TT_AMULETTE) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_POULET) < 1 || inventory->getTroc(TT_SAC_OLIVES) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 384 :
            if (inventory->getTroc(TT_PLUME) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_BOCAL_EPICES) < 1 || inventory->getTroc(TT_SAC_OLIVES) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 404 :
            if (link->getStatus()->getVirtualGanonOr() < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 414 :
            next = link->getInventory()->nbCristaux() == 7 ? 416 : 415;
            break;
        case 418 : case 419 :
            if (scene->getMap()->getId() >= 46 && scene->getMap()->getId() < 61) {
                next = 1245;
            } else {
                return false;
            }
            break;
        case 424 :
            next = 427;
            break;
        case 441 :
            next = 438;
            break;
        case 451 :
            if (inventory->getTroc(TT_TAPISSERIE) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_PERLES) < 2 || inventory->getTroc(TT_BOCAL_EPICES) < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 454 :
            if (inventory->getTroc(TT_AMULETTE) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_POULET) < 5 || inventory->getTroc(TT_SAC_OLIVES) < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 456 :
            if (inventory->getTroc(TT_PERLES) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_BOCAL_EPICES) < 2 || inventory->getTroc(TT_SAC_RIZ) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 458 :
            if (inventory->getTroc(TT_SAC_RIZ) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_SAC_OLIVES) < 1 || link->getStatus()->getVirtualRupees() < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 471 :
            if (inventory->getTroc(TT_PERLES) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 473 :
            if (inventory->getTroc(TT_PLUME) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 475 :
            if (inventory->getTroc(TT_POULET) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 477 :
            if (inventory->getTroc(TT_POULET) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_SAC_RIZ) < 1 || inventory->getTroc(TT_SAC_OLIVES) < 2) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 481 :
            if (scene->getAvancement() < AV_GANON_CAPTURE) {
                next = 482;
            } else {
                return false;
            }
            break;
        case 489 :
            if (link->getStatus()->getVirtualRupees() < 15) {
                next = 278;
            } else {
                next = 491;
            }
            break;
        case 503 :
            if (inventory->getTroc(TT_TAPISSERIE) < 1 || inventory->getTroc(TT_PARFUM) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 506 :
            if (inventory->getTroc(TT_PARFUM) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_PLUME) < 3 || inventory->getTroc(TT_SAC_RIZ) < 4) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 509 :
            if (inventory->getTroc(TT_SAC_OLIVES) >= 99) {
                next = 298;
            } else if (link->getStatus()->getVirtualRupees() < 15) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 511 :
            if (inventory->getTroc(TT_BOCAL_EPICES) >= 99) {
                next = 298;
            } else if (link->getStatus()->getVirtualRupees() < 20) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 515 :
            if (inventory->hasObject(BOTTES)) {
                next = 516;
            } else {
                return false;
            }
            break;
        case 517 :
            if (inventory->getTroc(TT_ROC_GIVRE) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_TAPISSERIE) < 1 || inventory->getTroc(TT_AMULETTE) < 1 || inventory->getTroc(TT_PARFUM) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 520 :
            if (inventory->getTroc(TT_PERLES) >= 99) {
                next = 298;
            } else if (inventory->getTroc(TT_BOCAL_EPICES) < 1 || inventory->getTroc(TT_SAC_RIZ) < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 577 :
            if (link->getBouclier() == 1) {
                next = 578;
            } else {
                next = 580;
            }
            break;
        case 601 :
            if (link->getStatus()->getVirtualGanonOr() < 100) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 602 : case 607 :
            next = 603;
            break;
        case 606 :
            if (link->getStatus()->getVirtualGanonOr() < 999) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 617 :
            if (link->getStatus()->getVirtualRupees() < 20) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 619 :
            if (link->getStatus()->getVirtualRupees() < 30) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 625 :
            if (link->getStatus()->getVirtualRupees() < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 627 :
            if (link->getStatus()->getVirtualRupees() < 15) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 629 :
            if (link->getStatus()->getVirtualRupees() < 25) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 632 :
            next = 635;
            break;
        case 635 :
            if (link->getInventory()->nbGemmeForce() < 30) {
                next = 637;
            } else {
                return false;
            }
            break;
        case 639 : case 646 : case 648 : case 653 :
            if (link->getInventory()->nbGemmeForce() < 20) {
                next = 637;
            } else {
                return false;
            }
            break;
        case 643 :
            if (link->getInventory()->nbGemmeForce() < 10) {
                next = 637;
            } else {
                return false;
            }
            break;
        case 651 : case 656 :
            if (link->getInventory()->nbGemmeForce() < 40) {
                next = 637;
            } else {
                return false;
            }
            break;
        case 663 :
            if (scene->getMap()->getEpoque() == EP_PRESENT) {
                next = 666;
            } else if (scene->getMap()->getEpoque() == EP_FUTUR) {
                next = 935;
            } else {
                next = 1017;
            }
            break;
        case 664 :
            if (scene->getMap()->getEpoque() == EP_PRESENT) {
                next = 668;
            } else if (scene->getMap()->getEpoque() == EP_FUTUR) {
                next = 937;
            } else {
                next = 1019;
            }
            break;
        case 666 :
            if (link->getStatus()->getVirtualRupees() < 60) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 668 :
            if (link->getStatus()->getVirtualRupees() < 40) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 676 :
            next = 679;
            break;
        case 684 :
            if (link->getStatus()->getVirtualRupees() < (4 - ((inventory->hasQuartCoeur(15) ? 0 : 1) + (inventory->hasGemmeForce(160) ? 0 : 1)
                + (inventory->hasGemmeForce(161) ? 0 : 1) + (inventory->hasGemmeForce(162) ? 0 : 1)) + 1) * 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 698 :
            if (link->getStatus()->getVirtualRupees() < 160) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 714 :
            if (scene->getAvancement() < AV_PARLE_PECHE) {
                scene->setAvancement(AV_PARLE_PECHE);
            }
            if (link->getStatus()->getVirtualRupees() < 10) {
                next = 278;
            } else {
                next = 716;
            }
            break;
        case 715 :
            if (scene->getAvancement() < AV_PARLE_PECHE) {
                scene->setAvancement(AV_PARLE_PECHE);
            }
            next = 717;
            break;
        case 717 :
            if (link->getStatus()->getVirtualRupees() < 5) {
                next = 278;
            } else {
                next = 719;
            }
            break;
        case 718 :
            next = 720;
            break;
        case 720 :
            if (link->getStatus()->getVirtualRupees() < 2) {
                next = 278;
            } else {
                next = 722;
            }
            break;
        case 721 :
            next = 723;
            break;
        case 723 :
            if (link->getStatus()->getVirtualRupees() < 1) {
                next = 278;
            } else {
                next = 725;
            }
            break;
        case 724 :
            next = 726;
            break;
        case 726 :
        next = 728;
            break;
        case 727 :
            next = 729;
            break;
        case 735 :
            AudioManager::getInstance()->playSound(TS_HAPPY, 2);
            next = 736;
            break;
        case 748 :
            AudioManager::getInstance()->playSound(TS_HAPPY, 2);
            next = 749;
            break;
        case 752 :
            if (link->getInventory()->hasObject(ENCYCLOPEDIE_POISSONS)) {
                next = 754;
            } else {
                next = 753;
            }
            break;
        case 759 : next = 762; break;
        case 766 : next = 770; break;
        case 767 : next = 771; break;
        case 768 : next = 773; break;
        case 769 : next = 774; break;
        case 778 : next = 278; break;
        case 785 : next = 788; break;
        case 807 :
            if (scene->getMap()->getEpoque() == EP_PASSE) {
                if (link->getStatus()->getVirtualRupees() < 4 && link->getStatus()->getVirtualGanonOr() < 2) {
                    next = 957;
                } else if (link->getStatus()->getVirtualRupees() >= 4 && link->getStatus()->getVirtualGanonOr() < 2) {
                    next = 958;
                } else if (link->getStatus()->getVirtualRupees() < 4 && link->getStatus()->getVirtualGanonOr() >= 2) {
                    next = 809;
                } else if (link->getStatus()->getVirtualRupees() >= 4 && link->getStatus()->getVirtualGanonOr() >= 2) {
                    next = 964;
                }
            } else if (scene->getMap()->getEpoque() == EP_PRESENT) {
                if (link->getStatus()->getVirtualGanonOr() == 0 && link->getStatus()->getVirtualPieceOr() == 0) {
                    next = 808;
                } else if (link->getStatus()->getVirtualGanonOr() > 0 && link->getStatus()->getVirtualPieceOr() == 0) {
                    next = 809;
                } else if (link->getStatus()->getVirtualGanonOr() == 0 && link->getStatus()->getVirtualPieceOr() > 0) {
                    next = 815;
                } else if (link->getStatus()->getVirtualGanonOr() > 0 && link->getStatus()->getVirtualPieceOr() > 0) {
                    next = 819;
                }
            } else {
                if (link->getStatus()->getVirtualRupees() < 2 && link->getStatus()->getVirtualPieceOr() == 0) {
                    next = 859;
                } else if (link->getStatus()->getVirtualRupees() >= 2 && link->getStatus()->getVirtualPieceOr() == 0) {
                    next = 860;
                } else if (link->getStatus()->getVirtualRupees() < 2 && link->getStatus()->getVirtualPieceOr() > 0) {
                    next = 864;
                } else if (link->getStatus()->getVirtualRupees() >= 2 && link->getStatus()->getVirtualPieceOr() > 0) {
                    next = 868;
                }
            }
            break;
        case 810 : case 820 : case 965 :
            if (scene->getMap()->getEpoque() == EP_PRESENT) {
                if (link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees() < 2) {
                    next = 813;
                } else {
                    next = 811;
                }
            } else if (scene->getMap()->getEpoque() == EP_PASSE) {
                if (link->getStatus()->getMaxPieceOr() == link->getStatus()->getVirtualPieceOr()) {
                    next = 813;
                } else {
                    next = 962;
                }
            }
            break;
        case 811 :
            tmp = (link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees()) / 2;
            if (tmp > link->getStatus()->getVirtualGanonOr()) tmp = link->getStatus()->getVirtualGanonOr();
            link->getStatus()->updateRupees(tmp * 2);
            link->getStatus()->updateGanonOr(-tmp);
            next = 814;
            break;
        case 816 : case 819 :
            if (link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees() < 4) {
                next = 813;
            } else {
                next = 817;
            }
            break;
        case 817 :
            tmp = (link->getStatus()->getMaxRupees() - link->getStatus()->getVirtualRupees()) / 4;
            if (tmp > link->getStatus()->getVirtualPieceOr()) tmp = link->getStatus()->getVirtualPieceOr();
            link->getStatus()->updateRupees(tmp * 4);
            link->getStatus()->updatePieceOr(-tmp);
            next = 814;
            break;
        case 833 : case 838 : case 843 :
            next = 828;
            break;
        case 847 :
            link->getInventory()->setObject(ENCYCLOPEDIE);
            if (scene->getMap()->getEpoque() == EP_PASSE) next = 848;
            else if (scene->getMap()->getEpoque() == EP_PRESENT) next = 849;
            else next = 850;
            break;
        case 851 : case 852 : case 853 : case 854 :
            next = 855;
            break;
        case 861 : case 869 :
            if (link->getStatus()->getMaxGanonOr() == link->getStatus()->getVirtualGanonOr()) {
                next = 813;
            } else {
                next = 862;
            }
            break;
        case 862 :
            tmp = link->getStatus()->getVirtualRupees() / 2;
            if (tmp > (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr())) {
                tmp = (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr());
            }
            link->getStatus()->updateGanonOr(tmp);
            link->getStatus()->updateRupees(-tmp * 2);
            next = 814;
            break;
        case 865 : case 868 :
            if (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr() < 2) {
                next = 813;
            } else {
                next = 866;
            }
            break;
        case 866 :
            tmp = (link->getStatus()->getMaxGanonOr() - link->getStatus()->getVirtualGanonOr()) / 2;
            if (tmp > link->getStatus()->getVirtualPieceOr()) tmp = link->getStatus()->getVirtualPieceOr();
            link->getStatus()->updateGanonOr(tmp * 2);
            link->getStatus()->updatePieceOr(-tmp);
            next = 814;
            break;
        case 902 :
            if (link->getStatus()->getVirtualGanonOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 904 :
            if (link->getStatus()->getVirtualGanonOr() < 15) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 906 :
            if (link->getStatus()->getVirtualGanonOr() < 4) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 908 :
            if (link->getStatus()->getVirtualGanonOr() < 8) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 910 :
            if (link->getStatus()->getVirtualGanonOr() < 16) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 935 :
            if (link->getStatus()->getVirtualGanonOr() < 40) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 937 :
            if (link->getStatus()->getVirtualGanonOr() < 25) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 959 : case 964 :
            if (link->getStatus()->getMaxPieceOr() == link->getStatus()->getVirtualPieceOr()) {
                next = 813;
            } else {
                next = 960;
            }
            break;
        case 960 :
            tmp = link->getStatus()->getVirtualRupees() / 4;
            if (tmp > (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr())) {
                tmp = (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr());
            }
            link->getStatus()->updatePieceOr(tmp);
            link->getStatus()->updateRupees(-tmp * 4);
            next = 814;
            break;
        case 962 :
            tmp = link->getStatus()->getVirtualGanonOr() / 2;
            if (tmp > (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr())) {
                tmp = (link->getStatus()->getMaxPieceOr() - link->getStatus()->getVirtualPieceOr());
            }
            link->getStatus()->updatePieceOr(tmp);
            link->getStatus()->updateGanonOr(-tmp * 2);
            next = 814;
            break;
        case 1006 :
            if (link->getStatus()->getVirtualPieceOr() < 5) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1008 :
            if (link->getStatus()->getVirtualPieceOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1010 :
            if (link->getStatus()->getVirtualPieceOr() < 1) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1012 :
            if (link->getStatus()->getVirtualPieceOr() < 3) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1014 :
            if (link->getStatus()->getVirtualPieceOr() < 6) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1017 :
            if (link->getStatus()->getVirtualPieceOr() < 15) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1019 :
            if (link->getStatus()->getVirtualPieceOr() < 10) {
                next = 278;
            } else {
                return false;
            }
            break;
        case 1050 :
            if (link->getStatus()->getVirtualPieceOr() < 1) {
                next = 278;
            } else if (scene->getCoffre(0, 29) == 0) {
                scene->setCoffre(0, 29, 1);
                link->getStatus()->updatePieceOr(-1);
                next = 1052;
            } else if (scene->getCoffre(0, 29) == 1) {
                scene->setCoffre(0, 29, 2);
                link->getStatus()->updatePieceOr(-1);
                next = 1053;
            } else {
                scene->setCoffre(0, 29, 3);
                scene->setAvancement(AV_INFO_PASSE_OK);
                link->getStatus()->updatePieceOr(-1);
                next = 1054;
            }
            break;
        case 1068 :
            if (scene->getCoffre(0, 1) > 100) {
                next = 1075;
            } else if (scene->getCoffre(0, 1) == 100) {
                next = 1074;
            } else if (scene->getCoffre(0, 1) >= 80) {
                next = 1073;
            } else if (scene->getCoffre(0, 1) >= 50) {
                next = 1072;
            } else if (scene->getCoffre(0, 1) >= 2) {
                next = 1071;
            } else if (scene->getCoffre(0, 1) == 1) {
                next = 1070;
            } else {
                next = 1069;
            }
            break;
        case 1099 :
            next = 1096;
            break;
        case 1153 :
            next = 1156;
            break;
        case 1167 :
            next = 1170;
            break;
        case 1196 :
            next = 1197;
            AudioManager::getInstance()->playMusic(75);
            break;
        case 1226 : case 1227 : case 1228 : case 1257 : case 1258 : case 1260 : case 1263 : case 1265 : case 1267 :
            next = 417;
            break;
        case 1255 :
            if (!scene->getCoffre(4, 30)) {
                scene->setCoffre(4, 30, 1);
                next = 417;
            } else {
                return false;
            }
            break;
        case 1332 :
            if (link->getY() == 25 * 16 + 8) {
                next = inventory->hasObject(TRIFORCE) ? 1663 : 1354;
                break;
            }
            return false;
        case 1357 :
            next = 1360;
            break;
        case 1425 :
            if (link->getStatus()->getVirtualGanonOr() < 10) {
                next = 1428;
            } else {
                next = 1424;
            }
            break;
        case 1426 : case 1431 : case 1437 : case 1444 : case 1451 : case 1457 :
            next = 1427;
            break;
        case 1430 :
            if (link->getStatus()->getVirtualGanonOr() < 5) {
                next = 1428;
            } else {
                next = 1432;
            }
            break;
        case 1435 : case 1442 : case 1445 : case 1448 : case 1454 : case 1455 :
            if (!scene->getMap()->isJeuCasinoStarted()) {
                next = 1436;
                break;
            }
            return false;
        case 1436 :
            if (link->getStatus()->getVirtualGanonOr() < 10) {
                next = 1428;
                break;
            }
            return false;
        case 1443 :
            if (link->getStatus()->getVirtualGanonOr() < 5) {
                next = 1428;
                break;
            }
            return false;
        case 1456 :
            if (link->getStatus()->getVirtualGanonOr() < scene->getMap()->getPriceCasino()) {
                next = 1428;
                break;
            }
            return false;
        case 1463 :
            for (int i = 0; i < 40; i++) scene->setCoffre(13, 19 + i, 0);
            tmp = (int)((float)rand() / RAND_MAX * (40));
            scene->setCoffre(13, 18, 1); // nb questions
            scene->setCoffre(13, 19 + tmp, 1);
            next = 1465 + tmp * 4;
            break;
        case 1464 :
            tmp = (int)((float)rand() / RAND_MAX * (40 - scene->getCoffre(13, 18)));
            for (int i = 0; i <= tmp; i++) if (scene->getCoffre(13, 19 + i)) tmp++;
            scene->setCoffre(13, 18, scene->getCoffre(13, 18) + 1); // nb questions
            scene->setCoffre(13, 19 + tmp, 1);
            next = 1465 + tmp * 4;
            break;
        case 1465 : case 1469 : case 1473 : case 1481 : case 1497 : case 1505 : case 1517 : case 1521 : case 1525 : case 1529 : // vrai sur affirmations fausses
        case 1537 : case 1545 : case 1549 : case 1557 : case 1561 : case 1565 : case 1569 : case 1581 : case 1593 : case 1597 :
        case 1605 : case 1613 : case 1621 :
            next = id + 3;
            link->getStatus()->setGanonOr(link->getStatus()->getVirtualGanonOr() - scene->getMap()->getCasino());
            scene->getMap()->increaseCasino();
            break;
        case 1466 : case 1470 : case 1474 : case 1482 : case 1498 : case 1506 : case 1518 : case 1522 : case 1526 : case 1530 : // faux sur affirmations fausses
        case 1538 : case 1546 : case 1550 : case 1558 : case 1562 : case 1566 : case 1570 : case 1582 : case 1594 : case 1598 :
        case 1606 : case 1614 : case 1622 :
            next = id + 1;
            scene->getMap()->testDegat(scene->getMap()->getBounds(), N, 1, TA_PHYSIC, TE_ARGENT, true);
            break;
        case 1477 : case 1485 : case 1489 : case 1493 : case 1501 : case 1509 : case 1513 : case 1533 : case 1541 : case 1553 : // vrai sur affirmations vraies
        case 1573 : case 1577 : case 1585 : case 1589 : case 1601 : case 1609 : case 1617 :
            next = id + 2;
            scene->getMap()->testDegat(scene->getMap()->getBounds(), N, 1, TA_PHYSIC, TE_ARGENT, true);
            break;
        case 1478 : case 1486 : case 1490 : case 1494 : case 1502 : case 1510 : case 1514 : case 1534 : case 1542 : case 1554 : // faux sur affirmations vraies
        case 1574 : case 1578 : case 1586 : case 1590 : case 1602 : case 1610 : case 1618 :
            next = id + 2;
            link->getStatus()->setGanonOr(link->getStatus()->getVirtualGanonOr() - scene->getMap()->getCasino());
            scene->getMap()->increaseCasino();
            break;
        case 1467 : case 1471 : case 1475 : case 1479 : case 1483 : case 1487 : case 1491 : case 1495 : case 1499 : case 1503 :
        case 1507 : case 1511 : case 1515 : case 1519 : case 1523 : case 1527 : case 1531 : case 1535 : case 1539 : case 1543 :
        case 1547 : case 1551 : case 1555 : case 1559 : case 1563 : case 1567 : case 1571 : case 1575 : case 1579 : case 1583 :
        case 1587 : case 1591 : case 1595 : case 1599 : case 1603 : case 1607 : case 1611 : case 1615 : case 1619 : case 1623 :
            next = scene->getMap()->bossCasinoVaincu() ? 1625 : 1464; // vaincu ou question suivante
            break;
        case 1468 : case 1472 : case 1476 : case 1480 : case 1484 : case 1488 : case 1492 : case 1496 : case 1500 : case 1504 :
        case 1508 : case 1512 : case 1516 : case 1520 : case 1524 : case 1528 : case 1532 : case 1536 : case 1540 : case 1544 :
        case 1548 : case 1552 : case 1556 : case 1560 : case 1564 : case 1568 : case 1572 : case 1576 : case 1580 : case 1584 :
        case 1588 : case 1592 : case 1596 : case 1600 : case 1604 : case 1608 : case 1612 : case 1616 : case 1620 : case 1624 :
            if (link->getStatus()->getVirtualGanonOr() <= 0) {
                return false;
            }
            next = 1464; // question suivante
            break;
        case 1631 :
            if (!scene->getCoffre(13, 59)) {
                scene->setCoffre(13, 59, 1);
                next = 417;
            } else {
                return false;
            }
            break;
        case 1637 :
            if (!scene->getCoffre(14, 15)) {
                scene->setCoffre(14, 15, 1);
                next = 417;
            } else {
                return false;
            }
            break;
        case 1639 :
            next =  1643;
            break;
        default : return false;
    }
    setTextId(next);
    return true;
}

void TextArea::drawAdditionalContent() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    int tmp;
    switch (id) {
        case 100 :
            tmp = link->getInventory()->nbQuartCoeur();
            if (tmp == 0) tmp = 4;
            WindowManager::getInstance()->draw(imageCoeur, 16 * tmp, 0, 16, 16, 16 * 9 + 8, 16 * 12);
            break;
        default : break;
    }
}
