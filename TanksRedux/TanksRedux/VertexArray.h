#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "PhysicsUtil.h"




class VertexArray
{

	VertexArray(sf::VertexArray vertices, int size)
		: sfmlVertexArray(vertices)
	{
		for (int i = 0; i < size; i++)
		{
			b2VertexArray[i] = ng::sf_to_b2(vertices[i].position, ng::SCALE);
		}
	}


private:
	sf::VertexArray			sfmlVertexArray;
	b2Vec2					b2VertexArray[];

};

