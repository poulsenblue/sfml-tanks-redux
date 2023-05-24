#include <iostream>

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Tank.h"
#include "Surface.h"
#include "Config.h"
#include "PhysicsUtil.h"
#include "DebugDraw.h"


#define DEBUG




Game::Game()
	: mWindow(sf::VideoMode(1280, 1024), "Tanks!")
	, mGravity(0.0f, 10.f)
	, mWorld(mGravity)
{
	// Initialize ground
	// TODO: move this to a method
	mGround.DEF.position.Set(ng::sf_to_b2(500.f, 500.f, conf::SCALE).x, ng::sf_to_b2(500.f, 500.f, conf::SCALE).y);
	mGround.RECT = sf::RectangleShape(sf::Vector2f(8000.f, 50.f));
	mGround.RECT.setOrigin(4000.f, 25.f);
	mGround.RECT.setPosition(500.f, 500.f);
	mGround.RECT.setFillColor(sf::Color(200, 75, 20, 255));
	mGround.SHAPE.SetAsBox(4000.0f / conf::SCALE, 25.f / conf::SCALE);
	mGround.BOD = mWorld.CreateBody(&mGround.DEF);
	mGround.FIX.shape = &mGround.SHAPE;
	mGround.FIX.density = 1.f;
	mGround.FIX.friction = 2.f;
	mGround.BOD->CreateFixture(&mGround.SHAPE, 1.0f);

	mSurfaces.push_back(&mGround);
	

	

	
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

		mWindow.draw(*playerTank.getShape());
		

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

	std::vector<surface*>::iterator surf_iter;
	for (surf_iter = mSurfaces.begin(); surf_iter != mSurfaces.end(); surf_iter++)
	{
		mWindow.draw((*surf_iter)->RECT);
	}

	std::vector<Tank*>::iterator tank_iter;
	for (tank_iter = mPlayers.begin(); tank_iter != mPlayers.end(); tank_iter++)
	{
		mWindow.draw(*(*tank_iter)->getShape());
	}

	mWindow.display();
}