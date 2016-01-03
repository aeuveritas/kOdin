#pragma once

#include "types.hpp"

#pragma pack(push, 1)

/// Class for Utilities [IA-32e Mode]
/// TODO: Apply singleton
class kMemory
{
    QWORD qwTotalRAMSize = 0;
public:
    kMemory(void);
    ~kMemory(void);
    
    void kInitializeMemory(void);

    // Memory operations
    void kMemSet(void* pvDestination, BYTE bData, int iSize);
    int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
    int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);
    
    // RAM
    void kCheckTotalRAMSize(void);
    QWORD kGetTotalRAMSize(void);
};

#pragma pack(pop)