#pragma once
#include "map.h"

using namespace std;

const int MAX_ENEMY = 1;

class Enemy {
	int hp;
	int atk;
	int exp;
	int kill;
	int width_map;
	int height_map;
public:
	Enemy(int i);			//敵の初期値を�Eれる

	void random_set(int height_r, int width_r);	//敵をランダムで配置する
	void walk_enemy(int height, int width);	//敵を動かす
	int get_height();
	int get_width();

	//void setmap_enemy(
};