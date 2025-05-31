#include "Employee.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

// Constructors
Employee::Employee() : Person() {
    employee_position = "n/a";
    employee_salary = 0.0;
}
Employee::Employee(int person_id, string person_name, string employee_position, float employee_salary)
    : Person(person_id, person_name) {
    this->employee_position = employee_position;
    this->employee_salary = employee_salary;
}
Employee::Employee(const Employee& obj) : Person(obj) {
    this->employee_position = obj.employee_position;
    this->employee_salary = obj.employee_salary;
}

void Employee::set_employee_position(string employee_position) {
    this->employee_position = employee_position;
}
void Employee::set_employee_salary(float employee_salary) {
    this->employee_salary = employee_salary;
}

string Employee::get_employee_position() {
    return employee_position;
}
float Employee::get_employee_salary() {
    return employee_salary;
}

// Member functions
string Employee::tostring() {
    return to_string(get_person_id()) + "\t" + get_person_name() + "\t" + employee_position + "\t" + to_string(employee_salary);
}
void Employee::promote(string new_position) {
    employee_position = new_position;
}
void Employee::store_to_file() {
    ofstream fout("Employee.txt", ios::app);
    if (fout.is_open()) {
        fout << tostring() << endl;
        fout.close();
        cout << "\nData Stored To Employee File.\n";
    }
    else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}
void Employee::view_from_file() {
    ifstream fin("Employee.txt");
    if (fin.is_open()) {
        // Table header
        cout << "\n"
            << left << setw(12) << "Emp. ID"
            << setw(25) << "Name"
            << setw(20) << "Position"
            << setw(12) << "Salary" << endl;
        cout << string(69, '-') << endl;

        int id;
        string name, position;
        float salary;
        bool any = false;
        while (fin >> id) {
            fin.ignore(); // skip tab
            getline(fin, name, '\t');
            getline(fin, position, '\t');
            fin >> salary;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << left << setw(12) << id
                << setw(25) << name
                << setw(20) << position
                << setw(12) << fixed << setprecision(2) << salary << endl;
            any = true;
        }
        if (!any) {
            cout << "No employee records found.\n";
        }
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Employee::update() {
    int id;
    cout << "Enter the ID of the Employee to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ifstream fin("Employee.txt");
    ofstream fout("temp.txt");

    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int Employee_id;
        string Employee_name, Employee_position;
        float Employee_salary;

        while (fin >> Employee_id) {
            fin.ignore();
            getline(fin, Employee_name, '\t');
            getline(fin, Employee_position, '\t');
            fin >> Employee_salary;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (Employee_id == id) {
                found = true;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline

                cout << "Enter new Employee Name: ";
                getline(cin, Employee_name);

                cout << "Enter new Employee Position: ";
                getline(cin, Employee_position);

                cout << "Enter new Employee Salary: ";
                while (!(cin >> Employee_salary)) {
                    cout << "Invalid input. Please enter a valid salary: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline after salary input
            }

            fout << Employee_id << "\t" << Employee_name << "\t" << Employee_position << "\t" << Employee_salary << endl;
        }

        fin.close();
        fout.close();

        remove("Employee.txt");
        rename("temp.txt", "Employee.txt");

        if (!found)
            cout << "Employee with ID " << id << " not found." << endl;
        else
            cout << "Employee updated successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}

void Employee::search() {
    int id;
    cout << "Enter the ID of the Employee to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Employee.txt");
    if (fin.is_open()) {
        bool found = false;
        int Employee_id;
        string Employee_name, Employee_position;
        float Employee_salary;
        while (fin >> Employee_id) {
            fin.ignore();
            getline(fin, Employee_name, '\t');
            getline(fin, Employee_position, '\t');
            fin >> Employee_salary;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Employee_id == id) {
                found = true;
                cout << "\nEmployee Details:\n";
                cout << "ID: " << Employee_id << endl;
                cout << "Name: " << Employee_name << endl;
                cout << "Position: " << Employee_position << endl;
                cout << "Salary: " << fixed << setprecision(2) << Employee_salary << endl;
                break;
            }
        }
        if (!found) {
            cout << "Employee with ID " << id << " not found." << endl;
        }
        fin.close();
    }
    else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
void Employee::del() {
    int id;
    cout << "Enter the ID of the Employee to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ifstream fin("Employee.txt");
    ofstream fout("temp.txt");
    if (fin.is_open() && fout.is_open()) {
        bool found = false;
        int Employee_id;
        string Employee_name, Employee_position;
        float Employee_salary;
        while (fin >> Employee_id) {
            fin.ignore();
            getline(fin, Employee_name, '\t');
            getline(fin, Employee_position, '\t');
            fin >> Employee_salary;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Employee_id == id) {
                found = true;
            }
            else {
                fout << Employee_id << "\t" << Employee_name << "\t" << Employee_position << "\t" << Employee_salary << endl;
            }
        }
        fin.close();
        fout.close();
        remove("Employee.txt");
        rename("temp.txt", "Employee.txt");
        if (!found) {
            cout << "Employee with ID " << id << " not found." << endl;
        }
        else {
            cout << "Employee with ID " << id << " deleted successfully." << endl;
        }
    }
    else {
        cerr << "Error: Unable to open file for reading or writing." << endl;
    }
}
void Employee::menu(Employee& obj) {
    int choice;
    do {
        cout << "\n========== Employee Management ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Search Employee\n";
        cout << "5. Delete Employee\n";
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

// Stream operators
ostream& operator<<(ostream& cout, const Employee& obj) {
    cout << "Employee ID: " << obj.get_person_id() << endl;
    cout << "Employee Name: " << obj.get_person_name() << endl;
    cout << "Employee Position: " << obj.employee_position << endl;
    cout << "Employee Salary: " << obj.employee_salary << endl;
    return cout;
}
istream& operator>>(istream& cin, Employee& obj) {
    int id;
    string name, position;
    float salary;

    // Employee ID
    do {
        cout << "Enter Employee ID (positive integer): ";
        if (!(cin >> id) || id <= 0) {
            cout << "Invalid input. Please enter a positive integer ID.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    obj.set_person_id(id);
    cin.ignore();

    // Employee Name
    do {
        cout << "Enter Employee Name: ";
        getline(cin, name);
        if (name.empty()) cout << "Employee Name cannot be empty.\n";
    } while (name.empty());
    obj.set_person_name(name);

    // Employee Position
    do {
        cout << "Enter Employee Position: ";
        getline(cin, position);
        if (position.empty()) cout << "Employee Position cannot be empty.\n";
    } while (position.empty());
    obj.set_employee_position(position);

    // Employee Salary
    do {
        cout << "Enter Employee Salary (non-negative number): ";
        if (!(cin >> salary) || salary < 0) {
            cout << "Invalid input. Please enter a non-negative salary.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    } while (true);
    obj.set_employee_salary(salary);

    obj.store_to_file();
    return cin;
}

