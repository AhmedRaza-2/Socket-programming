#include "ImageTransfer.h"
#include <fstream>
#include <iostream>

bool sendImage(SOCKET sock, const std::string& imagePath) {
    std::ifstream file(imagePath, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open image.\n";
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // First send command to indicate image is being sent
    std::string header = "SEND_IMAGE:" + std::to_string(size);
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

bool receiveImage(SOCKET sock, const std::string& savePath) {
    char header[128] = {0};
    recv(sock, header, sizeof(header), 0);
    std::string headerStr(header);

    if (headerStr.find("SEND_IMAGE:") != 0) {
        std::cerr << "Invalid image header.\n";
        return false;
    }

    size_t imageSize = std::stoi(headerStr.substr(11));

    std::ofstream file(savePath, std::ios::binary);
    char buffer[1024];
    size_t totalReceived = 0;

    while (totalReceived < imageSize) {
        int received = recv(sock, buffer, std::min((int)(imageSize - totalReceived), 1024), 0);
        if (received <= 0) return false;
        file.write(buffer, received);
        totalReceived += received;
    }

    file.close();
    return true;
}
