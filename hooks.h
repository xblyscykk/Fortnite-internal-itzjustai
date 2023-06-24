#pragma once

#include <Windows.h>
#include <SetupAPI.h>
#include <string>
#include <codecvt>
#include <fstream>
#include <iostream>

static bool debug = true;

int (*GetWindowTextAOriginal)(HWND hWnd, LPSTR lpString, int nMaxCount) = nullptr;
int (*GetWindowTextWOriginal)(HWND hWnd, LPWSTR lpString, int nMaxCount) = nullptr;

LSTATUS (*RegQueryValueExAOriginal)(
	HKEY    hKey,
	LPCSTR  lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
) = nullptr;

LSTATUS (*RegCloseKeyOriginal)(
	HKEY hKey
) = nullptr;

LSTATUS(*RegCreateKeyAOriginal)(
	HKEY   hKey,
	LPCSTR lpSubKey,
	PHKEY  phkResult
) = nullptr;

LSTATUS (*RegOpenKeyExAOriginal)(
	HKEY   hKey,
	LPCSTR lpSubKey,
	DWORD  ulOptions,
	REGSAM samDesired,
	PHKEY  phkResult
) = nullptr;

HANDLE(*CreateFileAOriginal)(
	LPCSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
	) = nullptr;

HANDLE(*CreateFileWOriginal)(
	LPCWSTR               lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
	) = nullptr;
BOOL(*DeviceIoControlOriginal)(
	HANDLE       hDevice,
	DWORD        dwIoControlCode,
	LPVOID       lpInBuffer,
	DWORD        nInBufferSize,
	LPVOID       lpOutBuffer,
	DWORD        nOutBufferSize,
	LPDWORD      lpBytesReturned,
	LPOVERLAPPED lpOverlapped
	) = nullptr;

BOOL(*SetupDiGetDevicePropertyWOriginal)(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	const DEVPROPKEY* PropertyKey,
	DEVPROPTYPE* PropertyType,
	PBYTE            PropertyBuffer,
	DWORD            PropertyBufferSize,
	PDWORD           RequiredSize,
	DWORD            Flags
	) = nullptr;

BOOL(*SetupDiGetDeviceRegistryPropertyWOriginal)(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	DWORD            Property,
	PDWORD           PropertyRegDataType,
	PBYTE            PropertyBuffer,
	DWORD            PropertyBufferSize,
	PDWORD           RequiredSize
	) = nullptr;

BOOL(*SetupDiGetDeviceInstanceIdWOrignal)(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	PWSTR            DeviceInstanceId,
	DWORD            DeviceInstanceIdSize,
	PDWORD           RequiredSize
	) = nullptr;

LSTATUS(*RegSetValueExWOriginal)(
	HKEY       hKey,
	LPCWSTR    lpValueName,
	DWORD      Reserved,
	DWORD      dwType,
	const BYTE* lpData,
	DWORD      cbData
	) = nullptr;

LSTATUS(*RegGetValueWOriginal)(
	HKEY    hkey,
	LPCWSTR lpSubKey,
	LPCWSTR lpValue,
	DWORD   dwFlags,
	LPDWORD pdwType,
	PVOID   pvData,
	LPDWORD pcbData
	) = nullptr;

LSTATUS(*RegDeleteKeyWOriginal)(
	HKEY    hKey,
	LPCWSTR lpSubKey
	) = nullptr;

LSTATUS(*RegEnumKeyExWOriginal)(
	HKEY      hKey,
	DWORD     dwIndex,
	LPWSTR    lpName,
	LPDWORD   lpcchName,
	LPDWORD   lpReserved,
	LPWSTR    lpClass,
	LPDWORD   lpcchClass,
	PFILETIME lpftLastWriteTime
	) = nullptr;

LSTATUS(*RegEnumValueWOriginal)(
	HKEY    hKey,
	DWORD   dwIndex,
	LPWSTR  lpValueName,
	LPDWORD lpcchValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
	) = nullptr;

LSTATUS(*RegCreateKeyExWOriginal)(
	HKEY                        hKey,
	LPCWSTR                     lpSubKey,
	DWORD                       Reserved,
	LPWSTR                      lpClass,
	DWORD                       dwOptions,
	REGSAM                      samDesired,
	const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY                       phkResult,
	LPDWORD                     lpdwDisposition
	) = nullptr;

LSTATUS(*RegQueryInfoKeyAOriginal)(
	HKEY      hKey,
	LPSTR     lpClass,
	LPDWORD   lpcchClass,
	LPDWORD   lpReserved,
	LPDWORD   lpcSubKeys,
	LPDWORD   lpcbMaxSubKeyLen,
	LPDWORD   lpcbMaxClassLen,
	LPDWORD   lpcValues,
	LPDWORD   lpcbMaxValueNameLen,
	LPDWORD   lpcbMaxValueLen,
	LPDWORD   lpcbSecurityDescriptor,
	PFILETIME lpftLastWriteTime
	) = nullptr;

LSTATUS(*RegOpenKeyExWOriginal)(
	HKEY    hKey,
	LPCWSTR lpSubKey,
	DWORD   ulOptions,
	REGSAM  samDesired,
	PHKEY   phkResult
	) = nullptr;

LSTATUS(*RegQueryValueExWOriginal)(
	HKEY    hKey,
	LPCWSTR lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
	) = nullptr;

LSTATUS(*RegEnumKeyExAOriginal)(
	HKEY      hKey,
	DWORD     dwIndex,
	LPSTR     lpName,
	LPDWORD   lpcchName,
	LPDWORD   lpReserved,
	LPSTR     lpClass,
	LPDWORD   lpcchClass,
	PFILETIME lpftLastWriteTime
	) = nullptr;

LSTATUS(*RegDeleteValueWOriginal)(
	HKEY    hKey,
	LPCWSTR lpValueName
	) = nullptr;

int GetWindowTextAHook(HWND hWnd, LPSTR lpString, int nMaxCount) {
	return 0;
}

int GetWindowTextWHook(HWND hWnd, LPWSTR lpString, int nMaxCount) {
	return 0;
}

//Registry hooks
LSTATUS RegOpenKeyExAHook(
	HKEY   hKey,
	LPCSTR lpSubKey,
	DWORD  ulOptions,
	REGSAM samDesired,
	PHKEY  phkResult
)
{
	std::cout << "RegOpenKeyExAHook: " << lpSubKey << std::endl;
	return RegOpenKeyExAOriginal(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LSTATUS RegCloseKeyHook(
	HKEY hKey
)
{
	return RegCloseKeyOriginal(hKey);
}

LSTATUS RegQueryValueExAHook(
	HKEY    hKey,
	LPCSTR  lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
)
{
	std::cout << "RegQueryValueExAHook: " << lpValueName << std::endl;
	return RegQueryValueExAOriginal(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

LSTATUS RegQueryValueExWHook(
	HKEY    hKey,
	LPCWSTR lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
)
{
	if (wcsstr(lpValueName, L"Debug"))
	{
		return RegQueryValueExWOriginal(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	}
	
	std::cout << "RegQueryValueExWHook: " << lpValueName << std::endl;
	return RegQueryValueExWOriginal(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

LSTATUS RegEnumValueWHook(
	HKEY    hKey,
	DWORD   dwIndex,
	LPWSTR  lpValueName,
	LPDWORD lpcchValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE  lpData,
	LPDWORD lpcbData
)
{
	std::cout << "RegEnumValueWHook: " << lpValueName << std::endl;
	return RegEnumValueWOriginal(hKey, dwIndex, lpValueName, lpcchValueName, lpReserved, lpType, lpData, lpcbData);
}

LSTATUS RegQueryInfoKeyAHook(
	HKEY      hKey,
	LPSTR     lpClass,
	LPDWORD   lpcchClass,
	LPDWORD   lpReserved,
	LPDWORD   lpcSubKeys,
	LPDWORD   lpcbMaxSubKeyLen,
	LPDWORD   lpcbMaxClassLen,
	LPDWORD   lpcValues,
	LPDWORD   lpcbMaxValueNameLen,
	LPDWORD   lpcbMaxValueLen,
	LPDWORD   lpcbSecurityDescriptor,
	PFILETIME lpftLastWriteTime
)
{
	std::cout << "RegQueryInfoKeyAHook: " << lpClass << std::endl;

	return RegQueryInfoKeyAOriginal(hKey, lpClass, lpcchClass, lpReserved, lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues, lpcbMaxValueNameLen,
		lpcbMaxValueLen, lpcbSecurityDescriptor, lpftLastWriteTime);
}

LSTATUS RegEnumKeyExAHook(
	HKEY      hKey,
	DWORD     dwIndex,
	LPSTR     lpName,
	LPDWORD   lpcchName,
	LPDWORD   lpReserved,
	LPSTR     lpClass,
	LPDWORD   lpcchClass,
	PFILETIME lpftLastWriteTime
)
{
	std::cout << "RegEnumKeyExAHook: " << lpName << std::endl;
	return RegEnumKeyExAOriginal(hKey, dwIndex, lpName, lpcchName, lpReserved, lpClass, lpcchClass, lpftLastWriteTime);
}

LSTATUS RegEnumKeyExWHook(
	HKEY      hKey,
	DWORD     dwIndex,
	LPWSTR    lpName,
	LPDWORD   lpcchName,
	LPDWORD   lpReserved,
	LPWSTR    lpClass,
	LPDWORD   lpcchClass,
	PFILETIME lpftLastWriteTime
)
{
	std::cout << "RegEnumKeyExWHook " << lpName << std::endl;
	return RegEnumKeyExWOriginal(hKey, dwIndex, lpName, lpcchName, lpReserved, lpClass, lpcchClass, lpftLastWriteTime);
}

LSTATUS RegDeleteValueWHook(
	HKEY    hKey,
	LPCWSTR lpValueName
)
{
	std::cout << "RegDeleteValueWHook: " << lpValueName << std::endl;
	return RegDeleteValueWOriginal(hKey, lpValueName);
}

LSTATUS RegDeleteKeyWHook(
	HKEY    hKey,
	LPCWSTR lpSubKey
)
{
	std::cout << "RegDeleteValueWHook: " << lpSubKey << std::endl;
	return RegDeleteKeyWOriginal(hKey, lpSubKey);
}

LSTATUS RegGetValueWHook(
	HKEY    hkey,
	LPCWSTR lpSubKey,
	LPCWSTR lpValue,
	DWORD   dwFlags,
	LPDWORD pdwType,
	PVOID   pvData,
	LPDWORD pcbData
)
{
	std::cout << "RegGetValueWHook: " << lpValue << std::endl;
	return RegGetValueWOriginal(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
}

LSTATUS RegSetValueExWHook(
	HKEY       hKey,
	LPCWSTR    lpValueName,
	DWORD      Reserved,
	DWORD      dwType,
	const BYTE* lpData,
	DWORD      cbData
)
{
	std::cout << "RegSetValueExWHook: " << lpValueName << std::endl;
	return RegSetValueExWOriginal(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

LSTATUS RegOpenKeyExWHook(
	HKEY    hKey,
	LPCWSTR lpSubKey,
	DWORD   ulOptions,
	REGSAM  samDesired,
	PHKEY   phkResult
)
{
	if (!wcsstr(lpSubKey, L"Software\\Razer\\ChromaBroadcast"))
	{
		std::cout << "RegOpenKeyExWHook:" << lpSubKey << std::endl;
	}

	return RegOpenKeyExWOriginal(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LSTATUS RegCreateKeyExWHook(
	HKEY                        hKey,
	LPCWSTR                     lpSubKey,
	DWORD                       Reserved,
	LPWSTR                      lpClass,
	DWORD                       dwOptions,
	REGSAM                      samDesired,
	const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY                       phkResult,
	LPDWORD                     lpdwDisposition
)
{
	std::cout << "RegCreateKeyExWHook: " << lpSubKey << " " << lpClass << std::endl;
	return RegCreateKeyExWOriginal(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

LSTATUS RegCreateKeyAHook(
	HKEY   hKey,
	LPCSTR lpSubKey,
	PHKEY  phkResult
)
{
	std::cout << "RegCreateKeyAHook: " << lpSubKey << std::endl;
	return RegCreateKeyAOriginal(hKey, lpSubKey, phkResult);
}

HANDLE CreateFileAHook(
	LPCSTR                file_name,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
	)
{
	if(debug)
		std::cout << "CreateFileA: " << file_name << std::endl;

	if (strstr(file_name, "BattlEye") || strstr(file_name, "EasyAntiCheat"))
	{
		return CreateFileAOriginal(file_name, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}

	return INVALID_HANDLE_VALUE;
}

HANDLE CreateFileWHook(
	LPCWSTR               lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
	)
{
	/*std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	std::wstring wide;
	std::string str;

	wide = lpFileName;

	str = conv.to_bytes(wide);*/

	if (wcsstr(lpFileName, L"Fortnite"))
	{
		if(debug)
			std::cout << "CreateFileW: " << lpFileName << std::endl;

		return CreateFileWOriginal(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}

	return NULL;
}

BOOL DeviceIoControlHook(
	HANDLE       hDevice,
	DWORD        dwIoControlCode,
	LPVOID       lpInBuffer,
	DWORD        nInBufferSize,
	LPVOID       lpOutBuffer,
	DWORD        nOutBufferSize,
	LPDWORD      lpBytesReturned,
	LPOVERLAPPED lpOverlapped
	)
{
	if (dwIoControlCode == IOCTL_STORAGE_QUERY_PROPERTY)
	{
		return 0;
	}

	return DeviceIoControlOriginal(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

BOOL SetupDiGetDevicePropertyWHook(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	const DEVPROPKEY* PropertyKey,
	DEVPROPTYPE* PropertyType,
	PBYTE            PropertyBuffer,
	DWORD            PropertyBufferSize,
	PDWORD           RequiredSize,
	DWORD            Flags
	)
{
	return 0;
}

BOOL SetupDiGetDeviceRegistryPropertyWHook(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	DWORD            Property,
	PDWORD           PropertyRegDataType,
	PBYTE            PropertyBuffer,
	DWORD            PropertyBufferSize,
	PDWORD           RequiredSize
	)
{
	return 0;
}

BOOL SetupDiGetDeviceInstanceIdWHook(
	HDEVINFO         DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	PWSTR            DeviceInstanceId,
	DWORD            DeviceInstanceIdSize,
	PDWORD           RequiredSize
	)
{
	return 0;
}
