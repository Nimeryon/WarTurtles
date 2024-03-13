#include "GameObjects/BoxObject.h"
#include "Components/Physic.h"
#include "Components/Collisions/BoxCollisionComponent.h"
#include "Components/Renderer/ShapeRenderer.h"

Turtle::BoxObject::BoxObject(const std::string& name, GameObject* parent) :
	GameObject(name, parent),
	m_isStatic(true)
{
	m_physicComponent = AddComponent<Turtle::Physic>();
	m_physicComponent->SetActive(false);

	m_colliderComponent = AddComponent<Turtle::BoxCollisionComponent>();
	m_shapeComponent = AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();

	InitParameters();
}

void Turtle::BoxObject::InitParameters(float width, float height, const sf::Color& color)
{
	m_colliderComponent->InitCollisionParameters(width, height);
	m_shapeComponent->GetShape().setFillColor(color);
	SetSize({ width, height });
}
void Turtle::BoxObject::InitPhysicsParameters(const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float staticFriction, float dynamicFriction, float restitution, float angularVelocity)
{
	m_physicComponent->InitPhysicParameters(initialVelocity, initialAcceleration, mass, staticFriction, dynamicFriction, restitution, angularVelocity);
	m_physicComponent->SetActive(true);
	m_isStatic = false;
}

bool Turtle::BoxObject::IsStatic() const { return m_isStatic; }
void Turtle::BoxObject::SetStatic(bool isStatic)
{
	m_isStatic = isStatic;
	m_physicComponent->SetActive(m_isStatic);
}

Turtle::Vector2f Turtle::BoxObject::GetSize() const
{
	return { GetWidth(), GetHeight() };
}
float Turtle::BoxObject::GetWidth() const { return m_shapeComponent->GetShape().getSize().x; }
float Turtle::BoxObject::GetHeight() const { return m_shapeComponent->GetShape().getSize().y; }

void Turtle::BoxObject::SetSize(const Vector2f& size)
{
	m_colliderComponent->InitCollisionParameters(size.x, size.y);
	m_shapeComponent->GetShape().setSize({ size.x, size.y });
	m_shapeComponent->SetOrigin({ size.x / 2.f, size.y / 2.f });
}
void Turtle::BoxObject::SetWidth(float width) { SetSize({ width, GetHeight() }); }
void Turtle::BoxObject::SetHeight(float height) { SetSize({ GetWidth(), height }); }

Turtle::Physic* Turtle::BoxObject::GetPhysicComponent() const { return m_physicComponent; }
Turtle::BoxCollisionComponent* Turtle::BoxObject::GetColliderComponent() const { return m_colliderComponent; }
Turtle::ShapeRenderer<sf::RectangleShape>* Turtle::BoxObject::GetShapeRendererComponent() const { return m_shapeComponent; }