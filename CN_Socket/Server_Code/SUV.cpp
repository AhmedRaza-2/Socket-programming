#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "SUV.h"
#include "Car.h"
#include <sstream>
using namespace std;

SUV::SUV() : Car() {
    offroad_capability = 0;
    towing_capacity = 0;
}
SUV::SUV(int car_id, string car_make, string car_model, float car_price, int car_seating_capacity, int car_ground_clearance, string is_car_available, int offroad_capability, int towing_capacity)
    : Car(car_id, car_make, car_model, car_price, car_seating_capacity, car_ground_clearance, is_car_available) {
    this->offroad_capability = offroad_capability;
    this->towing_capacity = towing_capacity;
}
SUV::SUV(const SUV& obj) : Car(obj) {
    this->offroad_capability = obj.offroad_capability;
    this->towing_capacity = obj.towing_capacity;
}
SUV::~SUV() {}
void SUV::set_offroad_capability(int offroad_capability) { this->offroad_capability = offroad_capability; }
void SUV::set_towing_capacity(int towing_capacity) { this->towing_capacity = towing_capacity; }
int SUV::get_offroad_capability() const { return offroad_capability; }
int SUV::get_towing_capacity() const { return towing_capacity; }
string SUV::toString() {
    return Car::tostring() + "\t" + to_string(offroad_capability) + "\t" + to_string(towing_capacity);
}
void SUV::store_to_file() {
    ofstream fout("SUV.txt", ios::app);
    if (fout.is_open()) {
        fout << toString() << endl;
        fout.close();
        cout << "\nData Stored To SUV File\n";
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}
void SUV::view_from_file() {
    ifstream fin("SUV.txt");
    if (fin.is_open()) {
        cout << left
            << setw(8) << "ID"
            << setw(15) << "Make"
            << setw(15) << "Model"
            << setw(10) << "Price"
            << setw(8) << "Seats"
            << setw(10) << "Clearance"
            << setw(12) << "Available"
            << setw(15) << "OffroadCap"
            << setw(15) << "TowingCap" << endl;
        cout << string(110, '-') << endl;
        int car_id, car_seating_capacity, car_ground_clearance, offroad_capability, towing_capacity;
        string car_make, car_model, availability;
        float car_price;
        bool any = false;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> offroad_capability >> towing_capacity;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << left
                << setw(8) << car_id
                << setw(15) << car_make
                << setw(15) << car_model
                << setw(10) << fixed << setprecision(2) << car_price
                << setw(8) << car_seating_capacity
                << setw(10) << car_ground_clearance
                << setw(12) << availability
                << setw(15) << offroad_capability
                << setw(15) << towing_capacity << endl;
            any = true;
        }
        if (!any) cout << "No SUV records found.\n";
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void SUV::search() {
    int id;
    cout << "Enter the ID of the SUV to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("SUV.txt");
    if (fin.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, offroad_capability, towing_capacity;
        string car_make, car_model, availability;
        float car_price;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> offroad_capability >> towing_capacity;
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
                    << "\nCar Offroad Capability: " << offroad_capability
                    << "\nCar Towing Capacity: " << towing_capacity << endl;
                break;
            }
        }
        if (!found) cout << "SUV with ID " << id << " not found." << endl;
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void SUV::update() {
    int id;
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

    ifstream fin("SUV.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout) {
        cerr << "Error opening file.\n";
        return;
    }

    bool found = false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        int car_id, seating_capacity, ground_clearance, offroad_capability, towing_capacity;
        string make, model, availability;
        float price;

        ss >> car_id;
        ss.ignore();
        getline(ss, make, '\t');
        getline(ss, model, '\t');
        ss >> price >> seating_capacity >> ground_clearance;
        ss.ignore();
        getline(ss, availability, '\t');
        ss >> offroad_capability >> towing_capacity;

        if (car_id == id) {
            found = true;

            cout << "Enter new Car Make: ";
            getline(cin, make);

            cout << "Enter new Car Model: ";
            getline(cin, model);

            cout << "Enter new Car Price: ";
            while (!(cin >> price)) {
                cout << "Invalid input. Enter price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Car Seating Capacity: ";
            while (!(cin >> seating_capacity)) {
                cout << "Invalid input. Enter seating: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Car Ground Clearance: ";
            while (!(cin >> ground_clearance)) {
                cout << "Invalid input. Enter ground clearance: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Car Availability (Yes/No): ";
            getline(cin, availability);

            cout << "Enter new Offroad Capability: ";
            while (!(cin >> offroad_capability)) {
                cout << "Invalid input. Enter offroad capability: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new Towing Capacity: ";
            while (!(cin >> towing_capacity)) {
                cout << "Invalid input. Enter towing capacity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        fout << car_id << "\t" << make << "\t" << model << "\t"
             << price << "\t" << seating_capacity << "\t"
             << ground_clearance << "\t" << availability << "\t"
             << offroad_capability << "\t" << towing_capacity << endl;
    }

    fin.close();
    fout.close();

    if (found) {
        remove("SUV.txt");
        rename("temp.txt", "SUV.txt");
        cout << "SUV updated successfully.\n";
    } else {
        remove("temp.txt");
        cout << "SUV with ID " << id << " not found.\n";
    }
}

void SUV::del() {
    int id;
    cout << "Enter the ID of the SUV to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("SUV.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int car_id, car_seating_capacity, car_ground_clearance, offroad_capability, towing_capacity;
        string car_make, car_model, availability;
        float car_price;
        while (fin >> car_id) {
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> car_price >> car_seating_capacity >> car_ground_clearance;
            fin.ignore();
            getline(fin, availability, '\t');
            fin >> offroad_capability >> towing_capacity;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (car_id == id) found = true;
            else fout << car_id << "\t" << car_make << "\t" << car_model << "\t" << car_price << "\t" << car_seating_capacity << "\t" << car_ground_clearance << "\t" << availability << "\t" << offroad_capability << "\t" << towing_capacity << endl;
        }
        fin.close(); fout.close();
        remove("SUV.txt"); rename("temp.txt", "SUV.txt");
        if (!found) cout << "SUV with ID " << id << " not found." << endl;
        else cout << "SUV with ID " << id << " deleted successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}
void SUV::menu(SUV& obj) {
    int choice;
    do {
        cout << "\n========== SUV Management ==========\n";
        cout << "1. Add SUV\n";
        cout << "2. View All SUVs\n";
        cout << "3. Update SUV\n";
        cout << "4. Search SUV\n";
        cout << "5. Delete SUV\n";
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
ostream& operator<<(ostream& cout, const SUV& obj) {
    cout << "Car ID : " << obj.get_car_id() << endl;
    cout << "Car Make : " << obj.get_car_make() << endl;
    cout << "Car Model : " << obj.get_car_model() << endl;
    cout << "Car Price : " << obj.get_car_price() << endl;
    cout << "Car Seating Capacity : " << obj.get_car_seating_capacity() << endl;
    cout << "Car Ground Clearance : " << obj.get_car_ground_clearance() << endl;
    cout << "Car Availability : " << obj.get_car_availability() << endl;
    cout << "Car Offroad Capability : " << obj.get_offroad_capability() << endl;
    cout << "Car Towing Capacity : " << obj.get_towing_capacity() << endl;
    return cout;
}
istream& operator>>(istream& cin, SUV& obj) {
    int car_id, car_seating_capacity, car_ground_clearance, offroad_capability, towing_capacity;
    string car_make, car_model, availability;
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

    // Offroad Capability
    do {
        cout << "Enter Offroad Capability (non-negative integer): ";
        if (!(cin >> offroad_capability) || offroad_capability < 0) {
            cout << "Invalid input. Enter a non-negative integer for Offroad Capability.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Towing Capacity
    do {
        cout << "Enter Towing Capacity (non-negative integer): ";
        if (!(cin >> towing_capacity) || towing_capacity < 0) {
            cout << "Invalid input. Enter a non-negative integer for Towing Capacity.\n";
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
    obj.set_offroad_capability(offroad_capability);
    obj.set_towing_capacity(towing_capacity);
    obj.store_to_file();
    return cin;
}

