#include "Interfaces/INamable.h"

Turtle::INamable::INamable(const std::string& name) :
	m_name(name)
{}

const std::string& Turtle::INamable::GetName() const { return m_name; }
void Turtle::INamable::SetName(const std::string& name) { m_name = name; }