#pragma once
#include "map.h"

class map;

class Player {
	int lv;
	int hp;
	int atk;
	int def;
	int exp;
	int width_map;
	int height_map;
public:
	Player();				//プレイヤーコンストラクタ　プレイヤーの初期値入れる
	void set_xy();			//heightとweightを入れる
	void draw_statas();		//プレイヤーのステータス表示
	void walk_player(int height, int width);		//プレイヤー移動処理
	int get_height();
	int get_width();

	//void setmap_player(Map map);	//マップにプレイヤーを配置する
};

