#pragma once

#include "Engine/GameEngine.h"

const std::string HERO_RES_PATH = "res/";

class CHeroGame : public CGame
{
private:
    CHeroGame();
    static CHeroGame *s_instance;
    virtual void init() override;

public:
    static CHeroGame *instance();
    ~CHeroGame();
};
