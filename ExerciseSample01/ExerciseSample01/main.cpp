#include <stdio.h>  // [1-1] �W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2] �W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h>
#include <time.h>
#include <conio.h>  // [1-5] �R���\�[�����o�̓w�b�_�[���C���N���[�h����

#include "window.h"
#include "monster.h"
#include "map.h"
#include "battle.h"
#include "command.h"

// [5] �ϐ���錾����ꏊ

int currentMap; // [5-5] ���݂̃}�b�v��錾����

int playerX = 6;  // [5-6] �v���C���[��X���W
int playerY = 15; // [5-7] �v���C���[��Y���W

// [6-1] �Q�[��������������֐���錾����
void Init()
{
	// [6-1-1] �v���C���[�̃X�e�[�^�X������������
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

	// [6-1-2] ���݂̃}�b�v������������
	currentMap = MAP_KING_CASTLE;

	// [6-1-3] �v���C���[��X���W������������
	playerX = 4;
	playerY = 6;
}

// [6-6] �v���O�����̎��s�J�n�_��錾����
int main()
{
	// [6-6-1] �������V���b�t������
	srand((unsigned int)time(NULL));

	SetConsoleWindowSize(34, 20);
	LockConsoleResize();

	Init();

	// [6-6-3] ���C�����[�v
	while (1)
	{
		Map_DrawMap(playerX, playerY, currentMap);

		// [6-6-5] �v���C���[�̈ړ��O�̍��W��錾����
		int lastPlayerX = playerX;
		int lastPlayerY = playerY;

		switch (_getch())
		{
		case 'w': playerY--; break;
		case 's': playerY++; break;
		case 'a': playerX--; break;
		case 'd': playerX++; break;
		}

		// [6-6-12] �}�b�v�̊O�ɏo�����ǂ����𔻒肷��
		if ((playerX < 0) || (playerX >= MAP_WIDTH)         // Y���W���}�b�v�͈̔͊O
			|| (playerY < 0) || (playerY >= MAP_HEIGHT)     // X���W���}�b�v�͈̔͊O
			|| (map[currentMap][playerY][playerX] == '\0')) // ���ݒ�̃}�X
		{
			switch (currentMap)
			{
			case MAP_KING_CASTLE: // [6-6-14] ���l�̏�
				// [6-6-15] �t�B�[���h�}�b�v�ɐ؂�ւ���
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

		// [6-6-22] �ړ���̃}�X�̎�ނɂ���Ĕ��������򂳂���
		switch (map[currentMap][playerY][playerX])
		{
		case 'K': // ���l�̏�
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
			// [6-6-32] ���l�̉�b���b�Z�[�W��\������
			printf("���@�u�����@�䂤�����I\n"
				"�Ђ����́@�܂��傤�́@�܂���\n"
				"�������@���������@�������Ă���I\n"
			);

			_getch();
			break;
		case '1':
			// [6-6-35] �P�̉�b���b�Z�[�W��\������
			printf("���@�u���݂Ɂ@���̂���@�������܂��B\n"
				"�����@���݂�I\n"
				"�䂤���Ⴓ�܂Ɂ@���キ�ӂ����I\n"
			);

			_getch();

			// [6-6-37] �v���C���[��HP���񕜂�����
			characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;
			characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;

			break;
		case '2':
			// [6-6-40] �����̉�b���b�Z�[�W��\������
			printf("���@�u���납�ȁ@�ɂ񂰂��I\n"
				"�킪�@��ڂ����@�͂΂ނ��̂�\n"
				"���̂悩��@���������Ă����I\n"
			);
			_getch();

			// [6-6-42] �����Ƃ̐퓬�𔭐�������
			Battle_BattleScene(MONSTER_BOSS);

			_getch();

			// [6-6-43] ���������񂾂��ǂ����𔻒肷��
			if (characters[CHARACTER_MONSTER].hp <= 0)
			{
				// [6-6-44] ��ʂ��N���A����
				system("cls");

				// [6-6-45] �G���f�B���O�̃��b�Z�[�W��\������
				printf("�@�܂����́@�ق�с@��������\n"
					"�߂ڂ��̂�������@������ꂽ�I\n"
					"\n"
					"�@�����́@�ӂ�������@�䂤�����\n"
					"���������Ƃ߂����A�����\n"
					"�݂����̂́@���Ȃ������Ƃ����c\n"
					"\n"
					"\n"
					"�@�@�@�@�s�g�d�@�d�m�c"
				);
				_getch();
			}
			break;
		}
		// [6-6-48] �ړ���̃}�X�̎�ނɂ���ĕ��򂳂���
		switch (map[currentMap][playerY][playerX])
		{
		case '.': // ���n
		case '#': // ��
			// [6-6-51] �G�Ƒ����������ǂ����𔻒肷��
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

		// [6-6-56] �v���C���[�����񂾂��ǂ����𔻒肷��
		if (characters[CHARACTER_PLAYER].hp <= 0)
		{
			Init();
			Map_DrawMap(playerX, playerY, currentMap);

			printf("���@�u�����@�䂤�����I\n"
				"���݂��@���Ȃ����@������ꂽ�I\n"
				"�䂤����Ɂ@���������@����I\n"
			);
			_getch();
		}
	}
}
