#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <queue>
#include<array>
#include "game.h"
#include "enemy.h"
#include "player.h"

using namespace std;

//敵生成　コンストラクタ
Game::Game() {
	for (int i = 0;i < MAX_ENEMY;i++) {
		enemy.push_back(i);
	}
}

//マップ自動生成
void Game::create_map() {
	map.create_map();
}


//プレイヤーマップ配置、敵マップ配置、をする
void Game::setmap_entity() {

	//プレイヤーの配置
	player.set_xy();


	//敵のランダム配置
	int height_r = 0;      //ランダム用関数
	int widht_r = 0;       //ランダム用関数
	int now = 0;//ランダムの種   

	now = (unsigned int)time(NULL);
	srand(now);
	//敵の数繰り返す
	for (int i = 0;i < MAX_ENEMY;i++) {
		//道じゃなければ繰り返す
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

//敵のいる場所を確認する　いたらtrue　いなかったらfalse
bool Game::chk_enemy(int height, int width) {
	for (int i = 0;i < MAX_ENEMY;i++) {
		if (height == enemy[i].get_height() && width == enemy[i].get_width()) {
			return true;
			break;
		}
		
	}
	return false;
}


//マップ、ステータスとか表示
void Game::disp_game() {

	
	for (int i = 0;i < MAP_HEIGHT;i++) {
		for (int j = 0;j < MAP_WIDTH;j++) {
			//プレイヤーの表示
			if (i == player.get_height() && j == player.get_width()) {
				cout << '@';
			}
			//敵の表示
			else if (chk_enemy(i, j) == 1) {
				cout << 'E';
			}
			//道か壁の表示
			else {
				cout << map.chk_map(i, j);
			}
		}
		cout << "\n";
	}




	//player.draw_statas();
}
//移動入力をとる
int Game::get_input() {
	int input;

	input = _getch();

	return input;
}

//再描画
void Game::reset_disp() {
	system("cls");
}

//プレイヤーの移動判定
void Game::move_player() {
	int input;

	input = get_input();	//キー入力取得

	//プレイヤーの現在位置
	int pl_height = player.get_height();
	int pl_width = player.get_width();

	//移動入力判定
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
	//移動した先を入れる
	player.walk_player(pl_height, pl_width);

}

//敵の移動
void Game::move_enemy() {

	//敵の数だけ繰り返す
	for (int em = 0;em < MAX_ENEMY;em++) {

		//↓プレイヤーまでの最短ルートを探索する		横幅優先探索アルゴリズム使用

		vector<array<int, 3>> log; //今まで進んだ記録を格納
		queue< array<int, 2>> que; //今進んでいる先（頂点）を格納

		int em_height = enemy[em].get_height();	//敵の位置　y軸
		int em_width = enemy[em].get_width();	//敵の位置	x軸

		int step = 0;	//敵の位置から進んだ距離
		int cnt1 = 1;	//stepのために使用
		int cnt2 = 1;	//stepのために使用

		int flg = 0;	//終了判定用

		//現在の位置をリストに格納
		log.push_back({ step, em_height,em_width });
		que.push({ em_height,em_width });

		//プレイヤーにたどり着くまでのループ
		while (1) {
			step++;
			cnt1 = cnt2;
			cnt2 = 0;
			
			for (int s = 0;s < cnt1;s++) {
				//キューの一番最初のｘ軸ｙ軸を格納
				em_height = que.front()[0];
				em_width = que.front()[1];

				que.pop();	//キューの最初を取り出す

				//現在の位置がプレイヤーと同じか　（終了判定）
				if (em_height == player.get_height() && em_width == player.get_width()) {
					flg = 1;
					break;
				}

				//上下左右に動けるかを格納する　初期値0	動け無いなら1
				int crossroad[4] = { 0,0,0,0 };		

				//logから訪問済みかどうか調べる　訪問済みならcrossroadに１をいれる
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
				//動ける場所を探す　壁判定
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
				//動ける場所をキューとログに格納
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

		//ログから最短ルートを探索		プレイヤーの位置から敵の位置へと計算
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
		
		//敵と被ると動かなくする
		int nomove = 0;
		for (int i = 0;i < MAX_ENEMY;i++) {
			if (enemy[i].get_height() == em_height && enemy[i].get_width() == em_width) {
				nomove = 1;
			}
		}
		//敵クラスに格納
		if (nomove == 0) {
			enemy[em].walk_enemy(em_height, em_width);
		}

		//プレイヤーと敵が隣同士なら戦闘開始
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

//戦闘チェック
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

	cout << "\n\n戦闘開始！！";

	
}

