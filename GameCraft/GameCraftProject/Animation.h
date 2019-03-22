#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
public:
	Animation();
	Animation(std::string path, int width, int height, int frames);
	~Animation();
	void update();
	void render(sf::RenderWindow & window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_sheetWidth;
	int m_sheetHeight;
	int m_spriteWidth;
	int m_spriteHeight;

	int m_counter;
	int m_counterLimit;
	int m_timer;
	int m_timerLimit;
};

#endif // !ANIMATION_H