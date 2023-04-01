#ifndef RRECTANGLE_H
#define RRECTANGLE_H

#include "assert.h"
#include "../conf_raylib.h"

Vector2 centerRect(const Rectangle &rect, float w, float h);
Vector2 centerRect(const Rectangle &rect, const Vector2 &dimension);

#endif