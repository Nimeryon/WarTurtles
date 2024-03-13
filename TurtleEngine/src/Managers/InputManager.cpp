// InputManager.cpp
#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Managers/InputManager.h"
#include "Managers/SceneManager.h"

namespace Turtle
{
InputManager::InputManager(Window& window):m_window(window){}

void InputManager::AddCallback(std::function<void()> callback, EventType eventType) {
    m_callbacks[eventType].push_back(callback);
}

void InputManager::RemoveCallback(std::function<void()> callback, EventType eventType) {
    auto& callbacksForEvent = m_callbacks[eventType];
        
    callbacksForEvent.erase(
        std::remove_if(
            callbacksForEvent.begin(),
            callbacksForEvent.end(),
            [&callback](const std::function<void()>& storedCallback) {
                return storedCallback.target<void()>() == callback.target<void()>();
            }
        ),
        callbacksForEvent.end()
    );
}

void InputManager::AddClickCallback(std::function<void(Vector2i)> callback) {
    m_clickCallbacks.push_back(callback);
}

void InputManager::RemoveClickCallback(std::function<void(Vector2i)> callback) {
    m_clickCallbacks.erase(
        std::remove_if(
            m_clickCallbacks.begin(),
            m_clickCallbacks.end(),
            [&callback](const std::function<void(Vector2i)>& storedCallback) {
                return storedCallback.target<void(Vector2i)>() == callback.target<void(Vector2i)>();
            }
        ),
        m_clickCallbacks.end()
    );
}

// KeyBoard Properties

bool InputManager::IsKey(const sf::Keyboard::Key& key) const { return m_keyboardState[key]; }
bool InputManager::IsKeyDown(const sf::Keyboard::Key& key) const { return m_keyboardState[key] && !m_oldKeyboardState[key]; }
bool InputManager::IsKeyUp(const sf::Keyboard::Key& key) const { return !m_keyboardState[key] && m_oldKeyboardState[key]; }
bool InputManager::Ctrl() const { return m_keyCtrl; }
bool InputManager::Alt() const { return m_keyAlt; }
bool InputManager::Shift() const { return m_keyShift; }

// Mouse Properties

const Turtle::Vector2f& InputManager::GetMousePosition() const { return m_mousePosition; }

bool InputManager::IsPointer(const sf::Mouse::Button& button) const { return m_mouseState[button]; }
bool InputManager::IsPointerDown(const sf::Mouse::Button& button) const { return m_mouseState[button] && !m_oldMouseState[button]; }
bool InputManager::IsPointerUp(const sf::Mouse::Button& button) const { return !m_mouseState[button] && m_oldMouseState[button]; }

void InputManager::Notify(EventType eventType) {
    const auto& callbacksForEvent = m_callbacks[eventType];
    for (auto& callback : callbacksForEvent) {
        callback();
    }
}

void InputManager::NotifyClick(Vector2i clickPosition) {
    for (auto& clickCallback : m_clickCallbacks) {
        if(!clickCallback)continue;
        clickCallback(clickPosition);
    }
}

void InputManager::HandleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                Notify(EventType::Jump);
            }
            if (event.key.code == sf::Keyboard::Left) {
                Notify(EventType::Left);
            }
            if (event.key.code == sf::Keyboard::Right) {
                Notify(EventType::Right);
            }
            if (event.key.code == sf::Keyboard::I) {
                Notify(EventType::Inventory);
            }
            if (event.key.code == sf::Keyboard::Space) {
                Notify(EventType::Shoot);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                Notify(EventType::Validate);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                const auto& mousePos = sf::Mouse::getPosition(m_window);
                NotifyClick(Vector2i(mousePos.x, mousePos.y));
            }
        }

        ImGui::SFML::ProcessEvent(m_window, event);
    }

    SceneManager::Instance().ProcessInputs();
}

}
