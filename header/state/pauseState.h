#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "common/state.h"

class PauseState final :public State
{
public:
	PauseState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

private:
	sf::Sprite _backgroundSprite;
	sf::Text _pausedText;
	sf::Text _instructionText;
};

