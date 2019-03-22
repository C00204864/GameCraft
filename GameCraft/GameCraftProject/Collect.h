#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

class Collect
{
public:
	Collect( float x, float y);
	~Collect();
	void setPos(float x,float y);
	void update();
	void draw(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPlayerPosition();

	int aniCount = 0;
	int aniRow = 0;

	float Scale;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f position;
	sf::CircleShape playerCircle;
	sf::Vector2f velocity;
	sf::Vector2f heading;
	int radius;
	sf::Texture collectTexture;
	sf::Sprite collectSprite;
	float orientation;
	float rotation;
	double speed;



	// Constants
	const float WIDTH = 100.f;
	const float HEIGHT = 150.f;

};

