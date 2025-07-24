// ==================================================
// File Name: command.h
// Date: 2025/07/24
// Author: Gu Anyi
// Description: Manage the interaction of the command menu
// ==================================================

#ifndef COMMAND_H
#define COMMAND_H

enum Command // �R�}���h�̎��
{
	COMMAND_FIGHT, // �키
	COMMAND_SPELL, // ����
	COMMAND_RUN,   // ������
	COMMAND_MAX    // �R�}���h�̎�ނ̐�
};

extern char commandNames[COMMAND_MAX][4 * 2 + 1];

void Command_SelectCommand();

#endif // COMMAND_H