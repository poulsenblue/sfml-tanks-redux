#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "PhysicsUtil.h"
#include "TerrainColumn.h"


TerrainColumn::TerrainColumn(b2World* world, sf::Vector2f size, sf::Vector2f position)
{
	mShape = new sf::RectangleShape(size);
	mShape->setOrigin(size / 2.f);
	mShape->setPosition(position);
	mShape->setFillColor(sf::Color::Green);

	mBodyShape.SetAsBox(ng::sf_to_b2(size / 2.f, ng::SCALE).x, ng::sf_to_b2(size / 2.f, ng::SCALE).y);
	mBodyDef.position.Set(ng::sf_to_b2(position, ng::SCALE).x, ng::sf_to_b2(position, ng::SCALE).y);
	mBody = world->CreateBody(&mBodyDef);
	mBodyFixtureDef.shape = &mBodyShape;
	mBodyFixtureDef.density = 1.f;
	mBodyFixtureDef.friction = 1.f;
	mBody->CreateFixture(&mBodyShape, 1.f);
}

sf::RectangleShape* TerrainColumn::getShape()
{
	return mShape;
}
