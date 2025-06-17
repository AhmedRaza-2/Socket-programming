#pragma once
#include <string>
#include <winsock2.h>

bool sendImage(SOCKET sock, const std::string& imagePath);
bool receiveImage(SOCKET sock, const std::string& savePath);
