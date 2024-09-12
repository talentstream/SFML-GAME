#pragma once

#include "common/commandQueue.h"

#include <SFML/Window/Event.hpp>

#include <unordered_map>

class Player
{
public:
	enum class Action : std::size_t
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		Count
	};

	enum class MissionStatus
	{
		Running,
		Success,
		Failure
	};

	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commandQueue);

	void handleRealtimeInput(CommandQueue& commandsQueue);

	void assignKey(Action action, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(Action action) const;

	void setMissionStatus(MissionStatus status);

	MissionStatus getMissionStatus() const;

private:
	void initializeActions();

	static bool isRealtimeAction(Action action);

	std::unordered_map<sf::Keyboard::Key, Action> _keyBinding;
	std::unordered_map<Action, Command> _actionBinding;
	MissionStatus _currentMissionStatus;
};
