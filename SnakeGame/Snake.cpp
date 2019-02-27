#include "Snake.h"

Snake::Snake(const Coord & startPos) : currentDirection({0,-1})
{
	drawableCoords.push_back(DrawableCoord(startPos, ResolveDirection(currentDirection)));
}

void Snake::SetDirection(const Coord & delta)
{
	currentDirection = delta;
}

wchar_t Snake::ResolveDirection(const Coord & delta)
{
	if (delta.x < 0)
		return L'<';
	else if (delta.x > 0)
		return L'>';
	else if (delta.y < 0)
		return L'^';
	else
		return L'V';
}

/*
 * Simple array shifting
 * The TmpHead saved in order to recover "shifted out" snake head
 */
void Snake::Move()
{
	auto tmpHead = drawableCoords.front();
	tmpHead += currentDirection;
	for (size_t i = drawableCoords.size() - 1; i > 0; i--)
	{
		drawableCoords[i].x = drawableCoords[i-1].x;
		drawableCoords[i].y = drawableCoords[i-1].y;
	}
	drawableCoords.front() = tmpHead;
	drawableCoords.front().value = ResolveDirection(currentDirection);
}

void Snake::Grow(const wchar_t & bodySymbol)
{
	drawableCoords.push_back(DrawableCoord(drawableCoords.back(), bodySymbol));
}

/*
 * In this specific case this method has been ovveridden because of 
 * possibility of snake`s head collission with it`s head.
 */
void Snake::ProcessCollision(const ICollisionProvokable* object) const
{
	auto provocateur = object->GetCollisionableCoords();
	auto collisionableCoordsIter = drawableCoords.cbegin();
	if (object == this)
	{
		collisionableCoordsIter++;
	}
	for (const auto& provoc : provocateur)
	{
		for (; collisionableCoordsIter != drawableCoords.cend(); collisionableCoordsIter++)
		{
			if ((provoc.x == collisionableCoordsIter->x) && (provoc.y == collisionableCoordsIter->y))
			{
				collisionCallbacks.at(object)();
				return;
			}
		}
	}
	
}

bool Snake::CheckCollisionWithCoord(const DrawableCoord& _point) const
{
	std::vector<DrawableCoord> absoluteSnake = ToAbsolute();
	for (const auto& segment : absoluteSnake)
	{
		if ((segment.x == _point.x) && (segment.y == _point.y))
		{
			return true;
		}
	}
	return false;
}

std::vector<DrawableCoord> Snake::GetCollisionableCoords() const
{
	std::vector<DrawableCoord> ret;
	ret.push_back(drawableCoords.front());
	return ret;
}


