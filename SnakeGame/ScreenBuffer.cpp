#include "ScreenBuffer.h"
#include <conio.h>
#include <algorithm>


ScreenBuffer::ScreenBuffer(const size_t& width, const size_t& height):width(width), height(height)
{
	hConsoleOutput = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	GetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo);
	curCursorInfo.dwSize = oldCursorInfo.dwSize;
	curCursorInfo.bVisible = oldCursorInfo.bVisible;
	curCursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOutput, &curCursorInfo);
	SetConsoleActiveScreenBuffer(hConsoleOutput);
	buffer.resize(width*height);
}

void ScreenBuffer::Pos(int x, int y, wchar_t ch) 
{
	buffer.at(y*width + x) = ch;
}

void ScreenBuffer::AddDrawable(VisibleGameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void ScreenBuffer::RemoveDrawable(VisibleGameObject* gameObject)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject));
}

void ScreenBuffer::Fill(const wchar_t& val)
{
	for (size_t i = 0; i < width; i++)
	{
		for(size_t j = 0; j < height; j++)
		Pos(i, j, val);
	}
}

void ScreenBuffer::Draw()
{
	Fill(L' ');
	for (auto gameObject : gameObjects)
	{
		auto buffer = gameObject->GetDrawableBuffer();
		for (auto drawableCoord : buffer)
		{
			Pos(drawableCoord.x, drawableCoord.y, drawableCoord.value);
		}
	}
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacterW(hConsoleOutput, buffer.data(), buffer.size(), { 0,0 }, &dwBytesWritten);
}