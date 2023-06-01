#include "Tank.h"
#include "Config.h"
#include "PhysicsUtil.h"




Tank::Tank(b2World* world, sf::Vector2f position)
	: mIsMovingLeft(false)
	, mIsMovingRight(false)
	, mIsMovingDown(false)
	, mIsMovingUp(false)
{
	sf::Vector2f size(20.f, 10.f);

	hullShape = new sf::RectangleShape(size);
	hullShape->setOrigin(size / 2.f);
	hullShape->setFillColor(sf::Color::Red);
	hullShape->setPosition(position);
	
	wheel1Shape = new sf::CircleShape(wheelRadius);
	//wheel1Shape->setOrigin(size / 2.f);
	wheel1Shape->setFillColor(sf::Color::White);
	wheel1Shape->setPosition(hullShape->getOrigin() + wheelPosition);

	mBodyShape.SetAsBox(ng::sf_to_b2(size / 2.f, ng::SCALE).x, ng::sf_to_b2(size / 2.f, ng::SCALE).y);
	mBodyDef.position.Set(ng::sf_to_b2(position, ng::SCALE).x, ng::sf_to_b2(position, ng::SCALE).y);
	mBodyDef.type = b2_dynamicBody;
	mBody = world->CreateBody(&mBodyDef);
	mBodyFixtureDef.shape = &mBodyShape;
	mBodyFixtureDef.density = 1.f;
	mBodyFixtureDef.friction = 2.f;
	mBody->CreateFixture(&mBodyShape, 1.f);

	mWheel1BodyShape.m_p.Set(2.0f, 3.0f);
	mWheel1BodyShape.m_radius = 0.5f;
	mWheel1BodyDef.position.Set(ng::sf_to_b2(position + wheelPosition, ng::SCALE).x, ng::sf_to_b2(position = wheelPosition, ng::SCALE).y);
	mWheel1BodyDef.type = b2_dynamicBody;
	mWheel1Body = world->CreateBody(&mWheel1BodyDef);
	mWheel1BodyFixtureDef.shape = &mWheel1BodyShape;
	mWheel1BodyFixtureDef.density = 1.f;
	mWheel1BodyFixtureDef.friction = 2.f;
	mWheel1Body->CreateFixture(&mWheel1BodyShape, 1.f);

	
}

void Tank::update()
{
	hullShape->setRotation(ng::toDegree(mBody->GetAngle()));
	hullShape->setPosition(ng::b2_to_sf(mBody->GetPosition().x, mBody->GetPosition().y, ng::SCALE));

	if (mIsMovingRight)
		drive(2.f);
	if (mIsMovingLeft)
		drive(-2.f);
}

sf::RectangleShape* Tank::getShape()
{
	return hullShape;
}

void Tank::drive(float magnitude)
{
	mBody->SetLinearVelocity(b2Vec2(magnitude, 0.f));
}


