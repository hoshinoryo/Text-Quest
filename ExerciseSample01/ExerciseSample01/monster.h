// ==================================================
// File Name: monster.h
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Manage all monster entities
// ==================================================

#ifndef MONSTER_H
#define MONSTER_H

// �L�����N�^�[�̎�ނ��`����
enum Character
{
	CHARACTER_PLAYER,  // �v���C���[
	CHARACTER_MONSTER, // �����X�^�[
	CHARACTER_MAX      // �L�����N�^�[�̎�ނ̐�
};

//�����X�^�[�̎�ނ��`����
enum Monster
{
	MONSTER_PLAYER, // �v���C���[
	MONSTER_SLIME,  // �X���C��
	MONSTER_BOSS,   // ����
	MONSTER_MAX     // �����X�^�[�̎�ނ̐�
};

// �L�����N�^�[�̍\���̂�錾����
struct CHARACTER
{
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;   // �U����
	char name[4 * 2 + 1]; // ���O�i�ő�4�����A2�o�C�g�����Ή��j
	char aa[256]; // �A�X�L�[�A�[�g
	int command;  // �R�}���h
	int target;   // �U���Ώ�
};

// extern�錾
extern CHARACTER monsters[MONSTER_MAX]; // �����X�^�[�̃X�e�[�^�X�̔z��
extern CHARACTER characters[CHARACTER_MAX]; // �L�����N�^�[�̔z��

#endif // MONSTER_H