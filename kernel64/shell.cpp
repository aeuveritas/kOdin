#include "shell.hpp"

/// Simple shell
void kShell::kPrompt(kKeyboard& clKeyboard, DWORD& dwLine)
{
    char cTemp[2] = {0, };
    BYTE bFlags;
    BYTE bTemp;
    int xIndex = 0;
    
    while (1)
    {
        // If the output buffer (port 0x60) is full, 
        // Scan Code is available
        if (clKeyboard.kIsOutputBufferFull() == true)
        {
            // Read Scan Code from the output buffer (0x60)
            bTemp = clKeyboard.kGetKeyboardScanCode();
            
            // Translate Scan Code to ASCII
            // and Check push and release
            if (clKeyboard.kConvertScanCodeToASCIICode(bTemp, 
                                                       &(cTemp[0]), 
                                                       &bFlags) == true)
            {
                // If key is pushed, print the key
                if (bFlags & KEY_FLAGS_DOWN)
                {
                    clUtils.kPrintString(xIndex++, dwLine, cTemp);
                    
                    // If the input is 0,
                    // try to divide by 0
                    // in order to occur Divide Error (0th vector)
                    if (cTemp[0] == '0')
                    {
                        bTemp = bTemp / (cTemp[0] - '0');
                    }
                }
            }
        }
    }
}
