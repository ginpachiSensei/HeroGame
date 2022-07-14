#include "HeroGame.h"

HeroGame *HeroGame::s_instance = NULL;

HeroGame::HeroGame() : CGame("HeroGame", {1280, 720})
{
    printf("Hero Game");
}

HeroGame::~HeroGame() {}

HeroGame *HeroGame::instance()
{
    if (s_instance == NULL)
        s_instance = new HeroGame();
    return s_instance;
}

void HeroGame::init() {}