#ifndef LOWKEY_H
#define LOWKEY_H
#include <sal.h>

#endif //LOWKEY_H

// types


typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    _Field_size_bytes_part_opt_(MaximumLength, Length) PWCH Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor; // PSECURITY_DESCRIPTOR;
    PVOID SecurityQualityOfService; // PSECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PIO_APC_ROUTINE)(
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );



//functions

typedef NTSTATUS(NTAPI *NtCreateFile)
(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength
    );

typedef NTSTATUS(NTAPI *NtOpenKey)(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

typedef NTSTATUS(NTAPI *NtCreateKey)(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition
    );
typedef NTSTATUS(NTAPI *NtWriteFile)
(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );


static const char ascii_lookup[128] = {
    '\0',   // 0  Null character
    '\x01', // 1  Start of Header
    '\x02', // 2  Start of Text
    '\x03', // 3  End of Text
    '\x04', // 4  End of Transmission
    '\x05', // 5  Enquiry
    '\x06', // 6  Acknowledge
    '\x07', // 7  Bell
    '\x08', // 8  Backspace
    '\t',   // 9  Horizontal Tab
    '\n',   // 10 Line Feed
    '\x0B', // 11 Vertical Tab
    '\x0C', // 12 Form Feed
    '\r',   // 13 Carriage Return
    '\x0E', // 14 Shift Out
    '\x0F', // 15 Shift In
    '\x10', // 16 Data Link Escape
    '\x11', // 17 Device Control 1
    '\x12', // 18 Device Control 2
    '\x13', // 19 Device Control 3
    '\x14', // 20 Device Control 4
    '\x15', // 21 Negative Acknowledge
    '\x16', // 22 Synchronous Idle
    '\x17', // 23 End of Transmission Block
    '\x18', // 24 Cancel
    '\x19', // 25 End of Medium
    '\x1A', // 26 Substitute
    '\x1B', // 27 Escape
    '\x1C', // 28 File Separator
    '\x1D', // 29 Group Separator
    '\x1E', // 30 Record Separator
    '\x1F', // 31 Unit Separator
    ' ',    // 32 Space
    '!',    // 33 Exclamation mark
    '"',    // 34 Double quote
    '#',    // 35 Hash
    '$',    // 36 Dollar sign
    '%',    // 37 Percent
    '&',    // 38 Ampersand
    '\'',   // 39 Single quote
    '(',    // 40 Left parenthesis
    ')',    // 41 Right parenthesis
    '*',    // 42 Asterisk
    '+',    // 43 Plus
    ',',    // 44 Comma
    '-',    // 45 Hyphen
    '.',    // 46 Period
    '/',    // 47 Slash
    '0',    // 48 Digit 0
    '1',    // 49 Digit 1
    '2',    // 50 Digit 2
    '3',    // 51 Digit 3
    '4',    // 52 Digit 4
    '5',    // 53 Digit 5
    '6',    // 54 Digit 6
    '7',    // 55 Digit 7
    '8',    // 56 Digit 8
    '9',    // 57 Digit 9
    ':',    // 58 Colon
    ';',    // 59 Semicolon
    '<',    // 60 Less than
    '=',    // 61 Equals
    '>',    // 62 Greater than
    '?',    // 63 Question mark
    '@',    // 64 At sign
    'A',    // 65 Uppercase A
    'B',    // 66 Uppercase B
    'C',    // 67 Uppercase C
    'D',    // 68 Uppercase D
    'E',    // 69 Uppercase E
    'F',    // 70 Uppercase F
    'G',    // 71 Uppercase G
    'H',    // 72 Uppercase H
    'I',    // 73 Uppercase I
    'J',    // 74 Uppercase J
    'K',    // 75 Uppercase K
    'L',    // 76 Uppercase L
    'M',    // 77 Uppercase M
    'N',    // 78 Uppercase N
    'O',    // 79 Uppercase O
    'P',    // 80 Uppercase P
    'Q',    // 81 Uppercase Q
    'R',    // 82 Uppercase R
    'S',    // 83 Uppercase S
    'T',    // 84 Uppercase T
    'U',    // 85 Uppercase U
    'V',    // 86 Uppercase V
    'W',    // 87 Uppercase W
    'X',    // 88 Uppercase X
    'Y',    // 89 Uppercase Y
    'Z',    // 90 Uppercase Z
    '[',    // 91 Left square bracket
    '\\',   // 92 Backslash
    ']',    // 93 Right square bracket
    '^',    // 94 Caret
    '_',    // 95 Underscore
    '`',    // 96 Grave accent
    'a',    // 97 Lowercase a
    'b',    // 98 Lowercase b
    'c',    // 99 Lowercase c
    'd',    // 100 Lowercase d
    'e',    // 101 Lowercase e
    'f',    // 102 Lowercase f
    'g',    // 103 Lowercase g
    'h',    // 104 Lowercase h
    'i',    // 105 Lowercase i
    'j',    // 106 Lowercase j
    'k',    // 107 Lowercase k
    'l',    // 108 Lowercase l
    'm',    // 109 Lowercase m
    'n',    // 110 Lowercase n
    'o',    // 111 Lowercase o
    'p',    // 112 Lowercase p
    'q',    // 113 Lowercase q
    'r',    // 114 Lowercase r
    's',    // 115 Lowercase s
    't',    // 116 Lowercase t
    'u',    // 117 Lowercase u
    'v',    // 118 Lowercase v
    'w',    // 119 Lowercase w
    'x',    // 120 Lowercase x
    'y',    // 121 Lowercase y
    'z',    // 122 Lowercase z
    '{',    // 123 Left curly brace
    '|',    // 124 Vertical bar
    '}',    // 125 Right curly brace
    '~',    // 126 Tilde
    '\x7F'  // 127 Delete
};
