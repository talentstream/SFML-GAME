#include "common/application.h"

#include "common/state.h"
#include "state/titleState.h"
#include "state/gameState.h"
#include "state/pauseState.h"
#include "state/menuState.h"
#include "state/settingsState.h"
#include "state/gameOverState.h"

// constexpr float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: _window{sf::VideoMode(640u, 480u), "SFML GAME", sf::Style::Close},
	  _player{},
	  _textureHolder{},
	  _fontHolder{},
	  _stateStack{State::Context{_window, _textureHolder, _fontHolder, _player}},
	  _statisticsText{},
	  _statisticsUpdateTime{}
{
	_window.setKeyRepeatEnabled(false);

	_fontHolder.load(FontID::Main,"resource/Sansation.ttf");

	_textureHolder.load(TextureID::TitleScreen, "resource/TitleScreen.png");
	_textureHolder.load(TextureID::ButtonNormal, "resource/ButtonNormal.png");
	_textureHolder.load(TextureID::ButtonSelected, "resource/ButtonSelected.png");
	_textureHolder.load(TextureID::ButtonPressed, "resource/ButtonPressed.png");

	_statisticsText.setFont(_fontHolder.get(FontID::Main));
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10u);

	registerState();
	_stateStack.pushState(StateID::Title);
}

void Application::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{sf::Time::Zero};

	while (_window.isOpen())
	{
		auto dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if(_stateStack.isEmpty())
			{
				_window.close();
			}
		}
		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	for (auto event = sf::Event{}; _window.pollEvent(event);)
	{
		_stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
	}
}

void Application::update(sf::Time dt)
{
	_stateStack.update(dt);
}

void Application::render()
{
	_window.clear();

	_stateStack.draw();

	_window.setView(_window.getDefaultView());
	_window.draw(_statisticsText);
	_window.display();
}

void Application::updateStatistics(sf::Time dt)
{
	_statisticsUpdateTime += dt;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		_statisticsText.setString("FPS: " + std::to_string(_statisticsNumFrames));

		_statisticsUpdateTime -= sf::seconds(1.0f);
		_statisticsNumFrames = 0;
	}
}

void Application::registerState()
{
	_stateStack.registerState<TitleState>(StateID::Title);
	_stateStack.registerState<MenuState>(StateID::Menu);
	_stateStack.registerState<GameState>(StateID::Game);
	_stateStack.registerState<PauseState>(StateID::Pause);
	_stateStack.registerState<SettingsState>(StateID::Settings);
	_stateStack.registerState<GameOverState>(StateID::GameOver);
}
