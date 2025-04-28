#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "enemy.h"
#include "map.h"
#include "game.h"

using namespace std;

//敵の初期値を入れる
Enemy::Enemy(int i) {
    hp = 10 + (i * 5);
    atk = 5 + (i * 2);
    exp = 5 + (i * 2);
    kill = 0;
}

void Enemy::random_set(int height_r, int width_r) {

    height_map = height_r;
    width_map = width_r;
}

int Enemy::get_height() {
    return height_map;
}
int Enemy::get_width() {
    return width_map;
}

//敵を動かす
void Enemy::walk_enemy(int height, int width) {
    height_map = height;
    width_map = width;
}
//マップに敵を配置する
//void Enemy::setmap_enemy() {}