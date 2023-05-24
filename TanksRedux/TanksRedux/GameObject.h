#pragma once


template <typename T>
class GameObject
{
	static_assert(std::is_base_of<sf::Shape>::value; "GameObject type must derive from sf::Shape");

public:

	GameObject();

	void update();
	b2Body* getBody();
	T* getShape();


private:

	T*				objectShape;

	b2Body*			body;
	b2BodyDef		bodyDef;
	b2PolygonShape	bodyShape;
	b2FixtureDef	bodyFixtureDef;

	b2Vec2			velocity;
	b2Vec2			position;

};