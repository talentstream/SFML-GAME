#include "common/commandQueue.h"

void CommandQueue::push(const Command& command)
{
	_queue.push(command);
}

Command CommandQueue::pop()
{
	auto command = _queue.front();
	_queue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return _queue.empty();
}
