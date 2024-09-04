#pragma once

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

class SceneNode;

enum class Category
{
	None,
	Scene,
	PlayerAircraft,
	AlliedAircraft,
	EnemyAircraft
};

class Command
{
public:
	std::function<void(SceneNode&, sf::Time)> _action;
	Category _category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function func)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		func(static_cast<GameObject&>(node), dt);
	};
}
