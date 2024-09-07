#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "common/state.h"

class MenuState final: public State
{
public:
	MenuState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

	void updateOptionText();

private:
	enum class Option : std::size_t
	{
		Play,
		Exit,
	};

	sf::Sprite _backgroundSprite;
	std::vector<sf::Text> _options;

	std::size_t _optionIndex;
};

