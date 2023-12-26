// Time.h
#ifndef TIME_H // include guard
#define TIME_H
#include <SFML/System/Time.hpp>

namespace Turtle
{
using Time = sf::Time;

static Time Seconds(float seconds) { return sf::seconds(seconds); }
static Time MilliSeconds(int milliSeconds) { return sf::microseconds(milliSeconds); }
static Time MicroSeconds(long long microSeconds) { return sf::microseconds(microSeconds); }
}

#endif /* TIME_H */