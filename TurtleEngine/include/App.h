// App.h
#ifndef APP_H // include guard
#define APP_H
#include "Utils/Clock.h"
#include "Utils/Time.h"

namespace sf
{
    class RenderWindow;
}

namespace Turtle
{
class App
{
public:
    App(sf::RenderWindow& window, const Time& logicTime = Time::Seconds(1.f / 60.f));

    void Run();

private:
    sf::RenderWindow& m_window;

    Clock m_clock;
    Time m_logicTime;
    Time m_currentLogicTime;

    void _ProcessInputs();
    void _Update(const Time& deltaTime);
    void _FixedUpdate(const Time& deltaTime);
    void _Draw(const Time& deltaTime);
};
}

#endif /* APP_H */