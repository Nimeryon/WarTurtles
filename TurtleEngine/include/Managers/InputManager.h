// InputManager.h
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <functional>
#include <unordered_map>

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

    private:
        void Notify(EventType eventType);
        void NotifyClick(Vector2i clickPosition);
        std::unordered_map<EventType, std::vector<std::function<void()>>> callbacks;
        std::vector<std::function<void(Vector2i)>> clickCallbacks;
        Window& m_window;
    };
}

#endif /* INPUT_MANAGER_H */