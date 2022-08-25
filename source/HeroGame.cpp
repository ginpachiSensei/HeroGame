#include "HeroGame.h"

HeroGame *HeroGame::s_instance = NULL;

HeroGame::HeroGame() : CGame("HeroGame", {1280, 720})
{
    const std::string texture_dir = HERO_RES_PATH + "Textures/";
    for (std::string texture : {"sky"})
    {
        textureManager().loadFromFile(texture, texture_dir + "Background/" + texture + ".png");
        textureManager().get(texture)->setRepeated(true);
    }
}

HeroGame::~HeroGame() {}

HeroGame *HeroGame::instance()
{
    if (s_instance == NULL)
        s_instance = new HeroGame();
    return s_instance;
}

void HeroGame::init() {}