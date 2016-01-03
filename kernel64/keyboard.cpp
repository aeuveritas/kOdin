#include "keyboard.hpp"
#include "interruptHandler.hpp"

extern kIH* g_pclIH;

/// Constructor
kKeyboard::kKeyboard(void) 
{
    a_pclPort = nullptr;
    bShiftDown = false;
    bCapsLockOn = false;
    bNumLockOn = false;
    bScrollLockOn = false;
    bExtendedCodeIn = false; 
    iSkipCountForPause = 0;
}

/// Deconstructor
kKeyboard::~kKeyboard(void) 
{
    a_pclPort = nullptr;
    bShiftDown = false;
    bCapsLockOn = false;
    bNumLockOn = false;
    bScrollLockOn = false;
    bExtendedCodeIn = false; 
    iSkipCountForPause = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Functions related to keyboard controller and keyboard 
///////////////////////////////////////////////////////////////////////////////
/// Initialize kKeyboard
bool kKeyboard::kInitializeKeyboard(kPort* _kPort)
{
    // Link class port
    a_pclPort = _kPort;
    
    // Initialize queue
    clKeyQueue.kInitializeQueue(stKeyQueueBuffer,
                                KEY_MAXQUEUECOUNT,
                                sizeof(KEYDATA));
    
    // Activate keyboard
    return kActivateKeyboard();
}

/** 
 * Check whether or not there is a received data 
 * in the output buffer (port 0x60).
 **/
bool kKeyboard::kIsOutputBufferFull(void)
{
    // Read the state register (port 0x64), 
    // and check the output buffer state bit (= Bit 0) is 1.
    // If it is 1, there is data from a keyboard.
    if (a_pclPort->kInPortByte(0x64) & 0x01)
    {
        return true;
    }
    
    return false;
}

/// Check whether ot nor there is a data in the input buffer (port 0x60).
bool kKeyboard::kIsInputBufferFull(void)
{
    // Read the state register (port 0x64),
    // and check the input buffer state bit (=x Bit 1) is 1.
    // IF it is 1, there is still data.
    if (a_pclPort->kInPortByte(0x64) & 0x02)
    {
        return true;
    }
    
    return false;
}

/** 
 * Wait for the ACK signal
 * If a received signal is not the ACK signal,
 * translate Scan Code and push it
 **/
bool kKeyboard::kWaitForACKAndPushOtherScanCode(void)
{
    bool bResult = false;
    BYTE bData;
    
    // It is possible to receive key data before the ACK signal
    // "kOdin" receives 100 data, and find the ACK signal among them
    for (int j = 0; j < 100; j++)
    {
        // The time to count from 0 to 0xFFF is enough
        // If the ACK signal is not shown, skip this step
        for (int i = 0; i < 0xFFFF; i++)
        {
            // If the output buffer(port 0x60) is full, it is readable
            if (kIsOutputBufferFull() == true)
            {
                break;
            }
        }
        
        // If the data from the output buffer(port 0x60) is
        // the ACK signal (0xFA), it returns true
        bData = _kInPortByte(0x60);
        if(bData == 0xFA)
        {
            bResult = true;
            break;
        }
        // If it is not 0xFA, translate it to ASCII code and push it
        else
        {
            kConvertScanCodeAndPushQueue(bData);
        }
    }
    
    return bResult;
}


/// Activate keyboard.
bool kKeyboard::kActivateKeyboard(void)
{
    bool bPreviousInterrupt;
    bool bResult;
    
    // Disable an interrupt
    bPreviousInterrupt = g_pclIH->kSetInterruptFlag(false);
   
    // Activate a keyboard device by sending keyboard activating command (0xAE)
    // to the control register (0x64).
    a_pclPort->kOutPortByte(0x64, 0xAE);
    
    // Wait for the input buffer (port 0x60) being empty.
    // If it is empty, send the command.
    // The maximum wait time is 0xFFFF.
    // If it is not empty until 0xFFFF, ignore previous data and send it.
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the input buffer (port 0x60) is empty, send the message.
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Activate a keyboard by sending keyboard activating command (0xF4)
    // to the input buffer (0x60).
    a_pclPort->kOutPortByte(0x60, 0xF4);
    
    // Wait for the ACK signal
    bResult = kWaitForACKAndPushOtherScanCode();
    
    // Restore the previous state of the interrupt flag
    g_pclIH->kSetInterruptFlag(bPreviousInterrupt);
    
    return bResult;
}

/// Read a key from the output buffer (port 0x60).
BYTE kKeyboard::kGetKeyboardScanCode(void)
{
    // Wait until the output buffer (port 0x60) is full.
    while (kIsOutputBufferFull() == false)
    {
        ;
    }
    
    return a_pclPort->kInPortByte(0x60);
}

/// Change the sate of LEDs.
bool kKeyboard::kChangeKeyboardLED(bool bCapsLockOn,
                                   bool bNumLockOn, bool bScrollLockOn)
{
    int bufferCount;
    bool bPreviousInterrupt;
    bool bResult;
    BYTE bData;
    
    // Disable an interrupt
    bPreviousInterrupt = g_pclIH->kSetInterruptFlag(false);
    
    // Send LED commands to a keyboard and wait until the command is done.
    for (int i = 0; i < 0xFFFF; i++)
    {
        // Send command if the input buffer (port 0x60) is empty.
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Send LED state change command (0xED) to the output buffer (port 0x60).
    a_pclPort->kOutPortByte(0x60, 0xED);
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the inpur buffer (port 0x60) is empty,
        // the keyboard takes the data.
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Wait for the ACK signal
    bResult = kWaitForACKAndPushOtherScanCode();
    
    if (bResult == false)
    {
        // Restore the previous state of the interrupt flag
        g_pclIH->kSetInterruptFlag(bPreviousInterrupt);
        return false;
    }
    
    // Send new LED state value to a keyboard until the command is done
    a_pclPort->kOutPortByte(0x60, 
                  (bCapsLockOn << 2) | (bNumLockOn << 1) | bScrollLockOn);
    
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the input buffer (port 0x60) is empty
        // a keyboard takes LED data
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Wait for the ACK signal
    bResult = kWaitForACKAndPushOtherScanCode();
    
    // Restore the previous state of the interrupt flag
    g_pclIH->kSetInterruptFlag(bPreviousInterrupt);
    
    return bResult;
}

/// Activate A20 gate.
void kKeyboard::kEnableA20Gate(void)
{
    BYTE bOutputPortData;
    
    // Send a command which read the output port value 
    // of the keyboard controller to the control register (port 0x64).
    a_pclPort->kOutPortByte(0x64, 0xD0);
    
    // Wait data of the output port and read.
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the output buffer (port 0x60) is full,
        // kOdin can read data.
        if (kIsOutputBufferFull() == true)
        {
            break;
        }
    }
    
    // Read the output port value of the keyboard controller
    // from the output port (0x60).
    bOutputPortData = a_pclPort->kInPortByte(0x60);
    
    // Set A20 gate activating bit
    bOutputPortData |= 0x01;
    
    // Send a command which write a data to the output port
    // and the output port data, if the input buffer (port 0x60) is empty.
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the input buffer (port 0x60) is empty, 
        // it is available to send.
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Send the output port setting command (0xD1)
    // to the command register (0x64).
    a_pclPort->kOutPortByte(0x64, 0xD1);
    
    // Send setting value for A20 gate to the input buffer (port 0x60).
    a_pclPort->kOutPortByte(0x60, bOutputPortData);
    
    return;
}

/// Reset a processor
void kKeyboard::kReboot(void)
{
    // If the input buffer (port 0x60) is empty,
    // send a command which write data to the output port
    // and the output port data.
    for (int i = 0; i < 0xFFFF; i++)
    {
        // If the input buffer (port 0x60) is empty, 
        // it is available to send.
        if (kIsInputBufferFull() == false)
        {
            break;
        }
    }
    
    // Send the output port setting command (0xD1)
    // to the command register (0x64).
    a_pclPort->kOutPortByte(0x64, 0xD1);
    
    // reset a processor by sending 0 to the inputer buffer (0x60).
    a_pclPort->kOutPortByte(0x60, 0x00);
    
    while (1)
    {
        ;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Functions to translate Scan Code to ASCII 
///////////////////////////////////////////////////////////////////////////////
/// Check the Scan Code is alphabet.
bool kKeyboard::kIsAlphabetScanCode(BYTE bScanCode)
{
    // Check the Scan Code is in the range of the alphabet.
    if (('a' <= stKeyMappingTable[bScanCode].bNormalCode) &&
        (stKeyMappingTable[bScanCode].bNormalCode <= 'z'))
    {
        return true;
    }
    
    return false;
}

/// Check the Scan Code is number or symbol.
bool kKeyboard::kIsNumberOrSymbolScanCode(BYTE bScanCode)
{
    // If it is in number pad or extended key range(Scan Code 2 ~ 53)
    // and it is not a character, it is a number or symbol.
    if ((2 <= bScanCode) && (bScanCode <= 53) &&
        (kIsAlphabetScanCode(bScanCode) == false))
    {
        return true;
    }

    return false;
}

/// Check the Scan Code is in number pad.
bool kKeyboard::kIsNumberPadScanCode(BYTE bScanCode)
{
    // The range of number pad is 71 ~ 83.
    if ((71 <= bScanCode) && (bScanCode <= 83))
    {
        return true;
    }
    
    return false;
}

/// Check whether or not a combination key should be used.
bool kKeyboard::kIsUseCombinedCode(BYTE bScanCode)
{
    BYTE bDownScanCode;
    bool bUseCombinedKey = false;
    
    bDownScanCode = bScanCode & 0x7F;
    
    // If the key is an alphabet,
    // it is affected by Shift or CAPS lock.
    if (kIsAlphabetScanCode(bDownScanCode) == true)
    {
        // If Shift or CAPS lock is pushed before,
        // return a combination key.
        if (bShiftDown ^ bCapsLockOn)
        {
            bUseCombinedKey = true;
        }
        else
        {
            bUseCombinedKey = false;
        }
    }
    // If the key is a number or symbol
    // it is affected by shift.
    else if (kIsNumberOrSymbolScanCode(bDownScanCode) == true)
    {
        // If shift key is pused before
        // return a combination key.
        if (bShiftDown == true)
        {
            bUseCombinedKey = true;
        }
        else
        {
            bUseCombinedKey = false;
        }
    }
    // If the key is from a number pad,
    // it is affected by Num Lock.
    // Except for 0xE0, entended key and number pad are overlapped,
    // return a combination code when extended key is nor received.
    else if ((kIsNumberPadScanCode(bDownScanCode) == true) &&
            (bExtendedCodeIn == false))
    {
        // If Num lock is pused before,
        // return a combination key.
        if (bNumLockOn == true)
        {
            bUseCombinedKey = true;
        }
        else
        {
            bUseCombinedKey = false;
        }
    }
    
    return bUseCombinedKey;
}

/// Update a combination key state and Sync LED state.
void kKeyboard::kUpdateCombinationKeyStatusAndLED(BYTE bScanCode)
{
    BYTE bDownScanCode;
    bool bDown;
    bool bLEDStatusChnaged = false;

    // Handle push and release.
    // If the highest bit (Bit 7) is 1, it is release.
    // If not, it is push.
    if (bScanCode & 0x80)
    {
        bDown = false;
        bDownScanCode = bScanCode & 0x7F;
    }
    else
    {
        bDown = true;
        bDownScanCode = bScanCode;
    }
    
    // Search a combination key.
    // If it is Scan Code of shift (42 or 54),
    // update the state of the shift key.
    if ((bDownScanCode == 42) || (bDownScanCode == 54))
    {
        bShiftDown = bDown;
    }
    // If it is Scan Code of CAPS lock (58)
    // update the state of CAPS Lock and change LED state.
    else if ((bDownScanCode == 58) && (bDown == true))
    {
        bCapsLockOn ^= true;
        bLEDStatusChnaged = true;
    }
    // If it is Scan Code of Num lock (69)
    // update the state of Num Lock and change LED state.
    else if ((bDownScanCode == 69) && (bDown == true))
    {
        bNumLockOn ^= true;
        bLEDStatusChnaged = true;
    }
    // If it is Scan Code of Scroll lock (70)
    // update the state of Scroll Lock and change LED state.
    else if ((bDownScanCode == 70) && (bDown == true))
    {
        bScrollLockOn ^= true;
        bLEDStatusChnaged = true;
    }
    
    // If the state of LED is changed,
    // send LED chang command to a keyboard.
    if (bLEDStatusChnaged == true)
    {
        kChangeKeyboardLED(bCapsLockOn, bNumLockOn, bScrollLockOn);
    }
    
    return;
}

/// Translate ScFALSEan Code to ASCII.
bool kKeyboard::kConvertScanCodeToASCIICode(BYTE bScanCode, 
                                            char* pbASCIICode, 
                                            BYTE* pbFlags)
{
    bool bUseCombineKey;
    
    // If Pause is pused before, 
    // ignore rest Scan Code of Pause.
    if (iSkipCountForPause > 0)
    {
        iSkipCountForPause--;
        return false;
    }
    
    // Special handling for Pause.
    if (bScanCode == 0xE1)
    {
        *pbASCIICode = KEY_PAUSE;
        *pbFlags = KEY_FLAGS_DOWN;
        iSkipCountForPause = KEY_SKIPCOUNTFORPAUSE;
        return true;
    }
    // If exnteded key is entered, actual key value will be entered next.
    // So set flag and return
    else if (bScanCode == 0xE0)
    {
        bExtendedCodeIn = true;
        return false;
    }
    
    // Return a combination key?
    bUseCombineKey = kIsUseCombinedCode(bScanCode);
    
    // Set key value
    if (bUseCombineKey == true)
    {
        *pbASCIICode = stKeyMappingTable[bScanCode & 0x7F].bCombinedCode;
    }
    else
    {
        *pbASCIICode = stKeyMappingTable[bScanCode & 0x7F].bNormalCode;
    }
    
    // Set whether or not it is extended key
    if (bExtendedCodeIn == true)
    {
        *pbFlags = KEY_FLAGS_EXTENDEDKEY;
        bExtendedCodeIn = false;
    }
    else
    {
        *pbFlags = 0;
    }
    
    // Check push or release
    if ((bScanCode & 0x80) == 0)
    {
        *pbFlags |= KEY_FLAGS_DOWN;
    }
    
    // update push or release of a combination key
    kUpdateCombinationKeyStatusAndLED(bScanCode);
    
    // Skip single shift key
    if (bShiftDown == true &&
        ( ( bScanCode & 0x7F ) == 42 || ( bScanCode & 0x7F ) == 54) )
        return false;
    // Skip single Caps Lock key
    else if ( ( bScanCode & 0x7F ) == 58 )
        return false;
    // Skip single Number Lock key 
    else if ( ( bScanCode & 0x7F ) == 69 )
        return false;
    // Skip Scroll Lock key 
    else if ( ( bScanCode & 0x7F ) == 70 )
        return false;
    
    return true;
}

/// Translate Scan Code to ASCII Code and push it
bool kKeyboard::kConvertScanCodeAndPushQueue(BYTE bScanCode)
{
    KEYDATA stData;
    bool bResult = false;
    bool bPreviousInterrupt;
    
    // Insert Scan Code to the key data structure
    stData.bScanCode = bScanCode;
    
    // Translate Scan Code to ASCII Code,
    // and insert it to the key data structure
    if (kConvertScanCodeToASCIICode(bScanCode, &(stData.bASCIICode),
        &(stData.bFlags)) == true)
    {
        // Disable interrupt
        bPreviousInterrupt = g_pclIH->kSetInterruptFlag(false);
        
        // Push the key data
        bResult = clKeyQueue.kPushQueue(&stData);
        
        // Restore previous interrupt flag
        g_pclIH->kSetInterruptFlag(bPreviousInterrupt);
    }
    
    return bResult;
}

/// Remove key data from the key queue
bool kKeyboard::kPopKeyFromKeyQueue(KEYDATA* pstData)
{
    bool bResult;
    bool bPreviousInterrupt;
    
    // If the key queue is empty, it is not readable
    if (clKeyQueue.kIsQueueEmpty() == true)
    {
        return false;
    }
    
    // Disable interrupt
    bPreviousInterrupt = g_pclIH->kSetInterruptFlag(false);
    
    // Pop data
    bResult = clKeyQueue.kPopQueue(pstData);
    
    // Restore previous interrupt flag
    g_pclIH->kSetInterruptFlag(bPreviousInterrupt);
    
    return bResult;
}

