#pragma once
template<typename T>
struct Vector2
{
public:
	Vector2(T _x = T(), T _y = T()) : x(_x), y(_y)
	{

	}

	Vector2(const Vector2<T>& v) : x(v.x), y(v.y)
	{

	}
	T x;
	T y;
};

