#pragma once


class Tank
{


public:
	Tank(std::vector<Tank*>& gamePlayerList, b2World& world, sf::Vector2f pos);
	void update();
	void updatePhysics(sf::Time deltaTime);
	b2Body* getBody();
	sf::RectangleShape* getShape();
	void setWorld(b2World& world);

	void drive(float magnitude);

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;


private:
	sf::RectangleShape* tankShape;

	sf::Vector2f	position;
	sf::Vector2f	velocity;

	b2Body*			body;
	b2BodyDef		bodyDef;
	b2PolygonShape	bodyShape;
	b2FixtureDef	bodyFixtureDef;

};
