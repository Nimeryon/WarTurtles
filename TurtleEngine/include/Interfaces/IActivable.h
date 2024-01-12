// IActivable.h
#ifndef IACTIVABLE_H // include guard
#define IACTIVABLE_H

namespace Turtle
{
struct IActivable
{
	IActivable(bool active = true);

	bool IsActive() const;
	void SetActive(bool active);

	virtual void OnActivate() {}
	virtual void OnDeactivate() {}

protected:
	bool m_isActive;
};
}

#endif /* IACTIVABLE_H */