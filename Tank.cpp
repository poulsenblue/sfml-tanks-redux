#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Tank.h"
#include "Config.h"
#include "PhysicsUtil.h"


Tank::Tank(std::vector<Tank*> &gamePlayerList, b2World& world, sf::Vector2f pos)
{
	position = pos;
	velocity = sf::Vector2f(0.f, 0.f);

	tankShape = new sf::RectangleShape(sf::Vector2f(20.f, 10.f));
	tankShape->setFillColor(sf::Color::Red);

	bodyDef.position.Set(ng::sf_to_b2(pos, 1.f).x, ng::sf_to_b2(pos, 1.f).y);
	bodyDef.type = b2_dynamicBody;
	bodyShape.SetAsBox(10.f / conf::SCALE, 5.f / conf::SCALE);
	bodyFixtureDef.shape = &bodyShape;
	bodyFixtureDef.density = 0.3f;
	bodyFixtureDef.friction = 1.f;
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&bodyFixtureDef);

	gamePlayerList.push_back(this);
}

void Tank::update()
{
	tankShape->setRotation(body->GetAngle());
	tankShape->setPosition(body->GetPosition().x, body->GetPosition().y);
}

void Tank::updatePhysics(sf::Time deltaTime)
{
	tankShape->setRotation(body->GetAngle());
	tankShape->setPosition(body->GetPosition().x, body->GetPosition().y);
}

b2Body* Tank::getBody()
{
	return body;
}

sf::RectangleShape* Tank::getShape()
{
	return tankShape;
}

void Tank::setWorld(b2World& world)
{

}

void Tank::drive(float magnitude)
{
	body->SetLinearVelocity(b2Vec2(magnitude, 0.f));
}


