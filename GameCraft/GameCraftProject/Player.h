#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

class Player
{
public:
	Player(b2World & world, float x, float y, const float SCALE);
	~Player();
	void update();
	void draw(sf::RenderWindow & window);
	float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
	sf::Vector2f getVelocity();
	sf::Vector2f getPlayerPosition();

	bool jumped = false;
	float previousVelY = 0;

	float Scale;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f position;
	sf::CircleShape playerCircle;
	sf::Vector2f velocity;
	sf::Vector2f heading;
	int radius;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	float orientation;
	float rotation;
	double speed;

	// Box2D
	b2World & m_refWorld;
	float m_worldScale;
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	// Constants
	const float WIDTH = 100.f;
	const float HEIGHT = 150.f;

};

