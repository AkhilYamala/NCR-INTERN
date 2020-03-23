#include<iostream>
#include<Windows.h>
#include<tchar.h>
using namespace std;

DWORD sleep1, sleep2;
DWORD WINAPI foo1(LPVOID parms) {
	cout << "Inside thread1" << endl;
	Sleep(sleep1);
	return 0;
}

DWORD WINAPI foo2(LPVOID parms) {
	cout << "Inside thread2" << endl;
	//cout << "S2 " << sleep2 << endl;
	Sleep(sleep2);
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	bool bwait = true;
	cout << "Enter bwait" << endl;
	cout << "1) True\n2) False" << endl;
	int choice;
	cin >> choice;
	if (choice == 2)
		bwait = false;
	DWORD timeOut = INFINITE;
	cout << "Enter timeout interval" << endl;
	cout << "1) INFINITE\n2) 2000" << endl;
	cin >> choice;
	cout << "Sleep time of thread : 1" << endl;
	cout << "1) 0 \n2) 4000 \n3) 2000" << endl;
	cin >> choice;
	switch (choice) {
	case 1: sleep1 = 0;
		break;
	case 2: sleep1 = 4000;
		break;
	case 3: sleep1 = 2000;
	}

	cout << "Sleep time of thread : 2" << endl;
	cout << "1) 0 \n2) 3000" << endl;
	cin >> choice;
	switch (choice) {
	case 1: sleep1 = 0;
		break;
	case 2: sleep1 = 3000;
	}
	
	HANDLE h[2];
	h[0] = CreateThread(
		NULL,
		0,
		foo1,
		NULL,
		0,
		NULL
	);
	h[1] = CreateThread(
		NULL,
		0,
		foo2,
		NULL,
		0,
		NULL
	);
	WaitForMultipleObjects(2, h, bwait, timeOut);
	CloseHandle(h[0]);
	CloseHandle(h[1]);
	return 0;
}