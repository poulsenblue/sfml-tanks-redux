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

	sf::RectangleShape* tankShape;

};
