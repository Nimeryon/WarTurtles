// BoxObject.h
#ifndef BOX_OBJECT_H // include guard
#define BOX_OBJECT_H
#include "GameObject.h"

namespace sf
{
	class RectangleShape;
}

namespace Turtle
{
class Physic;
class BoxCollisionComponent;
template <typename ShapeType>
class ShapeRenderer;

// Static by default
class BoxObject : public GameObject
{
public:
	explicit BoxObject(const std::string& name = "Box Object", GameObject* parent = nullptr);

	void InitParameters(float width = 10, float height = 10, const sf::Color& color = sf::Color::White);
	void InitPhysicsParameters(const Vector2f& initialVelocity = { 0, 0 }, const Vector2f& initialAcceleration = { 0, 0 }, float mass = 0, float staticFriction = 0, float dynamicFriction = 0, float restitution = 0, float angularVelocity = 0);

	bool IsStatic() const;
	void SetStatic(bool isStatic);

	Vector2f GetSize() const;
	float GetWidth() const;
	float GetHeight() const;

	void SetSize(const Vector2f& size);
	void SetWidth(float width);
	void SetHeight(float height);

	Physic* GetPhysicComponent() const;
	BoxCollisionComponent* GetColliderComponent() const;
	ShapeRenderer<sf::RectangleShape>* GetShapeRendererComponent() const;

private:
	Physic* m_physicComponent; 
	BoxCollisionComponent* m_colliderComponent;
	ShapeRenderer<sf::RectangleShape>* m_shapeComponent;

	bool m_isStatic;
};
}

#endif /* BOX_OBJECT_H */