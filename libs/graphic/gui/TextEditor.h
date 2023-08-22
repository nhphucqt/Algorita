#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "raylib.h"
#include "../../external/TextEditor/include/Page.h"
#include "../../global.h"

class TextEditor {
private:
    Page page;
    int blinkAfterFrames;
	int blinkTime;
	bool isBlinking;
	int frameCounter;

public:
    bool isEnabled;

    TextEditor();
    void draw(Rectangle bounds);
    std::string getContent();
};

#endif