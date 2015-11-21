#pragma once

#include "types.hpp"
#include "asmUtils.hpp"
#include "keyMappingEntry.hpp"

class kKeyboardManager
{
    // Information for combination
    bool bShiftDown;
    bool bCapsLockOn;
    bool bNumLockOn;
    bool bScrollLockOn;
    
    // Information for extended key
    bool bExtendedCodeIn;
    int iSkipCountForPause;
    
    // Functions
    void kEnableA20Gate(void);
    void kReboot(void);
    bool kIsAlphabetScanCode(BYTE bScanCode);
    bool kIsNumberOrSymbolScanCode(BYTE bScanCode);
    bool kIsNumberPadScanCode(BYTE bScanCode);
    bool kIsUseCombinedCode(BYTE bScanCode);
    void updateCombinationKeyStatusAndLED(BYTE bScanCode);
    
public:
    kKeyboardManager();
    
    bool kActivateKeyboard(void);
    bool kChangeKeyboardLED(bool bCapsLockOn, 
                            bool bNumLockOn, bool bScrollLockOn);
    bool kIsInputBufferFull(void);
    bool kIsOutputBufferFull(void);
    BYTE kGetKeyboardScanCode(void);
    bool kConvertScanCodeToASCIICode(BYTE bScanCode, 
                                     char* pbASCIICode, BYTE* pbFlags);
};