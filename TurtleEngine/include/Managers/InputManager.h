// InputManager.h
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <functional>
#include <array>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Utils/Window.h"
#include "Types/Vector2.h"

namespace Turtle
{
enum class EventType {
    Jump,
    Left,
    Right,
    Validate,
    Shoot,
    Inventory,
    Click
};

class InputManager final {
public:
    InputManager() = delete;
    InputManager(Window& window);
    InputManager(InputManager&) = delete;
    ~InputManager() = default;
        
    void AddCallback(std::function<void()> callback, EventType eventType);
    void RemoveCallback(std::function<void()> callback, EventType eventType);
    void AddClickCallback(std::function<void(Vector2i)> callback);
    void RemoveClickCallback(std::function<void(Vector2i)> callback);
    void HandleEvents();

    // KeyBoard Properties

    bool IsKey(const sf::Keyboard::Key& key) const;
    bool IsKeyDown(const sf::Keyboard::Key& key) const;
    bool IsKeyUp(const sf::Keyboard::Key& key) const;
    bool Ctrl() const;
    bool Alt() const;
    bool Shift() const;

    // Mouse Properties

    const Vector2f& GetMousePosition() const;

    bool IsPointer(const sf::Mouse::Button& button) const;
    bool IsPointerDown(const sf::Mouse::Button& button) const;
    bool IsPointerUp(const sf::Mouse::Button& button) const;

private:
    void Notify(EventType eventType);
    void NotifyClick(Vector2i clickPosition);

    std::unordered_map<EventType, std::vector<std::function<void()>>> m_callbacks;
    std::vector<std::function<void(Vector2i)>> m_clickCallbacks;
    Window& m_window;

    bool m_windowHasFocus;

    // KeyBoard
    std::array<bool, sf::Keyboard::KeyCount> m_keyboardState;
    std::array<bool, sf::Keyboard::KeyCount> m_oldKeyboardState;
    bool m_keyCtrl;
    bool m_keyAlt;
    bool m_keyShift;

    // Mouse
    Vector2f m_mousePosition;
    std::array<bool, sf::Mouse::ButtonCount> m_mouseState;
    std::array<bool, sf::Mouse::ButtonCount> m_oldMouseState;
};
}

#endif /* INPUT_MANAGER_H */