#include "Codeblock.h"

Codeblock::Codeblock() {
    backColor[0] = Gcolor::CODEBLOCK_BACKGROUND;
    backColor[1] = Gcolor::CODEBLOCK_BACKGROUND_FOCUS;
    foreColor[0] = Gcolor::CODEBLOCK_FOREGROUND;
    foreColor[1] = Gcolor::CODEBLOCK_FOREGROUND_FOCUS;
    linePadding = toVector2(Gui::CODEBLOCK_LINE_PADDING_X, Gui::CODEBLOCK_LINE_PADDING_Y);
    blockPadding = toVector2(Gui::CODEBLOCK_BLOCK_PADDING_X, Gui::CODEBLOCK_BLOCK_PADDING_Y);
    spacing = Gui::CODEBLOCK_SPACING;
    lines = std::vector<StyledText>();
    highlights = std::vector<int>();
}

void Codeblock::load(const std::string &path) {
    std::ifstream fin(path);
    assert(fin.is_open());
    std::string li;
    reset();
    blockDimension = blockPadding * 2;
    while (std::getline(fin, li)) {
        lines.emplace_back(li, Gfont::codeFont, spacing);
        blockDimension.x = std::max(blockDimension.x, lines.back().dim.x + (linePadding.x + blockPadding.x) * 2);
        blockDimension.y += lines.back().dim.y + linePadding.y * 2;
    }
    if (!lines.empty()) {
        textDimension = Vector2{blockDimension.x - (linePadding.x + blockPadding.x) * 2, lines[0].dim.y};
        lineDimension = Vector2{blockDimension.x - blockPadding.x * 2, lines[0].dim.y + linePadding.y * 2};
    }
    fin.close();
}

void Codeblock::reset() {
    textDimension = Z_VECT;
    lineDimension = Z_VECT;
    blockDimension = Z_VECT;
    lines.clear();
    highlights.clear();
}

Vector2 Codeblock::getBlockDimension() const {
    return blockDimension;
}

Vector2 Codeblock::getLineBoxPos(int id) const { // from (0, 0)
    return blockPadding + toVector2(0.0f, id * lineDimension.y);
}

Vector2 Codeblock::getLineTextPos(int id) const { // from (0, 0)
    return getLineBoxPos(id) + linePadding;
}

void Codeblock::setHighlight(const std::vector<int> &_highlights) {
    highlights = _highlights;
}

void Codeblock::resetHighlight() {
    highlights.clear();
}


void Codeblock::draw(float x, float y) {
    Vector2 org{(float)x,(float)y};
    DrawRectangleRec(toRectangle(org, blockDimension), backColor[0]);
    for (int i = 0; i < (int)lines.size(); ++i) {
        lines[i].draw(org + getLineTextPos(i), foreColor[0]);   
    }
    for (int id : highlights) {
        if (id < 0 || id >= (int)lines.size()) {
            // std::cerr << " >> id,lines.size() " << id << ' ' << lines.size() << '\n';
            assert(0 <= id && id < (int)lines.size());
        }
        DrawRectangleRec(toRectangle(org + getLineBoxPos(id), lineDimension), backColor[1]);
        lines[id].draw(org + getLineTextPos(id), foreColor[1]);
    }
}

void Codeblock::draw(const Vector2 &pos) {
    draw(pos.x, pos.y);
}
