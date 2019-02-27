#include "Fruit.h"

Fruit::Fruit(const size_t& _maxX, const size_t& _maxY) : maxX(_maxX), maxY(_maxY)
{
	drawableCoords.emplace_back(DrawableCoord());
	NextPosition();
}

void Fruit::NextPosition()
{
	drawableCoords[0].x = rand() % maxX;
	drawableCoords[0].y = rand() % maxY;
	drawableCoords[0].value = NextFruitSymbol();
}

wchar_t Fruit::GetSymbol()
{
	return drawableCoords[0].value;
}

bool Fruit::CheckCollisionWithCoord(const DrawableCoord& _point) const
{
	DrawableCoord absoluteCoord = ToAbsolute()[0];
	return (absoluteCoord.x == _point.x && absoluteCoord.y == _point.y);
}

wchar_t Fruit::NextFruitSymbol()
{
	return L'A' + rand() % (L'Z' - L'A');
}