#pragma once
#include "ICollisionable.h"
#include "ICollisionProvokable.h"
#include <vector>

typedef const ICollisionable* CPICollisionable;

/*
* This struct defines relationship between interactable and interactive objects
*/
struct CollisionGroup
{
	ICollisionProvokable* provocateur;
	std::vector< CPICollisionable > provoked;
};

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;
	void AddCollisionGroup(CollisionGroup && collisionGroup);
	void ProcessCollisions();
private:
	std::vector< CollisionGroup > collisionGroups;
};

