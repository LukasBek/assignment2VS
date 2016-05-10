#include <iostream>
#include <string>
#include <Windows.h>
#include <assert.h>
#include <tchar.h>


using namespace std;

int main() {
	//Opening the comm port
	HANDLE CommPort;
		CommPort = CreateFile("COM4",
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 
		0);

		if (CommPort == INVALID_HANDLE_VALUE) {
			if (GetLastError() == ERROR_FILE_NOT_FOUND) {
				cout << "Serial port does not exist" << endl;
				cin.get();
			}if (GetLastError() == ERROR_ACCESS_DENIED) {
				cout << "comm port i brug" << endl;
				cin.get();
			}
			cout << ("Error here 1: %d", GetLastError()) << endl;
			cin.get();
			
		}

		//Setting the parameters
		DCB dcb = { 0 };

		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(CommPort, &dcb)) {
			cout << "Error getting state" << endl;
			GetLastError();
		}

		dcb.BaudRate = CBR_115200;
		dcb.ByteSize = 8;
		dcb.StopBits = ONESTOPBIT;
		dcb.Parity = NOPARITY;

		if (!SetCommState(CommPort, &dcb)) {
			assert(0);
			cout << ("Failed to set Comm State %d", GetLastError());
		}


		//Reading data
		char buff[1024 + 1] = { 0 };
		DWORD dwBytesRead = 0;

		ReadFile(CommPort, buff, 1024, &dwBytesRead, NULL);
		cout << buff << endl;
		cin.get();
		CloseHandle(CommPort);
		//if (!ReadFile(CommPort, buff, 1024, &dwBytesRead, NULL)) {
			//cout << ("Error in reading data %d", GetLastError()) << endl;
		//}
		//else {
		//	
		//}

	return 0;
}