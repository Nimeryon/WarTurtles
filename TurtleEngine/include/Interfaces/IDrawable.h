// IObject.h
#ifndef IDRAWABLE_H // include guard
#define IDRAWABLE_H
#include "Utils/Window.h"

namespace Turtle
{
    struct IDrawable
    {
        virtual ~IDrawable() = default;
        
        // Called every frame before GUI
        virtual void Draw(Window& window) {}
    };
}

#endif /* IDRAWABLE_H */