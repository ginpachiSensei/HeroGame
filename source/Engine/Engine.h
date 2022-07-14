#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Container.h"

class CGame
{
private:
    sf::RenderWindow *m_window = NULL;
    Vector m_screen_size;
    std::string m_name;

protected:
    void virtual init();

public:
    CGame(const std::string &name, const Vector &screen_size);
    ~CGame();
    void run();
};
