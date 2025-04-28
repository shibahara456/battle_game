#include <iostream>
#include <vector>
#include <string>
#include "map.h"

using namespace std;

//マップのコンストラクタ　マップの基盤作成
Map::Map() {

    char wall = '#';    //壁
    char raod = '.';    //道
    string wall_str;    //壁だけの文字列
    string raod_str1;   //道だけの文字列
    string raod_str2;   //壁と道の文字列   #.#.#.#.#.#　←こういうやつ

    //壁の文字列作成
    for (int i = 0;i < MAP_WIDTH;i++) {
        wall_str = wall_str + wall;
    }
    //道の文字列作成
    for (int i = 0;i < MAP_WIDTH - 2;i++) {
        raod_str1 = raod_str1 + raod;
    }
    //壁と道の文字列作成
    for (int i = 0;i < MAP_WIDTH;i++) {
        if (i % 2 == 0) {
            raod_str2 = raod_str2 + wall;
        }
        else {
            raod_str2 = raod_str2 + raod;
        }
    }

    //マップ作成
    for (int i = 0;i < MAP_HEIGHT;i++) {
        if (i == 0 || i == MAP_HEIGHT - 1) {
            map.insert(map.begin() + i, wall_str);              //一番下と一番上を壁にする
        }
        else if (i % 2 == 0) {
            map.insert(map.begin() + i, raod_str2);             //2で割り切れたら壁と道の文字列を配置
        }
        else {
            map.insert(map.begin() + i, '#' + raod_str1 + '#'); //それ以外は道     左と右は壁にする
        }

    }
}
//マップの自動生成
void Map::create_map() {
    int r = 0;       //ランダム用関数
    int now = 0;//ランダムの種   
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
//マップの表示
void Map::draw_map() {
    for (int i = 0;i < map.size();i++) {
        cout << map[i] << "\n";
    }
}

char Map::chk_map(int height, int width) {
    return map[height][width];
}

/*
    //壁チェック
bool Map::chk_wall(int height, int width) {

    if (map[height][width] == '#') {
        return true;
    }
    else {
        return false;
    }
}
//敵チェック
bool Map::chk_enemy(int height, int width) {
    if (map[height][width] == 'E') {
        return true;
    }
    else {
        return false;
    }
}
//道チェック
bool Map::chk_raod(int height, int width) {
    if (map[height][width] == '.') {
        return true;
    }
    else {
        return false;
    }
}
*/

