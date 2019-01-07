#include <ncurses.h>
#include <string.h>
#include "main_game.h"
#include "menu.h"

int main()
{
	int playerY = 1;
	int playerX = 1;

	while(1)
	{
		main_game(playerY, playerX);
		
		if (out_int_choice == 120)
			break;

		else if (out_int_choice == 15)
		{
			playerY = player1_yLoc;
			playerX = player1_xLoc;
			print_options_menu();
			if (strcmp(my_choice, "Exit") == 0)
				break;
		}
	}

	return 0;
}
