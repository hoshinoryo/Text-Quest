// ==================================================
// File Name: monster.cpp
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Manage all monster entities
// ==================================================

#include "monster.h"

// モンスターのステータスの配列を宣言する
CHARACTER monsters[MONSTER_MAX] =
{
	// [5-1-1]MONSTER_PLAYER
	{
		100, 100, 15, 15, 30,
		"ゆうしゃ",
	},
	// [5-1-8]MONSTER_SLIME
	{
		3, 3, 0, 0, 2,
		"スライム",
		"／・Д ・＼\n"
		"～～～～～"
	},
	{
		255, 255, 0, 0, 50,
		"まおう",
		"　Ａ＠Ａ\n"
		"Ψ（▼ 皿▼ ）Ψ"
	},
};

// キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX] = {};