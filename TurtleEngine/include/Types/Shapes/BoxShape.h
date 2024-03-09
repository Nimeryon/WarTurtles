// BoxShape.h
#ifndef BOXSHAPE_H // include guard
#define BOXSHAPE_H
#include "Types/Shapes/PolygonShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
class BoxShape : public PolygonShape {
public:
	BoxShape() = delete;
	BoxShape(Vector2f& position, float rotation, float width, float height);

	float Width;
	float Height;

private:
	void CreateVertices() override;
};
}

#endif /* BOXSHAPE_H */