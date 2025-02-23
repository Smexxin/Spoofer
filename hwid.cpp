/* This file is part of hdd_serial_spoofer by namazso, licensed under the MIT license:
*
* MIT License
*
* Copyright (c) namazso 2018
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <ntddk.h>
#include <ntdddisk.h>
#include <scsi.h>
#include <intrin.h>
#include "defs.h"

PDRIVER_DISPATCH g_original_device_control;

void spoof_serial(char* serial, bool is_smart);
unsigned long long g_startup_time;


namespace Hooks
{
	tD3D11Present oPresent = NULL;
	bool bOnce = false;

	HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SysInterval, UINT Flags)
	{
		if (!bOnce)
		{
			//��һ�λ����
			//�õ���Ϸ����
			HWND hWindow = GetMainWindowHwnd(GetCurrentProcessId());
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)(&pDevice))))
			{
				pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)(&pDevice));
				pDevice->GetImmediateContext(&pContext);
			}

			ID3D11Texture2D* renderTargetTexture = nullptr;
			//��ȡ�󻺳�����ַ
			if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&renderTargetTexture)))
			{
				//����Ŀ����ͼ
				pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &pRenderTargetView);
				//�ͷź󻺳�
				renderTargetTexture->Release();
			}

			//��ʼ��ImGUI
			ImGui_ImplDX11_Init(hWindow, pDevice, pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			ImGui::StyleColorsDark();

			bOnce = true;
		}

		//��ͣ�Ļ��������
		ImGui_ImplDX11_NewFrame();

		DrawD3DMenuMain();

		ImGui::Render();
		pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return oPresent(pSwapChain, SysInterval, Flags);
	}
}


struct REQUEST_STRUCT
{
	PIO_COMPLETION_ROUTINE OldRoutine;
	PVOID OldContext;
	ULONG OutputBufferLength;
	PVOID SystemBuffer;
};

NTSTATUS completed_storage_query(
	PDEVICE_OBJECT device_object,
	PIRP irp,
	PVOID context
)
{
	if(!context)
	{
		KdPrint(("%s %d : Context was nullptr\n", __FUNCTION__, __LINE__));
		return STATUS_SUCCESS;
	}

	const auto request = (REQUEST_STRUCT*)context;
	const auto buffer_length = request->OutputBufferLength;
	const auto buffer = (PSTORAGE_DEVICE_DESCRIPTOR)request->SystemBuffer;
	const auto old_routine = request->OldRoutine;
	const auto old_context = request->OldContext;
	ExFreePool(context);

	do
	{

		if(buffer_length < FIELD_OFFSET(STORAGE_DEVICE_DESCRIPTOR, RawDeviceProperties))
			break;	// They just want the size

		if(buffer->SerialNumberOffset == 0)
		{
			KdPrint(("%s %d : Device doesn't have unique ID\n", __FUNCTION__, __LINE__));
			break;
		}

		if(buffer_length < FIELD_OFFSET(STORAGE_DEVICE_DESCRIPTOR, RawDeviceProperties) + buffer->RawPropertiesLength
			|| buffer->SerialNumberOffset < FIELD_OFFSET(STORAGE_DEVICE_DESCRIPTOR, RawDeviceProperties)
			|| buffer->SerialNumberOffset >= buffer_length
			)
		{
			KdPrint(("%s %d : Malformed buffer (should never happen) size: %d\n", __FUNCTION__, __LINE__, buffer_length));
		}
		else
		{
			const auto serial = (char*)buffer + buffer->SerialNumberOffset;
			KdPrint(("%s %d : Serial0: %s\n", __FUNCTION__, __LINE__, serial));
			spoof_serial(serial, false);
			KdPrint(("%s %d : Serial1: %s\n", __FUNCTION__, __LINE__, serial));
		}
	} while(false);

	// Call next completion routine (if any)
	if(irp->StackCount > 1ul && old_routine)
		return old_routine(device_object, irp, old_context);

	return STATUS_SUCCESS;
}

NTSTATUS completed_smart(
	PDEVICE_OBJECT device_object,
	PIRP irp,
	PVOID context
)
{
	UNREFERENCED_PARAMETER(device_object);

	if(!context)
	{
		KdPrint(("%s %d : Context was nullptr\n", __FUNCTION__, __LINE__));
		return STATUS_SUCCESS;
	}

	const auto request = (REQUEST_STRUCT*)context;
	const auto buffer_length = request->OutputBufferLength;
	const auto buffer = (SENDCMDOUTPARAMS*)request->SystemBuffer;
	//const auto old_routine = request->OldRoutine;
	//const auto old_context = request->OldContext;
	ExFreePool(context);

	if(buffer_length < FIELD_OFFSET(SENDCMDOUTPARAMS, bBuffer)
		|| FIELD_OFFSET(SENDCMDOUTPARAMS, bBuffer) + buffer->cBufferSize > buffer_length
		|| buffer->cBufferSize < sizeof(IDINFO)
		)
	{
		KdPrint(("%s %d : Malformed buffer (should never happen) size: %d\n", __FUNCTION__, __LINE__, buffer_length));
	}
	else
	{
		const auto info = (IDINFO*)buffer->bBuffer;
		const auto serial = info->sSerialNumber;
		KdPrint(("%s %d : Serial0: %s\n", __FUNCTION__, __LINE__, serial));
		spoof_serial(serial, true);
		KdPrint(("%s %d : Serial1: %s\n", __FUNCTION__, __LINE__, serial));
	}

	// I have no fucking idea why not calling the original doesnt cause problems but whatever

	//KdPrint(("%s: Returning STATUS_NOT_SUPPORTED\n", __FUNCTION__));

	// We deny access by returning an ERROR code
	//irp->IoStatus.Status = STATUS_NOT_SUPPORTED;

	// Call next completion routine (if any)
	//if ((irp->StackCount > (ULONG)1) && (OldCompletionRoutine != NULL))
	//	return OldCompletionRoutine(device_object, irp, OldContext);

	return irp->IoStatus.Status;
}

void do_completion_hook(PIRP irp, PIO_STACK_LOCATION ioc, PIO_COMPLETION_ROUTINE routine)
{
	// Register CompletionRotuine
	ioc->Control = 0;
	ioc->Control |= SL_INVOKE_ON_SUCCESS;

	const auto old_context = ioc->Context;
	ioc->Context = ExAllocatePool(NonPagedPool, sizeof(REQUEST_STRUCT));
	const auto request = (REQUEST_STRUCT*)ioc->Context;
	request->OldRoutine = ioc->CompletionRoutine;
	request->OldContext = old_context;
	request->OutputBufferLength = ioc->Parameters.DeviceIoControl.OutputBufferLength;
	request->SystemBuffer = irp->AssociatedIrp.SystemBuffer;

	// Setup our function to be called upon completion of the IRP
	ioc->CompletionRoutine = routine;
}

NTSTATUS hooked_device_control(PDEVICE_OBJECT device_object, PIRP irp)
{
	const auto ioc = IoGetCurrentIrpStackLocation(irp);

	switch(ioc->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_STORAGE_QUERY_PROPERTY:

		if(query->PropertyId == StorageDeviceProperty)
			do_completion_hook(irp, ioc, &completed_storage_query);
	}
		break;
	case SMART_RCV_DRIVE_DATA:
		do_completion_hook(irp, ioc, &completed_smart);
		break;
	default:
		break;
	}

	return g_original_device_control(device_object, irp);
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




void apply_hook()
{
	UNICODE_STRING driver_name = RTL_CONSTANT_STRING(L"\\Driver\\Disk");
	PDRIVER_OBJECT driver_object = nullptr;
	auto status = ObReferenceObjectByName(
		&driver_name,
		OBJ_CASE_INSENSITIVE,
		nullptr,
		0,
		*IoDriverObjectType,
		KernelMode,
		nullptr,
		(PVOID*)&driver_object
	);

	if(!driver_object || !NT_SUCCESS(status))
	{
		KdPrint(("%s %d : ObReferenceObjectByName returned 0x%08X driver_object: 0x%016X\n", __FUNCTION__, __LINE__, status, driver_object));
		return;
	}

	auto& device_control = driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL];
	g_original_device_control = device_control;
	device_control = &hooked_device_control;

	ObDereferenceObject(driver_object);
}

DWORD64 GetSystemModuleBaseAddress(const char* ModuleName)
{
	ULONG ReqSize = 0;
	std::vector<BYTE> Buffer(1024 * 1024);

	do
	{
		if (!NtQuerySystemInformation(SystemModuleInformation, Buffer.data(), Buffer.size(), &ReqSize))
			break;

		Buffer.resize(ReqSize * 2);
	} while (ReqSize > Buffer.size());

	for (size_t i = 0; i < ModuleInfo->Count; ++i)
	{
		char* KernelFileName = (char*)ModuleInfo->Module[i].FullPathName + ModuleInfo->Module[i].OffsetToFileName;
		if (!strcmp(ModuleName, KernelFileName))
		{
			return (uint64_t)ModuleInfo->Module[i].ImageBase;
		}
	}
	return 0;
}



