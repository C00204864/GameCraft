#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class Block
{
public:
	Block(b2World & world, float x, float y, const float SCALE);
	~Block();
	void render(sf::RenderWindow & window);
	sf::Vector2f getPosition();
private:
	// SFML Sprite
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	// Box2D
	b2World & m_refWorld;
	float m_worldScale;
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	// Constants
	const float WIDTH = 250.f;
	const float HEIGHT = 70.f;
};

#endif // !BLOCK_H