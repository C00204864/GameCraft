#include "Animation.h"


/// <summary>
/// Default Constructor for the Animation object
/// </summary>
Animation::Animation()
{

}

/// <summary>
/// Constructor for the Animation object
/// </summary>
Animation::Animation(std::string path, int width, int height, int speed, int frames)
{
	if (!m_texture.loadFromFile(path))
	{
		std::string s("error loading texture from file: " + path);
		throw std::exception(s.c_str());
	}

	m_sheetWidth = m_texture.getSize().x;
	m_sheetHeight = m_texture.getSize().y;

	m_spriteWidth = width;
	m_spriteHeight = height;

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));

	m_counter = 0;
	m_counterLimit = frames - 1;
	m_timer = 0;
	m_timerLimit = speed;
}

Animation::~Animation()
{

};

void Animation::setSpeed(int time)
{
	m_timerLimit = time;
}

void Animation::update(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	if (m_timer < m_timerLimit)
	{
		m_timer++;
	}
	else
	{
		m_timer = 0;
		if (m_counter < m_counterLimit)
		{
			m_counter++;
		}
		else
		{
			m_counter = 0;
		}

		m_sprite.setTextureRect(sf::IntRect(m_counter * m_spriteWidth, 0, m_spriteWidth, m_spriteHeight));
	}
}

void Animation::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

sf::Sprite Animation::getSprite()
{
	return m_sprite;
}