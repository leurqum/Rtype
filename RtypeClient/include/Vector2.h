#pragma once
template<typename T>
struct Vector2
{
public:
	Vector2(T _x = T(), T _y = T()) : x(_x), y(_y)
	{

	}
	T x;
	T y;
};

