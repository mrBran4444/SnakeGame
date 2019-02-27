#pragma once
#include <Windows.h>
#include "VisibleGameObject.h"
#include "vector"

class ScreenBuffer
{
public:
	ScreenBuffer(const size_t& width, const size_t& height);
	~ScreenBuffer() = default;               
	void Pos(int x, int y, wchar_t ch = 0);            				
	void Fill(const wchar_t& val);
	void AddDrawable(VisibleGameObject* gameObject);
	void RemoveDrawable(VisibleGameObject* gameObject);
	void Draw();
private:
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;

	std::vector<VisibleGameObject*> gameObjects;
	std::vector<wchar_t> buffer;
	size_t width;
	size_t height;
};

