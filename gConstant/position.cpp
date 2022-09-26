#include "position.h"

position::position() :x(0), y(0)
{
}
position::position(double _x, double _y) : x(_x), y(_y)
{
}
position position::operator*(float val)
{
	return position(x * val, y * val);
}

position position::operator-(position other)
{
	return position(x - other.x, y - other.y);
}

position position::operator+(position other)
{
	return position(x + other.x, y + other.y);
}

position position::operator/(float val)
{
	return position(x / val, y / val);
}

irr::core::vector3df position::p_vector()
{
	return irr::core::vector3df(y, 0, x);
}
