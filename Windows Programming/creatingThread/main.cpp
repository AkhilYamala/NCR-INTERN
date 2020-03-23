#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;

DWORD WINAPI display(LPVOID str) {
	cout << "Hello World" << endl;
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	HANDLE threadHandle = CreateThread(
		NULL,
		0,
		display,
		NULL,
		0,
		NULL
	);
	if (threadHandle == NULL) {
		cout << "Cannot create thread " << GetLastError() << endl;
	}
	WaitForSingleObject(threadHandle, INFINITE);
	CloseHandle(threadHandle);
}