#include "commandRDTSC.hpp"
#include "console.hpp"
#include "TSC.hpp"

extern kConsole* g_pclConsole;
extern kTSC* g_pclTSC;

/// Constructor of kCommandRDTSC
kCommandRDTSC::kCommandRDTSC(void)
{
    // Command name
    pcCommandName = "rdtsc";
    
    // Help message
    pcHelp = "Read time stamp counter";
    
    // Example message
    pcExample = "ex) rdtsc";
}

/// Deconstructor of kCommandRDTSC
kCommandRDTSC::~kCommandRDTSC(void)
{

}

/// Initialize kCommandRDTSC
void kCommandRDTSC::kInitializeCommandRDTSC(void)
{

}

/// Execute to wait
void kCommandRDTSC::kTask_do(const char* pcParameter)
{
    QWORD qwTSC;
    
    qwTSC = g_pclTSC->kReadTSC();
    g_pclConsole->kPrintf("Time Stamp Counter: %q\n", qwTSC);
    
    return;
}