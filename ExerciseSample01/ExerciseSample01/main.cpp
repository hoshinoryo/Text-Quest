#include <stdio.h>  // [1-1] 標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2] 標準ライブラリヘッダーをインクルードする
#include <string.h>
#include <time.h>
#include <conio.h>  // [1-5] コンソール入出力ヘッダーをインクルードする

#include "window.h"
#include "monster.h"
#include "map.h"
#include "battle.h"
#include "command.h"

// [5] 変数を宣言する場所

int currentMap; // [5-5] 現在のマップを宣言する

int playerX = 6;  // [5-6] プレイヤーのX座標
int playerY = 15; // [5-7] プレイヤーのY座標

// [6-1] ゲームを初期化する関数を宣言する
void Init()
{
	// [6-1-1] プレイヤーのステータスを初期化する
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

	// [6-1-2] 現在のマップを初期化する
	currentMap = MAP_KING_CASTLE;

	// [6-1-3] プレイヤーのX座標を初期化する
	playerX = 4;
	playerY = 6;
}

// [6-6] プログラムの実行開始点を宣言する
int main()
{
	// [6-6-1] 乱数をシャッフルする
	srand((unsigned int)time(NULL));

	SetConsoleWindowSize(34, 20);
	LockConsoleResize();

	Init();

	// [6-6-3] メインループ
	while (1)
	{
		Map_DrawMap(playerX, playerY, currentMap);

		// [6-6-5] プレイヤーの移動前の座標を宣言する
		int lastPlayerX = playerX;
		int lastPlayerY = playerY;

		switch (_getch())
		{
		case 'w': playerY--; break;
		case 's': playerY++; break;
		case 'a': playerX--; break;
		case 'd': playerX++; break;
		}

		// [6-6-12] マップの外に出たかどうかを判定する
		if ((playerX < 0) || (playerX >= MAP_WIDTH)         // Y座標がマップの範囲外
			|| (playerY < 0) || (playerY >= MAP_HEIGHT)     // X座標がマップの範囲外
			|| (map[currentMap][playerY][playerX] == '\0')) // 未設定のマス
		{
			switch (currentMap)
			{
			case MAP_KING_CASTLE: // [6-6-14] 王様の城
				// [6-6-15] フィールドマップに切り替える
				currentMap = MAP_FIELD;

				playerX = 6;
				playerY = 12;

				break;
			case MAP_BOSS_CASTLE:
				currentMap = MAP_FIELD;

				playerX = 10;
				playerY = 9;

				break;
			}
		}

		// [6-6-22] 移動先のマスの種類によって反応が分岐させる
		switch (map[currentMap][playerY][playerX])
		{
		case 'K': // 王様の城
			currentMap = MAP_KING_CASTLE;

			playerX = 6;
			playerY = 12;

			break;
		case 'B':
			currentMap = MAP_BOSS_CASTLE;

			playerX = 6;
			playerY = 15;

			break;
		case '0':
			// [6-6-32] 王様の会話メッセージを表示する
			printf("＊　「おお　ゆうしゃよ！\n"
				"ひがしの　まじょうの　まおう\n"
				"たおし　せかいを　すくってくれ！\n"
			);

			_getch();
			break;
		case '1':
			// [6-6-35] 姫の会話メッセージを表示する
			printf("＊　「かみに　いのりを　ささげます。\n"
				"おお　かみよ！\n"
				"ゆうしゃさまに　しゅくふくを！\n"
			);

			_getch();

			// [6-6-37] プレイヤーのHPを回復させる
			characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;
			characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;

			break;
		case '2':
			// [6-6-40] 魔王の会話メッセージを表示する
			printf("＊　「おろかな　にんげんよ！\n"
				"わが　やぼうを　はばむものは\n"
				"このよから　けしさってくれる！\n"
			);
			_getch();

			// [6-6-42] 魔王との戦闘を発生させる
			Battle_BattleScene(MONSTER_BOSS);

			_getch();

			// [6-6-43] 魔王が死んだかどうかを判定する
			if (characters[CHARACTER_MONSTER].hp <= 0)
			{
				// [6-6-44] 画面をクリアする
				system("cls");

				// [6-6-45] エンディングのメッセージを表示する
				printf("　まおうは　ほろび　せかいは\n"
					"めつぼうのききから　すくわれた！\n"
					"\n"
					"　おうは　ふれをだし　ゆうしゃを\n"
					"さがしもとめたが、だれも\n"
					"みたものは　いなかったという…\n"
					"\n"
					"\n"
					"　　　　ＴＨＥ　ＥＮＤ"
				);
				_getch();
			}
			break;
		}
		// [6-6-48] 移動先のマスの種類によって分岐させる
		switch (map[currentMap][playerY][playerX])
		{
		case '.': // 平地
		case '#': // 橋
			// [6-6-51] 敵と遭遇したかどうかを判定する
			if ((currentMap == MAP_FIELD) && (rand() % 16 == 0))
			{
				Battle_BattleScene(MONSTER_SLIME);
			}

			break;
		
		default:
			playerX = lastPlayerX;
			playerY = lastPlayerY;
			break;
		}

		// [6-6-56] プレイヤーが死んだかどうかを判定する
		if (characters[CHARACTER_PLAYER].hp <= 0)
		{
			Init();
			Map_DrawMap(playerX, playerY, currentMap);

			printf("＊　「おお　ゆうしゃよ！\n"
				"かみが　そなたを　すくわれた！\n"
				"ゆうしゃに　えいこう　あれ！\n"
			);
			_getch();
		}
	}
}
