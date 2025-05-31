// client.cpp
#include <iostream>
#include <winsock2.h>
#include <string>
#include <cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (sockaddr*)&server, sizeof(server));

    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << buffer << std::endl;

        std::string input;
        std::getline(std::cin, input);
        send(clientSocket, input.c_str(), input.size(), 0);

    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
