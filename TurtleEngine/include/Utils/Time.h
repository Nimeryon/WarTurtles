// Time.h
#ifndef TIME_H // include guard
#define TIME_H
#include <SFML/System/Time.hpp>

namespace Turtle
{
class Time : public sf::Time
{
public:
	static Time Seconds(float seconds);
	static Time MilliSeconds(int milliSeconds);
	static Time MicroSeconds(long long microSeconds);

	Time operator=(const sf::Time& time);
};
}

#endif /* TIME_H */