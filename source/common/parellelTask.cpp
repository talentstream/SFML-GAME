#include "common/parellelTask.h"

#include <SFML/System/Lock.hpp>

ParellelTask::ParellelTask() :
	_thread{&ParellelTask::runTask, this},
	_finished{false}
{
}

void ParellelTask::execute()
{
	_finished = false;
	_elapsedTime.restart();
	_thread.launch();
}

bool ParellelTask::isFinished()
{
	sf::Lock lock(_mutex);
	return _finished;
}

float ParellelTask::getCompletion()
{
	sf::Lock lock(_mutex);
	return _elapsedTime.getElapsedTime().asSeconds() / 10.f;
}

void ParellelTask::runTask()
{
	bool isEnd = false;
	while(!isEnd)
	{
		sf::Lock lock(_mutex);
		if(_elapsedTime.getElapsedTime().asSeconds() >= 10.f)
		{
			isEnd = true;
		}
	}

	{
		sf::Lock lock(_mutex);
		_finished = true;
	}
}
