#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;

HANDLE threadHandle;
DWORD WINAPI display(LPVOID str) {
	cout << "Inside secondary thread" << endl;
	long result;
	GetExitCodeThread(threadHandle, (LPDWORD)&result);
	cout << "Exit code is " << result << endl;
	TerminateThread(threadHandle, result);
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	threadHandle = CreateThread(
		NULL,
		0,
		display,
		NULL,
		NULL,
		NULL
		);
	if (threadHandle == NULL) {
		cout << "Cannot create thread " << GetLastError() << endl;
	}
	WaitForSingleObject(threadHandle, INFINITE);
	CloseHandle(threadHandle);
}