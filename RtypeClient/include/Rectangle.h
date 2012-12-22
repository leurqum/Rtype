#pragma once

#include "Vector2.h"

template<typename T>
struct Rectangle
{
public:
	Vector2<T> position;
	T width;
	T height;
};

