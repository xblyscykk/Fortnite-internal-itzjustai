#pragma once
#include "include.h"

using _RtlCreateUserThread = NTSTATUS(NTAPI*)(
	HANDLE ProcessHandle,
	PSECURITY_DESCRIPTOR SecurityDescriptor,
	BOOLEAN CreateSuspend,
	ULONG StackZeroBits,
	PULONG StackReserved,
	PULONG StackCommit,
	void* StartAddress,
	void* StartParameter,
	PHANDLE ThreadHandle,
	void* ClientID
	);

void SpoofThread(void* Thread, HMODULE& hModule)
{
	HMODULE NT_DLL = LoadLibrary(e("ntdll"));
	uintptr_t SpoofedAddress = NULL;
	int DefaultThreadSize = 1000;
	srand(time(NULL)); // see random nums

	for (int i = 1; i < 4; i++) {
		SpoofedAddress |= (rand() & 0xFF) << i * 8; // we store it in the lowest bytes
		SpoofedAddress |= (rand() & 0xFF) << i * 8;
		SpoofedAddress |= (rand() & 0xFF) << i * 8;
		//returns spoofed address
	}
	while (SpoofedAddress > 0x7FFFFFFF) {
		SpoofedAddress -= 0x1500;
	}
	itsjustaispoof(VirtualProtect)((void*)SpoofedAddress, DefaultThreadSize, PAGE_EXECUTE_READWRITE, NULL);

	CONTEXT tContext;
	HANDLE  pHandle = nullptr;

	_RtlCreateUserThread KeThread = (_RtlCreateUserThread)(GetProcAddress(GetModuleHandle(e("ntdll")), e("RtlCreateUserThread")));
	KeThread(GetCurrentProcess(), nullptr, TRUE, NULL, NULL, NULL, (PTHREAD_START_ROUTINE)SpoofedAddress, hModule, &pHandle, NULL); //create a thread & stop init everything

	tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
	itsjustaispoof(GetThreadContext)(pHandle, &tContext);


	tContext.Rcx = (ULONG64)Thread;


	tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

	itsjustaispoof(SetThreadContext)(pHandle, &tContext);

	itsjustaispoof(ResumeThread)(pHandle);
}

DWORD GetModuleSize(DWORD64 base)
{
	IMAGE_DOS_HEADER dos_header = { 0 };
	IMAGE_NT_HEADERS nt_headers = { 0 };
	if (!base)return -1;
	dos_header = *(IMAGE_DOS_HEADER*)base;
	nt_headers = *(IMAGE_NT_HEADERS*)(base + dos_header.e_lfanew);
	return nt_headers.OptionalHeader.SizeOfImage;
}
typedef struct
{
	DWORD64 dwEP;
	void* pParam;
}CALL_MYFUNCTION, * PCALL_MYFUNCTION;
typedef DWORD(*_Function)(VOID* p);
void WINAPI MyFunctionThread(PCALL_MYFUNCTION pCMF)
{
	if (pCMF != NULL && pCMF->dwEP != NULL)
	{
		_Function Function = (_Function)pCMF->dwEP;
		Function(pCMF->pParam);
	}
}

HANDLE MyCreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, LPDWORD lpThreadId)
{
	HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
	if (hNtDll != NULL)
	{
		DWORD dwImageSize = GetModuleSize((DWORD64)hNtDll);
		
		BYTE* pMemoryData = (BYTE*)hNtDll + dwImageSize - 0x400;

		if (pMemoryData != NULL)
		{
			DWORD dwProtect;
			VirtualProtect(pMemoryData, 0x100, PAGE_EXECUTE_READWRITE, &dwProtect);
			CALL_MYFUNCTION* pCMF = (CALL_MYFUNCTION*)VirtualAlloc(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			pCMF->dwEP = (DWORD64)(lpStartAddress);
			pCMF->pParam = lpParameter;
			memcpy((LPVOID)pMemoryData, (LPVOID)MyFunctionThread, 0x100);
			HANDLE hHandle = CreateRemoteThread(GetCurrentProcess(), NULL, 0, (LPTHREAD_START_ROUTINE)pMemoryData, pCMF, NULL, lpThreadId);
			return hHandle;
		}
	}
	return 0;
}

void log(char* logstr...) {
	itsjustaispoof(AllocConsole)();
	itsjustaispoof(freopen)(e("CONOUT$"), e("w"), stdout);
	itsjustaispoof(printf)(logstr);
}


BOOL valid_pointer(DWORD64 address)
{
	if (!itsjustaispoof(IsBadWritePtr)((LPVOID)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}

template<typename ReadT>
ReadT read(DWORD_PTR address, const ReadT& def = ReadT())
{
	if (valid_pointer(address)) {
		return *(ReadT*)(address);
	}
}

template<typename WriteT>
bool write(DWORD_PTR address, WriteT value, const WriteT& def = WriteT())
{
	if (valid_pointer(address)) {
		*(WriteT*)(address) = value;
		return true;
	}
	return false;
}

void MsgBox(const char* str, ...)
{
	va_list vl;
	va_start(vl, str);
	char buff[1024];
	itsjustaispoof(vsprintf)(buff, str, vl);
	itsjustaispoof(MessageBoxA)(0, buff, e(""), MB_OK | MB_ICONQUESTION);
}
void DrawLine(UCanvas* Canvas, Vector2 position1, Vector2 position2, ue::FLinearColor color, int thickness = 1, bool screenCheck = false)
{

	Canvas->K2_DrawLine(position1, position2, thickness, color);
}
bool ingame;
void DrawCorneredBox(UCanvas* Canvas, Vector2 position, Vector2 size, int thickness, ue::FLinearColor colora) {


	float lineW = (size.x / 4);
	float lineH = (size.y / 4);

	//corners
	DrawLine(Canvas, Vector2(position.x, position.y), Vector2(position.x, position.y + lineH), colora, thickness);
	DrawLine(Canvas, Vector2(position.x, position.y), Vector2(position.x + lineW, position.y), colora, thickness);
	DrawLine(Canvas, Vector2(position.x + size.x - lineW, position.y), Vector2(position.x + size.x, position.y), colora, thickness);
	DrawLine(Canvas, Vector2(position.x + size.x, position.y), Vector2(position.x + size.x, position.y + lineH), colora, thickness);
	DrawLine(Canvas, Vector2(position.x, position.y + size.y - lineH), Vector2(position.x, position.y + size.y), colora, thickness);
	DrawLine(Canvas, Vector2(position.x, position.y + size.y), Vector2(position.x + lineW, position.y + size.y), colora, thickness);
	DrawLine(Canvas, Vector2(position.x + size.x - lineW, position.y + size.y), Vector2(position.x + size.x, position.y + size.y), colora, thickness);
	DrawLine(Canvas, Vector2(position.x + size.x, position.y + size.y - lineH), Vector2(position.x + size.x, position.y + size.y), colora, thickness);
}
static BOOL IsNotInScreen(int SizeX, int SizeY, Vector2 Pos) {
	if (((Pos.x <= 0 or Pos.x > SizeX) and (Pos.y <= 0 or Pos.y > SizeY)) or ((Pos.x <= 0 or Pos.x > SizeX) or (Pos.y <= 0 or Pos.y > SizeY))) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
void __forceinline AnsiToWide(char* inAnsi, wchar_t* outWide)
{

	int i = 0;
	for (; inAnsi[i] != '\0'; i++)
		outWide[i] = (wchar_t)(inAnsi)[i];
	outWide[i] = L'\0';
}
void __forceinline AnsiToWide(char const* inAnsi, wchar_t* outWide)
{

	int i = 0;
	for (; inAnsi[i] != '\0'; i++)
		outWide[i] = (wchar_t)(inAnsi)[i];
	outWide[i] = L'\0';
}
inline BOOL IsInScreen(Vector2 Pos)
{
	if (((Pos.x <= 0 or Pos.x > width) and (Pos.y <= 0 or Pos.y > height)) or ((Pos.x <= 0 or Pos.x > width) or (Pos.y <= 0 or Pos.y > height))) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

auto color = ue::FLinearColor(0.04f, 0.5f, 2.55f, 1.f);
auto bluee = ue::FLinearColor(0.04f, 0.5f, 2.55f, 1.f);
auto redd = ue::FLinearColor(2.55f, 0.f, 0.f, 2.55f);
auto cyan = ue::FLinearColor(0.40f, 2.21f, 2.10f, 2.55f);
auto white = ue::FLinearColor(1.f, 1.f, 1.f, 1.f);
auto Yellow = ue::FLinearColor(255.f, 255.f, 51.f, 2.55f);
auto green = ue::FLinearColor(0.f, 255.f, 0.f, 2.55f);