#include "state/gameOverState.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "common/utility.h"

GameOverState::GameOverState(StateStack& stack, Context context) :
	State{stack, context},
	_gameOverText{},
	_elapsedTime{sf::Time::Zero}
{
	const auto& font = context._fontHolder->get(FontID::Main);
	sf::Vector2f windowSize{context._window->getSize()};

	_gameOverText.setFont(font);

	if (context._player->getMissionStatus() == Player::MissionStatus::Failure)
	{
		_gameOverText.setString("Mission Failed!");
	}
	else
	{
		_gameOverText.setString("Mission Successful!");
	}

	_gameOverText.setCharacterSize(70u);
	centerOrigin(_gameOverText);
	_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	auto& window = *getContext()._window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color{0, 0, 0, 150});
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(_gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	_elapsedTime += dt;
	if(_elapsedTime > sf::seconds(3))
	{
		requestStateClear();
		requestStackPush(StateID::Menu);
	}

	return false;

}

bool GameOverState::handleEvent(const sf::Event& event)
{
	return false;
}
