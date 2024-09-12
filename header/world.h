#pragma once

#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "sceneNode/aircraft.h"
#include "common/resourceHolder.h"
#include "common/sceneNode.h"
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

	

	void adaptPlayerPosition() const;

	void adaptPlayerVelocity();

	void buildScene();	

	void addEnemies();

	void addEnemy(Aircraft::Type type, float relX, float relY);

	void spawnEnemies();

	void destroyEntitiesOutsideView();

	void guideMissiles();

	sf::FloatRect getViewBounds() const;

	sf::FloatRect getBattlefieldBounds() const;


	enum class Layer : std::size_t
	{
		Background,
		Air,
		Count
	};

	struct SpawnPoint
	{
		SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
		{
		}

		Aircraft::Type type;
		float x;
		float y;
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

	std::vector<SpawnPoint> _enemySpawnPoints;
	std::vector<Aircraft*> _activeEnemies;
};
