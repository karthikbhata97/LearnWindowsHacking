#include <Windows.h>
#include <iostream>

int main()
{
	auto data = "Hello World";
	auto handle = GetStdHandle(-11);
	DWORD written = 0;
	auto success = WriteFile(handle, data, (DWORD)strlen(data), NULL, NULL);
	ExitProcess(0);
}
