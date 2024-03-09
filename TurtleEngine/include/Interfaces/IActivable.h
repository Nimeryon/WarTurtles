// IActivable.h
#ifndef IACTIVABLE_H // include guard
#define IACTIVABLE_H

namespace Turtle
{
struct IActivable
{
	IActivable(bool active = true);
	virtual ~IActivable() = default;

	virtual bool IsActive() const;
	virtual void SetActive(bool active);

	virtual void OnActivate() {}
	virtual void OnDeactivate() {}

protected:
	bool m_isActive;
};
}

#endif /* IACTIVABLE_H */