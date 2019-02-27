#pragma once
#include "VisibleGameObject.h"
#include "ICollisionable.h"

class Fruit : public VisibleGameObject, public ICollisionable
{
public:
	Fruit(const size_t& borderX, const size_t& borderY);
	void NextPosition();
	wchar_t GetSymbol();
	bool virtual CheckCollisionWithCoord(const DrawableCoord&) const;

	virtual ~Fruit() = default;
private:
	wchar_t NextFruitSymbol();

private:
	size_t maxX;
	size_t maxY;
};

