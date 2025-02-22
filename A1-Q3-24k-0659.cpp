#include <iostream>
#include <string>

using namespace std;

struct Client {
    int id;
    string fullName;
    int yearsOld;
    string permitType;
    string phoneNumber;
};

class Transport {
public:
    string type;
    double costPerDay;
    string neededPermit;

    Transport(const string& type, double cost, const string& permit)
        : type(type), costPerDay(cost), neededPermit(permit) {}

    void showInfo() const {
        cout << "Vehicle: " << type << ", Daily Rate: $" << costPerDay;
        cout << ", Required Permit: " << neededPermit << endl;
    }
};

int main() {
    Client activeClient;
    Transport* vehicleOptions[3];

    vehicleOptions[0] = new Transport("Sedan", 50.0, "Advanced");
    vehicleOptions[1] = new Transport("Compact", 30.0, "Standard");
    vehicleOptions[2] = new Transport("Moped", 20.0, "Basic");

    cout << "Client Registration:" << endl;
    cout << "Enter Client ID: ";
    
    cin >> activeClient.id;
    cout << "Enter Full Name: ";
    
    cin.ignore();
    getline(cin, activeClient.fullName);
    
    cout << "Enter Age: ";
    cin >> activeClient.yearsOld;
    
    cout << "Enter Permit Type (Basic, Standard, Advanced): ";
    cin.ignore();
    
    getline(cin, activeClient.permitType);
    cout << "Enter Phone Number: ";
    getline(cin, activeClient.phoneNumber);

    cout << "\nAvailable Vehicles:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ". ";
        vehicleOptions[i]->showInfo();
    }

    int choice;
    cout << "\nSelect vehicle number to rent: ";
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        Transport* chosenVehicle = vehicleOptions[choice - 1];
        if (activeClient.permitType == chosenVehicle->neededPermit ||
            (activeClient.permitType == "Advanced" && chosenVehicle->neededPermit == "Standard") ||
            (activeClient.permitType == "Advanced" && chosenVehicle->neededPermit == "Basic") ||
            (activeClient.permitType == "Standard" && chosenVehicle->neededPermit == "Basic")) {
        
            cout << "Booking Confirmed!" << endl;
            cout << "You have selected: ";                
            chosenVehicle->showInfo();
        } 
        else {
            cout << "Sorry, you are not authorized to rent this vehicle." << endl;
        }
    } 
    else {
        cout << "Invalid choice." << endl;
    }

    cout << "\nUpdate Client Information:" << endl;
    cout << "Enter updated Age: ";
    cin >> activeClient.yearsOld;
    cout << "Enter updated Permit Type (Basic, Standard, Advanced): ";
    cin.ignore();
    getline(cin, activeClient.permitType);
    cout << "Information successfully updated." << endl;

    for (int i = 0; i < 3; ++i) {
        delete vehicleOptions[i];
    }

    return 0;
}