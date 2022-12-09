#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>

#include "game.h"

using namespace std;

Player::Player()
{
	money = 0;
	upgrade = 1;
	game_time = 0;
	drone = 0;
	drone_upgrade = 1;
	drone_upgrade_price = 30;
	drone_price = 30;
}

//Init game
Window::Window()
{
	main_menu = newwin(16,50,0,0);
	stats = newwin(16,30,0,50);
	menu_type = 0;
	menu_selector = 0;
}

void Window::menu_io()
{
	wclear(main_menu);
	box(main_menu, 0, 0);
	if(menu_type == 0)
	{
		mvwprintw(main_menu,4,5,"Upgrade");
		mvwprintw(main_menu,5,5,"Drone Supply");
		mvwprintw(main_menu,6,5,"Quit");
	}
	if(menu_type != 0) mvwprintw(main_menu,4,5,"<-- Back");
	if(menu_type == 1)
	{
	    for(int i = 0; i < shop->get_upgrades_size() - 1; i++)
	    {
			mvwprintw(main_menu, 5 + i, 5, shop->upgrade_io(i).c_str());
	    }
	}
	if(menu_type == 2)
	{
		mvwprintw(main_menu, 5, 5, "Buy drone for: $%d", pc->get_drone_price());
		mvwprintw(main_menu, 6, 5, "Upgrade drones for: $%d", pc->get_drone_upgrade_price());
	}
	if(menu_type == 3)
	{
		mvwprintw(main_menu,5,5,"Exit game");
	}
	mvwprintw(main_menu, menu_selector + 4, 2, ">>");
}

void Window::stats_io(Player *pc)
{
	wclear(stats);
	box(stats,0,0);
	mvwprintw(stats,4,3,"Balance: $%d",pc->get_money());
	mvwprintw(stats,6,3,"Money Per Click: $%d",pc->get_upgrade());
	mvwprintw(stats,8,3,"Drones: %d",pc->get_drone());
	mvwprintw(stats,9,3,"Drones Money/Second: $%d",pc->get_drone_upgrade() * pc->get_drone());
	mvwprintw(stats,14,3,"Game Time: %d",pc->get_game_time());
	refresh_stats();
}

void Window::alert_popup_io(std::string alert_text)
{
	char ch;
	alert=newwin(5,50,5,15);
	box(alert,0,0);	
	mvwprintw(alert,0,22,"ALERT");
	mvwprintw(alert,2,2,alert_text.c_str());
	mvwprintw(alert,4,13,"To continue, press ENTER..");
	refresh_alert_popup();
	while(1)
	{
		ch = getch();
		if(ch == 10)
		{
			delwin(alert);
			break;
		}
	}
    menu_io();
    refresh_menu();
}

void Window::selector_up()
{
    if(menu_selector > 0)
    {
		menu_selector--;
    }
}

void Window::selector_down()
{
    if(menu_type == 0 && menu_selector < 2)
    {
		menu_selector++;
    }
    if(menu_type == 1 && menu_selector < shop->get_upgrades_size() - 1)
    {
		menu_selector++;
    }
    if(menu_type == 2 && menu_selector < 2)
    {
		menu_selector++;
    }
    if(menu_type == 3 && menu_selector < 1)
    {
		menu_selector++;
    }
}

void Window::quit_game()
{
	alert_popup_io("Exiting game...");
    system("clear");
    endwin();
    exit(0);
}

void Window::selected()
{
	if(menu_type == 0)
	{
	    menu_type = menu_selector + 1;
	    menu_selector = 0;
	}
	else
	{
		//back button
	    if(menu_type != 0 && menu_selector == 0)
	    {
	    	menu_type = 0;
	    }
	    //Upgrades menu
	    if(menu_type == 1)
	    {
	    	int *shop_data;
			if(menu_type == 1)
			{
				shop_data = shop->get_upgrades(menu_selector - 1);
			}

			if(pc->get_money() >= shop_data[1])
			{ 
				pc->buy_upgrade(shop_data[2], shop_data[1]);
			}
			else
			{
				alert_popup_io("You need more money");
			}
		}
		//Drone supply menu
	    if(menu_type == 2)
	    {
			if(menu_selector == 1)
			{
			    if(pc->get_money() >= pc->get_drone_price())
			    {
					pc->buy_drone();
			    }
			    else
			    {
					alert_popup_io("You need more money");
			    }
			}
			if(menu_selector == 2)
			{
			    if(pc->get_drone() >= 0)
			    {
					if(pc->get_money() >= pc->get_drone_upgrade_price())
					{
					    pc->buy_drone_upgrade();
					}
					else
					{
					    alert_popup_io("You need more money");
					}
			    }
			    else
			    {
					alert_popup_io("You have no drones");
			    }
			}
	    }

	    if(menu_type == 3)
	    {
			if(menu_selector == 1)
			{
				quit_game();
			}
		}
	wclear(main_menu);
	menu_io();
	refresh_menu();
	}
}
