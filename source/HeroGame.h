#pragma once

#include "Engine/GameEngine.h"

const std::string HERO_RES_PATH = "res/";

class CHeroGUI;

class CHeroGame : public CGame
{
public:
    static CHeroGame *instance();
    ~CHeroGame();

private:
    CHeroGame();
    static CHeroGame *s_instance;
    virtual void init() override;
    CHeroGUI *m_gui_object = NULL;
    enum class GameState
    {
        main_menu
    } m_game_state = GameState::main_menu;
    std::vector<CGameObject *> m_scene_stack;
    void clearScene();
    void loadLevel(const std::string &level_name);
    CGameObject *m_current_scene = NULL;
    std::string m_level_name;
    void setScene(CGameObject *new_scene);
    std::string m_first_level_name;
    void setState(GameState state);
    std::string m_current_level_name;
};

// CHeroGame &HeroGame();

// enum class GUIState
// {
//     normal,
//     status,
//     menu,
//     gameover
// };

class CHeroGUI : public CGameObject
{
public:
    CHeroGUI();

protected:
    void draw(sf::RenderWindow *render_window) override;

private:
    CLabel *m_game_logo;
};

class CHeroGameScene : public CGameObject
{
public:
    CHeroGameScene(const std::string &filepath);
    ~CHeroGameScene();
    const std::string &getLevelName() const;
    void loadFromFile(const std::string &filepath);

private:
    sf::View m_view;
    const float scale_factor = 1.5f;
    const Vector screen_size = {1280 / scale_factor, 720 / scale_factor};
    std::string m_level_name;
    void init();
};