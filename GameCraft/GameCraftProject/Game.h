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

class Player;
class Menu;

enum State 
{
	MainMenu,
	Play
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
	sf::Vector2f m_centre;
	sf::View m_camera;
	float CAM_SPEED = 4.0f;
	Player* m_player;
};

#endif // !GAME_H