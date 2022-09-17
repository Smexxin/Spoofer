#include "encryption.h"

namespace utils
{
	bool ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer);
	bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size);
}


{
	ifstream TargetDriverFile(TargetDriverName, ios::binary | ios::in);
	
	if (!TargetDriverFile.is_open())
		throw exception("Can not open target driver file");

	TargetDriverFile.seekg(0, ios::end);
	TagetFileSize = TargetDriverFile.tellg();

	ifstream ProxydriverFile(ProxyDriverName, ios::binary | ios::in);

	if (!ProxydriverFile.is_open())
		throw exception("Can not open proxy driver file");

	ProxydriverFile.seekg(0, ios::end);
	ProxyFileSize = ProxydriverFile.tellg();
	ProxydriverFile.seekg(0, ios::beg);

	ProxyDriverFileBuffer = new BYTE[ProxyFileSize];

	ProxydriverFile.read((char*)ProxyDriverFileBuffer, ProxyFileSize);

	//Getting section info
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)ProxyDriverFileBuffer;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		throw exception("Proxy Driver is not a valid PE file");

	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader->e_lfanew + (DWORD64)ProxyDriverFileBuffer);
	assert(pNtHeader->Signature == IMAGE_NT_SIGNATURE);

	if (pNtHeader->OptionalHeader.SizeOfCode < TagetFileSize)
		throw exception("Proxy Driver code section is too small for overwriting");

	auto NumberOfSections = pNtHeader->FileHeader.NumberOfSections;

	PIMAGE_SECTION_HEADER pFirstSection = (PIMAGE_SECTION_HEADER)(pNtHeader + 1);
	
	for (int i = 0; i < NumberOfSections; ++i)
	{
		auto pCurrentSectionHeader = pFirstSection + i;

		auto Characteristics = pCurrentSectionHeader->Characteristics;

		bool executable = (Characteristics & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE;
		bool writable = (Characteristics & IMAGE_SCN_MEM_WRITE) == IMAGE_SCN_MEM_WRITE;

		if (executable)
		{
			SECTION_INFO info;

			info.SectionBaseOffset = pCurrentSectionHeader->VirtualAddress;
			info.SectionSize = pCurrentSectionHeader->Misc.VirtualSize;
			info.writable = writable;

			if (info.SectionSize < TagetFileSize)
				continue;

			CodeSectionInfo.push_back(info);
		}
	}

	
		if(isBad())
		throw exception("Proxy driver code section is too small");
}

SanityChecker::~SanityChecker()
{
	if (ProxyDriverFileBuffer)
		delete[] ProxyDriverFileBuffer;
}

DWORD64 SanityChecker::GetOverwritableSectionOffset()
{
	for (const auto& info : CodeSectionInfo)
	{
		if (info.writable)
			return info.SectionBaseOffset;
	}

	if (!CodeSectionInfo.empty())
	{
		return CodeSectionInfo[0].SectionBaseOffset;
	}

	return NULL;
}

bool SanityChecker::isBad()
{
	ProxydriverFile.seekg(0, ios::end);
	ProxyFileSize = ProxydriverFile.tellg();
	
	return CodeSectionInfo.empty();
}

namespace serializer
{
	// thanks to namazso
	static inline bool is_good_char( char c )
	{
		const auto u = uint8_t( c );
		return ( u >= uint8_t( '0' ) && u <= uint8_t( '9' ) )
			|| ( u >= uint8_t( 'A' ) && u <= uint8_t( 'Z' ) )
			|| ( u >= uint8_t( 'a' ) && u <= uint8_t( 'z' ) );
	}
	static inline bool is_hex( char c )
	{
		const auto u = uint8_t( c );
		return ( u >= uint8_t( '0' ) && u <= uint8_t( '9' ) )
			|| ( u >= uint8_t( 'A' ) && u <= uint8_t( 'F' ) )
			|| ( u >= uint8_t( 'a' ) && u <= uint8_t( 'f' ) );
	}
	
	// {
	if(!context)
	{
		KdPrint(("%s %d : Context was nullptr\n", __FUNCTION__, __LINE__));
		return STATUS_SUCCESS;
	}
	
	
