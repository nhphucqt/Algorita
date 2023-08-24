#include "TextEditor.h"

TextEditor::TextEditor() : blinkAfterFrames(30), blinkTime(30), isBlinking(false), frameCounter(0), isEnabled(false) {
    page.HandleNewLine();
}

void TextEditor::draw(Rectangle bounds) {
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125))
        {
            page.AddCharToCurrentLine((char)key);
            isBlinking = false;
            frameCounter = 0;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        page.MoveCursorRight();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        page.MoveCursorLeft();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_UP))
    {
        page.MoveUpLine();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        page.MoveDownLine();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_DELETE))
    {
        page.DeleteCharacterAfterCursor();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        page.DeleteCharacterAtCursor();
        isBlinking = false;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        page.HandleNewLine();
        isBlinking = false;
        frameCounter = 0;
    }

    frameCounter++;
    if (!isBlinking && frameCounter > blinkAfterFrames)
    {
        isBlinking = true;
        frameCounter = 0;
    }

    if (isBlinking)
    {
        frameCounter = frameCounter % (2 * blinkTime);
    }
    // Draw
    //----------------------------------------------------------------------------------
    int cursorX = 0, cursorY = 0;
    page.GetCursorXY(cursorX, cursorY);
    DrawRectanglePro(bounds, {0,0}, 0, Theme::currTheme.TEXT_EDITOR_BACKGROUND);
    if (isBlinking)
    {
        if (frameCounter < blinkTime)
        {
            DrawRectangle(bounds.x + 20 + cursorX, bounds.y + 10 + cursorY, 12, 20, DARKGRAY);
        }
    }
    else
    {
        DrawRectangle(bounds.x + 20 + cursorX, bounds.y + 10 + cursorY, 12, 20, DARKGRAY);
    }
    page.Draw(bounds);
}

std::string TextEditor::getContent() {
    std::string content;
    for (int i = 0; i < (int)page.m_Lines.size(); ++i) {
        std::string s = page.m_Lines[i]->ToString();
        s.pop_back();
        content += s + "\n";
    }
    return content;
}
