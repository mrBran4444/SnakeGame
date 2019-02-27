#pragma once
#include "VisibleGameObject.h"
#include <string>

enum Choice
{
	Play,
	Quit
};

class MenuItem : public VisibleGameObject
{
public:
	MenuItem(const std::wstring& text, const Choice& choice);
	std::vector<DrawableCoord> GetDrawableBuffer() override;
	bool selected;
	operator Choice() const;
private:
	void Build(const std::wstring& text);
	std::wstring text;
	Choice choice;
};

class Menu : public VisibleGameObject
{
public:
	Menu();
	virtual ~Menu() = default;
	std::vector<DrawableCoord> virtual GetDrawableBuffer() override;
	void Next();
	Choice GetChoice();
private:
	std::vector<MenuItem> items;
	size_t selectedItem = 0;
};

