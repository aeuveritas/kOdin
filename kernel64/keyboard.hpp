#pragma once

#include "types.hpp"
#include "port.hpp"
#include "keyData.hpp"
#include "queue.hpp"

#pragma pack(push, 1)

/// Keyboard [IA-32e Mode]
class kKeyboard
{
    // class pointer for kPort
    kPort* a_pclPort;
    
    // Information for combination
    bool bShiftDown;
    bool bCapsLockOn;
    bool bNumLockOn;
    bool bScrollLockOn;
    
    // Information for extended key
    bool bExtendedCodeIn;
    int iSkipCountForPause;
    
    // Key queue
    kQueue clKeyQueue;
    KEYDATA stKeyQueueBuffer[KEY_MAXQUEUECOUNT];
    
    // Functions
    bool kActivateKeyboard(void);
    void kEnableA20Gate(void);
    bool kIsAlphabetScanCode(BYTE bScanCode);
    bool kIsNumberOrSymbolScanCode(BYTE bScanCode);
    bool kIsNumberPadScanCode(BYTE bScanCode);
    bool kIsUseCombinedCode(BYTE bScanCode);
    void kUpdateCombinationKeyStatusAndLED(BYTE bScanCode);
    bool kWaitForACKAndPushOtherScanCode(void);

public:
    kKeyboard(void);
    ~kKeyboard(void);
    
    bool kInitializeKeyboard(kPort* pclPort);
    bool kChangeKeyboardLED(bool bCapsLockOn, 
                            bool bNumLockOn, bool bScrollLockOn);
    bool kIsInputBufferFull(void);
    bool kIsOutputBufferFull(void);
    BYTE kGetKeyboardScanCode(void);
    bool kConvertScanCodeToASCIICode(BYTE bScanCode, 
                                     char* pbASCIICode, BYTE* pbFlags);
    bool kConvertScanCodeAndPushQueue(BYTE bScanCode);
    bool kPopKeyFromKeyQueue(KEYDATA* pstData);

    void kReboot(void);
};

#pragma pack(pop)