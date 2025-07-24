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

// �}�b�v�̎�ނ��`����
enum Map
{
	MAP_FIELD,       // �t�B�[���h
	MAP_KING_CASTLE, // ���l�̏�
	MAP_BOSS_CASTLE, // �����̏�
	MAP_MAX
};

extern char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1];

void Map_DrawMap(int playerX, int playerY, int cuurentMap);

#endif // MAP_H
