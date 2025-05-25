#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Hatchback.h"
#include "Car.h"
using namespace std;

Hatchback::Hatchback() : Car() {
    cargo_space = 0;
    fuel_type = "n/a";
}
Hatchback::Hatchback(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, int cargo_space, string fuel_type)
    : Car(car_id, car_make, car_model, car_price, car_seating_capacity, car_ground_clearance, is_car_available) {
    this->cargo_space = cargo_space;
    this->fuel_type = fuel_type;
}
Hatchback::Hatchback(const Hatchback& obj) : Car(obj) {
    this->cargo_space = obj.cargo_space;
    this->fuel_type = obj.fuel_type;
}
Hatchback::~Hatchback() {}
void Hatchback::set_cargo_space(int cargo_space) { this->cargo_space = cargo_space; }
void Hatchback::set_fuel_type(string fuel_type) { this->fuel_type = fuel_type; }
int Hatchback::get_cargo_space() const { return cargo_space; }
string Hatchback::get_fuel_type() const { return fuel_type; }
string Hatchback::toString() {
    return Car::tostring() + "\t" + to_string(cargo_space) + "\t" + fuel_type;
}
void Hatchback::store_to_file() {
    ofstream fout("Hatchback.txt", ios::app);
    if (fout.is_open()) {
        fout << toString() << endl;
        fout.close();
        cout << "\nData Stored To Hatchback File\n";
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}
void Hatchback::view_from_file() {
    ifstream fin("Hatchback.txt");
    if (fin.is_open()) {
        cout << left
            << setw(8) << "ID"
            << setw(15) << "Make"
            << setw(15) << "Model"
            << setw(10) << "Price"
            << setw(8) << "Seats"
            << setw(10) << "Clearance"
            << setw(12) << "Available"
            << setw(12) << "Cargo"
            << setw(12) << "FuelType" << endl;
        cout << string(100, '-') << endl;
        int car_id, car_seating_capacity, car_ground_clearance, cargo_space;
        string car_make, car_model, availability, fuel_type;
        float car_price;
        bool any = false;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> cargo_space;
            fin.ignore();
            getline(fin, fuel_type);
            cout << left
                << setw(8) << car_id
                << setw(15) << car_make
                << setw(15) << car_model
                << setw(10) << fixed << setprecision(2) << car_price
                << setw(8) << car_seating_capacity
                << setw(10) << car_ground_clearance
                << setw(12) << availability
                << setw(12) << cargo_space
                << setw(12) << fuel_type << endl;
            any = true;
        }
        if (!any) cout << "No hatchback records found.\n";
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Hatchback::search() {
    int id;
    cout << "Enter the ID of the Hatchback to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Hatchback.txt");
    if (fin.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, cargo_space;
        string car_make, car_model, availability, fuel_type;
        float car_price;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> cargo_space;
            fin.ignore();
            getline(fin, fuel_type);
            if (car_id == id) {
                found = true;
                cout << "\nCar ID: " << car_id
                    << "\nCar Make: " << car_make
                    << "\nCar Model: " << car_model
                    << "\nCar Price: " << car_price
                    << "\nCar Seating Capacity: " << car_seating_capacity
                    << "\nCar Ground Clearance: " << car_ground_clearance
                    << "\nCar Availability: " << availability
                    << "\nCar Cargo Space: " << cargo_space
                    << "\nCar Fuel Type: " << fuel_type << endl;
                break;
            }
        }
        if (!found) cout << "Hatchback with ID " << id << " not found." << endl;
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Hatchback::update() {
    int id;
    cout << "Enter the ID of the Hatchback to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Hatchback.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, cargo_space;
        string car_make, car_model, availability, fuel_type;
        float car_price;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> cargo_space;
            fin.ignore();
            getline(fin, fuel_type);
            if (car_id == id) {
                found = true;
                cout << "Enter new Car Make: "; cin.ignore(); getline(cin, car_make);
                cout << "Enter new Car Model: "; getline(cin, car_model);
                cout << "Enter new Car Price: "; while (!(cin >> car_price)) { cout << "Invalid input. Enter price: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                cout << "Enter new Car Seating Capacity: "; while (!(cin >> car_seating_capacity)) { cout << "Invalid input. Enter seats: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                cout << "Enter new Car Ground Clearance: "; while (!(cin >> car_ground_clearance)) { cout << "Invalid input. Enter clearance: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                cin.ignore();
                cout << "Enter new Car Availability: "; getline(cin, availability);
                cout << "Enter new Cargo Space: "; while (!(cin >> cargo_space)) { cout << "Invalid input. Enter cargo space: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                cin.ignore();
                cout << "Enter new Fuel Type: "; getline(cin, fuel_type);
            }
            fout << car_id << "\t" << car_make << "\t" << car_model << "\t" << car_price << "\t" << car_seating_capacity << "\t" << car_ground_clearance << "\t" << availability << "\t" << cargo_space << "\t" << fuel_type << endl;
        }
        fin.close(); fout.close();
        remove("Hatchback.txt"); rename("temp.txt", "Hatchback.txt");
        if (!found) cout << "Hatchback with ID " << id << " not found." << endl;
        else cout << "Hatchback updated successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}
void Hatchback::del() {
    int id;
    cout << "Enter the ID of the Hatchback to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Hatchback.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, cargo_space;
        string car_make, car_model, availability, fuel_type;
        float car_price;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> cargo_space;
            fin.ignore();
            getline(fin, fuel_type);
            if (car_id == id) found = true;
            else fout << car_id << "\t" << car_make << "\t" << car_model << "\t" << car_price << "\t" << car_seating_capacity << "\t" << car_ground_clearance << "\t" << availability << "\t" << cargo_space << "\t" << fuel_type << endl;
        }
        fin.close(); fout.close();
        remove("Hatchback.txt"); rename("temp.txt", "Hatchback.txt");
        if (!found) cout << "Hatchback with ID " << id << " not found." << endl;
        else cout << "Hatchback with ID " << id << " deleted successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}
void Hatchback::menu(Hatchback& obj) {
    int choice;
    do {
        cout << "\n========== Hatchback Management ==========\n";
        cout << "1. Add Hatchback\n";
        cout << "2. View All Hatchbacks\n";
        cout << "3. Update Hatchback\n";
        cout << "4. Search Hatchback\n";
        cout << "5. Delete Hatchback\n";
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
ostream& operator<<(ostream& cout, const Hatchback& obj) {
    cout << "Car ID : " << obj.get_car_id() << endl;
    cout << "Car Make : " << obj.get_car_make() << endl;
    cout << "Car Model : " << obj.get_car_model() << endl;
    cout << "Car Price : " << obj.get_car_price() << endl;
    cout << "Car Seating Capacity : " << obj.get_car_seating_capacity() << endl;
    cout << "Car Ground Clearance : " << obj.get_car_ground_clearance() << endl;
    cout << "Car Availability : " << obj.get_car_availability() << endl;
    cout << "Car Cargo Space : " << obj.get_cargo_space() << endl;
    cout << "Car Fuel Type : " << obj.get_fuel_type() << endl;
    return cout;
}
istream& operator>>(istream& cin, Hatchback& obj) {
    int car_id, car_seating_capacity, car_ground_clearance, cargo_space;
    string car_make, car_model, availability, fuel_type;
    float car_price;

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

    // Cargo Space
    do {
        cout << "Enter Cargo Space (positive integer): ";
        if (!(cin >> cargo_space) || cargo_space < 0) {
            cout << "Invalid input. Enter a non-negative integer for Cargo Space.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    cin.ignore();

    // Fuel Type
    do {
        cout << "Enter Fuel Type: ";
        getline(cin, fuel_type);
        if (fuel_type.empty()) cout << "Fuel Type cannot be empty.\n";
    } while (fuel_type.empty());

    obj.set_car_id(car_id);
    obj.set_car_make(car_make);
    obj.set_car_model(car_model);
    obj.set_car_price(car_price);
    obj.set_car_seating_capacity(car_seating_capacity);
    obj.set_car_ground_clearance(car_ground_clearance);
    obj.set_car_availability(availability);
    obj.set_cargo_space(cargo_space);
    obj.set_fuel_type(fuel_type);
    obj.store_to_file();
    return cin;
}

