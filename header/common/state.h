#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "player.h"
#include "resourceHolder.h"

class StateStack;

enum class StateID
{
	None,
	Title,
	Menu,
	Game,
	Loading,
	Pause,
	Settings,
	GameOver
};

class State
{
public:
	using StatePtr = std::unique_ptr<State>;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, Player& player)
			: _window(&window)
			  , _textureHolder(&textureHolder)
			  , _fontHolder(&fontHolder)
			  , _player(&player)
		{
		}

		sf::RenderWindow* _window;
		TextureHolder* _textureHolder;
		FontHolder* _fontHolder;
		Player* _player;
	};

	State(StateStack& stack, Context context);

	virtual ~State() = default;

	virtual void draw() = 0;

	virtual bool update(sf::Time dt) = 0;

	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(StateID stateID);

	void requestStackPop();

	void requestStateClear();

	Context getContext() const;

private:
	StateStack* _stack;

	Context _context;
};
