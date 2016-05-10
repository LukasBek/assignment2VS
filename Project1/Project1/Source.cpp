#include <iostream>
#include <string>
#include <Windows.h>


using namespace std;

int main() {
	//Opening the comm port
	HANDLE CommPort;
		CommPort = CreateFile("COM11",
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
			}
			cout << "Error here 1" << endl;
			cin.get();
		}

		//Setting the parameters
		DCB dcb = { 0 };

		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(CommPort, &dcb)) {
			cout << "Error getting state" << endl;
		}

		dcb.BaudRate = CBR_115200;
		dcb.ByteSize = 8;
		dcb.StopBits = ONESTOPBIT;
		dcb.Parity = NOPARITY;

		if (!SetCommState(CommPort, &dcb)) {
			cout << "Error setting serial port state" << endl;
		}

		//Reading data
		char buff[1024 + 1] = { 0 };
		DWORD dwBytesRead = 0;

		if (!ReadFile(CommPort, buff, 1024, &dwBytesRead, NULL)) {
			cout << "Error in reading data" << endl;
		}

	return 0;
}