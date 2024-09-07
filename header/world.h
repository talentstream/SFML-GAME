#pragma once

#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "aircraft.h"
#include "common/resourceHolder.h"
#include "sceneNode.h"
#include "common/commandQueue.h"

class World :
	private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	void update(sf::Time dt);

	void draw();

	CommandQueue& getCommandQueue();

private:
	void loadTextures();

	void buildScene();
	void adaptPlayerPosition() const;
	void adaptPlayerVelocity();

	enum class Layer : std::size_t
	{
		Background,
		Air,
		Count
	};

	sf::RenderWindow& _window;
	sf::View _worldView;
	TextureHolder _textureHolder;

	SceneNode _sceneGraph;
	std::unordered_map<Layer, SceneNode*> _sceneLayers;
	CommandQueue _commandQueue;

	sf::FloatRect _worldBounds;
	sf::Vector2f _spawnPosition;
	float _scrollSpeed;
	Aircraft* _playerAircraft;
};
