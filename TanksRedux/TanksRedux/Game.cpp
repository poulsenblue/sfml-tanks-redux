#include <iostream>

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
	, mGravity(0.0f, 10.f)
	, mWorld(mGravity)
{
	// Initialize ground
	// TODO: move this to a method
	mGround.DEF.position.Set(640.f / conf::SCALE, 2000.f / conf::SCALE);
	mGround.RECT = sf::RectangleShape(sf::Vector2f(8000.f, 50.f));
	mGround.RECT.setPosition(sf::Vector2f(0.f, 0.f));
	mGround.RECT.setFillColor(sf::Color(200, 75, 20, 255));
	mGround.SHAPE.SetAsBox(4000.0f / conf::SCALE, 25.f / conf::SCALE);
	mGround.BOD = mWorld.CreateBody(&mGround.DEF);
	mGround.FIX.shape = &mGround.SHAPE;
	mGround.FIX.density = 1.f;
	mGround.FIX.friction = 2.f;
	mGround.BOD->CreateFixture(&mGround.SHAPE, 1.0f);


	

	

	
#ifdef DEBUG
	// Debug
	mDebugDrawer.setRenderWindow(&mWindow);
	mDebugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	mWorld.SetDebugDraw(&mDebugDrawer);
#endif



}

void Game::run()
{
	// Create Player
	Tank playerTank(mPlayers, mWorld, sf::Vector2f(20.f, 0.f));

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
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	std::cout << "input: " << std::to_string(key) << std::endl;

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
	std::vector<Tank*>::iterator iter;
	for (iter = mPlayers.begin(); iter != mPlayers.end(); iter++)
	{
		(*iter)->update();
	}
}

void Game::render()
{
	mWindow.clear();

	mWorld.DebugDraw();

	mWindow.display();
}