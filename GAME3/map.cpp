#include <iostream>
#include <vector>
#include <string>
#include "map.h"

using namespace std;

//�}�b�v�̃R���X�g���N�^�@�}�b�v�̊�Ս쐬
Map::Map() {

    char wall = '#';    //��
    char raod = '.';    //��
    string wall_str;    //�ǂ����̕�����
    string raod_str1;   //�������̕�����
    string raod_str2;   //�ǂƓ��̕�����   #.#.#.#.#.#�@�������������

    //�ǂ̕�����쐬
    for (int i = 0;i < MAP_WIDTH;i++) {
        wall_str = wall_str + wall;
    }
    //���̕�����쐬
    for (int i = 0;i < MAP_WIDTH - 2;i++) {
        raod_str1 = raod_str1 + raod;
    }
    //�ǂƓ��̕�����쐬
    for (int i = 0;i < MAP_WIDTH;i++) {
        if (i % 2 == 0) {
            raod_str2 = raod_str2 + wall;
        }
        else {
            raod_str2 = raod_str2 + raod;
        }
    }

    //�}�b�v�쐬
    for (int i = 0;i < MAP_HEIGHT;i++) {
        if (i == 0 || i == MAP_HEIGHT - 1) {
            map.insert(map.begin() + i, wall_str);              //��ԉ��ƈ�ԏ��ǂɂ���
        }
        else if (i % 2 == 0) {
            map.insert(map.begin() + i, raod_str2);             //2�Ŋ���؂ꂽ��ǂƓ��̕������z�u
        }
        else {
            map.insert(map.begin() + i, '#' + raod_str1 + '#'); //����ȊO�͓�     ���ƉE�͕ǂɂ���
        }

    }
}
//�}�b�v�̎�������
void Map::create_map() {
    int r = 0;       //�����_���p�֐�
    int now = 0;//�����_���̎�   
    int flg = 0;

    now = (unsigned int)time(NULL);
    srand(now);

    for (int i = 2;i < MAP_HEIGHT - 2;i += 2) {
        for (int j = 2;j < MAP_WIDTH - 2;j += 2) {
            if (i == 2) {
                while (1) {

                    r = rand() % 4;
                    switch (r) {
                    case 0:
                        if (chk_map(i + 1, j) == '.') {
                            map[i + 1].replace(j, 1, "#");
                            flg = 1;
                        }
                        break;
                    case 1:
                        if (chk_map(i - 1, j) == '.') {
                            map[i - 1].replace(j, 1, "#");
                            flg = 1;
                        }
                        break;
                    case 2:
                        if (chk_map(i, j + 1) == '.') {
                            map[i].replace(j + 1, 1, "#");
                            flg = 1;
                        }
                        break;
                    case 3:
                        if (chk_map(i, j - 1) == '.') {
                            map[i].replace(j - 1, 1, "#");
                            flg = 1;
                        }
                        break;
                    }
                    if (flg == 1) {
                        break;
                    }
                }

            }
            else {
                while (1) {

                    r = rand() % 3;
                    switch (r) {
                    case 0:
                        if (chk_map(i + 1, j) == '.') {
                            map[i + 1].replace(j, 1, "#");
                            flg = 1;
                        }
                        break;
                    case 1:
                        if (chk_map(i, j + 1) == '.') {
                            map[i].replace(j + 1, 1, "#");
                            flg = 1;
                        }
                        break;
                    case 2:
                        if (chk_map(i, j - 1) == '.') {
                            map[i].replace(j - 1, 1, "#");
                            flg = 1;
                        }
                        break;
                    }
                    if (flg == 1) {
                        break;
                    }
                }
            }
        }
    }
}
//�}�b�v�̕\��
void Map::draw_map() {
    for (int i = 0;i < map.size();i++) {
        cout << map[i] << "\n";
    }
}

char Map::chk_map(int height, int width) {
    return map[height][width];
}

/*
    //�ǃ`�F�b�N
bool Map::chk_wall(int height, int width) {

    if (map[height][width] == '#') {
        return true;
    }
    else {
        return false;
    }
}
//�G�`�F�b�N
bool Map::chk_enemy(int height, int width) {
    if (map[height][width] == 'E') {
        return true;
    }
    else {
        return false;
    }
}
//���`�F�b�N
bool Map::chk_raod(int height, int width) {
    if (map[height][width] == '.') {
        return true;
    }
    else {
        return false;
    }
}
*/

