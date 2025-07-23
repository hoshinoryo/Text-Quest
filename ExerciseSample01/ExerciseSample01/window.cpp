// ==================================================
// File Name: window.cpp
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Set the game window size
// ==================================================

#include "window.h"

void SetConsoleWindowSize(int width, int height)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD bufferSize = { (SHORT)width, (SHORT)height };
	SetConsoleScreenBufferSize(hOut, bufferSize);

	SMALL_RECT consoleWindow = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
	SetConsoleWindowInfo(hOut, TRUE, &consoleWindow);
}

void LockConsoleResize()
{
	HWND hwnd = GetConsoleWindow();

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, style);
}