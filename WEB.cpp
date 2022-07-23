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
