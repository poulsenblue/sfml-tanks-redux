#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Tank.h"
#include "TerrainColumn.h"
#include "Config.h"
#include "PhysicsUtil.h"
#include "DebugDraw.h"

#define DEBUG_DRAW_




Game::Game()
	: mWindow(sf::VideoMode(1280, 1024), "Tanks!")
	, mGravity(0.0f, 10.f)
	, mWorld(mGravity)
{
	
#ifdef DEBUG_DRAW_
	mDebugDrawer.setRenderWindow(&mWindow);
	mDebugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	mWorld.SetDebugDraw(&mDebugDrawer);
#endif
}

void Game::run()
{
	TerrainColumn testCol(&mWorld, sf::Vector2f(20.f, 500.f), sf::Vector2f(0, 774.f));
	mGameObjects.push_back(&testCol);

	TerrainColumn ground(&mWorld, sf::Vector2f(1280.f, 50.f), sf::Vector2f(640.f, 1000.f));
	mGameObjects.push_back(&ground);

	Tank playerTank(&mWorld, sf::Vector2f(300.f, 300.f));
	mPlayers.push_back(&playerTank);

	sf::Clock frameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time frameDelta = mFrameClock.restart();
		

		processEvents();

		// Catch-up loop to update physics consistently independent of framerate
		timeSinceLastUpdate += frameClock.restart();
		while (timeSinceLastUpdate > sf::seconds(conf::timeStep)) 
		{
			timeSinceLastUpdate -= sf::seconds(conf::timeStep);
			processEvents();
			update();
		}

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
	// Step the physics engine
	mWorld.Step(conf::timeStep, 8, 3);

	// Call update on every player
	std::vector<Tank*>::iterator iter;
	for (iter = mPlayers.begin(); iter != mPlayers.end(); iter++)
	{
		(*iter)->update();
	}
}

void Game::render()
{
	mWindow.clear();


	std::vector<GameObject*>::iterator obj_iter;
	for (obj_iter = mGameObjects.begin(); obj_iter != mGameObjects.end(); obj_iter++)
	{
		mWindow.draw(*(*obj_iter)->getShape());
	}

	std::vector<Tank*>::iterator tank_iter;
	for (tank_iter = mPlayers.begin(); tank_iter != mPlayers.end(); tank_iter++)
	{
		mWindow.draw(*(*tank_iter)->getShape());
	}

#ifdef DEBUG_DRAW_
	mWorld.DebugDraw();
#endif


	mWindow.display();
}