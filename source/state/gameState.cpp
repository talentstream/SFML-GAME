#include "state/gameState.h"

GameState::GameState(StateStack& stack, Context context) :
	State{stack, context},
	_world{*context._window},
	_player{*context._player}
{
}

void GameState::draw()
{
	_world.draw();
}

bool GameState::update(sf::Time dt)
{
	_world.update(dt);

	_player.handleRealtimeInput(_world.getCommandQueue());

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	_player.handleEvent(event, _world.getCommandQueue());

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(StateID::Pause);
	}
	return true;
}
