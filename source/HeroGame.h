#pragma once

#include "Engine/GameEngine.h"

const std::string HERO_RES_PATH = "res/";

class CHeroGUI;

class CHeroGame : public CGame
{
private:
    CHeroGame();
    static CHeroGame *s_instance;
    virtual void init() override;
    CHeroGUI *m_gui_object = NULL;

public:
    static CHeroGame *instance();
    ~CHeroGame();
};

CHeroGame &HeroGame();

class CHeroGUI : public CGameObject
{
public:
    CHeroGUI();

protected:
    void draw(sf::RenderWindow *render_window) override;

private:
    CLabel *m_game_logo;
};
