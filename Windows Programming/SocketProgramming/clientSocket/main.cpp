#include<iostream>
#include<string>
#include<WS2tcpip.h>

using namespace std;
#pragma comment (lib, "ws2_32.lib")

void main() {
	string ipAddress = "192.168.1.7";
	int port = 8080;

	// initialize ws
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &data);
	if (wsok != 0) {
		cout << "Falied initializaion process" << GetLastError() <<endl;
		return;
	}

	//	create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << "Error while creating socket " << GetLastError() << endl;
		return;
	}

	// fill hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	// hint.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str());  --> depricated

	// connect to server
	int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == SOCKET_ERROR) {
		cout << "cat't connect to server" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// send and receive data
	char buf[4096];
	string userInput;
	do {
		// prompt
		cout << "> ";
		// read data
		getline(cin, userInput);
		if (userInput.size() > 0) {
			// send data
			int sendRes = send(sock, userInput.c_str(), userInput.length() + 1, 0);
			if (sendRes != SOCKET_ERROR) {
				// wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0) {
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
		
	} while (userInput.length() > 0);

	// close socket
	closesocket(sock);
	WSACleanup();
}