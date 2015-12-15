#include "IH.hpp"

extern kUtils* g_pclUtils;
extern kIH* g_pclIH;

/// Constructor of IH
kIH::kIH(void)
{
    a_pclPIC = nullptr;
    
    iCommonInterruptCount = 0;
    iKeyboardInterruptCount = 0;
}

/// Deconstructor of IH
kIH::~kIH(void)
{
    a_pclPIC = nullptr;
    
    iCommonInterruptCount = 0;
    iKeyboardInterruptCount = 0;    
}

/// Initialize IH
void kIH::kInitializeIH(kPIC* _kPIC)
{
    a_pclPIC = _kPIC;
    
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
    
    // When interrupt occurs, print message
    // It will be shown on the right upper screen as 2 digits
    cBuffer[5] = '0' + iVectorNumber / 10;
    cBuffer[6] = '0' + iVectorNumber % 10;
    
    // Print the number of interrupt happened
    cBuffer[8] = '0' + iKeyboardInterruptCount;
    g_pclUtils->kPrintKeyboardInterrupt(cBuffer);
    
    iKeyboardInterruptCount = (iKeyboardInterruptCount + 1) % 10;
    
    // Send EOI
    a_pclPIC->kSendEOIToPIC(iVectorNumber - PIC_IRQSTARTVECTOR);
    
    return;
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
