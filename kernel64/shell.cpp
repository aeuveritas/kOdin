#include "shell.hpp"

extern kUtils* g_pclUtils;

/// Constructor of kShell
kShell::kShell(void)
{
    a_pclKeyboard = nullptr;
}

/// Deconstructor of kShell
kShell::~kShell(void)
{
    a_pclKeyboard = nullptr;
}

/// Initialize Shell
void kShell::kInitializeShell(kKeyboard* _kKeyboard)
{
    a_pclKeyboard = _kKeyboard;
}

/// Simple shell
void kShell::kPrompt()
{
    char cTemp[2] = {0, };
    BYTE bFlags;
    BYTE bTemp;
    
    while (1)
    {
        // If the output buffer (port 0x60) is full, 
        // Scan Code is available
        if (a_pclKeyboard->kIsOutputBufferFull() == true)
        {
            // Read Scan Code from the output buffer (0x60)
            bTemp = a_pclKeyboard->kGetKeyboardScanCode();
            
            // Translate Scan Code to ASCII
            // and Check push and release
            if (a_pclKeyboard->kConvertScanCodeToASCIICode(bTemp, 
                                                       &(cTemp[0]), 
                                                       &bFlags) == true)
            {
                // If key is pushed, print the key
                if (bFlags & KEY_FLAGS_DOWN)
                {
                    g_pclUtils->kPrintChar(cTemp);
                    
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
