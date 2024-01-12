#include "Interfaces/IActivable.h"

Turtle::IActivable::IActivable(bool active)
{
	SetActive(active);
}

bool Turtle::IActivable::IsActive() const { return m_isActive; }
void Turtle::IActivable::SetActive(bool active)
{
	m_isActive = active;
	m_isActive ? OnActivate() : OnDeactivate();
}
