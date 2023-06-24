// Authored by Tristan aka HylianTimelord
// Posted for my dudes @ unknowncheats.me
// Creds to IAmDaz for suggesting memcpy & void*

#pragma once

#include <Windows.h>
#include <map>
#include <cassert>

using namespace std;

class VMTHook
{
public:

	void** vmt = nullptr; // Pointer to the VMT, we're using it more as an array of void*

	VMTHook(void* vmt); // Hook original VMT by it's address
	VMTHook(DWORD64* vmt_ptr); // Create Shadow VMT from VMT pointer ( Not implemented here )
	~VMTHook(); // Destructor, removes all hooks

	void* Hook(int index, void* hk);
	void ClearHooks();
private:
	map<int, void*>::iterator func_iterator; // Iterator so we can iterate the map below
	map<int, void*> hooked_funcs; // std::map which holds the index hooked and the original function's address
};

VMTHook::VMTHook(void* vmt_addy)
{
	vmt = (void**)vmt_addy;
}
void* TrampHook64(void* src, void* dst, int len)
{
	if (len < 14) return nullptr;

	BYTE stub[14] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,				// jmp qword ptr instruction
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 8 byte ptr to jmp destination
	};

	void* pTrampoline = VirtualAlloc(0, len + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD oldProtect = 0;
	itsjustaispoof(VirtualProtect)(src, len, PAGE_EXECUTE_READWRITE, &oldProtect);

	uintptr_t jmpBackAddr = (uintptr_t)src + len;

	// copy trampoline jmpback addr to stub
	memcpy(stub + 6, &jmpBackAddr, 8);
	// copy stolen bytes to trampoline
	memcpy((void*)(pTrampoline), src, len);
	// copy stub to trampoline
	memcpy((void*)((uintptr_t)pTrampoline + len), stub, sizeof(stub));

	// copy dst to the stub, creating our jmp to our hook function
	memcpy(stub + 6, &dst, 8);
	// copy new stub to src
	memcpy(src, stub, sizeof(stub));

	// nop any stolen bytes in src
	for (int i = 14; i < len; i++)
	{
		*(BYTE*)((uintptr_t)src + i) = 0x90;
	}

	itsjustaispoof(VirtualProtect)(src, len, oldProtect, &oldProtect);
	return (void*)(pTrampoline);
}
void* VMTHook::Hook(int index, void* hk)
{
	// Store the index and original function address
	hooked_funcs.insert(make_pair(index, vmt[index]));
	
	// Change the memory's access rights, patch the address to our hook, restore original rights
	DWORD old;
	itsjustaispoof(VirtualProtect)(&vmt[index], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	
	vmt[index] = hk;
	
	itsjustaispoof(VirtualProtect)(&vmt[index], sizeof(void*), old, NULL);
	
	return hooked_funcs[index];

}

void VMTHook::ClearHooks()
{
	for (func_iterator = hooked_funcs.begin(); func_iterator != hooked_funcs.end(); func_iterator++)
	{
		
		DWORD old;
		itsjustaispoof(VirtualProtect)(&vmt[func_iterator->first], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
		
		vmt[func_iterator->first] = func_iterator->second;
		
		itsjustaispoof(VirtualProtect)(&vmt[func_iterator->first], sizeof(void*), old, NULL);
		
	}
	hooked_funcs.clear();
	vmt = nullptr;
}

VMTHook::~VMTHook() {}

//paste by JeremyOnTop#0001