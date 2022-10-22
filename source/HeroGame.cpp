#include "HeroGame.h"
#include <iomanip>

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

void CHeroGame::updateGUI()
{
    m_gui_object->setGameTime(m_game_time / 1000);
    m_gui_object->setLevelName(m_level_name);
    m_gui_object->setLives(m_lives);
    m_gui_object->setScore(m_score);
}

void CHeroGame::reset()
{
    m_lives = 3;
    m_score = 0;
    m_delay_timer = 0;
    updateGUI();
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
        reset();
        // set the state in gui
        m_gui_object->setState(GUIState::menu);
        // update the scene
        m_current_scene->enable();
        m_current_scene->update(0);
        m_current_scene->disable();
        m_current_scene->show();
        std::cout << "main menu state";
        break;
    }
    }
}

void CHeroGame::init()
{
    getRootObject()->addObject(m_gui_object = new CHeroGUI());
    setState(GameState::main_menu);
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

//----------------------------------------------------------------------------------------

CHeroGUI::CHeroGUI()
{
    const int y_gui_pos = 5;

    m_score_lab = new CLabel();
    // m_score_lab->setFontName(*MarioGame().fontManager().get("some_font"));
    // m_score_lab->setPosition({70, y_gui_pos});
    // m_score_lab->setFontStyle(sf::Text::Bold);
    // m_score_lab->setFontColor({255, 255, 220});
    // m_score_lab->setFontSize(40);
    // m_score_lab->setTextAlign(CLabel::left);
    addObject(m_score_lab);

    m_timer = createLabel();
    m_timer->setPosition({1080, y_gui_pos});
    addObject(m_timer);

    m_game_logo = new CLabel(sf::Sprite(*CHeroGame::instance()->textureManager().get("Logo"), {0, 0, 750, 300}));
    m_game_logo->setPosition(280, 70);
    addObject(m_game_logo);
}

void CHeroGUI::update(int delta_time)
{
    CGameObject::update(delta_time);
}

void CHeroGUI::draw(sf::RenderWindow *render_window)
{
    CGameObject::draw(render_window);
}

void CHeroGUI::setGameTime(int time)
{
    std::stringstream str;
    str << "TIME:" << std::setw(3) << std::setfill('0') << time;
    m_timer->setString(str.str());
}

CLabel *CHeroGUI::createLabel()
{
    return m_score_lab->clone();
}

void CHeroGUI::setLevelName(const std::string &level_name)
{
    m_level_name->setString(level_name);
}

void CHeroGUI::setScore(int value)
{
    std::stringstream str;
    str << "HERO:" << std::setw(6) << std::setfill('0') << value;
    m_score_lab->setString(str.str());
}

void CHeroGUI::setLives(int value)
{
    m_lives->setString("  X  " + toString(value));
}

void CHeroGUI::setState(GUIState state)
{
    m_state = state;

    // // clang-format off
    // CGameObject *states_labs[3][5] =
    // {
    //     {},
    //     {},
    //     {}
    // };
    // // clang-format on

    // for (CGameObject **state_labs : states_labs)
    // {
    //     for (int i = 0; state_labs[i]; i++)
    //     {
    //         state_labs[i]->turnOff();
    //     }
    // }

    // if (state == GUIState::normal)
    //     return;

    // CGameObject **state_labs = states_labs[(int)state - 1];
    // for (int i = 0; state_labs[i]; i++)
    // {
    //     state_labs[i]->turnOn();
    // }
}

CHeroGUI::~CHeroGUI()
{
}