#include "DxLib.h"
#include <time.h>
#include <math.h>

#define LEFT_LIMIT -220
#define RIGHT_LIMIT 220
#define TOP_LIMIT 240
#define BOTTOM_LIMIT -240

#define PLAYER_SHOT_MAX 30

#define DISP_ENEMY_MAX 5
#define STAGE_ENEMY_MAX 10
#define ENEMY_DATA_MAX 9
#define ENEMY_SHOT_MAX 20
#define DISP_BOSS_MAX 2
#define STAGE_BOSS_MAX 2
#define BOSS_DATA_MAX 10

#define EXP_EFFECT_MAX 20
#define ITEM_MAX 10

#define STAGE_MAX 3

void my_init_back_img(void);
void my_init_bgm(void);
void my_init_bullet_img(void);
void my_init_item_img(void);
void my_init_variable(void);
void my_init_variable2(void);
void my_init_player(void);
void my_init_player2(void);
void my_init_player_shot(void);
void my_init_player_shot2(void);
void my_init_enemy(void);
void my_init_enemy2(void);
void my_init_enemy_shot(void);
void my_init_enemy_shot2(void);
void my_init_boss(void);
void my_init_boss2(void);
void my_init_exp_effect(void);
void my_init_exp_effect2(void);
void my_init_item(void);
void my_init_item2(void);

void my_set_player_shot(int);
void my_set_enemy(void);
void my_set_enemy_shot(double, double, int, int);
void my_set_boss(void);
void my_set_exp_effect(double, double, int);
void my_set_item(double, double, int);

void my_move_player(void);
void my_move_player_shot(void);
void my_move_enemy(void);
void my_move_enemy_shot(void);
void my_move_boss(void);
void my_move_exp_effect(void);
void my_move_item(void);
void my_move_back(void);

int my_pythago_theorem(double, double, double, double, double, double);
void my_collision_detection(void);
void my_collision_player_enemy(void);
void my_collision_player_shot_enemy(void);
void my_collision_player_enemy_shot(void);
void my_collision_player_boss(void);
void my_collision_player_shot_boss(void);
void my_collision_player_item(void);
void my_check_player_power(void);
void my_check_enemy_power(void);
void my_check_boss_power(void);

void my_change_state(void);
void my_to_center(void);

void my_draw_op(void);
void my_draw_ed(void);
void my_draw_stage_num(void);
void my_draw_start(void);
void my_draw_clear(void);
void my_draw_back(void);
void my_draw_back2(void);
void my_draw_player(void);
void my_draw_player_shot(void);
void my_draw_enemy(void);
void my_draw_enemy_shot(void);
void my_draw_enemy_power(void);
void my_draw_boss(void);
void my_draw_boss_power(void);
void my_draw_exp_effect(void);
void my_draw_item(void);
void my_draw_score_board(void);
void my_draw_sounds_title(void);
void my_draw_gameover(void);

void my_play_bgm(void);

void my_stop_bgm(void);

void my_timer(void);

int my_get_key(void);

struct PLAYER {
	double x, y;
	double draw_x, draw_y;
	int speed;
	int shot_type;
	int bomb;
	int power;
	int life;
	double range;
};

struct PLAYER p1;

struct PLAYER_SHOT {
	double x[5];
	double y[5];
	double draw_x[5];
	double draw_y[5];
	int init_flag;
	int move_flag;
	int move_type;
	int flag[5];
	double angle[5];
	int max_bullet;
	int gamecount_point;
	double range;
};

struct PLAYER_SHOT ps1[PLAYER_SHOT_MAX];

struct ENEMY {
	int serial_num;
	int appear_point;
	double first_x, first_y;
	double x, y;
	double draw_x, draw_y;
	double m_x, m_y;
	double a_x, a_y;
	double f_x, f_y;
	int init_flag;
	int move_flag;
	double angle;
	int move_type;
	int shot_type;
	int pattern;
	double var[5];
	int gamecount_point;
	int power;
	double range;
	int item_flag;
};

struct ENEMY enemy[DISP_ENEMY_MAX];

struct ENEMY_SHOT {
	double first_x;
	double first_y;
	double x[10];
	double y[10];
	double draw_x[10];
	double draw_y[10];
	double angle[10];
	int init_flag;
	int move_flag;
	int move_type;
	int max_bullet;
	int gamecount_point[5];
	double range;
	int enemy_num;
};

struct ENEMY_SHOT enemy_shot[ENEMY_SHOT_MAX];

struct BOSS {
	int serial_num;
	int appear_point;
	double first_x, first_y;
	double x, y;
	double draw_x, draw_y;
	double angle;
	int init_flag;
	int move_flag;
	int damage_flag;
	int move_type;
	int shot_type;
	double var[5];
	int gamecount_point[5];
	int power;
	double range;
	int item_flag;
	int end_flag;
};

struct BOSS boss[DISP_BOSS_MAX];

struct EXP_EFFECT {
	double first_x;
	double first_y;
	double x;
	double y;
	double draw_x;
	double draw_y;
	int init_flag;
	int move_flag;
	int move_type;
	int gamecount_point;
};

struct EXP_EFFECT exp_effect[EXP_EFFECT_MAX];

struct ITEM {
	double first_x;
	double first_y;
	double x;
	double y;
	double draw_x;
	double draw_y;
	double m_x, m_y;
	double a_x, a_y;
	double f_x, f_y;
	int init_flag;
	int move_flag;
	int move_type;
	int gamecount_point;
	double range;
};

struct ITEM item[ITEM_MAX];

int ary_enemy_data[STAGE_MAX][STAGE_ENEMY_MAX * ENEMY_DATA_MAX] = {
	{
	0,100,-100,260,0,0,1,10,1,
	1,100,100,260,0,0,1,10,0,
	2,700,0,260,1,1,1,10,1,
	3,1000,0,260,2,1,1,10,0,
	4,1500,100,260,3,2,1,10,1,
	5,1500,-100,260,4,2,1,10,0,
	6,2000,0,260,5,3,1,10,1,
	7,2000,0,260,6,3,1,10,0,
	8,2300,-155,260,7,4,1,10,1,
	9,2700,155,260,8,4,1,10,0
	},
	{
	10,100,-180,260,0,0,10,10,1,
	11,300,-140,260,0,0,10,10,0,
	12,500,-100,260,0,0,10,10,1,
	13,700,-60,260,0,0,10,10,0,
	14,900,-20,260,0,0,10,10,1,
	15,1800,20,260,0,0,10,10,0,
	16,2000,60,260,0,0,10,10,1,
	17,2200,100,260,0,0,10,10,0,
	18,2400,140,260,0,0,10,10,1,
	19,2600,180,260,0,0,10,10,0
	},
	{
	20,100,-180,260,0,0,10,10,1,
	21,300,-140,260,0,0,10,10,0,
	22,500,-100,260,0,0,10,10,1,
	23,700,-60,260,0,0,10,10,0,
	24,900,-20,260,0,0,10,10,1,
	25,1800,20,260,0,0,10,10,0,
	26,2000,60,260,0,0,10,10,1,
	27,2200,100,260,0,0,10,10,0,
	28,2400,140,260,0,0,10,10,1,
	29,2600,180,260,0,0,10,10,0
	}
};

int ary_boss_data[STAGE_MAX][STAGE_BOSS_MAX * BOSS_DATA_MAX] = {
	{
	0,3100,-100,260,1,4,30,10,0,0,
	1,3100,100,260,1,4,30,10,0,1
	},
	{
	2,1100,0,260,1,0,30,10,0,0,
	3,2800,0,260,1,0,30,10,0,1
	},
	{
	4,1100,0,260,1,0,30,10,0,0,
	5,2800,0,260,1,0,30,10,0,1
	}
};

int key[256];

int Bg_1st;
int Bg_2nd;
int Bg_3rd;

int BGM_1st;
int BGM_2nd;
int BGM_3rd;

int img_bullet;
int img_item;

int gamecount;
int gamecount2;
int gamecount3;
int game_state;
int stage_num;
int gameover_flag;
int gameclear_flag;
int score;

int Color_White;
int Color_Maroon;
int Color_Green;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);



	while (ScreenFlip() == 0 && ProcessMessage() == 0
		&& ClearDrawScreen() == 0 && my_get_key() == 0) {

		switch (game_state) {
		case 0:
			my_init_back_img();
			my_init_bgm();
			my_init_bullet_img();
			my_init_item_img();
			game_state = 2;
			break;
		case 2:
			my_init_variable();
			my_init_player();
			my_init_player_shot();
			my_init_enemy();
			my_init_enemy_shot();
			my_init_boss();
			my_init_exp_effect();
			my_init_item();
			game_state = 4;
			break;
		case 4:
			my_draw_op();
			if (key[KEY_INPUT_RETURN] == 1) {
				game_state = 5;
			}
			break;
		case 5:
			my_init_variable2();
			my_init_player2();
			my_init_player_shot2();
			my_init_enemy2();
			my_init_enemy_shot2();
			my_init_boss2();
			my_init_exp_effect2();
			my_init_item2();
			game_state = 10;
			break;
		case 10:
			my_draw_stage_num();
			if (gamecount == 300) {
				gamecount = 0;
				game_state = 15;
			}
			else {
				my_timer();
			}
			break;
		case 15:
			my_to_center();
			my_draw_back();
			my_draw_player();
			my_draw_score_board();
			my_play_bgm();
			if (gamecount2 % 2 == 1) {
				my_draw_start();
			}
			if (gamecount == 200) {
				gamecount = 0;
				gamecount2 = 0;
				game_state = 20;
			}
			else {
				if (gamecount % 10 == 1) {
					gamecount2++;
				}
				p1.y++;
				my_timer();
			}
			break;
		case 20:
			my_set_enemy();
			my_set_boss();

			my_move_player();
			my_move_player_shot();
			my_move_enemy();
			my_move_enemy_shot();
			my_move_boss();
			my_move_exp_effect();
			my_move_item();

			my_collision_detection();
			my_to_center();

			my_draw_back();
			my_draw_player();
			my_draw_player_shot();
			my_draw_enemy();
			my_draw_enemy_shot();
			my_draw_enemy_power();
			my_draw_boss();
			my_draw_boss_power();
			my_draw_exp_effect();
			my_draw_item();
			my_draw_score_board();
			my_draw_sounds_title();

			my_change_state();

			my_timer();

			break;
		case 25:
			my_to_center();
			my_draw_back2();
			my_draw_player();
			my_draw_score_board();
			my_stop_bgm();
			my_move_back();
			if (gamecount2 % 2 == 1) {
				my_draw_clear();
			}
			if (gamecount == 500) {
				if (stage_num == STAGE_MAX) {
					game_state = 30;
				}
				else {
					game_state = 5;
				}
			}
			else {
				if (gamecount % 10 == 1) {
					gamecount2++;
				}
				p1.y++;
				my_timer();
			}
			break;
		case 30:
			my_draw_ed();
			break;
		default:
			break;
		}
	}
	DxLib_End();
	return 0;
}

void my_init_bgm() {
	BGM_1st = LoadSoundMem("sounds_legacy/bgm/U.N.Owen.wav");
	BGM_2nd = LoadSoundMem("sounds_legacy/bgm/Aliens of the Heian period.wav");
	BGM_3rd = LoadSoundMem("sounds_legacy/bgm/Komakusa Blooming Perpetual Snow.wav");
}

void my_init_back_img() {
	Bg_1st = LoadGraph("images_legacy/Bg_1st.bmp");
	Bg_2nd = LoadGraph("images_legacy/Bg_2nd.bmp");
	Bg_3rd = LoadGraph("images_legacy/Bg_3rd.bmp");
}

void my_init_bullet_img() {
	img_bullet = LoadGraph("images_legacy/bullet.png");
}

void my_init_item_img() {
	img_item = LoadGraph("images_legacy/item.png");
}

void my_init_variable() {
	gamecount = 0;
	gamecount2 = 0;
	gamecount3 = 0;
	game_state = 0;
	stage_num = 0;
	gameover_flag = 0;
	gameclear_flag = 0;
	score = 0;
	Color_White = GetColor(255, 255, 255);
	Color_Maroon = GetColor(128, 0, 0);
	Color_Green = GetColor(0, 255, 0);
	SetFontSize(16);
}

void my_init_variable2() {
	gamecount = 0;
	gamecount2 = 0;
	gamecount3 = 0;
	gameover_flag = 0;
	gameclear_flag = 0;
	srand((unsigned)time(NULL));
}

void my_init_player() {
	p1.x = 0;
	p1.y = -200;
	p1.draw_x = 0;
	p1.draw_y = 0;
	p1.speed = 5;
	p1.shot_type = 0;
	p1.bomb = 1;
	p1.power = 1;
	p1.life = 3;
	p1.range = 10;
}

void my_init_player2() {
	p1.x = 0;
	p1.y = -300;
	p1.bomb = 1;
	p1.power = 1;
}

void my_init_player_shot() {
	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		ps1[i].init_flag = 0;
		ps1[i].move_flag = 0;
		ps1[i].move_type = 0;
		ps1[i].max_bullet = 0;
		ps1[i].gamecount_point = 0;
		ps1[i].range = 20;
		for (int j = 0;j < 5;j++) {
			ps1[i].x[j] = 0;
			ps1[i].y[j] = 0;
			ps1[i].draw_x[j] = 0;
			ps1[i].draw_y[j] = 0;
			ps1[i].flag[j] = 0;
			ps1[i].angle[j] = 0;
		}
	}
}

void my_init_player_shot2() {
	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		ps1[i].init_flag = 0;
		ps1[i].move_flag = 0;
	}
}

void my_init_enemy() {
	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		enemy[i].serial_num = 0;
		enemy[i].appear_point = 0;
		enemy[i].first_x = 0;
		enemy[i].first_y = 0;
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].draw_x = 0;
		enemy[i].draw_y = 0;
		enemy[i].m_x = 0;
		enemy[i].m_y = 0;
		enemy[i].a_x = 0;
		enemy[i].a_y = 0;
		enemy[i].f_x = 0;
		enemy[i].f_y = 0;
		enemy[i].init_flag = 0;
		enemy[i].move_flag = 0;
		enemy[i].angle = 0;
		enemy[i].move_type = 0;
		enemy[i].shot_type = 0;
		enemy[i].pattern = 0;
		enemy[i].gamecount_point = 0;
		enemy[i].power = 0;
		enemy[i].range = 0;
		enemy[i].item_flag = 0;
		for (int j = 0;j < 5;j++) {
			enemy[i].var[j] = 0;
		}
	}
}

void my_init_enemy2() {
	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		enemy[i].init_flag = 0;
		enemy[i].move_flag = 0;
	}
}

void my_init_enemy_shot() {
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		enemy_shot[i].first_x = 0;
		enemy_shot[i].first_y = 0;
		enemy_shot[i].init_flag = 0;
		enemy_shot[i].move_flag = 0;
		enemy_shot[i].move_type = 0;
		enemy_shot[i].max_bullet = 0;
		enemy_shot[i].range = 10;
		enemy_shot[i].enemy_num = 0;
		for (int j = 0;j < 10;j++) {
			enemy_shot[i].x[j] = 0;
			enemy_shot[i].y[j] = 0;
			enemy_shot[i].draw_x[j] = 0;
			enemy_shot[i].draw_y[j] = 0;
			enemy_shot[i].angle[j] = 0;
		}
		for (int j = 0;j < 5;j++) {
			enemy_shot[i].gamecount_point[j] = 0;
		}
	}
}

void my_init_enemy_shot2() {
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		enemy_shot[i].init_flag = 0;
		enemy_shot[i].move_flag = 0;
	}
}

void my_init_boss() {
	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		boss[i].serial_num = 0;
		boss[i].appear_point = 0;
		boss[i].first_x = 0;
		boss[i].first_y = 0;
		boss[i].x = 0;
		boss[i].y = 0;
		boss[i].draw_x = 0;
		boss[i].draw_y = 0;
		boss[i].angle = 0;
		boss[i].init_flag = 0;
		boss[i].move_flag = 0;
		boss[i].damage_flag = 0;
		boss[i].move_type = 0;
		boss[i].shot_type = 0;
		boss[i].power = 0;
		boss[i].range = 0;
		boss[i].item_flag = 0;
		boss[i].end_flag = 0;
		for (int j = 0;j < 5;j++) {
			boss[i].var[j] = 0;
			boss[i].gamecount_point[j] = 0;
		}
	}
}

void my_init_boss2() {
	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		boss[i].init_flag = 0;
		boss[i].move_flag = 0;
	}
}

void my_init_exp_effect() {
	for (int i = 0; i < EXP_EFFECT_MAX; i++) {
		exp_effect[i].first_x = 0;
		exp_effect[i].first_y = 0;
		exp_effect[i].x = 0;
		exp_effect[i].y = 0;
		exp_effect[i].draw_x = 0;
		exp_effect[i].draw_y = 0;
		exp_effect[i].init_flag = 0;
		exp_effect[i].move_flag = 0;
		exp_effect[i].move_type = 0;
		exp_effect[i].gamecount_point = 0;
	}
}

void my_init_exp_effect2() {
	for (int i = 0; i < EXP_EFFECT_MAX; i++) {
		exp_effect[i].init_flag = 0;
		exp_effect[i].move_flag = 0;
	}
}

void my_init_item() {
	for (int i = 0; i < ITEM_MAX; i++) {
		item[i].first_x = 0;
		item[i].first_y = 0;
		item[i].x = 0;
		item[i].y = 0;
		item[i].draw_x = 0;
		item[i].draw_y = 0;
		item[i].m_x = 0;
		item[i].m_y = 0;
		item[i].a_x = 0;
		item[i].a_y = 0;
		item[i].f_x = 0;
		item[i].f_y = 0;
		item[i].init_flag = 0;
		item[i].move_flag = 0;
		item[i].move_type = 0;
		item[i].range = 10;
		item[i].gamecount_point = 0;
	}
}

void my_init_item2() {
	for (int i = 0; i < ITEM_MAX; i++) {
		item[i].init_flag = 0;
		item[i].move_flag = 0;
	}
}


void my_move_player() {
	if (key[KEY_INPUT_LSHIFT] >= 1) {
		if (key[KEY_INPUT_RIGHT] >= 1 && p1.x < (RIGHT_LIMIT - 20)) {
			p1.x += (p1.speed * 2 / 3);
		}
		if (key[KEY_INPUT_DOWN] >= 1 && p1.y > (BOTTOM_LIMIT + 20)) {
			p1.y -= (p1.speed * 2 / 3);
		}
		if (key[KEY_INPUT_LEFT] >= 1 && p1.x > LEFT_LIMIT) {
			p1.x -= (p1.speed * 2 / 3);
		}
		if (key[KEY_INPUT_UP] >= 1 && p1.y < TOP_LIMIT) {
			p1.y += (p1.speed * 2 / 3);
		}
	}
	else {
		if (key[KEY_INPUT_RIGHT] >= 1 && p1.x < (RIGHT_LIMIT - 20)) {
			p1.x += (p1.speed);
		}
		if (key[KEY_INPUT_DOWN] >= 1 && p1.y > (BOTTOM_LIMIT + 20)) {
			p1.y -= (p1.speed);
		}
		if (key[KEY_INPUT_LEFT] >= 1 && p1.x > LEFT_LIMIT) {
			p1.x -= (p1.speed);
		}
		if (key[KEY_INPUT_UP] >= 1 && p1.y < TOP_LIMIT) {
			p1.y += (p1.speed);
		}
	}
	if (key[KEY_INPUT_Z] % 7 == 1) {
		my_set_player_shot(p1.shot_type);
	}
}

void my_set_player_shot(int shot_type) {
	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		if (ps1[i].move_flag == 0) {
			ps1[i].move_type = shot_type;
			ps1[i].move_flag = 1;
			break;
		}
	}
}

void my_move_player_shot() {
	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		if (ps1[i].move_flag == 1) {
			switch (ps1[i].move_type) {
			case 0:
				if (ps1[i].init_flag == 0) {
					ps1[i].max_bullet = 1;
					for (int j = 0;j < ps1[i].max_bullet;j++) {
						ps1[i].x[j] = p1.x;
						ps1[i].y[j] = p1.y;
						ps1[i].flag[j] = 1;
					}
					ps1[i].gamecount_point = gamecount;
					ps1[i].init_flag = 1;
				}
				else {
					if (gamecount < ps1[i].gamecount_point + 100) {
						for (int j = 0;j < ps1[i].max_bullet;j++) {
							ps1[i].y[j] += 8;
						}
					}
					else {
						ps1[i].move_flag = 0;
						ps1[i].init_flag = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void my_set_enemy() {
	for (int i = 0; i < STAGE_ENEMY_MAX; i++) {
		if (ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 1] == gamecount && gamecount > 0) {
			for (int j = 0; j < DISP_ENEMY_MAX; j++) {
				if (enemy[j].move_flag == 0) {
					enemy[j].move_flag = 1;
					enemy[j].serial_num = ary_enemy_data[stage_num][i * ENEMY_DATA_MAX];
					enemy[j].appear_point = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 1];
					enemy[j].first_x = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 2];
					enemy[j].first_y = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 3];
					enemy[j].move_type = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 4];
					enemy[j].shot_type = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 5];
					enemy[j].power = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 6];
					enemy[j].range = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 7];
					enemy[j].item_flag = ary_enemy_data[stage_num][(i * ENEMY_DATA_MAX) + 8];
					break;
				}
			}
		}
	}
}

void my_move_enemy() {
	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		if (enemy[i].move_flag == 1) {
			switch (enemy[i].move_type) {
			case 0:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = enemy[i].first_x;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 220) {
							enemy[i].y--;
						}
						if (gamecount == enemy[i].gamecount_point + 240) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 260) {
							enemy[i].y++;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 1:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 0;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 600) {
						if (gamecount < enemy[i].gamecount_point + 260) {
							enemy[i].y--;
						}
						if (gamecount == enemy[i].gamecount_point + 280) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 300) {
							enemy[i].x++;
							enemy[i].y = 1 * enemy[i].x;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 2:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 0;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 600) {
						if (gamecount < enemy[i].gamecount_point + 260) {
							enemy[i].y--;
						}
						if (gamecount == enemy[i].gamecount_point + 280) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 300) {
							enemy[i].x--;
							enemy[i].y = -1 * enemy[i].x;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 3:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 100;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 260) {
							enemy[i].y--;
						}
						if (gamecount == enemy[i].gamecount_point + 270) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 280) {
							enemy[i].x++;
							enemy[i].y = (2 * enemy[i].x) - 200;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 4:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = -100;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 260) {
							enemy[i].y--;
						}
						if (gamecount == enemy[i].gamecount_point + 270) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 280) {
							enemy[i].x--;
							enemy[i].y = (-2 * enemy[i].x) - 200;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 5:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 0;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 50) {
							enemy[i].x = enemy[i].x + 2;
							enemy[i].y = 6000 / enemy[i].x;
						}
						if (gamecount == enemy[i].gamecount_point + 60) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 110) {
							enemy[i].x = enemy[i].x + 2;
							enemy[i].y = 6000 / enemy[i].x;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 6:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 0;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 50) {
							enemy[i].x = enemy[i].x - 2;
							enemy[i].y = -6000 / enemy[i].x;
						}
						if (gamecount == enemy[i].gamecount_point + 60) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 110) {
							enemy[i].x = enemy[i].x - 2;
							enemy[i].y = -6000 / enemy[i].x;
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 7:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = -155;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 90) {
							enemy[i].x++;
							enemy[i].y = 0.01 * (enemy[i].x * enemy[i].x);
						}
						if (gamecount == enemy[i].gamecount_point + 100) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 200) {
							enemy[i].x++;
							enemy[i].y = 0.01 * (enemy[i].x * enemy[i].x);
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			case 8:
				if (enemy[i].init_flag == 0) {
					enemy[i].x = 155;
					enemy[i].y = 260;
					enemy[i].gamecount_point = gamecount;
					enemy[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy[i].gamecount_point + 500) {
						if (gamecount < enemy[i].gamecount_point + 90) {
							enemy[i].x--;
							enemy[i].y = 0.01 * (enemy[i].x * enemy[i].x);
						}
						if (gamecount == enemy[i].gamecount_point + 100) {
							my_set_enemy_shot(enemy[i].x, enemy[i].y, enemy[i].shot_type, i);
						}
						if (gamecount > enemy[i].gamecount_point + 200) {
							enemy[i].x--;
							enemy[i].y = 0.01 * (enemy[i].x * enemy[i].x);
						}
					}
					else {
						enemy[i].move_flag = 0;
						enemy[i].init_flag = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}


void my_set_enemy_shot(double x, double y, int shot_type, int enemy_num) {
	for (int i = 0;i < ENEMY_SHOT_MAX;i++) {
		if (enemy_shot[i].move_flag == 0) {
			enemy_shot[i].move_flag = 1;
			enemy_shot[i].first_x = x;
			enemy_shot[i].first_y = y;
			enemy_shot[i].move_type = shot_type;
			enemy_shot[i].enemy_num = enemy_num;
			break;
		}
	}
}

void my_move_enemy_shot() {
	for (int i = 0;i < ENEMY_SHOT_MAX;i++) {
		if (enemy_shot[i].move_flag == 1) {
			switch (enemy_shot[i].move_type) {
			case 0:
				if (enemy_shot[i].init_flag == 0) {
					enemy_shot[i].x[0] = enemy_shot[i].first_x;
					enemy_shot[i].y[0] = enemy_shot[i].first_y;
					enemy_shot[i].max_bullet = 1;
					enemy_shot[i].gamecount_point[0] = gamecount;
					enemy_shot[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy_shot[i].gamecount_point[0] + 300) {
						enemy_shot[i].y[0] -= 2;
					}
					else {
						enemy_shot[i].move_flag = 0;
						enemy_shot[i].init_flag = 0;
					}
				}
				break;
			case 1:
				if (enemy_shot[i].init_flag == 0) {
					enemy_shot[i].gamecount_point[0] = gamecount;
					enemy_shot[i].gamecount_point[1] = gamecount;
					enemy_shot[i].max_bullet = 1;
					for (int j = 0; j < 5; j++) {
						enemy_shot[i].x[j] = enemy_shot[i].first_x;
						enemy_shot[i].y[j] = enemy_shot[i].first_y;
					}
					enemy_shot[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy_shot[i].gamecount_point[0] + 500) {
						for (int j = 0; j < enemy_shot[i].max_bullet; j++) {
							enemy_shot[i].y[j] = enemy_shot[i].y[j] - 2;
						}
						if (enemy_shot[i].max_bullet < 5) {
							if (gamecount == enemy_shot[i].gamecount_point[1] + 5) {
								enemy_shot[i].max_bullet++;
								enemy_shot[i].gamecount_point[1] += 5;
							}
						}
					}
					else {
						enemy_shot[i].move_flag = 0;
						enemy_shot[i].init_flag = 0;
					}
				}
				break;
			case 2:
				if (enemy_shot[i].init_flag == 0) {
					enemy_shot[i].gamecount_point[0] = gamecount;
					enemy_shot[i].max_bullet = 1;
					enemy_shot[i].x[0] = enemy_shot[i].first_x;
					enemy_shot[i].y[0] = enemy_shot[i].first_y;
					enemy_shot[i].angle[0] = atan2(p1.y - enemy_shot[i].first_y, p1.x - enemy_shot[i].first_x);
					enemy_shot[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy_shot[i].gamecount_point[0] + 400) {
						enemy_shot[i].x[0] += cos(enemy_shot[i].angle[0]) * 2;
						enemy_shot[i].y[0] += sin(enemy_shot[i].angle[0]) * 2;
					}
					else {
						enemy_shot[i].move_flag = 0;
						enemy_shot[i].init_flag = 0;
					}
				}
				break;
			case 3:
				if (enemy_shot[i].init_flag == 0) {
					enemy_shot[i].gamecount_point[0] = gamecount;
					enemy_shot[i].gamecount_point[1] = gamecount;
					enemy_shot[i].max_bullet = 1;
					for (int j = 0; j < 10; j++) {
						enemy_shot[i].x[j] = enemy_shot[i].first_x;
						enemy_shot[i].y[j] = enemy_shot[i].first_y;
					}
					enemy_shot[i].angle[0] = atan2(p1.y - enemy_shot[i].first_y, p1.x - enemy_shot[i].first_x);
					enemy_shot[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy_shot[i].gamecount_point[0] + 500) {
						for (int j = 0; j < enemy_shot[i].max_bullet; j++) {
							enemy_shot[i].x[j] += cos(enemy_shot[i].angle[0]) * 4;
							enemy_shot[i].y[j] += sin(enemy_shot[i].angle[0]) * 4;
						}
						if (enemy_shot[i].max_bullet < 10) {
							if (gamecount == enemy_shot[i].gamecount_point[1] + 5
								&& enemy[enemy_shot[i].enemy_num].move_flag == 1) {
								enemy_shot[i].max_bullet++;
								enemy_shot[i].gamecount_point[1] += 5;
							}
						}
					}
					else {
						enemy_shot[i].move_flag = 0;
						enemy_shot[i].init_flag = 0;
					}
				}
				break;
			case 4:
				if (enemy_shot[i].init_flag == 0) {
					enemy_shot[i].gamecount_point[0] = gamecount;
					enemy_shot[i].gamecount_point[1] = gamecount;
					enemy_shot[i].max_bullet = 1;
					for (int j = 0; j < 10; j++) {
						enemy_shot[i].x[j] = enemy_shot[i].first_x;
						enemy_shot[i].y[j] = enemy_shot[i].first_y;
					}
					enemy_shot[i].angle[0] = atan2(p1.y - enemy_shot[i].first_y, p1.x - enemy_shot[i].first_x);
					enemy_shot[i].init_flag = 1;
				}
				else {
					if (gamecount < enemy_shot[i].gamecount_point[0] + 500) {
						for (int j = 0; j < enemy_shot[i].max_bullet; j++) {
							enemy_shot[i].x[j] += cos(enemy_shot[i].angle[j]) * 4;
							enemy_shot[i].y[j] += sin(enemy_shot[i].angle[j]) * 4;
						}
						if (enemy_shot[i].max_bullet < 10) {
							if (gamecount == enemy_shot[i].gamecount_point[1] + 10
								&& enemy[enemy_shot[i].enemy_num].move_flag == 1) {
								enemy_shot[i].angle[enemy_shot[i].max_bullet] = atan2(p1.y - enemy_shot[i].first_y, p1.x - enemy_shot[i].first_x);
								enemy_shot[i].max_bullet++;
								enemy_shot[i].gamecount_point[1] += 10;
							}
						}
					}
					else {
						enemy_shot[i].move_flag = 0;
						enemy_shot[i].init_flag = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void my_set_boss() {
	for (int i = 0; i < STAGE_BOSS_MAX; i++) {
		if (ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 1] == gamecount && gamecount > 0) {
			for (int j = 0; j < DISP_BOSS_MAX; j++) {
				if (boss[j].move_flag == 0) {
					boss[j].move_flag = 1;
					boss[j].serial_num = ary_boss_data[stage_num][i * BOSS_DATA_MAX];
					boss[j].appear_point = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 1];
					boss[j].first_x = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 2];
					boss[j].first_y = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 3];
					boss[j].move_type = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 4];
					boss[j].shot_type = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 5];
					boss[j].power = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 6];
					boss[j].range = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 7];
					boss[j].item_flag = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 8];
					boss[j].end_flag = ary_boss_data[stage_num][(i * BOSS_DATA_MAX) + 9];
					break;
				}
			}
		}
	}
}

void my_move_boss() {
	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		if (boss[i].move_flag == 1) {
			switch (boss[i].move_type) {
			case 0:
				if (boss[i].init_flag == 0) {
					boss[i].x = boss[i].first_x;
					boss[i].y = 260;
					boss[i].gamecount_point[0] = gamecount;
					boss[i].init_flag = 1;
				}
				else {
					if (gamecount < boss[i].gamecount_point[0] + 1000) {
						if (boss[i].power > 0) {
							if (gamecount < boss[i].gamecount_point[0] + 220) {
								boss[i].y--;
							}
							if (gamecount == boss[i].gamecount_point[0] + 220) {
								boss[i].damage_flag = 1;
							}
							if (gamecount > boss[i].gamecount_point[0] + 240
								&& gamecount < boss[i].gamecount_point[0] + 520) {
								if (gamecount % 100 == 1) {
									my_set_enemy_shot(boss[i].x, boss[i].y, boss[i].shot_type, i);
								}
							}
							if (gamecount > boss[i].gamecount_point[0] + 520) {
								boss[i].y++;
							}
						}
					}
					else {
						boss[i].move_flag = 0;
						boss[i].init_flag = 0;
					}
				}
				break;
			case 1:
				if (boss[i].init_flag == 0) {
					boss[i].x = boss[i].first_x;
					boss[i].y = 260;
					boss[i].gamecount_point[0] = gamecount;
					boss[i].init_flag = 1;
				}
				else {
					if (boss[i].power > 0) {
						if (gamecount < boss[i].gamecount_point[0] + 220) {
							boss[i].y--;
						}
						if (gamecount == boss[i].gamecount_point[0] + 220) {
							boss[i].damage_flag = 1;
						}
						if (gamecount > boss[i].gamecount_point[0] + 240) {
							if (gamecount % 100 == 1) {
								my_set_enemy_shot(boss[i].x, boss[i].y, boss[i].shot_type, i);
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void my_set_exp_effect(double x, double y, int exp_type) {
	for (int i = 0;i < EXP_EFFECT_MAX;i++) {
		if (exp_effect[i].move_flag == 0) {
			exp_effect[i].move_flag = 1;
			exp_effect[i].first_x = x;
			exp_effect[i].first_y = y;
			exp_effect[i].move_type = exp_type;
			break;
		}
	}
}

void my_move_exp_effect() {
	for (int i = 0;i < EXP_EFFECT_MAX;i++) {
		if (exp_effect[i].move_flag == 1) {
			switch (exp_effect[i].move_type) {
			case 0:
				if (exp_effect[i].init_flag == 0) {
					exp_effect[i].x = exp_effect[i].first_x;
					exp_effect[i].y = exp_effect[i].first_y;
					exp_effect[i].gamecount_point = gamecount;
					exp_effect[i].init_flag = 1;
				}
				else {
					if (gamecount < exp_effect[i].gamecount_point + 2) {

					}
					else {
						exp_effect[i].move_flag = 0;
						exp_effect[i].init_flag = 0;
					}
				}
				break;
			case 1:
				if (exp_effect[i].init_flag == 0) {
					exp_effect[i].x = exp_effect[i].first_x;
					exp_effect[i].y = exp_effect[i].first_y;
					exp_effect[i].gamecount_point = gamecount;
					exp_effect[i].init_flag = 1;
				}
				else {
					if (gamecount < exp_effect[i].gamecount_point + 30) {

					}
					else {
						exp_effect[i].move_flag = 0;
						exp_effect[i].init_flag = 0;
					}
				}
				break;
			case 2:
				if (exp_effect[i].init_flag == 0) {
					exp_effect[i].x = exp_effect[i].first_x;
					exp_effect[i].y = exp_effect[i].first_y;
					exp_effect[i].gamecount_point = gamecount;
					exp_effect[i].init_flag = 1;
				}
				else {
					if (gamecount < exp_effect[i].gamecount_point + 200) {
						if (gamecount % 10 == 1) {
							int ran = (rand() % 5);
							int ran2 = (rand() % 5);
							int ary[5] = { -20,-10,0,10,20 };
							exp_effect[i].x = exp_effect[i].first_x + ary[ran];
							exp_effect[i].y = exp_effect[i].first_y + ary[ran2];
						}
					}
					else {
						exp_effect[i].move_flag = 0;
						exp_effect[i].init_flag = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void my_set_item(double x, double y, int item_type) {
	for (int i = 0;i < ITEM_MAX;i++) {
		if (item[i].move_flag == 0) {
			item[i].move_flag = 1;
			item[i].first_x = x;
			item[i].first_y = y;
			item[i].move_type = item_type;
			break;
		}
	}
}

void my_move_item() {
	for (int i = 0;i < ITEM_MAX;i++) {
		if (item[i].move_flag == 1) {
			switch (item[i].move_type) {
			case 0:
				if (item[i].init_flag == 0) {
					item[i].x = item[i].first_x;
					item[i].y = item[i].first_y;
					item[i].gamecount_point = gamecount;
					item[i].init_flag = 1;
				}
				else {
					if (gamecount < item[i].gamecount_point + 240) {
						item[i].y -= 2;
					}
					else {
						item[i].move_flag = 0;
						item[i].init_flag = 0;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void my_move_back() {
	switch (stage_num) {
	case 1:
		GraphFilter(Bg_1st, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0 - (gamecount / 32));
		break;
	case 2:
		GraphFilter(Bg_2nd, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0 - (gamecount / 32));
		break;
	case 3:
		GraphFilter(Bg_3rd, DX_GRAPH_FILTER_HSB, 0, 0, 0, 0 - (gamecount / 32));
		break;
	}
}

int my_pythago_theorem(double x, double x2, double y, double y2, double range, double range2) {
	double x3 = x - x2;
	double y3 = y - y2;
	double range3 = range + range2;
	if (x3 * x3 + y3 * y3 < range3 * range3) {
		return 1;
	}
	else {
		return 0;
	}
}

void my_collision_detection() {
	my_collision_player_enemy();
	my_collision_player_shot_enemy();
	my_collision_player_enemy_shot();
	my_collision_player_boss();
	my_collision_player_shot_boss();
	my_collision_player_item();
	my_check_player_power();
	my_check_enemy_power();
	my_check_boss_power();
}

void my_collision_player_enemy() {
	for (int i = 0;i < DISP_ENEMY_MAX;i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1 && p1.power > 0) {
			if (my_pythago_theorem(p1.x, enemy[i].x,
				p1.y, enemy[i].y, p1.range, enemy[i].range)) {
				p1.power--;
				enemy[i].power--;
			}
		}
	}
}

void my_collision_player_shot_enemy() {
	for (int i = 0;i < DISP_ENEMY_MAX;i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1) {
			for (int j = 0;j < PLAYER_SHOT_MAX;j++) {
				if (ps1[j].move_flag == 1 && ps1[j].init_flag == 1) {
					for (int k = 0;k < ps1[j].max_bullet;k++) {
						if (ps1[j].flag[k] == 1 && ps1[j].x[k] > LEFT_LIMIT && ps1[j].x[k] < RIGHT_LIMIT &&
							ps1[j].y[k] > BOTTOM_LIMIT && ps1[j].y[k] < TOP_LIMIT) {
							if (my_pythago_theorem(enemy[i].x, ps1[j].x[k],
								enemy[i].y, ps1[j].y[k], enemy[i].range, ps1[j].range)) {
								enemy[i].power--;
								ps1[j].flag[k] = 0;
							}
						}
					}
				}
			}
		}
	}
}

void my_collision_player_enemy_shot() {
	for (int i = 0;i < ENEMY_SHOT_MAX;i++) {
		if (enemy_shot[i].move_flag == 1 && enemy_shot[i].init_flag == 1 && p1.power > 0) {
			for (int j = 0;j < enemy_shot[i].max_bullet;j++) {
				if (my_pythago_theorem(p1.x, enemy_shot[i].x[j],
					p1.y, enemy_shot[i].y[j], p1.range, enemy_shot[i].range)) {
					p1.power--;
				}
			}
		}
	}
}

void my_collision_player_boss() {
	for (int i = 0;i < DISP_BOSS_MAX;i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1 && p1.power > 0) {
			if (my_pythago_theorem(p1.x, boss[i].x,
				p1.y, boss[i].y, p1.range, boss[i].range)) {
				p1.power--;
				if (boss[i].damage_flag == 1) {
					boss[i].power--;
				}
				my_set_exp_effect(boss[i].x, boss[i].y, 0);
			}
		}
	}
}

void my_collision_player_shot_boss() {
	for (int i = 0;i < DISP_BOSS_MAX;i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1) {
			for (int j = 0;j < PLAYER_SHOT_MAX;j++) {
				if (ps1[j].move_flag == 1 && ps1[j].init_flag == 1) {
					for (int k = 0;k < ps1[j].max_bullet;k++) {
						if (ps1[j].flag[k] == 1 && ps1[j].x[k] > LEFT_LIMIT && ps1[j].x[k] < RIGHT_LIMIT &&
							ps1[j].y[k] > BOTTOM_LIMIT && ps1[j].y[k] < TOP_LIMIT) {
							if (my_pythago_theorem(boss[i].x, ps1[j].x[k],
								boss[i].y, ps1[j].y[k], boss[i].range, ps1[j].range)) {
								if (boss[i].damage_flag == 1) {
									boss[i].power--;
								}
								ps1[j].flag[k] = 0;
								my_set_exp_effect(boss[i].x, boss[i].y, 0);
							}
						}
					}
				}
			}
		}
	}
}

void my_collision_player_item() {
	for (int i = 0;i < ITEM_MAX;i++) {
		if (item[i].move_flag == 1 && item[i].init_flag == 1 && p1.power > 0) {
			if (my_pythago_theorem(p1.x, item[i].x,
				p1.y, item[i].y, p1.range, item[i].range)) {
				item[i].move_flag = 0;
				item[i].init_flag = 0;
			}
		}
	}
}

void my_check_player_power() {
	if (p1.power <= 0 && gameover_flag == 0) {
		my_set_exp_effect(p1.x, p1.y, 1);
		gameover_flag = 1;
	}
}

void my_check_enemy_power() {
	for (int i = 0;i < DISP_ENEMY_MAX;i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1) {
			if (enemy[i].power <= 0) {
				enemy[i].move_flag = 0;
				enemy[i].init_flag = 0;
				my_set_exp_effect(enemy[i].x, enemy[i].y, 1);
				if (enemy[i].item_flag == 1) {
					my_set_item(enemy[i].x, enemy[i].y, 0);
				}
				score += 10;
			}
		}
	}
}

void my_check_boss_power() {
	for (int i = 0;i < DISP_BOSS_MAX;i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1) {
			if (boss[i].power <= 0) {
				gamecount2++;
				if (gamecount2 == 1) {
					my_set_exp_effect(boss[i].x, boss[i].y, 2);
				}
				else if (gamecount2 == 200) {
					boss[i].move_flag = 0;
					boss[i].init_flag = 0;
					if (boss[i].end_flag == 1) {
						gameclear_flag = 1;
					}
					gamecount2 = 0;
					score += 1000;
				}
			}
		}
	}
}

void my_change_state() {
	if (gameover_flag == 1) {
		gamecount3++;
		if (gamecount3 == 200) {
			if (p1.life == 1) {
				game_state = 2;
			}
			else {
				p1.life--;
				p1.shot_type = 0;
				game_state = 5;
			}
		}
	}
	else if (gameclear_flag == 1) {
		stage_num++;
		gamecount = 0;
		game_state = 25;
	}
}

void my_to_center() {
	p1.draw_x = p1.x + 220;
	p1.draw_y = ((-1) * p1.y) + 240;

	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		if (ps1[i].move_flag == 1 && ps1[i].init_flag == 1) {
			for (int j = 0;j < ps1[i].max_bullet;j++) {
				ps1[i].draw_x[j] = ps1[i].x[j] + 220;
				ps1[i].draw_y[j] = ((-1) * ps1[i].y[j]) + 240;
			}
		}
	}

	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1) {
			enemy[i].draw_x = enemy[i].x + 220;
			enemy[i].draw_y = ((-1) * enemy[i].y) + 240;
		}
	}

	for (int i = 0;i < ENEMY_SHOT_MAX;i++) {
		if (enemy_shot[i].move_flag == 1 && enemy_shot[i].init_flag == 1) {
			for (int j = 0;j < enemy_shot[i].max_bullet;j++) {
				enemy_shot[i].draw_x[j] = enemy_shot[i].x[j] + 220;
				enemy_shot[i].draw_y[j] = ((-1) * enemy_shot[i].y[j]) + 240;
			}
		}
	}

	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1) {
			boss[i].draw_x = boss[i].x + 220;
			boss[i].draw_y = ((-1) * boss[i].y) + 240;
		}
	}

	for (int i = 0;i < EXP_EFFECT_MAX;i++) {
		if (exp_effect[i].move_flag == 1 && exp_effect[i].init_flag == 1) {
			exp_effect[i].draw_x = exp_effect[i].x + 220;
			exp_effect[i].draw_y = ((-1) * exp_effect[i].y) + 240;
		}
	}

	for (int i = 0;i < ITEM_MAX;i++) {
		if (item[i].move_flag == 1 && item[i].init_flag == 1) {
			item[i].draw_x = item[i].x + 220;
			item[i].draw_y = ((-1) * item[i].y) + 240;
		}
	}
}

void my_draw_op() {
	DrawFormatString(320 - (GetDrawFormatStringWidth("ƒI[ƒvƒjƒ“ƒO@‚d‚m‚s‚d‚q‚ÅƒXƒ^[ƒg") / 2), 240, Color_White, "ƒI[ƒvƒjƒ“ƒO@‚d‚m‚s‚d‚q‚ÅƒXƒ^[ƒg");
}

void my_draw_ed() {
	DrawFormatString(320 - (GetDrawFormatStringWidth("ƒGƒ“ƒfƒBƒ“ƒO") / 2), 240, Color_White, "ƒGƒ“ƒfƒBƒ“ƒO");
}

void my_draw_stage_num() {
	DrawFormatString(320 - (GetDrawFormatStringWidth("‚r‚s‚`‚f‚d@%d@‚r‚s‚`‚q‚s", stage_num + 1) / 2), 220, Color_White, "‚r‚s‚`‚f‚d@%d@‚r‚s‚`‚q‚s", stage_num + 1);
	DrawFormatString(320 - (GetDrawFormatStringWidth("‚o‚k‚`‚x‚d‚q@~@%d", p1.life) / 2), 240, Color_White, "‚o‚k‚`‚x‚d‚q@~@%d", p1.life);
}

void my_draw_start() {
	DrawFormatString(220 - (GetDrawFormatStringWidth("‚r‚s‚`‚f‚d@‚r‚s‚`‚q‚s") / 2), 160, Color_White, "‚r‚s‚`‚f‚d@‚r‚s‚`‚q‚s");
}

void my_draw_clear() {
	DrawFormatString(220 - (GetDrawFormatStringWidth("‚r‚s‚`‚f‚d@‚b‚k‚d‚`‚q") / 2), 160, Color_White, "‚r‚s‚`‚f‚d@‚b‚k‚d‚`‚q");
	DrawFormatString(220 - (GetDrawFormatStringWidth("‚s‚n‚s‚`‚k@‚r‚b‚n‚q‚d") / 2), 180, Color_White, "‚s‚n‚s‚`‚k@‚r‚b‚n‚q‚d");
	DrawFormatString(220 - (GetDrawFormatStringWidth("%d", score) / 2), 200, Color_White, "%d", score);
}

void my_draw_gameover() {
	if (gameover_flag == 1 && p1.life == 1) {
		DrawFormatString(220 - (GetDrawFormatStringWidth("‚f‚`‚l‚d@‚n‚u‚d‚q") / 2), 220, Color_White, "‚f‚`‚l‚d@‚n‚u‚d‚q");
	}
}


void my_draw_back() {
	if (stage_num == 0)
		DrawGraph(0, 0, Bg_1st, TRUE);
	else if (stage_num == 1)
		DrawGraph(0, 0, Bg_2nd, TRUE);
	else
		DrawGraph(0, 0, Bg_3rd, TRUE);
	DrawLine(0, 240, 440, 240, Color_White);
	DrawLine(220, 0, 220, 480, Color_White);
	DrawFormatString(220, 240, Color_White, "(0,0)");
}

void my_draw_back2() {
	if (stage_num == 1)
		DrawGraph(0, 0, Bg_1st, TRUE);
	else if (stage_num == 2)
		DrawGraph(0, 0, Bg_2nd, TRUE);
	else
		DrawGraph(0, 0, Bg_3rd, TRUE);
	DrawLine(0, 240, 440, 240, Color_White);
	DrawLine(220, 0, 220, 480, Color_White);
	DrawFormatString(220, 240, Color_White, "(0,0)");
}




void my_draw_player() {
	DrawFormatString(p1.draw_x, p1.draw_y, Color_White, "m9(‚^ê^¶)");
}

void my_draw_player_shot() {
	for (int i = 0;i < PLAYER_SHOT_MAX;i++) {
		if (ps1[i].move_flag == 1 && ps1[i].init_flag == 1) {
			for (int j = 0;j < ps1[i].max_bullet;j++) {
				if (ps1[i].flag[j] == 1) {
					DrawFormatString(ps1[i].draw_x[j], ps1[i].draw_y[j], Color_White, "ÚÎß°Ä");
				}
			}
		}
	}
}

void my_draw_enemy() {
	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1) {
			DrawFormatString(enemy[i].draw_x, enemy[i].draw_y, Color_Maroon, "‹³ˆõ[%d]", enemy[i].serial_num);
		}
	}
}

void my_draw_enemy_shot() {
	for (int i = 0;i < ENEMY_SHOT_MAX;i++) {
		if (enemy_shot[i].move_flag == 1 && enemy_shot[i].init_flag == 1) {
			for (int j = 0;j < enemy_shot[i].max_bullet;j++) {

				DrawRotaGraph(enemy_shot[i].draw_x[j], enemy_shot[i].draw_y[j], 1.5, 0.0, img_bullet, TRUE);
			}
		}
	}
}

void my_draw_boss() {
	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1) {
			DrawFormatString(boss[i].draw_x, boss[i].draw_y, Color_Maroon, "‘²Œ¤”­•\[%d]", boss[i].serial_num);
		}
	}
}

void my_draw_boss_power() {
	SetFontSize(7);
	for (int i = 0; i < DISP_BOSS_MAX; i++) {
		if (boss[i].move_flag == 1 && boss[i].init_flag == 1) {
			int x_point = 0;
			for (int j = 0; j < boss[i].power; j++) {
				DrawFormatString(boss[i].draw_x + x_point, boss[i].draw_y - 7, Color_White, "|");
				x_point += 1;
			}
		}
	}
	SetFontSize(16);
}

void my_draw_enemy_power() {
	SetFontSize(7);
	for (int i = 0; i < DISP_ENEMY_MAX; i++) {
		if (enemy[i].move_flag == 1 && enemy[i].init_flag == 1) {
			int x_point = 0;
			for (int j = 0; j < enemy[i].power; j++) {
				DrawFormatString(enemy[i].draw_x + x_point, enemy[i].draw_y - 7, Color_White, "|");
				x_point += 1;
			}
		}
	}
	SetFontSize(16);
}

void my_draw_exp_effect() {
	for (int i = 0;i < EXP_EFFECT_MAX;i++) {
		if (exp_effect[i].move_flag == 1 && exp_effect[i].init_flag == 1) {
			DrawFormatString(exp_effect[i].draw_x, exp_effect[i].draw_y, Color_Maroon, "¬•§");
		}
	}
}

void my_draw_item() {
	for (int i = 0;i < ITEM_MAX;i++) {
		if (item[i].move_flag == 1 && item[i].init_flag == 1) {
			DrawRotaGraph(item[i].draw_x, item[i].draw_y, 0.7, 0.0, img_item, TRUE);
		}
	}
}

void my_draw_sounds_title() {
	if (gamecount >= 180 && gamecount <= 400 && stage_num == 0) {
		DrawFormatString(20, 460, Color_White, "BGMF‹¶‹C‚Ì‰QŠª‚Ì’Ê‚è“¹");
	}
	if (gamecount >= 180 && gamecount <= 400 && stage_num == 1) {
		DrawFormatString(20, 460, Color_White, "BGMFl—ö‚µ_—l");
	}
	if (gamecount >= 180 && gamecount <= 400 && stage_num == 2) {
		DrawFormatString(20, 460, Color_White, "BGMFƒtƒH[ƒ‹ƒIƒuƒtƒH[ƒ‹@`@H‚ß‚­‘ê");
	}
}

void my_draw_score_board() {
	DrawBox(440, 0, 640, 480, Color_Maroon, true);
	DrawFormatString(460, 20, Color_White, "gamecount = %d", gamecount);
	DrawFormatString(460, 40, Color_White, "p1.power = %d", p1.power);
	DrawFormatString(460, 360, Color_White, "score = %d", score);
	DrawFormatString(460, 380, Color_White, "‘€ì•û–@");
	DrawFormatString(460, 400, Color_White, "ˆÚ“®:–îˆóƒL[");
	DrawFormatString(460, 420, Color_White, "ƒVƒ‡ƒbƒg:‚yƒL[");
}

void my_play_bgm() {
	if (gamecount == 0) {
		switch (stage_num) {
		case 0: PlaySoundMem(BGM_1st, DX_PLAYTYPE_LOOP); break;
		case 1: PlaySoundMem(BGM_2nd, DX_PLAYTYPE_LOOP); break;
		case 2: PlaySoundMem(BGM_3rd, DX_PLAYTYPE_LOOP); break;
		}
	}
}

void my_stop_bgm() {
	switch (stage_num) {
	case 1:
		ChangeVolumeSoundMem(254 - (gamecount / 2), BGM_1st);
		if (gamecount == 508)
			StopSoundMem(BGM_1st);
		break;
	case 2:
		ChangeVolumeSoundMem(254 - (gamecount / 2), BGM_2nd);
		if (gamecount == 508)
			StopSoundMem(BGM_2nd);
		break;
	case 3:
		ChangeVolumeSoundMem(254 - (gamecount / 2), BGM_3rd);
		if (gamecount == 508)
			StopSoundMem(BGM_3rd);
		break;
	}
}

void my_timer() {
	gamecount++;
}

int my_get_key() {
	char keys[256];
	GetHitKeyStateAll(keys);
	for (int i = 0; i < 256; i++) {
		if (keys[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
	return 0;
}