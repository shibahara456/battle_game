#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <queue>
#include<array>
#include "game.h"
#include "enemy.h"
#include "player.h"

using namespace std;

Game::Game() {
	for (int i = 0;i < MAX_ENEMY;i++) {
		enemy.push_back(i);
	}
}

//�}�b�v��������
void Game::create_map() {
	map.create_map();
}


//�v���C���[�}�b�v�z�u�A�G�}�b�v�z�u�A������
void Game::setmap_entity() {

	//�v���C���[�̔z�u
	player.set_xy();


	//�G�̃����_���z�u
	int height_r = 0;      //�����_���p�֐�
	int widht_r = 0;       //�����_���p�֐�
	int now = 0;//�����_���̎�   

	now = (unsigned int)time(NULL);
	srand(now);
	//�G�̐��J��Ԃ�
	for (int i = 0;i < MAX_ENEMY;i++) {
		//������Ȃ���ΌJ��Ԃ�
		while (1) {
			height_r = rand() % MAP_HEIGHT;
			widht_r = rand() % MAP_WIDTH;

			if (map.chk_map(height_r, widht_r) == '.') {
				enemy[i].random_set(height_r, widht_r);
				break;
			}
		}
	}

	//player.setmap_player(map);
	//enemy[].setmap_enemy();
}

bool Game::chk_enemy(int height, int width) {
	for (int i = 0;i < MAX_ENEMY;i++) {
		if (height == enemy[i].get_height() && width == enemy[i].get_width()) {
			return true;
			break;
		}
		else {
			return false;
		}
	}
}


//�}�b�v�A�X�e�[�^�X�Ƃ��\��
void Game::disp_game() {
	//map.draw_map();

	for (int i = 0;i < MAP_HEIGHT;i++) {
		for (int j = 0;j < MAP_WIDTH;j++) {
			if (i == player.get_height() && j == player.get_width()) {
				cout << '@';
			}
			else if (chk_enemy(i, j) == 1) {
				cout << 'E';
			}
			else {
				cout << map.chk_map(i, j);
			}
		}
		cout << "\n";
	}




	//player.draw_statas();
}
//�ړ����͂��Ƃ�
int Game::get_input() {
	int input;

	input = _getch();

	return input;
}

void Game::reset_disp() {
	system("cls");
}


void Game::move_player() {
	int input;

	input = get_input();

	//�v���C���[�̌��݈ʒu
	int pl_height = player.get_height();
	int pl_width = player.get_width();

	//�ړ����͔���
	if (input == 'w') {
		if (map.chk_map(pl_height - 1, pl_width) == '.') {
			pl_height--;
		}
	}
	if (input == 's') {
		if (map.chk_map(pl_height + 1, pl_width) == '.') {
			pl_height++;
		}
	}
	if (input == 'a') {
		if (map.chk_map(pl_height, pl_width - 1) == '.') {
			pl_width--;
		}
	}
	if (input == 'd') {
		if (map.chk_map(pl_height, pl_width + 1) == '.') {
			pl_width++;
		}
	}
	//�ړ������������
	player.walk_player(pl_height, pl_width);

}

void Game::move_enemy() {

	

	for (int em = 0;em < MAX_ENEMY;em++) {
		vector<array<int, 3>> log;
		queue< array<int, 2>> que;

		int em_height = enemy[em].get_height();
		int em_width = enemy[em].get_width();
		int step = 0;
		int cnt1 = 1;
		int cnt2 = 1;
		int flg = 0;

		log.push_back({ step, em_height,em_width });
		que.push({ em_height,em_width });


		while (1) {
			step++;
			cnt1 = cnt2;
			cnt2 = 0;
			
			for (int s = 0;s < cnt1;s++) {
				em_height = que.front()[0];
				em_width = que.front()[1];

				que.pop();

				if (em_height == player.get_height() && em_width == player.get_width()) {
					flg = 1;
					break;
				}




				int crossroad[4] = { 0,0,0,0 };		//�㉺���E�ɓ����邩���i�[����@�����l0	���������Ȃ�1

				//log����K��ς݂��ǂ������ׂ�@�K��ς݂Ȃ�crossroad�ɂP�������
				for (int i = 0;i < log.size();i++) {
					if (em_height == log[i][1] && em_width + 1 == log[i][2]) {
						crossroad[0] = 1;
					}
					if (em_height == log[i][1] && em_width - 1 == log[i][2]) {
						crossroad[1] = 1;
					}
					if (em_height - 1 == log[i][1] && em_width == log[i][2]) {
						crossroad[2] = 1;
					}
					if (em_height + 1 == log[i][1] && em_width == log[i][2]) {
						crossroad[3] = 1;
					}
				}
				//������ꏊ��T���@�ǔ���
				if (map.chk_map(em_height, em_width + 1) == '#') {
					crossroad[0] = 1;
				}
				if (map.chk_map(em_height, em_width - 1) == '#') {
					crossroad[1] = 1;
				}
				if (map.chk_map(em_height - 1, em_width) == '#') {
					crossroad[2] = 1;
				}
				if (map.chk_map(em_height + 1, em_width) == '#') {
					crossroad[3] = 1;
				}
				//������ꏊ���L���[�ƃ��O�Ɋi�[
				for (int j = 0;j < 4;j++) {
					if (crossroad[j] == 0) {
						switch (j) {
						case 0:
							que.push({ em_height,em_width + 1 });
							log.push_back({ step,em_height,em_width + 1 });
							cnt2++;
							break;
						case 1:
							que.push({ em_height,em_width - 1 });
							log.push_back({ step,em_height,em_width - 1 });
							cnt2++;
							break;
						case 2:
							que.push({ em_height - 1,em_width });
							log.push_back({ step,em_height - 1,em_width });
							cnt2++;
							break;
						case 3:
							que.push({ em_height + 1,em_width });
							log.push_back({ step,em_height + 1,em_width });
							cnt2++;
							break;
						}

					}
				}
			}	
			if (flg == 1) {
				break;
			}
		}
		cout << em_height << "  " << em_width << "\n";

		for (int i = log.size() - 1;i > 1;i--) {
			
			
		}
		cout << em_height << "  " << em_width;
		enemy[em].walk_enemy(em_height, em_width);
	}
}

/*
if (log[i][0] == step - 2) {
				int chk = (em_height - log[i][1]) + (em_width - log[i][2]);
				if (chk == 1 || chk == -1) {
					em_height = log[i][1];
					em_width = log[i][2];
					step--;
				}
			}
*/



void Game::chk_battle() {
	for (int i = 0;i < MAX_ENEMY;i++) {
		if (enemy[i].get_height() == player.get_height() && enemy[i].get_width() == player.get_width()) {
			//start_battle();
		}
	}
}

