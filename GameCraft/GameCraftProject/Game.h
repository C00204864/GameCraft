#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
<<<<<<< HEAD
#include "Player.h"

class Player;
=======
#include "Block.h"
#include "MainMenuScreen.h"

class Menu;

enum State 
{
	MainMenu,
	Play
};
>>>>>>> 83154645c3f2c7e9f9185d602dbfcbc4fa5d0f93

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
<<<<<<< HEAD

	Player* m_player;
=======
	const float WORLD_SCALE = 30.f;

	// Test
	Block * block;

	State m_gameState;
	Menu * m_menu;
>>>>>>> 83154645c3f2c7e9f9185d602dbfcbc4fa5d0f93
};

#endif // !GAME_H