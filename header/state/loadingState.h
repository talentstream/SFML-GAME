#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "common/parellelTask.h"
#include "common/state.h"

class LoadingState final : public State
{
public:
	LoadingState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

	void setCompletion(float percent);

private:
	sf::Text _loadingText;
	sf::RectangleShape _progressBarBackground;
	sf::RectangleShape _progressBar;

	ParellelTask _loadingTask;
};

