#include "Vector.h"



Vector::Vector()
{
}

Vector::Vector(double x_, double y_)
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

double Vector::get_x()
{
	return x;
}

double Vector::get_y()
{
	return y;
}

void Vector::set_x(double x_)
{
	x = x_;
}

void Vector::set_y(double y_)
{
	y = y_;
}
