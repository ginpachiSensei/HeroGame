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

void CHeroGame::setScene(CGameObject *new_scene)
{
    m_current_scene = new_scene;
    new_scene->turnOff();
    getRootObject()->addObject(new_scene);
    m_scene_stack.push_back(new_scene);
    m_level_name = new_scene->getName();
}

void CHeroGame::setState(GameState state)
{
    m_game_state = state;
    switch (state)
    {
        case(GameState::main_menu){
            loadLevel(m_first_level);
            m_gui_object->setState(GUIState::menu);
            m_current_scene->enable();
            m_current_scene->update(0);
            m_current_scene->disable();
            break;
        }
    }
}

void CHeroGame::init()
{
    getRootObject()->addObject(m_gui_object = new CHeroGUI());
    setState(GameState::main_menu);
}

void CHeroGame::loadLevel(const std::string &_level_name)
{
    std::string level_name = _level_name;
    // create new scene and set it to the current scene
    m_current_stage_name = level_name;
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