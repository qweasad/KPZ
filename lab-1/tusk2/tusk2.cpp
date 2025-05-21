= #include <iostream>
#include <ctime>
#include "tusk1.cpp"


std::string formatDate(const std::time_t & time)
{
    std::tm* tm_ptr = std::localtime(&time);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_ptr);
    return std::string(buffer);
}

int main()
{
    Money price(100, 50);
    std::cout << "Початкова ціна: " << price << std::endl;

    Product product("Цукор", price);
    std::cout << "Продукт: " << product << std::endl;

    std::time_t now = std::time(nullptr);
    std::time_t ten_days_ago = now - 10 * 24 * 60 * 60;
    Warehouse warehouse(product, "кг", 200, ten_days_ago);
    std::cout << "Склад: " << warehouse << std::endl;

    Reporting reporting;

    reporting.RegisterArrival(&warehouse, 50, now);
    std::cout << "\nПісля прибутку 50 кг:" << std::endl;
    std::cout << warehouse << std::endl;

    reporting.RegisterShipment(&warehouse, 100);
    std::cout << "\nПісля відвантаження 100 кг:" << std::endl;
    std::cout << warehouse << std::endl;

    std::cout << "\nЗвіт по інвентаризації:" << std::endl;
    reporting.InventoryReport();

    product.DecreasePrice(10, 0);
    std::cout << "\nПісля зниження ціни:" << std::endl;
    std::cout << product << std::endl;

    return 0;
}
