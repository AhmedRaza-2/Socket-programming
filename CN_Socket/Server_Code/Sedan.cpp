#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Sedan.h"
#include "Car.h"
using namespace std;

Sedan::Sedan() : Car() {
    trunk_capacity = 0.0;
    fuel_efficiency = 0.0;
}
Sedan::Sedan(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, float trunk_capacity, float fuel_efficiency)
    : Car(car_id, car_make, car_model, car_price, car_seating_capacity, car_ground_clearance, is_car_available) {
    this->trunk_capacity = trunk_capacity;
    this->fuel_efficiency = fuel_efficiency;
}
Sedan::Sedan(const Sedan& obj) : Car(obj) {
    this->trunk_capacity = obj.trunk_capacity;
    this->fuel_efficiency = obj.fuel_efficiency;
}
Sedan::~Sedan() {}
void Sedan::set_trunk_capacity(float trunk_capacity) { this->trunk_capacity = trunk_capacity; }
void Sedan::set_fuel_efficiency(float fuel_efficiency) { this->fuel_efficiency = fuel_efficiency; }
float Sedan::get_trunk_capacity() const { return trunk_capacity; }
float Sedan::get_fuel_efficiency() const { return fuel_efficiency; }
string Sedan::toString() {
    return Car::tostring() + "\t" + to_string(trunk_capacity) + "\t" + to_string(fuel_efficiency);
}
void Sedan::store_to_file() {
    ofstream fout("Sedan.txt", ios::app);
    if (fout.is_open()) {
        fout << toString() << endl;
        fout.close();
        cout << "\nData Stored To Sedan File\n";
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}
void Sedan::view_from_file() {
    ifstream fin("Sedan.txt");
    if (fin.is_open()) {
        cout << left
            << setw(8) << "ID"
            << setw(15) << "Make"
            << setw(15) << "Model"
            << setw(10) << "Price"
            << setw(8) << "Seats"
            << setw(10) << "Clearance"
            << setw(12) << "Available"
            << setw(15) << "TrunkCap"
            << setw(15) << "FuelEff" << endl;
        cout << string(110, '-') << endl;
        int car_id, car_seating_capacity, car_ground_clearance;
        string car_make, car_model, availability;
        float car_price, trunk_capacity, fuel_efficiency;
        bool any = false;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> trunk_capacity >> fuel_efficiency;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << left
                << setw(8) << car_id
                << setw(15) << car_make
                << setw(15) << car_model
                << setw(10) << fixed << setprecision(2) << car_price
                << setw(8) << car_seating_capacity
                << setw(10) << car_ground_clearance
                << setw(12) << availability
                << setw(15) << trunk_capacity
                << setw(15) << fuel_efficiency << endl;
            any = true;
        }
        if (!any) cout << "No sedan records found.\n";
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Sedan::search() {
    int id;
    cout << "Enter the ID of the Sedan to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Sedan.txt");
    if (fin.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance;
        string car_make, car_model, availability;
        float car_price, trunk_capacity, fuel_efficiency;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> trunk_capacity >> fuel_efficiency;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (car_id == id) {
                found = true;
                cout << "\nCar ID: " << car_id
                    << "\nCar Make: " << car_make
                    << "\nCar Model: " << car_model
                    << "\nCar Price: " << car_price
                    << "\nCar Seating Capacity: " << car_seating_capacity
                    << "\nCar Ground Clearance: " << car_ground_clearance
                    << "\nCar Availability: " << availability
                    << "\nCar Trunk Capacity: " << trunk_capacity
                    << "\nCar Fuel Efficiency: " << fuel_efficiency << endl;
                break;
            }
        }
        if (!found) cout << "Sedan with ID " << id << " not found." << endl;
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Sedan::update() {
    int id;
    cout << "Enter the ID of the Sedan to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ifstream fin("Sedan.txt");
    ofstream fout("temp.txt");

    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, trunk_capacity;
        string car_make, car_model, availability, fuel_type;
        float car_price;

        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> trunk_capacity;
            fin.ignore();
            getline(fin, fuel_type);

            if (car_id == id) {
                found = true;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline

                cout << "Enter new Car Make: ";
                getline(cin, car_make);

                cout << "Enter new Car Model: ";
                getline(cin, car_model);

                cout << "Enter new Car Price: ";
                while (!(cin >> car_price)) {
                    cout << "Invalid input. Enter price: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

                cout << "Enter new Car Seating Capacity: ";
                while (!(cin >> car_seating_capacity)) {
                    cout << "Invalid input. Enter seats: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

                cout << "Enter new Car Ground Clearance: ";
                while (!(cin >> car_ground_clearance)) {
                    cout << "Invalid input. Enter clearance: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

                cout << "Enter new Car Availability (Yes/No): ";
                getline(cin, availability);

                cout << "Enter new Trunk Capacity: ";
                while (!(cin >> trunk_capacity)) {
                    cout << "Invalid input. Enter trunk capacity: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

                cout << "Enter new Fuel Type: ";
                getline(cin, fuel_type);
            }

            fout << car_id << "\t" << car_make << "\t" << car_model << "\t"
                 << car_price << "\t" << car_seating_capacity << "\t"
                 << car_ground_clearance << "\t" << availability << "\t"
                 << trunk_capacity << "\t" << fuel_type << endl;
        }

        fin.close();
        fout.close();
        remove("Sedan.txt");
        rename("temp.txt", "Sedan.txt");

        if (!found)
            cout << "Sedan with ID " << id << " not found." << endl;
        else
            cout << "Sedan updated successfully." << endl;
    } else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}

void Sedan::del() {
    int id;
    cout << "Enter the ID of the Sedan to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Sedan.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance;
        string car_make, car_model, availability;
        float car_price, trunk_capacity, fuel_efficiency;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> trunk_capacity >> fuel_efficiency;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (car_id == id) found = true;
            else fout << car_id << "\t" << car_make << "\t" << car_model << "\t" << car_price << "\t" << car_seating_capacity << "\t" << car_ground_clearance << "\t" << availability << "\t" << trunk_capacity << "\t" << fuel_efficiency << endl;
        }
        fin.close(); fout.close();
        remove("Sedan.txt"); rename("temp.txt", "Sedan.txt");
        if (!found) cout << "Sedan with ID " << id << " not found." << endl;
        else cout << "Sedan with ID " << id << " deleted successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}
void Sedan::menu(Sedan& obj) {
    int choice;
    do {
        cout << "\n========== Sedan Management ==========\n";
        cout << "1. Add Sedan\n";
        cout << "2. View All Sedans\n";
        cout << "3. Update Sedan\n";
        cout << "4. Search Sedan\n";
        cout << "5. Delete Sedan\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice (1-6): ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1: cin >> obj; break;
        case 2: obj.view_from_file(); break;
        case 3: obj.update(); break;
        case 4: obj.search(); break;
        case 5: obj.del(); break;
        case 6: cout << "Returning to main menu...\n"; break;
        default: cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 6);
}
ostream& operator<<(ostream& cout, const Sedan& obj) {
    cout << "Car ID : " << obj.get_car_id() << endl;
    cout << "Car Make : " << obj.get_car_make() << endl;
    cout << "Car Model : " << obj.get_car_model() << endl;
    cout << "Car Price : " << obj.get_car_price() << endl;
    cout << "Car Seating Capacity : " << obj.get_car_seating_capacity() << endl;
    cout << "Car Ground Clearance : " << obj.get_car_ground_clearance() << endl;
    cout << "Car Availability : " << obj.get_car_availability() << endl;
    cout << "Car Trunk Capacity : " << obj.get_trunk_capacity() << endl;
    cout << "Car Fuel Efficiency : " << obj.get_fuel_efficiency() << endl;
    return cout;
}
istream& operator>>(istream& cin, Sedan& obj) {
    int car_id, car_seating_capacity, car_ground_clearance;
    string car_make, car_model, availability;
    float car_price, trunk_capacity, fuel_efficiency;

    // Car ID
    do {
        cout << "Enter Car ID (positive integer): ";
        if (!(cin >> car_id) || car_id <= 0) {
            cout << "Invalid input. Enter a positive integer for Car ID.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    cin.ignore();

    // Car Make
    do {
        cout << "Enter Car Make: ";
        getline(cin, car_make);
        if (car_make.empty()) cout << "Car Make cannot be empty.\n";
    } while (car_make.empty());

    // Car Model
    do {
        cout << "Enter Car Model: ";
        getline(cin, car_model);
        if (car_model.empty()) cout << "Car Model cannot be empty.\n";
    } while (car_model.empty());

    // Car Price
    do {
        cout << "Enter Car Price (positive number): ";
        if (!(cin >> car_price) || car_price <= 0) {
            cout << "Invalid input. Enter a positive number for Car Price.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Car Seating Capacity
    do {
        cout << "Enter Car Seating Capacity (positive integer): ";
        if (!(cin >> car_seating_capacity) || car_seating_capacity <= 0) {
            cout << "Invalid input. Enter a positive integer for Seating Capacity.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Car Ground Clearance
    do {
        cout << "Enter Car Ground Clearance (positive integer): ";
        if (!(cin >> car_ground_clearance) || car_ground_clearance <= 0) {
            cout << "Invalid input. Enter a positive integer for Ground Clearance.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    cin.ignore();

    // Car Availability
    do {
        cout << "Enter Car Availability (yes/no): ";
        getline(cin, availability);
        if (availability.empty() || (availability != "yes" && availability != "no")) {
            cout << "Invalid input. Enter 'yes' or 'no'.\n";
        }
    } while (availability.empty() || (availability != "yes" && availability != "no"));

    // Trunk Capacity
    do {
        cout << "Enter Trunk Capacity (positive number): ";
        if (!(cin >> trunk_capacity) || trunk_capacity < 0) {
            cout << "Invalid input. Enter a non-negative number for Trunk Capacity.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Fuel Efficiency
    do {
        cout << "Enter Fuel Efficiency (positive number): ";
        if (!(cin >> fuel_efficiency) || fuel_efficiency < 0) {
            cout << "Invalid input. Enter a non-negative number for Fuel Efficiency.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    obj.set_car_id(car_id);
    obj.set_car_make(car_make);
    obj.set_car_model(car_model);
    obj.set_car_price(car_price);
    obj.set_car_seating_capacity(car_seating_capacity);
    obj.set_car_ground_clearance(car_ground_clearance);
    obj.set_car_availability(availability);
    obj.set_trunk_capacity(trunk_capacity);
    obj.set_fuel_efficiency(fuel_efficiency);
    obj.store_to_file();
    return cin;
}
