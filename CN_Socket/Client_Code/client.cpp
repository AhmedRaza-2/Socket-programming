// client.cpp
#include <iostream>
#include <winsock2.h>
#include <string>
#include <cstring>
#include "ImageTransfer.h" 
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
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        string serverMsg(buffer);
        cout << serverMsg << endl;

        if (serverMsg.find("Image Upload: Please send the image now") != string::npos) {
            cout << "Enter full path of image to upload (e.g. D:\\\\img.jpg): ";
            string imgPath;
            getline(cin, imgPath);

            if (sendImage(clientSocket, imgPath)) {
                cout << "✅ Image sent successfully.\n";
            } else {
                cout << "❌ Failed to send image.\n";
            }

            memset(buffer, 0, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer), 0);
            cout << buffer << endl;
            continue;
        }

        string input;
        getline(cin, input);
        send(clientSocket, input.c_str(), input.size(), 0);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
