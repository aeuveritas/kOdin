#include "types.hpp"
#include "keyboard.hpp"
#include "descriptionTable.hpp"
#include "PIC.hpp"
#include "interruptHandler.hpp"
#include "memory.hpp"
#include "stringHelper.hpp"
#include "console.hpp"
#include "consoleShell.hpp"

#include "debug.hpp"

kConsole* g_pclConsole;
kIH* g_pclIH;
kMemory* g_pclMemory;
kStringHelper* g_pclStringHelper;

void main(void)
{
    kConsole clConsole;
    kPort clPort;
    kDT clDT;
    kKeyboard clKeyboard;
    kPIC clPIC;
    kIH clIH;
    kMemory clMemory;
    kConsoleShell clConsoleShell;
    kStringHelper clStringHelper;
    
    kDebug clDebug;
    
    int iRamSize;
    
    //clDebug.kLock();
    
    // Initialize kMemory
    clMemory.kInitializeMemory();
    
    // Set global pointer of kMemory
    g_pclMemory = & clMemory;
    
    
    // Initialize kStringHelper
    clStringHelper.kInitializeStringHelper();
    

    // Set global pointer of kStringHelper
    g_pclStringHelper = &clStringHelper;
    
    // Initialize kConsole
    clConsole.kInitializeConsole(&clPort, &clKeyboard, 0, 11);
    
    // Set global pointer of kConsole
    g_pclConsole = &clConsole;
    
    // Jump to kernel64 
    clConsole.kPrintStringXY(2, 10, "PASS");
    
    // Start C++ kernel
    clConsole.kPrintTry("[      ]  Start IA-32e C++ Language Kernel");
    clConsole.kPrintResult("PASS");
    
    // Initialize DTs
    clDT.kInitializeDT();

    // Check total RAM size
    clConsole.kPrintTry("[      ]  Check Total RAM Size");
    clMemory.kCheckTotalRAMSize();
    iRamSize = clMemory.kGetTotalRAMSize();
    clConsole.kPrintResultIntValue(iRamSize);
    clConsole.kPrintResult("PASS");

    // Activate a keyboard
    clConsole.kPrintTry("[      ]  Activate Keyboard");
    if (clKeyboard.kInitializeKeyboard(&clPort))
    {
        clConsole.kPrintResult("PASS");

        clKeyboard.kChangeKeyboardLED(false, false, false);
    }
    else
    {
        clConsole.kPrintResult("FAIL");
        while (1);
    }
    
    // Initialize PIC and Activate interrupt
    clConsole.kPrintTry("[      ]  Initialize PIC and Interrupt");
    clPIC.kInitializePIC(&clPort);
    clPIC.kMaskPICInterrupt(0);
    clConsole.kPrintResult("PASS");
   
    // Initialize interrupt handler
    clConsole.kPrintTry("[      ]  Initialize Interrupt Handler");
    clIH.kInitializeIH(&clPIC, &clKeyboard);
    g_pclIH = &clIH;
    clConsole.kPrintResult("PASS");
    
    // Enable interrupt
    clConsole.kPrintTry("[      ]  Enable Interrupt");
    clIH.kEnableInterrupt();
    clConsole.kPrintResult("PASS");

    // Initialize shell
    clConsoleShell.kInitializeConsoleShell();
    
    // Run shell
    clConsoleShell.kActivateConsoleShell();
}