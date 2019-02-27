#pragma once
#include "Coord.h"
#include "ICollisionable.h"
#include <vector>

/*
 * Base clase for all drawable object
 */

class VisibleGameObject
{
public:
	VisibleGameObject() = default;
	virtual ~VisibleGameObject() = default;

	/*
	 * Get vector of symbols which would be drowen in screenBuffer
	 */
	std::vector<DrawableCoord> virtual GetDrawableBuffer()
	{
		return ToAbsolute();
	}

	/*
	 * Setting world point for objects.
	 * Internally objects are managed using local coordinates.
	 * Hence they will drawn in screenBuffer using absolute coordinates
	 */
	void SetAbsolutePosition(const Coord & newPos)
	{
		absolutePosition = newPos;
	}
protected:

	std::vector<DrawableCoord> virtual ToAbsolute() const
	{
		std::vector<DrawableCoord> absoluteCoords;
		for (auto coord : drawableCoords)
		{
			coord.x += absolutePosition.x;
			coord.y += absolutePosition.y;
			absoluteCoords.emplace_back(std::move(coord));
		}
		return absoluteCoords;
	}

protected:
	/*
	 *	Buffer for storing drawable objects
	 */
	std::vector<DrawableCoord> drawableCoords;
	Coord absolutePosition;
};
