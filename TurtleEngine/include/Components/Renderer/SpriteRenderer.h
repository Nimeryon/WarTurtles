#ifndef SPRITERENDERER_H // include guard
#define SPRITERENDERER_H
#include "Components/Component.h"
#include "Interfaces/IDrawable.h"

namespace Turtle
{
    class SpriteRenderer final : public Component, public IDrawable
    {
    };
}

#endif

