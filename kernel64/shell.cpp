#include "shell.hpp"

#include "utils.hpp"

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
    BYTE bTemp;
    KEYDATA stData;
    
    while (1)
    {
        // If the output buffer (port 0x60) is full, 
        // Scan Code is available
        if (a_pclKeyboard->kPopKeyFromKeyQueue(&stData) == true)
        {
            // If key is pushed, print the key
            if (stData.bFlags & KEY_FLAGS_DOWN)
            {
                cTemp[0] = stData.bASCIICode;
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
