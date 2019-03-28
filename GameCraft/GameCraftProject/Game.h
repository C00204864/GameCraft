#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Block.h"
#include "MainMenuScreen.h"
#include "Player.h"
#include "Timer.h"
#include "GameOver.h"
#include "Collect.h"

#include <thread>
#include <mutex>
#include "ThreadPool.h"

class Player;
class Menu;
class GameOver;
class Collect;

enum State 
{
	MainMenu,
	Play,
	Over
};

class Game
{
public:
	// Public Methods
	Game();
	~Game();
	void run();
	void setGameState(State state);
	void endGame();
private:
	// Private Methods
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	// Private Members
	sf::RenderWindow m_window; // main SFML window
	sf::View m_mainView;
	sf::View m_miniMapView;
	bool m_exitGame; // control exiting game

	// Box2D
	b2Vec2 m_gravity;
	b2World m_world;
	const float WORLD_SCALE = 30.f;

	std::vector<Block *> m_blocks;

	State m_gameState;
	Menu * m_menu;
	GameOver * m_gameOver;
	sf::Vector2f m_centre;
	sf::View m_camera;
	float CAM_SPEED = 4.0f;
	float maxCamSpeed = 5.f;
	float baseDistance = 500.f;
	float maxDistance = 750.f;
	Player* m_player;
	Collect* m_collect;

	Timer * m_timer;

	// Background
	sf::Texture m_bgTexture;
	sf::Texture m_bgTexture2;
	sf::Sprite m_bgSprite;
	sf::Sprite m_bgSprite2;
	int m_moved;

	std::vector<std::thread> m_threads;
	std::mutex mtx;
	ThreadPool m_pool;

	void drawTimer();
	void drawBlocks();
	void drawPlayer();
	void drawCollect();
};

#endif // !GAME_H