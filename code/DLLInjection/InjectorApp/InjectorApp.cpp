#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>

#include <iostream>
#include <vector>

/* This function uses modern C++ to print out the Windows platform error message.  It was refactored into
 * being its own function after being reused in multiple locations.
 */
void printError(std::string prefix) {
	std::wcerr << std::system_error(GetLastError(), std::system_category(), prefix).what() << std::endl;
}

// Inspired by: https://stackoverflow.com/a/57710089
bool findProcess(const wchar_t* targetName, std::vector<HANDLE>& handles) {
	NTSTATUS status;
	UCHAR* buf; /* byte array is easier because it is mixture of structs, and has offsets to each process */
	ULONG buf_size = 16384 * sizeof(SYSTEM_PROCESS_INFORMATION); /* Account for 16384 processes */

	do {
		if ((buf = new UCHAR[buf_size]) != NULL) {
			status = NtQuerySystemInformation(SystemProcessInformation, buf, buf_size, &buf_size);

			if (status == STATUS_SUCCESS) {
				PSYSTEM_PROCESS_INFORMATION process = (PSYSTEM_PROCESS_INFORMATION)buf;
				do {
					if (process->ImageName.Length > 0 && _wcsnicmp(targetName, process->ImageName.Buffer, process->ImageName.Length / sizeof(WCHAR)) == 0) {
						handles.push_back(OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)process->UniqueProcessId));
					}

					process = (PSYSTEM_PROCESS_INFORMATION)(((UCHAR*)process) + process->NextEntryOffset);
				} while (process->NextEntryOffset != 0);
				delete[] buf;
			}
		}
	} while (status == STATUS_INFO_LENGTH_MISMATCH);

	return handles.size() != 0;
}

/* This function loads a DLL into the memory space of another process.  It works by:
 *		1. Creating space in the memory of the other process for the DLL path string.
 *		2. Copying the DLL path string into the memory of the other process.
 *		3. Creating a remote thread to run in the other process.
 *		4. Executing LoadLibrary in the remote thread with the copied string as input.
 * Inspired from: https://github.com/Arvanaghi/Windows-DLL-Injector/blob/master/Source/DLL_Injector.c
 */
bool loadRemoteDLL(HANDLE process, const wchar_t* dllPath) {
	if (process == NULL) {
		return false;
	}

	/* Allocate space for the path string in the memory of the other process. */
	LPVOID remoteMemoryDLLPath = VirtualAllocEx(process, NULL, wcslen(dllPath) * 2, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (remoteMemoryDLLPath == NULL) {
		printError("Failed memory allocation for DLL Path string in other process");
		return false;
	}

	/* Copy the DLL path into the memory space of the other process. */
	BOOL succeededWriting = WriteProcessMemory(process, remoteMemoryDLLPath, dllPath, wcslen(dllPath) * 2, NULL);
	if (!succeededWriting) {
		printError("Failed writing to newly allocated memory in other process memory space");
		return false;
	}
	else {
		/* Apparently, kernel32.dll is usually loaded in the same place in all processes.
		 * TODO: Need to check if ASLR enabled, as this is NOT ASLR safe.
		 */
		LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
		if (loadLibraryAddress == NULL) {
			printError("Failed finding LoadLibraryW");
			return false;
		}
		else {
			HANDLE remoteThread = CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress, remoteMemoryDLLPath, NULL, NULL);
			if (remoteThread == NULL) {
				printError("Failed CreateRemoteThread");
				return false;
			}
		}
	}

	return true;
}

int main()
{
	/* Replace the following three variables with an app of your choice and the path to your DLLs. */
	const wchar_t* appName = L"notepad.exe";
#ifdef _WIN64
	const wchar_t* dllPath = L"C:\\Users\\WolfgangRichter\\Development\\LearnWindowsHacking\\code\\DLLInjection\\Injector\\x64\\Debug\\Injector.dll";
#elif defined _WIN32
	const wchar_t* dllPath = L"C:\\Users\\WolfgangRichter\\Development\\LearnWindowsHacking\\code\\DLLInjection\\Injector\\Debug\\Injector.dll";
#else
#error Compilation target doesn't make sense. Either _WIN32 or _WIN64 **must** be defined.
#endif
	bool attached = false;
	std::vector<HANDLE> processes;

	while (!attached) {
		findProcess(appName, processes);

		if (processes.size() == 0) {
			std::wcerr << "Error getting handle to process." << std::endl;
			Sleep(1);
			continue;
		}

		for (HANDLE process : processes) {
			std::wstring input;

			if (loadRemoteDLL(process, dllPath)) {
				std::wcout << L"Succeeded at DLL injection into " << appName << "!" << std::endl;
				std::wcout << L"Injected: " << dllPath << std::endl;
				attached = true;
			}
			else {
				std::wcerr << L"Failed DLL injection, process handle: " << process << std::endl;
				return EXIT_FAILURE;
			}
		}

		/* Cleanup if we got handles to the process. */
		for (HANDLE h : processes) {
			if (h != NULL) {
				CloseHandle(h);
			}
		}
	}

}