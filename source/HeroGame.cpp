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

void CHeroGame::clearScene()
{
    if (!m_scene_stack.empty())
    {
        for (auto m_scene : m_scene_stack)
        {
            getRootObject()->removeObject(m_scene);
        }
        m_scene_stack.clear();
    }
    m_current_scene = NULL;
}

void CHeroGame::setScene(CGameObject *new_scene)
{
    clearScene();
    m_current_scene = new_scene;
    new_scene->turnOff();
    getRootObject()->addObject(new_scene);
    m_scene_stack.push_back(new_scene);
    m_level_name = new_scene->castTo<CHeroGameScene>()->getLevelName();
}

void CHeroGame::loadLevel(const std::string &_level_name)
{
    std::string level_name = _level_name;
    // create new scene and set it to the current scene
    setScene(new CHeroGameScene(HERO_RES_PATH + "Levels/" + level_name + ".tmx"));
    m_gui_object->moveToFront();
    m_current_level_name = level_name;
}

void CHeroGame::setState(GameState state)
{
    m_game_state = state;
    switch (state)
    {
    case (GameState::main_menu):
    { // load first level
        loadLevel(m_first_level_name);
        // TODO
        // reset all stats of the game .. life etc
        // set the state in gui
        // update the scene
        // break
        std::cout << "main menu state";
    }
    }
}

void CHeroGame::init()
{
    getRootObject()->addObject(m_gui_object = new CHeroGUI());
    setState(GameState::main_menu);
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

//----------------------------------------------------------------------------------------

void CHeroGameScene::loadFromFile(const std::string &filepath)
{
    setName("HeroGameScene");
    m_level_name = filepath;
    // TODO
    // parse filepath for getting the level name
    // clear all assets of the previous level
    // load the level file from res/level
    // load all assets
}

void CHeroGameScene::init()
{
    setName("HeroGameScene");
    m_view.setSize(screen_size);
    CHeroGame::instance()->eventManager().subscribe(this);
}
const std::string &CHeroGameScene::getLevelName() const
{
    return m_level_name;
}

CHeroGameScene::CHeroGameScene(const std::string &filepath)
{
    loadFromFile(filepath);
    init();
}

CHeroGameScene::~CHeroGameScene()
{
    CHeroGame::instance()->eventManager().unsubcribe(this);
}

void CHeroGameScene::draw(sf::RenderWindow *render_window)
{
    render_window->setView(m_view);
    CGameObject::draw(render_window);
    render_window->setView(render_window->getDefaultView());
}