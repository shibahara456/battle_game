#pragma once
#include <vector>

using namespace std;

const int MAP_WIDTH = 23;
const int MAP_HEIGHT = 9;


class Map {
	vector<string> map;
	int stage = 0;
public:
	Map();	//�}�b�v�̘g�g�ݍ쐬
	void create_map();		//�}�b�v�̎�������
	void draw_map();		//�}�b�v�̕\��

	char chk_map(int height, int width);

	//void set_map(int height, int width, char entity);  //�}�b�v�ɔz�u����@�����P�A�����Q�͍��W�@�@�����R�͉���z�u���邩
	/*
	bool chk_wall(int height,int width);//�ǃ`�F�b�N
	bool chk_enemy(int height,int width);//�G�`�F�b�N
	bool chk_raod(int height, int width);//���`�F�b�N
	*/



};

