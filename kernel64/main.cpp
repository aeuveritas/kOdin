#include "types.hpp"
#include "utils.hpp"
#include "keyboardManager.hpp"

void main(void)
{
    DWORD dwLine;
    kUtils clUtils;
    kKeyboardManager clKM;
    
    dwLine = 10;

    clUtils.kPrintString(2, dwLine++,
                         "PASS");
    clUtils.kPrintString(0, dwLine++,
                         "[ PASS ]  IA-32e C++ Language Kernel Start");
    
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Keyboard Activate");
    
    // Activate a keyboard
    if (clKM.kActivateKeyboard() == true)
    {
        clUtils.kPrintString(2, dwLine++,
                         "PASS");
        clKM.kChangeKeyboardLED(false, false, false);
    }
    else
    {
        clUtils.kPrintString(2, dwLine++,
                         "FAIL");
        while (1);
    }
    
    clUtils.kShell(clKM, dwLine);
}