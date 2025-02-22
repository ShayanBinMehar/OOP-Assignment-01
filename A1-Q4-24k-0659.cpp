#include <iostream>
#include <string>

using namespace std;

const int MAX_USERS = 100;
const int MAX_STOPS = 20;
const int MAX_ROUTES = 10;
const int MAX_VEHICLES = 5;

class Passenger {
private:
    int userID;
    string fullName;
    bool hasPaidFees;
    bool hasTransportPass;
    string designatedStop;

public:
    Passenger(int id, string name) : userID(id), fullName(name), hasPaidFees(false), hasTransportPass(false), designatedStop("") {}

    void processPayment() {
        hasPaidFees = true;
        hasTransportPass = true;
        cout << fullName << " has completed fee payment and received a transport pass.\n";
    }

    void setStop(string stop) {
        designatedStop = stop;
    }

    void checkIn() {
        if (hasTransportPass) {
            cout << fullName << " checked in. Presence recorded.\n";
        } else {
            cout << fullName << " lacks a valid transport pass!\n";
        }
    }

    void showDetails() {
        cout << "User ID: " << userID << ", Name: " << fullName << ", Stop: " << designatedStop << "\n";
    }

    int getUserID() const {
        return userID;
    }
};

class Station {
private:
    string stationID;
    string location;
    Passenger* passengerList[MAX_USERS];
    int totalPassengers;

public:
    Station(string id, string loc) : stationID(id), location(loc), totalPassengers(0) {}

    void enrollPassenger(Passenger* passenger) {
        if (totalPassengers < MAX_USERS) {
            passengerList[totalPassengers++] = passenger;
            passenger->setStop(location);
        } else {
            cout << "Station is at capacity.\n";
        }
    }

    void listPassengers() {
        cout << "Passengers at station " << location << ":\n";
        for (int i = 0; i < totalPassengers; i++) {
            passengerList[i]->showDetails();
        }
    }
};

class Pathway {
private:
    string pathwayID;
    Station* stationList[MAX_STOPS];
    int totalStops;

public:
    Pathway(string id) : pathwayID(id), totalStops(0) {}

    void addStation(Station* station) {
        if (totalStops < MAX_STOPS) {
            stationList[totalStops++] = station;
        } else {
            cout << "Pathway is at capacity.\n";
        }
    }

    void showPathway() {
        cout << "Pathway " << pathwayID << " includes stops:\n";
        for (int i = 0; i < totalStops; i++) {
            cout << " - " << stationList[i] << "\n";
        }
    }
};

class Vehicle {
private:
    string vehicleID;
    Pathway* assignedPathway;
    static const int maxCapacity = 50;

public:
    Vehicle(string id) : vehicleID(id), assignedPathway(nullptr) {}

    void allocatePathway(Pathway* pathway) {
        assignedPathway = pathway;
    }

    void displayPathway() {
        if (assignedPathway) {
            assignedPathway->showPathway();
        } else {
            cout << "No pathway allocated.\n";
        }
    }
};

class TransitSystem {
private:
    Passenger* passengers[MAX_USERS];
    int passengerCount;
    Vehicle* vehicles[MAX_VEHICLES];
    int vehicleCount;
    Pathway* pathways[MAX_ROUTES];
    int pathwayCount;

public:
    TransitSystem() : passengerCount(0), vehicleCount(0), pathwayCount(0) {}

    void addPassenger(int id, string name) {
        if (passengerCount < MAX_USERS) {
            passengers[passengerCount++] = new Passenger(id, name);
        } else {
            cout << "Max passenger limit reached.\n";
        }
    }

    void processFeePayment(int id) {
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i]->getUserID() == id) {
                passengers[i]->processPayment();
                return;
            }
        }
        cout << "Passenger not found!\n";
    }

    void markAttendance(int id) {
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i]->getUserID() == id) {
                passengers[i]->checkIn();
                return;
            }
        }
        cout << "Passenger not found!\n";
    }
};

int main() {
    TransitSystem system;
    system.addPassenger(1, "Ali");
    system.addPassenger(2, "Sara");

    system.processFeePayment(1);
    system.markAttendance(1);
    system.markAttendance(2);

    return 0;
}
