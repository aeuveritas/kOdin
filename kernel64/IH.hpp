#pragma once

#include "types.hpp"
#include "keyboard.hpp"
#include "PIC.hpp"

#pragma pack(push, 1)

extern "C" {
    void _kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode);
    void _kCommonInterruptHandler(int iVectorNumber);
    void _kKeyboardHandler(int iVectorNumber);

    void _kEnableInterrupt(void);
    void _kDisableInterrupt(void);
    QWORD _kReadRFLAGS(void);
};

/// Class for interrupt handler
class kIH
{
    kPIC* a_pclPIC;
    kKeyboard* a_pclKeyboard;
    
    int iCommonInterruptCount;
    int iKeyboardInterruptCount;
    
    void kDecodeError(QWORD qwCode, char* value);
    
public:
    kIH(void);
    ~kIH(void);
    
    void kInitializeIH(kPIC* _kPIC, kKeyboard* _kKeyboard);
    
    void kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode);
    void kCommonInterruptHandler(int iVectorNumber);
    void kKeyboardHandler(int iVectorNumber);

    void kEnableInterrupt(void);
    void kDisableInterrupt(void);
    QWORD kReadRFLAGS(void);

    // Flag
    bool kSetInterruptFlag(bool bEnableInterrupt);
};


#pragma pack(pop)