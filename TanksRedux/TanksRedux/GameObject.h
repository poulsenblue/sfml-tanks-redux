#pragma once




class GameObject
{

public:

	GameObject();

	virtual void			update();
	virtual sf::Shape*		getShape() = 0;


protected:

	b2Body*				mBody;
	b2BodyDef			mBodyDef;
	b2PolygonShape		mBodyShape;
	b2FixtureDef		mBodyFixtureDef;

};