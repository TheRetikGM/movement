#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct player
{
	int xLoc;
	int yLoc;
	int lastyLoc;
	int lastxLoc;
	char ch;
};
void printWall(WINDOW *win, int y, int x, char ch, int len, char (*cor)[1225*5], char reg)
{
	char buf[10];
	int count = 0;
	char cha[2] = "-";

	while(strcmp(cha, cor[count]) != 0)
	{
		count++;
	}
	if (ch == 'h')
	{
		int a = 0;

		mvwhline(win, y, x, ACS_HLINE, len);
		if (reg == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				sprintf(buf, "%i;%i", y, x);
				for (int k = 0; strcmp(cor[k], "-") != 0; k++)
					if (strcmp(cor[k], buf) == 0)
						a++;
				if (a == 0)
					strcpy(cor[count + i], buf);

				else
				{
					a = 0;
					i--;
				}
				x++;
			}
		}
		else if (reg == 'n');
	}
	else if (ch == 'v')
	{
		int a = 0;

		mvwvline(win, y, x, ACS_VLINE, len);
		if(reg == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				sprintf(buf, "%i;%i", y, x);
				for (int k = 0; strcmp(cor[k], "-") != 0; k++)
					if (strcmp(cor[k], buf) == 0)
						a++;
				if (a == 0)
					strcpy(cor[count + i], buf);
				else
				{
					a = 0;
					i--;
				}
				y++;
			}
		}
		else if (reg == 'n');
	}
}
void printRoom(WINDOW *win, int y, int x, char (*cor)[1225*5], char reg)
{
	box(win, 0, 0);
	printWall(win, y / 2 - 5, x / 2 - 10, 'h', 20, cor, reg);
	printWall(win, y / 2 - 5, x / 2 + 10, 'v', 10, cor, reg);
	printWall(win, y / 2 + 5, x / 2 - 9, 'h', 20, cor, reg);
	printWall(win, y / 2 - 4, x / 2 - 10, 'v', 10, cor, reg);
	mvwaddch(win, y / 2 - 5, x / 2 - 10, ACS_ULCORNER);
	mvwaddch(win, y / 2 - 5, x / 2 + 10, ACS_URCORNER);
	mvwaddch(win, y / 2 + 5, x / 2 + 10, ACS_LRCORNER);
	mvwaddch(win, y / 2 + 5, x / 2 - 10, ACS_LLCORNER); 
	move(LINES - 2, 0);
	clrtoeol();
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 3, "Press \"x\" to exit or Press \"Ctrl+O\" to enter options menu");
	attroff(COLOR_PAIR(2));
	refresh();
	wrefresh(win);

}
int out_int_choice;
int main_game()
{
	initscr();
	start_color();
	noecho();
	nodelay(stdscr, true);
	curs_set(FALSE);
	
	struct player player1;
	int Maxx, Maxy;
	unsigned int y = 25;
	unsigned int x = 49;
	int c = 0;
	char coordinates[1225][1225*5];
	player1.xLoc = 1;
	player1.yLoc = 1;
	player1.ch = '@';

	int lastyLoc, lastxLoc;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	
	getmaxyx(stdscr, Maxy, Maxx);
	WINDOW *win = newwin(y, x, Maxy / 2 - y / 2, Maxx / 2 - x / 2);

	refresh();

	for(int i = 0; i < 1225; i++)
	{
		strcpy(coordinates[i], "-");
	}
	
	printRoom(win, y, x, coordinates, 'y');

	wrefresh(win);
	keypad(win, true);

	mvwaddch(win, player1.yLoc, player1.xLoc, player1.ch);
	do
	{
		player1.lastyLoc = player1.yLoc;
		player1.lastxLoc = player1.xLoc;
		out_int_choice = c;
		switch(c)
		{
			case KEY_UP:
			{
				int a = 0;
				char curcoor[10];
				int nexty = player1.yLoc - 1;
				sprintf(curcoor, "%i;%i", nexty, player1.xLoc);
				 
				for (int i = 0; strcmp(coordinates[i], "-") != 0; i++)
					if(strcmp(coordinates[i], curcoor) == 0)
						a++;

				if (a == 0)
					player1.yLoc--;

				if (player1.yLoc == 0)
				{
					player1.yLoc = 1;
				}
				break;
			}
			case KEY_DOWN:
			{
				int a = 0;
				char curcoor[10];
				int nexty = player1.yLoc + 1;
				sprintf(curcoor, "%i;%i", nexty, player1.xLoc);
				 
				for (int i = 0; strcmp(coordinates[i], "-") != 0; i++)
					if(strcmp(coordinates[i], curcoor) == 0)
						a++;

				if (a == 0)
					player1.yLoc++;

				if (player1.yLoc == (y - 1))
					player1.yLoc = y - 2;
				break;
			}
			case KEY_LEFT:
			{
				int a = 0;
				char curcoor[10];
				int nextx = player1.xLoc - 1;
				sprintf(curcoor, "%i;%i", player1.yLoc, nextx);
				 
				for (int i = 0; strcmp(coordinates[i], "-") != 0; i++)
					if(strcmp(coordinates[i], curcoor) == 0)
						a++;

				if (a == 0)
					player1.xLoc -= 1;

				if (player1.xLoc <= 0)
					player1.xLoc = player1.lastxLoc;
				break;
			}
			case KEY_RIGHT:
			{
				int a = 0;
				char curcoor[10];
				int nextx = player1.xLoc + 1;
				sprintf(curcoor, "%i;%i", player1.yLoc, nextx);
				 
				for (int i = 0; strcmp(coordinates[i], "-") != 0; i++)
					if(strcmp(coordinates[i], curcoor) == 0)
						a++;

				if (a == 0)
					player1.xLoc += 1;

				if (player1.xLoc >= (x - 1))
					player1.xLoc = player1.lastxLoc;
				break;
			}
			default:
				break;
		}
		if (c == 120)
		{
			break;
		}
		else if (c == 15)
		{
			break;
		}
		mvwaddch(win, player1.lastyLoc, player1.lastxLoc, ' ');

		wattron(win, COLOR_PAIR(1));
		mvwaddch(win, player1.yLoc, player1.xLoc, player1.ch);
		wattroff(win, COLOR_PAIR(1));

		wrefresh(win);
	} while(c = wgetch(win));

	endwin();
	
	return 0;
}

/*void printWall(WINDOW *win, int y, int x, char ch, int len, char (*cor)[1225*5], char reg)
{
	char buf[10];
	int count = 0;
	char cha[2] = "-";

	while(strcmp(cha, cor[count]) != 0)
	{
		count++;
	}
	if (ch == 'h')
	{
		int a = 0;

		mvwhline(win, y, x, ACS_HLINE, len);
		if (reg == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				sprintf(buf, "%i;%i", y, x);
				for (int k = 0; strcmp(cor[k], "-") != 0; k++)
					if (strcmp(cor[k], buf) == 0)
						a++;
				if (a == 0)
					strcpy(cor[count + i], buf);

				else
				{
					a = 0;
					i--;
				}
				x++;
			}
		}
		else if (reg == 'n');
	}
	else if (ch == 'v')
	{
		int a = 0;

		mvwvline(win, y, x, ACS_VLINE, len);
		if(reg == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				sprintf(buf, "%i;%i", y, x);
				for (int k = 0; strcmp(cor[k], "-") != 0; k++)
					if (strcmp(cor[k], buf) == 0)
						a++;
				if (a == 0)
					strcpy(cor[count + i], buf);
				else
				{
					a = 0;
					i--;
				}
				y++;
			}
		}
		else if (reg == 'n');
	}
}

void printRoom(WINDOW *win, int y, int x, char (*cor)[1225*5], char reg)
{
	box(win, 0, 0);
	printWall(win, y / 2 - 5, x / 2 - 10, 'h', 20, cor, reg);
	printWall(win, y / 2 - 5, x / 2 + 10, 'v', 10, cor, reg);
	printWall(win, y / 2 + 5, x / 2 - 9, 'h', 20, cor, reg);
	printWall(win, y / 2 - 4, x / 2 - 10, 'v', 10, cor, reg);
	mvwaddch(win, y / 2 - 5, x / 2 - 10, ACS_ULCORNER);
	mvwaddch(win, y / 2 - 5, x / 2 + 10, ACS_URCORNER);
	mvwaddch(win, y / 2 + 5, x / 2 + 10, ACS_LRCORNER);
	mvwaddch(win, y / 2 + 5, x / 2 - 10, ACS_LLCORNER); 
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 3, "Press \"x\" to exit");
	attroff(COLOR_PAIR(2));
	refresh();
	wrefresh(win);

}*/
