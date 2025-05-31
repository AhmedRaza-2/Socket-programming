#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "Person.h"
#include "Customer.h"
#include "Transaction.h"
#include "Insurance.h"
#include "Service.h"
#include <string>
using namespace std;

// Constructors
Customer::Customer() : Person(), Transaction(), Car(), Insurance(), Service() {
    customer_vehicle_status = "n/a";
    customer_payment_status = "n/a";
    membership = "n/a";
}
Customer::Customer(int person_id, string person_name, string customer_vehicle_status, string customer_payment_status, string membership, int transaction_id, float transaction_amount, int car_id, string car_make, string car_model, int insurance_id, int service_id, string insurance_type, string service_name)
    : Person(person_id, person_name), Transaction(transaction_id, transaction_amount), Car(car_id, car_make, car_model), Insurance(insurance_id, insurance_type), Service(service_id, service_name) {
    this->customer_vehicle_status = customer_vehicle_status;
    this->customer_payment_status = customer_payment_status;
    this->membership = membership;
}
Customer::Customer(const Customer& obj) : Person(obj), Transaction(obj), Car(obj), Insurance(obj), Service(obj) {
    this->customer_vehicle_status = obj.customer_vehicle_status;
    this->customer_payment_status = obj.customer_payment_status;
    this->membership = obj.membership;
}

// Setters
void Customer::set_customer_vehicle_status(string customer_vehicle_status) {
    this->customer_vehicle_status = customer_vehicle_status;
}
void Customer::set_customer_payment_status(string customer_payment_status) {
    this->customer_payment_status = customer_payment_status;
}
void Customer::set_customer_membership(string membership) {
    this->membership = membership;
}

// Getters
string Customer::get_customer_vehicle_status() { return customer_vehicle_status; }
string Customer::get_customer_payment_status() { return customer_payment_status; }
string Customer::get_customer_membership() { return membership; }

// Utility functions
string Customer::tostring() {
    return to_string(get_person_id()) + "\t" + get_person_name() + "\t" +
        to_string(get_transaction_id()) + "\t" + to_string(get_transaction_amount()) + "\t" +
        to_string(get_car_id()) + "\t" + get_car_make() + "\t" + get_car_model() + "\t" +
        to_string(get_Insurance_id()) + "\t" + get_Insurance_type() + "\t" +
        to_string(get_service_id()) + "\t" + get_service_name() + "\t" +
        customer_vehicle_status + "\t" + customer_payment_status + "\t" + membership;
}

void Customer::store_to_file() {
    ofstream fout("Customer.txt", ios::app);
    if (fout.is_open()) {
        fout << tostring() << endl;
        fout.close();
        cout << "\nData Stored To Customer File.\n";
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

void Customer::view_from_file() {
    ifstream fin("Customer.txt");
    if (fin.is_open()) {
        // Table header
        cout << left
            << setw(6) << "ID"
            << setw(18) << "Name"
            << setw(8) << "TxnID"
            << setw(12) << "TxnAmt"
            << setw(8) << "CarID"
            << setw(12) << "CarMake"
            << setw(12) << "CarModel"
            << setw(10) << "InsID"
            << setw(14) << "InsType"
            << setw(10) << "SrvID"
            << setw(14) << "SrvName"
            << setw(12) << "VehStatus"
            << setw(12) << "PayStatus"
            << setw(12) << "Member" << endl;
        cout << string(150, '-') << endl;

        int person_id, transaction_id, car_id, insurance_id, service_id;
        float transaction_amount;
        string person_name, car_make, car_model, insurance_type, service_name, vehicle_status, payment_status, membership;
        bool any = false;
        while (fin >> person_id) {
            fin.ignore();
            getline(fin, person_name, '\t');
            fin >> transaction_id >> transaction_amount >> car_id;
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> insurance_id;
            fin.ignore();
            getline(fin, insurance_type, '\t');
            fin >> service_id;
            fin.ignore();
            getline(fin, service_name, '\t');
            getline(fin, vehicle_status, '\t');
            getline(fin, payment_status, '\t');
            getline(fin, membership);

            cout << left
                << setw(6) << person_id
                << setw(18) << person_name
                << setw(8) << transaction_id
                << setw(12) << fixed << setprecision(2) << transaction_amount
                << setw(8) << car_id
                << setw(12) << car_make
                << setw(12) << car_model
                << setw(10) << insurance_id
                << setw(14) << insurance_type
                << setw(10) << service_id
                << setw(14) << service_name
                << setw(12) << vehicle_status
                << setw(12) << payment_status
                << setw(12) << membership << endl;
            any = true;
        }
        if (!any) {
            cout << "No customer records found.\n";
        }
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}

void Customer::search() {
    int id;
    cout << "Enter the ID of the Customer to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Customer.txt");
    if (fin.is_open()) {
        bool found = false;
        int person_id, transaction_id, car_id, insurance_id, service_id;
        float transaction_amount;
        string person_name, car_make, car_model, insurance_type, service_name, vehicle_status, payment_status, membership;
        while (fin >> person_id) {
            fin.ignore();
            getline(fin, person_name, '\t');
            fin >> transaction_id >> transaction_amount >> car_id;
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> insurance_id;
            fin.ignore();
            getline(fin, insurance_type, '\t');
            fin >> service_id;
            fin.ignore();
            getline(fin, service_name, '\t');
            getline(fin, vehicle_status, '\t');
            getline(fin, payment_status, '\t');
            getline(fin, membership);

            if (person_id == id) {
                found = true;
                cout << "\nCustomer Details:\n";
                cout << "ID: " << person_id << endl;
                cout << "Name: " << person_name << endl;
                cout << "Transaction ID: " << transaction_id << endl;
                cout << "Transaction Amount: " << transaction_amount << endl;
                cout << "Car ID: " << car_id << endl;
                cout << "Car Make: " << car_make << endl;
                cout << "Car Model: " << car_model << endl;
                cout << "Insurance ID: " << insurance_id << endl;
                cout << "Insurance Type: " << insurance_type << endl;
                cout << "Service ID: " << service_id << endl;
                cout << "Service Name: " << service_name << endl;
                cout << "Vehicle Status: " << vehicle_status << endl;
                cout << "Payment Status: " << payment_status << endl;
                cout << "Membership: " << membership << endl;
                break;
            }
        }
        if (!found) {
            cout << "Customer with ID " << id << " not found." << endl;
        }
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}

void Customer::update() {
    int id;
    cout << "Enter the ID of the Customer to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ifstream fin("Customer.txt");
    ofstream fout("temp.txt");

    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int person_id, transaction_id, car_id, insurance_id, service_id;
        float transaction_amount;
        string person_name, car_make, car_model, insurance_type, service_name, vehicle_status, payment_status, membership;

        while (fin >> person_id) {
            fin.ignore();
            getline(fin, person_name, '\t');
            fin >> transaction_id >> transaction_amount >> car_id;
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> insurance_id;
            fin.ignore();
            getline(fin, insurance_type, '\t');
            fin >> service_id;
            fin.ignore();
            getline(fin, service_name, '\t');
            getline(fin, vehicle_status, '\t');
            getline(fin, payment_status, '\t');
            getline(fin, membership);

            if (person_id == id) {
                found = true;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline

                cout << "Enter new Customer Name: ";
                getline(cin, person_name);

                cout << "Enter new Transaction ID: ";
                while (!(cin >> transaction_id)) {
                    cout << "Invalid input. Please enter a valid integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter new Transaction Amount: ";
                while (!(cin >> transaction_amount)) {
                    cout << "Invalid input. Please enter a valid amount: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter new Car ID: ";
                while (!(cin >> car_id)) {
                    cout << "Invalid input. Please enter a valid integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush before getline

                cout << "Enter new Car Make: ";
                getline(cin, car_make);

                cout << "Enter new Car Model: ";
                getline(cin, car_model);

                cout << "Enter new Insurance ID: ";
                while (!(cin >> insurance_id)) {
                    cout << "Invalid input. Please enter a valid integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush before getline

                cout << "Enter new Insurance Type: ";
                getline(cin, insurance_type);

                cout << "Enter new Service ID: ";
                while (!(cin >> service_id)) {
                    cout << "Invalid input. Please enter a valid integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush before getline

                cout << "Enter new Service Name: ";
                getline(cin, service_name);

                cout << "Enter new Vehicle Status: ";
                getline(cin, vehicle_status);

                cout << "Enter new Payment Status: ";
                getline(cin, payment_status);

                cout << "Enter new Membership: ";
                getline(cin, membership);
            }

            fout << person_id << "\t" << person_name << "\t" << transaction_id << "\t" << transaction_amount << "\t"
                 << car_id << "\t" << car_make << "\t" << car_model << "\t"
                 << insurance_id << "\t" << insurance_type << "\t"
                 << service_id << "\t" << service_name << "\t"
                 << vehicle_status << "\t" << payment_status << "\t" << membership << endl;
        }

        fin.close();
        fout.close();

        remove("Customer.txt");
        rename("temp.txt", "Customer.txt");

        if (!found) {
            cout << "Customer with ID " << id << " not found." << endl;
        } else {
            cout << "Customer updated successfully." << endl;
        }
    } else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}


void Customer::del() {
    int id;
    cout << "Enter the ID of the Customer to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Customer.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int person_id, transaction_id, car_id, insurance_id, service_id;
        float transaction_amount;
        string person_name, car_make, car_model, insurance_type, service_name, vehicle_status, payment_status, membership;
        while (fin >> person_id) {
            fin.ignore();
            getline(fin, person_name, '\t');
            fin >> transaction_id >> transaction_amount >> car_id;
            fin.ignore();
            getline(fin, car_make, '\t');
            getline(fin, car_model, '\t');
            fin >> insurance_id;
            fin.ignore();
            getline(fin, insurance_type, '\t');
            fin >> service_id;
            fin.ignore();
            getline(fin, service_name, '\t');
            getline(fin, vehicle_status, '\t');
            getline(fin, payment_status, '\t');
            getline(fin, membership);

            if (person_id == id) {
                found = true;
            }
            else {
                fout << person_id << "\t" << person_name << "\t" << transaction_id << "\t" << transaction_amount << "\t"
                    << car_id << "\t" << car_make << "\t" << car_model << "\t"
                    << insurance_id << "\t" << insurance_type << "\t"
                    << service_id << "\t" << service_name << "\t"
                    << vehicle_status << "\t" << payment_status << "\t" << membership << endl;
            }
        }
        fin.close();
        fout.close();
        remove("Customer.txt");
        rename("temp.txt", "Customer.txt");
        if (!found) {
            cout << "Customer with ID " << id << " not found." << endl;
        }
        else {
            cout << "Customer with ID " << id << " deleted successfully." << endl;
        }
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}

void Customer::menu(Customer& obj) {
    int choice;
    do {
        cout << "\n========== Customer Management ==========\n";
        cout << "1. Add Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Update Customer\n";
        cout << "4. Search Customer\n";
        cout << "5. Delete Customer\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice (1-6): ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1:
            cin >> obj;
            break;
        case 2:
            obj.view_from_file();
            break;
        case 3:
            obj.update();
            break;
        case 4:
            obj.search();
            break;
        case 5:
            obj.del();
            break;
        case 6:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 6);
}

void Customer::customer_membership(string new_membership) {
    membership = new_membership;
}

ostream& operator<<(ostream& cout, const Customer& obj) {
    cout << "Customer ID: " << obj.get_person_id() << endl;
    cout << "Customer Name: " << obj.get_person_name() << endl;
    cout << "Customer Membership: " << obj.membership << endl;
    cout << "Customer Transaction ID: " << obj.get_transaction_id() << endl;
    cout << "Customer Transaction Amount: " << obj.get_transaction_amount() << endl;
    cout << "Customer Car ID: " << obj.get_car_id() << endl;
    cout << "Customer Car Make: " << obj.get_car_make() << endl;
    cout << "Customer Car Model: " << obj.get_car_model() << endl;
    cout << "Customer Insurance ID: " << obj.get_Insurance_id() << endl;
    cout << "Customer Insurance Type: " << obj.get_Insurance_type() << endl;
    cout << "Customer Service ID: " << obj.get_service_id() << endl;
    cout << "Customer Service Name: " << obj.get_service_name() << endl;
    cout << "Customer Vehicle Status: " << obj.customer_vehicle_status << endl;
    cout << "Customer Payment Status: " << obj.customer_payment_status << endl;
    return cout;
}

istream& operator>>(istream& cin, Customer& obj) {
    int option;
    cout << "\nWe have an offer for you\n1-) Free Service 1-year\n2-) Free Insurance 1-year\nEnter the details for what you want: ";
    while (!(cin >> option) || (option != 1 && option != 2)) {
        cout << "Invalid input. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int id, t_id, car_id, insurance_id, service_id;
    string name, car_model, car_make, insurance_type, service_name;
    float t_amount;

    // Customer ID
    do {
        cout << "Customer ID (positive integer): ";
        if (!(cin >> id) || id <= 0) {
            cout << "Invalid input. Please enter a positive integer ID: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    obj.set_person_id(id);
    cin.ignore();

    // Customer Name
    do {
        cout << "Customer Name: ";
        getline(cin, name);
        if (name.empty()) cout << "Customer Name cannot be empty.\n";
    } while (name.empty());
    obj.set_person_name(name);

    // Customer Membership
    do {
        cout << "Customer Membership: ";
        getline(cin, obj.membership);
        if (obj.membership.empty()) cout << "Membership cannot be empty.\n";
    } while (obj.membership.empty());

    // Transaction ID
    do {
        cout << "Customer Transaction ID (positive integer): ";
        if (!(cin >> t_id) || t_id <= 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Transaction Amount
    do {
        cout << "Customer Transaction Amount (positive number): ";
        if (!(cin >> t_amount) || t_amount < 0) {
            cout << "Invalid input. Please enter a non-negative amount: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    // Car ID
    do {
        cout << "Customer Car ID (positive integer): ";
        if (!(cin >> car_id) || car_id <= 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    cin.ignore();

    // Car Make
    do {
        cout << "Customer Car Make: ";
        getline(cin, car_make);
        if (car_make.empty()) cout << "Car Make cannot be empty.\n";
    } while (car_make.empty());

    // Car Model
    do {
        cout << "Customer Car Model: ";
        getline(cin, car_model);
        if (car_model.empty()) cout << "Car Model cannot be empty.\n";
    } while (car_model.empty());

    // Vehicle Status
    do {
        cout << "Customer Vehicle Status: ";
        getline(cin, obj.customer_vehicle_status);
        if (obj.customer_vehicle_status.empty()) cout << "Vehicle Status cannot be empty.\n";
    } while (obj.customer_vehicle_status.empty());

    // Payment Status
    do {
        cout << "Customer Payment Status: ";
        getline(cin, obj.customer_payment_status);
        if (obj.customer_payment_status.empty()) cout << "Payment Status cannot be empty.\n";
    } while (obj.customer_payment_status.empty());

    // Insurance Type
    do {
        cout << "Enter Insurance Type: ";
        getline(cin, insurance_type);
        if (insurance_type.empty()) cout << "Insurance Type cannot be empty.\n";
    } while (insurance_type.empty());

    // Insurance ID
    do {
        cout << "Enter Insurance ID (positive integer): ";
        if (!(cin >> insurance_id) || insurance_id <= 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    cin.ignore();

    // Service Name
    do {
        cout << "Enter Service Name: ";
        getline(cin, service_name);
        if (service_name.empty()) cout << "Service Name cannot be empty.\n";
    } while (service_name.empty());

    // Service ID
    do {
        cout << "Enter Service ID (positive integer): ";
        if (!(cin >> service_id) || service_id <= 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);

    obj.set_service_id(service_id);
    obj.set_service_name(service_name);
    obj.set_person_id(id);
    obj.set_person_name(name);
    obj.set_transaction_id(t_id);
    obj.set_transaction_amount(t_amount);
    obj.set_car_id(car_id);
    obj.set_car_make(car_make);
    obj.set_car_model(car_model);
    obj.set_Insurance_id(insurance_id);
    obj.set_Insurance_type(insurance_type);
    obj.set_service_id(service_id);
    obj.set_service_name(service_name);
    obj.set_customer_vehicle_status(obj.customer_vehicle_status);
    obj.set_customer_payment_status(obj.customer_payment_status);
    obj.set_customer_membership(obj.membership);
    obj.store_to_file();
    return cin;
}

