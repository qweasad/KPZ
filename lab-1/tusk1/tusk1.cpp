#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

class Money {
private:
    int griv;
    int cop;

    void Normalize() {
        if (cop >= 100) {
            griv += cop / 100;
            cop %= 100;
        }
        else if (cop < 0) {
            int borrow = (abs(cop) + 99) / 100;
            griv -= borrow;
            cop += borrow * 100;
        }
    }

public:
    Money(int w = 0, int f = 0) : griv(w), cop(f) {
        Normalize();
    }

    void SetValue(int w, int f) {
        griv = w;
        cop = f;
        Normalize();
    }

    int GetWhole() const { return griv; }
    int GetFraction() const { return cop; }

    std::string ToString() const {
        char buffer[20];
        sprintf(buffer, "%d,%02d", griv, cop);
        return std::string(buffer);
    }
};

class Product {
private:
    std::string name;
    Money price;

public:
    Product(const std::string& n, const Money& p) : name(n), price(p) {}

    void DecreasePrice(int w, int f) {
        int totalCurrent = price.GetWhole() * 100 + price.GetFraction();
        int totalDecrease = w * 100 + f;
        int totalNew = totalCurrent - totalDecrease;
        if (totalNew < 0) totalNew = 0;
        price.SetValue(totalNew / 100, totalNew % 100);
    }

    std::string GetName() const { return name; }
    Money GetPrice() const { return price; }

    std::string ToString() const {
        return name + " - " + price.ToString() + " грн";
    }
};

class Warehouse {
public:
    Product product;
    std::string unit;
    int quantity;
    std::time_t last_Delivery_Date;

    Warehouse(const Product& p, const std::string& u, int q, std::time_t date)
        : product(p), unit(u), quantity(q), last_Delivery_Date(date) {
    }

    std::string ToString() const {
        char buffer[100];
        std::tm* tm_ptr = std::localtime(&last_Delivery_Date);
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", tm_ptr);

        return product.GetName() + ", " + std::to_string(quantity) + " " + unit +
            ", ціна за одиницю: " + product.GetPrice().ToString() +
            ", останнє надходження: " + std::string(buffer);
    }
};

class Reporting {
private:
    std::vector<Warehouse*> warehouses;

public:
    void RegisterArrival(Warehouse* wh, int quantity, std::time_t deliveryDate) {
        wh->quantity += quantity;
        wh->last_Delivery_Date = deliveryDate;
        if (std::find(warehouses.begin(), warehouses.end(), wh) == warehouses.end()) {
            warehouses.push_back(wh);
        }
    }

    void RegisterShipment(Warehouse* wh, int quantity) {
        if (wh->quantity < quantity) {
            std::cerr << "Неможливо відвантажити більше, ніж є на складі.\n";
            return;
        }
        wh->quantity -= quantity;
    }

    void InventoryReport() const {
        std::cout << "Звіт по інвентаризації:" << std::endl;
        for (const auto& wh : warehouses) {
            std::cout << *wh << std::endl;
        }
    }
};


std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << m.ToString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.ToString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& w) {
    os << w.ToString();
    return os;
}
