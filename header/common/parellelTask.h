#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

class ParellelTask
{
public:
	ParellelTask();

	void execute();

	bool isFinished();

	float getCompletion();

private:
	void runTask();

private:
	sf::Thread _thread;
	bool _finished;
	sf::Clock _elapsedTime;
	sf::Mutex _mutex;

};

