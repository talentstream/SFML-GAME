#pragma once

#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "aircraft.h"
#include "resourceHolder.h"
#include "sceneNode.h"


class World :
	private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	void update(sf::Time dt);

	void draw();

private:
	void loadTextures();

	void buildScene();

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

	sf::FloatRect _worldBounds;
	sf::Vector2f _spawnPosition;
	float _scrollSpeed;
	Aircraft* _playerAircraft;
};
