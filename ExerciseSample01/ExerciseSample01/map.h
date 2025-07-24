// ==================================================
// File Name: map.h
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage all maps
// ==================================================

#ifndef MAP_H
#define MAP_H

constexpr int MAP_WIDTH = 16;
constexpr int MAP_HEIGHT = 16;

// マップの種類を定義する
enum Map
{
	MAP_FIELD,       // フィールド
	MAP_KING_CASTLE, // 王様の城
	MAP_BOSS_CASTLE, // 魔王の城
	MAP_MAX
};

extern char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1];

void Map_DrawMap(int playerX, int playerY, int cuurentMap);

#endif // MAP_H
