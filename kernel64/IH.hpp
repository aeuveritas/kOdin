#pragma once

#include "types.hpp"
#include "utils.hpp"
#include "PIC.hpp"

#pragma pack(push, 1)

extern "C" {
    void _kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode);
    void _kCommonInterruptHandler(int iVectorNumber);
    void _kKeyboardHandler(int iVectorNumber);
}

/// Class for interrupt handler
class kIH
{
    kPIC* a_pclPIC;
    
    int iCommonInterruptCount;
    int iKeyboardInterruptCount;
    
    void kDecodeError(QWORD qwCode, char* value);
    
public:
    kIH(void);
    ~kIH(void);
    
    void kInitializeIH(kPIC* _kPIC);
    
    void kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode);
    void kCommonInterruptHandler(int iVectorNumber);
    void kKeyboardHandler(int iVectorNumber);
};


#pragma pack(pop)