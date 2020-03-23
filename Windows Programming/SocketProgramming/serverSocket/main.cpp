#include<iostream>
#include<WS2tcpip.h>
#include<string>

using namespace std;
#pragma comment (lib, "ws2_32.lib") 

void main() {
	// initialization
	WSADATA data;   // data gets stored
	WORD version = MAKEWORD(2, 2);  // version 2.2
	int wsok = WSAStartup(version, &data);  // used to initialize the socket

	// creating socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cout << "Socket cannot be created " << GetLastError() << endl;
		return;
	}

	// binding ip address to port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	hint.sin_port = htons(8080);
	bind(listening, (sockaddr*)&hint, sizeof(hint));  // type of host is sockaddr_in --> sockaddr

	// make socket listen
	listen(listening, SOMAXCONN);  // maximum number of connections

	// wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];  // 1025   get host name
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((SOCKADDR*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0) {
		// success
		cout << host << " connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST); // convert ipv4 
		cout << host << "connected on port " << ntohs(client.sin_port) << endl;
	}

	// closing socket
	closesocket(listening);

	// accept and echo message back to client
	char buf[4096];
	string userInput;
	while (true) {
		ZeroMemory(buf, 4096);
		// wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR) {
			cout << "Error in receiving" << endl;
			break;
		}
		if (bytesReceived == 0) {
			cout << "Client disconnected" << endl;
			break;
		}
		// echo message back, for client server model
		//send(clientSocket, buf, bytesReceived+1, 0); 
		cout << string(buf, 0, bytesReceived + 1) <<endl;
		cout << "> ";
		getline(cin, userInput);
		send(clientSocket, userInput.c_str(), userInput.length(), 0);
	}

	// close the socket
	closesocket(clientSocket);

	// cleanUp winsock
	WSACleanup();
}