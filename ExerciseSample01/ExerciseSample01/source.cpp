// [1] ヘッダーをインクルードする場所
#include <windows.h>
#include <stdio.h>  // [1-1] 標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2] 標準ライブラリヘッダーをインクルードする
#include <string.h> // [1-3] 文字列操作ヘッダーをインクルードする
#include <time.h>   // [1-4] 時間管理ヘッダーをインクルードする
#include <conio.h>  // [1-5] コンソール入出力ヘッダーをインクルードする

// [2] 定数を定義する場所

constexpr int SPELL_COST = 3;  // [2-1] 呪文の消費MPを定義する
constexpr int MAP_WIDTH  = 16; // [2-2] マップの幅を定義する
constexpr int MAP_HEIGHT = 16;
constexpr int SCREEN_WIDTH  = 16; // [2-4] スクロール画面の幅を定義する
constexpr int SCREEN_HEIGHT = 12;

// [3] 列挙定数を定義する場所

// [3-1] モンスターの種類を定義する
enum Monster
{
	MONSTER_PLAYER, // [3-1-1] プレイヤー
	MONSTER_SLIME,  // [3-1-2] スライム
	MONSTER_BOSS,
	MONSTER_MAX     // [3-1-4] モンスターの種類の数
};

// [3-2] キャラクターの種類を定義する
enum Character
{
	CHARACTER_PLAYER,  // [3-2-1]プレイヤー
	CHARACTER_MONSTER, // [3-2-2]モンスター
	CHARACTER_MAX      // [3-2-3]キャラクターの種類の数
};

// [3-3] コマンドの種類を定義する
enum Command
{
	COMMAND_FIGHT, // 戦う
	COMMAND_SPELL, // 呪文
	COMMAND_RUN,   // 逃げる
	COMMAND_MAX    // コマンドの種類の数
};

// [3-4] マップの種類を定義する
enum Map
{
	MAP_FIELD,       // [3-4-1] フィールド
	MAP_KING_CASTLE, // [3-4-2] 王様の城
	MAP_BOSS_CASTLE, // [3-4-2] 魔王の城
	MAP_MAX
};

// [4] 構造体を定義する場所

// [4-1] キャラクターの構造体を宣言する
struct CHARACTER
{
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;   // [4-1-5] 攻撃力
	char name[4 * 2 + 1];
	char aa[256]; // [4-1-7] アスキーアート
	int command;  // [4-1-8] コマンド
	int target;   // [4-1-9] 攻撃対象
};

// [5] 変数を宣言する場所

// [5-1] モンスターのステータスの配列を宣言する
CHARACTER monsters[MONSTER_MAX] =
{
	// [5-1-1]MONSTER_PLAYER
	{
		100, 100, 15, 15, 30,
		"ゆうしゃ",
	},
	// [5-1-8]MONSTER_SLIME
	{
		3, 3, 0, 0, 2,
		"スライム",
		"／・Д ・＼\n"
		"～～～～～"
	},
	{
		255, 255, 0, 0, 50,
		"まおう",
		"　Ａ＠Ａ\n"
		"Ψ（▼ 皿▼ ）Ψ"
	},
};

// [5-2] キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX] = {};

// [5-3] コマンドの名前を宣言する
char commandNames[COMMAND_MAX][4 * 2 + 1]
{
	"たたかう",
	"じゅもん",
	"にげる"
};

// [5-4] マップの地形データを宣言する
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
	// [5-4-1] MAP_FIELD フィールド
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
	// [5-4-2] MAP_KING_CASTLE 王様の城
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
	// [5-4-3] MAP_BOSS_CASTLE 魔王の城
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

int currentMap; // [5-5] 現在のマップを宣言する

int playerX = 6;  // [5-6] プレイヤーのX座標
int playerY = 15; // [5-7] プレイヤーのY座標

// [6] 関数を宣言する場所

// [6-1] ゲームを初期化する関数を宣言する
void Init()
{
	// [6-1-1] プレイヤーのステータスを初期化する
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

	// [6-1-2] 現在のマップを初期化する
	currentMap = MAP_KING_CASTLE;

	// [6-1-3] プレイヤーのX座標を初期化する
	playerX = 4;
	playerY = 6;
}

// [6-2] 戦闘シーンの画面描画する関数を宣言する
void DrawBattleScreen()
{
	// [6-2-1] 画面をクリアする
	system("cls");

	// [6-2-2] プレイヤーの名前を表示する
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("ＨＰ: %d／%d ＭＰ: %d／%d\n",
		characters[CHARACTER_PLAYER].hp,
	
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp
	);
	printf("\n");

	// [6-2-5] モンスターもアスキーアートを描画する
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("（ＨＰ: %d／%d） \n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp
	);
	printf("\n");
}

// [6-3] コマンドを選択する関数を宣言する
void SelectCommand()
{
	// [6-3-1] プレイヤーのコマンドを初期化する
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	// [6-3-2] コマンドが決定されるまでループする
	while (1)
	{
		DrawBattleScreen();

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

// [6-4] 戦闘シーンの関数を宣言する
void Battle(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[_monster];
	// [6-4-2] プレイヤーの攻撃対象をモンスターに設定する
	characters[CHARACTER_PLAYER].target  = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	DrawBattleScreen();
	printf("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);
	_getch();

	// [6-4-7] 戦闘が終了するまでループする
	while (1)
	{
		SelectCommand();

		// [6-4-9] 各キャラクターを反複する
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10] 戦闘シーンの画面を描画する関数を呼び出す
			DrawBattleScreen();

			// [6-4-11] 選択されたコマンドで分岐する
			switch (characters[i].command)
			{
			case COMMAND_FIGHT:
			{
				printf("%sの　こうげき！\n", characters[i].name);

				// [6-4-15] 敵に与えるダメージを計算する
				int damage = 1 + rand() % characters[i].attack;

				// [6-4-16] 敵にダメージを与える
				characters[characters[i].target].hp -= damage;

				// [6-4-17] 敵のHPが負の値になったかどうかを判定する
				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}

				// [6-4-19] 戦闘シーンの画面を再描画する関数を呼び出す
				_getch();
				DrawBattleScreen();

				// [6-4-20] 敵にダメージを与えらメッセージを表示する
				printf("%sに　%dの　ダメージ！\n",
					characters[characters[i].target].name,
					damage
				);

				// [6-4-21] キーボード入力を待つ
				_getch();

				break;
			}
			case COMMAND_SPELL:
				// [6-4-23] MPが足りるかどうかを判定する
				if (characters[i].mp < SPELL_COST)
				{
					printf("ＭＰが　たりない！\n");
					_getch();

					break;
				}
				characters[i].mp -= SPELL_COST; // [6-4-27] MPを消費させる
				DrawBattleScreen();
				printf("%sは　ヒールを　となえた！\n", characters[i].name);
				_getch();

				characters[i].hp = characters[i].maxHp;
				DrawBattleScreen();
				printf("%sのきずが　かいふくした！\n", characters[i].name);
				_getch();

				break;
			case COMMAND_RUN: // [6-4-35] 逃げる
				printf("%sは　にげだした！\n", characters[i].name);
				_getch();

				return;

				break;
			}

			// [6-4-39] 攻撃対象を倒したかどうかを判定する
			if (characters[characters[i].target].hp <= 0)
			{
				// [6-4-40] 攻撃対象によって処理を分岐させる
				switch (characters[i].target)
				{
				case CHARACTER_PLAYER:
					printf("あなたは　しにました");

					break;
				case CHARACTER_MONSTER:
					// [6-4-44] モンスターのアスキーアートを何も表示しないように書き換える
					strcpy_s(characters[characters[i].target].aa, "\n");
					DrawBattleScreen();

					printf("%sを　たおした！\n", characters[characters[i].target].name);
					break;
				}

				_getch();
				return;
			}
		}
	}
}

// [6-5] マップを描画する処理を記述する関数を宣言する
void DrawMap()
{
	system("cls");

	// [6-5-2] 描画するすべての行を反複する
	for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
	{
		for (int x = playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH / 2; x++)
		{
			if ((x == playerX) && (y == playerY))
			{
				printf("勇");
			}
			// [6-5-6] 対象の座標がマップデータの範囲外かどうかを判定する
			else if ((x < 0) || (x >= MAP_WIDTH)
				|| (y < 0) || (y >= MAP_HEIGHT)
				|| (map[currentMap][y][x] == '\0'))
			{
				switch (currentMap)
				{
				case MAP_FIELD:       printf("～"); break;
				case MAP_KING_CASTLE: 
				case MAP_BOSS_CASTLE:
					printf("．"); break;
				}
			}
			else
			{
				// [6-5-12] マスの種類によって分岐する
				switch (map[currentMap][y][x])
				{
				case '~': printf("～"); break; // 海
				case '.': printf("．"); break; // 平地
				case 'M': printf("Ｍ"); break; // 山
				case '#': printf("＃"); break; // 橋
				case 'K': printf("王"); break; // 王様の城
				case 'B': printf("魔"); break; // 魔王の城
				case 'H': printf("〇"); break; // 壁debug
				//case 'H': printf("□"); break; // 壁
				case 'W': printf("炎"); break; // 炎
				case 'Y': printf("Ｙ"); break; // 燭台
				case '0': printf("王"); break; // 王
				case '1': printf("姫"); break; // 姫
				case '2': printf("魔"); break; // 魔王
				}
			}
		}
		printf("\n");
	}
	printf("\n");

	// [6-5-27] プレイヤーの名前を表示する
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	// [6-5-28] プレイヤーのステータスを表示する
	printf("ＨＰ: %d／%d ＭＰ: %d／%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);
	printf("\n");
}

// コンソールウィンドウサイズ変更
void SetConsoleWindowSize(int width, int height)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD bufferSize = { (SHORT)width, (SHORT)height };
	SetConsoleScreenBufferSize(hOut, bufferSize);

	SMALL_RECT consoleWindow = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
	SetConsoleWindowInfo(hOut, TRUE, &consoleWindow);
}

void LockConsoleResize()
{
	HWND hwnd = GetConsoleWindow();

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, style);
}

// [6-6] プログラムの実行開始点を宣言する
int main()
{
	// [6-6-1] 乱数をシャッフルする
	srand((unsigned int)time(NULL));

	SetConsoleWindowSize(34, 20);
	LockConsoleResize();

	Init();

	// [6-6-3] メインループ
	while (1)
	{
		DrawMap();

		// [6-6-5] プレイヤーの移動前の座標を宣言する
		int lastPlayerX = playerX;
		int lastPlayerY = playerY;

		switch (_getch())
		{
		case 'w': playerY--; break;
		case 's': playerY++; break;
		case 'a': playerX--; break;
		case 'd': playerX++; break;
		}

		// [6-6-12] マップの外に出たかどうかを判定する
		if ((playerX < 0) || (playerX >= MAP_WIDTH)         // Y座標がマップの範囲外
			|| (playerY < 0) || (playerY >= MAP_HEIGHT)     // X座標がマップの範囲外
			|| (map[currentMap][playerY][playerX] == '\0')) // 未設定のマス
		{
			switch (currentMap)
			{
			case MAP_KING_CASTLE: // [6-6-14] 王様の城
				// [6-6-15] フィールドマップに切り替える
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

		// [6-6-22] 移動先のマスの種類によって反応が分岐させる
		switch (map[currentMap][playerY][playerX])
		{
		case 'K': // 王様の城
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
			// [6-6-32] 王様の会話メッセージを表示する
			printf("＊　「おお　ゆうしゃよ！\n"
				"ひがしの　まじょうの　まおう\n"
				"たおし　せかいを　すくってくれ！\n"
			);

			_getch();
			break;
		case '1':
			// [6-6-35] 姫の会話メッセージを表示する
			printf("＊　「かみに　いのりを　ささげます。\n"
				"おお　かみよ！\n"
				"ゆうしゃさまに　しゅくふくを！\n"
			);

			_getch();

			// [6-6-37] プレイヤーのHPを回復させる
			characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;
			characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;

			break;
		case '2':
			// [6-6-40] 魔王の会話メッセージを表示する
			printf("＊　「おろかな　にんげんよ！\n"
				"わが　やぼうを　はばむものは\n"
				"このよから　けしさってくれる！\n"
			);
			_getch();

			// [6-6-42] 魔王との戦闘を発生させる
			Battle(MONSTER_BOSS);

			_getch();

			// [6-6-43] 魔王が死んだかどうかを判定する
			if (characters[CHARACTER_MONSTER].hp <= 0)
			{
				// [6-6-44] 画面をクリアする
				system("cls");

				// [6-6-45] エンディングのメッセージを表示する
				printf("　まおうは　ほろび　せかいは\n"
					"めつぼうのききから　すくわれた！\n"
					"\n"
					"　おうは　ふれをだし　ゆうしゃを\n"
					"さがしもとめたが、だれも\n"
					"みたものは　いなかったという…\n"
					"\n"
					"\n"
					"　　　　ＴＨＥ　ＥＮＤ"
				);
				_getch();
			}
			break;
		}
		// [6-6-48] 移動先のマスの種類によって分岐させる
		switch (map[currentMap][playerY][playerX])
		{
		case '.': // 平地
		case '#': // 橋
			// [6-6-51] 敵と遭遇したかどうかを判定する
			if ((currentMap == MAP_FIELD) && (rand() % 16 == 0))
			{
				Battle(MONSTER_SLIME);
			}

			break;
		
		default:
			playerX = lastPlayerX;
			playerY = lastPlayerY;
			break;
		}

		// [6-6-56] プレイヤーが死んだかどうかを判定する
		if (characters[CHARACTER_PLAYER].hp <= 0)
		{
			Init();
			DrawMap();

			printf("＊　「おお　ゆうしゃよ！\n"
				"かみが　そなたを　すくわれた！\n"
				"ゆうしゃに　えいこう　あれ！\n"
			);
			_getch();
		}
	}
}
