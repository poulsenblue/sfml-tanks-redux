#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "GameObject.h"




class Tank : public GameObject
{

public:

	Tank(b2World* world, sf::Vector2f position);
	
	void					update();
	sf::RectangleShape*		getShape();

	void					drive(float magnitude);

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;


private:

	sf::RectangleShape*		hullShape;
	sf::CircleShape*		wheel1Shape;
	sf::RectangleShape*		wheel2Shape;

	const float				wheelRadius = 10.f;
	const sf::Vector2f		wheelPosition = sf::Vector2f(-10.f, -5.f);
	const sf::Vector2f		tankSize = sf::Vector2f(20.f, 10.f);

	// Wheel body
	b2Body*				mWheel1Body;
	b2BodyDef			mWheel1BodyDef;
	b2CircleShape		mWheel1BodyShape;
	b2FixtureDef		mWheel1BodyFixtureDef;

};
