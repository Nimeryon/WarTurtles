// INamable.h
#ifndef INAMABLE_H // include guard
#define INAMABLE_H
#include <string>

namespace Turtle
{
struct INamable
{
	virtual ~INamable() = default;

	INamable(const std::string& name);
	INamable() = delete;

	virtual const std::string& GetName() const;
	virtual void SetName(const std::string& name);

protected:
	std::string m_name;
};
}

#endif /* INAMABLE_H */