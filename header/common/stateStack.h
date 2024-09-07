#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/System/NonCopyable.hpp>

#include "common/state.h"

class StateStack : private sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);

	template <typename T>
	void registerState(StateID stateID);

	void update(sf::Time dt);

	void draw();

	void handleEvent(const sf::Event& event);

	void pushState(StateID stateID);

	void popState();

	void clearStates();

	bool isEmpty() const;

private:
	State::StatePtr createState(StateID stateID);

	void applyPendingChanges();

	struct PendingChange
	{
		Action action;
		StateID stateID;
	};

	std::vector<State::StatePtr> _stack;
	std::vector<PendingChange> _pendingList;
	State::Context _context;
	std::unordered_map<StateID, std::function<State::StatePtr()>> _factories;
};

template <typename T>
void StateStack::registerState(StateID stateID)
{
	_factories[stateID] = [this]()
	{
		return State::StatePtr(new T(*this, _context));
	};
}
