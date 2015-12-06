#pragma once

#include "types.hpp"

#pragma pack(push, 1)

/// Class for Utilities [IA-32e Mode]
/// TODO: Apply singleton
class kUtils
{
public:
    bool kPrintString(int iX, int iY, const char* pcString);
    
    // Memory operations
    void kMemSet(void* pvDestination, BYTE bData, int iSize);
    int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
    int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);
};

#pragma pack(pop)