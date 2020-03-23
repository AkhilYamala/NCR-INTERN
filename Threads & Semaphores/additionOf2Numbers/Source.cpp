#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;

DWORD WINAPI readData(LPVOID parm) {
	DWORD* x = (DWORD*)parm;
	cout << "Enter data" << endl;
	int temp;
	cin >> temp;
	*x = temp;
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	int x = 0, y = 0;
	// process1
	HANDLE h = CreateThread(
		NULL,
		0,
		readData,
		&x,
		0,
		NULL
	);
	if (h == NULL) {
		cout << "Cannot create thread" << GetLastError() << endl;
		return 0;
	}
	WaitForSingleObject(h, INFINITE);
	
	// process2
	h = CreateThread(
		NULL,
		0,
		readData,
		&y,
		0,
		NULL
	);
	if (h == NULL) {
		cout << "Cannot create thread" << GetLastError() << endl;
		return 0;
	}
	WaitForSingleObject(h, INFINITE);
	cout << "The sum of " << x << " and " << y << " is " << x + y << endl;
	CloseHandle(h);
	return 0;
}