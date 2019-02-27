#pragma once
#include <vector>
#include "Coord.h"
/*
* interface for object that can initiate collision with collisionable objects
*/
class ICollisionProvokable
{
public:
	virtual ~ICollisionProvokable() {}
	std::vector<DrawableCoord> virtual GetCollisionableCoords() const = 0;
};