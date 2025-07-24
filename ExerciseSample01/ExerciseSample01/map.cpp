// ==================================================
// File Name: map.cpp
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage all maps
// ==================================================

#include <stdio.h>
#include <Windows.h>

#include "map.h"
#include "monster.h"

static constexpr int SCREEN_WIDTH = 16;
static constexpr int SCREEN_HEIGHT = 12;

// マップの地形データを宣言する
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
	// [5-4-1] MAP_FIELD フィールド
	{
		"~~~~~~~~~~~~~~~~",
		"~~MMMMM~~MMMM.~~",
		"~M...M.##..M...~",
		"~M.M.M.~~M.M.M.~",
		"~M.M...~~M...M.~",
		"~M.MMMM~~MMMM..~",
		"~M..MM.~~~~~~#~~",
		"~~M.M.~~~~~~~#~~",
		"~~M.MM~~~~BMM..~",
		"~~...MM~~M.MMM.~",
		"~...~~M~~M...M.~",
		"~..~~~K~~MMM.M.~",
		"~..~~~.~~M...M.~",
		"~......~~M.MM..~",
		"~~....~~~~....~~",
		"~~~~~~~~~~~~~~~~"
	},
	// [5-4-2] MAP_KING_CASTLE 王様の城
	{
		"HHH.......HHH",
		"H.H.......H.H",
		"HHHHHHHHHHHHH",
		".H.........H.",
		".H.HHH.HHH.H.",
		".H.H0H.H1H.H.",
		".H.........H.",
		".HW.......WH.",
		".HY.......YH.",
		"HHHHHH.HHHHHH",
		"H.H~~~#~~~H.H",
		"HHH~~~#~~~HHH",
		"............."
	},
	// [5-4-3] MAP_BOSS_CASTLE 魔王の城
	{
		"HHH.......HHH",
		"H.H.......H.H",
		"HHHHHHHHHHHHH",
		".H....H....H.",
		".H..WHHHW..H.",
		".H..YH2HY..H.",
		".H.........H.",
		".H..W...W..H.",
		".H..Y...Y..H.",
		".H.........H.",
		"HHHHHH.HHHHHH",
		"H.H~~~#~~~H.H",
		"HHH~~~#~~~HHH",
		"~~~~~~#~~~~~~",
		"~~~~~~#~~~~~~",
		"............."
	},
};

void Map_DrawMap(int playerX, int playerY, int currentMap)
{
	system("cls");

	// [6-5-2] 描画するすべての行を反複する
	for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
	{
		for (int x = playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH / 2; x++)
		{
			if ((x == playerX) && (y == playerY))
			{
				printf("勇");
			}
			// [6-5-6] 対象の座標がマップデータの範囲外かどうかを判定する
			else if ((x < 0) || (x >= MAP_WIDTH)
				|| (y < 0) || (y >= MAP_HEIGHT)
				|| (map[currentMap][y][x] == '\0'))
			{
				switch (currentMap)
				{
				case MAP_FIELD:       printf("～"); break;
				case MAP_KING_CASTLE:
				case MAP_BOSS_CASTLE:
					printf("．"); break;
				}
			}
			else
			{
				// [6-5-12] マスの種類によって分岐する
				switch (map[currentMap][y][x])
				{
				case '~': printf("～"); break; // 海
				case '.': printf("．"); break; // 平地
				case 'M': printf("Ｍ"); break; // 山
				case '#': printf("＃"); break; // 橋
				case 'K': printf("王"); break; // 王様の城
				case 'B': printf("魔"); break; // 魔王の城
				case 'H': printf("〇"); break; // 壁debug
					//case 'H': printf("□"); break; // 壁
				case 'W': printf("炎"); break; // 炎
				case 'Y': printf("Ｙ"); break; // 燭台
				case '0': printf("王"); break; // 王
				case '1': printf("姫"); break; // 姫
				case '2': printf("魔"); break; // 魔王
				}
			}
		}
		printf("\n");
	}
	printf("\n");

	// [6-5-27] プレイヤーの名前を表示する
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	// [6-5-28] プレイヤーのステータスを表示する
	printf("ＨＰ: %d／%d ＭＰ: %d／%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);
	printf("\n");
}