#include "game.h"

// constexpr float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: _window{sf::VideoMode(640u, 480u), "SFML GAME"},
	  _world{_window}
{
}

void Game::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{sf::Time::Zero};

	while(_window.isOpen())
	{
		processEvents();

		auto elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

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

void Game::update(sf::Time elapsedTime)
{
	_world.update(elapsedTime);
}

void Game::render()
{
	_window.clear();
	_world.draw();

	_window.setView(_window.getDefaultView());

	_window.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}
