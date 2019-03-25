#include "GameOver.h"

GameOver::GameOver(float width, float height, Game & game, sf::RenderWindow & window) :
	m_label("Game Over", 90.f, 100.f),
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	m_label.setUnderLined();
	m_label.changeTextSize(100);
	m_widgets[0] = new Button("Go To Menu", 100.f, 300.f);
	m_widgets[0]->getFocus();
	m_widgets[0]->Enter = std::bind(&GameOver::GoToPlay, this); //func bind
	m_widgets[1] = new Button("End Game", 100.f, 400.f);
	m_widgets[1]->Enter = std::bind(&GameOver::EndGame, this); //bind
	m_selectedItemIndex = 0; //start at top 

	m_gui.vertical = true; //control scheme


	m_widgets[0]->updateFocusColor(sf::Color(0, 255, 0, 255));
	m_widgets[1]->updateFocusColor(sf::Color(0, 255, 0, 255));

	if (!m_texture.loadFromFile("Assets\\Images\\background.png"))
	{
		//handle
	}

	//m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	//m_background.setFillColor(sf::Color(0, 0, 0, 255));

	m_background.setTexture(m_texture);
	m_background.setPosition(0, 0);

	//add ui elements to gui
	for (auto & var : m_widgets)
	{
		m_gui.addWidget(var);
	}
	m_gui.addLabel(&m_label);
}

GameOver::~GameOver()
{
}

void GameOver::draw()
{
	m_window.draw(m_background);
	m_gui.draw(m_window);
}

void GameOver::update(Timer timer)
{
	m_gui.update(m_selectedItemIndex, MAX_ITEMS);
	m_label.updateText("Game Over: " + std::to_string(timer.getTime()));
	m_xbox.update();
}

bool GameOver::itemSelected()
{
	return m_itemSelected;
}

void GameOver::GoToPlay()
{
	m_game->setGameState(State::MainMenu);
}

void GameOver::EndGame()
{
	m_game->endGame();
}