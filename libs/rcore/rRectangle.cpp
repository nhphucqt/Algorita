#include "rRectangle.h"

Rectangle toRectangle(const Vector2 &pos, const Vector2 &dim) {
    return Rectangle{pos.x, pos.y, dim.x, dim.y};
}

Vector2 centerRect(const Rectangle &rect, float w, float h) {
    return Vector2{rect.x + (rect.width - w) / 2, rect.y + (rect.height - h) / 2};
}

Rectangle centerRectRec(const Rectangle &rect, float w, float h) {
    return Rectangle{rect.x + (rect.width - w) / 2, rect.y + (rect.height - h) / 2, w, h};
}

Vector2 centerRect(const Rectangle &rect, const Vector2 &dimension) {
    assert(dimension.x <= rect.width && dimension.y <= rect.height);
    return Vector2{rect.x + (rect.width - dimension.x) / 2, rect.y + (rect.height - dimension.y) / 2};
}