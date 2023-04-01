#include "rColor.h"

Color TRNSP(Color color, float transparent) {
    color.a = round(color.a * transparent);
    return color;
}

Color TRANSCOLOR(const Color &source, const Color &destination, float percent) {
    // r g b a
    return CLITERAL(Color){
        (unsigned char)(source.r + (destination.r - source.r) * percent),
        (unsigned char)(source.g + (destination.g - source.g) * percent),
        (unsigned char)(source.b + (destination.b - source.b) * percent),
        (unsigned char)(source.a + (destination.a - source.a) * percent)
    };
}