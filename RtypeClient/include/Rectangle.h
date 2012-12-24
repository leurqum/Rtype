#pragma once

#include "Vector2.h"

template<typename T>
struct Rectangle
{
public:
	Rectangle(T w = 0, T h = 0, Vector2<T> p = Vector2<T>()) : position(p), width(w), height(h)
	{
		
	}

	Rectangle(const Rectangle& r) : position(r.position), width(r.width), height(r.height)
	{
		
	}

	Vector2<T> position;
	T width;
	T height;
};

