#include "utils.hpp"

// Print message
bool kUtils::kPrintString(int iX, int iY, const char* pcString)
{
    CHARACTER* pstScreen = (CHARACTER*) 0xB8000;

    pstScreen += (iY * 80) + iX;

    for (int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharactor = pcString[i];
    }

    return true;
}

// Simple shell
void kUtils::kShell(kKeyboardManager& clKM, DWORD& dwLine)
{
    char cTemp[2] = {0, };
    BYTE bFlags;
    BYTE bTemp;
    int xIndex = 0;
    
    while (1)
    {
        // If the output buffer (port 0x60) is full, 
        // Scan Code is available
        if (clKM.kIsOutputBufferFull() == true)
        {
            // Read Scan Code from the output buffer (0x60)
            bTemp = clKM.kGetKeyboardScanCode();
            
            // Translate Scan Code to ASCII
            // and Check push and release
            if (clKM.kConvertScanCodeToASCIICode(bTemp, &(cTemp[0]), &bFlags) == true)
            {
                // If key is pushed, print the key
                if (bFlags & KEY_FLAGS_DOWN)
                {
                    kPrintString(xIndex++, dwLine, cTemp);
                }
            }
        }
    }
}
