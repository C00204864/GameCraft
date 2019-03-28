#include "Game.h"

/// <summary>
/// Constructor for the game object
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "GameCraft" },
	m_exitGame{ false },
	m_gravity{ 0, 90.81 },
	m_world{ m_gravity },// When true game will exit
	m_pool(3)
{
	m_mainView = m_window.getView();
	m_centre = m_window.getView().getCenter();
	m_mainView.setCenter(m_centre);
	m_window.setView(m_mainView);
	for (int i = 0; i < 10; i++)
	{
		m_blocks.push_back(new Block(m_world, (500 * i), 400, WORLD_SCALE));
	}
	m_gameState = State::MainMenu;
	m_menu = new Menu(1280, 720, *this, m_window);
	m_player = new Player(m_world, 400, 200, WORLD_SCALE);
	m_collect = new Collect(200, 200);
	srand(time(NULL));


	m_gameOver = new GameOver(1280, 720, *this, m_window);

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

	//m_threads.push_back(std::thread(&Timer::render, m_timer, m_window));
	//for (auto &b : m_blocks)
	//{
	//	m_threads.push_back(std::thread(&Block::render, b, m_window));
	//}
	//m_threads.push_back(std::thread(&Collect::draw, m_collect, m_window));
	//m_threads.push_back(std::thread(&Player::draw, m_player, m_window));

	//m_threads.push_back(std::thread(&Game::drawTimer, this));
	//m_threads.push_back(std::thread(&Game::drawBlocks, this));
	//m_threads.push_back(std::thread(&Game::drawPlayer, this));
	//m_threads.push_back(std::thread(&Game::drawCollect, this));

	//std::future<void> f();
	//m_pool.enqueue(&Game::drawTimer, this);
	//m_pool.enqueue(&Game::drawBlocks, this);
	//m_pool.enqueue(&Game::drawPlayer, this);
	//m_pool.enqueue(&Game::drawCollect, this);
		
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

void Game::runGame() 
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (true)
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
		}
		//std::thread t = std::thread(&Game::render, this);
		//t.join();
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
		m_playerPos = m_player->getPlayerPosition();
		//CAM_SPEED += 0.001f;
		switch (m_gameState)
		{
		case State::MainMenu:
			m_timer->reset();
			m_menu->update();
			m_window.setView(m_window.getDefaultView());
			break;
		case State::Play:

			drawMtx.lock();
		

			m_timer->update(t_deltaTime.asMilliseconds(), m_centre.x);
			drawMtx.unlock();
			m_pool.enqueue(&Game::setView, this);
			m_pool.enqueue(&Game::moveBG, this);
			m_pool.enqueue(&Game::onScreen, this, t_deltaTime);

			drawMtx.lock();
			m_collect->update(m_centre.x);
			m_world.Step(1 / 60.f, 10, 5); // Update the Box2d world

			if (baseDistance < maxDistance)
			{
				baseDistance += 0.2f;
			}
			if (CAM_SPEED < maxCamSpeed)
			{
				CAM_SPEED += 0.01f;
			}
			drawMtx.unlock();
			

			break;
		case State::Over:
			m_gameOver->update(*m_timer);
			m_window.setView(m_window.getDefaultView());
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
			drawTimer();
			drawBlocks();
			drawCollect();
			drawPlayer();
			//m_pool.enqueue(&Game::drawTimer, this);
			//m_pool.enqueue(&Game::drawBlocks, this);
			//m_pool.enqueue(&Game::drawCollect, this);
			//m_pool.enqueue(&Game::drawPlayer, this);
			break;
		case State::Over:
			m_gameOver->draw();
			break;
		default:
			break;
		}
		m_window.display();

}

void Game::drawTimer()
{
	//drawMtx.lock();
	//sf::Context context;
	//m_window.setActive(true);
	m_timer->render(m_window);
	//m_window.setActive(false);
	//drawMtx.unlock();
}

void Game::drawBlocks()
{
	//drawMtx.lock();
	//sf::Context context;
	//m_window.setActive(true);
	for (auto &b : m_blocks)
	{
		b->render(m_window);
	}
	//m_window.setActive(false);
	//drawMtx.unlock();
}

void Game::drawPlayer()
{
	//drawMtx.lock();
	//sf::Context context;
	//m_window.setActive(true);
	m_player->draw(m_window);
	//m_window.setActive(false);
	//drawMtx.unlock();
};
void Game::drawCollect()
{
	//drawMtx.lock();
	//sf::Context context;
	//m_window.setActive(true);
	m_collect->draw(m_window);
	//m_window.setActive(false);
	//drawMtx.unlock();
};


void Game::setView()
{
	drawMtx.lock();
	m_mainView.setCenter(m_centre);
	m_window.setView(m_mainView);

	drawMtx.unlock();
};
void Game::moveBG()
{
	drawMtx.lock();
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
	drawMtx.unlock();
};

void Game::onScreen(sf::Time t_deltaTime)
{

	drawMtx.lock();
	if (m_playerPos.y > 1500
		|| m_playerPos.x < m_centre.x - 640
		|| m_playerPos.x > m_centre.x + 640)
	{
		// Offscreen
		//std::cout << "Offscreen" << std::endl;
		m_bgSprite.setPosition(0, 0);
		m_bgSprite2.setPosition(m_bgTexture.getSize().x * 0.7f, 0);
		m_moved = 1;
		m_gameState = State::Over;
		m_window.setView(m_window.getDefaultView());
		m_mainView = m_window.getView();
		m_centre = m_window.getView().getCenter();
		m_mainView.setCenter(m_centre);
		m_window.setView(m_mainView);
		m_blocks.clear();

		for (int i = 0; i < 10; i++)
		{
			m_blocks.push_back(new Block(m_world, (500 * i), 400, WORLD_SCALE));
		}
		delete m_player;
		m_player = new Player(m_world, 400, 200, WORLD_SCALE);
		baseDistance = 400.f;
		CAM_SPEED = 4.f;
	}
	else
	{
		m_timer->update(t_deltaTime.asMilliseconds(), m_centre.x);
		m_mainView.setCenter(m_centre);
		m_window.setView(m_mainView);
		m_world.Step(1 / 60.f, 10, 5); // Update the Box2d world

		m_centre.x += CAM_SPEED;
		m_player->update();
		for (int i = 0; i < m_blocks.size(); i++)
		{
			if (m_blocks.at(i)->getPosition().x < m_centre.x - (1280 / 2) - 250)
			{
				m_blocks.at(i)->~Block();
				m_blocks.erase(std::remove(m_blocks.begin(), m_blocks.end(), m_blocks.at(i)), m_blocks.end());
				int random = rand() % 200 - 1;
				random -= 100;
				m_blocks.push_back(new Block(m_world, m_blocks.at(m_blocks.size() - 1)->getPosition().x + baseDistance, 400 + random, WORLD_SCALE));
			}
		}
	}

	drawMtx.unlock();
};