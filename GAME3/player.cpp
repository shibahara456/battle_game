#include <iostream>
#include "player.h"

#include "map.h"
#include "game.h"

using namespace std;

//プレイヤーコンストラクタ　プレイヤーの初期値入れる
Player::Player() {
	lv = 1;
	hp = 50;
	atk = 10;
	def = 3;
	exp = 0;
}

void Player::set_xy() {
	height_map = MAP_HEIGHT - 2;
	width_map = MAP_WIDTH - 2;
}

//プレイヤーのステータス表示
void Player::draw_statas() {

}

int Player::get_height() {
	return height_map;
}
int Player::get_width() {
	return width_map;
}

void Player::walk_player(int height, int width) {
	height_map = height;
	width_map = width;
}
//マップにプレイヤーを配置する
//void Player::setmap_player(Map map) {}