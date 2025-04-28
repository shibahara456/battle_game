#pragma once
#include <vector>

using namespace std;

const int MAP_WIDTH = 23;
const int MAP_HEIGHT = 9;


class Map {
	vector<string> map;
	int stage = 0;
public:
	Map();	//マップの枠組み作成
	void create_map();		//マップの自動生成
	void draw_map();		//マップの表示

	char chk_map(int height, int width);

	//void set_map(int height, int width, char entity);  //マップに配置する　引数１、引数２は座標　　引数３は何を配置するか
	/*
	bool chk_wall(int height,int width);//壁チェック
	bool chk_enemy(int height,int width);//敵チェック
	bool chk_raod(int height, int width);//道チェック
	*/



};

