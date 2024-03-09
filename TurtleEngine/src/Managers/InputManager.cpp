#include "Managers/InputManager.h"

#include <imgui-SFML.h>

#include "Managers/SceneManager.h"

Turtle::InputManager::InputManager(sf::RenderWindow& window):m_window(window){}

void Turtle::InputManager::AddCallback(std::function<void()> callback, EventType eventType) {
    callbacks[eventType].push_back(callback);
}

void Turtle::InputManager::RemoveCallback(std::function<void()> callback, EventType eventType) {
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
void Turtle::InputManager::Notify(EventType eventType) {
    const auto& callbacksForEvent = callbacks[eventType];
    for (auto& callback : callbacksForEvent) {
        callback();
    }
}

void Turtle::InputManager::HandleEvents() {
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
        ImGui::SFML::ProcessEvent(m_window, event);
    }

}
