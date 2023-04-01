#include "rRectangle.h"

Vector2 centerRect(const Rectangle &rect, float w, float h) {
    return Vector2{rect.x + (rect.width - w) / 2, rect.y + (rect.height - h) / 2};
}

Vector2 centerRect(const Rectangle &rect, const Vector2 &dimension) {
    assert(dimension.x <= rect.width && dimension.y <= rect.height);
    return Vector2{rect.x + (rect.width - dimension.x) / 2, rect.y + (rect.height - dimension.y) / 2};
}