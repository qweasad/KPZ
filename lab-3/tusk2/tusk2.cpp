#include <iostream>
#include <string>
#include <memory>

using namespace std;

class ICharacter {
public:
    virtual ~ICharacter() = default;
    virtual string describe() const = 0;
};

class Warrior : public ICharacter {
public:
    string describe() const override {
        return "Warrior";
    }
};

class Mage : public ICharacter {
public:
    string describe() const override {
        return "Mage";
    }
};

class Paladin : public ICharacter {
public:
    string describe() const override {
        return "Paladin";
    }
};

class InventoryDecorator : public ICharacter {
protected:
    shared_ptr<ICharacter> character;  
public:
    InventoryDecorator(shared_ptr<ICharacter> c) : character(c) {}
    virtual string describe() const override {
        return character->describe();
    }
};


class Armor : public InventoryDecorator {
    string armorName;
public:
    Armor(shared_ptr<ICharacter> c, const string& name) : InventoryDecorator(c), armorName(name) {}
    string describe() const override {
        return character->describe() + " wearing armor: " + armorName;
    }
};

class Weapon : public InventoryDecorator {
    string weaponName;
public:
    Weapon(shared_ptr<ICharacter> c, const string& name) : InventoryDecorator(c), weaponName(name) {}
    string describe() const override {
        return character->describe() + " wielding weapon: " + weaponName;
    }
};

class Artifact : public InventoryDecorator {
    string artifactName;
public:
    Artifact(shared_ptr<ICharacter> c, const string& name) : InventoryDecorator(c), artifactName(name) {}
    string describe() const override {
        return character->describe() + " carrying artifact: " + artifactName;
    }
};

int main() {
   
    shared_ptr<ICharacter> hero = make_shared<Warrior>();

    hero = make_shared<Armor>(hero, "Steel Plate");
    hero = make_shared<Weapon>(hero, "Sword of Flames");
    hero = make_shared<Artifact>(hero, "Amulet of Health");

    cout << hero->describe() << endl;

    shared_ptr<ICharacter> mage = make_shared<Mage>();
    mage = make_shared<Weapon>(mage, "Staff of Wisdom");
    mage = make_shared<Artifact>(mage, "Ring of Mana");

    cout << mage->describe() << endl;

    return 0;
}
