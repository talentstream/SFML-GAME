#pragma once

#include <array>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "aircraft.h"
#include "resourceHolder.h"
#include "sceneNode.h"


class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	void update(sf::Time dt);

	void draw();

private:
	void loadTextures();

	void buildScene();

private:
	enum class Layer
	{
		Background,
		Air,
		Count
	};

	sf::RenderWindow& _window;
	sf::View _worldView;
	TextureHolder _textureHolder;

	SceneNode _sceneGraph;
	std::array<SceneNode*, static_cast<size_t>(Layer::Count)> _SceneLayers;

	sf::FloatRect _worldBounds;
	sf::Vector2f _spawnPosition;
	float _scrollSpeed;
	Aircraft* _playerAircraft;

};

