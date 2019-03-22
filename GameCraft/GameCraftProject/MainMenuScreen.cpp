#include "MainMenuScreen.h"


//main menu of the game
Menu::Menu(float width, float height, Game & game, sf::RenderWindow &window) :
	m_label("GameCraft", 390.f, 100.f ),
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	m_label.setUnderLined();
	m_label.changeTextSize(100);
	m_widgets[0] = new Button("Play Game", 475.f,300.f);
	m_widgets[0]->getFocus();
	m_widgets[0]->Enter = std::bind(&Menu::GoToPlay, this); //func bind
	m_widgets[1] = new Button("End Game", 475.f, 400.f);
	m_widgets[1]->Enter = std::bind(&Menu::EndGame, this); //bind
	m_selectedItemIndex = 0; //start at top 

	m_gui.vertical = true; //control scheme


	m_widgets[0]->updateFocusColor(sf::Color(255, 0, 0, 255));
	m_widgets[1]->updateFocusColor(sf::Color(255, 0, 0, 255));

	if (!m_texture.loadFromFile("Assets\\Images\\background.png"))
	{
		//handle
	}

	//m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	//m_background.setFillColor(sf::Color(0, 0, 0, 255));

	m_background.setTexture(m_texture);
	m_background.setPosition(0, 0);

	m_collect = new Collect(750, 300);

	//add ui elements to gui
	for (auto & var : m_widgets)
	{
		m_gui.addWidget(var);
	}
	m_gui.addLabel(&m_label);


}


Menu::~Menu()
{
	for (auto & var : m_widgets)
	{
		delete var;
	}
}

/*
Draw the ui elements
*/
void Menu::draw()
{
	m_window.draw(m_background);
	m_collect->draw(m_window);
	m_gui.draw(m_window);
}

//update ui elements
void Menu::update()
{

	if (m_selectedItemIndex == 0)
	{
		m_collect->setPos(750, 300);
	}
	else {
		m_collect->setPos(750, 400);
	}
	m_collect->update();
	m_gui.update(m_selectedItemIndex, MAX_ITEMS);
	m_xbox.update();


}

//return selected item NOTE: not used
bool Menu::itemSelected()
{
	return m_itemSelected;
}

void Menu::GoToPlay()
{
	m_game->setGameState(State::Play);
}

void Menu::EndGame()
{
	m_game->endGame();
}
