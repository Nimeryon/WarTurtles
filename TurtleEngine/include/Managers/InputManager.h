// InputManager.h
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

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
        InputManager(sf::RenderWindow& window);
        InputManager(InputManager&) = delete;
        ~InputManager() = default;
        
        void AddCallback(std::function<void()> callback, EventType eventType);
        void RemoveCallback(std::function<void()> callback, EventType eventType);
        void AddClickCallback(std::function<void(sf::Vector2f)> callback);
        void RemoveClickCallback(std::function<void(sf::Vector2f)> callback);
        void HandleEvents();

    private:
        void Notify(EventType eventType);
        void NotifyClick(sf::Vector2f clickPosition);
        std::unordered_map<EventType, std::vector<std::function<void()>>> callbacks;
        std::vector<std::function<void(sf::Vector2f)>> clickCallbacks;
        sf::RenderWindow& m_window;
    };
}

#endif /* INPUT_MANAGER_H */