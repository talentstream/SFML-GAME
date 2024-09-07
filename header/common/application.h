#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "player.h"
#include "resourceHolder.h"
#include "stateStack.h"
#include "world.h"

class Application
{
public:
	Application();

	void run();

private:
	void processInput();

	void update(sf::Time dt);

	void render();

	void updateStatistics(sf::Time dt);

	void registerState();

private:
	// static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow _window;
	World _world;
	Player _player;
	TextureHolder _textureHolder;
	FontHolder _fontHolder;

	StateStack _stateStack;

	sf::Text _statisticsText;
	sf::Time _statisticsUpdateTime;
	std::size_t _statisticsNumFrames{0};
};

