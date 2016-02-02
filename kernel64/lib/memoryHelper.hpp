#pragma once

#include <types.hpp>

#pragma pack(push, 1)

/// TODO: Apply singleton
/// Memory utilities [IA-32e Mode]
class kMemoryHelper
{
    QWORD qwTotalRAMSize = 0;
public:
    kMemoryHelper(void);
    ~kMemoryHelper(void);
    
    void kInitializeMemoryHelper(void);

    // Memory operations
    void kMemSet(void* pvDestination, BYTE bData, int iSize);
    int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
    int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);
    
    // RAM
    void kCheckTotalRAMSize(void);
    QWORD kGetTotalRAMSize(void);
};

#pragma pack(pop)