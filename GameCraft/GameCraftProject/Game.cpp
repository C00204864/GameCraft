#include "Game.h"

/// <summary>
/// Constructor for the game object
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "GameCraft" },
	m_exitGame{ false },
	m_gravity{ 0, 90.81 },
	m_world{ m_gravity }// When true game will exit
{
	m_mainView = m_window.getView();
	m_centre = m_window.getView().getCenter();
	m_mainView.setCenter(m_centre);
	m_window.setView(m_mainView);
	block = new Block(m_world, 400, 400, WORLD_SCALE);
	m_gameState = State::MainMenu;
	m_menu = new Menu(1280, 720, *this, m_window);
	m_player = new Player(m_world, 400, 200, WORLD_SCALE);
	
	// Timer
	m_timer = new Timer();
	m_timer->start();

	// Background
	if (!m_bgTexture.loadFromFile("Assets\\Images\\GameBackground.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	// Background
	if (!m_bgTexture2.loadFromFile("Assets\\Images\\GameBackground2.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setPosition(0, 0);
	m_bgSprite.setScale(0.7f, 0.7f);
	m_bgSprite2.setTexture(m_bgTexture2);
	m_bgSprite2.setPosition(m_bgTexture.getSize().x * 0.7f, 0);
	m_bgSprite2.setScale(0.7f, 0.7f);
	m_moved = 1;

}

/// <summary>
/// Destructor for the game object
/// </summary>
Game::~Game() {}

/// <summary>
/// Run the Game
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // As many as possible
	}
}

void Game::setGameState(State state)
{
	m_gameState = state;
}

void Game::endGame()
{
	m_exitGame = true;
}

/// <summary>
/// Process the game events
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update loop for the game
/// </summary>
/// <param name="t_deltaTime">deltatime</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	else
	{
		switch (m_gameState)
		{
		case State::MainMenu:
			m_menu->update();
			m_window.setView(m_window.getDefaultView());
			break;
		case State::Play:
			if (m_bgSprite.getPosition().x + 1920.0f < m_centre.x - 100.0f)
			{
				m_moved++;
				m_bgSprite.setPosition((m_bgTexture.getSize().x * 0.7f) * m_moved, 0);
			}
			else if (m_bgSprite2.getPosition().x + 1920.0f < m_centre.x - 100.0f)
			{
				m_moved++;
				m_bgSprite2.setPosition((m_bgTexture.getSize().x * 0.7f) * m_moved, 0);
			}
			m_timer->update(t_deltaTime.asMilliseconds(), m_centre.x);
			m_mainView.setCenter(m_centre);
			m_window.setView(m_mainView);
			m_world.Step(1 / 60.f, 10, 5); // Update the Box2d world
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_centre.x += CAM_SPEED;
			}
			m_player->update();
			break;
		default:
			break;
		}

	}
}

/// <summary>
/// Draw loop for the game
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	switch (m_gameState)
	{
	case State::MainMenu:
		m_menu->draw();
		break;
	case State::Play:
		m_window.draw(m_bgSprite);
		m_window.draw(m_bgSprite2);
		m_timer->render(m_window);
		block->render(m_window);
		m_player->draw(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}