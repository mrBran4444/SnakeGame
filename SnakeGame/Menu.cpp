#include "Menu.h"

Menu::Menu()
{
	MenuItem item1(L"Play", Choice::Play);
	item1.SetAbsolutePosition({ 0,0 });
	MenuItem item2(L"Quit", Choice::Quit);
	item2.SetAbsolutePosition({ 0,1 });
	items.push_back(item1);
	items.push_back(item2);
	items[selectedItem].selected = true;
}

std::vector<DrawableCoord> Menu::GetDrawableBuffer()
{
	drawableCoords.clear();

	for (auto & item : items)
	{
		auto drawItem = item.GetDrawableBuffer();
		drawableCoords.insert(drawableCoords.end(), drawItem.begin(), drawItem.end());
	}
	return ToAbsolute();
}

void Menu::Next()
{
	items[selectedItem].selected = false;
	selectedItem++;
	if (selectedItem == items.size())
		selectedItem = 0;
	items[selectedItem].selected = true;
}

Choice Menu::GetChoice()
{
	return (Choice)items[selectedItem];
}

MenuItem::MenuItem(const std::wstring & text, const Choice & choice) : selected(false), text(text), choice(choice)
{
	Build(text);
}

std::vector<DrawableCoord> MenuItem::GetDrawableBuffer()
{
	if (selected)
	{
		Build(L"-----" + text + L"-----");
	}
	else
	{
		Build(L"     " + text + L"     ");
	}
	return ToAbsolute();
}

MenuItem::operator Choice() const
{
	return choice;
}
/*
* This method converts string to vector of drawable coordinates
*/
void MenuItem::Build(const std::wstring & text)
{
	drawableCoords.clear();
	for (int i = 0; i < text.size(); i++)
	{
		drawableCoords.push_back(DrawableCoord({ i,0 }, text[i]));
	}
}
