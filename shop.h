#include <iostream>
#include <vector>

class Item
{
	public:
		std::string name;
		int price;
		int get_price() { return price; };
};

class Upgrade : public Item
{
    private:
		int money_per;
    public:
		void set(std::string name_d, int price_d, int money_per_d);
		std::string print_data();
		int get_money_per() { return money_per; };
};

class Shop
{
    private:
		std::vector < Upgrade > upgrades;
    public:
		std::string upgrade_io(int id);
		void generate_items();
		int* get_upgrades(int id);
		int get_upgrades_size() { return upgrades.size(); };
};

