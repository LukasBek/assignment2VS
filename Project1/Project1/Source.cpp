#include <iostream>
#include <string>
#include <Windows.h>


using namespace std;

int main() {
	HANDLE CommPort;
		CommPort = CreateFile("COM11",
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		0

		);

	return 0;
}