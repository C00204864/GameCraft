#include "Collect.h"
#include <iostream>
#include <math.h>

Collect::Collect( float x, float y)
	: position(x, y),
	velocity(0, 0),
	heading(0, 0),
	speed(0),
	radius(50),
	orientation(0),
	rotation(0.1)
{

	playerCircle.setFillColor(sf::Color::Black);
	collectSprite.setPosition(x, y);

	if (!collectTexture.loadFromFile("Coins.png"))
	{
		// Error...
	}
	collectSprite.setScale(1.0f, 1.0f);
	collectSprite.setTexture(collectTexture);
	collectSprite.setTextureRect(sf::IntRect(0, 160, 70, 72));
}

Collect::~Collect()
{
}
void Collect::setPos(float x,float y) {
	collectSprite.setPosition(x,y);
}
sf::Vector2f Collect::getPlayerPosition()
{
	return collectSprite.getPosition();
}
sf::Vector2f Collect::getVelocity()
{
	velocity.x = heading.x * speed;
	velocity.y = heading.y * speed;
	return velocity;
}

void Collect::update(float x)
{
	//Apply velocity
	if (x != 0)
	{
		collectSprite.setPosition(sf::Vector2f(x - 170.0f, 0));
	}
	collectSprite.setTextureRect(sf::IntRect(68 * aniCount, 160 + 71 * aniRow, 68, 71));
	if (aniCount < 15)
	{
		aniCount = aniCount + 1;
	}
	else {
		aniCount = 0;
		if (aniRow == 0)
		{
			aniRow = 1;
		}
		else
		{
			aniRow = 0;
		}
	}
}
void Collect::draw(sf::RenderWindow & window)
{
	window.draw(collectSprite);
}