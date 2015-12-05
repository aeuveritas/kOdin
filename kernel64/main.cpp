#include "types.hpp"
#include "utils.hpp"
#include "keyboard.hpp"

void main(void)
{
    DWORD dwLine;
    kUtils clUtils;
    kKeyboard clKeyboard;
    
    dwLine = 10;

    clUtils.kPrintString(2, dwLine++,
                         "PASS");
    clUtils.kPrintString(0, dwLine++,
                         "[ PASS ]  IA-32e C++ Language Kernel Start");
    
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Keyboard Activate");
    
    // Activate a keyboard
    if (clKeyboard.kActivateKeyboard() == true)
    {
        clUtils.kPrintString(2, dwLine++,
                         "PASS");
        clKeyboard.kChangeKeyboardLED(false, false, false);
    }
    else
    {
        clUtils.kPrintString(2, dwLine++,
                         "FAIL");
        while (1);
    }
    
    clUtils.kShell(clKeyboard, dwLine);
}