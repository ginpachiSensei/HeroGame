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
    m_root_object = new CGameObject();
    m_root_object->setName(name);
    m_screen_size = screen_size;
}

void CGame::run()
{
    m_window = new sf::RenderWindow(sf::VideoMode(m_screen_size.x, m_screen_size.y), m_root_object->getName());
    init();

    sf::Event event;
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    const sf::Time ups = sf::seconds(1.f / 60.f);

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
        sf::Time elapsedTime = clock.restart();
        accumulator += elapsedTime;

        while (accumulator > ups)
        {
            accumulator -= ups;
            sf::sleep(sf::milliseconds(10));
        }

        m_window->clear(sf::Color::Black);
        m_window->display();
    }
}
