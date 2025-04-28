#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <queue>
#include<array>
#include "game.h"
#include "enemy.h"
#include "player.h"

using namespace std;

//�G�����@�R���X�g���N�^
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
			height_r = rand() % (MAP_HEIGHT - 3);
			widht_r = rand() % (MAP_WIDTH - 3);

			if (map.chk_map(height_r, widht_r) == '.') {
				enemy[i].random_set(height_r, widht_r);
				break;
			}
		}
	}

	//player.setmap_player(map);
	//enemy[].setmap_enemy();
}

//�G�̂���ꏊ���m�F����@������true�@���Ȃ�������false
bool Game::chk_enemy(int height, int width) {
	for (int i = 0;i < MAX_ENEMY;i++) {
		if (height == enemy[i].get_height() && width == enemy[i].get_width()) {
			return true;
			break;
		}
		
	}
	return false;
}


//�}�b�v�A�X�e�[�^�X�Ƃ��\��
void Game::disp_game() {

	
	for (int i = 0;i < MAP_HEIGHT;i++) {
		for (int j = 0;j < MAP_WIDTH;j++) {
			//�v���C���[�̕\��
			if (i == player.get_height() && j == player.get_width()) {
				cout << '@';
			}
			//�G�̕\��
			else if (chk_enemy(i, j) == 1) {
				cout << 'E';
			}
			//�����ǂ̕\��
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

//�ĕ`��
void Game::reset_disp() {
	system("cls");
}

//�v���C���[�̈ړ�����
void Game::move_player() {
	int input;

	input = get_input();	//�L�[���͎擾

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

//�G�̈ړ�
void Game::move_enemy() {

	//�G�̐������J��Ԃ�
	for (int em = 0;em < MAX_ENEMY;em++) {

		//���v���C���[�܂ł̍ŒZ���[�g��T������		�����D��T���A���S���Y���g�p

		vector<array<int, 3>> log; //���܂Ői�񂾋L�^���i�[
		queue< array<int, 2>> que; //���i��ł����i���_�j���i�[

		int em_height = enemy[em].get_height();	//�G�̈ʒu�@y��
		int em_width = enemy[em].get_width();	//�G�̈ʒu	x��

		int step = 0;	//�G�̈ʒu����i�񂾋���
		int cnt1 = 1;	//step�̂��߂Ɏg�p
		int cnt2 = 1;	//step�̂��߂Ɏg�p

		int flg = 0;	//�I������p

		//���݂̈ʒu�����X�g�Ɋi�[
		log.push_back({ step, em_height,em_width });
		que.push({ em_height,em_width });

		//�v���C���[�ɂ��ǂ蒅���܂ł̃��[�v
		while (1) {
			step++;
			cnt1 = cnt2;
			cnt2 = 0;
			
			for (int s = 0;s < cnt1;s++) {
				//�L���[�̈�ԍŏ��̂����������i�[
				em_height = que.front()[0];
				em_width = que.front()[1];

				que.pop();	//�L���[�̍ŏ������o��

				//���݂̈ʒu���v���C���[�Ɠ������@�i�I������j
				if (em_height == player.get_height() && em_width == player.get_width()) {
					flg = 1;
					break;
				}

				//�㉺���E�ɓ����邩���i�[����@�����l0	���������Ȃ�1
				int crossroad[4] = { 0,0,0,0 };		

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

		step = step - 2;

		//���O����ŒZ���[�g��T��		�v���C���[�̈ʒu����G�̈ʒu�ւƌv�Z
		for (int i = log.size() - 1;i > 0;i--) {
			if (log[i][0] == step) {
				int chk = (em_height - log[i][1]) + (em_width - log[i][2]);
				if ((chk == 1 || chk == -1) && (em_height == log[i][1] || em_width == log[i][2])) {
					em_height = log[i][1];
					em_width = log[i][2];
					step--;
				}
			}
		}
		
		//�G�Ɣ��Ɠ����Ȃ�����
		int nomove = 0;
		for (int i = 0;i < MAX_ENEMY;i++) {
			if (enemy[i].get_height() == em_height && enemy[i].get_width() == em_width) {
				nomove = 1;
			}
		}
		//�G�N���X�Ɋi�[
		if (nomove == 0) {
			enemy[em].walk_enemy(em_height, em_width);
		}

		//�v���C���[�ƓG���ד��m�Ȃ�퓬�J�n
		int player_xy[2] = { player.get_height(),player.get_width() };

		if (player_xy[0] + 1 == em_height && player_xy[1] == em_width) {
			start_battle();
		}
		if (player_xy[0] - 1 == em_height && player_xy[1] == em_width) {
			start_battle();
		}
		if (player_xy[0] == em_height && player_xy[1] + 1 == em_width) {
			start_battle();
		}
		if (player_xy[0] == em_height && player_xy[1] - 1 == em_width) {
			start_battle();
		}
		
	}
}

//�퓬�`�F�b�N
void Game::chk_battle() {
	for (int i = 0;i < MAX_ENEMY;i++) {
		int em_height = enemy[i].get_height();
		int em_width = enemy[i].get_width();

		int player_xy[2] = { player.get_height(),player.get_width() };

		if (player_xy[0] + 1 == em_height && player_xy[1] == em_width) {
			start_battle();
		}
		if (player_xy[0] - 1 == em_height && player_xy[1] == em_width) {
			start_battle();
		}
		if (player_xy[0] == em_height && player_xy[1] + 1 == em_width) {
			start_battle();
		}
		if (player_xy[0] == em_height && player_xy[1] - 1 == em_width) {
			start_battle();
		}
	}
}

void Game::start_battle(){
	reset_disp();
	disp_game();

	cout << "\n\n�퓬�J�n�I�I";

	
}

