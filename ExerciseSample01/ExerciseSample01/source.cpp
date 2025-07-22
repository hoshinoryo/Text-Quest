// [1] �w�b�_�[���C���N���[�h����ꏊ
#include <windows.h>
#include <stdio.h>  // [1-1] �W�����o�̓w�b�_�[���C���N���[�h����
#include <stdlib.h> // [1-2] �W�����C�u�����w�b�_�[���C���N���[�h����
#include <string.h> // [1-3] �����񑀍�w�b�_�[���C���N���[�h����
#include <time.h>   // [1-4] ���ԊǗ��w�b�_�[���C���N���[�h����
#include <conio.h>  // [1-5] �R���\�[�����o�̓w�b�_�[���C���N���[�h����

// [2] �萔���`����ꏊ

constexpr int SPELL_COST = 3;  // [2-1] �����̏���MP���`����
constexpr int MAP_WIDTH  = 16; // [2-2] �}�b�v�̕����`����
constexpr int MAP_HEIGHT = 16;
constexpr int SCREEN_WIDTH  = 16; // [2-4] �X�N���[����ʂ̕����`����
constexpr int SCREEN_HEIGHT = 12;

// [3] �񋓒萔���`����ꏊ

// [3-1] �����X�^�[�̎�ނ��`����
enum Monster
{
	MONSTER_PLAYER, // [3-1-1] �v���C���[
	MONSTER_SLIME,  // [3-1-2] �X���C��
	MONSTER_BOSS,
	MONSTER_MAX     // [3-1-4] �����X�^�[�̎�ނ̐�
};

// [3-2] �L�����N�^�[�̎�ނ��`����
enum Character
{
	CHARACTER_PLAYER,  // [3-2-1]�v���C���[
	CHARACTER_MONSTER, // [3-2-2]�����X�^�[
	CHARACTER_MAX      // [3-2-3]�L�����N�^�[�̎�ނ̐�
};

// [3-3] �R�}���h�̎�ނ��`����
enum Command
{
	COMMAND_FIGHT, // �키
	COMMAND_SPELL, // ����
	COMMAND_RUN,   // ������
	COMMAND_MAX    // �R�}���h�̎�ނ̐�
};

// [3-4] �}�b�v�̎�ނ��`����
enum Map
{
	MAP_FIELD,       // [3-4-1] �t�B�[���h
	MAP_KING_CASTLE, // [3-4-2] ���l�̏�
	MAP_BOSS_CASTLE, // [3-4-2] �����̏�
	MAP_MAX
};

// [4] �\���̂��`����ꏊ

// [4-1] �L�����N�^�[�̍\���̂�錾����
struct CHARACTER
{
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;   // [4-1-5] �U����
	char name[4 * 2 + 1];
	char aa[256]; // [4-1-7] �A�X�L�[�A�[�g
	int command;  // [4-1-8] �R�}���h
	int target;   // [4-1-9] �U���Ώ�
};

// [5] �ϐ���錾����ꏊ

// [5-1] �����X�^�[�̃X�e�[�^�X�̔z���錾����
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

// [5-2] �L�����N�^�[�̔z���錾����
CHARACTER characters[CHARACTER_MAX] = {};

// [5-3] �R�}���h�̖��O��錾����
char commandNames[COMMAND_MAX][4 * 2 + 1]
{
	"��������",
	"�������",
	"�ɂ���"
};

// [5-4] �}�b�v�̒n�`�f�[�^��錾����
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

int currentMap; // [5-5] ���݂̃}�b�v��錾����

int playerX = 6;  // [5-6] �v���C���[��X���W
int playerY = 15; // [5-7] �v���C���[��Y���W

// [6] �֐���錾����ꏊ

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

// [6-2] �퓬�V�[���̉�ʕ`�悷��֐���錾����
void DrawBattleScreen()
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

// [6-3] �R�}���h��I������֐���錾����
void SelectCommand()
{
	// [6-3-1] �v���C���[�̃R�}���h������������
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	// [6-3-2] �R�}���h�����肳���܂Ń��[�v����
	while (1)
	{
		DrawBattleScreen();

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

// [6-4] �퓬�V�[���̊֐���錾����
void Battle(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[_monster];
	// [6-4-2] �v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
	characters[CHARACTER_PLAYER].target  = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	DrawBattleScreen();
	printf("%s���@�����ꂽ�I\n", characters[CHARACTER_MONSTER].name);
	_getch();

	// [6-4-7] �퓬���I������܂Ń��[�v����
	while (1)
	{
		SelectCommand();

		// [6-4-9] �e�L�����N�^�[�𔽕�����
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10] �퓬�V�[���̉�ʂ�`�悷��֐����Ăяo��
			DrawBattleScreen();

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
				DrawBattleScreen();

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
				DrawBattleScreen();
				printf("%s�́@�q�[�����@�ƂȂ����I\n", characters[i].name);
				_getch();

				characters[i].hp = characters[i].maxHp;
				DrawBattleScreen();
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
					DrawBattleScreen();

					printf("%s���@���������I\n", characters[characters[i].target].name);
					break;
				}

				_getch();
				return;
			}
		}
	}
}

// [6-5] �}�b�v��`�悷�鏈�����L�q����֐���錾����
void DrawMap()
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

// �R���\�[���E�B���h�E�T�C�Y�ύX
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
		DrawMap();

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
			Battle(MONSTER_BOSS);

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
				Battle(MONSTER_SLIME);
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
			DrawMap();

			printf("���@�u�����@�䂤�����I\n"
				"���݂��@���Ȃ����@������ꂽ�I\n"
				"�䂤����Ɂ@���������@����I\n"
			);
			_getch();
		}
	}
}
