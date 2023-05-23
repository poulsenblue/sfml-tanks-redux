#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>


struct surface
{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body* BOD;
    sf::RectangleShape RECT;
};