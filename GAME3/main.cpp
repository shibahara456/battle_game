#include <iostream>
#include "game.h"

using namespace std;

int main() {
	Game game;

	game.create_map();

	game.setmap_entity();

	while (1) {
		game.disp_game();

		game.move_player();

		game.move_enemy();


		game.chk_battle();



		game.reset_disp();
	}



	return 0;
}



