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
	Player();				//�v���C���[�R���X�g���N�^�@�v���C���[�̏����l�����
	void set_xy();			//height��weight������
	void draw_statas();		//�v���C���[�̃X�e�[�^�X�\��
	void walk_player(int height, int width);		//�v���C���[�ړ�����
	int get_height();
	int get_width();

	//void setmap_player(Map map);	//�}�b�v�Ƀv���C���[��z�u����
};

