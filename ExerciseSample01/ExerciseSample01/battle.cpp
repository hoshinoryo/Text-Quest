// ==================================================
// File Name: battle.cpp
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage battle scene rendering
// ==================================================

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "battle.h"
#include "monster.h"
#include "command.h"

static constexpr int SPELL_COST = 3;  // [2-1] 呪文の消費MPを定義する

void Battle_DrawBattleScreen()
{
	// [6-2-1] 画面をクリアする
	system("cls");

	// [6-2-2] プレイヤーの名前を表示する
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("ＨＰ: %d／%d ＭＰ: %d／%d\n",
		characters[CHARACTER_PLAYER].hp,

		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp
	);
	printf("\n");

	// [6-2-5] モンスターもアスキーアートを描画する
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("（ＨＰ: %d／%d） \n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp
	);
	printf("\n");
}

void Battle_BattleScene(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[_monster];
	// [6-4-2] プレイヤーの攻撃対象をモンスターに設定する
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	Battle_DrawBattleScreen();
	printf("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);
	_getch();

	// [6-4-7] 戦闘が終了するまでループする
	while (1)
	{
		Command_SelectCommand();

		// [6-4-9] 各キャラクターを反複する
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10] 戦闘シーンの画面を描画する関数を呼び出す
			Battle_DrawBattleScreen();

			// [6-4-11] 選択されたコマンドで分岐する
			switch (characters[i].command)
			{
			case COMMAND_FIGHT:
			{
				printf("%sの　こうげき！\n", characters[i].name);

				// [6-4-15] 敵に与えるダメージを計算する
				int damage = 1 + rand() % characters[i].attack;

				// [6-4-16] 敵にダメージを与える
				characters[characters[i].target].hp -= damage;

				// [6-4-17] 敵のHPが負の値になったかどうかを判定する
				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}

				// [6-4-19] 戦闘シーンの画面を再描画する関数を呼び出す
				_getch();
				Battle_DrawBattleScreen();

				// [6-4-20] 敵にダメージを与えらメッセージを表示する
				printf("%sに　%dの　ダメージ！\n",
					characters[characters[i].target].name,
					damage
				);

				// [6-4-21] キーボード入力を待つ
				_getch();

				break;
			}
			case COMMAND_SPELL:
				// [6-4-23] MPが足りるかどうかを判定する
				if (characters[i].mp < SPELL_COST)
				{
					printf("ＭＰが　たりない！\n");
					_getch();

					break;
				}
				characters[i].mp -= SPELL_COST; // [6-4-27] MPを消費させる
				Battle_DrawBattleScreen();
				printf("%sは　ヒールを　となえた！\n", characters[i].name);
				_getch();

				characters[i].hp = characters[i].maxHp;
				Battle_DrawBattleScreen();
				printf("%sのきずが　かいふくした！\n", characters[i].name);
				_getch();

				break;
			case COMMAND_RUN: // [6-4-35] 逃げる
				printf("%sは　にげだした！\n", characters[i].name);
				_getch();

				return;

				break;
			}

			// [6-4-39] 攻撃対象を倒したかどうかを判定する
			if (characters[characters[i].target].hp <= 0)
			{
				// [6-4-40] 攻撃対象によって処理を分岐させる
				switch (characters[i].target)
				{
				case CHARACTER_PLAYER:
					printf("あなたは　しにました");

					break;
				case CHARACTER_MONSTER:
					// [6-4-44] モンスターのアスキーアートを何も表示しないように書き換える
					strcpy_s(characters[characters[i].target].aa, "\n");
					Battle_DrawBattleScreen();

					printf("%sを　たおした！\n", characters[characters[i].target].name);
					break;
				}

				_getch();
				return;
			}
		}
	}
}