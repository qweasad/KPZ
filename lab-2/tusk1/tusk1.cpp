#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class Subscription {
public:
    virtual ~Subscription() {}
    virtual void showInfo() = 0;
};


class DomesticSubscription : public Subscription {
public:
    void showInfo() override {
        cout << "Domestic Subscription\n";
        cout << "Price: $5/month\n";
        cout << "Period: 1 month\n";
        cout << "Channels: National channels only\n\n";
    }
};

class EducationalSubscription : public Subscription {
public:
    void showInfo() override {
        cout << "Educational Subscription\n";
        cout << "Price: $8/month\n";
        cout << "Period: 3 months\n";
        cout << "Channels: Educational and National\n\n";
    }
};

class PremiumSubscription : public Subscription {
public:
    void showInfo() override {
        cout << "Premium Subscription\n";
        cout << "Price: $15/month\n";
        cout << "Period: 6 months\n";
        cout << "Channels: All channels, movies, and sports\n\n";
    }
};

class SubscriptionCreator {
public:
    virtual ~SubscriptionCreator() {}
    virtual unique_ptr<Subscription> createSubscription(const string& type) = 0;
};


class WebSite : public SubscriptionCreator {
public:
    unique_ptr<Subscription> createSubscription(const string& type) override {
        if (type == "domestic") return make_unique<DomesticSubscription>();
        if (type == "educational") return make_unique<EducationalSubscription>();
        if (type == "premium") return make_unique<PremiumSubscription>();
        return nullptr;
    }
};

class MobileApp : public SubscriptionCreator {
public:
    unique_ptr<Subscription> createSubscription(const string& type) override {
        if (type == "domestic") return make_unique<DomesticSubscription>();
        if (type == "premium") return make_unique<PremiumSubscription>();
        return nullptr; 
    }
};

class ManagerCall : public SubscriptionCreator {
public:
    unique_ptr<Subscription> createSubscription(const string& type) override {
        if (type == "educational") return make_unique<EducationalSubscription>();
        if (type == "premium") return make_unique<PremiumSubscription>();
        return nullptr;
    };


    int main() {
        unique_ptr<SubscriptionCreator> site = make_unique<WebSite>();
        unique_ptr<SubscriptionCreator> app = make_unique<MobileApp>();
        unique_ptr<SubscriptionCreator> manager = make_unique<ManagerCall>();

        auto s1 = site->createSubscription("premium");
        auto s2 = app->createSubscription("domestic");
        auto s3 = manager->createSubscription("educational");

        if (s1) s1->showInfo();
        if (s2) s2->showInfo();
        if (s3) s3->showInfo();

        return 0;
    }

};