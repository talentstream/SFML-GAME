#include "common/application.h"

#include "common/state.h"

// constexpr float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: _window{sf::VideoMode(640u, 480u), "SFML GAME", sf::Style::Close},
	  _world{_window},
	  _player{},
	  _textureHolder{},
	  _fontHolder{},
	  _stateStack{State::Context{_window, _textureHolder, _fontHolder, _player}},
	  _font{},
	  _statisticsText{},
	  _statisticsUpdateTime{}
{
	_window.setKeyRepeatEnabled(false);


	_font.loadFromFile("resource/Sansation.ttf");
	_statisticsText.setFont(_font);
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10u);
}

void Application::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{sf::Time::Zero};

	while (_window.isOpen())
	{
		processInput();

		auto elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Application::processInput()
{
	auto& commandQueue = _world.getCommandQueue();

	for (auto event = sf::Event{}; _window.pollEvent(event);)
	{
		_player.handleEvent(event, commandQueue);

		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
	}

	_player.handleRealtimeInput(commandQueue);
}

void Application::update(sf::Time elapsedTime)
{
	_world.update(elapsedTime);
}

void Application::render()
{
	_window.clear();
	_world.draw();

	_window.setView(_window.getDefaultView());
	_window.draw(_statisticsText);
	_window.display();
}

void Application::updateStatistics(sf::Time elapsedTime)
{
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		_statisticsText.setString(
			"Frames / Second = " + std::to_string(_statisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(_statisticsUpdateTime.asMicroseconds() / _statisticsNumFrames) + "us"
		);

		_statisticsUpdateTime -= sf::seconds(1.0f);
		_statisticsNumFrames = 0;
	}
}

void Application::registerState()
{
}
