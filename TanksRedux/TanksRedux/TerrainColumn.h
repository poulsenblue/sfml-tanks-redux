#pragma once

#include "GameObject.h"




class TerrainColumn : public GameObject
{

public:

	TerrainColumn(b2World* world, sf::Vector2f size, sf::Vector2f position);
	sf::RectangleShape* getShape() override;


private:

	sf::RectangleShape* mShape;

};

