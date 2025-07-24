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
	"��������",
	"�������",
	"�ɂ���"
};

void Command_SelectCommand()
{
	// [6-3-1] �v���C���[�̃R�}���h������������
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	// [6-3-2] �R�}���h�����肳���܂Ń��[�v����
	while (1)
	{
		Battle_DrawBattleScreen();

		// [6-3-17] �J�[�\�����㉺�Ƀ��[�v������
		characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;

		// [6-3-4] �R�}���h�̈ꗗ��\������
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			// [6-3-5] �I�𒆂̃R�}���h�Ȃ�
			if (i == characters[CHARACTER_PLAYER].command)
			{
				// [6-3-6] �J�[�\����`�悷��
				printf(">");
			}
			// [6-3-7] �I�𒆂̃R�}���h�łȂ����
			else
			{
				// [6-3-8] �X�y�[�X�`�悷��
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
