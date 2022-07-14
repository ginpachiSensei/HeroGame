#pragma once
#include "SFML/Graphics.hpp"
#include <string>

struct screen_size
{
    int x, y;
};

class CGame
{
private:
    sf::RenderWindow *m_window = NULL;
    screen_size m_screen_size;
    std::string m_name;

protected:
    void virtual init();

public:
    CGame(const std::string &name, const screen_size &screen_size);
    ~CGame();
    void run();
};
