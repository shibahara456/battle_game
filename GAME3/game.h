#pragma once
#include "player.h"
#include "map.h"
#include "enemy.h"
#include <vector>

class Player;
class Map;
class Enemy;

class Game {
	Player player;
	Map map;
	vector<Enemy> enemy;
public:
	Game();
	void create_map();		// } b v        
	void setmap_entity();		// v   C   [ } b v z u A G } b v z u A      
	void disp_game();			// } b v A X e [ ^ X ?  \  
	int get_input();		// ?    ?  ? 
	void move_player();
	void move_enemy();
	void reset_disp();
	bool chk_enemy(int height, int width);
	void chk_battle();
	//void start_battle();

};

