#include <iostream>
#include <ncurses.h>

#include "shop.h"

class Player
{
	protected:
		std::string name;
		int upgrade;
		int money;
		int drone; 
		int drone_upgrade;
		int drone_upgrade_price;
		int drone_price;
		int game_time;
	public:
		Player();
		void set_name(std::string name);
		void add_money(int amount) { money += amount; };
		void add_game_time() { game_time++; };

		void buy_upgrade(int amount, int price) { upgrade += amount; money -= price; };
		void buy_drone() { drone++; money -= drone_price; drone_price *= 2; };
		void buy_drone_upgrade() { drone_upgrade++; money -= drone_upgrade_price; drone_upgrade_price *= 2; };

		int get_money() { return money; };
		int get_upgrade() { return upgrade; };
		int get_game_time() { return game_time; };
		int get_drone() { return drone; };
		int get_drone_upgrade() { return drone_upgrade; };
		int get_drone_upgrade_price() { return drone_upgrade_price; };
		int get_drone_price() { return drone_price; };
};

class Window
{
	private:
		Shop *shop;
		Player *pc;
		int menu_type;
		int menu_selector;
		WINDOW *main_menu;
		WINDOW *stats;
		WINDOW *alert;

	public:
		Window();
		void set_player(Player &p) { pc = &p; };
		void set_shop(Shop &s) { shop = &s; };
		void menu_io();
		void stats_io(Player *pc);
		void alert_popup_io(std::string alert_text);
		void selector_up();
		void selector_down();
		void quit_game();
		void selected();
		void refresh_menu() { wrefresh(main_menu); };
		void refresh_stats() { wrefresh(stats); };
		void refresh_alert_popup() { wrefresh(alert); };
};


