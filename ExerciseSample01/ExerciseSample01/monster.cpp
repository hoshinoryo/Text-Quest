// ==================================================
// File Name: monster.cpp
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Manage all monster entities
// ==================================================

#include "monster.h"

// �����X�^�[�̃X�e�[�^�X�̔z���錾����
CHARACTER monsters[MONSTER_MAX] =
{
	// [5-1-1]MONSTER_PLAYER
	{
		100, 100, 15, 15, 30,
		"�䂤����",
	},
	// [5-1-8]MONSTER_SLIME
	{
		3, 3, 0, 0, 2,
		"�X���C��",
		"�^�E�D �E�_\n"
		"�`�`�`�`�`"
	},
	{
		255, 255, 0, 0, 50,
		"�܂���",
		"�@�`���`\n"
		"���i�� �M�� �j��"
	},
};

// �L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX] = {};