#pragma once

#define BYTE    unsigned char
#define WORD    unsigned short
#define DWORD   unsigned int
#define QWORD   unsigned long

#pragma pack(push, 1)

/// Data structure for text to print in video mode
typedef struct kCharactorStruct {
    /// Charactor
    BYTE bCharactor;
    /// Attribute
    BYTE bAttribute;
} CHARACTER;

#pragma pack(pop)

