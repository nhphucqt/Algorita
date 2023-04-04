#ifndef RRECTANGLE_H
#define RRECTANGLE_H

#include "assert.h"
#include "../conf_raylib.h"

Rectangle toRectangle(const Vector2 &pos, const Vector2 &dim);

Vector2 centerRect(const Rectangle &rect, float w, float h);
Vector2 centerRect(const Rectangle &rect, const Vector2 &dimension);


#endif