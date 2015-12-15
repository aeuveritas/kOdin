#include "types.hpp"
#include "utils.hpp"
#include "keyboard.hpp"
#include "GDT.hpp"
#include "IDT.hpp"
#include "PIC.hpp"
#include "shell.hpp"
#include "IH.hpp"

kUtils* g_pclUtils;
kIH* g_pclIH;

void main(void)
{
    kUtils clUtils;
    kPort clPort;
    kKeyboard clKeyboard;
    kGDT clGDT;
    kIDT clIDT;
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
    
    // Initialize GDT
    clUtils.kPrintMessage("[      ]  Initialize GDT for IA-32e Mode");
    clGDT.kInitializeGDT();
    clGDT.kLoadGDTR(GDTR_STARTADDRESS);
    clUtils.kPrintResult("PASS");
    
    // Initialize TSS
    clUtils.kPrintMessage("[      ]  Initialize TSS");
    clGDT.kInitializeTSS();
    clGDT.kLoadTR(GDT_TSS);
    clUtils.kPrintResult("PASS");
    
    // Initialize IDT
    clUtils.kPrintMessage("[      ]  Initialize IDT");
    clIDT.kInitializeIDT();
    clIDT.kLoadIDTR(IDTR_STARTADDRESS);
    clUtils.kPrintResult("PASS");

    // Activate a keyboard
    clUtils.kPrintMessage("[      ]  Activate Keyboard");
    clKeyboard.kInitializeKeyboard(&clPort);

    if (clKeyboard.kActivateKeyboard())
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
    clIH.kInitializeIH(&clPIC);
    g_pclIH = &clIH;
    clUtils.kPrintResult("PASS");
    
    // Enable interrupt
    clUtils.kPrintMessage("[      ]  Enable Interrupt");
    clPIC.kEnableInterrupt();
    clUtils.kPrintResult("PASS");
    
    // Initialize shell
    clShell.kInitializeShell(&clKeyboard);
    
    // Run shell
    clShell.kPrompt();
}