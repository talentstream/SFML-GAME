#include "common/stateStack.h"

#include <cassert>
#include <ranges>

StateStack::StateStack(State::Context context)
	: _stack{},
	  _pendingList{},
	  _context{context},
	  _factories{}
{
}

void StateStack::update(sf::Time dt)
{
	auto it = std::ranges::find_if(_stack, [dt](const auto& state)
	{
		return !state->update(dt);
	});

	applyPendingChanges();
}

void StateStack::draw()
{
	std::ranges::for_each(_stack, [](const auto& state)
	{
		state->draw();
	});
}

void StateStack::handleEvent(const sf::Event& event)
{
	auto it = std::ranges::find_if(_stack, [event](const auto& state)
	{
		return !state->handleEvent(event);
	});

	applyPendingChanges();
}

void StateStack::pushState(StateID stateID)
{
	_pendingList.push_back({Action::Push, stateID});
}

void StateStack::popState()
{
	_pendingList.push_back({Action::Pop, StateID::None});
}

void StateStack::clearStates()
{
	_pendingList.push_back({Action::Clear, StateID::None});
}

bool StateStack::isEmpty() const
{
	return _stack.empty();
}

State::StatePtr StateStack::createState(StateID stateID)
{
	auto found = _factories.find(stateID);

	assert(found != _factories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	std::ranges::for_each(_pendingList, [this](const auto& change)
	{
		switch (change.action)
		{
		case Action::Push:
			_stack.push_back(createState(change.stateID));
			break;
		case Action::Pop:
			_stack.pop_back();
			break;
		case Action::Clear:
			_stack.clear();
			break;
		}
	});

	_pendingList.clear();
}
