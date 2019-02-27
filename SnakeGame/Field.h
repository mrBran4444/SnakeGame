#pragma once
#include "VisibleGameObject.h"
class Field : public VisibleGameObject, public ICollisionable
{
public:
	Field() = default;
	Field(const size_t& width, const size_t& height) : Field(width, height, L'H', L'~')
	{}
	Field(const size_t& width, const size_t& height, const wchar_t& borderSymbol, const wchar_t& fieldSymbol);
	virtual ~Field() = default;

protected:
	virtual bool CheckCollisionWithCoord(const DrawableCoord &) const override;

private:
	void Generate();

private:
	size_t width;
	size_t height;
	wchar_t borderSymbol;
	wchar_t fieldSymbol;
};

