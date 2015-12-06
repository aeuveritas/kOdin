#include "types.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "DT.hpp"
#include "shell.hpp"

kUtils clUtils;

void main(void)
{
    DWORD dwLine;
    kKeyboard clKeyboard;
    kDT clDT;
    kShell clShell;
    
    dwLine = 10;

    clUtils.kPrintString(2, dwLine++,
                           "PASS");
    clUtils.kPrintString(0, dwLine++,
                         "[ PASS ]  IA-32e C++ Language Kernel Start");
    
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Initialize GDT for IA-32e Mode");
    clDT.kInitializeGDT();
    clDT.kLoadGDTR(GDTR_STARTADDRESS);
    clUtils.kPrintString(2, dwLine++,
                           "PASS");
    
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Initialize TSS");
    clDT.kInitializeTSS();
    clDT.kLoadTR(GDT_TSS);
    clUtils.kPrintString(2, dwLine++,
                           "PASS");
    
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Initialize IDT");
    clDT.kInitializeIDT();
    clDT.kLoadIDTR(IDTR_STARTADDRESS);
    clUtils.kPrintString(2, dwLine++,
                           "PASS");
    
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
    
    clShell.kPrompt(clKeyboard, dwLine);
}