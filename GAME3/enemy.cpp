#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "enemy.h"
#include "map.h"
#include "game.h"

using namespace std;

//�G�̏����l������
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

//�G�𓮂���
void Enemy::walk_enemy(int height, int width) {
    height_map = height;
    width_map = width;
}
//�}�b�v�ɓG��z�u����
//void Enemy::setmap_enemy() {}