#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "resourceHolder.h"

class Game
{
public:
	Game();

	void run();

private:
	void processEvents();

	void update(sf::Time deltaTime);

	void render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	std::unique_ptr<TextureHolder> _textureHolder;
	sf::RenderWindow _window;
	sf::Texture _texture;
	sf::Sprite _player;

	bool _isMovingUp{ false };
	bool _isMovingDown{ false };
	bool _isMovingLeft{ false };
	bool _isMovingRight{ false };
};

