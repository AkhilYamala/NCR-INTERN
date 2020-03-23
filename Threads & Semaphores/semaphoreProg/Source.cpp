#include<iostream>
#include<Windows.h>
#include<tchar.h>
int MAX_SEM_COUNT = 2;
int const total_threads = 4;

using namespace std;
HANDLE semHandle; // semaphore handle
LONG count1 = 0;  // return number of remaining threads

DWORD WINAPI foo(LPVOID parm) {
	DWORD waitRes;
	BOOL bContinue = TRUE;
	
	while (bContinue) {
		// acquire lock
		waitRes = WaitForSingleObject(semHandle, 200);
		Sleep(200);
		int i = *(DWORD*)parm + 1;
		cout << "Process " << i << " is running" << endl;
		// number of allowed locks
		cout << "Can allow " << (count1) << " threads" << endl;
		if (waitRes == WAIT_OBJECT_0) {
			bContinue = FALSE;
			if (!ReleaseSemaphore(semHandle, 1, &count1))
				cout << "Released Semaphore error" << endl;
			else
				cout << "Semaphore " << i << " released" << endl;
		}
		else if (waitRes == WAIT_TIMEOUT) {
			cout << "Thread timed out" << endl;
		}
	}
	return 0;
}

int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	semHandle = CreateSemaphore(
		NULL,
		MAX_SEM_COUNT,
		MAX_SEM_COUNT,
		NULL
	);
	if (semHandle == NULL) {
		cout << "Cannot create semaphore " << GetLastError() << endl;
		return 0;
	}
	// creating 4 processes, requires a constant value for total_threads
	HANDLE threadHandle[total_threads];
	int i;
	for (i = 0; i < 4; i++) {
		threadHandle[i] = CreateThread(
			NULL,
			0,
			foo,
			&i,
			0,
			NULL
		);
	}
	WaitForMultipleObjects(total_threads, threadHandle, TRUE, INFINITE);
	for (int i = 0; i < total_threads; i++)
		CloseHandle(threadHandle[i]);
	CloseHandle(semHandle);
}