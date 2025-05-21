#include <iostream>
#include <string>

using namespace std;

class CommandCentre {
public:
    virtual void notify(const string& sender, const string& event) = 0;
};

class Aircraft;
class Runway;

class ConcreteCommandCentre : public CommandCentre {
private:
    Aircraft* aircraft = nullptr;
    Runway* runway = nullptr;

public:
    void setAircraft(Aircraft* a) { aircraft = a; }
    void setRunway(Runway* r) { runway = r; }

    void notify(const string& sender, const string& event) override;
};

class Aircraft {
private:
    CommandCentre* mediator;
    bool isLandingAllowed = false;

public:
    Aircraft(CommandCentre* mediator) : mediator(mediator) {}

    void requestLanding() {
        cout << "Aircraft: ����� �� ����� �������.\n";
        mediator->notify("Aircraft", "requestLanding");
    }

    void land() {
        if (isLandingAllowed) {
            cout << "Aircraft: ������� ���������. ���� �� �������.\n";
            mediator->notify("Aircraft", "landed");
        }
        else {
            cout << "Aircraft: ������� �� ���������.\n";
        }
    }

    void allowLanding() {
        isLandingAllowed = true;
    }
};

class Runway {
private:
    CommandCentre* mediator;
    bool isAvailable = true;

public:
    Runway(CommandCentre* mediator) : mediator(mediator) {}

    void freeRunway() {
        isAvailable = true;
        cout << "Runway: �����-��������� ����� �����.\n";
        mediator->notify("Runway", "free");
    }

    void occupyRunway() {
        isAvailable = false;
        cout << "Runway: �����-��������� ����� �������.\n";
    }

    bool available() const {
        return isAvailable;
    }
};

void ConcreteCommandCentre::notify(const string& sender, const string& event) {
    if (sender == "Aircraft" && event == "requestLanding") {
        if (runway && runway->available()) {
            cout << "CommandCentre: �����-��������� ����� �����. �������� �������.\n";
            aircraft->allowLanding();
            runway->occupyRunway();
        }
        else {
            cout << "CommandCentre: ������� ����������, ����� �������.\n";
        }
    }
    else if (sender == "Aircraft" && event == "landed") {
        cout << "CommandCentre: ˳��� ������ �����������.\n";
        runway->freeRunway();
    }
    else if (sender == "Runway" && event == "free") {
        cout << "CommandCentre: ����� �����, ������ ������.\n";
    }
}

int main() {
    ConcreteCommandCentre commandCentre;

    Aircraft aircraft(&commandCentre);
    Runway runway(&commandCentre);

    commandCentre.setAircraft(&aircraft);
    commandCentre.setRunway(&runway);

    aircraft.requestLanding();  
    aircraft.land();   

    aircraft.requestLanding();
    aircraft.land();

    return 0;
}

