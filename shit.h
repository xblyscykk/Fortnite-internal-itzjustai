#pragma once
#include "include.h"
#include "DrawTransition.h"

#include <sstream>
#include <fstream>

bool ShowMenu = true;
bool check = true;
UCanvas* static_canvas;


using DrawTransitionOrg = void(*)(uintptr_t _this, uintptr_t canvas);
DrawTransitionOrg DrawTransitionOriginal = 0;
APlayerController* PlayerController;

ue::FKey InsertKey;
ue::FKey F7Key;
ue::FKey RBKey;
ue::FKey ltKey;
ue::FKey LBKey;

#pragma region trackingfilesblocker

//real winapi function
HANDLE(WINAPI* Real_CreateFileW) (
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile) = CreateFileW;

//real winapi function
BOOL(WINAPI* Real_CreateDirectoryW) (
	LPCWSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes) = CreateDirectoryW;


//our own hooked function
HANDLE WINAPI _CreateFileW(LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile)
{
	//ignore pak, sig files and anything to fortnite and pipes
	if (wcsstr(lpFileName, e(L".pak")) || wcsstr(lpFileName, e(L".sig")) || wcsstr(lpFileName, e(L"Fortnite")) || wcsstr(lpFileName, e(L"\\.\\")))
		return Real_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	else
		return Real_CreateFileW(e(L"C:\\Windows\\a"), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

//our own hooked function
BOOL WINAPI _CreateDirectoryW(LPCWSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	//ignore fortnite folder creation
	if (wcsstr(lpPathName, e(L"Fortnite")))
		return Real_CreateDirectoryW(lpPathName, lpSecurityAttributes);
	else
		return Real_CreateDirectoryW(e(L"C:\\Windows\\a"), lpSecurityAttributes);
}

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES* POBJECT_ATTRIBUTES;
typedef struct _IO_STATUS_BLOCK {
#pragma warning(push)
#pragma warning(disable: 4201) // we'll always use the Microsoft compiler
	union {
		NTSTATUS Status;
		PVOID Pointer;
	} DUMMYUNIONNAME;
#pragma warning(pop)

	ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;
typedef
VOID
(NTAPI* PIO_APC_ROUTINE) (
	IN PVOID ApcContext,
	IN PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG Reserved
	);



typedef NTSTATUS(NTAPI* p_NtCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
#define SERVICE_PROXY_KERNEL	L"\\??\\pipe\\11010"
static p_NtCreateFile o_NtCreateFile;
typedef VOID(WINAPI* p_RtlInitUnicodeString)(PUNICODE_STRING Object, LPCWSTR String);
static p_RtlInitUnicodeString o_RtlInitUnicodeString;
NTSTATUS NTAPI NtCreateFile_Hook(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength)
{
	
	DWORD dwWritten = 0;
	NTSTATUS Status = -1;
	if (ObjectAttributes &&
		ObjectAttributes->ObjectName &&
		ObjectAttributes->ObjectName->Buffer &&
		wcsstr(ObjectAttributes->ObjectName->Buffer, L"BattlEye") &&
		wcsstr(ObjectAttributes->ObjectName->Buffer, L"pipe")) // the pipename is \\??\\pipe\\BattlEye 内核名字和应用层不一样
	{

	
		o_RtlInitUnicodeString(ObjectAttributes->ObjectName, SERVICE_PROXY_KERNEL);
		MessageBoxA(0, e("yes yes"), e("pysen"), MB_OK | MB_ICONERROR);
		NTSTATUS Status = o_NtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);


		return Status;
	}
	
	return o_NtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);

};
BOOL GetFileNameFromHandle(HANDLE hFile, std::string& fileName)
{
	DWORD size = MAX_PATH * sizeof(WCHAR) + sizeof(DWORD);
	FILE_NAME_INFO* Path = (FILE_NAME_INFO*)malloc(size);
	memset(Path, 0, size);
	BOOL ret = GetFileInformationByHandleEx(hFile, FILE_INFO_BY_HANDLE_CLASS::FileNameInfo, Path, size);
	if (!ret) return false;
	std::wstring wstr = Path->FileName;
	fileName = std::string(wstr.begin(), wstr.end());
	free(Path);
	return true;
}
std::ostringstream OutputBuffer;
void hex_dump(PVOID Buffer, size_t length, std::ostringstream& OutputBuffer) {
	OutputBuffer.str("");
	OutputBuffer.clear();
	OutputBuffer << "│ ";
	for (size_t i = 0; i < length; i++)
	{
		OutputBuffer.fill('0');
		OutputBuffer.width(2);
		OutputBuffer << std::hex << (int)(*((unsigned char*)Buffer + i));
		OutputBuffer << " ";
	}
	OutputBuffer << std::endl << "│ ";
	for (size_t i = 0; i < length; i++)
	{
		OutputBuffer << *((unsigned char*)Buffer + i);
	}
}
BOOL(WINAPI* Real_ReadFile)(HANDLE a0,
	LPVOID a1,
	DWORD a2,
	LPDWORD a3,
	LPOVERLAPPED a4)
	= ReadFile;
BOOL(WINAPI* Real_WriteFile)(HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped)
	= WriteFile;
NTSTATUS NTAPI ZwReadFile_Hook(HANDLE a0,
	LPVOID a1,
	DWORD a2,
	LPDWORD a3,
	LPOVERLAPPED a4)
{
	std::string fileName;
	if (GetFileNameFromHandle(a0, fileName))
	{
		bool isBattlEye = fileName.compare("\\BattlEye") == 0;
		if (isBattlEye) {
		//	MessageBoxA(0, e("BattlEye"), e("pysen"), MB_OK | MB_ICONERROR);
		
			DWORD cbWritten;

			hex_dump(a1, a2, OutputBuffer);
			if (a2 < 10)
				return  Real_ReadFile(a0, a1, a2, a3, a4);
			std::string fileName1 = OutputBuffer.str();
			bool a = fileName1.find("fVfRfOfFf");
			if (a != std::string::npos) {
	//			MessageBoxA(0, e("BattlEye fVfRfOfFf"), e("pysen"), MB_OK | MB_ICONERROR);
				return Real_ReadFile(a0, a1, a2, a3, a4);

			}
			else
				return 0;

			
		}
		return Real_ReadFile(a0, a1, a2, a3, a4);
	}
	return Real_ReadFile(a0, a1, a2, a3, a4);
}

NTSTATUS NTAPI ZwWriteFile_Hook(HANDLE hFile,
	PVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped)
{
	std::string fileName;
	if (GetFileNameFromHandle(hFile, fileName))
	{
		bool isBattlEye = fileName.compare("\\BattlEye") == 0;
		if (isBattlEye) {
		//	MessageBoxA(0, e("BattlEye"), e("pysen"), MB_OK | MB_ICONERROR);
			
			DWORD cbWritten;

			hex_dump(lpBuffer, nNumberOfBytesToWrite, OutputBuffer);
			if (nNumberOfBytesToWrite < 10)
				return  Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
			std::string fileName1 = OutputBuffer.str();
			bool a = fileName1.find("fVfRfOfFf");
			if (a != std::string::npos) {
			//	MessageBoxA(0, e("BattlEye fVfRfOfFf"), e("pysen"), MB_OK | MB_ICONERROR);
				return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

			}
			else
				return 0;

		
		}
		
		
		return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	}
	return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	
	
}

void MsgBox1(const char* str, ...)
{
	va_list vl;
	va_start(vl, str);
	char buff[1024];
	itsjustaispoof(vsprintf)(buff, str, vl);
	itsjustaispoof(MessageBoxA)(0, buff, e(""), MB_OK | MB_ICONQUESTION);
}
#pragma endregion trackingfilesblocker

void itsjustai() {
	/*trackingfilesblockinit();
	test();*/
	ue::cached::Base = sdkUssage->GetGameBase();




	ue::cached::signatures::GWorld = sdkUssage->PatternScan(ue::cached::Base, e("48 89 05 ?? ?? ?? ?? 0F 28 D7"), 7, true); //48 89 05 ? ? ? ? 48 8B 4B 78
	if (!ue::cached::signatures::GWorld) {
		MessageBoxA(HWND_DESKTOP, e("GWorld"), e("Fortnite  "), MB_ICONERROR);
	}
	ue::cached::signatures::GetBoneMatrix = sdkUssage->PatternScan(ue::cached::Base, e("E8 ? ? ? ? 0F 10 40 68"), 5, true);
	if (!ue::cached::signatures::GetBoneMatrix) {
		MessageBoxA(HWND_DESKTOP, e("GetBoneMatrix"), e("Fortnite  "), MB_ICONERROR);
	}
	//ue::cached::signatures::ProjectWorldToScreen = sdkUssage->PatternScan(ue::cached::Base, e("40 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 33 DB 45 8A F9 49 8B F8 48 8B EA 4C 8B F1 48 85 C9 0F 84 ? ? ? ? 48 8D B1 ? ? ? ? 48 39 1E 74 19 E8 ? ? ? ? 48 8B D0 48 8B CE E8 ? ? ? ? 84 C0 74 05 48 8B 0E EB 03"), 5, false);
	//if (!ue::cached::signatures::ProjectWorldToScreen) {
	//	MessageBoxA(HWND_DESKTOP, e("ProjectWorldToScreen"), e("Fortnite  "), MB_ICONERROR);
	//}
	ue::cached::signatures::FreeFn = sdkUssage->PatternScan(ue::cached::Base, e("E8 ? ? ? ? 89 6F 50"), 0, false);
	if (!ue::cached::signatures::FreeFn) {
		MessageBoxA(HWND_DESKTOP, e("FreeFn"), e("Fortnite  "), MB_ICONERROR);
	}
	ue::cached::signatures::GetNameByIndex = sdkUssage->PatternScan(ue::cached::Base, e("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B 19 48 8B FA E8 ? ? ? ? 0F B7 F3 8B D3 48 C1 EA 10 C1 E6"), 0, false);
	if (!ue::cached::signatures::GetNameByIndex) {
		MessageBoxA(HWND_DESKTOP, e("GetNameByIndex"), e("Fortnite  "), MB_ICONERROR);
	}
	ue::cached::signatures::LineSightOfTo = sdkUssage->PatternScan(ue::cached::Base, e("48 8B C4 55 53 56 57 41 54 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 9D ? ? ? ? 48 8B FA 48 8D 55 D8 4D 8B E1 4D 8B F8 4C 8B F1 E8 ? ? ? ?"), 0, false);;
	if (!ue::cached::signatures::LineSightOfTo) {
		MessageBoxA(HWND_DESKTOP, e("LineSightOfTo"), e("Fortnite  "), MB_ICONERROR);
	}
	ue::classes::objects = (ue::classes::GObjects*)sdkUssage->PatternScan(ue::cached::Base, e("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"), 7, true);;
	if (!ue::classes::objects) {
		MessageBoxA(HWND_DESKTOP, e("GObjects"), e("Fortnite  "), MB_ICONERROR);
	}

	ue::cached::objects::camera::GetCameraLocation = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerCameraManager.GetCameraLocation")); if (!ue::cached::objects::camera::GetCameraLocation) return;
	ue::cached::objects::camera::GetCameraRotation = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerCameraManager.GetCameraRotation")); if (!ue::cached::objects::camera::GetCameraRotation) return;

	ue::cached::objects::camera::GetFOVAngle = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerCameraManager.GetFOVAngle")); if (!ue::cached::objects::camera::GetCameraRotation) return;

	ue::cached::objects::render::Font = (ue::classes::UObject*)find::FindObject(e(L"/Engine/EngineFonts/Roboto.Roboto")); if (!ue::cached::objects::render::Font) return;


	ue::cached::objects::render::K2_DrawLine = (ue::classes::UObject*)find::FindObject(e(L"Engine.Canvas.K2_DrawLine")); if (!ue::cached::objects::render::K2_DrawLine) return;
	ue::cached::objects::render::K2_DrawBox = (ue::classes::UObject*)find::FindObject(e(L"Engine.Canvas.K2_DrawBox")); if (!ue::cached::objects::render::K2_DrawBox) return;
	ue::cached::objects::render::K2_DrawText = (ue::classes::UObject*)find::FindObject(e(L"Engine.Canvas.K2_DrawText")); if (!ue::cached::objects::render::K2_DrawText) return;
	ue::cached::objects::render::K2_TextSize = (ue::classes::UObject*)find::FindObject(e(L"Engine.Canvas.K2_TextSize")); if (!ue::cached::objects::render::K2_DrawBox) return;

	ue::cached::objects::actor::FortPlayerPawnAthena = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortPlayerPawnAthena")); if (!ue::cached::objects::actor::FortPlayerPawnAthena) return;
	ue::cached::objects::actor::ClientSetRotation = (ue::classes::UObject*)find::FindObject(e(L"Engine.Controller.ClientSetRotation")); if (!ue::cached::objects::actor::ClientSetRotation) return;
	ue::cached::objects::actor::GetPlayerName = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerState.GetPlayerName")); if (!ue::cached::objects::actor::GetPlayerName) return;
	ue::cached::objects::actor::ApplyPawnHighlight = (ue::classes::UObject*)find::FindObject(e(L"PlayerPawn_Athena.PlayerPawn_Athena_C.ApplyPawnHighlight")); if (!ue::cached::objects::actor::ApplyPawnHighlight) return;
	ue::cached::objects::actor::Fov = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerController.FOV")); if (!ue::cached::objects::actor::Fov) return;
	ue::cached::objects::actor::SetMouseLocation = (ue::classes::UObject*)find::FindObject(e(L"Engine.PlayerController.SetMouseLocation")); if (!ue::cached::objects::actor::SetMouseLocation) return;
	ue::cached::objects::FortProjectileBase = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortProjectileBase")); if (!ue::cached::objects::FortProjectileBase) return;
	ue::cached::objects::AFortAthenaZipline = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortAthenaZipline")); if (!ue::cached::objects::AFortAthenaZipline) return;
	ue::cached::objects::FortRangedWeaponStats = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortRangedWeaponStats")); if (!ue::cached::objects::FortRangedWeaponStats) return;
	ue::cached::objects::actor::FortPickup = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortPickupAthena")); if (!ue::cached::objects::actor::FortPickup) return;
	ue::cached::objects::actor::PlayerMarker = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortPlayerMarkerBase")); if (!ue::cached::objects::actor::FortPickup) return;

	ue::cached::objects::K2_GetActorRotation = (ue::classes::UObject*)find::FindObject(e(L"Engine.Actor.K2_GetActorRotation")); if (!ue::cached::objects::K2_GetActorRotation) return;

	ue::cached::objects::actor::isHiddingInProp = (ue::classes::UObject*)find::FindObject(e(L"PlayerPawn_Athena.PlayerPawn_Athena_C.isHiddingInProp")); if (!ue::cached::objects::actor::isHiddingInProp) return;
	ue::cached::objects::actor::SetCharacterBodyVisibilityForPossession = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortPlayerPawnAthena.SetCharacterBodyVisibilityForPossession")); if (!ue::cached::objects::actor::SetCharacterBodyVisibilityForPossession) return;
	ue::cached::FortKismetLibrary = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortKismetLibrary")); if (!ue::cached::FortKismetLibrary) return;
	ue::cached::KismetStringLibrary = (ue::classes::UObject*)find::FindObject(e(L"Engine.KismetStringLibrary")); if (!ue::cached::KismetStringLibrary) return;
	ue::cached::KismetMathLibrary = (ue::classes::UObject*)find::FindObject(e(L"Engine.KismetMathLibrary")); if (!ue::cached::KismetMathLibrary) return;
	ue::cached::FortVoiceChannelSpeaker_C = (ue::classes::UObject*)find::FindObject(e(L"FortVoiceChannelSpeaker.FortVoiceChannelSpeaker_C")); if (!ue::cached::KismetMathLibrary) return;
	ue::cached::Conv_StringToName = (ue::classes::UObject*)find::FindObject(e(L"Engine.KismetStringLibrary.Conv_StringToName")); if (!ue::cached::Conv_StringToName) return;


	ue::cached::objects::actor::K2_PayBuildingResourceCost = (ue::classes::UObject*)find::FindObject(e(L"FortniteGame.FortKismetLibrary.K2_PayBuildingResourceCost")); if (!ue::cached::objects::actor::K2_PayBuildingResourceCost) return;

	ue::cached::objects::K2_TeleportTo = (ue::classes::UObject*)find::FindObject(e(L"Engine.Actor.K2_TeleportTo")); if (!ue::cached::objects::K2_TeleportTo) return;
	ue::cached::objects::K2_SetActorLocation = (ue::classes::UObject*)find::FindObject(e(L"Engine.Actor.K2_SetActorLocation")); if (!ue::cached::objects::K2_SetActorLocation) return;

	InsertKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(e(L"Insert")) }, 0 };
	LBKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(e(L"LeftMouseButton")) }, 0 };
	RBKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(e(L"RightMouseButton")) }, 0 };
	ltKey = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(e(L"Gamepad_LeftTrigger")) }, 0 };
	F7Key = ue::FKey{ ue::FName{ sdkUssage->Conv_StringToName(e(L"F7")) }, 0 };


	sdk_p->Initialize((uintptr_t)ue::classes::objects, ue::cached::signatures::GetNameByIndex, ue::cached::signatures::FreeFn);

	ue::cached::offsets::OwningGameInstance = sdk_p->FindOffset(e("World"), e("OwningGameInstance"));
	ue::cached::offsets::Levels = sdk_p->FindOffset(e("World"), e("Levels"));
	ue::cached::offsets::AcknowledgedPawn = sdk_p->FindOffset(e("PlayerController"), e("AcknowledgedPawn"));
	ue::cached::offsets::PlayerCameraManager = sdk_p->FindOffset(e("PlayerController"), e("PlayerCameraManager"));
	ue::cached::offsets::PlayerState = sdk_p->FindOffset(e("Pawn"), e("PlayerState"));
	ue::cached::offsets::bADSWhileNotOnGround = sdk_p->FindOffset(e("FortPlayerPawnAthena"), e("bADSWhileNotOnGround"));
	ue::cached::offsets::CurrentWeapon = sdk_p->FindOffset(e("FortPawn"), e("CurrentWeapon"));
	ue::cached::offsets::TeamIndex = sdk_p->FindOffset(e("FortPlayerStateAthena"), e("TeamIndex"));
	ue::cached::offsets::WeaponData = sdk_p->FindOffset(e("FortWeapon"), e("WeaponData"));
	ue::cached::offsets::DisplayName = sdk_p->FindOffset(e("FortItemDefinition"), e("DisplayName"));
	ue::cached::offsets::Mesh = sdk_p->FindOffset(e("Character"), e("Mesh"));
	ue::cached::offsets::RootComponent = sdk_p->FindOffset(e("Actor"), e("RootComponent"));
	ue::cached::offsets::RelativeLocation = sdk_p->FindOffset(e("SceneComponent"), e("RelativeLocation"));
	ue::cached::offsets::LastFireTime = sdk_p->FindOffset(e("FortWeapon"), e("LastFireTime"));
	ue::cached::offsets::AmmoCount = sdk_p->FindOffset(e("FortWeapon"), e("AmmoCount"));
	ue::cached::offsets::LastFireTimeVerified = sdk_p->FindOffset(e("FortWeapon"), e("LastFireTimeVerified"));
	ue::cached::offsets::Tier = sdk_p->FindOffset(e("FortItemDefinition"), e("Tier"));

}



float color_speed = -10.0;
static ue::FLinearColor FromHSB(float hue, float saturation, float brightness)
{

	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return ue::FLinearColor(
			(float)(brightness),
			(float)(t),
			(float)(p),
			(float)(0.7f)
		);
	}
	else if (h < 2)
	{
		return ue::FLinearColor(
			(float)(q),
			(float)(brightness),
			(float)(p),
			(float)(0.7f)
		);
	}
	else if (h < 3)
	{
		return ue::FLinearColor(
			(float)(p),
			(float)(brightness),
			(float)(t),
			(float)(0.7f)
		);
	}
	else if (h < 4)
	{
		return ue::FLinearColor(
			(float)(p),
			(float)(q),
			(float)(brightness),
			(float)(0.7f)
		);
	}
	else if (h < 5)
	{
		return ue::FLinearColor(
			(float)(t),
			(float)(p),
			(float)(brightness),
			(float)(0.7f)
		);
	}
	else
	{
		return ue::FLinearColor(
			(float)(brightness),
			(float)(p),
			(float)(q),
			(float)(0.7f)
		);
	}
}