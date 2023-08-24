#include "../include/Page.h"
#include "raylib.h"

void Page::AddCharToCurrentLine(char c)
{
	if (m_LineIndex > -1)
	{
		m_Lines[m_LineIndex]->InsertCharacterAtCursor(c);
	}
}

void Page::HandleNewLine()
{
	if (m_LineIndex == m_Lines.size() - 1)
	{
		m_Lines.emplace_back(std::make_unique<TextLine>());
		m_LineIndex = m_Lines.size() - 1;
	}
	else
	{
		m_Lines.insert(m_Lines.begin() + m_LineIndex + 1, std::make_unique<TextLine>());
		m_LineIndex++;
	}
}

void Page::DeleteCurrentLine()
{
	if (m_Lines.size() > 1)
	{
		m_Lines.erase(m_Lines.begin() + m_LineIndex);
		if (m_LineIndex == m_Lines.size())
		{
			m_LineIndex--;
		}
	}
}

void Page::MoveCursorLeft()
{
	if (m_LineIndex > -1)
	{
		m_Lines[m_LineIndex]->MoveCursorLeft();
	}
}

void Page::MoveCursorRight()
{
	if (m_LineIndex > -1)
	{
		m_Lines[m_LineIndex]->MoveCursorRight();
	}
}

void Page::MoveDownLine()
{
	if (m_LineIndex < m_Lines.size() - 1)
	{
		m_LineIndex++;
	}
}

void Page::MoveUpLine()
{
	if (m_LineIndex > 0)
	{
		m_LineIndex--;
	}
}

void Page::DeleteCharacterAfterCursor()
{
	if (m_LineIndex > -1)
	{
		if (m_Lines[m_LineIndex]->Size() == 0)
		{
			DeleteCurrentLine();
			return;
		}
		m_Lines[m_LineIndex]->DeleteCharacterAfterCursor();
	}
}

void Page::DeleteCharacterAtCursor()
{
	if (m_LineIndex > -1)
	{
		if (m_Lines[m_LineIndex]->Size() == 0)
		{
			DeleteCurrentLine();
			return;
		}
		m_Lines[m_LineIndex]->DeleteCharacterAtCursor();
	}
}

void Page::Draw(Rectangle bounds)
{
	static char buffer[20];
	DrawRectangle(bounds.x, bounds.y, 20, bounds.height, Theme::currTheme.TEXT_EDITOR_LINE_NUMBER_BACKGROUND);
	for (int i = 0; i < m_Lines.size(); ++i)
	{
		const char* lineNumber = itoa(i + 1, buffer, 10);
		// int width = MeasureText(lineNumber, 20);
		int width = MeasureTextEx(*Gfont::defaultFont, lineNumber, 30, 0).x;
		// DrawText(lineNumber, bounds.x + 15 - width, bounds.y + 10 + i * 20, 20, BLACK);
		DrawTextEx(*Gfont::defaultFont, lineNumber, {bounds.x + 15 - width, bounds.y + 10 + i * 20}, 30, 0, Theme::currTheme.TEXT_EDITOR_LINE_NUMBER_FOREGROUND);
	}

	for (int i = 0; i < (int)m_Lines.size(); ++i)
	{
		std::string text = m_Lines[i]->ToString();
		// DrawText(text.c_str(), bounds.x + 20, bounds.y + 10 + i * 20, 20, BLACK);
		DrawTextEx(*Gfont::defaultFont, text.c_str(), {bounds.x + 20, bounds.y + 10 + i * 20}, 30, 0, Theme::currTheme.TEXT_EDITOR_FOREGROUND);
	}
}

void Page::GetCursorXY(int& x, int& y)
{
	if (m_LineIndex > -1)
	{
		std::string text = m_Lines[m_LineIndex]->ToString();
		// x = MeasureText(text.substr(0, m_Lines[m_LineIndex]->CursorIndex()).c_str(), 20);
		x = MeasureTextEx(*Gfont::defaultFont, text.substr(0, m_Lines[m_LineIndex]->CursorIndex()).c_str(), 30, 0).x;
		y = m_LineIndex * 20;
	}
	else
	{
		x = 0;
		y = 0;
	}
}
