#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Block.h"
#include "MainMenuScreen.h"

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

	// Test
	Block * block;

	State m_gameState;
	Menu * m_menu;
};

#endif // !GAME_H