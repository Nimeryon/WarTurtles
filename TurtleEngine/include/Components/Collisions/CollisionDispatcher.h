// CollisionDispatcher.h
#ifndef COLLISIONDISPATCHER_H
#define COLLISIONDISPATCHER_H
#include <type_traits>
#include <functional>
#include <map>

namespace Turtle
{
template<typename LeftICollision, typename RightICollision = LeftICollision>
class CollisionDispatcher {
public:
	using callable = std::function<bool(LeftICollision&, RightICollision&, Vector2f&, float&)>;
	using key_t = std::pair<std::string, std::string>;

	template<typename LCollision, typename RCollision, 
			bool (*Func)(LCollision&, RCollision&, Vector2f&, float&)>
	void add() {

		struct trampoline_s {
			static bool trampoline(LeftICollision& lhs, RightICollision& rhs, Vector2f& normal, float& depth)
			{
				return std::invoke(Func, static_cast<LCollision&>(lhs), static_cast<RCollision&>(rhs), normal, depth);
			}
		};

		key_t key(typeid(LCollision).name(), typeid(RCollision).name());
		if (m_map.contains(key))
			throw std::runtime_error("This collision callback is already in the map");
		
		m_map.insert({ key, &trampoline_s::trampoline });
	}

	bool operator()(LeftICollision& lhs, RightICollision& rhs, Vector2f& normal, float& depth)
	{
		auto iterator = std::find_if(m_map.begin(), m_map.end(), [&lhs, &rhs](const auto& element) {
			return (typeid(lhs).name() == element.first.first) && (typeid(rhs).name() == element.first.second);
		});
		if(iterator == m_map.end())
			throw std::runtime_error("This collision callback is not implemented");
		return iterator->second(lhs, rhs, normal, depth);
	}

private:
	std::map<key_t, callable> m_map;
};
}
#endif // !COLLISIONDISPATCHER_H

