#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
			"Choice 1", "Choice 2",
			"Choice 3", "Choice 4",
			"Choice 5", "Choice 6",
			"Exit",
			(char *)NULL,
		};
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

char my_choice[200];
int print_options_menu()
{
	ITEM **my_items;
	int c;
	MENU *my_menu;
	int n_choices, i;
	WINDOW *my_menu_win;
	int menu_x, menu_y;
	
	initscr();
	noecho();
	start_color();
	cbreak();
	curs_set(FALSE);
	keypad(stdscr, true);
	raw();

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);\
	init_pair(5, COLOR_RED, COLOR_WHITE);
	
	menu_x = 30;
	menu_y = 10;
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
	
	for(i = 0; i < n_choices; ++i)
	{
		my_items[i] = new_item(choices[i], choices[i]);
	}
	my_menu = new_menu((ITEM **)my_items);
	set_menu_format(my_menu, 4, 2);
	menu_opts_off(my_menu, O_SHOWDESC);
	
	my_menu_win = newwin(menu_y, menu_x, getmaxy(stdscr) / 2 - menu_y / 2, getmaxx(stdscr) / 2 - menu_x / 2);
	wbkgd(my_menu_win, COLOR_PAIR(1)); 
	keypad(my_menu_win, true);

	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, menu_x - 2, 3, 1));
	set_menu_mark(my_menu, " * ");

	set_menu_fore(my_menu, COLOR_PAIR(2) | COLOR_PAIR(3));
	set_menu_back(my_menu, COLOR_PAIR(1));

	box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, menu_x, "Options", COLOR_PAIR(5));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, menu_x - 2);
	mvwaddch(my_menu_win, 2, menu_x - 1, ACS_RTEE);
	attron(COLOR_PAIR(4));
	move(LINES - 2, 0);
	clrtoeol();
	mvprintw(LINES - 2, 3, "Press \"q\" to quit options menu");
	attroff(COLOR_PAIR(4));
	refresh();

	post_menu(my_menu);
	wrefresh(my_menu_win);

	while(c = wgetch(my_menu_win))
	{
		if (c == 'q')
			break;
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				break;
			case 10:
			{
				ITEM *cur;
				
				cur = current_item(my_menu);
				my_choice[0] = '\0';
				sprintf(my_choice, "%s", item_name(cur));

				break;
			}
			break;
		}
		if (strcmp(my_choice, "Exit") == 0)
			break;
		wrefresh(my_menu_win);
	}
	for (int k = 0; k < n_choices; k++)
	{
		free_item(my_items[k]);
	}
	free(my_menu);
	unpost_menu(my_menu);
	werase(my_menu_win);

	endwin();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int lenght, menu_x, menu_y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, menu_y, menu_x);
	if(startx != 0)
		menu_x = startx;
	if(starty != 0)
		menu_y = starty;
	if(width == 0)
		width = 80;
	
	lenght = strlen(string);
	temp = (width - lenght) / 2;
	menu_x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, menu_y, menu_x, "%s", string);
	wattroff(win, color);
	refresh();
}
