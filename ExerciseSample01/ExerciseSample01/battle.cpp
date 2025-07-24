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

static constexpr int SPELL_COST = 3;  // [2-1] �����̏���MP���`����

void Battle_DrawBattleScreen()
{
	// [6-2-1] ��ʂ��N���A����
	system("cls");

	// [6-2-2] �v���C���[�̖��O��\������
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("�g�o: %d�^%d �l�o: %d�^%d\n",
		characters[CHARACTER_PLAYER].hp,

		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp
	);
	printf("\n");

	// [6-2-5] �����X�^�[���A�X�L�[�A�[�g��`�悷��
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("�i�g�o: %d�^%d�j \n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp
	);
	printf("\n");
}

void Battle_BattleScene(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[_monster];
	// [6-4-2] �v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	Battle_DrawBattleScreen();
	printf("%s���@�����ꂽ�I\n", characters[CHARACTER_MONSTER].name);
	_getch();

	// [6-4-7] �퓬���I������܂Ń��[�v����
	while (1)
	{
		Command_SelectCommand();

		// [6-4-9] �e�L�����N�^�[�𔽕�����
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10] �퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
			Battle_DrawBattleScreen();

			// [6-4-11] �I�����ꂽ�R�}���h�ŕ��򂷂�
			switch (characters[i].command)
			{
			case COMMAND_FIGHT:
			{
				printf("%s�́@���������I\n", characters[i].name);

				// [6-4-15] �G�ɗ^����_���[�W���v�Z����
				int damage = 1 + rand() % characters[i].attack;

				// [6-4-16] �G�Ƀ_���[�W��^����
				characters[characters[i].target].hp -= damage;

				// [6-4-17] �G��HP�����̒l�ɂȂ������ǂ����𔻒肷��
				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}

				// [6-4-19] �퓬�V�[���̉�ʂ��ĕ`�悷��֐����Ăяo��
				_getch();
				Battle_DrawBattleScreen();

				// [6-4-20] �G�Ƀ_���[�W��^���烁�b�Z�[�W��\������
				printf("%s�Ɂ@%d�́@�_���[�W�I\n",
					characters[characters[i].target].name,
					damage
				);

				// [6-4-21] �L�[�{�[�h���͂�҂�
				_getch();

				break;
			}
			case COMMAND_SPELL:
				// [6-4-23] MP������邩�ǂ����𔻒肷��
				if (characters[i].mp < SPELL_COST)
				{
					printf("�l�o���@����Ȃ��I\n");
					_getch();

					break;
				}
				characters[i].mp -= SPELL_COST; // [6-4-27] MP���������
				Battle_DrawBattleScreen();
				printf("%s�́@�q�[�����@�ƂȂ����I\n", characters[i].name);
				_getch();

				characters[i].hp = characters[i].maxHp;
				Battle_DrawBattleScreen();
				printf("%s�̂������@�����ӂ������I\n", characters[i].name);
				_getch();

				break;
			case COMMAND_RUN: // [6-4-35] ������
				printf("%s�́@�ɂ��������I\n", characters[i].name);
				_getch();

				return;

				break;
			}

			// [6-4-39] �U���Ώۂ�|�������ǂ����𔻒肷��
			if (characters[characters[i].target].hp <= 0)
			{
				// [6-4-40] �U���Ώۂɂ���ď����𕪊򂳂���
				switch (characters[i].target)
				{
				case CHARACTER_PLAYER:
					printf("���Ȃ��́@���ɂ܂���");

					break;
				case CHARACTER_MONSTER:
					// [6-4-44] �����X�^�[�̃A�X�L�[�A�[�g�������\�����Ȃ��悤�ɏ���������
					strcpy_s(characters[characters[i].target].aa, "\n");
					Battle_DrawBattleScreen();

					printf("%s���@���������I\n", characters[characters[i].target].name);
					break;
				}

				_getch();
				return;
			}
		}
	}
}