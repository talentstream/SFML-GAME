#pragma once
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

void centerOrigin(sf::Sprite& sprite);

void centerOrigin(sf::Text& text);

float toDegree(float radian);

float toRadian(float degree);

int randomInt(int exclusiveMax);

float length(sf::Vector2f vector);

sf::Vector2f unitVector(sf::Vector2f vector);