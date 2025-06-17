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
#include "ImageTransfer.h"
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
            int err = WSAGetLastError();
            cerr << "Accept failed. Error: " << err << "\n";
        
            // Only break if it's a fatal error, e.g., WSANOTINITIALISED or WSAENOTSOCK
            if (err == WSAENOTSOCK || err == WSANOTINITIALISED) {
                break; // fatal
            }
            Sleep(100);
            continue; // retry on temporary errors
        }
        
        cout << "Client connected.\n";
        clientThreads.emplace_back(thread([clientSocket]() {
            handleClient(clientSocket);
            cout << "Client disconnected.\n";
            closesocket(clientSocket);
        }));
    }
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
            "5. Exit\n"
            "Enter your choice: ";
        sendMsg(clientSocket, menu);
        string recvData = recvMsg(clientSocket);
        if (recvData.empty()) break;
        choice = stoi(recvData);
        if (choice == 5) {
            sendMsg(clientSocket, "Exiting...\n");
            break;
                    }
        if (choice == 1) {
            while (true) {
                string carMenu =
                    "\nCar Menu:\n1. SUV\n2. Sedan\n3. Hatchback\n5. Back\n"
                    "Enter your choice: ";
                sendMsg(clientSocket, carMenu);
                int carChoice = stoi(recvMsg(clientSocket));
                if (carChoice == 5) break;
        
                switch (carChoice) {
                    case 1: {
                        SUV suv;
                        while (true) {
                            string suvMenu =
                                "\nSUV Management Menu:\n"
                                "1. Add New SUV\n"
                                "2. View All SUVs\n"
                                "3. Search SUV by ID\n"
                                "5. Update SUV by ID\n"
                                "6. Delete SUV by ID\n"
                                "7. Back to Car Menu\n"
                                "Enter your choice: ";
                            sendMsg(clientSocket, suvMenu);
                            int suvChoice = stoi(recvMsg(clientSocket));
                            if (suvChoice == 7) break;
        
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
                                        SUV newSUV(
                                            stoi(inputs[0]), inputs[1], inputs[2], stof(inputs[3]),
                                            stoi(inputs[4]), stoi(inputs[5]), inputs[6],
                                            stoi(inputs[7]), stoi(inputs[8])
                                        );
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
                                case 5: {  
                                    sendMsg(clientSocket, "Enter the ID of the SUV to update: ");
                                    int id = stoi(recvMsg(clientSocket));
                                    
                                    string prompts[] = {
                                        "Enter new Car Make: ",
                                        "Enter new Car Model: ",
                                        "Enter new Car Price: ",
                                        "Enter new Car Seating Capacity: ",
                                        "Enter new Car Ground Clearance: ",
                                        "Enter new Car Availability (Yes/No): ",
                                        "Enter new Offroad Capability: ",
                                        "Enter new Towing Capacity: "
                                    };
                                    const int numFields = sizeof(prompts) / sizeof(prompts[0]);
                                    string inputs[numFields];
                                    
                                    for (int i = 0; i < numFields; ++i) {
                                        sendMsg(clientSocket, prompts[i]);
                                        inputs[i] = recvMsg(clientSocket);
                                    }
                                
                                    stringstream inputStream;
                                    inputStream << id << "\n";
                                    for (int i = 0; i < numFields; ++i) {
                                        inputStream << inputs[i] << "\n";
                                    }
                                
                                    // Redirect cin/cout for simulation
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                
                                    ostringstream outputStream;
                                    cout.rdbuf(outputStream.rdbuf());
                                
                                    suv.update();  // call the method to handle update logic
                                
                                    // Restore original cin/cout
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                
                                case 6: {  
                                    sendMsg(clientSocket, "Enter the ID of the SUV to delete: ");
                                    int id = stoi(recvMsg(clientSocket));
                                    stringstream inputStream;
                                    inputStream << id << "\n";
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                    ostringstream outputStream;
                                    cout.rdbuf(outputStream.rdbuf());
                                    suv.del();
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                default:
                                    sendMsg(clientSocket, "Invalid SUV menu option.\n");
                            }
                        }
                        break;
                    }
                    case 2: {
                        Sedan sedan;
                        while (true) {
                            string sedanMenu =
                                "\nSedan Management Menu:\n"
                                "1. Add New Sedan\n"
                                "2. View All Sedans\n"
                                "3. Search Sedan by ID\n"
                                "5. Update Sedan \n"
                                "6. Delete Sedan \n"
                                "7. Back to Car Menu\n"
                                "Enter your choice: ";
                            sendMsg(clientSocket, sedanMenu);
                            int sedanChoice = stoi(recvMsg(clientSocket));
                            if (sedanChoice == 7) break;
        
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
                                case 5: {  
                                    sendMsg(clientSocket, "Enter the ID of the Sedan to update: ");
                                    int id = stoi(recvMsg(clientSocket));
                                    string prompts[] = {
                                        "Enter new Car Make: ",
                                        "Enter new Car Model: ",
                                        "Enter new Price: ",
                                        "Enter new Seating Capacity: ",
                                        "Enter new Ground Clearance: ",
                                        "Enter new Availability (Yes/No): ",
                                        "Enter new Trunk Capacity: ",
                                        "Enter new Fuel Type: "
                                    };
                                    const int numFields = sizeof(prompts) / sizeof(prompts[0]);
                                    string inputs[numFields];
                                    for (int i = 0; i < numFields; ++i) {
                                        sendMsg(clientSocket, prompts[i]);
                                        inputs[i] = recvMsg(clientSocket);
                                    }
                                    stringstream inputStream;
                                    inputStream << id << "\n";
                                    for (int i = 0; i < numFields; ++i) {
                                        inputStream << inputs[i] << "\n";
                                    }
                                    inputStream << "\n"; 
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                
                                    ostringstream outputStream;
                                    cout.rdbuf(outputStream.rdbuf());
                                    sedan.update();
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                
                                case 6: {  
                                    sendMsg(clientSocket, "Enter the ID of the Sedan to delete: ");
                                    int id = stoi(recvMsg(clientSocket));
                                    stringstream inputStream;
                                    inputStream << id << "\n";
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                    ostringstream outputStream;
                                    cout.rdbuf(outputStream.rdbuf());
                                    sedan.del();
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                default:
                                    sendMsg(clientSocket, "Invalid Sedan menu option.\n");
                            }
                        }
                        break;
                    }
                    case 3: {
                        Hatchback hatchback;
                        while (true) {
                            string hatchMenu =
                                "\nHatchback Management Menu:\n"
                                "1. Add New Hatchback\n"
                                "2. View All Hatchbacks\n"
                                "3. Search Hatchback by ID\n"
                                "5. Update Hatchback by ID\n"
                                "6. Delete Hatchback by ID\n"
                                "7. Back to Car Menu\n"
                                "Enter your choice: ";
                            sendMsg(clientSocket, hatchMenu);
                            int hatchChoice = stoi(recvMsg(clientSocket));
                            if (hatchChoice == 7) break;
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
                                case 5: {
                                    sendMsg(clientSocket, "Enter the ID of the Hatchback to update: ");
                                    int id = stoi(recvMsg(clientSocket));
                                    string prompts[] = {
                                        "Enter new Car Make: ", "Enter new Car Model: ", "Enter new Price: ",
                                        "Enter new Seating Capacity: ", "Enter new Ground Clearance: ",
                                        "Enter new Availability (Yes/No): ", "Enter new Cargo Space: ", "Enter new Fuel Type: "
                                    };
                                    string inputs[8];
                                    for (int i = 0; i < 8; ++i) {
                                        sendMsg(clientSocket, prompts[i]);
                                        inputs[i] = recvMsg(clientSocket);
                                    }
                                    ostringstream outputStream;
                                    stringstream inputStream;
                                    inputStream << id << "\n"
                                                << inputs[0] << "\n" << inputs[1] << "\n" << inputs[2] << "\n"
                                                << inputs[3] << "\n" << inputs[4] << "\n" << inputs[5] << "\n"
                                                << inputs[6] << "\n" << inputs[7] << "\n"
                                                << "\n"; 
                                
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                    cout.rdbuf(outputStream.rdbuf());
                                
                                    hatchback.update();
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                
                                case 6: {
                                    sendMsg(clientSocket, "Enter the ID of the Hatchback to delete: ");
                                    int id = stoi(recvMsg(clientSocket));
                    
                                    stringstream inputStream;
                                    ostringstream outputStream;
                                    inputStream << id << "\n";
                    
                                    streambuf* oldCin = cin.rdbuf();
                                    streambuf* oldCout = cout.rdbuf();
                                    cin.rdbuf(inputStream.rdbuf());
                                    cout.rdbuf(outputStream.rdbuf());
                    
                                    hatchback.del();
                                    cin.rdbuf(oldCin);
                                    cout.rdbuf(oldCout);
                                    sendMsg(clientSocket, outputStream.str());
                                    break;
                                }
                                default:
                                    sendMsg(clientSocket, "Invalid Hatchback menu option.\n");
                            }
                        }
                        break;
                    }
                    default:
                        sendMsg(clientSocket, "Invalid Car menu option.\n");
                }
            }
        }
        else if (choice == 2) {
            Employee employee;
            while (true){
                        
            string empMenu =
                "\nEmployee Management Menu:\n"
                "1. Add New Employee\n"
                "2. View All Employees\n"
                "3. Search Employee by ID\n"
                "5. Update Employee \n"
                "6. Delete Employee \n"
                "7. Back to Main Menu\n"
                "Enter your choice: ";
            sendMsg(clientSocket, empMenu);
            int empChoice = stoi(recvMsg(clientSocket));
            if (empChoice == 7) break;
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
                case 5: { 
                    sendMsg(clientSocket, "Enter the ID of the Employee to update: ");
                    int id = stoi(recvMsg(clientSocket));
                
                    string prompts[] = {
                        "Enter new Name: ",
                        "Enter new Position: ",
                        "Enter new Salary: "
                    };
                    const int numFields = sizeof(prompts) / sizeof(prompts[0]);
                    string inputs[numFields];
                
                    for (int i = 0; i < numFields; ++i) {
                        sendMsg(clientSocket, prompts[i]);
                        inputs[i] = recvMsg(clientSocket);
                    }
                    stringstream inputStream;
                    inputStream << id << "\n";
                    for (int i = 0; i < numFields; ++i) {
                        inputStream << inputs[i] << "\n";
                    }
                    inputStream << "\n"; 
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
                    cin.rdbuf(inputStream.rdbuf());
                    ostringstream outputStream;
                    cout.rdbuf(outputStream.rdbuf());
                    employee.update();
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }            
                case 6: { 
                    sendMsg(clientSocket, "Enter the ID of the Employee to delete: ");
                    int id = stoi(recvMsg(clientSocket));
                    stringstream inputStream;
                    inputStream << id << "\n";
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
                    cin.rdbuf(inputStream.rdbuf());                
                    ostringstream outputStream;
                    cout.rdbuf(outputStream.rdbuf());               
                    employee.del();
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }                
                default:
                    sendMsg(clientSocket, "Invalid Employee menu option.\n");}}}
  else if (choice == 3) {
            Customer customer;
            while (true) {            
            string custMenu =
                "\nCustomer Management Menu:\n"
                "1. Add New Customer\n"
                "2. View All Customers\n"
                "3. Search Customer\n"
                "5. Update Customer\n"
                "6. Delete Customer\n"
                "7. Back to Main Menu\n"
                "8. Image Upload\n"
                "Enter your choice: ";
            sendMsg(clientSocket, custMenu);
            int custChoice = stoi(recvMsg(clientSocket));
            if (custChoice == 7) break;
            switch (custChoice) {
                case 1: {
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
                    Customer newCust(
                        stoi(inputs[0]),   
                        inputs[1],         
                        inputs[2],         
                        inputs[3],         
                        inputs[4],         
                        stoi(inputs[5]),   
                        stof(inputs[6]),   
                        stoi(inputs[7]),   
                        inputs[8],         
                        inputs[9],         
                        stoi(inputs[10]),  
                        stoi(inputs[11]),  
                        inputs[12],        
                        inputs[13]        
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
                case 5: { 
                    sendMsg(clientSocket, "Enter the ID of the Customer to update: ");
                    int id = stoi(recvMsg(clientSocket));
                    string prompts[] = {
                        "Enter new Person Name: ",
                        "Enter new Customer Vehicle Status: ",
                        "Enter new Customer Payment Status: ",
                        "Enter new Membership: ",
                        "Enter new Transaction ID (int): ",
                        "Enter new Transaction Amount (float): ",
                        "Enter new Car ID (int): ",
                        "Enter new Car Make: ",
                        "Enter new Car Model: ",
                        "Enter new Insurance ID (int): ",
                        "Enter new Service ID (int): ",
                        "Enter new Insurance Type: ",
                        "Enter new Service Name: "
                    };
                    const int numFields = sizeof(prompts) / sizeof(prompts[0]);
                    string inputs[numFields];
                    for (int i = 0; i < numFields; ++i) {
                        sendMsg(clientSocket, prompts[i]);
                        inputs[i] = recvMsg(clientSocket);
                    }
                    stringstream inputStream;
                    inputStream << id << "\n"; 
                    for (int i = 0; i < numFields; ++i) {
                        inputStream << inputs[i] << "\n";
                    }
                    inputStream << "\n"; 
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
                    cin.rdbuf(inputStream.rdbuf());                
                    ostringstream outputStream;
                    cout.rdbuf(outputStream.rdbuf());
                    customer.update();
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }
                case 6: {  
                    sendMsg(clientSocket, "Enter the ID of the Customer to delete: ");
                    int id = stoi(recvMsg(clientSocket));
                    stringstream inputStream;
                    inputStream << id << "\n";
                    streambuf* oldCin = cin.rdbuf();
                    streambuf* oldCout = cout.rdbuf();
                    cin.rdbuf(inputStream.rdbuf());
                    ostringstream outputStream;
                    cout.rdbuf(outputStream.rdbuf());
                    customer.del();
                    cin.rdbuf(oldCin);
                    cout.rdbuf(oldCout);
                    sendMsg(clientSocket, outputStream.str());
                    break;
                }
                case 8: { 
                    sendMsg(clientSocket, "Image Upload: Please send the image now...");
                    
                    string filename = "customer_upload_" + to_string(time(0)) + ".jpg";
                
                    if (receiveImage(clientSocket, filename)) {
                        cout << "[SERVER] Customer image saved as: " << filename << endl;
                        sendMsg(clientSocket, "✅ Image received and saved as: " + filename + "\n");
                    } else {
                        cerr << "[SERVER] Failed to receive customer image." << endl;
                        sendMsg(clientSocket, "❌ Failed to receive image. Please try again.\n");
                    }
                    break;
                }
                
                default:
                    sendMsg(clientSocket, "Invalid Customer menu option.\n");
            }
        }
    }           
  else {
            sendMsg(clientSocket, "Invalid main menu option.\n");
        }
    }
    closesocket(clientSocket);
    cout << "[THREAD] handleClient finished for one client.\n";

}