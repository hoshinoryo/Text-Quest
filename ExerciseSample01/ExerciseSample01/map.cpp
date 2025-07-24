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

// �}�b�v�̒n�`�f�[�^��錾����
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
	// [5-4-1] MAP_FIELD �t�B�[���h
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
	// [5-4-2] MAP_KING_CASTLE ���l�̏�
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
	// [5-4-3] MAP_BOSS_CASTLE �����̏�
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

	// [6-5-2] �`�悷�邷�ׂĂ̍s�𔽕�����
	for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
	{
		for (int x = playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH / 2; x++)
		{
			if ((x == playerX) && (y == playerY))
			{
				printf("�E");
			}
			// [6-5-6] �Ώۂ̍��W���}�b�v�f�[�^�͈̔͊O���ǂ����𔻒肷��
			else if ((x < 0) || (x >= MAP_WIDTH)
				|| (y < 0) || (y >= MAP_HEIGHT)
				|| (map[currentMap][y][x] == '\0'))
			{
				switch (currentMap)
				{
				case MAP_FIELD:       printf("�`"); break;
				case MAP_KING_CASTLE:
				case MAP_BOSS_CASTLE:
					printf("�D"); break;
				}
			}
			else
			{
				// [6-5-12] �}�X�̎�ނɂ���ĕ��򂷂�
				switch (map[currentMap][y][x])
				{
				case '~': printf("�`"); break; // �C
				case '.': printf("�D"); break; // ���n
				case 'M': printf("�l"); break; // �R
				case '#': printf("��"); break; // ��
				case 'K': printf("��"); break; // ���l�̏�
				case 'B': printf("��"); break; // �����̏�
				case 'H': printf("�Z"); break; // ��debug
					//case 'H': printf("��"); break; // ��
				case 'W': printf("��"); break; // ��
				case 'Y': printf("�x"); break; // �C��
				case '0': printf("��"); break; // ��
				case '1': printf("�P"); break; // �P
				case '2': printf("��"); break; // ����
				}
			}
		}
		printf("\n");
	}
	printf("\n");

	// [6-5-27] �v���C���[�̖��O��\������
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	// [6-5-28] �v���C���[�̃X�e�[�^�X��\������
	printf("�g�o: %d�^%d �l�o: %d�^%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);
	printf("\n");
}