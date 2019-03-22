#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <iostream>

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	void stop();
	void reset();
	void penalty(int t);
	void reward(int t);

	void update(int dt, float x);
	void render(sf::RenderWindow & window);

private:
	int m_currentMilli;
	int m_currentSec;
	int m_currentMin;
	std::string m_display;
	sf::Font m_font;
	sf::Text m_text;
	bool m_running;
};

#endif // !TIMER_H