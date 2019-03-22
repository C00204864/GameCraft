#include "Player.h"
#include <iostream>
#include <math.h>

Player::Player(b2World & world, float x, float y, const float SCALE)
	: m_refWorld(world),
	position(100, 200),
	velocity(0, 0),
	heading(0, 0),
	speed(0),
	radius(50),
	orientation(0),
	rotation(0.1)
{

	playerCircle.setFillColor(sf::Color::Black);
	playerSprite.setPosition(x, y);

	if (!playerTexture.loadFromFile("man.jpg"))
	{
		// Error...
	}
	Scale = SCALE;
	playerSprite.setScale(0.5f, 0.5f);
	playerSprite.setTexture(playerTexture);

	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((100.f / 2) / SCALE, (150.f / 2) / SCALE);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_body->SetGravityScale(4.0);
	if (!m_texture.loadFromFile("TestSquare.png")) // TBI
	{
		std::cout << "Error: Could not load block texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	float scaleX = WIDTH / bounds.width;
	float scaleY = HEIGHT / bounds.height;
	m_sprite.setScale(scaleX, scaleY);
}

Player::~Player()
{
	m_refWorld.DestroyBody(m_body);
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
		if (velocity.x > -12)
		{
			velocity.x = velocity.x - 1;
		}
		//playerSprite.rotate(-0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (velocity.x < 12)
		{
			velocity.x = velocity.x + 1;
		}
		//playerSprite.rotate(0.1);
	}
	if (velocity.x != 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (jumped == false)
		{
			velocity.y = -25;
			jumped = true;
		}
	}

	
	if (m_body->GetLinearVelocity().y != 0)
	{
		velocity.y = velocity.y + 0.5;
	}
	if (velocity.y < 0.1 && velocity.y > -0.1)
	{
		//velocity.y = 0;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//if (speed > -1)
		//{
		//	speed = speed - 0.01;
		//}
	}
	if (m_body->GetLinearVelocity().y == 0)
	{
		if (jumped == true)
		{
			jumped = false;
			std::cout << "Called" << std::endl;
		}
	}




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
	previousVelY = velocity.y;
	//Apply velocity
	playerSprite.setPosition(m_body->GetPosition().x * Scale, m_body->GetPosition().y * Scale);
	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	m_sprite.setPosition(m_body->GetPosition().x * Scale, m_body->GetPosition().y * Scale);
}
void Player::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
	window.draw(playerSprite);
}