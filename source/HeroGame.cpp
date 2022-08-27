#include "HeroGame.h"

CHeroGame *CHeroGame::s_instance = NULL;

CHeroGame::CHeroGame() : CGame("HeroGame", {1280, 720})
{
    const std::string texture_dir = HERO_RES_PATH + "Textures/";
    for (std::string texture : {"sky"})
    {
        textureManager().loadFromFile(texture, texture_dir + "Background/" + texture + ".png");
        textureManager().get(texture)->setRepeated(true);
    }
}

CHeroGame::~CHeroGame() {}

CHeroGame *CHeroGame::instance()
{
    if (s_instance == NULL)
        s_instance = new CHeroGame();
    return s_instance;
}

void CHeroGame::init() {}