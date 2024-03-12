﻿// IClickable.cpp
#include "Interfaces/IClickable.h"

#include "App.h"

namespace Turtle
{
    Clickable::Clickable(sf::Shape* shape) : shape(shape)
    {
        App::GetInputManager()->AddClickCallback(std::bind(&Clickable::CheckClick, this, std::placeholders::_1));
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
