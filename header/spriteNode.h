#pragma once
#include "sceneNode.h"

class SpriteNode :
	public SceneNode
{
public:
	SpriteNode(const sf::Texture& texture);

	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _sprite;
};
