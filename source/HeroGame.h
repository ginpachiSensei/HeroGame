#pragma once

#include "Engine/Engine.h"

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
