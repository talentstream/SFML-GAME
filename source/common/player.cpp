#include "common/player.h"
#include "sceneNode/aircraft.h"

Player::Player()
	: _currentMissionStatus{MissionStatus::Running}
{
	_keyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	_keyBinding[sf::Keyboard::Right] = Action::MoveRight;
	_keyBinding[sf::Keyboard::Up] = Action::MoveUp;
	_keyBinding[sf::Keyboard::Down] = Action::MoveDown;
	_keyBinding[sf::Keyboard::Space] = Action::Fire;
	_keyBinding[sf::Keyboard::M] = Action::LaunchMissile;

	initializeActions();

	for (auto& action : _actionBinding | std::views::values)
	{
		action._category = Category::PlayerAircraft;
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commandQueue)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = _keyBinding.find(event.key.code);
		if (found != _keyBinding.end() && isRealtimeAction(found->second) == false)
		{
			commandQueue.push(_actionBinding[found->second]);
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commandsQueue)
{
	for (const auto& [key, action] : _keyBinding)
	{
		if (sf::Keyboard::isKeyPressed(key) && isRealtimeAction(action))
		{
			commandsQueue.push(_actionBinding[action]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	std::erase_if(_keyBinding, [action](const auto& pair)
	{
		return pair.second == action;
	});

	_keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (const auto& [key, act] : _keyBinding)
	{
		if (act == action)
		{
			return key;
		}
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	_currentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return _currentMissionStatus;
}

void Player::initializeActions()
{
	constexpr float playerSpeed = 200.f;

	_actionBinding[Action::MoveLeft]._action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	_actionBinding[Action::MoveRight]._action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
	_actionBinding[Action::MoveUp]._action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	_actionBinding[Action::MoveDown]._action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
	_actionBinding[Action::Fire]._action = derivedAction<Aircraft>([](Aircraft& aircraft, sf::Time)
	{
		aircraft.fire();
	});
	_actionBinding[Action::LaunchMissile]._action = derivedAction<Aircraft>([](Aircraft& aircraft, sf::Time)
	{
		aircraft.launchMissile();
	});
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveDown:
	case Action::MoveUp:
	case Action::Fire:
		return true;

	default:
		return false;
	}
}
