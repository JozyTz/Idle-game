#include <ncurses.h>
#include <time.h>
#include "game.h"
#include <sys/ioctl.h> // for my own kbhit
#include <termios.h> //for my own kbhit
#include <stdlib.h> //system operations lib

using namespace std;

int main(void)
{
	//init game data and ncurses
	char ch = 0;
	bool run = 1;
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);
	Window game;
	Player pc;
	Shop shop;
	game.set_player(pc);
	game.set_shop(shop);
	shop.generate_items();
	clock_t start,end;
	time(&start);

	while(run==1)
	{
		//init game windows
		game.menu_io();
		game.stats_io(&pc);
		game.refresh_menu();
		ch = getch();
		napms(100);

		//game contols: w/k - up, s/j - down, ENTER - select, SPACE - add money
		if(ch == 32)
		{
			pc.add_money(pc.get_upgrade());
			game.stats_io(&pc);
		}
		if(ch==107 || ch==119)
		{
		    game.selector_up();
		    game.menu_io();
		    game.refresh_menu();
		}
		if(ch==106 || ch==115)
		{
		    game.selector_down();
		    game.menu_io();
		    game.refresh_menu();
		}
		if(ch==10)
		{
		    game.selected();
		    game.stats_io(&pc);
		}

		//timer stuff
		time(&end);
		if(difftime(end,start) > 1)
		{
			pc.add_game_time();
			pc.add_money(pc.get_drone() * pc.get_drone_upgrade());
			game.stats_io(&pc);
			time(&start);
		}
	}
	system("clear");
	endwin();
	return 0;
}
