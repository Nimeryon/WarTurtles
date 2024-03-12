// App.h
#ifndef APP_H // include guard
#define APP_H
#include "Managers/InputManager.h"
#include "Utils/Clock.h"
#include "Utils/Singleton.h"
#include "Utils/Time.h"
#include "Utils/Window.h"

namespace Turtle
{
class App
{
public:
    App(Window& window, const Time& logicTime = Seconds(1.f / 60.f));
    static InputManager* GetInputManager();
    void Run();
    static void Quit();

private:
    Window& m_window;
    static std::unique_ptr<InputManager> m_inputManager;
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