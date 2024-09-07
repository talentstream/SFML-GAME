#include "state/pauseState.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "common/utility.h"

PauseState::PauseState(StateStack& stack, Context context) :
	State{stack, context},
	_backgroundSprite{},
	_pausedText{},
	_instructionText{}
{
	auto& font = context._fontHolder->get(FontID::Main);
	auto viewSize = context._window->getView().getSize();

	_pausedText.setFont(font);
	_pausedText.setString("Game Paused");
	_pausedText.setCharacterSize(70);
	centerOrigin(_pausedText);
	_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	_instructionText.setFont(font);
	_instructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(_instructionText);
	_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	auto& window = *getContext()._window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(_pausedText);
	window.draw(_instructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if(event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	if(event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(StateID::Menu);
	}

	return false;
}
