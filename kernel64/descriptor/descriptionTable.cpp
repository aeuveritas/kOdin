#include "descriptionTable.hpp"

/// Constructor of kDT
kDT::kDT(void)
{
    
}

/// Destructor of kDT
kDT::~kDT(void)
{
    
}

/// Initialize kDT
void kDT::kInitializeDT(void)
{
    // Initialize GDT
    clGDT.kInitializeGDT();
    clGDT.kLoadGDTR(GDTR_STARTADDRESS);
    //g_pclConsole->kPrintResult("PASS");
    
    // Initialize TSS
    setTSSAddress();
    clTSS.kInitializeTSS();
    clTSS.kLoadTR(GDT_TSS);
    //g_pclConsole->kPrintResult("PASS");
    
    // Initialize IDT
    clIDT.kInitializeIDT();
    clIDT.kLoadIDTR(IDTR_STARTADDRESS);
    //g_pclConsole->kPrintResult("PASS");
}

/// Set TSS address
void kDT::setTSSAddress(void)
{
    GDTENTRY8* pstGDTEntry8;
    
    pstGDTEntry8 = clGDT.kGetGDTEntry8();
    
    clTSS.kSetTSSAddress(pstGDTEntry8);
}


