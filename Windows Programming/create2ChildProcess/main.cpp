#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;


// char arr[5] : Used to store 5 characters
// char *arr[5] : Used to store 5 character pointers or strings
// _tmain is like a generic method, if unicode is enabled then char takes 2 bytes, char --> wchar, main --> wmain
// wchar is wide character, to convert string to wchar preceed it with 'L' letter. 
// wmain and wchar are not part of cpp but provided by Microsoft
int _tmain(int argc, WCHAR* argv[], WCHAR* env[]) {
	BOOL processStatus;
	STARTUPINFO startUpInfo;   // the position of window, width and height are modified here
	PROCESS_INFORMATION processInfo; // the process id, thread id can be extracted
	SECURITY_ATTRIBUTES securityAttributes; // used to inherit another process from current process
	securityAttributes.bInheritHandle = FALSE; // to make inheritance possible
	securityAttributes.lpSecurityDescriptor = NULL; // it deals with access token
	// by providing NULL, default access is allowed. We can define our own access by specifing here
	securityAttributes.nLength = sizeof(securityAttributes); // defines the size
	ZeroMemory(&startUpInfo, sizeof(startUpInfo));  // used to initialize every attribute with 0
	startUpInfo.cb = sizeof(startUpInfo);  // defines size
	ZeroMemory(&processInfo, sizeof(processInfo));
	processStatus = CreateProcess(
		L"C:\\Users\\ay185064\\Desktop\\a.exe",
		NULL, //if application is taken through command line
		&securityAttributes,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
	if (processStatus == 0) {
		cout << "Parent creation falied " << GetLastError() << endl;
		return 0;
	}
	cout << "Parent process handle " << processInfo.hProcess << endl;
	WCHAR handel[] = { (WCHAR)processInfo.hProcess };
	processStatus = CreateProcess(
		L"C:\\Windows\\System32\\calc.exe",
		handel,
		&securityAttributes,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
	if (processStatus == FALSE) {
		cout << "Process1 creation failed" << GetLastError() << endl;
		return 0;
	}
	cout << "Process1 process handle " << processInfo.hProcess << " Process1 thread handle " << processInfo.hThread << endl;
	cout << "Process1 id " << processInfo.dwProcessId << endl;
	processStatus = CreateProcess(
		L"C:\\Windows\\System32\\notepad.exe",
		handel,
		&securityAttributes,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
	if (processStatus == FALSE) {
		cout << "Process2 creation failed" << GetLastError() << endl;
		return 0;
	}
	cout << "Process2 process handle " << processInfo.hProcess << " Process2 thread handle " << processInfo.hThread << endl;
	cout<< "Process2 id " << processInfo.dwProcessId << endl;
	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
}