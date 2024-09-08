#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "common/state.h"
#include "gui/container.h"

class MenuState final: public State
{
public:
	MenuState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

private:

	sf::Sprite _backgroundSprite;
	GUI::Container _container;

};

