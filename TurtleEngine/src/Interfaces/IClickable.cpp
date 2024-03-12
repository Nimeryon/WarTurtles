// IClickable.cpp
#include "Interfaces/IClickable.h"

#include "App.h"

namespace Turtle
{
    Clickable::Clickable(sf::Shape* shape) : shape(shape)
    {
        callback = std::bind(&Clickable::CheckClick, this, std::placeholders::_1);
        App::GetInputManager()->AddClickCallback(callback);
    }

    Clickable::~Clickable()
    {
        App::GetInputManager()->RemoveClickCallback(callback);
    }

    void Clickable::OnClick(std::function<void()> callback)
    {
        callbacks.push_back(callback);
    }

    void Clickable::CheckClick(const Vector2i& clickPosition) const
    {
        if (shape->getGlobalBounds().contains({ static_cast<float>(clickPosition.x), static_cast<float>(clickPosition.y) }))
        {
            for (const auto& callback : callbacks)
            {
                callback();
            }
        }
    }
} // namespace Turtle
