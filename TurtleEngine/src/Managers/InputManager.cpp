// InputManager.cpp
#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Managers/InputManager.h"
#include "Managers/SceneManager.h"

namespace Turtle
{
InputManager::InputManager(Window& window) :
    m_window(window),
    m_windowHasFocus(true),
    m_keyboardState({}),
    m_oldKeyboardState({}),
    m_keyCtrl(false),
    m_keyAlt(false),
    m_keyShift(false),
    m_mouseState({}),
    m_oldMouseState({})
{}

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
    m_oldKeyboardState = m_keyboardState;
    m_oldMouseState = m_mouseState;
    m_keyboardState.fill(false);
    m_mouseState.fill(false);

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;

            // Window Focus Events
        case sf::Event::LostFocus:
            m_keyboardState.fill(false);
            m_mouseState.fill(false);

            m_keyCtrl = false;
            m_keyAlt = false;
            m_keyShift = false;

            m_windowHasFocus = false;
            break;

        case sf::Event::GainedFocus:
            m_windowHasFocus = true;
            break;


        case sf::Event::KeyPressed:
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
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                const auto& mousePos = sf::Mouse::getPosition(m_window);
                NotifyClick(Vector2i(mousePos.x, mousePos.y));
            }
            break;
        }

        if (m_windowHasFocus)
        {
            switch (event.type)
            {
            // Keyboard Events
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            {
                int keyCode = event.key.code;
                if (keyCode >= 0 && keyCode < sf::Keyboard::KeyCount)
                    m_keyboardState[keyCode] = event.type == sf::Event::KeyPressed;
                m_keyCtrl = event.key.control;
                m_keyAlt = event.key.alt;
                m_keyShift = event.key.shift;
            }
            break;

            // Mouse Button Events
            case sf::Event::MouseButtonPressed:
            case::sf::Event::MouseButtonReleased:
            {
                int buttonCode = event.key.code;
                m_mouseState[buttonCode] = event.type == sf::Event::MouseButtonPressed;
            }
            break;

            // Mouse Move Event
            case sf::Event::MouseMoved:
                sf::Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
                m_mousePosition = { mousePos.x, mousePos.y };
                break;
            }
        }

        ImGui::SFML::ProcessEvent(m_window, event);
    }

    SceneManager::Instance().ProcessInputs(*this);
}

}
