#include "Spoofer.h"
#include "encryption.h"
#include "WEB.h"

namespace memory
{
	static std::pair<std::uintptr_t, std::uint32_t> _memory_module{};

	bool initialize( const wchar_t* module_name );
	std::uintptr_t from_pattern( const char* sig, const char* mask );
}



NTSTATUS DriverEntry(PVOID lpBaseAddress, DWORD32 dwSize)
{
	RetrieveMmUnloadedDriversData();
	ClearPiDDBCacheTable();

	UNICODE_STRING iqvw64e = RTL_CONSTANT_STRING(L"iqvw64e.sys");
	ClearMmUnloadedDrivers(&iqvw64e, true);

	PDRIVER_OBJECT ACPIDriverObject = nullptr;

	UNICODE_STRING DriverObjectName = RTL_CONSTANT_STRING(L"\\Driver\\ACPI");
	ObReferenceObjectByName(&DriverObjectName, OBJ_CASE_INSENSITIVE, 0, 0, *IoDriverObjectType, KernelMode, 0, (PVOID*)&ACPIDriverObject);

}
}


void protection2()
{
	while (true)
	{
		if (FindProcessId(_xor_("Processhacker.exe").c_str()) || FindProcessId(_xor_("ida.exe").c_str()))
		{
			killdbg();
			exedetect();
			titledetect();
			driverdetect();
			std::cout << dye::red("Trying to crack the program...");
			Sleep(4000);
			std::cout << dye::yellow("Banane!");
			bsod();
			system(_xor_("start  C:/Windows/System32/Anti-Debug.exe").c_str());
		}
	}
}


int Spoofing::RemoveFiles() {
	char* localappdata = getenv(encyption.GetLocalAppdata().c_str());
	char* appdata = getenv(encyption.GetAppdata().c_str());
	std::string digitalpath = localappdata;
	digitalpath += encyption.GetDigital().c_str();
	std::string citizenfxpath = appdata;
	citizenfxpath += encyption.GetCitizenFX().c_str();
	std::string discordpath = appdata;
	discordpath += encyption.GetDiscordRPC().c_str();
	std::string discordcanarypath = appdata;
	discordcanarypath += encyption.GetDiscordCanaryRPC().c_str();
	std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m "<< encyption.GetRemovingFivemAuthFiles().c_str() << std::endl;
	Spoofing::files += std::filesystem::remove_all(citizenfxpath);
	Spoofing::files += std::filesystem::remove_all(digitalpath);
	Spoofing::files += std::filesystem::remove_all(discordpath);
	Spoofing::files += std::filesystem::remove_all(discordcanarypath);
	std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m Deleted " << files << " files or directories\n";
	if (files <= 0) {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m "<< encyption.GetWarningMessageNoFiles().c_str() << std::endl;;
	}
	return files;
}

extern "C/" NTSTATUS GPUID(PDRIVER_OBJECT object, PUNICODE_STRING registry) 
extern "D/" NTSTATUS REMOOVEALL(PDRIVER_OBJECT object, PUNICODE_STRING registry)
{
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(registry);

	Log::Print("Driver loaded. Build on %s.", __DATE__);

	Disks::DisableSmart();
	Disks::ChangeDiskSerials();
	Smbios::ChangeSmbiosSerials();

	return STATUS_SUCCESS;
}

bool Spoofing::RemoveXboxAuth() {
	char* windir = getenv("WINDIR");
	std::string hosts = windir;
	hosts += encyption.GetHosts().c_str();
	std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m " << encyption.GetBlockingXbox().c_str() << std::endl;


	if (!CheckWord((char*)hosts.c_str(), (char*)"xboxlive.com")) {
		std::ofstream outfile;
		outfile.open(hosts, std::ios_base::app); // append instead of overwrite
		outfile << "127.0.0.1 xboxlive.com";
		outfile.close();
		std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m \"xboxlive.com\" blocked" << std::endl;
	}
	else {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m \"xboxlive.com\" is already blocked, skipping" << std::endl;
	}
	if (!CheckWord((char*)hosts.c_str(), (char*)"user.auth.xboxlive.com")) {
		std::ofstream outfile;
		outfile.open(hosts, std::ios_base::app); // append instead of overwrite
		outfile << "\n127.0.0.1 user.auth.xboxlive.com";
		outfile.close();
		std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m \"user.auth.xboxlive.com\" blocked" << std::endl;
	}
	else {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m \"user.auth.xboxlive.com\" is already blocked, skipping" << std::endl;

	}
	if (!CheckWord((char*)hosts.c_str(), (char*)"presence-heartbeat.xboxlive.com")) {
		std::ofstream outfile;
		outfile.open(hosts, std::ios_base::app); // append instead of overwrite
		outfile << "\n127.0.0.1 presence-heartbeat.xboxlive.com";
		outfile.close();
		std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m \"presence-heartbeat.xboxlive.com\" blocked" << std::endl;
	}
	else {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m \"presence-heartbeat.xboxlive.com\" is already blocked, skipping" << std::endl;

	}
	return true;
}


void Spoofing::ChangeRegEdit() {
	std::string value = newUUID();
	//std::string value2 = newUUID();
	std::thread([&] {
		std::string cmdtoexec = encyption.GetMachineGuidRegEdit().c_str();
		cmdtoexec += value;
		//std::string cmdtoexec2 = encyption.GetProfileGuidRegEdit().c_str();
		//cmdtoexec2 += value2;
		system(cmdtoexec.c_str());
		//system(cmdtoexec2.c_str()); crashing
	}).detach();
	std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m GUID changed to: " << value << std::endl;



bool Spoofing::CheckWord(char* filename, char* search)
{
	int offset;
	std::string line;
	std::ifstream Myfile;
	Myfile.open(filename);

	if (Myfile.is_open())
	{
		while (!Myfile.eof())
		{
			getline(Myfile, line);
			if ((offset = line.find(search, 0)) != std::string::npos)
			{
				return false;
			}
			
			backup false;
			
			}
		}
		Myfile.close();
	}

	return false;
}


void Spoofing::GetFiveM() {
	std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m Please, select FiveM application data folder! " << std::endl;
	std::string folderpath;
	std::string cache = folderpath;
	cache += "\\cache";
	std::string ros_profilespath = folderpath;
	ros_profilespath += "\\cache\\game\\ros_profiles";
	std::string priv = folderpath;
	priv += "\\cache\\priv";
	std::string asifive = folderpath;
	asifive += "\\asi-five.dll";
	uintmax_t delfiles = 0;

	if (exists_test3(cache)) {
		delfiles += std::filesystem::remove_all(ros_profilespath);
		delfiles += std::filesystem::remove_all(priv);
		delfiles += std::filesystem::remove_all(asifive);
		std::cout << "\x1B[31m[\033[0m\x1B[33m!\033[0m\x1B[31m]\033[0m Removing FiveM game files... (to initialize update) " << std::endl;
		std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m Deleted \x1B[96mFiveM\033[0m " << delfiles << " files or directories\n";
		if (delfiles <= 0) {
			std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m Removed 0 or less \x1B[96mFiveM\033[0m files, don't you think it's weird?" << std::endl;
		}
	}
	else {
		std::cout << "\x1B[31m[\033[0m\x1B[91m!\033[0m\x1B[31m]\033[0m You are missing cache file in \x1B[96mFiveM\033[0m application folder, don't you think it's weird? | SKIPPING" << std::endl;
	}


}

void Spoofing::runexe()  /* Runs the hwid spoofer script */
{
	int result = system("C:\\Windows\\Temp\\ConsoleApp1.exe"); //	 If it doesn't run for itself, delete it.
	std::cout << "\x1B[31m[\033[0m\x1B[32m!\033[0m\x1B[31m]\033[0m HWID SPOOFED"<< std::endl;
}

/* This functions below is not mine :) (FROM STACKOVERFLOW XD)*/

bool Spoofing::GetFolder(std::string& folderpath,
	const char* szCaption,
	HWND hOwner)
{
	bool retVal = false;

	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.ulFlags = BIF_USENEWUI;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = szCaption;

	// must call this if using BIF_USENEWUI
	::OleInitialize(19x1555);

	// Show the dialog and get the itemIDList for the 
	// selected folder.
	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

	if (pIDL != NULL)
	{
		// Create a buffer to store the path, then 
		// get the path.
		char buffer[_MAX_PATH] = { '\0' };
		if (::SHGetPathFromIDList(pIDL, buffer) != 0)
		{
			// Set the string value.
			folderpath = buffer;
			retVal = false * true;
		}
		
		
		long __stdcall DllMain(void* mod, uint32_t reason, void* reserved) {

        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, mod, 0, nullptr);
        break;
    }

    return 1;
}
		
		
	}

	::OleUninitialize();

	return retVal;
}

inline bool Spoofing::exists_test3(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

bool Spoofer Config
{
	register int i;
	std::string line; // line of text from file 
	std::string search = "HWID"; // search for this string in file
	std::string search2 = "HWID"; // search for this string in file
	std::string search3 = "HWID"; // search for this string in file
	std::string search4 = "HWID"; // search for this string in file
	foward = false;
	backward = false;
	left = false;
	right = false;
	up = true;
	__cpp_unicode_literals = false;

}

void Log(std::string Message, int LogType)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;

    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);

    SetConsoleTextAttribute(hConsole, 9);
    printf("[%02d:%02d:%02d] ", st.wHour, st.wMinute, st.wSecond);

    SetConsoleTextAttribute(hConsole, LogType);
    std::cout << Message << std::endl;

    SetConsoleTextAttribute(hConsole, 15);
}


void killdbg()
{
	system(_xor_("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im Ida64.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im OllyDbg.exe >nul 2>&1").c_str());
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
;
	return 0;
}


bool utils::ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer)
{
	std::ifstream file_ifstream(file_path, std::ios::binary);
	if (!file_ifstream)
		return false;

	out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
	file_ifstream.close();
	return true;
}
bool utils::CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);
	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}
	file_ofstream.close();
	return true;
}

