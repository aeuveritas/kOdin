#pragma once

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int    DWORD;
typedef unsigned long   QWORD;

#pragma pack(push, 1)

/// Data structure for text to print in video mode [IA-32e Mode]
typedef struct kCharactorStruct {
    /// Charactor
    BYTE bCharactor;
    /// Attribute
    BYTE bAttribute;
} CHARACTER;

#pragma pack(pop)

