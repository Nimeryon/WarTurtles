// IShape.h
#ifndef ISHAPE_H // include guard
#define ISHAPE_H
#include "Components/Transform.h"

namespace Turtle
{
class IShape {
public:
	IShape() {};
	virtual ~IShape() {};

	virtual void UpdateShapeFromTransform(Transform& transform) {};
};
}

#endif /* ISHAPE_H */