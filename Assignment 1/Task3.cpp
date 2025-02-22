#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    string model;
    double rentalPricePerDay;
    string licenceRequired;

    Vehicle(string M, double R, string L) : model(M), rentalPricePerDay(R), licenceRequired(L) {}
};

class User {
public:
    int age;
    long int contactNO;
    string licenceType;
    int userID;
    string name;

    User(string n, int a, long int c, string l, int u) 
        : name(n), age(a), contactNO(c), licenceType(l), userID(u) {}

    void updateUser(string name, int age, long int contactNO, string licenceType, int userID) {
        this->name = name;
        this->age = age;
        this->contactNO = contactNO;
        this->licenceType = licenceType;
        this->userID = userID;
    }
};

bool isEligible(User* U, Vehicle* V) {
    return U->licenceType == V->licenceRequired;
}

void displayVehicles(Vehicle** V, int VehicleCount) {
    cout << "Available Vehicles are..." << endl;
    for (int i = 0; i < VehicleCount; i++) {
        cout << i + 1 << ". Vehicle model: " << V[i]->model << endl;
        cout << "   Rental price: $" << V[i]->rentalPricePerDay << " per day" << endl;
        cout << "   Licence required: " << V[i]->licenceRequired << endl;
        cout<<endl;
    }
}

int main() {
    const int size = 5;
    Vehicle* V[size];
    int VehicleCount = 0;

    V[VehicleCount++] = new Vehicle("Cultus", 450.00, "Full");
    V[VehicleCount++] = new Vehicle("Corolla", 500.00, "Learner");
    V[VehicleCount++] = new Vehicle("Mira", 400.00, "Intermediate");

    string name, licenceType;
    long int contactNO;
    int age, userID;

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter Your contact NO: ";
    cin >> contactNO;
    cout << "Enter your licence type: ";
    cin.ignore(); 
    getline(cin, licenceType);
    cout << "Enter user ID: ";
    cin >> userID;

    User* U = new User(name, age, contactNO, licenceType, userID);

    displayVehicles(V, VehicleCount);

    int vehiclesNo;
    cout << "Enter the number of the vehicle you want to rent: ";
    cin >> vehiclesNo;

    if (vehiclesNo > 0 && vehiclesNo <= VehicleCount) {
        Vehicle* V2 = V[vehiclesNo - 1];
        if (isEligible(U, V2)) {
            cout << "Successfully rented the car " << V2->model << endl;
            cout << "Rental price: $" << V2->rentalPricePerDay << " per day." << endl;
        } else {
            cout << "You are not eligible to rent this vehicle." << endl;
        }
    } else {
        cout << "Invalid choice! Please enter a valid vehicle number." << endl;
    }

    // Update user details
    cout << "Update your details..." << endl;
    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter Your contact NO: ";
    cin >> contactNO;
    cout << "Enter your licence type: ";
    cin.ignore(); 
    getline(cin, licenceType);
    cout << "Enter user ID: ";
    cin >> userID;

    U->updateUser(name, age, contactNO, licenceType, userID);
    cout << "Your details have been updated." << endl;

    for (int i = 0; i < VehicleCount; i++) {
        delete V[i];
    }
    delete U;

    return 0;
}
