#pragma once

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "command.h"

class SceneNode;

template <typename T>
struct enable_bitmask_operators : std::false_type
{
};


template <typename T>
constexpr bool enable_bitmask_operators_or(T)
{
	return enable_bitmask_operators<T>::value;
}

template <typename T>
	requires(std::is_enum_v<T> && requires(T e)
	{
		enable_bitmask_operators_or(e);
	})
constexpr auto operator |(const T lhs, const T rhs)
{
	return static_cast<T>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

template <typename T>
	requires(std::is_enum_v<T> && requires(T e)
	{
		enable_bitmask_operators_or(e);
	})
constexpr auto operator &(const T lhs, const T rhs)
{
	return static_cast<T>(std::to_underlying(lhs) & std::to_underlying(rhs));
}

enum class Category
{
	None = 0,
	SceneAirLayer = 1 << 0,
	PlayerAircraft = 1 << 1,
	AlliedAircraft = 1 << 2,
	EnemyAircraft = 1 << 3,
	Pickup = 1 << 4,
	AlliedProjectile = 1 << 5,
	EnemyProjectile = 1 << 6,

	Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
	Projectile = AlliedProjectile | EnemyProjectile,
};

template <>
struct enable_bitmask_operators<Category> : std::true_type
{
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
