// ==================================================
// File Name: command.cpp
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage the interaction of the command menu
// ==================================================

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "command.h"
#include "monster.h"
#include "battle.h"

char commandNames[COMMAND_MAX][4 * 2 + 1]
{
	"たたかう",
	"じゅもん",
	"にげる"
};

void Command_SelectCommand()
{
	// [6-3-1] プレイヤーのコマンドを初期化する
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	// [6-3-2] コマンドが決定されるまでループする
	while (1)
	{
		Battle_DrawBattleScreen();

		// [6-3-17] カーソルを上下にループさせる
		characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;

		// [6-3-4] コマンドの一覧を表示する
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			// [6-3-5] 選択中のコマンドなら
			if (i == characters[CHARACTER_PLAYER].command)
			{
				// [6-3-6] カーソルを描画する
				printf(">");
			}
			// [6-3-7] 選択中のコマンドでなければ
			else
			{
				// [6-3-8] スペース描画する
				printf(" ");
			}
			printf("%s\n", commandNames[i]);
		}
		switch (_getch())
		{
		case 'w':
			characters[CHARACTER_PLAYER].command--;
			break;
		case 's':
			characters[CHARACTER_PLAYER].command++;
			break;
		default:
			return;
		}
	}
}
