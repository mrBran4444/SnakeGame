#pragma once
struct Coord
{
	int x, y;

	Coord() : x(0), y(0) {}
	Coord(int _x, int _y) : x(_x), y(_y) {}
	bool operator==(const Coord& c) const
	{
		return x == c.x && y == c.y;
	}
	Coord& operator +=(const Coord& op) {
		x += op.x;
		y += op.y;
		return *this;
	}

	Coord operator +(const Coord& coord) {
		return Coord(x + coord.x, y + coord.y);
	}
};

struct DrawableCoord : public Coord
{
	DrawableCoord() = default;
	DrawableCoord(const Coord& p, const wchar_t& val) : value(val)
	{
		x = p.x;
		y = p.y;
	}
	wchar_t value;
};