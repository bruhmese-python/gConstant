#pragma once

#include "irrlicht.h"

struct position //to be replaced with irrlicht position
{
public:
    double x, y;

    position();
    position(double _x, double _y);

    position operator-(position);
    position operator+(position);

    position operator*(float);
    position operator/(float);

    irr::core::vector3df p_vector();
};