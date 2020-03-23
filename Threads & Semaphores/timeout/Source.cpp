#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;

DWORD sleep = 0;
DWORD WINAPI greet(LPVOID str) {
	cout << "Hello, your are inside call back function" << endl;
	Sleep(sleep);
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	cout << "Enter the timeout interval" << endl;
	cout << "1) INFINITE \n2) 1000" << endl;
	int choice;
	cin >> choice;
	DWORD time = INFINITE;
	if (choice == 2)
		time = 2000;
	cout << "Enter sleep time" << endl;
	cout << "1) 0 \n2) 2000" << endl;
	cin >> choice;
	if (choice == 2)
		sleep = 2000;
	HANDLE h = CreateThread(
		NULL,
		0,
		greet,
		NULL,
		0,
		NULL
	);
	if (h == NULL) {
		cout << "Thread cannot be created " << GetLastError()<<endl;
		return 0;
	}
	DWORD value = WaitForSingleObject(h, time);
	CloseHandle(h);
	cout << "The returned value is " << value << endl;
	if (value == 258)
		cout << "Interval time out";
	else if (value == 0)
		cout << "Completed execution successfully";
	else if (value == 128)
		cout << "Function in use";
	else
		cout << "There is an error";
	return 0;
}