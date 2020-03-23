#include<iostream>
#include<Windows.h>
#include<tchar.h>

using namespace std;	
int data1;

DWORD WINAPI increment(LPVOID parm) {
	data1++;
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	data1 = 0;
	HANDLE h = CreateThread(
		NULL,
		0,
		increment,
		NULL,
		0,
		NULL
	);
	WaitForSingleObject(h, 100);
	h = CreateThread(
		NULL,
		0,
		increment,
		NULL,
		0,
		NULL
	);
	WaitForSingleObject(h, 100);
	cout << "After increment " << data1 << endl;
}