#include "Car.h"
#include "SUV.h"
#include "Hatchback.h"
#include "Sedan.h"
#include "Person.h"
#include "Employee.h"
#include "Customer.h"
#include "Showroom.h"
#include <iostream>
#include <limits>
using namespace std;

void clearInput() {
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// int main() {
//    int choice;
//    char sure = 'n';

//    cout << "========================================\n";
//    cout << "      Welcome to the Car Showroom       \n";
//    cout << "========================================\n";

//    do {
//        cout << "\nMain Menu:\n";
//        cout << "  1. Car Management\n";
//        cout << "  2. Employee Management\n";
//        cout << "  3. Customer Management\n";
//        cout << "  4. Exit\n";
//        cout << "Enter your choice (1-4): ";

//        if (!(cin >> choice)) {
//            cout << "Invalid input. Please enter a number between 1 and 4.\n";
//            clearInput();
//            continue;
//        }

//        switch (choice) {
//        case 1: {
//            int carChoice;
//            do {
//                cout << "\nCar Management Menu:\n";
//                cout << "  1. SUV\n";
//                cout << "  2. Sedan\n";
//                cout << "  3. Hatchback\n";
//                cout << "  4. Back to Main Menu\n";
//                cout << "Enter your choice (1-4): ";

//                if (!(cin >> carChoice)) {
//                    cout << "Invalid input. Please enter a number between 1 and 4.\n";
//                    clearInput();
//                    continue;
//                }

//                switch (carChoice) {
//                case 1: {
//                    SUV obj;
//                    obj.menu(obj);
//                    break;
//                }
//                case 2: {
//                    Sedan obj;
//                    obj.menu(obj);
//                    break;
//                }
//                case 3: {
//                    Hatchback obj;
//                    obj.menu(obj);
//                    break;
//                }
//                case 4:
//                    cout << "Returning to Main Menu...\n";
//                    break;
//                default:
//                    cout << "Incorrect choice. Please select between 1 and 4.\n";
//                }
//            } while (carChoice != 4);
//            break;
//        }
//        case 2: {
//            Employee obj;
//            obj.menu(obj);
//            break;
//        }
//        case 3: {
//            Customer obj;
//            obj.menu(obj);
//            break;
//        }
//        case 4: {
//            cout << "\nAre you sure you want to exit? (Y/N): ";
//            cin >> sure;
//            sure = toupper(sure);
//            if (sure == 'Y') {
//                cout << "Thank you for using the Car Showroom Management System!\n";
//            }
//            break;
//        }
//        default:
//            cout << "Invalid choice. Please select a valid option (1-4).\n";
//        }
//    } while (sure != 'Y');

//    return 0;
// }
