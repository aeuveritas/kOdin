#pragma once

#include "types.hpp"
#include "utils.hpp"
#include "port.hpp"
#include "keyData.hpp"
#include "queue.hpp"

#pragma pack(push, 1)

/// Class for keyboard [IA-32e Mode]
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
    void kReboot(void);
    bool kIsAlphabetScanCode(BYTE bScanCode);
    bool kIsNumberOrSymbolScanCode(BYTE bScanCode);
    bool kIsNumberPadScanCode(BYTE bScanCode);
    bool kIsUseCombinedCode(BYTE bScanCode);
    void kUpdateCombinationKeyStatusAndLED(BYTE bScanCode);
    bool kWaitForACKAndPushOtherScanCode(void);

public:
    kKeyboard(void);
    ~kKeyboard(void);
    
    bool kInitializeKeyboard(kPort* _kPort);
    bool kChangeKeyboardLED(bool bCapsLockOn, 
                            bool bNumLockOn, bool bScrollLockOn);
    bool kIsInputBufferFull(void);
    bool kIsOutputBufferFull(void);
    BYTE kGetKeyboardScanCode(void);
    bool kConvertScanCodeToASCIICode(BYTE bScanCode, 
                                     char* pbASCIICode, BYTE* pbFlags);
    bool kConvertScanCodeAndPushQueue(BYTE bScanCode);
    bool kPopKeyFromKeyQueue(KEYDATA* pstData);
};

#pragma pack(pop)