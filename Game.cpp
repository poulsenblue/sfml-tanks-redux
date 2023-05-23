#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Tank.h"
#include "Surface.h"
#include "Config.h"
#include "DebugDraw.h"


#define DEBUG




Game::Game()
	: mWindow(sf::VideoMode(1280, 1024), "Tanks!")
	, mPlayer()
	, mGravity(0.0f, 10.f)
	, mWorld(mGravity)
{
	// Initialize ground
	// TODO: move this to a method
	surface ground;
	ground.DEF.position.Set(640.f / conf::SCALE, 2000.f / conf::SCALE);
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000.f, 50.f));
	ground.RECT.setPosition(sf::Vector2f(0.f, 0.f));
	ground.RECT.setFillColor(sf::Color(200, 75, 20, 255));
	ground.SHAPE.SetAsBox(4000.0f / conf::SCALE, 25.f / conf::SCALE);
	ground.BOD = mWorld.CreateBody(&ground.DEF);
	ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = 1.f;
	ground.FIX.friction = 2.f;
	ground.BOD->CreateFixture(&ground.SHAPE, 1.0f);


	// Create Player
	Tank playerTank(mPlayers, mWorld, sf::Vector2f(20.f, 0.f));

	


#ifdef DEBUG
	// Debug
	DebugDraw debugDrawer;
	debugDrawer.setRenderWindow(&mWindow);
	debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	mWorld.SetDebugDraw(&debugDrawer);
#endif



}

void Game::run()
{
	while (mWindow.isOpen())
	{
		sf::Time frameDelta = mFrameClock.restart();

		mWorld.Step(conf::timeStep, 8, 3);

		processEvents();
		update();
		render();

	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

		}
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	std::vector<Tank*>::iterator iter;
	for (iter = mPlayers.begin(); iter != mPlayers.end(); iter++)
	{
		if (key == sf::Keyboard::W)
		{
			(*iter)->mIsMovingUp = isPressed;
		}
		else if (key == sf::Keyboard::S)
		{
			(*iter)->mIsMovingDown = isPressed;
		}
		else if (key == sf::Keyboard::A)
		{
			(*iter)->mIsMovingLeft = isPressed;
		}
		else if (key == sf::Keyboard::D)
		{
			(*iter)->mIsMovingRight = isPressed;
		}
			
	}
	
}

void Game::update()
{

}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}