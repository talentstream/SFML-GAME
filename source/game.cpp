#include "game.h"

constexpr float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: _window{sf::VideoMode(640u, 480u), "SFML GAME"},
	  _texture{},
	  _player{}
{
}

void Game::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{sf::Time::Zero};

	while(_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	for (auto event = sf::Event{}; _window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			_window.close();
			break;
		default: 
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement{ 0.f,0.f };
	if (_isMovingUp) {
		movement.y -= PlayerSpeed;
	}
	if (_isMovingDown) {
		movement.y += PlayerSpeed;
	}
	if (_isMovingLeft) {
		movement.x -= PlayerSpeed;
	}
	if (_isMovingRight) {
		movement.x += PlayerSpeed;
	}

	_player.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	_window.clear();
	_window.draw(_player);
	_window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		_isMovingUp = isPressed;
		break;
	case sf::Keyboard::S:
		_isMovingDown = isPressed;
		break;
	case sf::Keyboard::A:
		_isMovingLeft = isPressed;
		break;
	case sf::Keyboard::D:
		_isMovingRight = isPressed;
		break;
	default: 
		break;
	}
}
