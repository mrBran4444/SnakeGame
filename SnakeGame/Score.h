#pragma once
#include "VisibleGameObject.h"
#include <string>

class Score : public VisibleGameObject
{
public:
	void AddPoint() 
	{
		points++;
	}
	std::vector<DrawableCoord> virtual GetDrawableBuffer()
	{
		drawableCoords.clear();
		std::wstring text = L"Your score : " + std::to_wstring(points);
		for (int i = 0; i < text.size(); i++)
		{
			drawableCoords.push_back(DrawableCoord({ i,0 }, text[i]));
		}
		return ToAbsolute();
	}
private:
	size_t points = 0;
};
