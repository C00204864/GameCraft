#include "Player.h"
#include <iostream>
#include <math.h>

Player::Player() :
	position(100, 200),
	velocity(0, 0),
	heading(0, 0),
	speed(0),
	radius(50),
	orientation(0),
	rotation(0.1)
{

	playerCircle.setFillColor(sf::Color::Black);
	playerSprite.setPosition(100, 200);

	if (!playerTexture.loadFromFile("man.jpg"))
	{
		// Error...
	}

	playerSprite.setScale(0.5f, 0.5f);
	playerSprite.setTexture(playerTexture);
}

Player::~Player()
{
}

sf::Vector2f Player::getPlayerPosition()
{
	return playerSprite.getPosition();
}
sf::Vector2f Player::getVelocity()
{
	velocity.x = heading.x * speed;
	velocity.y = heading.y * speed;
	return velocity;
}

void Player::update()
{
	//orientation = getNewOrientation(orientation,velocity);

	//if (playerSprite.getRotation() >= orientation + 1 || playerSprite.getRotation() <= orientation -1)
	//{
	//	playerSprite.rotate(rotation);
	//}

	
	//Keyboard input to change velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (velocity.x > -5)
		{
			velocity.x = velocity.x - 0.1;
		}
		//playerSprite.rotate(-0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (velocity.x < 5)
		{
			velocity.x = velocity.x + 0.1;
		}
		//playerSprite.rotate(0.1);
	}
	if (velocity.x != 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -5;
	}
	else
	{
		if (velocity.y < 0)
		{
			velocity.y = velocity.y + 0.1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//if (speed > -1)
		//{
		//	speed = speed - 0.01;
		//}
	}


	//Apply velocity
	playerSprite.setPosition(playerSprite.getPosition().x + velocity.x, playerSprite.getPosition().y + velocity.y);


	//Window borders
	if (playerSprite.getPosition().x >= 1280)
	{
		//playerSprite.setPosition(-100, playerSprite.getPosition().y);
		if (velocity.x > 0)
		{
			velocity.x = 0;
		}
	}
	if (playerSprite.getPosition().x <= 0)
	{
		if (velocity.x < 0)
		{
			velocity.x = 0;
		}
	}
	if (playerSprite.getPosition().y >= 720)
	{
		if (velocity.y > 0)
		{
			velocity.y = 0;
		}
	}
	if (playerSprite.getPosition().y <= 0)
	{
		if (velocity.y < 0)
		{
			velocity.y = 0;
		}
	}
}
void Player::draw(sf::RenderWindow & window)
{
	window.draw(playerSprite);
}