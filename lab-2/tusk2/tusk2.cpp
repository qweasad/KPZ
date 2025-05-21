#include <iostream>
#include <memory>

using namespace std;

class Laptop {
public:
    virtual void info() = 0;
    virtual ~Laptop() {}
};

class Smartphone {
public:
    virtual void info() = 0;
    virtual ~Smartphone() {}
};

class EBook {
public:
    virtual void info() = 0;
    virtual ~EBook() {}
};

class Netbook {
public:
    virtual void info() = 0;
    virtual ~Netbook() {}
};

class IProneLaptop : public Laptop {
public:
    void info() override { cout << "IProne Laptop\n"; }
};

class IProneSmartphone : public Smartphone {
public:
    void info() override { cout << "IProne Smartphone\n"; }
};

class IProneEBook : public EBook {
public:
    void info() override { cout << "IProne E-Book\n"; }
};

class IProneNetbook : public Netbook {
public:
    void info() override { cout << "IProne Netbook\n"; }
};

class KiaomiLaptop : public Laptop {
public:
    void info() override { cout << "Kiaomi Laptop\n"; }
};

class KiaomiSmartphone : public Smartphone {
public:
    void info() override { cout << "Kiaomi Smartphone\n"; }
};

class KiaomiEBook : public EBook {
public:
    void info() override { cout << "Kiaomi E-Book\n"; }
};

class KiaomiNetbook : public Netbook {
public:
    void info() override { cout << "Kiaomi Netbook\n"; }
};

class BalaxyLaptop : public Laptop {
public:
    void info() override { cout << "Balaxy Laptop\n"; }
};

class BalaxySmartphone : public Smartphone {
public:
    void info() override { cout << "Balaxy Smartphone\n"; }
};

class BalaxyEBook : public EBook {
public:
    void info() override { cout << "Balaxy E-Book\n"; }
};

class BalaxyNetbook : public Netbook {
public:
    void info() override { cout << "Balaxy Netbook\n"; }
};

class DeviceFactory {
public:
    virtual unique_ptr<Laptop> createLaptop() = 0;
    virtual unique_ptr<Smartphone> createSmartphone() = 0;
    virtual unique_ptr<EBook> createEBook() = 0;
    virtual unique_ptr<Netbook> createNetbook() = 0;
    virtual ~DeviceFactory() {}
};

class IProneFactory : public DeviceFactory {
public:
    unique_ptr<Laptop> createLaptop() override { return make_unique<IProneLaptop>(); }
    unique_ptr<Smartphone> createSmartphone() override { return make_unique<IProneSmartphone>(); }
    unique_ptr<EBook> createEBook() override { return make_unique<IProneEBook>(); }
    unique_ptr<Netbook> createNetbook() override { return make_unique<IProneNetbook>(); }
};

class KiaomiFactory : public DeviceFactory {
public:
    unique_ptr<Laptop> createLaptop() override { return make_unique<KiaomiLaptop>(); }
    unique_ptr<Smartphone> createSmartphone() override { return make_unique<KiaomiSmartphone>(); }
    unique_ptr<EBook> createEBook() override { return make_unique<KiaomiEBook>(); }
    unique_ptr<Netbook> createNetbook() override { return make_unique<KiaomiNetbook>(); }
};

class BalaxyFactory : public DeviceFactory {
public:
    unique_ptr<Laptop> createLaptop() override { return make_unique<BalaxyLaptop>(); }
    unique_ptr<Smartphone> createSmartphone() override { return make_unique<BalaxySmartphone>(); }
    unique_ptr<EBook> createEBook() override { return make_unique<BalaxyEBook>(); }
    unique_ptr<Netbook> createNetbook() override { return make_unique<BalaxyNetbook>(); }
};

void demoFactory(DeviceFactory& factory, const string& brandName) {
    cout << "=== Devices from " << brandName << " ===\n";
    factory.createLaptop()->info();
    factory.createSmartphone()->info();
    factory.createEBook()->info();
    factory.createNetbook()->info();
    cout << endl;
}

int main() {
    IProneFactory iprone;
    KiaomiFactory kiaomi;
    BalaxyFactory balaxy;

    demoFactory(iprone, "IProne");
    demoFactory(kiaomi, "Kiaomi");
    demoFactory(balaxy, "Balaxy");

    return 0;
}
