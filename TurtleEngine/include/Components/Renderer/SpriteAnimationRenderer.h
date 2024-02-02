#ifndef SPRITEANIMATIONRENDERER_H // include guard
#define SPRITEANIMATIONRENDERER_H
#include "Components/Component.h"
#include "Interfaces/IDrawable.h"

namespace Turtle
{
    class SpriteAnimationRenderer final : public Component, public IDrawable
    {
    };
}

#endif

