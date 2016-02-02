#include "core.hpp"

kConsole* g_pclConsole;
kIH* g_pclIH;
kMemoryHelper* g_pclMemoryHelper;
kStringHelper* g_pclStringHelper;
kPIT* g_pclPIT;
kTSC* g_pclTSC;
kRTC* g_pclRTC;

kCore::kCore(void)
{

}

kCore::~kCore(void)
{

}

void kCore::kInitializeCoere(void)
{   
    int iRamSize;
    
    int iCursorX, iCursorY;
    
    clDebug.kInitializeDebug();
    //clDebug.kLock();
    
    // Initialize kMemory
    clMemoryHelper.kInitializeMemoryHelper();
    
    // Set global pointer of kMemory
    g_pclMemoryHelper = & clMemoryHelper;
    
    
    // Initialize kStringHelper
    clStringHelper.kInitializeStringHelper();
    

    // Set global pointer of kStringHelper
    g_pclStringHelper = &clStringHelper;
    
    // Set global pointer of kConsole
    g_pclConsole = &clConsole;
    
    // Jump from kernel32 
    clConsole.kPrintStringXY(2, 10, "PASS");
    
    // Initialize kConsole
    clConsole.kInitializeConsole(&clPort, &clKeyboard, 0, 11);
    
    // Start C++ kernel
    g_pclConsole->kGetCursor(&iCursorX, &iCursorY);
    clConsole.kPrintf("[      ]  Start IA-32e C++ Language Kernel"); 
    clConsole.kPrintResult("PASS");
    
    /// Memory
    // Initialize DTs
    clDT.kInitializeDT();

    // Check total RAM size
    clConsole.kPrintTry("[      ]  Check Total RAM Size");
    clMemoryHelper.kCheckTotalRAMSize();
    iRamSize = clMemoryHelper.kGetTotalRAMSize();
    clConsole.kPrintResultIntValue(iRamSize);
    clConsole.kPrintResult("PASS");
    
    /// Interrupt
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
    
    /// Device driver 
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
    
    // Initialize PIT
    clPIT.kInitializePIT(&clPort);
    
    // Initialize TSC
    clTSC.kInitializeTSC();
    g_pclTSC = &clTSC;
    
    // Initialize RTC
    clRTC.kIntializeRTC(&clPort);
    g_pclRTC = &clRTC;
    
    /// Shell
    // Initialize shell
    clConsoleShell.kInitializeConsoleShell();
    
    // Run shell
    clConsoleShell.kActivateConsoleShell();
}
