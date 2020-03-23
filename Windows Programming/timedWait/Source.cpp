#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;

DWORD WINAPI display(LPVOID str) {
	for (int i = 1; i <= 1000; i++)
		cout << i << " ";
	cout << endl;
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	cout << "Enter the sleep time :";
	int n;
	cin >> n;
	HANDLE threadHandle = CreateThread(
		NULL,
		0,
		display,
		NULL,
		CREATE_SUSPENDED,
		NULL
	);
	if (threadHandle == NULL) {
		cout << "Cannot create thread " << GetLastError() << endl;
	}
	Sleep(n * 1000);
	ResumeThread(threadHandle);
	WaitForSingleObject(threadHandle, INFINITE);
	CloseHandle(threadHandle);
}