// GameObject.h
#ifndef GAME_OBJECT_H // include guard
#define GAME_OBJECT_H
#include "Interfaces/IActivable.h"
#include "Interfaces/INamable.h"
#include "Interfaces/IObject.h"
#include "Components/Component.h"

namespace Turtle
{
	class Transform;
}

namespace Turtle
{
class GameObject : public INamable, public IObject, public IActivable
{
public:
	GameObject() = delete;
	GameObject(const std::string& name, GameObject* parent = nullptr, const std::string& tags = "");

	~GameObject() override;

	// =====================
	// Tags
	// =====================

	const std::vector<std::string> GetTags() const;
	const std::string& GetTagsString() const;

	// Tags separated by ',': Player,Object
	bool CompareTags(const std::string& tags) const;
	// Tags separated by ',': Player,Object
	bool CompareTags(const std::vector<std::string>& tags) const;

	// Tags separated by ',': Player,Object
	void AddTags(const std::string& tagsToAdd);
	// Tags separated by ',': Player,Object
	void RemoveTags(const std::string& tagsToRemove);

	// =====================
	// Children
	// =====================

	GameObject* GetChild(const int& index) const;
	// Return first child with name
	GameObject* GetChildWidthName(const std::string& name) const;
	// Return first child with tags
	GameObject* GetChildWithTags(const std::string& tags) const;
	// Return all children with name
	const std::vector<GameObject*> GetChildrenWithName(const std::string& name) const;
	// Return all children with tags
	const std::vector<GameObject*> GetChildrenWithTags(const std::string& tags) const;
	// return all children
	const std::vector<GameObject*>& GetChildren() const;

	void SetParent(GameObject* object);
	void AddChild(GameObject* object);
	void RemoveChild(GameObject* object);
	void RemoveFromParent();

	// =====================
	// Components
	// =====================
	
	Transform* GetTransform() const;

	const std::vector<Component*>& GetComponents() const;

	template<typename Type>
	Type* GetComponent() const;
	template<typename Type>
	Type* GetOrAddComponent();

	template<typename Type>
	Type* AddComponent();
	template<typename Type>
	void RemoveComponent();

protected:
	// tags separated by ','
	std::string m_tags;

	// Objects
	std::vector<GameObject*> m_children;
	GameObject* m_parent;

	// Components
	std::vector<Component*> m_components;
	Transform* m_transform;
};
}

#include "GameObject.hxx"

#endif /* GAME_OBJECT_H */