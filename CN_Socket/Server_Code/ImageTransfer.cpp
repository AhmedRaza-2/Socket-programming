#include "ImageTransfer.h"
#include <fstream>
#include <iostream>
using namespace std;
bool sendImage(SOCKET sock, const string& imagePath) {
    ifstream file(imagePath, ios::binary | ios::ate);
    if (!file) {
        cerr << "Failed to open image.\n";
        return false;
    }

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    // First send command to indicate image is being sent
    string header = "SEND_IMAGE:" + to_string(size);
    send(sock, header.c_str(), header.size(), 0);
    Sleep(100); // Wait briefly to ensure header is received

    char* buffer = new char[size];
    if (!file.read(buffer, size)) {
        delete[] buffer;
        return false;
    }

    int totalSent = 0;
    while (totalSent < size) {
        int sent = send(sock, buffer + totalSent, size - totalSent, 0);
        if (sent == SOCKET_ERROR) {
            delete[] buffer;
            return false;
        }
        totalSent += sent;
    }

    delete[] buffer;
    return true;
}

bool receiveImage(SOCKET sock, const string& savePath) {
    char header[128] = {0};
    recv(sock, header, sizeof(header), 0);
    string headerStr(header);

    if (headerStr.find("SEND_IMAGE:") != 0) {
        cerr << "Invalid image header.\n";
        return false;
    }

    size_t imageSize = stoi(headerStr.substr(11));

    ofstream file(savePath, ios::binary);
    char buffer[1024];
    size_t totalReceived = 0;

    while (totalReceived < imageSize) {
        int received = recv(sock, buffer, min((int)(imageSize - totalReceived), 1024), 0);
        if (received <= 0) return false;
        file.write(buffer, received);
        totalReceived += received;
    }

    file.close();
    return true;
}
