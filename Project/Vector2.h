#pragma once

#include <math.h>

struct Vector2
{
	float x;
	float y;

	Vector2() :x(0.f), y(0.f) {}
	Vector2(float x, float y) :x(x), y(y) {}
	Vector2(const POINT& point) :x(float(point.x)), y(float(point.y)) {}

	float Degree()
	{
		double radian = atan2(this->y, this->x);
		return radian * (180 / 3.141592653589793);
	}

	float Length()
	{
		return 0.f;
	}

	static Vector2 Lerp(Vector2 a, Vector2 b, float t)
	{
		return (a * (1 - t)) + (b * t);
	}

	Vector2 operator+(const Vector2& v) 
	{
		return Vector2(this->x + v.x, this->y + v.y);
	}

	Vector2 operator-(const Vector2& v)
	{
		return Vector2(this->x - v.x, this->y - v.y);
	}

	Vector2 operator-()
	{
		return Vector2(-this->x, -this->y);
	}

	Vector2 operator/(const float s)
	{
		return Vector2(this->x / s, this->y / s);
	}

	Vector2 operator*(const float s)
	{
		return Vector2(this->x * s, this->y * s);
	}

	explicit operator POINT () const
	{
		return POINT {
			long(round(this->x)),
			long(round(this->y))
		};
	}
};