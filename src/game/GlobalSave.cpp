#include "GlobalSave.h"

GlobalSave GlobalSave::instance = GlobalSave();

GlobalSave *GlobalSave::getInstance()
{
    return &instance;
}
GlobalSave::GlobalSave()
{
    init();
    load();
}

GlobalSave::~GlobalSave()
{
}

void GlobalSave::init()
{
    fullROTH = false;
    ultimeROTH = false;
    rushROTH = false;
    fullOLB = false;
    ultimeOLB = false;
    rushOLB = false;
    full3T = false;
    ultime3T = false;
    rush3T = false;
    bestTime = -1;
}

void GlobalSave::load()
{
    // ROTH
    ifstream fROTH("../Zelda Return of the Hylian/saves/records.dat", ios::in | ios::binary);
    if (fROTH.is_open())
    {
        fROTH.read((char *)&fullROTH, sizeof(bool));
        fROTH.read((char *)&ultimeROTH, sizeof(bool));
        fROTH.read((char *)&rushROTH, sizeof(bool));
        fROTH.close();
    }

    // OLB
    ifstream fOLB("../Zelda Oni Link Begins/saves/records.dat", ios::in | ios::binary);
    if (fOLB.is_open())
    {
        fOLB.read((char *)&fullOLB, sizeof(bool));
        fOLB.read((char *)&ultimeOLB, sizeof(bool));
        fOLB.read((char *)&rushOLB, sizeof(bool));
        fOLB.close();
    }

    ifstream f3T("saves/records.dat", ios::in | ios::binary);
    if (!f3T.is_open())
    {
        return;
    }
    f3T.read((char *)&full3T, sizeof(bool));
    f3T.read((char *)&ultime3T, sizeof(bool));
    f3T.read((char *)&rush3T, sizeof(bool));
    f3T.read((char *)&bestTime, sizeof(int));

    f3T.close();
}

void GlobalSave::save()
{
    ofstream f("saves/records.dat", ios::out | ios::binary);
    f.write((char *)&full3T, sizeof(bool));
    f.write((char *)&ultime3T, sizeof(bool));
    f.write((char *)&rush3T, sizeof(bool));
    f.write((char *)&bestTime, sizeof(int));
    f.close();
}

void GlobalSave::erase()
{
    remove("saves/records.dat");
    full3T = false;
    ultime3T = false;
    rush3T = false;
    bestTime = -1;
}

void GlobalSave::update(Save *sv, bool endGame)
{
    bool needToSave = false;

    if (endGame)
    {
        if (!full3T && sv->getCompletion() == 100)
        {
            full3T = true;
            needToSave = true;
        }
        if (!ultime3T && !sv->getDeaths() && sv->getMaxLife() <= 24 && !sv->getFlacons(0) && !sv->getFlacons(1) && !sv->getFlacons(2) && !sv->getFlacons(3))
        {
            ultime3T = true;
            needToSave = true;
        }
        if (sv->getTime() < bestTime || bestTime == -1)
        {
            bestTime = sv->getTime();
            if (!rush3T && bestTime < 25200)
            {
                rush3T = true;
            }
            needToSave = true;
        }
    }

    if (needToSave)
    {
        save();
    }
}

bool GlobalSave::isFullROTH()
{
    return fullROTH;
}

bool GlobalSave::isUltimeROTH()
{
    return ultimeROTH;
}

bool GlobalSave::isRushROTH()
{
    return rushROTH;
}

bool GlobalSave::isFullOLB()
{
    return fullOLB;
}

bool GlobalSave::isUltimeOLB()
{
    return ultimeOLB;
}

bool GlobalSave::isRushOLB()
{
    return rushOLB;
}

bool GlobalSave::isFull3T()
{
    return full3T;
}

bool GlobalSave::isUltime3T()
{
    return ultime3T;
}

bool GlobalSave::isRush3T()
{
    return rush3T;
}

int GlobalSave::getBestTime()
{
    return bestTime;
}

bool GlobalSave::is9Ranks()
{
    return fullROTH && ultimeROTH && rushROTH && fullOLB && ultimeOLB && rushOLB && full3T && ultime3T && rush3T;
}
