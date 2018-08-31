#pragma once
class Vector
{
public:
	Vector();
	Vector(double x_, double y_);
	Vector(Vector& v);
	~Vector();

	double get_x();
	double get_y();

	void set_x(double x_);
	void set_y(double y_);

private:
	double x;
	double y;
};

