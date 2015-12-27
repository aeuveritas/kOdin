#include "DT.hpp"

extern kUtils* g_pclUtils;

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
    g_pclUtils->kPrintMessage("[      ]  Initialize GDT");
    clGDT.kInitializeGDT();
    clGDT.kLoadGDTR(GDTR_STARTADDRESS);
    g_pclUtils->kPrintResult("PASS");
    
    // Initialize TSS
    g_pclUtils->kPrintMessage("[      ]  Initialize TSS");
    clGDT.kInitializeTSS();
    clGDT.kLoadTR(GDT_TSS);
    g_pclUtils->kPrintResult("PASS");
    
    // Initialize IDT
    g_pclUtils->kPrintMessage("[      ]  Initialize IDT");
    clIDT.kInitializeIDT();
    clIDT.kLoadIDTR(IDTR_STARTADDRESS);
    g_pclUtils->kPrintResult("PASS");
}
