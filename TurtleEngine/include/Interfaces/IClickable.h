// IClickable.h
#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <functional>
#include <SFML/Graphics.hpp>

namespace Turtle
{
    class Clickable
    {
    public:
        Clickable(sf::Shape* shape);
        virtual ~Clickable() = default;

        void OnClick(std::function<void()> callback);

    private:
        void CheckClick(const sf::Vector2f& clickPosition) const;
        sf::Shape* shape;
        std::vector<std::function<void()>> callbacks;
    };
} // namespace Turtle

#endif /* ICLICKABLE_H */
