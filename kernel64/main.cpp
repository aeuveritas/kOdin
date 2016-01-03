#include "types.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "descriptionTable.hpp"
#include "PIC.hpp"
#include "interruptHandler.hpp"
#include "shell.hpp"

kUtils* g_pclUtils;
kIH* g_pclIH;

void main(void)
{
    kUtils clUtils;
    kPort clPort;
    kDT clDT;
    kKeyboard clKeyboard;
    kPIC clPIC;
    kIH clIH;
    kShell clShell;
    
    // Initialize Utils
    clUtils.kInitializeUtils(10);
    //clUtils.kLock();
    
    // Set global pointer of kUtils
    g_pclUtils = &clUtils;
    
    // Jump to kernel64 
    clUtils.kPrintResult("PASS");
    
    // Start C++ kernel
    clUtils.kPrintMessage("[      ]  Start IA-32e C++ Language Kernel");
    clUtils.kPrintResult("PASS");
    
    // Initialize DTs
    clUtils.kPrintPairMessage("[      ]  Initialize DT for IA-32e Mode");
    clDT.kInitializeDT();
    clUtils.kPrintPairResult("PASS");

    // Activate a keyboard
    clUtils.kPrintMessage("[      ]  Activate Keyboard");
    if (clKeyboard.kInitializeKeyboard(&clPort))
    {
        clUtils.kPrintResult("PASS");

        clKeyboard.kChangeKeyboardLED(false, false, false);
    }
    else
    {
        clUtils.kPrintResult("FAIL");
        while (1);
    }
    
    // Initialize PIC and Activate interrupt
    clUtils.kPrintMessage("[      ]  Initialize PIC and Interrupt");
    clPIC.kInitializePIC(&clPort);
    clPIC.kMaskPICInterrupt(0);
    clUtils.kPrintResult("PASS");
   
    // Initialize interrupt handler
    clUtils.kPrintMessage("[      ]  Initialize Interrupt Handler");
    clIH.kInitializeIH(&clPIC, &clKeyboard);
    g_pclIH = &clIH;
    clUtils.kPrintResult("PASS");
    
    // Enable interrupt
    clUtils.kPrintMessage("[      ]  Enable Interrupt");
    clIH.kEnableInterrupt();
    clUtils.kPrintResult("PASS");
    
    // Initialize shell
    clShell.kInitializeShell(&clKeyboard);
    
    // Run shell
    clShell.kPrompt();
}