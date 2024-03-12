// IClickable.h
#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <functional>
#include <SFML/Graphics.hpp>

#include "Types/Vector2.h"

namespace Turtle
{
    class Clickable
    {
    public:
        Clickable(sf::Shape* shape);
        virtual ~Clickable();

        void OnClick(std::function<void()> callback);

    private:
        void CheckClick(const Vector2i& clickPosition) const;
        sf::Shape* shape;
        std::vector<std::function<void()>> callbacks;
        std::function<void(Vector2i)> callback;
    };
} // namespace Turtle

#endif /* ICLICKABLE_H */
