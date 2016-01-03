#include "interruptHandler.hpp"

#include "utils.hpp"

extern kUtils* g_pclUtils;
extern kIH* g_pclIH;

/// Constructor of IH
kIH::kIH(void)
{
    a_pclPIC = nullptr;
    a_pclKeyboard = nullptr;

    iCommonInterruptCount = 0;
    iKeyboardInterruptCount = 0;
}

/// Deconstructor of IH
kIH::~kIH(void)
{
    a_pclPIC = nullptr;
    a_pclKeyboard = nullptr;
    
    iCommonInterruptCount = 0;
    iKeyboardInterruptCount = 0;    
}

/// Initialize IH
void kIH::kInitializeIH(kPIC* _kPIC, kKeyboard* _kKeyboard)
{
    a_pclPIC = _kPIC;
    a_pclKeyboard = _kKeyboard;
    
    return;
}

/// Common exception handler
void kIH::kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode)
{
    char cNumber[3] = { 0, };
    
    // Print interrupt vector number as 2 digit number
    cNumber[0] = '0' + iVectorNumber / 10;
    cNumber[1] = '0' + iVectorNumber % 10;
    
    g_pclUtils->kPrintException(cNumber);
    
    while (1);

}

/// Common interrupt handler
void kIH::kCommonInterruptHandler(int iVectorNumber)
{
    char cBuffer[] = "[INT:  , ]";
    
    // When interrupt occurs, print message
    // It will be shown on the right upper screen as 2 digits
    cBuffer[5] = '0' + iVectorNumber / 10;
    cBuffer[6] = '0' + iVectorNumber % 10;
    
    // Print the number of interrupt happened
    cBuffer[8] = '0' + iCommonInterruptCount;
    g_pclUtils->kPrintInterrupt(cBuffer);
    
    iCommonInterruptCount = (iCommonInterruptCount + 1) % 10;
    
    // Send EOI
    a_pclPIC->kSendEOIToPIC(iVectorNumber - PIC_IRQSTARTVECTOR);
    
    return;
}

/// Keyboard interrupt handler
void kIH::kKeyboardHandler(int iVectorNumber)
{
    char cBuffer[] = "[INT:  , ]";
    BYTE bTemp;
    
    // When interrupt occurs, print message
    // It will be shown on the right upper screen as 2 digits
    cBuffer[5] = '0' + iVectorNumber / 10;
    cBuffer[6] = '0' + iVectorNumber % 10;
    
    // Print the number of interrupt happened
    cBuffer[8] = '0' + iKeyboardInterruptCount;
    g_pclUtils->kPrintKeyboardInterrupt(cBuffer);
    
    iKeyboardInterruptCount = (iKeyboardInterruptCount + 1) % 10;
    
    
    // Read data from the keyboard controller,
    // and translate it to ASCII Code
    // Also, push it
    if (a_pclKeyboard->kIsOutputBufferFull() == true)
    {
        bTemp = a_pclKeyboard->kGetKeyboardScanCode();
        a_pclKeyboard->kConvertScanCodeAndPushQueue(bTemp);
    }
    
    // Send EOI
    a_pclPIC->kSendEOIToPIC(iVectorNumber - PIC_IRQSTARTVECTOR);
    
    return;
}

/// Enable interrupt
void kIH::kEnableInterrupt(void)
{
    _kEnableInterrupt();
}

/// Disable interrupt
void kIH::kDisableInterrupt(void)
{
    _kDisableInterrupt();
}

/// Read RFLGAS and return it
QWORD kIH::kReadRFLAGS(void)
{
    return _kReadRFLAGS();
}

/**
 * Change interrupt flag of RFLAG register,
 * and return previous interrupt flag
 **/
bool kIH::kSetInterruptFlag(bool bEnableInterrupt)
{
    QWORD qwRFLAGS;
    
    // Read current RFLAGS, and enable/disable interrupt
    qwRFLAGS = kReadRFLAGS();
    if (bEnableInterrupt == true)
    {
        kEnableInterrupt();
    }
    else
    {
        kDisableInterrupt();
    }
    
    // Check IF bit (bit 9th) of qwRFLAGS,
    // and return the state of interrupt
    if (qwRFLAGS & 0x0200)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void _kCommonExceptionHandler(int iVectorNumber, QWORD qwErrorCode)
{
    g_pclIH->kCommonExceptionHandler(iVectorNumber, qwErrorCode);
    
    return;
}

void _kCommonInterruptHandler(int iVectorNumber)
{
    g_pclIH->kCommonInterruptHandler(iVectorNumber);

    return;
}

void _kKeyboardHandler(int iVectorNumber)
{
    g_pclIH->kKeyboardHandler(iVectorNumber);
    
    return;
}