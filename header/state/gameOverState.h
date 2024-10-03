#pragma once

#include "common/state.h"

#include <SFML/Graphics/Text.hpp>

class GameOverState final : public State
{
public:
	GameOverState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

private:
	sf::Text _gameOverText;
	sf::Time _elapsedTime;
};
