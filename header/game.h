#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "resourceHolder.h"
#include "world.h"

class Game
{
public:
	Game();

	void run();

private:
	void processEvents();

	void update(sf::Time elapsedTime);

	void render();

	void updateStatistics(sf::Time elapsedTime);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	// static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow _window;
	World _world;
	//
	// bool _isMovingUp{ false };
	// bool _isMovingDown{ false };
	// bool _isMovingLeft{ false };
	// bool _isMovingRight{ false };
};

