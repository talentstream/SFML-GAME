#include "common/state.h"
#include "common/statestack.h"

State::State(StateStack& stack, Context context) :
	_stack{&stack},
	_context{context}
{
}

void State::requestStackPush(StateID stateID)
{
	_stack->pushState(stateID);
}

void State::requestStackPop()
{
	_stack->popState();
}

void State::requestStateClear()
{
	_stack->clearStates();
}

State::Context State::getContext() const
{
	return _context;
}
