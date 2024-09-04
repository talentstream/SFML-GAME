#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "player.h"
#include "resourceHolder.h"
#include "world.h"

class Game
{
public:
	Game();

	void run();

private:
	void processInput();

	void update(sf::Time elapsedTime);

	void render();

	void updateStatistics(sf::Time elapsedTime);

private:
	// static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow _window;
	World _world;
	Player _player;

	sf::Font _font;
	sf::Text _statisticsText;
	sf::Time _statisticsUpdateTime;
	std::size_t _statisticsNumFrames{0};
};

