// ==================================================
// File Name: command.h
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage the interaction of the command menu
// ==================================================

#ifndef COMMAND_H
#define COMMAND_H

enum Command // コマンドの種類
{
	COMMAND_FIGHT, // 戦う
	COMMAND_SPELL, // 呪文
	COMMAND_RUN,   // 逃げる
	COMMAND_MAX    // コマンドの種類の数
};

extern char commandNames[COMMAND_MAX][4 * 2 + 1];

void Command_SelectCommand();

#endif // COMMAND_H