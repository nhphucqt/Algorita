#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../../rcore/rRectangle.h"
#include "StyledText.h"

class Codeblock {
private:
    Color backColor[2];
    Color foreColor[2];

    Vector2 linePadding, blockPadding;
    float spacing;

    Vector2 textDimension;
    Vector2 lineDimension;
    Vector2 blockDimension;
    
    std::vector<StyledText> lines;
    std::vector<int> highlights;

public:
    Codeblock();

    void load(const std::string &path);

    Vector2 getBlockDimension() const;

    Vector2 getLineBoxPos(int id) const; // from (0, 0)
    Vector2 getLineTextPos(int id) const; // from (0, 0)

    void setHighlight(const std::vector<int> &_highlights);
    void draw(float x, float y);
    void draw(const Vector2 &pos);
};

#endif