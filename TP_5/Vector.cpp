#include "Vector.h"



Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(int x_, int y_)
{
	x = x_;
	y = y_;
}

Vector::Vector(Vector & v)
{
	x = v.get_x();
	y = v.get_y();
}


Vector::~Vector()
{
}

int Vector::get_x()
{
	return x;
}

int Vector::get_y()
{
	return y;
}

void Vector::set_x(int x_)
{
	x = x_;
}

void Vector::set_y(int y_)
{
	y = y_;
}

void Vector::inc_x(int dx)
{
	x += dx;
}

void Vector::inc_y(int dy)
{
	y += dy;
}
