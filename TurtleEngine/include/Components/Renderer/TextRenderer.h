#ifndef TEXTRENDERER_H // include guard
#define TEXTRENDERER_H
#include "Components/Component.h"
#include "Interfaces/IDrawable.h"

namespace Turtle
{
    class TextRenderer final : public Component, public IDrawable
    {
    };
}

#endif

