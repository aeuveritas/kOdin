#pragma once

#include "types.hpp"
#include "asmUtils.hpp"
#include "keyMappingEntry.hpp"

#pragma pack(push, 1)

/// Class for keyboard
class kKeyboard
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
    void kUpdateCombinationKeyStatusAndLED(BYTE bScanCode);
    
public:
    kKeyboard(void);
    ~kKeyboard(void);
    
    bool kActivateKeyboard(void);
    bool kChangeKeyboardLED(bool bCapsLockOn, 
                            bool bNumLockOn, bool bScrollLockOn);
    bool kIsInputBufferFull(void);
    bool kIsOutputBufferFull(void);
    BYTE kGetKeyboardScanCode(void);
    bool kConvertScanCodeToASCIICode(BYTE bScanCode, 
                                     char* pbASCIICode, BYTE* pbFlags);
};

#pragma pack(pop)