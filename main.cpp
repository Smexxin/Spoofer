#include <iostream>
#include <Windows.h>
#include "basics.h"
#include "Spoofer.h"
#include "encryption.h"
#include "WEB.h"


// Where the magic happens


	/* The size of the memory that we will look for the pattern */
	auto size_to_scan = 4096 * 100;
	

	/* Now we call the function that will search for the pattern*/
	DWORD* address = (DWORD*)ExPatternScanByStartAddress(hprocess, main_module_address, size_to_scan, pattern_byte, mask);
	if (!address) {
		SetConsoleTextAttribute(console, 0x0c);
		cout << "Error. Address for hook wasn't found. This may be because you already executed this program or because somehow the bypass is outdate. Trying again anyway..." << endl;
		Sleep(10000);
		system("cls");
		main();
	}
	
	/* As the pattern that I scanned is -6 that the address that I want to modify, i am increasing 6  to this */
	address = (DWORD*)((DWORD)address + 6); 
	// cout << "The hook address was found. It is: 0x" << hex << address << endl;
	
	/* Now we need to know where the return address should be. Because we will hook the address with a jump */
	/* The return address is address + 8. This is where the jmp and nops are finisheds */
	DWORD* return_hook_address = (DWORD*)((DWORD)address + 8);

	/* Now we alloc memory to the target process. We will need this to hook. VirtualAllocEx  will return the address were it was allocated	*/
	DWORD* alloc_address = (DWORD*) VirtualAllocEx(hprocess, 0, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!alloc_address) {
		SetConsoleTextAttribute(console, 0x0c);
		cout << "Error while allocating memory..." << endl;
		Sleep(3000);
		main();
	}


int choice;
Encryption encryption = Encryption();
WEB webb = WEB();


int main()
{
	webb.CheckVersion("2.0");
	Spoofing spoofer = Spoofing();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << " _______  _______  _______  _______  _______  _______  ______   " << std::endl;
	std::cout << "|       ||       ||       ||       ||       ||       ||    _ |  " << std::endl;
	std::cout << "|  _____||    _  ||   _   ||   _   ||    ___||    ___||   | ||  " << std::endl;
	std::cout << "| |_____ |   |_| ||  | |  ||  | |  ||   |___ |   |___ |   |_||_ " << std::endl;
	std::cout << "|_____  ||    ___||  |_|  ||  |_|  ||    ___||    ___||    __  |" << std::endl;
	std::cout << "|_____| ||   |    |       ||       ||   |    |   |___ |   |  | |" << std::endl;
	std::cout << "|_______||___|    |_______||_______||___|    |_______||___|  |_|" << std::endl;
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << encryption.GetCredits().c_str() << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	system("pause");
	while (true) {
		system("cls");
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << " _______  _______  _______  _______  _______  ___   __    _  _______             " << std::endl;
		std::cout << "|       ||       ||       ||       ||       ||   | |  |  | ||       |" << std::endl;
		std::cout << "|  _____||    _  ||   _   ||   _   ||    ___||   | |   |_| ||    ___|  " << std::endl;
		std::cout << "| |_____ |   |_| ||  | |  ||  | |  ||   |___ |   | |       ||   | __    " << std::endl;
		std::cout << "|_____  ||    ___||  |_|  ||  |_|  ||    ___||   | |  _    ||   ||  | ___   ___   ___  " << std::endl;
		std::cout << " _____| ||   |    |       ||       ||   |    |   | | | |   ||   |_| ||   | |   | |   | " << std::endl;
		std::cout << "|_______||___|    |_______||_______||___|    |___| |_|  |__||_______||___| |___| |___| " << std::endl;
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "\nVersion 2.0\n" << std::endl;
		std::cout << "\nSelect game that you want to spoof...\n" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "[1] << \x1B[36mFiveM\033[0m\t\t" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "[2] << \x1B[36msecond game\033[0m\t\t" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::cin >> choice;
		if (choice && choice > 0 && choice <= 2) {
			switch (choice) {
			case 1: // fivem case
				spoofer.Initialize();
				system("pause");
				break;
			}
		}
	}

}

// {
	if(!context)
	{
		KdPrint(("%s %d : Context was nullptr\n", __FUNCTION__, __LINE__));
		return STATUS_SUCCESS;
	}


void killdbg()
{
	system(_xor_("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im Ida64.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im OllyDbg.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im Dbg64.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im Dbg32.exe >nul 2>&1").c_str());
	system(_xor_("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1").c_str());
}

DWORD_PTR FindProcessId(const std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

