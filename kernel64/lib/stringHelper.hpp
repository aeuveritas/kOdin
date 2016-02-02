#pragma once

#include <stdarg.h>
#include <types.hpp>

/// Enum for decimal type
enum kDECIMALTYPE {
    BINARY,
    OCTAL,
    DECIMAL,
    HEXADECIMAL
};

/// StringModifier [IA-32e Mode]
class kStringHelper
{
public:
    kStringHelper(void);
    ~kStringHelper(void);
    
    void kInitializeStringHelper(void);
    
    int kStrLen(const char* pcBuffer);
    void kReverseString(char* pcBuffer);
    long kAToI(const char* pcBuffer, kDECIMALTYPE _type);
    QWORD kHexStringToQword(const char* pcBuffer);
    long kDecimalStringToLong(const char* pcBuffer);
    int kIToA(long lValue, char* pcBuffer, kDECIMALTYPE _type);
    int kHexToString(QWORD qwValue, char* pcBuffer);
    int kDecimalToString(long lValue, char* pcBuffer);
    int kSPrintf(char* pcBuffer, const char* pcFormatString, ...);
    int kVSPrintf(char* pcBuffer, const char* pcFormatString, va_list ap);
};
