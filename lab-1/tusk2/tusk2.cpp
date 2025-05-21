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
    std::cout << "��������� ����: " << price << std::endl;

    Product product("�����", price);
    std::cout << "�������: " << product << std::endl;

    std::time_t now = std::time(nullptr);
    std::time_t ten_days_ago = now - 10 * 24 * 60 * 60;
    Warehouse warehouse(product, "��", 200, ten_days_ago);
    std::cout << "�����: " << warehouse << std::endl;

    Reporting reporting;

    reporting.RegisterArrival(&warehouse, 50, now);
    std::cout << "\nϳ��� �������� 50 ��:" << std::endl;
    std::cout << warehouse << std::endl;

    reporting.RegisterShipment(&warehouse, 100);
    std::cout << "\nϳ��� ������������ 100 ��:" << std::endl;
    std::cout << warehouse << std::endl;

    std::cout << "\n��� �� ��������������:" << std::endl;
    reporting.InventoryReport();

    product.DecreasePrice(10, 0);
    std::cout << "\nϳ��� �������� ����:" << std::endl;
    std::cout << product << std::endl;

    return 0;
}
