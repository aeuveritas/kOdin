#pragma once

#pragma pack(push, 1)

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int    DWORD;
typedef unsigned long   QWORD;

/// Data structure for text to print in video mode [IA-32e Mode]
typedef struct kCharactorStruct {
    /// Charactor
    BYTE bCharactor;
    /// Attribute
    BYTE bAttribute;
} CHARACTER;

#pragma pack(pop)

