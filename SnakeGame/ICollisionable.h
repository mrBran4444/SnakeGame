#pragma once
#include "Coord.h"
#include "ICollisionProvokable.h"
#include <map>
#include <vector>
#include <functional>

class ICollisionable
{
public:
	virtual ~ICollisionable() {};
	/*
	* Iterates all provoked for provocateur
	*/
	void virtual ProcessCollision(const ICollisionProvokable* object) const
	{
		for (const auto & collisionableCoord : object->GetCollisionableCoords())
		{
			if (CheckCollisionWithCoord(collisionableCoord))
			{
				collisionCallbacks.at(object)();
				return; //current implemintation. In general we should check all collisions.
			}
		}
	}
	/*
	* Bind callback to a specific object
	*/
	void virtual BindCollisionCallback(const ICollisionProvokable* object, const std::function<void()>& callBack)
	{
		collisionCallbacks.insert(std::pair<decltype(object), decltype(callBack)>(object, callBack));
	}

protected:
	bool virtual CheckCollisionWithCoord(const DrawableCoord&) const = 0;

protected:
	std::map<const ICollisionProvokable*, std::function<void()>> collisionCallbacks;
};