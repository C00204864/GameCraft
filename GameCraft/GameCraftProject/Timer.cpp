#include "Timer.h"

Timer::Timer():m_text(), m_font()
{
	m_currentMilli = 0;
	m_currentSec = 0;
	m_currentMin = 0;
	m_display = "Timer: " + std::to_string(m_currentMin) + " : " + std::to_string(m_currentSec) + " : " + std::to_string(m_currentMilli);

	if (!m_font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "Error loading font in timer" << std::endl;
	}

	m_text.setFont(m_font);

	m_text.setString(m_display);

	m_text.setCharacterSize(24); // in pixels, not points!

	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(sf::Vector2f(0, 0));
}

Timer::~Timer()
{

}

void Timer::start()
{
	m_running = true;
}

void Timer::stop()
{
	m_running = false;
}

void Timer::reset()
{
	m_currentMilli = 0;
	m_currentSec = 0;
	m_currentMin = 0;

}

void Timer::penalty(int t)
{
	m_currentSec += t;
}

void Timer::reward(int t)
{
	m_currentSec -= t;
}

void Timer::update(int dt, float x)
{

	if (m_running)
	{
		if (m_currentMilli >= 1000)
		{
			m_currentMilli = 0;
			m_currentSec++;
			if (m_currentSec >= 60)
			{
				m_currentSec = 0;
				m_currentMin++;
			}
		}
		m_currentMilli += dt;
		if (m_currentMin <= 0)
		{
			m_display = "Timer: " + std::to_string(m_currentSec) + " : " + std::to_string(m_currentMilli);
		}
		else
		{
			m_display = "Timer: " + std::to_string(m_currentMin) + " : " + std::to_string(m_currentSec) + " : " + std::to_string(m_currentMilli);
		}
		m_text.setString(m_display);
		m_text.setPosition(sf::Vector2f(x - 100.0f, 0));
	}
}

void Timer::render(sf::RenderWindow & window)
{
	window.draw(m_text);
}

int Timer::getTime()
{
	return m_currentMin * 60 + m_currentSec;
}