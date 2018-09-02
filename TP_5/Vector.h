#pragma once
class Vector
{
public:
	Vector();
	Vector(int x_, int y_);
	Vector(Vector& v);
	~Vector();

	int get_x();
	int get_y();

	void set_x(int x_);
	void set_y(int y_);
	void inc_x(int dx);
	void inc_y(int dy);

private:
	int x;
	int y;
};

