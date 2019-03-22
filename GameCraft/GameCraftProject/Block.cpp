#include "Block.h"

Block::Block(b2World & world, float x, float y, const float SCALE)
	: m_refWorld(world)
{
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_staticBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((150.f / 2) / SCALE, (100.f / 2) / SCALE);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	if (!m_texture.loadFromFile("TestSquare.png")) // TBI
	{
		std::cout << "Error: Could not load block texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	float scaleX = bounds.width / WIDTH;
	float scaleY = bounds.height / HEIGHT;
}

Block::~Block()
{
	m_refWorld.DestroyBody(m_body);
}

void Block::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
