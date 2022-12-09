#include <fstream>
#include <sstream>

#include "shop.h"

std::string Upgrade :: print_data()
{
    std::stringstream buff;
    if(money_per > 0)
    {
        buff<<name<<", Price: "<<price<<"$, + "<<money_per<<"$/click";
    }
    std::string tmp = buff.str();
    return tmp;
}

void Upgrade :: set(std::string name_d, int price_d, int money_per_d)
{
    name = name_d;
    price = price_d;
    money_per = money_per_d;
}

void Shop::generate_items()
{
    upgrades.clear();
    Upgrade upgrade_tmp;
    std::string name;
    int price,increase;
    std::ifstream file;
    file.open("shop.dat");
    if(file.is_open())
    {
        while(file)
        {
            file>>name;
            file>>price;
            file>>increase;
            upgrade_tmp.set(name, price, increase);
            upgrades.push_back(upgrade_tmp);
    	}
    }
    file.close();
}

int* Shop :: get_upgrades(int id)
{
    int* col = new int[3];
    col[1]=upgrades[id].get_price();
    col[2]=upgrades[id].get_money_per();

    return col;
}

std::string Shop::upgrade_io(int id)
{
    return upgrades[id].print_data();
}
