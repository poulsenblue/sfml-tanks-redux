#pragma once

#include "Tank.h"




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
	sf::CircleShape		mPlayer;
	sf::Clock			mFrameClock;


	//
	// Physics -- Box2d
	//
	b2Vec2		mGravity;
	b2World		mWorld;

	

	// Objects
	std::vector<Tank*> mPlayers;
};

int main()
{
	Game game;
	game.run();
}
