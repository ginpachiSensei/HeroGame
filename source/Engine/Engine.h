#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Container.h"
#include <list>

class CGameObject
{
private:
    std::string m_name;
    Vector m_pos, m_size;
    std::list<CGameObject *> m_objects;

public:
    CGameObject();
    virtual ~CGameObject();
    void setName(const std::string &name);
    const std::string &getName() const;
};

class CGame
{
private:
    sf::RenderWindow *m_window = NULL;
    Vector m_screen_size;
    CGameObject *m_root_object = NULL;

protected:
    void virtual init();

public:
    CGame(const std::string &name, const Vector &screen_size);
    ~CGame();
    void run();
};
