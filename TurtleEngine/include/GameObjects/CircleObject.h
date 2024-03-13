// CircleObject.h
#ifndef CIRCLE_OBJECT_H // include guard
#define CIRCLE_OBJECT_H
#include "GameObject.h"

namespace sf
{
	class CircleShape;
}

namespace Turtle
{
	class Physic;
	class CircleCollisionComponent;
	template <typename ShapeType>
	class ShapeRenderer;

	// Static by default
	class CircleObject : public GameObject
	{
	public:
		explicit CircleObject(const std::string& name = "Circle Object", GameObject* parent = nullptr);

		void InitParameters(float radius = 10, const Vector2f& center = { 0, 0 }, const sf::Color & color = sf::Color::White);
		void InitPhysicsParameters(const Vector2f& initialVelocity = { 0, 0 }, const Vector2f& initialAcceleration = { 0, 0 }, float mass = 1, float friction = 0, float restitution = 0.5f, float angularVelocity = 0);

		bool IsStatic() const;
		void SetStatic(bool isStatic);

		float GetRadius() const;
		const Vector2f& GetCenter() const;

		void SetRadius(float radius);
		void SetCenter(const Vector2f& center);

		Physic* GetPhysicComponent() const;
		CircleCollisionComponent* GetColliderComponent() const;
		ShapeRenderer<sf::CircleShape>* GetShapeRendererComponent() const;

	private:
		Physic* m_physicComponent;
		CircleCollisionComponent* m_colliderComponent;
		ShapeRenderer<sf::CircleShape>* m_shapeComponent;

		bool m_isStatic;
	};
}

#endif /* CIRCLE_OBJECT_H */