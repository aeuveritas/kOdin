#pragma once

#include "types.hpp"

#pragma pack(push, 1)

/// Class for Utilities [IA-32e Mode]
/// TODO: Apply singleton
class kUtils
{
    DWORD dwLine;
    DWORD dwXIndex;
    DWORD dwPairLine;
    
public:
    void kInitializeUtils(DWORD offset);
    
    // Print message
    bool kPrintString(int iX, int iY, const char* pcString);
    bool kPrintChar(const char* pcString);
    bool kPrintMessage(const char* pcString);
    bool kPrintResult(const char* pcString);
    void kPrintException(const char* pcVectorNumber);
    bool kPrintInterrupt(const char* pcString);
    bool kPrintKeyboardInterrupt(const char* pcString);
    
    // Print pair message
    bool kPrintPairMessage(const char* pcString);
    bool kPrintPairResult(const char* pcString);
    
    // Memory operations
    void kMemSet(void* pvDestination, BYTE bData, int iSize);
    int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
    int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);

    // Debug
    void kLock(void);
};

#pragma pack(pop)