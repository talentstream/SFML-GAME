#include "spriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture) :
	_sprite{texture}
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect):
	_sprite{texture, textureRect}
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
