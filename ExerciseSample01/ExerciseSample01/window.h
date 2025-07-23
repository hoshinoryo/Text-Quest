// ==================================================
// File Name: window.h
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Set the game window size
// ==================================================

#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>

// コンソールウィンドウサイズ変更
void SetConsoleWindowSize(int width, int height);
void LockConsoleResize();

#endif // WINDOW_H
