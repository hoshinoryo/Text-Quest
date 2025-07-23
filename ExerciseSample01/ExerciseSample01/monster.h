// ==================================================
// File Name: monster.h
// Date: 2025/07/23
// Author: Gu Anyi
// Description: Manage all monster entities
// ==================================================

#ifndef MONSTER_H
#define MONSTER_H

// キャラクターの種類を定義する
enum Character
{
	CHARACTER_PLAYER,  // プレイヤー
	CHARACTER_MONSTER, // モンスター
	CHARACTER_MAX      // キャラクターの種類の数
};

//モンスターの種類を定義する
enum Monster
{
	MONSTER_PLAYER, // プレイヤー
	MONSTER_SLIME,  // スライム
	MONSTER_BOSS,   // 魔王
	MONSTER_MAX     // モンスターの種類の数
};

// キャラクターの構造体を宣言する
struct CHARACTER
{
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;   // 攻撃力
	char name[4 * 2 + 1]; // 名前（最大4文字、2バイト文字対応）
	char aa[256]; // アスキーアート
	int command;  // コマンド
	int target;   // 攻撃対象
};

// extern宣言
extern CHARACTER monsters[MONSTER_MAX]; // モンスターのステータスの配列
extern CHARACTER characters[CHARACTER_MAX]; // キャラクターの配列

#endif // MONSTER_H