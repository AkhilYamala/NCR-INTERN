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
	/*
	processStatus = CreateProcess(
		//L"C:\\Program Files\\Windows Media Player\\wmplayer.exe", 
		NULL, // if application is taken through command line
		argv[1],
		&securityAttributes,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
	if (processStatus == 0)
		cout << "Process creation falied " << GetLastError() << endl;
	cout << processInfo.hProcess << endl;
	WCHAR handel[] = { (WCHAR)processInfo.hProcess };
	*/
	processStatus = CreateProcess(
		L"C:\\Users\\ay185064\\Desktop\\a.exe",
		NULL,
		&securityAttributes,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&startUpInfo,
		&processInfo
	);
	if (processStatus == FALSE)
		cout << "Process creation failed" << GetLastError() << endl;
	cout << "Process " << processInfo.hThread << endl << processInfo.hProcess << endl;
	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
}