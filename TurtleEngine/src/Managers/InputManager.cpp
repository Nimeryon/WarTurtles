﻿// InputManager.cpp
#include "Managers/InputManager.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Turtle
{
    InputManager::InputManager(sf::RenderWindow& window):m_window(window){}

    void InputManager::AddCallback(std::function<void()> callback, EventType eventType) {
        callbacks[eventType].push_back(callback);
    }

    void InputManager::RemoveCallback(std::function<void()> callback, EventType eventType) {
        auto& callbacksForEvent = callbacks[eventType];
        
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

    void InputManager::AddClickCallback(std::function<void(sf::Vector2f)> callback) {
        clickCallbacks.push_back(callback);
    }

    void InputManager::RemoveClickCallback(std::function<void(sf::Vector2f)> callback) {
        clickCallbacks.erase(
            std::remove_if(
                clickCallbacks.begin(),
                clickCallbacks.end(),
                [&callback](const std::function<void(sf::Vector2f)>& storedCallback) {
                    return storedCallback.target<void(sf::Vector2f)>() == callback.target<void(sf::Vector2f)>();
                }
            ),
            clickCallbacks.end()
        );
    }

    void InputManager::Notify(EventType eventType) {
        const auto& callbacksForEvent = callbacks[eventType];
        for (auto& callback : callbacksForEvent) {
            callback();
        }
    }

    void InputManager::NotifyClick(sf::Vector2f clickPosition) {
        for (auto& clickCallback : clickCallbacks) {
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
                    NotifyClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
            }
        }
    }
}
