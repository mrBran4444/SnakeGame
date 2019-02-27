#pragma once
#include "VisibleGameObject.h"
#include <list>

class Snake : public VisibleGameObject, public ICollisionable, public ICollisionProvokable
{
public:
	Snake(const Coord& startPos);
	virtual ~Snake() = default;
	void Move();
	void Grow(const wchar_t& bodySymbol);
	void ProcessCollision(const ICollisionProvokable* object) const override;
	bool CheckCollisionWithCoord(const DrawableCoord&) const override;
	std::vector<DrawableCoord> virtual GetCollisionableCoords() const override;
	void Die() { dead = true; }
	bool Dead() { return dead; }
	void SetDirection(const Coord& delta);
private:
	wchar_t ResolveDirection(const Coord & delta);
	Coord currentDirection;
	bool dead = false;
};

