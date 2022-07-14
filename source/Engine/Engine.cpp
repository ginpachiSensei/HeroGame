#include "Engine.h"

CGameObject::CGameObject() {}
CGameObject::~CGameObject()
{
    for (auto &obj : m_objects)
    {
        delete obj;
    }
    m_objects.clear();
}
void CGameObject::setName(const std::string &name)
{
    m_name = name;
}
const std::string &CGameObject::getName() const
{
    return m_name;
}

//---------------------------------------------------------------------------------------------------------

void CGame::init() {}

CGame::~CGame() {}

CGame::CGame(const std::string &name, const Vector &screen_size)
{
    m_name = name;
    m_screen_size = screen_size;
}

void CGame::run()
{
    m_window = new sf::RenderWindow(sf::VideoMode(m_screen_size.x, m_screen_size.y), m_name);
    init();

    sf::Event event;

    while (true) // game loop
    {
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
            {
                m_window->close();
                exit(0);
            }
        }
    }
}
