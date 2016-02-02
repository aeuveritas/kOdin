#include "console.hpp"
#include "memoryHelper.hpp"
#include "stringHelper.hpp"
#include <stdarg.h>

extern kMemoryHelper* g_pclMemoryHelper;
extern kStringHelper* g_pclStringHelper;

/// Constructor of console
kConsole::kConsole(void)
{
    iCursorLocationStamp = 0;
}

/// Destructor of console
kConsole::~kConsole(void)
{
    iCursorLocationStamp = 0;
}

/// Initialize kConsole
void kConsole::kInitializeConsole(kPort* pcPort, kKeyboard* pcKeyboard, int iCursorX, int iCursorY)
{
    a_pclPort = pcPort;
    a_pclKeyboard = pcKeyboard;
    
    iCursorLocationStamp = 0;
    iPairY = iCursorY;
    
    kSetCursor(iCursorX, iCursorY);
    
    return;
}

/**
 * Set the cursor's location
 * Change iCursorLocationStamp also
 **/
void kConsole::kSetCursor(int iX, int iY)
{
    int iLinearValue;
    
    // Calculate the location of the cursor
    iLinearValue = iY * CONSOLE_WIDTH + iX;
    
    // Select CLHR (Cursor Location High Register)
    // by sending 0x0E
    // to CRTC CAR (Control Address Register), 0x3D4
    a_pclPort->kOutPortByte(VGA_PORT_INDEX, VGA_INDEX_UPPERCURSOR);
    
    // Set upper byte
    // by sending upper byte of iLinearValue
    // to CRTC CDR(Contorl Data Register), 0x3D5
    a_pclPort->kOutPortByte(VGA_PORT_DATA, iLinearValue >> 8);
    
    // Select CLLR (Cursor Location Low Register)
    // by sending 0x0F
    // to CRTC CAR (Control Address Register), 0x3D4
    a_pclPort->kOutPortByte(VGA_PORT_INDEX, VGA_INDEX_LOWERCURSOR);
    
    // Set lower byte
    // by sending lower byte of iLinearValue
    // to CRTC CDR(Contorl Data Register), 0x3D5
    a_pclPort->kOutPortByte(VGA_PORT_DATA, iLinearValue & 0xFF);
    
    // Update the cursor location of this class
    iCursorLocationStamp = iLinearValue;
    
    return;
}

/// Return the current location of the cursor
void kConsole::kGetCursor(int* piX, int* piY)
{
    // The reminder of division by console width is the location of X
    // The quotient is the location of Y
    *piX = iCursorLocationStamp % CONSOLE_WIDTH;
    *piY = iCursorLocationStamp / CONSOLE_WIDTH;
    
    return;
}

/// The "kOdin" version of printf()
void kConsole::kPrintf(const char* pcFormatString, ...)
{
    va_list ap;
    char cBuffer[1024];
    int iNextCursorLocation;
    
    // Call kVSPrintf()
    va_start(ap, pcFormatString);
    g_pclStringHelper->kVSPrintf(cBuffer, pcFormatString, ap);
    va_end(ap);
    
    // Print the output string
    iNextCursorLocation = kConsolePrintString(cBuffer);
    
    // Update the location of the cursor
    kSetCursor(iNextCursorLocation % CONSOLE_WIDTH,
               iNextCursorLocation / CONSOLE_WIDTH);
    
    return;
}

/// Handle '\n' and '\t'
int kConsole::kConsolePrintString(const char* pcBuffer)
{
    CHARACTER* pstScreen = (CHARACTER*) CONSOLE_VIDEOMEMORYADDRESS;
    int iLength;
    int iCursorLocation;

    // Set the target location of output string
    iCursorLocation = iCursorLocationStamp;
    
    // Print string as mush as the length of the string
    iLength = g_pclStringHelper->kStrLen(pcBuffer);
    for (int iBufferIndex = 0; iBufferIndex < iLength; iBufferIndex++)
    {
        // Go to the next line
        if (pcBuffer[iBufferIndex] == '\n')
        {
            // Move to the next the multiple of 80
            // Add current cursor and the left in the line
            iCursorLocation += 
                (CONSOLE_WIDTH - (iCursorLocation % CONSOLE_WIDTH));
        }
        // Go to the next multiple of tab size
        else if (pcBuffer[iBufferIndex] == '\t')
        {
            iCursorLocation += (TAB_SIZE - (iCursorLocation % TAB_SIZE));
        }
        // Normal character
        else
        {
            // Print character with its properties and increase the index
            pstScreen[iCursorLocation].bCharactor = pcBuffer[iBufferIndex];
            pstScreen[iCursorLocation].bAttribute = CONSOLE_DEFAULTTEXTCOLOR;
            iCursorLocation++;
        }
        
        // If the location exceeds 80 * 25, scroll screen
        if (iCursorLocation >= (CONSOLE_HEIGHT * CONSOLE_WIDTH))
        {
            // Copy all lines to their 1 line upper, except for the first line
            void* pvCopyDest = (void*) (CONSOLE_VIDEOMEMORYADDRESS);
            void* pvCopySrc = (void*) (CONSOLE_VIDEOMEMORYADDRESS + 
                                      CONSOLE_WIDTH * sizeof(CHARACTER));
            int iCopySize = ((CONSOLE_HEIGHT - 1) * 
                             (CONSOLE_WIDTH * sizeof(CHARACTER)));
            
            g_pclMemoryHelper->kMemCpy(pvCopyDest, pvCopySrc, iCopySize);
            
            // Make the last line as empty
            for (int iEmpty = (CONSOLE_HEIGHT - 1) * (CONSOLE_WIDTH);
                 iEmpty < (CONSOLE_HEIGHT * CONSOLE_WIDTH); iEmpty++)
            {
                // Print empty
                pstScreen[iEmpty].bCharactor = ' ';
                pstScreen[iEmpty].bAttribute = CONSOLE_DEFAULTTEXTCOLOR;
            }
            
            // Set cursor at the last line
            iCursorLocation = (CONSOLE_HEIGHT - 1) * CONSOLE_WIDTH;
        }
    }
    
    return iCursorLocation;
}

/// Clear screen
void kConsole::kClearScreen(void)
{
    CHARACTER* pstScreen = (CHARACTER*) CONSOLE_VIDEOMEMORYADDRESS;
    
    // Fill all screen with empty
    for (int iIndex = 0; iIndex < CONSOLE_WIDTH * CONSOLE_HEIGHT; iIndex++)
    {
        pstScreen[iIndex].bCharactor = ' ';
        pstScreen[iIndex].bAttribute = CONSOLE_DEFAULTTEXTCOLOR;
    }
    
    // Move the cursor to the first line
    kSetCursor(0, 0);
}

/// Wait for keyboard input and return what an user types
BYTE kConsole::kGetCh(void)
{
    KEYDATA stData;
    
    while (1)
    {
        // Wait until key input is stored in key queue
        while (a_pclKeyboard->kPopKeyFromKeyQueue(&stData) == false)
        {
            ;
        }
        
        // If key is pushepcBuuferd, translate Scan code to ASCII code
        if (stData.bFlags & KEY_FLAGS_DOWN)
        {
            return stData.bASCIICode;
        }
    }
}

/// Print string at (X,Y)
void kConsole::kPrintStringXY(int iX, int iY, const char* pcString)
{
    CHARACTER* pstScreen = (CHARACTER*) CONSOLE_VIDEOMEMORYADDRESS;
    
    // Calculate the target location of the string
    pstScreen += (iY * CONSOLE_WIDTH) + iX;
    
    // Print the string
    for (int iIndex = 0; pcString[iIndex] != '\0'; iIndex++)
    {
        pstScreen[iIndex].bCharactor = pcString[iIndex];
        pstScreen[iIndex].bAttribute = CONSOLE_DEFAULTTEXTCOLOR;
    }
}

/// Reboot kOdin
void kConsole::kReboot(void)
{
    a_pclKeyboard->kReboot();
}

/// Print set message: Check
void kConsole::kPrintTry(const char* pcBuffer)
{
    int iCursorX;
    int iCursorY;
    
    kGetCursor(&iCursorX, &iCursorY);
    iPairY = iCursorY;
    
    kPrintStringXY(iCursorX, iCursorY, pcBuffer);
    
    iCursorX = g_pclStringHelper->kStrLen(pcBuffer);
    
    kSetCursor(iCursorX, iCursorY);
    
    return;
}

/// Print set message: Middle integer
void kConsole::kPrintResultIntValue(const int iValue)
{
    kPrintf(" - %dMB", iValue);
    
    return;
}

/// Print set message: Middle string
void kConsole::kPrintResultStrValue(const char* pcBuffer)
{
    kPrintf(" - %s", pcBuffer);
    
    return;
}

/// Print set message: Result
void kConsole::kPrintResult(const char* pcBuffer)
{
    kPrintStringXY(2, iPairY++, pcBuffer);
    kSetCursor(0, iPairY);
    return;
}

