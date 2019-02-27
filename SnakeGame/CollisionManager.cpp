#include "CollisionManager.h"


void CollisionManager::AddCollisionGroup(CollisionGroup && collisionGroup)
{
	collisionGroups.emplace_back(std::move(collisionGroup));
}
void CollisionManager::ProcessCollisions()
{
	for (const auto& collisionGroup : collisionGroups)
	{
		for (const auto& provoked : collisionGroup.provoked)
		{
			provoked->ProcessCollision(collisionGroup.provocateur);
		}
	}
}
