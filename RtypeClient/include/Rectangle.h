#pragma once

#include "Vector2.h"

template<typename T>
struct Rectangle
{
public:
	Rectangle(T w, T h, Vector2<T> p = Vector2<T>()) : position(p), width(w), height(h)
	{
		
	}

	Vector2<T> position;
	T width;
	T height;
};

