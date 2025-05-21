#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Character {
public:
    string name;
    float height;
    string build;
    string hairColor;
    string eyeColor;
    string outfit;
    vector<string> inventory;
    vector<string> deeds;

    void show() const {
        cout << "Character: " << name << "\n";
        cout << "Height: " << height << "m\n";
        cout << "Build: " << build << "\n";
        cout << "Hair: " << hairColor << ", Eyes: " << eyeColor << "\n";
        cout << "Outfit: " << outfit << "\n";
        cout << "Inventory: ";
        for (const auto& item : inventory) cout << item << ", ";
        cout << "\nDeeds: ";
        for (const auto& deed : deeds) cout << deed << ", ";
        cout << "\n--------------------------\n";
    }
};

template <typename Derived>
class CharacterBuilderBase {
protected:
    unique_ptr<Character> character;
public:
    CharacterBuilderBase() { character = make_unique<Character>(); }
    virtual ~CharacterBuilderBase() = default;

    Derived& setName(const string& name) {
        character->name = name;
        return static_cast<Derived&>(*this);
    }

    Derived& setHeight(float h) {
        character->height = h;
        return static_cast<Derived&>(*this);
    }

    Derived& setBuild(const string& b) {
        character->build = b;
        return static_cast<Derived&>(*this);
    }

    Derived& setHairColor(const string& color) {
        character->hairColor = color;
        return static_cast<Derived&>(*this);
    }

    Derived& setEyeColor(const string& color) {
        character->eyeColor = color;
        return static_cast<Derived&>(*this);
    }

    Derived& setOutfit(const string& outfit) {
        character->outfit = outfit;
        return static_cast<Derived&>(*this);
    }

    Derived& addItem(const string& item) {
        character->inventory.push_back(item);
        return static_cast<Derived&>(*this);
    }

    unique_ptr<Character> build() {
        return move(character);
    }
};

class HeroBuilder : public CharacterBuilderBase<HeroBuilder> {
public:
    HeroBuilder& addGoodDeed(const string& deed) {
        character->deeds.push_back("Good: " + deed);
        return *this;
    }
};

class EnemyBuilder : public CharacterBuilderBase<EnemyBuilder> {
public:
    EnemyBuilder& addEvilDeed(const string& deed) {
        character->deeds.push_back("Evil: " + deed);
        return *this;
    }
};

class Director {
public:
    void createHero(HeroBuilder& builder) {
        builder.setName("Aeloria")
            .setHeight(1.75f)
            .setBuild("Athletic")
            .setHairColor("Silver")
            .setEyeColor("Emerald")
            .setOutfit("Mage Robe")
            .addItem("Staff of Wisdom")
            .addItem("Amulet of Light")
            .addGoodDeed("Saved the village")
            .addGoodDeed("Healed the wounded");
    }

    void createEnemy(EnemyBuilder& builder) {
        builder.setName("Dreadthorn")
            .setHeight(2.1f)
            .setBuild("Muscular")
            .setHairColor("Black")
            .setEyeColor("Red")
            .setOutfit("Dark Armor")
            .addItem("Axe of Doom")
            .addItem("Ring of Shadows")
            .addEvilDeed("Destroyed the temple")
            .addEvilDeed("Cursed the forest");
    }
};

int main() {
    Director director;

    HeroBuilder heroBuilder;
    director.createHero(heroBuilder);
    unique_ptr<Character> hero = heroBuilder.build();
    hero->show();

    EnemyBuilder enemyBuilder;
    director.createEnemy(enemyBuilder);
    unique_ptr<Character> enemy = enemyBuilder.build();
    enemy->show();

    return 0;
}
