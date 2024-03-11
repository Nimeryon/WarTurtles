// BoxCollisionComponent.h
#ifndef BOX_COLLISION_COMPONENT_H
#define BOX_COLLISION_COMPONENT_H
#include <SFML/Graphics.hpp>

#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class BoxCollisionComponent : public PolygonCollisionComponent
	{
	public:
		BoxCollisionComponent() = delete;
		explicit BoxCollisionComponent(GameObject* parent, const std::string& name = "Collision Component (Box)");

		void InitCollisionParameters(float width, float height);

		float GetWidth() const;
		float GetHeight() const;

		void SetWidth(float width);
		void SetHeight(float height);

		void DebugDraw(Window& window) override;

	protected:
		float m_width;
		float m_height;

	private:
		void _UpdateVertice();

		sf::VertexArray m_debugShape;
	};
}

#endif // BOX_COLLISION_COMPONENT_H