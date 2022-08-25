#pragma once

#include "Engine/GameEngine.h"

const std::string HERO_RES_PATH = "res/";

class HeroGame : public CGame
{
private:
    HeroGame();
    static HeroGame *s_instance;
    virtual void init() override;

public:
    static HeroGame *instance();
    ~HeroGame();
};
