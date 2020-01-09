#pragma once

class Vector2
{
public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	inline Vector2 Normalize()
	{
		float l = Length();
		return Vector2(x / l, y / l);
	}

	inline float Length()
	{
		return SquareRoot(SquareLength());
	}

	inline float SquareLength()
	{
		return x * x + y * y;
	}

private:
	// https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
	double inline __declspec (naked) __fastcall SquareRoot(double n)
	{
		_asm fld qword ptr[esp + 4]
		_asm fsqrt
		_asm ret 8
	}
	//float SquareRoot(const float x)
	//{
	//	const float xhalf = 0.5f * x;

	//	union // get bits for floating value
	//	{
	//		float x;
	//		int i;
	//	} u;

	//	u.x = x;
	//	u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
	//	return x * u.x * (1.5f - xhalf * u.x * u.x);// Newton step, repeating increases accuracy 
	//}
};