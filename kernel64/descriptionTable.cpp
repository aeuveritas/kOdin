#include "descriptionTable.hpp"

#include "console.hpp"

extern kConsole* g_pclConsole;

/// Constructor of kDT
kDT::kDT(void)
{
    
}

/// Deconstructor of kDT
kDT::~kDT(void)
{
    
}

/// Initialize descriptor Table
void kDT::kInitializeDT(void)
{
    // Initialize GDT
    g_pclConsole->kPrintSetCheck("[      ]  Initialize GDT for IA-32e Mode");
    clGDT.kInitializeGDT();
    clGDT.kLoadGDTR(GDTR_STARTADDRESS);
    g_pclConsole->kPrintSetResult("PASS");
    
    // Initialize TSS
    g_pclConsole->kPrintSetCheck("[      ]  Initialize TSS for IA-32e Mode");
    clGDT.kInitializeTSS();
    clGDT.kLoadTR(GDT_TSS);
    g_pclConsole->kPrintSetResult("PASS");
    
    // Initialize IDT
    g_pclConsole->kPrintSetCheck("[      ]  Initialize IDT for IA-32e Mode");
    clIDT.kInitializeIDT();
    clIDT.kLoadIDTR(IDTR_STARTADDRESS);
    g_pclConsole->kPrintSetResult("PASS");
}
