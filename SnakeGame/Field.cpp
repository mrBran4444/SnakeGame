#include "Field.h"

Field::Field(const size_t & width, const size_t & height, const wchar_t & borderSymbol, const wchar_t & fieldSymbol)
	: width(width)
	, height(height)
	, borderSymbol(borderSymbol)
	, fieldSymbol(fieldSymbol)
{
	Generate();
}

void Field::Generate()
{
	drawableCoords.clear();
	drawableCoords.reserve(width*height);
	for (Coord point(0, 0); point.x < width; point.x++)
	{
		for (point.y = 0; point.y < height; point.y++)
		{
			wchar_t tmpSymbol = fieldSymbol;
			if (0 == point.x || 0 == point.y || point.x == width - 1 || point.y == height - 1)
			{
				tmpSymbol = borderSymbol;
			}
			drawableCoords.push_back(DrawableCoord(point, tmpSymbol));
		}
	}
}
/*
* This method checks line equations instead of iterating all coordinates
*/
bool Field::CheckCollisionWithCoord(const DrawableCoord &collisionalbeCoord) const
{
	if (collisionalbeCoord.x == absolutePosition.x ||
		collisionalbeCoord.y == absolutePosition.y ||
		absolutePosition.x + width - 1 == collisionalbeCoord.x ||
		absolutePosition.y + height - 1 == collisionalbeCoord.y)
	{
		return true;
	}
	return false;
}