#include "Utils/Time.h"

Turtle::Time Turtle::Time::Seconds(float seconds)
{
	return Time(sf::seconds(seconds));
}
Turtle::Time Turtle::Time::MilliSeconds(int milliSeconds)
{
	return Time(sf::milliseconds(milliSeconds));
}
Turtle::Time Turtle::Time::MicroSeconds(long long microSeconds)
{
	return Time(sf::microseconds(microSeconds));
}

Turtle::Time Turtle::Time::operator=(const sf::Time& time)
{
	return Time(time);
}
