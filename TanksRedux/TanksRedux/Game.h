#pragma once

#include "Tank.h"
#include "Surface.h"
#include "DebugDraw.h"




class Game
{
public:
	Game();
	void	run();

private:
	void	processEvents();
	void	handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void	update();
	void	render();

	//
	// SFML
	//
	sf::RenderWindow	mWindow;
	sf::Clock			mFrameClock;


	//
	// Physics -- Box2d
	//
	b2Vec2		mGravity;
	b2World		mWorld;
	DebugDraw	mDebugDrawer;
	

	// Objects
	std::vector<Tank*> mPlayers;
	surface mGround;
};

int main()
{
	Game game;
	game.run();
}
