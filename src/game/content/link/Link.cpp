#include "Link.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../../config/ConfigurationManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

#include "../effects/Plouf.h"
#include "../effects/Flamme.h"
#include "../effects/FumeeRose.h"
#include "../effects/FumeeViolette.h"
#include "../effects/Naufrage.h"

#include "../objects/ObjBomb.h"
#include "../objects/TasDePierres.h"

#include "../helper/ProjectileHelper.h"

Link::Link(Save *save, Metronome *metronome) : metronome(metronome), epee(0), bouclier(0), charging(false), animation(IDLE),
                                               anim(0), animMax(0), vanim(40), imageLink(0), porte(0), elan(2), grappin(0), flamme(0), lapin(false)
{

    imageEffets = ResourceManager::getInstance()->loadImage("data/images/link/effects.png", true);
    imageObjets = ResourceManager::getInstance()->loadImage("data/images/link/objets.png", true);

    status = new Status(save);
    inventory = new Inventory(save);

    loadFromSave(save);

    w = 16;
    h = 24;
    speed = 0;

    height = h; // for display order

    accuPush = 0;
    charge = 0;
    wasOnIce = false;
    moved = false;

    for (int i = 0; i < 8; i++)
    {
        oldx[i] = x;
        oldy[i] = y;
    }

    startX = x;
    startY = y;
    startDir = direction;

    startX2 = x;
    startY2 = y;
    startDir2 = direction;

    recup = 0;

    chrono.reset();
}

Link::~Link()
{
    ResourceManager::getInstance()->free(imageLink);
    ResourceManager::getInstance()->free(imageEffets);
    ResourceManager::getInstance()->free(imageObjets);
    delete status;
    delete inventory;
    delete porte;
    delete grappin;
    delete flamme;
    delete epee;
    delete bouclier;
}

void Link::loadFromSave(Save *save)
{
    x = save->getX();
    y = save->getY();
    direction = save->getDirection();
    tunique = save->getTunique();
    setEpee(save->getEpee());
    setBouclier(save->getBouclier());
    setOniLink(status->isOniLink(), true);
}

void Link::saveData(Save *save)
{
    save->setX(startX);
    save->setY(startY);
    save->setDirection(startDir);
    save->setTunique(tunique);
    save->setEpee(getEpee());
    save->setBouclier(getBouclier());
    status->saveData(save);
    inventory->saveData(save);
}

int Link::getDefense()
{
    int defense = tunique - 1 + getBouclier();
    if (tunique == 4)
        defense--;
    if (getBouclier() == 4)
        defense--;
    if (defense > 0 && status->isOniLink())
    {
        defense += 3;
    }
    if (inventory->hasObject(BONUS_DEFENSE_1))
    {
        defense++;
    }
    if (inventory->hasObject(BONUS_DEFENSE_2))
    {
        defense++;
    }
    return defense;
}

int Link::getForce()
{
    int force = getEpee();
    if (force && status->isOniLink())
    {
        force += 3;
    }
    if (inventory->hasObject(BONUS_FORCE_1))
    {
        force++;
    }
    if (inventory->hasObject(BONUS_FORCE_2))
    {
        force++;
    }
    return force;
}

bool Link::underAttack(Direction dir, int force, TypeAttack type, TypeEffect effect)
{
    if (!status->isInvincible() && status->getVirtualLife() > 0 && animation != COULE && animation != TOUCHE && animation != CHUTE && animation != ELECTRIC)
    {
        status->setInvincible();

        int def = getDefense();
        int degats = def == 0 ? force * 2 : force / def;

        if (effect == TE_QUASI_MORT)
        {
            degats = status->getLife() - 1;
        }
        else if (effect == TE_MORT)
        {
            degats = status->getMaxLife();
        }
        else if (effect == TE_GRAVITE)
        {
            degats = (status->getLife() + 1) / 2;
        }
        else if (effect == TE_GLACE)
        {
            status->updateGel(128);
        }
        else if (effect == TE_CONFUSION)
        {
            status->updateIvre(128);
            return true;
        }
        else if (effect == TE_LAPIN)
        {
            if (!lapin)
            {
                accuPush = 0;
                anim = 0;
                charge = 0;
                if (porte != 0)
                    lacheObj();
                setAnimation(IDLE);
                setLapin(true);
                Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                map->addEffect(new FumeeRose(x + 8, y + 16));
                AudioManager::getInstance()->playSound(TS_CAPE_OFF);
            }
            return true;
        }
        else if (effect == TE_COLERE)
        {
        }
        else if (effect == TE_EXPONENTIEL)
        {
            Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            degats = map->getDestFinal();
            map->increaseDestFinal();
        }

        if (lapin)
        {
            setLapin(false);
            Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            map->addEffect(new FumeeRose(x + 8, y + 16));
            AudioManager::getInstance()->playSound(TS_CAPE_OFF);
        }

        if (effect == TE_ARGENT)
        {
            Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
            status->updateGanonOr(-map->getCasino());
            map->increaseCasino();
            if (status->getVirtualGanonOr() <= 0)
            {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(58, 69 * 16 + 8, 102 * 16, N, false, true);
                MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                AudioManager::getInstance()->playSound(TS_TELEPORT);
                return true;
            }
        }
        else if (effect != TE_COLERE)
        {
            if (degats < 1)
                degats = 1;
            status->setLife(status->getLife() - degats);
        }
        else
        {
            degats = 5;
        }

        if (effect == TE_ELECTRIC)
        {
            setAnimation(ELECTRIC);
            AudioManager::getInstance()->playSound(TS_SHOCK);
            switch (dir)
            {
            case N:
                moveY(-4, 4, 1);
                break;
            case S:
                moveY(4, 4, 1);
                break;
            case W:
                moveX(-4, 4, 1);
                break;
            case E:
                moveX(4, 4, 1);
                break;
            }
        }
        else if (animation == BARQUE_IDLE || animation == BARQUE)
        {
            AudioManager::getInstance()->playSound(TS_HURT);
            switch (dir)
            {
            case N:
                moveY(-4, 4, 1);
                break;
            case S:
                moveY(4, 4, 1);
                break;
            case W:
                moveX(-4, 4, 1);
                break;
            case E:
                moveX(4, 4, 1);
                break;
            }
            if (status->getVirtualLife() <= 0)
            {
                AudioManager::getInstance()->playMusic(3);
                Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
                map->addEffect(new Naufrage(x + 8, y + 16));
                map->addEffect(new Plouf(x, y));
                AudioManager::getInstance()->playSound(TS_BREAK);
                AudioManager::getInstance()->playSound(TS_PLOUF);
            }
        }
        else
        {
            switch (dir)
            {
            case N:
                toucheX = 0;
                toucheY = -1;
                direction = S;
                break;
            case S:
                toucheX = 0;
                toucheY = 1;
                direction = N;
                break;
            case W:
                toucheX = -1;
                toucheY = 0;
                direction = E;
                break;
            case E:
                toucheX = 1;
                toucheY = 0;
                direction = W;
                break;
            }
            setAnimation(TOUCHE);
            AudioManager::getInstance()->playSound(TS_HURT);
        }

        return true;
    }
    return false;
}

int Link::compareTo(Listable *other)
{
    Drawable *o = dynamic_cast<Drawable *>(other);
    if (o == 0)
        return 0;
    if (animation == COULE)
        return 1;
    return o->getDown() - getDown();
}

void Link::startNewMap()
{
    startNewRoom(true);
    startX = x;
    startY = y;
    startDir = direction;
    setAnimation(isOnWater() ? FLOTTE : IDLE);
}

void Link::startNewRoom(bool newMap)
{
    startX2 = x;
    startY2 = y;
    startDir2 = direction;

    if (animation == PORTE || animation == TRANSPORTE)
    {
        if (animation == PORTE)
        {
            setAnimation(IDLE);
        }
        else
        {
            setAnimation(WALK);
        }
        if (porte != 0 && !newMap && porte->isResetable())
        {
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->addObject(porte);
            porte->reset();
        }
        else
        {
            delete porte;
        }
        porte = 0;
    }
    if (animation == SOULEVE)
    {
        setAnimation(IDLE);
        porte = 0;
    }
}

void Link::revit()
{
    status->setLife(status->getMaxLife());
    status->increaseDeaths();
    status->setInvincible();
    status->resetGel();
    status->resetIvre();
    if (status->isOniLink())
    {
        setOniLink(false, true);
    }
    x = startX;
    y = startY;
    direction = startDir;
    startX2 = x;
    startY2 = y;
    startDir2 = direction;
    lapin = false;
    accuPush = 0;
    charge = 0;
    wasOnIce = false;
    moved = false;
    setAnimation(isOnWater() ? FLOTTE : IDLE);
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    scene->getMap()->reset();
}

void Link::setLapin(bool l)
{
    lapin = l;
}

bool Link::isLapin()
{
    return lapin;
}

void Link::setOniLink(bool b, bool revit)
{
    status->setOniLink(b);

    if (b)
    {
        ResourceManager::getInstance()->free(imageLink);
        imageLink = ResourceManager::getInstance()->loadImage("data/images/link/onilink.png", true);
    }
    else
    {
        setTunique(tunique);
    }
    if (epee != 0)
        setEpee(epee->getForce());
    if (bouclier != 0)
        setBouclier(bouclier->getLevel());

    if (!revit)
    {
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        map->addEffect(new FumeeViolette(x + 8, y + 16));
        AudioManager::getInstance()->playSound(TS_CAPE_OFF);
    }
}

int Link::getSpeed()
{
    return speed;
}

void Link::handleAction(Action *action)
{

    moved = false;

    if (status->getVirtualLife() <= 0)
    {
        if (action->isAction(ACTION) || action->isAction(INVENTAIRE) || action->isAction(QUIT_GAME))
        {
            action->setAction(ACTION, false);
            action->setAction(INVENTAIRE, false);
            action->setAction(QUIT_GAME, false);
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->setStep(SCENE_TRANSITION_LIVE);
        }
        return;
    }

    if (action->isAction(QUIT_GAME))
    {
        MainController::getInstance()->getGameController()->displayText(97);
        return;
    }

    bool isAble = true;

    int prevX = x;
    int prevY = y;

    charging = action->isAction(LOAD);
    if (charge && !charging)
    {
        if (charge == 21)
        {
            AudioManager::getInstance()->playSound(TS_SPIN);
            setAnimation(SPIN_EPEE);
        }
        charge = 0;
    }

    if ((animation != IDLE && animation != WALK && animation != FLOTTE && animation != NAGE && animation != BARQUE_IDLE && animation != BARQUE && animation != PUSH && charge == 0) || porte != 0)
    {
        isAble = false;
    }

    if (porte != 0 && animation != SOULEVE && ((action->isAction(HIT) && epee != 0) || action->isAction(ACTION) || action->isAction(OBJECT)))
    {
        if (animation == PORTE && porte->isPosable())
        {
            setAnimation(IDLE);
            lacheObj();
        }
        else
        {
            if (animation == PORTE)
            {
                elan = 2;
            }
            else
            {
                elan = speed;
            }
            setAnimation(THROW);
            lanceObj();
        }
    }

    if (isAble && animation != FLOTTE && animation != NAGE && animation != BARQUE_IDLE && animation != BARQUE && action->isAction(HIT) && epee != 0 && !lapin)
    {
        TypeSound type = TS_ATTACK1;
        switch (rand() % 4)
        {
        case 0:
            type = TS_ATTACK1;
            break;
        case 1:
            type = TS_ATTACK2;
            break;
        case 2:
            type = TS_ATTACK3;
            break;
        case 3:
            type = TS_ATTACK4;
            break;
        }

        AudioManager::getInstance()->playSound(type);
        AudioManager::getInstance()->playSound(TS_SWORD);
        setAnimation(HIT_EPEE);
        isAble = false;
    }

    if (((isAble && animation != FLOTTE && animation != NAGE && animation != BARQUE_IDLE && animation != BARQUE) || animation == PECHE) && action->isAction(OBJECT) && !charging && !lapin /*&& !status->isOniLink()*/)
    {
        isAble = !useStuff() && isAble;
    }

    if (isAble && action->isAction(ACTION))
    {
        BoundingBox bb;
        bb.setW(16);
        bb.setH(16);
        switch (direction)
        {
        case N:
            bb.setX(x);
            bb.setY(y - 8 + 8);
            bb.setH(8);
            break;
        case S:
            bb.setX(x);
            bb.setY(y + 24);
            bb.setH(8);
            break;
        case W:
            bb.setX(x - 16 + 8);
            bb.setY(y + 8);
            bb.setW(8);
            break;
        case E:
            bb.setX(x + 16);
            bb.setY(y + 8);
            bb.setW(8);
            break;
        }
        isAble = !MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->tryToTalk(&bb, direction);
    }

    if (isAble && animation != FLOTTE && animation != NAGE && animation != BARQUE_IDLE && animation != BARQUE && action->isAction(ACTION) && !lapin)
    {
        isAble = !porteObjet();
    }

    int nbDir = 0;
    int dx = 0;
    int dy = 0;
    speed = (inventory->hasObject(BOTTES) && action->isAction(RUN) && !status->getGel() && inventory->getTrocGemme(0) != TGR_ENCLUME) ? 4 : 2;

    if (isAble || animation == PORTE || animation == TRANSPORTE)
    {

        if (status->getIvre())
        {
            bool upIvre = action->isAction(UP);
            bool downIvre = action->isAction(DOWN);
            bool leftIvre = action->isAction(LEFT);
            bool rightIvre = action->isAction(RIGHT);
            action->setAction(UP, downIvre);
            action->setAction(DOWN, upIvre);
            action->setAction(LEFT, rightIvre);
            action->setAction(RIGHT, leftIvre);
        }

        if (action->isAction(UP))
        {
            nbDir++;
            dy--;
        }
        if (action->isAction(DOWN))
        {
            nbDir++;
            dy++;
        }
        if (action->isAction(LEFT))
        {
            nbDir++;
            dx--;
        }
        if (action->isAction(RIGHT))
        {
            nbDir++;
            dx++;
        }

        if ((action->isAction(UP) && !action->isAction(DOWN)) || (action->isAction(DOWN) && !action->isAction(UP)) || (action->isAction(LEFT) && !action->isAction(RIGHT)) || (action->isAction(RIGHT) && !action->isAction(LEFT)))
        {

            if (animation == IDLE || animation == FLOTTE || animation == BARQUE_IDLE || animation == PORTE)
            {
                if (isAble && animation != FLOTTE && animation != BARQUE_IDLE)
                {
                    setAnimation(WALK);
                }
                else if (porte)
                {
                    setAnimation(TRANSPORTE);
                }
                else if (animation == FLOTTE)
                {
                    setAnimation(NAGE);
                }
                else
                {
                    setAnimation(BARQUE);
                }
            }
            else if (animation == PUSH)
            {
                if (nbDir > 1 ||
                    (direction == N && !action->isAction(UP)) ||
                    (direction == S && !action->isAction(DOWN)) ||
                    (direction == W && !action->isAction(LEFT)) ||
                    (direction == E && !action->isAction(RIGHT)))
                {
                    setAnimation(WALK);
                }
            }
        }
        else
        {
            if (isAble && animation != FLOTTE && animation != NAGE && animation != BARQUE_IDLE && animation != BARQUE)
            {
                setAnimation(IDLE);
            }
            else if (porte)
            {
                setAnimation(PORTE);
            }
            else if (animation == FLOTTE || animation == NAGE)
            {
                setAnimation(FLOTTE);
            }
            else
            {
                setAnimation(BARQUE_IDLE);
            }
        }

        if (!charge)
        {
            findDirection(action->isAction(UP), action->isAction(DOWN), action->isAction(LEFT), action->isAction(RIGHT), nbDir);
        }

        moveX(dx, speed, nbDir);

        moveY(dy, speed, nbDir);
    }

    if (isAble && action->isAction(ONILINK) && inventory->hasObject(MASQUE) && !lapin)
    {
        setOniLink(!status->isOniLink(), false);
        isAble = false;
    }

    if (isAble && action->isAction(TELEPORT) && !lapin && status->isOniLink())
    {

        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Map *map = scene->getMap();

        MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(map->getId(), startX, startY, startDir, false, true);
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        return;
    }

    if (isOnIce())
    {

        slide.setMoves(dx, dy, speed);

        if (wasOnIce)
        {

            int oldY = y;
            int oldX = x;

            dy = slide.getSlideY();
            if (dy < 0)
            {
                moveY(-1, -dy, 2);
            }
            else if (dy > 0)
            {
                moveY(1, dy, 2);
            }

            if (dy != 0 && oldY == y)
            {
                slide.stopY();
            }

            dx = slide.getSlideX();
            if (dx < 0)
            {
                moveX(-1, -dx, 2);
            }
            else if (dx > 0)
            {
                moveX(1, dx, 2);
            }

            if (dx != 0 && oldX == x)
            {
                slide.stopX();
            }

            if (grappin != 0 && animation == TIR_GRAPPIN)
            {
                grappin->slide(x - oldX, y - oldY);
            }

            if (flamme != 0 && animation == TIR_LANTERNE)
            {
                flamme->slide(x - oldX, y - oldY);
            }
        }

        wasOnIce = true;
    }
    else if (wasOnIce)
    {
        slide.raz();
        wasOnIce = false;
    }
    else if (animation == WALK && !charge)
    {
        if (prevX == x && prevY == y && accuPush == 0 && nbDir < 2 && !lapin)
        {
            accuPush = 1;
        }
        if ((prevX != x || prevY != y) && accuPush != 0)
        {
            accuPush = 0;
        }
    }
    else if (animation == PUSH)
    {
        BoundingBox pushBox(x, y + 8, 16, 16);
        switch (direction)
        {
        case N:
            pushBox.setY(y);
            break;
        case S:
            pushBox.setY(y + 16);
            break;
        case W:
            pushBox.setX(x - 8);
            break;
        case E:
            pushBox.setX(x + 8);
            break;
        }
        Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        if (scene->checkCollisions(&pushBox, this, false, false, false, false, true, x, y + 8, 16, 16))
        {
            if (isAble)
            {
                setAnimation(WALK);
            }
            else if (porte)
            {
                setAnimation(TRANSPORTE);
            }
        }
    }
}

void Link::loop()
{

    status->loop();

    // if link is dead, nothing to do
    if (status->getVirtualLife() <= 0 && animation != TOUCHE && animation != COULE && animation != ELECTRIC)
    {
        return;
    }

    // hit
    if (status->getVirtualLife() > 0 && epee > 0)
    {
        bool hit = epee->hit(x, y, direction, animation, anim, charge, getForce());
        if (hit && charge)
        {
            charge = 0;
        }
    }

    // check position

    // jump in water
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map *map = scene->getMap();
    Collision c = (Collision)map->getMur(x + 8, y + 16 /*+ 2*/);
    Collision c2 = (Collision)map->getMur(x + 7, y + 15 /*+ 2*/);
    Collision c3 = (Collision)map->getMur(x + 8, y + 15 /*+ 2*/);
    Collision c4 = (Collision)map->getMur(x + 7, y + 16 /*+ 2*/);
    if (c == EAU_PROF && c2 == EAU_PROF && c3 == EAU_PROF && c4 == EAU_PROF && (animation == WALK || animation == IDLE || animation == PUSH || animation == TRANSPORTE || animation == PORTE))
    {
        jumpInWater();
    }

    // jump out water
    if ((animation == NAGE || animation == FLOTTE) && !isOnWater())
    {
        jumpOutWater();
    }
    if ((animation == BARQUE_IDLE || animation == BARQUE) && !isOnWater())
    {
        map->updatePonton(x, y);
        map->barque();
        setAnimation(WALK);
    }

    // fall
    if (animation != CHUTE && animation != TOUCHE && animation != COULE && animation != TIR_GRAPPIN && animation != ELECTRIC)
    {
        if (c == TROU && c2 == TROU && c3 == TROU && c4 == TROU)
        {
            fallInGap();
        }
    }

    // fishing
    if (animation == PECHE)
    {
        int random;
        if (animMax == 0)
        {
            random = rand() % 500;
            if (random == 1)
                animMax = 2;
        }
        else
        {
            random = rand() % 200;
            if (random == 1)
                animMax = 0;
        }
    }

    // update histo
    if (animation != TOUCHE && animation != COULE && animation != TIR_GRAPPIN && animation != ELECTRIC)
    {
        for (int i = 6; i >= 0; i--)
        {
            oldx[i] = oldx[i + 1];
            oldy[i] = oldy[i + 1];
        }
        oldx[7] = x;
        oldy[7] = y;
    }

    if (charge && charge < 21)
    {
        charge++;
        if (charge == 20)
        {
            AudioManager::getInstance()->playSound(TS_SWORDCHARGING);
        }
    }

    map->pickUpItems(getBoundingBox());

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        Equipment equipement;
        switch (animation)
        {
        case WALK:
            if (accuPush > 0)
            {
                accuPush++;
                if (accuPush == 2)
                {
                    setAnimation(PUSH);
                    break;
                }
            }
            if (anim == 0)
                playStep(0);
            else if (anim == 4)
                playStep(1);
            break;
        case PUSH:
            // try to push a pushable object
            if (anim == 0)
            {
                pousse();
            }
            break;
        case TOUCHE:
            computeProjection();
            if (anim == 0)
            {
                setAnimation(IDLE);
                if (status->getVirtualLife() <= 0)
                {
                    AudioManager::getInstance()->playMusic(3);
                }
            }
            break;
        case ELECTRIC:
            if (anim == 0)
            {
                setAnimation(IDLE);
                if (status->getVirtualLife() <= 0)
                {
                    AudioManager::getInstance()->playMusic(3);
                }
            }
            break;
        case NAGE:
            if (anim == 0)
                AudioManager::getInstance()->playSound(TS_NAGE);
            break;
        case COULE:
            if (anim == 0)
            {
                status->setLife(status->getLife() - 1);
                if (status->getVirtualLife() > 0)
                {
                    x = oldx[0];
                    y = oldy[0];
                    setAnimation(IDLE);
                    status->setInvincible();
                }
                else
                {
                    AudioManager::getInstance()->playMusic(3);
                    setAnimation(NOYE);
                }
                return;
            }
            break;
        case CHUTE:
            if (anim == 0)
            {
                if (map->getId() == 21)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(63, 6 * 16 + 8, 6 * 16, S, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 26)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(47, 169 * 16 + 8, 19 * 16 + 8, S, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 27)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(67, 9 * 16 + 8, 21 * 16 + 8, S, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 48 && x < 280 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(48, x + 140 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() >= 50 && map->getId() <= 52 && x < 20 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(map->getId(), x + 40 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() >= 50 && map->getId() <= 52 && x < 80 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(map->getId(), x + 80 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() >= 50 && map->getId() <= 52 && x < 180 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(map->getId(), x + 120 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 53 && x >= 80 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, x - 80 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 53 && x < 80 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(53, x + 80 * 16, y + 60 * 16, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 54)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(54, x + 120 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 59)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(59, x - 80 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 78 && x >= 60 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(78, x - 60 * 16, y, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else if (map->getId() == 156 && y < 225 * 16)
                {
                    setAnimation(NOYE);
                    MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(156, x, y + 75 * 16, S, false, false, true);
                    MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
                }
                else
                {
                    if (map->getId() == 48 || map->getId() == 55 || map->getId() == 68 || map->getId() == 155)
                    { // lave
                        status->setLife(status->getLife() - 2);
                    }
                    else
                    {
                        status->setLife(status->getLife() - 1);
                    }
                    if (status->getVirtualLife() > 0)
                    {
                        x = startX2;
                        y = startY2;
                        direction = startDir2;
                        setAnimation(IDLE);
                        status->setInvincible();
                    }
                    else
                    {
                        AudioManager::getInstance()->playMusic(3);
                        setAnimation(NOYE);
                    }
                }
                return;
            }
            break;
        case HIT_EPEE:
            if (anim == 0)
            {
                if (charging)
                {
                    charge = 1;
                }
                setAnimation(IDLE);
            }
            break;
        case SPIN_EPEE:
        case THROW:
        case TIR_LANTERNE:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            break;
        case TIR_ARC:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            equipement = inventory->getCurrent();
            if (anim == 2 && status->getArrows() && (status->getVirtualMagic() >= 8 || (equipement != FLECHE_FEU && equipement != FLECHE_GLACE)) && (status->getVirtualMagic() >= 16 || equipement != FLECHE_LUMIERE))
            {
                int a = 0;
                int b = 0;
                switch (direction)
                {
                case N:
                    a = x + 4;
                    b = y;
                    break;
                case S:
                    a = x + 6;
                    b = y + 16;
                    break;
                case W:
                    a = x - 4;
                    b = y + 11;
                    break;
                case E:
                    a = x + 4;
                    b = y + 11;
                    break;
                }
                TypeProjectile type;
                switch (equipement)
                {
                default:
                case ARC:
                    type = TP_ARROW;
                    AudioManager::getInstance()->playSound(TS_SHOOT);
                    break;
                case ARC_FEE:
                    type = TP_ARROW_2;
                    AudioManager::getInstance()->playSound(TS_SHOOT);
                    break;
                case FLECHE_FEU:
                    type = TP_ARROW_FIRE;
                    AudioManager::getInstance()->playSound(TS_MAGIC);
                    break;
                case FLECHE_GLACE:
                    type = TP_ARROW_ICE;
                    AudioManager::getInstance()->playSound(TS_MAGIC);
                    break;
                case FLECHE_LUMIERE:
                    type = TP_ARROW_LIGHT;
                    AudioManager::getInstance()->playSound(TS_MAGIC);
                    break;
                }
                ProjectileHelper::getInstance()->addProjectile(type, a, b, direction);
                status->setArrows(status->getArrows() - 1);
                if (equipement == FLECHE_FEU || equipement == FLECHE_GLACE)
                {
                    status->updateMagic(-8);
                }
                if (equipement == FLECHE_LUMIERE)
                {
                    status->updateMagic(-16);
                }
            }
            break;
        case TRANSPORTE:
            if (anim == 0)
                playStep(0);
            else if (anim == 2)
                playStep(1);
            break;
        case SOULEVE:
            if (anim == 0)
            {
                Portable *p = getPortable();
                if (p != 0 && p->getPoids() <= status->getMaxWeight())
                {
                    TasDePierres *pierres = dynamic_cast<TasDePierres *>(p);
                    if (pierres != 0)
                    {
                        p = pierres->getPierre();
                    }
                    else
                    {
                        p->onLift();
                        map->removeObject(p);
                    }
                    porte = p;
                    setAnimation(PORTE);
                    AudioManager::getInstance()->playSound(TS_PORTE);
                }
                else
                {
                    porte = 0;
                    setAnimation(IDLE);
                }
            }
            break;
        case TIR_BAGUETTE_FEU:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            if (anim == 2 && status->getVirtualMagic() >= 4)
            {
                int a = 0;
                int b = 0;
                switch (direction)
                {
                case N:
                    a = x;
                    b = y;
                    break;
                case S:
                    a = x;
                    b = y + 16;
                    break;
                case W:
                    a = x - 16 + 1;
                    b = y + 8;
                    break;
                case E:
                    a = x + 16 - 1 - 4;
                    b = y + 8;
                    break;
                }
                ProjectileHelper::getInstance()->addProjectile(TP_BAGUETTE_FEU, a, b, direction);
                AudioManager::getInstance()->playSound(TS_BAGUETTE_FEU);
                status->updateMagic(-4);
            }
            break;
        case TIR_BAGUETTE_GLACE:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            if (anim == 2 && status->getVirtualMagic() >= 4)
            {
                int a = 0;
                int b = 0;
                switch (direction)
                {
                case N:
                    a = x;
                    b = y;
                    break;
                case S:
                    a = x;
                    b = y + 16;
                    break;
                case W:
                    a = x - 16 + 1;
                    b = y + 8;
                    break;
                case E:
                    a = x + 16 - 1 - 4;
                    b = y + 8;
                    break;
                }
                ProjectileHelper::getInstance()->addProjectile(TP_BAGUETTE_GLACE, a, b, direction);
                AudioManager::getInstance()->playSound(TS_BAGUETTE_GLACE);
                status->updateMagic(-4);
            }
            break;
        case TIR_MARTEAU:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            else if (anim == 2)
            {
                BoundingBox bb;
                bb.setW(16);
                bb.setH(16);
                switch (direction)
                {
                case N:
                    bb.setX(x);
                    bb.setY(y - 8);
                    break;
                case S:
                    bb.setX(x);
                    bb.setY(y + 24);
                    break;
                case W:
                    bb.setX(x - 16);
                    bb.setY(y + 8);
                    break;
                case E:
                    bb.setX(x + 16);
                    bb.setY(y + 8);
                    break;
                }
                MainController::getInstance()->getGameController()->getSceneController()->getScene()->testDegat(&bb, direction, 3, TA_MARTEAU, TE_NORMAL);
                AudioManager::getInstance()->playSound(TS_MARTEAU);
            }
            break;
        case BOIT_POTION:
            if (anim == 0)
            {
                setAnimation(IDLE);
            }
            if (anim == 2)
            {
                switch (inventory->getCurrentFlacon())
                {
                case 1: // rouge
                    status->updateLife(status->getMaxLife() - status->getVirtualLife());
                    if (status->getLife() == status->getMaxLife())
                    {
                        AudioManager::getInstance()->playSound(TS_ITEM);
                    }
                    break;
                case 2: // verte
                    status->updateMagic(status->getMaxMagic() - status->getVirtualMagic());
                    if (status->getMagic() == status->getMaxMagic())
                    {
                        AudioManager::getInstance()->playSound(TS_ITEM);
                    }
                    else
                    {
                        AudioManager::getInstance()->playSound(TS_MAGICCHARGE);
                    }
                    break;
                case 3: // bleue
                    status->updateLife(status->getMaxLife() - status->getVirtualLife());
                    status->updateMagic(status->getMaxMagic() - status->getVirtualMagic());
                    if (status->getMagic() == status->getMaxMagic() && status->getLife() == status->getMaxLife())
                    {
                        AudioManager::getInstance()->playSound(TS_ITEM);
                    }
                    else if (status->getMagic() != status->getMaxMagic())
                    {
                        AudioManager::getInstance()->playSound(TS_MAGICCHARGE);
                    }
                    break;
                default:
                    break;
                }
                inventory->setCurrentFlacon(0);
            }
            break;
        case BARQUE:
            if (anim == 0)
                AudioManager::getInstance()->playSound(TS_NAGE);
            break;
        case JUMP_IN_WAGON:
            if (anim == 0)
            {
                setAnimation(WAGON);
            }
            break;
        case JUMP_OUT_WAGON:
            if (anim == 0)
            {
                setAnimation(IDLE);
                startNewRoom(false);
            }
            break;
        default:
            break;
        }

        recup++;
        if (recup == 50)
        {
            if (inventory->hasObject(RECUP_BOMBE))
            {
                status->setBombs(status->getBombs() + 1);
            }
            if (inventory->hasObject(RECUP_FLECHE))
            {
                status->setArrows(status->getArrows() + 1);
            }
            if (bouclier != 0 && bouclier->getLevel() == 4)
            {
                status->updateLife(1);
            }
            if (tunique == 4)
            {
                status->updateMagic(status->getMaxMagic() == 64 ? 8 : 4);
            }
            recup = 0;
        }

        chrono.reset();
    }

    if (animation == IDLE && c == EAU_PROF && c2 == EAU_PROF && c3 == EAU_PROF && c4 == EAU_PROF)
    {
        // plouf
        AudioManager::getInstance()->playSound(TS_PLOUF);
        map->addEffect(new Plouf(x, y));

        if (inventory->hasObject(PALMES) && !lapin && inventory->getTrocGemme(0) != TGR_ENCLUME)
        {
            setAnimation(FLOTTE);
        }
        else
        {
            setAnimation(COULE);
        }
    }

    if (porte != 0 && animation != SOULEVE)
    {
        if (!porte->isAlive())
        {
            delete porte;
            porte = 0;
            if (animation == PORTE)
            {
                setAnimation(IDLE);
            }
            else
            {
                setAnimation(WALK);
            }
        }
        else
        {
            porte->portLoop();
        }
    }

    if (grappin != 0)
    {
        if (animation == TIR_GRAPPIN)
        {
            grappin->projLoop();
        }
        else
        {
            delete grappin;
            grappin = 0;
        }
    }

    if (flamme != 0)
    {
        if (animation == TIR_LANTERNE)
        {
            flamme->loop();
        }
        else
        {
            delete flamme;
            flamme = 0;
        }
    }
}

void Link::draw(int offsetX, int offsetY)
{

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    int dstX2 = dstX;

    if (status->getVirtualLife() > 0 &&
        (animation == IDLE || animation == WALK ||
         animation == SPIN_EPEE || animation == TIR_ARC))
    {
        if (direction == W)
        {
            dstX2 = dstX + 2;
        }
        else if (direction == E)
        {
            dstX2 = dstX - 2;
        }
    }

    if (status->getVirtualLife() > 0 && direction == N && bouclier > 0 && animation != HIT_EPEE && !charge && !lapin)
    {
        bouclier->draw(dstX2, dstY, direction, animation, anim, 0);
    }

    if (status->getVirtualLife() > 0 && epee > 0 && animation == SPIN_EPEE)
    {
        if ((direction == N && anim >= 9 && anim <= 12) || (direction == S && anim >= 5 && anim <= 17) || (direction == W && anim >= 13 && anim <= 16) || (direction == E && anim >= 6 && anim <= 8))
            epee->draw(dstX2, dstY, direction, animation, anim, charge);
    }

    switch (animation)
    {
    case IDLE:
        if (status->getVirtualLife() <= 0)
            drawDead(dstX2, dstY);
        else if (charge)
            drawCharge(dstX2, dstY);
        else
            drawIdle(dstX2, dstY);
        break;
    case WALK:
        if (charge)
            drawCharge(dstX2, dstY);
        else
            drawWalk(dstX2, dstY);
        break;
    case PUSH:
        drawPush(dstX2, dstY);
        break;
    case TOUCHE:
        drawTouche(dstX2, dstY);
        break;
    case ELECTRIC:
        drawElectric(dstX2, dstY);
        break;
    case FLOTTE:
    case NAGE:
        if (status->getVirtualLife() > 0)
            drawFlotte(dstX2, dstY);
        break;
    case COULE:
        drawCoule(dstX2, dstY);
        break;
    case CHUTE:
        drawChute(dstX2, dstY);
        break;
    case HIT_EPEE:
        drawEpee(dstX2, dstY);
        break;
    case SPIN_EPEE:
        drawSpin(dstX2, dstY);
        break;
    case TROUVE_SIMPLE:
        drawTrouveSimple(dstX2, dstY);
        break;
    case TROUVE_DOUBLE:
        drawTrouveDouble(dstX2, dstY);
        break;
    case TIR_ARC:
        drawArc(dstX2, dstY);
        break;
    case PORTE:
    case TRANSPORTE:
        drawPorte(dstX2, dstY, offsetX, offsetY);
        break;
    case THROW:
        drawThrow(dstX2, dstY);
        break;
    case SOULEVE:
        drawSouleve(dstX2, dstY);
        break;
    case TIR_GRAPPIN:
        drawGrappin(dstX2, dstY, offsetX, offsetY);
        break;
    case TIR_BAGUETTE_FEU:
    case TIR_BAGUETTE_GLACE:
    case TIR_MARTEAU:
        drawBaguette(dstX2, dstY);
        break;
    case TIR_LANTERNE:
        drawLanterne(dstX2, dstY, offsetX, offsetY);
        break;
    case BOIT_POTION:
        drawFlacon(dstX2, dstY);
        break;
    case JOUE_OCARINA:
        drawOcarina(dstX2, dstY);
        break;
    case PECHE:
        drawPeche(dstX2, dstY);
        break;
    case BARQUE_IDLE:
    case BARQUE:
        drawBarquee(dstX2, dstY);
        break;
    case JUMP_IN_WAGON:
        drawTouche(dstX2, dstY);
        break;
    case WAGON:
        drawWagon(dstX2, dstY);
        break;
    case JUMP_OUT_WAGON:
        drawTouche(dstX2, dstY);
        break;
    default:
        break;
    }

    if (animation != TOUCHE && animation != CHUTE && animation != ELECTRIC)
    {
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        Collision c = (Collision)map->getMur(x + 7, y + 16);
        if (c == HERBE_HAUTE)
        {
            int tmp = (animation == WALK) ? (anim / 2) : 0;
            WindowManager::getInstance()->draw(imageEffets, tmp * 16, 0, 16, 8, dstX, dstY + 16);
        }
        if (c == EAU || (c == EAU_PROF && ((Collision)map->getMur(x + 8, y + 16)) == EAU))
        {
            int offset = map->getEpoque() == EP_FUTUR ? 45 : 0;
            int tmp = (metronome->getValue() / 2) % 4;
            WindowManager::getInstance()->draw(imageEffets, tmp * 16, 8 + offset, 16, 8, dstX, dstY + 16);
        }
    }

    if (status->getVirtualLife() > 0 && (direction != N || animation == HIT_EPEE || charge) && bouclier > 0 && !lapin)
    {
        bouclier->draw(dstX2, dstY, direction, animation, anim, charge);
    }

    if (status->getVirtualLife() > 0 && epee > 0)
    {
        if (animation != SPIN_EPEE || !(
                                          (direction == N && anim >= 9 && anim <= 12) || (direction == S && anim >= 5 && anim <= 17) || (direction == W && anim >= 13 && anim <= 16) || (direction == E && anim >= 6 && anim <= 8)))
            epee->draw(dstX2, dstY, direction, animation, anim, charge);
    }
}

void Link::setAnimation(Animation newAnim)
{
    if (animation == newAnim)
    {
        return;
    }
    if (porte != 0 && animation == SOULEVE && (newAnim == TOUCHE || newAnim == CHUTE || newAnim == ELECTRIC))
    {
        porte = 0;
    }

    accuPush = 0;
    animation = newAnim;
    anim = 0;
    animMax = 0;
    switch (animation)
    { // animMax = nbAnim - 1
    case WALK:
        anim = 0;
        animMax = 7;
        vanim = 90;
        playStep(0);
        break;
    case PUSH:
        anim = 0;
        animMax = 14;
        vanim = 80;
        break;
    case TOUCHE:
        anim = 0;
        animMax = 9;
        vanim = 30;
        charge = 0;
        if (porte != 0)
            lacheObj();
        break;
    case ELECTRIC:
        anim = 0;
        animMax = 9;
        vanim = 90;
        charge = 0;
        if (porte != 0)
            lacheObj();
        break;
    case FLOTTE:
        anim = 0;
        animMax = 1;
        vanim = 240;
        break;
    case NAGE:
        anim = 0;
        animMax = 3;
        vanim = 240;
        AudioManager::getInstance()->playSound(TS_NAGE);
        break;
    case COULE:
        anim = 0;
        animMax = 4;
        vanim = 240;
        break;
    case CHUTE:
        anim = 0;
        animMax = 5;
        vanim = 240;
        charge = 0;
        if (porte != 0)
            lacheObj();
        break;
    case HIT_EPEE:
        anim = 0;
        animMax = 4;
        vanim = 45;
        break;
    case SPIN_EPEE:
        anim = 0;
        animMax = 30;
        vanim = 10;
        break;
    case TIR_ARC:
        anim = 0;
        animMax = 2;
        vanim = 120;
        break;
    case TRANSPORTE:
        anim = 0;
        animMax = 3;
        vanim = 180;
        playStep(0);
        break;
    case THROW:
        anim = 0;
        animMax = 0;
        vanim = 120;
        break;
    case SOULEVE:
        anim = 0;
        animMax = 1;
        vanim = 180;
        break;
    case TIR_GRAPPIN:
        anim = 0;
        animMax = 0;
        vanim = 240;
        for (int i = 0; i < 8; i++)
        {
            oldx[i] = x;
            oldy[i] = y;
        }
        break;
    case TIR_BAGUETTE_FEU:
    case TIR_BAGUETTE_GLACE:
        anim = 0;
        animMax = 2;
        vanim = 120;
        break;
    case TIR_LANTERNE:
        anim = 0;
        animMax = 3;
        vanim = 240;
        break; // to avoid problem if 'enter' is pressed
    case TIR_MARTEAU:
        anim = 0;
        animMax = 2;
        vanim = 120;
        break;
    case BOIT_POTION:
        anim = 0;
        animMax = 2;
        vanim = 360;
        break;
    case JOUE_OCARINA:
        anim = 0;
        animMax = 0;
        direction = S;
        break;
    case PECHE:
        anim = 0;
        animMax = 0;
        direction = S;
        vanim = 240;
        break;
    case BARQUE_IDLE:
        if (porte != 0)
            lacheObj();
        anim = 0;
        animMax = 1;
        vanim = 240;
        break;
    case BARQUE:
        if (porte != 0)
            lacheObj();
        anim = 0;
        animMax = 1;
        vanim = 240;
        AudioManager::getInstance()->playSound(TS_NAGE);
        break;
    case JUMP_IN_WAGON:
    case JUMP_OUT_WAGON:
        status->setInvincible();
        anim = 0;
        animMax = 9;
        vanim = 30;
        charge = 0;
        if (porte != 0)
            lacheObj();
        break;
    default:
        break;
    }
    chrono.reset();
}

void Link::findDirection(bool up, bool down, bool left, bool right, int nb_dir)
{

    switch (nb_dir)
    {
    case 1:
        if (up)
        {
            direction = N;
            break;
        }
        if (down)
        {
            direction = S;
            break;
        }
        if (left)
        {
            direction = W;
            break;
        }
        if (right)
        {
            direction = E;
            break;
        }
        break;
    case 2:
        if (up && direction != N)
        {
            if (left && direction != W)
            {
                direction = N;
                break;
            }
            if (right && direction != E)
            {
                direction = N;
                break;
            }
            break;
        }
        if (down && direction != S)
        {
            if (left && direction != W)
            {
                direction = S;
                break;
            }
            if (right && direction != E)
            {
                direction = S;
                break;
            }
            break;
        }
        break;
    case 3:
        if (!up)
        {
            direction = S;
            break;
        }
        if (!down)
        {
            direction = N;
            break;
        }
        if (!left)
        {
            direction = E;
            break;
        }
        if (!right)
        {
            direction = W;
            break;
        }
        break;
    default:
        break;
    }
}

void Link::pousseX(int dx)
{
    int oldX = x;
    int oldY = y;
    moveX(dx, 2, 1);
    if (oldX != x || oldY != y)
    {
        if (grappin != 0 && animation == TIR_GRAPPIN)
        {
            grappin->slide(x - oldX, y - oldY);
        }
        if (flamme != 0 && animation == TIR_LANTERNE)
        {
            flamme->slide(x - oldX, y - oldY);
        }
    }
}

void Link::pousseY(int dy)
{
    int oldX = x;
    int oldY = y;
    moveY(dy, 2, 1);
    if (oldX != x || oldY != y)
    {
        if (grappin != 0 && animation == TIR_GRAPPIN)
        {
            grappin->slide(x - oldX, y - oldY);
        }
        if (flamme != 0 && animation == TIR_LANTERNE)
        {
            flamme->slide(x - oldX, y - oldY);
        }
    }
}

void Link::moveX(int dx, int vitesse, int nbDir)
{

    int v = vitesse;
    if (dx != 0)
    {
        int modX = x % vitesse;
        if (modX != 0)
        {
            if (dx > 0)
            {
                v -= modX;
            }
            else
            {
                v = modX;
            }
        }
    }

    dx *= v;
    BoundingBox *bb = getBoundingBox();
    bb->setX(x + dx);

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->checkCollisions(bb, this, false, false, false, false, true, x, y + 8, 16, 16, true))
    {
        x += dx;
        moved = true;
    }
    else if (nbDir == 1)
    {

        int mod = y % 8;

        bb->setY(y + 8 - (mod == 0 ? 8 : mod));
        if (scene->checkCollisions(bb, this, false))
        {
            moveY(-1, vitesse, 0);
        }
        else
        {
            bb->setY(y + 8 + 8 - mod);
            if (scene->checkCollisions(bb, this, false))
            {
                moveY(1, vitesse, 0);
            }
        }
    }
}

void Link::moveY(int dy, int vitesse, int nbDir)
{

    int v = vitesse;
    if (dy != 0)
    {
        int modY = y % vitesse;
        if (modY != 0)
        {
            if (dy > 0)
            {
                v -= modY;
            }
            else
            {
                v = modY;
            }
        }
    }

    dy *= v;
    BoundingBox *bb = getBoundingBox();
    bb->setY(y + dy + 8);

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->checkCollisions(bb, this, false, false, false, false, true, x, y + 8, 16, 16, true))
    {
        y += dy;
        moved = true;
    }
    else if (nbDir == 1)
    {

        int mod = x % 8;

        bb->setX(x - (mod == 0 ? 8 : mod));
        if (scene->checkCollisions(bb, this, false))
        {
            moveX(-1, vitesse, 0);
        }
        else
        {
            bb->setX(x + 8 - mod);
            if (scene->checkCollisions(bb, this, false))
            {
                moveX(1, vitesse, 0);
            }
        }
    }
}

bool Link::hasMoved()
{
    return moved;
}

/**
 * id have to be between 0 and 1
 */
void Link::playStep(int id)
{

    Collision c = (Collision)MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getMur(x + 7, y + 16 /*+ 2*/);

    int type = getSoundForCollision(c, id);

    if (type == -1)
    {
        c = (Collision)MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->getMur(x + 8, y + 15 /*+ 2*/);
        type = getSoundForCollision(c, id);
    }

    if (type == -1)
    {
        return;
    }

    AudioManager::getInstance()->playSound(type);
}

int Link::getSoundForCollision(Collision c, int id)
{
    int type = -1;

    switch (c)
    {
    case HERBE:
        type = id == 0 ? TS_STEP_GRASS1 : TS_STEP_GRASS2;
        break;
    case HERBE_HAUTE:
        type = id == 0 ? TS_STEP_TALLGRASS1 : TS_STEP_TALLGRASS2;
        break;
    case TERRE:
        type = id == 0 ? TS_STEP_DIRT1 : TS_STEP_DIRT2;
        break;
    case GLACE:
        type = id == 0 ? TS_STEP_ICE1 : TS_STEP_ICE2;
        break;
    case EAU:
        type = id == 0 ? TS_STEP_WATER1 : TS_STEP_WATER2;
        break;
    case SABLE:
        type = id == 0 ? TS_STEP_SAND1 : TS_STEP_SAND2;
        break;
    case PIERRE:
        type = id == 0 ? TS_STEP_STONE1 : TS_STEP_STONE2;
        break;
    case SOL_BOIS:
        type = id == 0 ? TS_STEP_WOOD1 : TS_STEP_WOOD2;
        break;
    case TAPIS:
        type = id == 0 ? TS_STEP_CARPET1 : TS_STEP_CARPET2;
        break;
    case NEIGE:
        type = id == 0 ? TS_STEP_SNOW1 : TS_STEP_SNOW2;
        break;
    default:
        break;
    }
    return type;
}

void Link::jumpInWater()
{

    AudioManager::getInstance()->playSound(TS_JUMP);
    setAnimation(TOUCHE);

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    toucheX = 0;
    toucheY = 0;

    if ((Collision)map->getMur(x + 7, y + 8) != EAU_PROF || (Collision)map->getMur(x + 8, y + 8) != EAU_PROF)
    {
        toucheY = 1;
    }
    else if ((Collision)map->getMur(x + 7, y + 23) != EAU_PROF || (Collision)map->getMur(x + 8, y + 23) != EAU_PROF)
    {
        toucheY = -1;
    }

    if ((Collision)map->getMur(x, y + 15) != EAU_PROF || (Collision)map->getMur(x, y + 16) != EAU_PROF)
    {
        toucheX = 1;
    }
    else if ((Collision)map->getMur(x + 16, y + 15) != EAU_PROF || (Collision)map->getMur(x + 16, y + 16) != EAU_PROF)
    {
        toucheX = -1;
    }

    if (toucheX == 0 && toucheY == 0)
    {
        if ((Collision)map->getMur(x, y + 8) != EAU_PROF)
        {
            toucheX = 1;
            toucheY = 1;
        }
        if ((Collision)map->getMur(x + 15, y + 8) != EAU_PROF)
        {
            toucheX = -1;
            toucheY = 1;
        }
        if ((Collision)map->getMur(x, y + 15 + 8) != EAU_PROF)
        {
            toucheX = 1;
            toucheY = -1;
        }
        if ((Collision)map->getMur(x + 15, y + 15 + 8) != EAU_PROF)
        {
            toucheX = -1;
            toucheY = -1;
        }
    }
}

void Link::jumpOutWater()
{
    AudioManager::getInstance()->playSound(TS_JUMP);
    setAnimation(TOUCHE);

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    toucheX = 0;
    toucheY = 0;

    if ((Collision)map->getMur(x + 7, y + 8) != EAU_PROF || (Collision)map->getMur(x + 8, y + 8) != EAU_PROF)
    {
        toucheY = -1;
    }
    else if ((Collision)map->getMur(x + 7, y + 23) != EAU_PROF || (Collision)map->getMur(x + 8, y + 23) != EAU_PROF)
    {
        toucheY = 1;
    }

    if ((Collision)map->getMur(x, y + 15) != EAU_PROF || (Collision)map->getMur(x, y + 16) != EAU_PROF)
    {
        toucheX = -1;
    }
    else if ((Collision)map->getMur(x + 15, y + 15) != EAU_PROF || (Collision)map->getMur(x + 15, y + 16) != EAU_PROF)
    {
        toucheX = 1;
    }

    if (toucheX == 0 && toucheY == 0)
    {
        if ((Collision)map->getMur(x, y + 8) != EAU_PROF)
        {
            toucheX = -1;
            toucheY = -1;
        }
        if ((Collision)map->getMur(x + 15, y + 8) != EAU_PROF)
        {
            toucheX = 1;
            toucheY = -1;
        }
        if ((Collision)map->getMur(x, y + 15 + 8) != EAU_PROF)
        {
            toucheX = -1;
            toucheY = 1;
        }
        if ((Collision)map->getMur(x + 15, y + 15 + 8) != EAU_PROF)
        {
            toucheX = 1;
            toucheY = 1;
        }
    }
}

void Link::computeProjection()
{
    if (toucheY != 0)
    {
        int prevY = y;
        moveY(toucheY, 2, 1);
        if (prevY == y)
            toucheY = 0;
    }
    if (toucheX != 0)
    {
        int prevX = x;
        moveX(toucheX, 2, 1);
        if (prevX == x)
            toucheX = 0;
    }
}

void Link::fallInGap()
{

    if (isOnGap())
    {
        setAnimation(CHUTE);
        AudioManager::getInstance()->playSound(TS_FALL);
        return;
    }

    if (metronome->getValue() % 2 == 0)
    {
        return;
    }

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    int tombeX = 0;
    int tombeY = 0;

    if ((Collision)map->getMur(x + 8, y + 8) != TROU)
    {
        tombeY = 1;
    }
    if ((Collision)map->getMur(x + 8, y + 23) != TROU)
    {
        tombeY = -1;
    }
    if ((Collision)map->getMur(x, y + 16) != TROU)
    {
        tombeX = 1;
    }
    if ((Collision)map->getMur(x + 15, y + 16) != TROU)
    {
        tombeX = -1;
    }

    if (tombeY != 0)
    {
        moveY(tombeY, 1, 1);
    }
    if (tombeX != 0)
    {
        moveX(tombeX, 1, 1);
    }
}

Animation Link::getAnimation()
{
    return animation;
}

BoundingBox *Link::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 8);
    box.setW(w);
    box.setH(h - 8);
    return &box;
}

Status *Link::getStatus() { return status; }
Inventory *Link::getInventory() { return inventory; }

int Link::getX() { return x; }
int Link::getY() { return y; }
int Link::getW() { return w; }
int Link::getH() { return h; }
Direction Link::getDirection() { return direction; }

void Link::setX(int i) { x = i; }
void Link::setY(int j) { y = j; }
void Link::setDirection(Direction dir) { direction = dir; }

int Link::getTunique() { return tunique; }
int Link::getEpee() { return (epee == 0 ? 0 : epee->getForce()); }
int Link::getBouclier() { return (bouclier == 0 ? 0 : bouclier->getLevel()); }

void Link::setTunique(int i)
{
    tunique = i;
    if (!status->isOniLink())
    {
        ResourceManager::getInstance()->free(imageLink);
        ostringstream os;
        os << ConfigurationManager::getInstance()->getSkinName() << tunique;
        string filename = "data/images/link/link" + os.str() + ".png";
        imageLink = ResourceManager::getInstance()->loadImage(filename, true);
    }
}

void Link::setEpee(int i)
{
    delete epee;
    epee = 0;
    if (i > 0 && i < 6)
    {
        epee = new Sword(i, status->isOniLink());
    }
}

void Link::setBouclier(int i)
{
    delete bouclier;
    if (i > 0 && i < 5)
    {
        bouclier = new Shield(i, status->isOniLink());
    }
}

bool Link::isAbleToChangeStuff()
{
    return animation != TIR_ARC && animation != TIR_GRAPPIN && animation != TIR_BAGUETTE_FEU && animation != TIR_BAGUETTE_GLACE && animation != TIR_LANTERNE && animation != TIR_MARTEAU && animation != BOIT_POTION && animation != JOUE_OCARINA && animation != PECHE && !lapin;
}

void Link::trouveObjet(TypeItem type, int id)
{
    AudioManager::getInstance()->playSound(TS_HAPPY, 2);

    int tmp = 0;
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (type)
    {
    case TI_QUART_COEUR:
        inventory->setQuartCoeur(id);
        if (inventory->nbQuartCoeur() == 0)
        {
            status->setMaxLife(status->getMaxLife() + 2);
        }
        status->updateLife(status->getMaxLife() - status->getLife());
        MainController::getInstance()->getGameController()->displayText(100);
        break;
    case TI_COEUR:
        inventory->setCoeur(id);
        status->setMaxLife(status->getMaxLife() + 2);
        status->updateLife(status->getMaxLife() - status->getLife());
        MainController::getInstance()->getGameController()->displayText(1224);
        break;
    case TI_CRISTAL:
        inventory->setCristal(id);
        MainController::getInstance()->getGameController()->displayText(414);
        break;
    case TI_MEDAILLON_1:
        inventory->setMedaillon(0);
        MainController::getInstance()->getGameController()->displayText(1226);
        break;
    case TI_MEDAILLON_2:
        inventory->setMedaillon(1);
        MainController::getInstance()->getGameController()->displayText(1227);
        break;
    case TI_MEDAILLON_3:
        inventory->setMedaillon(2);
        MainController::getInstance()->getGameController()->displayText(1228);
        break;
    case TI_CLE_TEMPS:
        inventory->setObject(CLE_TEMPS);
        MainController::getInstance()->getGameController()->displayText(1257);
        break;
    case TI_GEMME_ROUGE:
        inventory->setObject(TROC_GEMME_ROUGE);
        MainController::getInstance()->getGameController()->displayText(1267);
        break;
    case TI_GEMME_BLEUE:
        inventory->setObject(TROC_GEMME_BLEUE);
        MainController::getInstance()->getGameController()->displayText(1265);
        break;
    case TI_GEMME_JAUNE:
        inventory->setObject(TROC_GEMME_JAUNE);
        MainController::getInstance()->getGameController()->displayText(1260);
        break;
    case TI_GEMME_VERTE:
        inventory->setObject(TROC_GEMME_VERTE);
        MainController::getInstance()->getGameController()->displayText(1263);
        break;
    case TI_FLACON_1:
        inventory->setObject(FLACON_1);
        MainController::getInstance()->getGameController()->displayText(645);
        break;
    case TI_FLACON_2:
        inventory->setObject(FLACON_2);
        MainController::getInstance()->getGameController()->displayText(645);
        break;
    case TI_FLACON_3:
        inventory->setObject(FLACON_3);
        MainController::getInstance()->getGameController()->displayText(645);
        break;
    case TI_FLACON_4:
        inventory->setObject(FLACON_4);
        MainController::getInstance()->getGameController()->displayText(645);
        break;
    case TI_FLECHE_FEU:
        inventory->setObject(FLECHE_FEU);
        MainController::getInstance()->getGameController()->displayText(829);
        break;
    case TI_FLECHE_GLACE:
        inventory->setObject(FLECHE_GLACE);
        MainController::getInstance()->getGameController()->displayText(835);
        break;
    case TI_FLECHE_LUMIERE:
        inventory->setObject(FLECHE_LUMIERE);
        MainController::getInstance()->getGameController()->displayText(840);
        break;
    case TI_CANNE_A_PECHE_1:
        inventory->setObject(CANNE_A_PECHE_1);
        MainController::getInstance()->getGameController()->displayText(730);
        break;
    case TI_CANNE_A_PECHE_2:
        inventory->setObject(CANNE_A_PECHE_2);
        MainController::getInstance()->getGameController()->displayText(743);
        break;
    case TI_CANNE_A_PECHE_3:
        inventory->setObject(CANNE_A_PECHE_3);
        MainController::getInstance()->getGameController()->displayText(746);
        break;
    case TI_GEMME_FORCE:
        inventory->setGemmeForce(id);
        MainController::getInstance()->getGameController()->displayText(238);
        break;
    case TI_BOUCLIER_1:
        setBouclier(1);
        MainController::getInstance()->getGameController()->displayText(1307);
        break;
    case TI_BOUCLIER_2:
        setBouclier(2);
        MainController::getInstance()->getGameController()->displayText(579);
        break;
    case TI_BOUCLIER_3:
        setBouclier(3);
        MainController::getInstance()->getGameController()->displayText(1268);
        break;
    case TI_BOUCLIER_4:
        setBouclier(4);
        MainController::getInstance()->getGameController()->displayText(1627);
        break;
    case TI_TUNIQUE_BLEUE:
        MainController::getInstance()->getGameController()->displayText(1256);
        break;
    case TI_TUNIQUE_ROUGE:
        MainController::getInstance()->getGameController()->displayText(1363);
        break;
    case TI_TUNIQUE_BLANCHE:
        MainController::getInstance()->getGameController()->displayText(1632);
        break;
    case TI_CHANT_1:
        inventory->setObject(CHANT_1);
        MainController::getInstance()->getGameController()->displayText(1160);
        break;
    case TI_CHANT_2:
        inventory->setObject(CHANT_2);
        MainController::getInstance()->getGameController()->displayText(1161);
        break;
    case TI_CHANT_3:
        inventory->setObject(CHANT_3);
        MainController::getInstance()->getGameController()->displayText(1162);
        break;
    case TI_EPEE_1:
        setEpee(1);
        MainController::getInstance()->getGameController()->displayText(558);
        break;
    case TI_EPEE_2:
        setEpee(2);
        MainController::getInstance()->getGameController()->displayText(573);
        break;
    case TI_EPEE_3:
        setEpee(3);
        MainController::getInstance()->getGameController()->displayText(1004);
        break;
    case TI_EPEE_5:
        setEpee(5);
        MainController::getInstance()->getGameController()->displayText(1295);
        break;
    case TI_SAC_BOMBES:
        inventory->setObject(BOMBES);
        status->setMaxBombs(10);
        status->setBombs(10);
        MainController::getInstance()->getGameController()->displayText(354);
        break;
    case TI_GANT:
        inventory->setObject(GANTS);
        MainController::getInstance()->getGameController()->displayText(1229);
        break;
    case TI_GANT2:
        inventory->setObject(GANTS_2);
        inventory->setCurrent(inventory->getCurrent()); // force refresh
        MainController::getInstance()->getGameController()->displayText(1259);
        break;
    case TI_ARC:
        inventory->setObject(ARC);
        status->setArrows(30);
        MainController::getInstance()->getGameController()->displayText(1225);
        break;
    case TI_ARC_FEE:
        inventory->setObject(ARC_FEE);
        status->setArrows(status->getMaxArrows());
        inventory->setCurrent(inventory->getCurrent()); // force refresh
        MainController::getInstance()->getGameController()->displayText(1262);
        break;
    case TI_ARC_OR:
        inventory->setObject(ARC_OR);
        MainController::getInstance()->getGameController()->displayText(1296);
        break;
    case TI_PALMES:
        inventory->setObject(PALMES);
        MainController::getInstance()->getGameController()->displayText(1251);
        break;
    case TI_OCARINA:
        inventory->setObject(OCARINA);
        MainController::getInstance()->getGameController()->displayText(1329);
        break;
    case TI_MARTEAU:
        inventory->setObject(MARTEAU);
        MainController::getInstance()->getGameController()->displayText(1258);
        break;
    case TI_BOTTES:
        inventory->setObject(BOTTES);
        MainController::getInstance()->getGameController()->displayText(505);
        break;
    case TI_PERLE_LUNE:
        inventory->setObject(PERLE);
        MainController::getInstance()->getGameController()->displayText(339);
        break;
    case TI_LIVRE:
        inventory->setObject(LIVRE);
        MainController::getInstance()->getGameController()->displayText(1023);
        break;
    case TI_LANTERNE:
        inventory->setObject(LANTERNE);
        if (status->getMaxMagic() == 0)
        {
            status->setMaxMagic(32);
        }
        status->setMagic(status->getMaxMagic());
        MainController::getInstance()->getGameController()->displayText(1250);
        break;
    case TI_DOUBLE_MAGIE:
        status->setMaxMagic(64);
        status->setMagic(status->getMaxMagic());
        MainController::getInstance()->getGameController()->displayText(370);
        break;
    case TI_POTION_ROUGE:
        if (inventory->hasObject(FLACON_1) && !inventory->getFlacon(0))
            tmp = 0;
        else if (inventory->hasObject(FLACON_2) && !inventory->getFlacon(1))
            tmp = 1;
        else if (inventory->hasObject(FLACON_3) && !inventory->getFlacon(2))
            tmp = 2;
        else if (inventory->hasObject(FLACON_4) && !inventory->getFlacon(3))
            tmp = 3;
        inventory->setFlacon(tmp, 1);
        MainController::getInstance()->getGameController()->displayText(670);
        break;
    case TI_POTION_VERTE:
        if (inventory->hasObject(FLACON_1) && !inventory->getFlacon(0))
            tmp = 0;
        else if (inventory->hasObject(FLACON_2) && !inventory->getFlacon(1))
            tmp = 1;
        else if (inventory->hasObject(FLACON_3) && !inventory->getFlacon(2))
            tmp = 2;
        else if (inventory->hasObject(FLACON_4) && !inventory->getFlacon(3))
            tmp = 3;
        inventory->setFlacon(tmp, 2);
        MainController::getInstance()->getGameController()->displayText(671);
        break;
    case TI_POTION_BLEUE:
        if (inventory->hasObject(FLACON_1) && !inventory->getFlacon(0))
            tmp = 0;
        else if (inventory->hasObject(FLACON_2) && !inventory->getFlacon(1))
            tmp = 1;
        else if (inventory->hasObject(FLACON_3) && !inventory->getFlacon(2))
            tmp = 2;
        else if (inventory->hasObject(FLACON_4) && !inventory->getFlacon(3))
            tmp = 3;
        inventory->setFlacon(tmp, 3);
        MainController::getInstance()->getGameController()->displayText(672);
        break;
    case TI_CARTE:
        inventory->setObject(CARTE);
        MainController::getInstance()->getGameController()->displayText(568);
        break;
    case TI_CARTE_DONJON:
        tmp = scene->getMap()->getId();
        scene->setCoffre(tmp == 156 ? 16 : tmp - 45, 0, 1);
        MainController::getInstance()->getGameController()->displayText(1204);
        break;
    case TI_BOUSSOLE:
        tmp = scene->getMap()->getId();
        scene->setCoffre(tmp == 156 ? 16 : tmp - 45, 1, 1);
        MainController::getInstance()->getGameController()->displayText(1205);
        break;
    case TI_CLE_BOSS:
        tmp = scene->getMap()->getId();
        scene->setCoffre(tmp == 156 ? 16 : tmp - 45, 2, 1);
        MainController::getInstance()->getGameController()->displayText(1206);
        break;
    case TI_CLE:
        tmp = scene->getMap()->getId();
        if (tmp == 155)
        {
            if (scene->getAvancement() < AV_CLE_PRISON_F_TROUVEE)
            {
                scene->setAvancement(AV_CLE_PRISON_F_TROUVEE);
            }
        }
        else
        {
            scene->setCoffre(tmp == 156 ? 16 : tmp - 45, 3, scene->getCoffre(tmp == 156 ? 16 : tmp - 45, 3) + 1);
            scene->setCoffre(tmp == 156 ? 16 : tmp - 45, id, 1);
        }
        MainController::getInstance()->getGameController()->displayText(1207);
        break;
    case TI_GRAPPIN:
        inventory->setObject(GRAPPIN);
        MainController::getInstance()->getGameController()->displayText(895);
        break;
    case TI_BAGUETTE_FEU:
        inventory->setObject(BAGUETTE_FEU);
        status->setMagic(status->getMaxMagic());
        MainController::getInstance()->getGameController()->displayText(1266);
        break;
    case TI_BAGUETTE_GLACE:
        inventory->setObject(BAGUETTE_GLACE);
        status->setMagic(status->getMaxMagic());
        MainController::getInstance()->getGameController()->displayText(1264);
        break;
    case TI_MASQUE:
        inventory->setObject(MASQUE);
        MainController::getInstance()->getGameController()->displayText(1653);
        break;
    case TI_TRIFORCE:
        inventory->setObject(TRIFORCE);
        MainController::getInstance()->getGameController()->displayText(1382);
        break;
    case TI_ECREVISSE:
    case TI_EPERLAN:
    case TI_POISSON_ZEBRE:
    case TI_GOBIE:
    case TI_CRABE:
    case TI_PIBALE:
    case TI_VAIRON:
    case TI_CARASSIN_DORE:
    case TI_ABLETTE:
    case TI_GOUJON:
    case TI_LOCHE:
    case TI_EPINOCHE:
    case TI_GREMILLE:
    case TI_BLENNIE:
    case TI_MAGICARPE:
    case TI_TRUITE:
    case TI_AYU:
    case TI_PERCHE_NOIRE:
    case TI_ANGUILLE:
    case TI_POISSON_CHAT:
    case TI_BLACK_BASS:
    case TI_HUCHON:
    case TI_BARBEAU:
    case TI_LAMPROIE:
    case TI_HOTU:
    case TI_SAUMON:
    case TI_ESTURGEON:
    case TI_OMBLE_CHEVALIER:
    case TI_CARPE:
    case TI_SILURE:
        scene->setPoissons(type - TI_ECREVISSE);
        MainController::getInstance()->getGameController()->displayText(type - TI_ECREVISSE + 160);
        break;
    case TI_ENCLUME:
        inventory->setTrocGemme(0, TGR_ENCLUME);
        MainController::getInstance()->getGameController()->displayText(543);
        break;
    case TI_FER_CHEVAL:
        inventory->setTrocGemme(0, TGR_FER_CHEVAL);
        MainController::getInstance()->getGameController()->displayText(982);
        break;
    case TI_RIEN:
        inventory->setTrocGemme(0, TGR_RIEN);
        MainController::getInstance()->getGameController()->displayText(680);
        break;
    case TI_BIJOU:
        inventory->setTrocGemme(0, TGR_BIJOU);
        MainController::getInstance()->getGameController()->displayText(942);
        break;
    case TI_LETTRE:
        inventory->setTrocGemme(0, TGR_LETTRE);
        MainController::getInstance()->getGameController()->displayText(1126);
        break;
    case TI_ALLIANCE:
        inventory->setTrocGemme(0, TGR_ALLIANCE);
        MainController::getInstance()->getGameController()->displayText(1171);
        break;
    case TI_RIEN_2:
        inventory->setTrocGemme(0, TGR_RIEN_2);
        MainController::getInstance()->getGameController()->displayText(1100);
        break;
    case TI_MARTEAU_PONT:
        inventory->setTrocGemme(0, TGR_MARTEAU);
        MainController::getInstance()->getGameController()->displayText(1093);
        break;
    case TI_VIEILLE_BOTTE:
        inventory->setTrocGemme(1, TGB_BOTTES);
        MainController::getInstance()->getGameController()->displayText(763);
        break;
    case TI_MARTEAU_LOURD:
        inventory->setTrocGemme(1, TGB_MARTEAU);
        MainController::getInstance()->getGameController()->displayText(439);
        break;
    case TI_CLOCHE:
        inventory->setTrocGemme(1, TGB_CLOCHE);
        MainController::getInstance()->getGameController()->displayText(989);
        break;
    case TI_HACHE:
        inventory->setTrocGemme(1, TGB_HACHE);
        MainController::getInstance()->getGameController()->displayText(554);
        break;
    case TI_CORDE:
        inventory->setTrocGemme(1, TGB_CORDE);
        MainController::getInstance()->getGameController()->displayText(1088);
        break;
    case TI_PLAN:
        inventory->setTrocGemme(1, TGB_PLAN);
        MainController::getInstance()->getGameController()->displayText(879);
        break;
    case TI_VIN:
        inventory->setTrocGemme(2, TGJ_VIN);
        MainController::getInstance()->getGameController()->displayText(1034);
        break;
    case TI_POUDRE_OR:
        inventory->setTrocGemme(2, TGJ_POUDRE_OR);
        MainController::getInstance()->getGameController()->displayText(534);
        break;
    case TI_MIROIR:
        inventory->setTrocGemme(2, TGJ_MIROIR);
        MainController::getInstance()->getGameController()->displayText(995);
        break;
    case TI_CUILLERE:
        inventory->setTrocGemme(2, TGJ_CUILLERE);
        MainController::getInstance()->getGameController()->displayText(1361);
        break;
    case TI_CRANE:
        inventory->setTrocGemme(2, TGJ_CRANE);
        MainController::getInstance()->getGameController()->displayText(1179);
        break;
    case TI_REC_DETTE:
        inventory->setTrocGemme(2, TGJ_REC_DETTE);
        MainController::getInstance()->getGameController()->displayText(428);
        break;
    case TI_SCIE:
        inventory->setTrocGemme(2, TGJ_SCIE);
        MainController::getInstance()->getGameController()->displayText(1157);
        break;
    case TI_CARTE_VOYAGE:
        inventory->setTrocGemme(3, TGV_CARTE);
        MainController::getInstance()->getGameController()->displayText(707);
        break;
    case TI_BALAIS:
        inventory->setTrocGemme(3, TGV_BALAIS);
        MainController::getInstance()->getGameController()->displayText(276);
        break;
    case TI_CONFITURE:
        inventory->setTrocGemme(3, TGV_CONFITURE);
        MainController::getInstance()->getGameController()->displayText(397);
        break;
    case TI_CROISSANT:
        inventory->setTrocGemme(3, TGV_CROISSANT);
        MainController::getInstance()->getGameController()->displayText(951);
        break;
    case TI_BIERE:
        inventory->setTrocGemme(3, TGV_BIERE);
        MainController::getInstance()->getGameController()->displayText(1045);
        break;
    case TI_CLOU:
        inventory->setTrocGemme(3, TGV_CLOU);
        MainController::getInstance()->getGameController()->displayText(1202);
        break;
    case TI_SAC_RIZ:
        inventory->addTroc(TT_SAC_RIZ);
        MainController::getInstance()->getGameController()->displayText(304);
        break;
    case TI_SAC_OLIVES:
        inventory->addTroc(TT_SAC_OLIVES);
        MainController::getInstance()->getGameController()->displayText(307);
        break;
    case TI_BOCAL_EPICES:
        inventory->addTroc(TT_BOCAL_EPICES);
        MainController::getInstance()->getGameController()->displayText(363);
        break;
    case TI_POULET:
        inventory->addTroc(TT_POULET);
        MainController::getInstance()->getGameController()->displayText(297);
        break;
    case TI_PLUME:
        inventory->addTroc(TT_PLUME);
        MainController::getInstance()->getGameController()->displayText(301);
        break;
    case TI_PERLES:
        inventory->addTroc(TT_PERLES);
        MainController::getInstance()->getGameController()->displayText(360);
        break;
    case TI_TAPISSERIE:
        inventory->addTroc(TT_TAPISSERIE);
        MainController::getInstance()->getGameController()->displayText(453);
        break;
    case TI_AMULETTE:
        inventory->addTroc(TT_AMULETTE);
        MainController::getInstance()->getGameController()->displayText(383);
        break;
    case TI_PARFUM:
        inventory->addTroc(TT_PARFUM);
        MainController::getInstance()->getGameController()->displayText(508);
        break;
    case TI_ROC_MAGMA:
        inventory->addTroc(TT_ROC_MAGMA);
        MainController::getInstance()->getGameController()->displayText(357);
        break;
    case TI_ROC_GIVRE:
        inventory->addTroc(TT_ROC_GIVRE);
        MainController::getInstance()->getGameController()->displayText(519);
        break;
    case TI_POIVRON:
        inventory->addTroc(TT_POIVRON);
        MainController::getInstance()->getGameController()->displayText(884);
        break;
    case TI_ROUAGE:
        inventory->addTroc(TT_ROUAGE);
        MainController::getInstance()->getGameController()->displayText(282);
        break;
    case TI_JAUGE:
        inventory->addTroc(TT_JAUGE);
        MainController::getInstance()->getGameController()->displayText(599);
        break;
    case TI_ROUE:
        inventory->addTroc(TT_ROUE);
        MainController::getInstance()->getGameController()->displayText(351);
        break;
    case TI_SOURCE_NRJ:
        inventory->addTroc(TT_SOURCE_NRJ);
        MainController::getInstance()->getGameController()->displayText(1183);
        break;
    case TI_BOURSE_RUBIS_1:
        status->setMaxRupees(99);
        status->setRupees(0);
        MainController::getInstance()->getGameController()->displayText(1308);
        break;
    case TI_BOURSE_RUBIS_2:
        status->setMaxRupees(200);
        MainController::getInstance()->getGameController()->displayText(288);
        break;
    case TI_BOURSE_RUBIS_3:
        status->setMaxRupees(500);
        MainController::getInstance()->getGameController()->displayText(291);
        break;
    case TI_BOURSE_RUBIS_4:
        status->setMaxRupees(999);
        MainController::getInstance()->getGameController()->displayText(294);
        break;
    case TI_BOURSE_GANON_OR_1:
        status->setMaxGanonOr(99);
        MainController::getInstance()->getGameController()->displayText(955);
        break;
    case TI_BOURSE_GANON_OR_2:
        status->setMaxGanonOr(200);
        MainController::getInstance()->getGameController()->displayText(342);
        break;
    case TI_BOURSE_GANON_OR_3:
        status->setMaxGanonOr(500);
        MainController::getInstance()->getGameController()->displayText(345);
        break;
    case TI_BOURSE_GANON_OR_4:
        status->setMaxGanonOr(999);
        MainController::getInstance()->getGameController()->displayText(348);
        break;
    case TI_BOURSE_PIECE_OR_1:
        status->setMaxPieceOr(99);
        MainController::getInstance()->getGameController()->displayText(1022);
        break;
    case TI_BOURSE_PIECE_OR_2:
        status->setMaxPieceOr(200);
        MainController::getInstance()->getGameController()->displayText(374);
        break;
    case TI_BOURSE_PIECE_OR_3:
        status->setMaxPieceOr(500);
        MainController::getInstance()->getGameController()->displayText(377);
        break;
    case TI_BOURSE_PIECE_OR_4:
        status->setMaxPieceOr(999);
        MainController::getInstance()->getGameController()->displayText(380);
        break;
    case TI_PLANCHES:
        MainController::getInstance()->getGameController()->displayText(444);
        break;
    case TI_SAC_RIZ_10:
        inventory->addTroc(TT_SAC_RIZ, 10);
        MainController::getInstance()->getGameController()->displayText(581);
        break;
    case TI_BOCAL_EPICES_10:
        inventory->addTroc(TT_BOCAL_EPICES, 10);
        MainController::getInstance()->getGameController()->displayText(582);
        break;
    case TI_SAC_OLIVES_10:
        inventory->addTroc(TT_SAC_OLIVES, 10);
        MainController::getInstance()->getGameController()->displayText(583);
        break;
    case TI_DETECTEUR:
        inventory->setObject(DETECTEUR);
        MainController::getInstance()->getGameController()->displayText(641);
        break;
    case TI_BONUS_FORCE_1:
        inventory->setObject(BONUS_FORCE_1);
        MainController::getInstance()->getGameController()->displayText(650);
        break;
    case TI_BONUS_FORCE_2:
        inventory->setObject(BONUS_FORCE_2);
        MainController::getInstance()->getGameController()->displayText(650);
        break;
    case TI_BONUS_DEFENSE_1:
        inventory->setObject(BONUS_DEFENSE_1);
        MainController::getInstance()->getGameController()->displayText(655);
        break;
    case TI_BONUS_DEFENSE_2:
        inventory->setObject(BONUS_DEFENSE_2);
        MainController::getInstance()->getGameController()->displayText(655);
        break;
    default:
        break;
    }

    if ((animation == IDLE || animation == WALK || animation == PUSH) && charge == 0 /*&& !lapin*/)
    {
        // anim with one arm or two
        if (lapin || (type == TI_QUART_COEUR || type == TI_EPEE_1 || type == TI_EPEE_2 || type == TI_EPEE_3 || type == TI_EPEE_4 || type == TI_EPEE_5 || type == TI_CLE || type == TI_CLE_BOSS || type == TI_CARTE_DONJON || type == TI_BOUSSOLE))
        {
            setAnimation(TROUVE_SIMPLE);
        }
        else
        {
            setAnimation(TROUVE_DOUBLE);
        }
        trouve = type;
    }
}

bool Link::useStuff()
{
    Equipment e = inventory->getCurrent();

    if (!inventory->hasObject(e))
    {
        return false;
    }

    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    switch (e)
    {
    case ARC:
    case ARC_FEE:
    case FLECHE_FEU:
    case FLECHE_GLACE:
    case FLECHE_LUMIERE:
        setAnimation(TIR_ARC);
        return true;
    case TROC_GEMME_ROUGE:
    case TROC_GEMME_BLEUE:
    case TROC_GEMME_JAUNE:
    case TROC_GEMME_VERTE:
        MainController::getInstance()->getGameController()->displayText(1261);
        return true;
    case BOMBES:
        if (status->getBombs())
        {
            status->setBombs(status->getBombs() - 1);
            porte = new ObjBomb(x, y);
            setAnimation(PORTE);
            AudioManager::getInstance()->playSound(TS_PORTE);
            return true;
        }
        return false;
    case GRAPPIN:
        setAnimation(TIR_GRAPPIN);
        delete grappin;
        grappin = new ProjGrappin(x + 2, y + 10, direction);
        AudioManager::getInstance()->playSound(TS_GRAPPIN);
        return true;
    case BAGUETTE_FEU:
        setAnimation(TIR_BAGUETTE_FEU);
        return true;
    case BAGUETTE_GLACE:
        setAnimation(TIR_BAGUETTE_GLACE);
        return true;
    case LANTERNE:
        if (status->getVirtualMagic() > 0)
        {
            int a = 0;
            int b = 0;
            switch (direction)
            {
            case N:
                a = x;
                b = y - 8;
                break;
            case S:
                a = x;
                b = y + 24;
                break;
            case W:
                a = x - 16;
                b = y + 8;
                break;
            case E:
                a = x + 16;
                b = y + 8;
                break;
            }
            delete flamme;
            flamme = new Flamme(a, b, direction);
            setAnimation(TIR_LANTERNE);
            AudioManager::getInstance()->playSound(TS_BURN);
            status->updateMagic(-1);
            return true;
        }
        return false;
    case MARTEAU:
        setAnimation(TIR_MARTEAU);
        return true;
    case OCARINA:
        setAnimation(JOUE_OCARINA);
        if (inventory->hasObject(CHANT_1))
        {
            MainController::getInstance()->getGameController()->displayText(245);
        }
        else if (inventory->hasObject(CHANT_3))
        {
            MainController::getInstance()->getGameController()->displayText(242);
        }
        else if (inventory->hasObject(CHANT_2))
        {
            MainController::getInstance()->getGameController()->displayText(240);
        }
        else
        {
            MainController::getInstance()->getGameController()->displayText(239);
        }
        direction = S;
        return true;
    case FLACON_1:
    case FLACON_2:
    case FLACON_3:
    case FLACON_4:
        setAnimation(BOIT_POTION);
        return true;
    case CANNE_A_PECHE_1:
    case CANNE_A_PECHE_2:
    case CANNE_A_PECHE_3:
        if (animation == PECHE)
        {
            if (animMax == 0)
            {
                setAnimation(IDLE);
                MainController::getInstance()->getGameController()->displayText(159);
            }
            else
            {
                setAnimation(IDLE);
                trouveObjet(ItemHelper::getInstance()->getFish(e, map->getId()));
            }
        }
        else if (map->getSol(x, y + 23) == 67)
        { // ponton present
            setAnimation(PECHE);
        }
        else if (map->getSol(x, y + 23) == 1794)
        { // ponton futur
            MainController::getInstance()->getGameController()->displayText(158);
        }
        else
        {
            MainController::getInstance()->getGameController()->displayText(157);
        }
        return true;
    default:
        return false;
    }
}

bool Link::porteObjet()
{
    if (porte != 0)
    {
        return false;
    }

    Portable *p = getPortable();
    if (p == 0)
    {
        return false;
    }
    porte = p;
    porte->stopBeforeUp();
    setAnimation(SOULEVE);
    return true;
}

Portable *Link::getPortable()
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    Portable *result = map->pickUpObject(getBoundingBox());
    if (result)
        return result;

    BoundingBox bb;
    switch (direction)
    {
    case N:
        bb.setX(x + 7);
        bb.setY(y + 6);
        bb.setW(2);
        bb.setH(2);
        break;
    case S:
        bb.setX(x + 7);
        bb.setY(y + 24);
        bb.setW(2);
        bb.setH(2);
        break;
    case W:
        bb.setX(x - 2);
        bb.setY(y + 15);
        bb.setW(2);
        bb.setH(2);
        break;
    case E:
        bb.setX(x + 16);
        bb.setY(y + 15);
        bb.setW(2);
        bb.setH(2);
        break;
    }

    return map->pickUpObject(&bb);
}

void Link::pousse()
{
    Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    BoundingBox bb;
    switch (direction)
    {
    case N:
        bb.setX(x + 7);
        bb.setY(y + 6);
        bb.setW(2);
        bb.setH(2);
        break;
    case S:
        bb.setX(x + 7);
        bb.setY(y + 24);
        bb.setW(2);
        bb.setH(2);
        break;
    case W:
        bb.setX(x - 2);
        bb.setY(y + 15);
        bb.setW(2);
        bb.setH(2);
        break;
    case E:
        bb.setX(x + 16);
        bb.setY(y + 15);
        bb.setW(2);
        bb.setH(2);
        break;
    }

    return map->pushObject(&bb, direction);
}

void Link::lacheObj()
{
    if (porte != 0)
    {
        porte->lache(getDown());
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        map->addObject(porte);
        porte = 0;
    }
}

void Link::lanceObj()
{
    if (porte != 0)
    {
        porte->lance(getDown(), direction, elan);
        Map *map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
        map->addObject(porte);
        porte = 0;
        AudioManager::getInstance()->playSound(TS_THROW);
    }
}

int Link::getStartX() { return startX; }
int Link::getStartY() { return startY; }
Direction Link::getStartDir() { return startDir; }

/*******
 * DRAW *
 *******/

void Link::drawForMenu(int dstX, int dstY)
{
    if (lapin)
    {
        WindowManager::getInstance()->draw(imageLink, 352 + w, 120, w, h, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(imageLink, w, 0, w, h, dstX, dstY);
        if (bouclier > 0)
        {
            bouclier->draw(dstX, dstY, S, IDLE, 0, 0);
        }
    }
}

void Link::drawIdle(int dstX, int dstY)
{
    if (lapin)
        WindowManager::getInstance()->draw(imageLink, 352 + direction * w, 120, w, h, dstX, dstY);
    else
        WindowManager::getInstance()->draw(imageLink, direction * w, 0, w, h, dstX, dstY);
}

void Link::drawDead(int dstX, int dstY)
{
    if (!isOnWater() && !isOnGap())
    {
        if (lapin)
            WindowManager::getInstance()->draw(imageLink, 416, 128, 24, 16, dstX - 4, dstY + 8);
        else
            WindowManager::getInstance()->draw(imageLink, 192, 200, 24, 16, dstX - 4, dstY + 8);
    }
}

void Link::drawWalk(int dstX, int dstY)
{
    if (lapin)
        WindowManager::getInstance()->draw(imageLink, 352 + direction * w, 144 + h * ((anim / 2) % 2), w, h, dstX, dstY);
    else
        WindowManager::getInstance()->draw(imageLink, direction * w, h * (anim + 1), w, h, dstX, dstY);
}

void Link::drawPush(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 352 + direction * w, h * (anim / 3), w, h, dstX, dstY);
}

void Link::drawPorte(int dstX, int dstY, int offsetX, int offsetY)
{

    int dstX0 = dstX;

    int srcX = 272 + direction * w;
    int srcY = 48 + h * anim;
    int srcW = w;
    int srcH = h;

    if (direction == W)
    {
        dstX += 2;
        srcW = 24;
        if (anim == 2)
        {
            dstX--;
        }
    }
    if (direction == E)
    {
        dstX -= 10;
        srcX += 8;
        srcW = 24;
        if (anim == 2)
        {
            dstX++;
        }
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX, dstY);

    if (porte != 0)
    {
        dstX0 += 8;
        dstY += 7;
        if (direction == N || direction == S)
            dstY++;
        if (anim % 2 && (direction == N || direction == S))
            dstY++;
        if ((anim == 1 || anim == 3) && (direction == W || direction == E))
            dstY++;
        if (anim == 2 && (direction == W || direction == E))
            dstY += 2;
        porte->drawWhenCarried(dstX0 + offsetX, dstY + offsetY, offsetX, offsetY);
    }
}

void Link::drawThrow(int dstX, int dstY)
{
    int srcX = 272 + direction * w;
    int srcY = 144;
    int srcW = w;
    int srcH = h;

    if (direction == W)
    {
        dstX += 2;
        srcW = 24;
    }
    if (direction == E)
    {
        dstX -= 10;
        srcX += 8;
        srcW = 24;
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX, dstY);
}

void Link::drawSouleve(int dstX, int dstY)
{

    int srcX = 272 + direction * w;
    int srcY = anim * h;
    int srcW = w;
    int srcH = h;

    if (direction == W)
    {
        dstX += 2;
        srcW = 24;
    }
    if (direction == E)
    {
        dstX -= 10;
        srcX += 8;
        srcW = 24;
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX, dstY);
}

void Link::drawTouche(int dstX, int dstY)
{

    int var = 0;
    switch (anim)
    {
    case 0:
        var = 2;
        break;
    case 1:
        var = 5;
        break;
    case 2:
        var = 6;
        break;
    case 3:
        var = 6;
        break;
    case 4:
        var = 6;
        break;
    case 5:
        var = 6;
        break;
    case 6:
        var = 6;
        break;
    case 7:
        var = 6;
        break;
    case 8:
        var = 5;
        break;
    case 9:
        var = 2;
        break;
    case 10:
        var = 0;
        break;
    }

    if (lapin)
        WindowManager::getInstance()->draw(imageLink, 416 + direction * w, 144, w, h, dstX, dstY - var);
    else
        WindowManager::getInstance()->draw(imageLink, 64 + direction * w, 192, w, h, dstX, dstY - var);

    WindowManager::getInstance()->draw(imageEffets, 58, 34, 8, 4, dstX + 4, dstY + 20);
}

void Link::drawChute(int dstX, int dstY)
{

    int srcX;
    int srcY;
    int srcW = 22;
    int srcH = 22;

    dstX -= 3;
    dstY += 5;

    if (lapin && anim < 4)
    {
        switch (anim)
        {
        case 0:
            srcX = 272;
            break;
        case 1:
            srcX = 294;
            srcW = 17;
            dstX += 3;
            break;
        case 2:
            srcX = 311;
            srcW = 13;
            dstX += 4;
            break;
        case 3:
            srcX = 324;
            srcW = 8;
            dstX += 7;
            break;
        default:
            srcX = 272;
            break;
        }
        srcY = 173;
    }
    else
    {
        srcX = 216 + srcW * anim;
        srcY = 194;
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX, dstY);
}

void Link::drawTrouveSimple(int dstX, int dstY)
{
    if (lapin)
    {
        WindowManager::getInstance()->draw(imageLink, 352, 192, 16, 24, dstX, dstY);
    }
    else
    {
        WindowManager::getInstance()->draw(imageLink, 256, 48, 16, 24, dstX, dstY);
    }
    ItemHelper::getInstance()->drawItem(trouve, dstX + 14, dstY - 6);
}

void Link::drawTrouveDouble(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 256, 24, 16, 24, dstX, dstY);
    ItemHelper::getInstance()->drawItem(trouve, dstX + 8, dstY - 6);
}

void Link::drawArc(int dstX, int dstY)
{
    int tmp = (int)((anim + 1) / 2);

    if (direction == N)
    {
        WindowManager::getInstance()->draw(imageObjets, 16 * direction, 16 * tmp, 16, 16, dstX - 2 - 3 * tmp, dstY + 7 + 3 * tmp);
    }

    WindowManager::getInstance()->draw(imageLink, 128 + w * direction, 120 + h * anim, 16, 24, dstX, dstY);

    if (direction == N)
    {
        return;
    }

    switch (direction)
    {
    case S:
        dstX += 10 - 8 * tmp;
        dstY += 10 + 5 * tmp;
        break;
    case W:
        dstX -= 1 + 2 * tmp;
        dstY += 11 - 4 * tmp;
        break;
    case E:
        dstX += 4 + 8 * tmp;
        dstY += 11 - 4 * tmp;
        break;
    default:
        break;
    }

    WindowManager::getInstance()->draw(imageObjets, 16 * direction, 16 * tmp, 16, 16, dstX, dstY);
}

void Link::drawGrappin(int dstX, int dstY, int offsetX, int offsetY)
{

    if (grappin != 0)
    {
        grappin->draw(offsetX, offsetY);
    }

    WindowManager::getInstance()->draw(imageLink, 128 + w * direction, 192, 16, 24, dstX, dstY);

    if (direction == N)
    {
        return;
    }

    int srcX = 56;
    int srcY = 74;
    int srcW = 8;
    int srcH = 4;
    switch (direction)
    {
    case S:
        dstX += 6;
        dstY += 17;
        srcW = 4;
        srcH = 8;
        break;
    case W:
        dstX -= 7;
        dstY += 14;
        srcY += 8;
        break;
    case E:
        dstX += 15;
        dstY += 14;
        srcY += 12;
        break;
    default:
        break;
    }

    WindowManager::getInstance()->draw(imageObjets, srcX, srcY, srcW, srcH, dstX, dstY);
}

void Link::drawLanterne(int dstX, int dstY, int offsetX, int offsetY)
{

    if (flamme != 0)
    {
        flamme->draw(offsetX, offsetY);
    }

    WindowManager::getInstance()->draw(imageLink, 128 + w * direction, 192, 16, 24, dstX, dstY);
}

void Link::drawFlacon(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 256, 0, 16, 24, dstX, dstY);

    int flacon = inventory->getCurrentFlacon();

    int srcY = anim == 2 ? 0 : 8 * (flacon % 4);
    int srcX = anim == 2 || flacon == 0 ? 96 : 96 + 8 * anim + 32 * (flacon / 4);

    dstX += 4;
    dstY += 12;
    if (anim != 1)
        dstY++;

    WindowManager::getInstance()->draw(imageObjets, srcX, srcY, 8, 7, dstX, dstY);
}

void Link::drawOcarina(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 256, 0, 16, 24, dstX, dstY);
    WindowManager::getInstance()->draw(imageObjets, 104, 0, 8, 4, dstX + 4, dstY + 13);
}

void Link::drawBaguette(int dstX, int dstY)
{

    WindowManager::getInstance()->draw(imageLink, 192 + w * direction, h * anim, w, h, dstX, dstY);

    int srcX = 14 * direction;
    int srcY = 32 + anim * 14;
    if (animation == TIR_BAGUETTE_GLACE)
        srcX += 56;
    if (animation == TIR_MARTEAU)
        srcY += 42;
    switch (direction)
    {
    case N:
        dstX -= 2;
        dstY -= 5;
        if (anim == 1)
            dstY += 3;
        if (anim == 2)
            dstY += 7;
        break;
    case S:
        dstX += 10;
        dstY -= 3;
        if (anim == 1)
            dstY += 13;
        if (anim == 2)
        {
            dstX--;
            dstY += 23;
        }
        break;
    case W:
        dstY--;
        if (anim == 1)
        {
            dstX -= 8;
            dstY += 5;
        }
        if (anim == 2)
        {
            dstX -= 10;
            dstY += 15;
        }
        break;
    case E:
        dstX += 8;
        dstY--;
        if (anim == 1)
        {
            dstX += 5;
            dstY += 5;
        }
        if (anim == 2)
        {
            dstX += 4;
            dstY += 15;
        }
        break;
    }
    WindowManager::getInstance()->draw(imageObjets, srcX, srcY, 14, 14, dstX, dstY);
}

void Link::drawFlotte(int dstX, int dstY)
{

    int srcX = 192 + 16 * direction;
    int srcY = 72 + h * anim;
    int srcW = 16;

    if (direction == W)
    {
        dstX--;
        srcW = 24;
    }
    if (direction == E)
    {
        dstX -= 7;
        srcW = 24;
        srcX += 8;
    }

    if (animation == NAGE)
        srcY += h * 2;
    if (srcY == 192)
        srcY -= 48;

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, h, dstX, dstY);
}

void Link::drawCoule(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageEffets, 16 * (anim % 2), 38, 16, 15, dstX, dstY + 8);
}

void Link::drawEpee(int dstX, int dstY)
{

    int srcX = 64 + 16 * direction;
    int srcY = h * anim;

    if (direction == W)
    {
        dstX += 2;
        switch (anim)
        {
        case 1:
            dstX -= 2;
            break;
        case 2:
            dstX -= 3;
            break;
        case 3:
            dstX -= 2;
            break;
        case 4:
            dstX--;
            break;
        default:
            break;
        }
    }
    if (direction == E)
    {
        dstX -= 2;
        switch (anim)
        {
        case 1:
            dstX += 2;
            break;
        case 2:
            dstX += 3;
            break;
        case 3:
            dstX += 2;
            break;
        case 4:
            dstX++;
            break;
        default:
            break;
        }
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, 16, 24, dstX, dstY);
}

void Link::drawCharge(int dstX, int dstY)
{

    int tmp = anim / 2;
    int srcX = 128 + 16 * direction;
    int srcY = 24 * tmp;

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, 16, 24, dstX, dstY);
}

void Link::drawSpin(int dstX, int dstY)
{

    int srcX = 0;
    int srcY = 0;

    switch (direction)
    {
    case N:
        if (anim == 0 || anim == 5 || (anim >= 21 && anim <= 26))
        {
            srcX = 64;
            srcY = 120;
        }
        if (anim >= 1 && anim <= 4)
        {
            srcX = 64;
            srcY = 144;
        }
        if (anim >= 6 && anim <= 8)
        {
            srcX = 64;
            srcY = 168;
        }
        if (anim >= 9 && anim <= 12)
        {
            srcX = 80;
            srcY = 120;
        }
        if (anim >= 13 && anim <= 16)
        {
            srcX = 80;
            srcY = 144;
        }
        if (anim >= 17 && anim <= 20)
        {
            srcX = 80;
            srcY = 168;
        }
        break;
    case S:
        if (anim == 0 || anim == 5 || (anim >= 21 && anim <= 26))
        {
            srcX = 96;
            srcY = 120;
        }
        if (anim >= 1 && anim <= 4)
        {
            srcX = 96;
            srcY = 144;
        }
        if (anim >= 6 && anim <= 8)
        {
            srcX = 80;
            srcY = 144;
        }
        if (anim >= 9 && anim <= 12)
        {
            srcX = 80;
            srcY = 168;
        }
        if (anim >= 13 && anim <= 16)
        {
            srcX = 64;
            srcY = 168;
        }
        if (anim >= 17 && anim <= 20)
        {
            srcX = 80;
            srcY = 120;
        }
        break;
    case W:
        if (anim == 0 || anim == 5 || (anim >= 21 && anim <= 26))
        {
            srcX = 96;
            srcY = 168;
        }
        if (anim >= 1 && anim <= 4)
        {
            srcX = 112;
            srcY = 120;
        }
        if (anim >= 6 && anim <= 8)
        {
            srcX = 80;
            srcY = 168;
        }
        if (anim >= 9 && anim <= 12)
        {
            srcX = 64;
            srcY = 168;
        }
        if (anim >= 13 && anim <= 16)
        {
            srcX = 80;
            srcY = 120;
        }
        if (anim >= 17 && anim <= 20)
        {
            srcX = 80;
            srcY = 144;
        }
        break;
    case E:
        if (anim == 0 || anim == 5 || (anim >= 21 && anim <= 26))
        {
            srcX = 112;
            srcY = 144;
        }
        if (anim >= 1 && anim <= 4)
        {
            srcX = 112;
            srcY = 168;
        }
        if (anim >= 6 && anim <= 8)
        {
            srcX = 80;
            srcY = 120;
        }
        if (anim >= 9 && anim <= 12)
        {
            srcX = 80;
            srcY = 144;
        }
        if (anim >= 13 && anim <= 16)
        {
            srcX = 80;
            srcY = 168;
        }
        if (anim >= 17 && anim <= 20)
        {
            srcX = 64;
            srcY = 168;
        }
        break;
    }

    if (anim > 26)
        drawIdle(dstX, dstY);
    else
        WindowManager::getInstance()->draw(imageLink, srcX, srcY, w, h, dstX, dstY);
}

void Link::drawElectric(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 416 + 16 * (anim % 2), 96, w, h, dstX, dstY);
}

void Link::drawPeche(int dstX, int dstY)
{
    WindowManager::getInstance()->draw(imageLink, 400, 192, w, h, dstX, dstY);

    int srcX = 144 + 20 * anim;
    int srcY = 0;

    if (inventory->getCurrent() == CANNE_A_PECHE_3)
    {
        srcY = 64;
    }
    else if (inventory->getCurrent() == CANNE_A_PECHE_2)
    {
        srcY = 32;
    }

    WindowManager::getInstance()->draw(imageObjets, srcX, srcY, 20, 32, dstX, dstY);
}

void Link::drawBarquee(int dstX, int dstY)
{
    int srcX = 0;
    int srcY = 0;
    int srcW = 0;
    int srcH = 0;
    int offsetX = 0;
    int offsetY = 0;

    if (status->getVirtualLife() <= 0)
    {

        return;
    }

    if (direction == W)
    {
        srcX = animation == BARQUE ? 333 + 67 * anim : 336;
        srcY = animation == BARQUE ? 25 : 1;
        srcW = animation == BARQUE ? 19 - 3 * anim : 16;
        srcH = animation == BARQUE ? 17 : 16;
        offsetX = animation == BARQUE ? -3 + 3 * anim : 0;
        offsetY = animation == BARQUE ? -1 : 0;
        WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX + offsetX, dstY + offsetY);
    }
    else if (direction == E)
    {
        srcX = animation == BARQUE ? 304 + 80 * anim : 304;
        srcY = animation == BARQUE ? 25 : 1;
        srcW = animation == BARQUE ? 19 - 3 * anim : 16;
        srcH = animation == BARQUE ? 17 : 16;
        offsetY = animation == BARQUE ? -1 : 0;
        WindowManager::getInstance()->draw(imageLink, srcX, srcY, srcW, srcH, dstX, dstY + offsetY);
    }

    switch (direction)
    {
    case N:
        srcX = 204 + 34 * anim + (animation == BARQUE ? 70 : 0);
        srcY = 0;
        srcW = 32;
        srcH = 37;
        offsetX = -8;
        offsetY = 0;
        break;
    case S:
        srcX = 204 + 34 * anim + (animation == BARQUE ? 70 : 0);
        srcY = 37;
        srcW = 32;
        srcH = 41;
        offsetX = -8;
        offsetY = -9;
        break;
    case W:
        srcX = 204 + 35 * anim + (animation == BARQUE ? 70 : 0);
        srcY = 98;
        srcW = 35;
        srcH = 20;
        offsetX = -5;
        offsetY = 7;
        break;
    case E:
        srcX = 204 + 35 * anim + (animation == BARQUE ? 70 : 0);
        srcY = 78;
        srcW = 35;
        srcH = 20;
        offsetX = -14;
        offsetY = 7;
        break;
    }
    WindowManager::getInstance()->draw(imageObjets, srcX, srcY, srcW, srcH, dstX + offsetX, dstY + offsetY);

    if (direction == N)
    {
        srcX = animation == BARQUE ? 368 : 288;
        srcY = animation == BARQUE ? 102 - 50 * anim : 4;
        srcH = animation == BARQUE ? 17 : 20;
        offsetY = animation == BARQUE ? 0 : -3;
        WindowManager::getInstance()->draw(imageLink, srcX, srcY, 16, srcH, dstX, dstY + offsetY);
    }
    else if (direction == S)
    {
        srcX = animation == BARQUE ? 384 - 112 * anim : 352;
        srcY = animation == BARQUE ? 196 - 168 * anim : 2;
        srcH = animation == BARQUE ? 15 : 17;
        offsetY = animation == BARQUE ? 4 : 2;
        WindowManager::getInstance()->draw(imageLink, srcX, srcY, 16, srcH, dstX, dstY + offsetY);
        WindowManager::getInstance()->draw(imageObjets, 218, 62, 4, 3, dstX + 6, dstY + 16);
    }
}

void Link::drawWagon(int dstX, int dstY)
{
    int srcX = 0;
    int srcY = 0;
    int srcH = 0;
    int offsetX = 0;
    int offsetY = 0;

    switch (direction)
    {
    case N:
        srcX = 272;
        srcY = 3;
        srcH = 14;
        offsetX = 0;
        offsetY = -4;
        break;
    case S:
        srcX = 288;
        srcY = 4;
        srcH = 20;
        offsetX = 0;
        offsetY = -8;
        break;
    case W:
        srcX = 304;
        srcY = 1;
        srcH = 17;
        offsetX = -3;
        offsetY = -9;
        break;
    case E:
        srcX = 336;
        srcY = 1;
        srcH = 17;
        offsetX = 3;
        offsetY = -9;
        break;
    }

    WindowManager::getInstance()->draw(imageLink, srcX, srcY, 16, srcH, dstX + offsetX, dstY + offsetY);
}
