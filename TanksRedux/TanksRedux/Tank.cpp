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

	tankShape = new sf::RectangleShape(size);
	tankShape->setOrigin(size / 2.f);
	tankShape->setFillColor(sf::Color::Red);
	tankShape->setPosition(position);

	mBodyShape.SetAsBox(ng::sf_to_b2(size / 2.f, ng::SCALE).x, ng::sf_to_b2(size / 2.f, ng::SCALE).y);
	mBodyDef.position.Set(ng::sf_to_b2(position, ng::SCALE).x, ng::sf_to_b2(position, ng::SCALE).y);
	mBodyDef.type = b2_dynamicBody;
	mBody = world->CreateBody(&mBodyDef);
	mBodyFixtureDef.shape = &mBodyShape;
	mBodyFixtureDef.density = 1.f;
	mBodyFixtureDef.friction = 2.f;
	mBody->CreateFixture(&mBodyShape, 1.f);
}

void Tank::update()
{
	tankShape->setRotation(mBody->GetAngle());
	tankShape->setPosition(ng::b2_to_sf(mBody->GetPosition().x, mBody->GetPosition().y, ng::SCALE));

	if (mIsMovingRight)
		drive(2.f);
	if (mIsMovingLeft)
		drive(-2.f);
}

sf::RectangleShape* Tank::getShape()
{
	return tankShape;
}

void Tank::drive(float magnitude)
{
	mBody->SetLinearVelocity(b2Vec2(magnitude, 0.f));
}


