#include <ncurses.h>
#include <string.h>
#include "main_game.h"
#include "menu.h"

int main()
{
	while(1)
	{
		main_game();
		
		if (out_int_choice == 120)
			break;
		else if (out_int_choice == 15)
		{
			print_options_menu();
			if (strcmp(my_choice, "Exit") == 0)
				break;
		}
	}

	return 0;
}
