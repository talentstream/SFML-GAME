#pragma once

#include "commandQueue.h"

#include <SFML/Window/Event.hpp>

#include <unordered_map>

class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};

	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commandQueue);

	void handleRealtimeInput(CommandQueue& commandsQueue);

	void assignKey(Action action, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	void initializeActions();

	static bool isRealtimeAction(Action action);

private:
	std::unordered_map<sf::Keyboard::Key, Action> _keyBinding;
	std::unordered_map<Action, Command> _actionBinding;
};
