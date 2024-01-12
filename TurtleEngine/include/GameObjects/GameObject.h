// GameObject.h
#ifndef GAME_OBJECT_H // include guard
#define GAME_OBJECT_H
#include "Interfaces/IActivable.h"
#include "Interfaces/INamable.h"
#include "Interfaces/IObject.h"

namespace Turtle
{
class GameObject : public INamable, public IObject, public IActivable
{
public:
	GameObject(const std::string& name, GameObject* parent = nullptr);

	GameObject* GetChild(const int& index) const;
	// Return first child with name
	GameObject* GetChild(const std::string& name) const;
	const std::vector<GameObject*> GetChildren() const;

	void SetParent(GameObject* object);
	void AddChildren(GameObject* object);
	void RemoveChildren(GameObject* object);
	void RemoveFromParent();

protected:
	GameObject* m_parent;
	std::vector<GameObject*> m_children;
};
}

#endif /* GAME_OBJECT_H */