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

	const std::string& GetName() const;
	void SetName(const std::string& name);

protected:
	std::string m_name;
};
}

#endif /* INAMABLE_H */