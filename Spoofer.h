#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <wchar.h>
#include <tchar.h>
#include <random>
#include <sstream>
#include <thread>
#include <Shlwapi.h>
#include <WinUser.h>
#include <ShlObj.h>


class Spoofing {
	std::uintmax_t files;
	std::uintmax_t ffiles;
public:
	void Initialize();
private:
	int RemoveFiles();
	int CleanerFileTemp();
	bool RemoveXboxAuth();
	bool CheckWord(char* filename, char* search);
	void ChangeRegEdit();
	std::string newUUID();
	void GetFiveM();
	void runexe();
	bool GetFolder(std::string& folderpath, const char* szCaption = NULL, HWND hOwner = NULL);
	inline bool exists_test3(const std::string& name);
};



class Menu {
public:
	ImFont* smallFont;
	ImFont* mediumFont;
	void Main(bool loader_active, PDIRECT3DTEXTURE9 my_texture);
private:
	void MainMenu();
	void LoadingScene();
};

template< typename ... Args >
std::string stringer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

extern std::unique_ptr<Menu> m_Menu;

class CConsole
{
public:
    static void MakeSexy();

    static void SetRandomTitle();

    static void SetTitle(_In_ LPCSTR lpConsoleTitle);

    static int Print(char const* const _Format, ...);

    static int WPrint(wchar_t const* const _Format, ...);

    static void Clear();

    static void SetColor(unsigned short color);

    static void Pause();

};
std::string GetHWID();

struct S_LogType
{
    int Default = 15;
    int Warning = 6;
    int Success = 2;
    int Error = 4;
    int Info = 11;
};

void Log(std::string Message, int LogType);
void Log1(std::string Message, int LogType);
