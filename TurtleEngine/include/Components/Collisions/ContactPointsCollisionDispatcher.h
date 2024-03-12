// ContactPointsCollisionDispatcher.h
#ifndef CONTACTPOINTSCOLLISIONDISPATCHER_H
#define CONTACTPOINTSCOLLISIONDISPATCHER_H
#include <type_traits>
#include <functional>
#include <map>
#include <vector>
#include "Types/Vector2.h"

namespace Turtle
{
template<typename LeftICollision, typename RightICollision = LeftICollision>
class ContactPointsCollisionDispatcher {
public:
	using callable = std::function<std::vector<Vector2f>(LeftICollision&, RightICollision&)>;
	using key_t = std::pair<std::string, std::string>;

	template<typename LCollision, typename RCollision, 
		std::vector<Vector2f> (*Func)(LCollision&, RCollision&)>
	void add() {

		struct trampoline_s {
			static std::vector<Vector2f> trampoline(LeftICollision& lhs, RightICollision& rhs)
			{
				return std::invoke(Func, static_cast<LCollision&>(lhs), static_cast<RCollision&>(rhs));
			}
		};

		key_t key(typeid(LCollision).name(), typeid(RCollision).name());
		if (m_map.contains(key))
			throw std::runtime_error("This collision callback is already in the map");
		
		m_map.insert({ key, &trampoline_s::trampoline });
	}

	std::vector<Vector2f> operator()(LeftICollision& lhs, RightICollision& rhs)
	{
		auto iterator = std::find_if(m_map.begin(), m_map.end(), [&lhs, &rhs](const auto& element) {
			return (typeid(lhs).name() == element.first.first) && (typeid(rhs).name() == element.first.second);
		});
		if(iterator == m_map.end())
			throw std::runtime_error("This collision callback is not implemented");
		return iterator->second(lhs, rhs);
	}

private:
	std::map<key_t, callable> m_map;
};
}
#endif // COLLISIONDISPATCHER_H

