#include "HeroGame.h"

CHeroGame *CHeroGame::s_instance = NULL;

CHeroGame::CHeroGame() : CGame("HeroGame", {1280, 720})
{
    const std::string textures_dir = HERO_RES_PATH + "Textures/";

    for (auto texture : {"Logo"})
        textureManager().loadFromFile(texture, textures_dir + texture + ".png");

    for (std::string texture : {"sky"})
    {
        textureManager().loadFromFile(texture, textures_dir + "Backgrounds/" + texture + ".png");
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

void CHeroGame::init()
{
    getRootObject()->addObject(m_gui_object = new CHeroGUI());
}

//----------------------------------------------------------------------------------------

CHeroGame &HeroGame()
{
    return *CHeroGame::instance();
}

//----------------------------------------------------------------------------------------

CHeroGUI::CHeroGUI()
{
    const int y_gui_pos = 5;
    m_game_logo = new CLabel(sf::Sprite(*CHeroGame::instance()->textureManager().get("Logo"), {0, 0, 750, 300}));
    m_game_logo->setPosition(280, 70);
    addObject(m_game_logo);
}

void CHeroGUI::draw(sf::RenderWindow *render_window)
{
    CGameObject::draw(render_window);
}