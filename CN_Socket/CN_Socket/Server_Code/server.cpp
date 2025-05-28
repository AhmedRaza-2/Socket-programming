// server.cpp
#include <iostream>
#include <winsock2.h>
#include "Car.h"
#include "SUV.h"
#include "Hatchback.h"
#include "Sedan.h"
#include "Person.h"
#include "Employee.h"
#include "Customer.h"
#include "Showroom.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
void handleClient(SOCKET clientSocket);

vector<thread> clientThreads;
int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cerr << "Failed to initialize Winsock.\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Failed to create socket.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server listening on port 8080...\n";

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Accept failed.\n";
            continue;
        }

        cout << "Client connected.\n";

        // Handle each client in a new thread
        clientThreads.emplace_back(thread([clientSocket]() {
            handleClient(clientSocket);
            closesocket(clientSocket);
        }));
    }

    // Cleanup: join all threads and cleanup Winsock (never actually reached unless loop breaks)
    for (auto& t : clientThreads) {
        if (t.joinable()) t.join();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}


void sendMsg(SOCKET sock, const string& msg) {
    send(sock, msg.c_str(), msg.length(), 0);
}

string recvMsg(SOCKET sock) {
    char buffer[1024] = {0};
    int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) return "";
    return string(buffer);
}

void handleClient(SOCKET clientSocket) {
    int choice;
    while (true) {
        string menu =
            "Main Menu:\n"
            "1. Car Management\n"
            "2. Employee Management\n"
            "3. Customer Management\n"
            "4. Exit\n"
            "Enter your choice: ";
        sendMsg(clientSocket, menu);
        string recvData = recvMsg(clientSocket);
        if (recvData.empty()) break;
        choice = stoi(recvData);

        if (choice == 1) {
            string carMenu =
                "\nCar Menu:\n1. SUV\n2. Sedan\n3. Hatchback\n4. Back\n"
                "Enter your choice: ";
            sendMsg(clientSocket, carMenu);
            int carChoice = stoi(recvMsg(clientSocket));

            switch (carChoice) {
                case 1: {
                    SUV suv;
                    
                    string suvMenu =
                        "\nSUV Management Menu:\n"
                        "1. Add New SUV\n"
                        "2. View All SUVs\n"
                        "3. Search SUV by ID\n"
                        "4. Back to Car Menu\n"
                        "Enter your choice: ";
                    sendMsg(clientSocket, suvMenu);
                    int suvChoice = stoi(recvMsg(clientSocket));

                    switch (suvChoice) {
                        case 1: {
                            string prompts[] = {
                                "Enter Car ID: ", "Enter Make: ", "Enter Model: ", "Enter Price: ",
                                "Enter Seating Capacity: ", "Enter Ground Clearance: ",
                                "Is Car Available (Yes/No): ", "Enter Offroad Capability: ", "Enter Towing Capacity: "
                            };
                            string inputs[9];
                            for (int i = 0; i < 9; ++i) {
                                sendMsg(clientSocket, prompts[i]);
                                inputs[i] = recvMsg(clientSocket);
                                if (inputs[i].empty()) {
                                    sendMsg(clientSocket, "Error: Missing input. Operation cancelled.\n");
                                    return;
                                }
                            }
                        
                            try {
                                int car_id = stoi(inputs[0]);
                                string make = inputs[1];
                                string model = inputs[2];
                                float price = stof(inputs[3]);
                                int seating = stoi(inputs[4]);
                                int clearance = stoi(inputs[5]);
                                string availability = inputs[6];
                                int offroad = stoi(inputs[7]);
                                int towing = stoi(inputs[8]);
                        
                                SUV newSUV(car_id, make, model, price, seating, clearance, availability, offroad, towing);
                                newSUV.store_to_file();
                                sendMsg(clientSocket, "SUV added successfully.\n");
                            } catch (const exception& e) {
                                cerr << "Error: " << e.what() << endl;
                                sendMsg(clientSocket, "Error: Invalid or incomplete input. Please try again.\n");
                            }
                            break;
                        }
                        
                        case 2: {
                            ostringstream oss;
                            streambuf* oldCout = cout.rdbuf(oss.rdbuf());
                            suv.view_from_file();
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, oss.str());
                            break;
                        }
                        case 3: {
                            sendMsg(clientSocket, "Enter the ID to search: ");
                            int id = stoi(recvMsg(clientSocket));
                            istringstream inputStream(to_string(id));
                            ostringstream outputStream;
                            streambuf* oldCin = cin.rdbuf();
                            streambuf* oldCout = cout.rdbuf();
                            cin.rdbuf(inputStream.rdbuf());
                            cout.rdbuf(outputStream.rdbuf());
                            suv.search();
                            cin.rdbuf(oldCin);
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, outputStream.str());
                            break;
                        }
                        case 4: break;
                        default:
                            sendMsg(clientSocket, "Invalid SUV menu option.\n");
                    }
                    break;
                }
                case 2: {
                    // Sedan
                    Sedan sedan;
                    string sedanMenu =
                        "\nSedan Management Menu:\n"
                        "1. Add New Sedan\n"
                        "2. View All Sedans\n"
                        "3. Search Sedan by ID\n"
                        "4. Back to Car Menu\n"
                        "Enter your choice: ";
                    sendMsg(clientSocket, sedanMenu);
                    int sedanChoice = stoi(recvMsg(clientSocket));

                    switch (sedanChoice) {
                        case 1: {
                            string prompts[] = {
                                "Enter Car ID: ", "Enter Make: ", "Enter Model: ", "Enter Price: ",
                                "Enter Seating Capacity: ", "Enter Ground Clearance: ",
                                "Is Car Available (Yes/No): ", "Enter Fuel Efficiency: ", "Enter Trunk Capacity: "
                            };
                            string inputs[9];
                            for (int i = 0; i < 9; ++i) {
                                sendMsg(clientSocket, prompts[i]);
                                inputs[i] = recvMsg(clientSocket);
                            }

                            Sedan newSedan(
                                stoi(inputs[0]), inputs[1], inputs[2], stof(inputs[3]),
                                stoi(inputs[4]), stoi(inputs[5]), inputs[6],
                                stof(inputs[7]), stof(inputs[8])
                            );
                            newSedan.store_to_file();
                            sendMsg(clientSocket, "Sedan added successfully.\n");
                            break;
                        }
                        case 2: {
                            ostringstream oss;
                            streambuf* oldCout = cout.rdbuf(oss.rdbuf());
                            sedan.view_from_file();
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, oss.str());
                            break;
                        }
                        case 3: {
                            sendMsg(clientSocket, "Enter the ID to search: ");
                            int id = stoi(recvMsg(clientSocket));
                            istringstream inputStream(to_string(id));
                            ostringstream outputStream;
                            streambuf* oldCin = cin.rdbuf();
                            streambuf* oldCout = cout.rdbuf();
                            cin.rdbuf(inputStream.rdbuf());
                            cout.rdbuf(outputStream.rdbuf());
                            sedan.search();
                            cin.rdbuf(oldCin);
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, outputStream.str());
                            break;
                        }
                        case 4: break;
                        default:
                            sendMsg(clientSocket, "Invalid Sedan menu option.\n");
                    }
                    break;
                }
                case 3: {
                    Hatchback hatchback;
                    string hatchMenu =
                        "\nHatchback Management Menu:\n"
                        "1. Add New Hatchback\n"
                        "2. View All Hatchbacks\n"
                        "3. Search Hatchback by ID\n"
                        "4. Back to Car Menu\n"
                        "Enter your choice: ";
                    sendMsg(clientSocket, hatchMenu);
                    int hatchChoice = stoi(recvMsg(clientSocket));

                    switch (hatchChoice) {
                        case 1: {
                            string prompts[] = {
                                "Enter Car ID: ", "Enter Make: ", "Enter Model: ", "Enter Price: ",
                                "Enter Seating Capacity: ", "Enter Ground Clearance: ",
                                "Is Car Available (Yes/No): ", "Enter Cargo Space: ", "Enter Fuel Type: "
                            };
                            string inputs[9];
                            for (int i = 0; i < 9; ++i) {
                                sendMsg(clientSocket, prompts[i]);
                                inputs[i] = recvMsg(clientSocket);
                            }

                            Hatchback newHatchback(
                                stoi(inputs[0]), inputs[1], inputs[2], stof(inputs[3]),
                                stoi(inputs[4]), stoi(inputs[5]), inputs[6],
                                stoi(inputs[7]), inputs[8]
                            );
                            newHatchback.store_to_file();
                            sendMsg(clientSocket, "Hatchback added successfully.\n");
                            break;
                        }
                        case 2: {
                            ostringstream oss;
                            streambuf* oldCout = cout.rdbuf(oss.rdbuf());
                            hatchback.view_from_file();
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, oss.str());
                            break;
                        }
                        case 3: {
                            sendMsg(clientSocket, "Enter the ID to search: ");
                            int id = stoi(recvMsg(clientSocket));
                            istringstream inputStream(to_string(id));
                            ostringstream outputStream;
                            streambuf* oldCin = cin.rdbuf();
                            streambuf* oldCout = cout.rdbuf();
                            cin.rdbuf(inputStream.rdbuf());
                            cout.rdbuf(outputStream.rdbuf());
                            hatchback.search();
                            cin.rdbuf(oldCin);
                            cout.rdbuf(oldCout);
                            sendMsg(clientSocket, outputStream.str());
                            break;
                        }
                        case 4: break;
                        default:
                            sendMsg(clientSocket, "Invalid Hatchback menu option.\n");
                    }
                    break;
                }
                case 4: break;
                default:
                    sendMsg(clientSocket, "Invalid Car menu option.\n");
            }
        } else if (choice == 2) {
            Employee employee;
            string empMenu =
                "\nEmployee Management Menu:\n"
                "1. Add New Employee\n"
                "2. View All Employees\n"
                "3. Search Employee by ID\n"
                "4. Back to Main Menu\n"
                "Enter your choice: ";
            sendMsg(clientSocket, empMenu);
            int empChoice = stoi(recvMsg(clientSocket));

            switch (empChoice) {
                case 1: {
                    string prompts[] = {
                        "Enter Employee ID: ", "Enter Name: ",
                        "Enter Position: ", "Enter Salary: "
                    };
                    string inputs[4];
                    for (int i = 0; i < 4; ++i) {
                        sendMsg(clientSocket, prompts[i]);
                        inputs[i] = recvMsg(clientSocket);
                    }
                
                    Employee newEmp(stoi(inputs[0]), inputs[1], inputs[2], stof(inputs[3]));
                    newEmp.store_to_file();
                    sendMsg(clientSocket, "Employee added successfully.\n");
                    break;
                }
                
                case 2: {
                    ostringstream oss;
                    streambuf* oldCout = cout.rdbuf(oss.rdbuf());
                    employee.view_from_file();
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, oss.str());
                    break;
                }
                case 3: {
                    sendMsg(clientSocket, "Enter the ID to search: ");
                    int id = stoi(recvMsg(clientSocket));
                    istringstream inputStream(to_string(id));
                    ostringstream outputStream;
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
                    cin.rdbuf(inputStream.rdbuf());
                    cout.rdbuf(outputStream.rdbuf());
                    employee.search();
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }
                case 4: break;
                default:
                    sendMsg(clientSocket, "Invalid Employee menu option.\n");
            }
        } else if (choice == 3) {
            Customer customer;
            string custMenu =
                "\nCustomer Management Menu:\n"
                "1. Add New Customer\n"
                "2. View All Customers\n"
                "3. Search Customer by ID\n"
                "4. Back to Main Menu\n"
                "Enter your choice: ";
            sendMsg(clientSocket, custMenu);
            int custChoice = stoi(recvMsg(clientSocket));
        
            switch (custChoice) {
                case 1: {
                    // Collect all 14 parameters from the client
                    string prompts[] = {
                        "Enter Person ID (int): ",
                        "Enter Person Name: ",
                        "Enter Customer Vehicle Status: ",
                        "Enter Customer Payment Status: ",
                        "Enter Membership: ",
                        "Enter Transaction ID (int): ",
                        "Enter Transaction Amount (float): ",
                        "Enter Car ID (int): ",
                        "Enter Car Make: ",
                        "Enter Car Model: ",
                        "Enter Insurance ID (int): ",
                        "Enter Service ID (int): ",
                        "Enter Insurance Type: ",
                        "Enter Service Name: "
                    };
                    string inputs[14];
                    for (int i = 0; i < 14; ++i) {
                        sendMsg(clientSocket, prompts[i]);
                        inputs[i] = recvMsg(clientSocket);
                    }
        
                    // Parse numerical inputs as needed and create Customer object
                    Customer newCust(
                        stoi(inputs[0]),    // person_id
                        inputs[1],          // person_name
                        inputs[2],          // customer_vehicle_status
                        inputs[3],          // customer_payment_status
                        inputs[4],          // membership
                        stoi(inputs[5]),    // transaction_id
                        stof(inputs[6]),    // transaction_amount
                        stoi(inputs[7]),    // car_id
                        inputs[8],          // car_make
                        inputs[9],          // car_model
                        stoi(inputs[10]),   // insurance_id
                        stoi(inputs[11]),   // service_id
                        inputs[12],         // insurance_type
                        inputs[13]          // service_name
                    );
                    newCust.store_to_file();
                    sendMsg(clientSocket, "Customer added successfully.\n");
                    break;
                }
                case 2: {
                    ostringstream oss;
                    streambuf* oldCout = cout.rdbuf(oss.rdbuf());
                    customer.view_from_file();
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, oss.str());
                    break;
                }
                case 3: {
                    sendMsg(clientSocket, "Enter the ID to search: ");
                    int id = stoi(recvMsg(clientSocket));
        
                    istringstream inputStream(to_string(id));
                    ostringstream outputStream;
        
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
        
                    cin.rdbuf(inputStream.rdbuf());
                    cout.rdbuf(outputStream.rdbuf());
        
                    customer.search();
        
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
        
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }
                case 4: break;
                default:
                    sendMsg(clientSocket, "Invalid Customer menu option.\n");
            }
        }
           
 else if (choice == 4) {
            sendMsg(clientSocket, "Exiting the system. Goodbye!\n");
            break;
        } else {
            sendMsg(clientSocket, "Invalid main menu option.\n");
        }
    }

    closesocket(clientSocket);
    WSACleanup();
}

