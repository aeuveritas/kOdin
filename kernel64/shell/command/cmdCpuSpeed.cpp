#include "cmdCpuSpeed.hpp"
#include "console.hpp"
#include "interruptHandler.hpp"
#include "TSC.hpp"
#include "PIT.hpp"

extern kConsole* g_pclConsole;
extern kIH* g_pclIH;
extern kTSC* g_pclTSC;
extern kPIT* g_pclPIT;

/// Constructor of kCommandCpuSpeed
kCommandCpuSpeed::kCommandCpuSpeed(void)
{
    // Command name
    pcCommandName = "cpuspeed";
    
    // Help message
    pcHelp = "Measure processor speed";
    
    // Example message
    pcExample = "ex) cpuspeed";
}

/// Deconstructor of kCommandCpuSpeed
kCommandCpuSpeed::~kCommandCpuSpeed(void)
{

}

/// Initialize kCommandCpuSpeed
void kCommandCpuSpeed::kInitializeCommandCpuSpeed(void)
{

}

/// Execute to wait
void kCommandCpuSpeed::kTask_do(const char* pcParameter)
{
    QWORD qwLastTSC;
    QWORD qwTotalTSC = 0;
    
    if (pcParameter == nullptr)
    {
        return;
    }
    
    g_pclConsole->kPrintf("Now Measuring.");
    
    // Check time stamp counter variation during 10 seconds
    g_pclIH->kDisableInterrupt();
    for (int iCount = 0; iCount < 200; iCount++)
    {
        qwLastTSC = g_pclTSC->kReadTSC();
        g_pclPIT->kWaitUsingDirectPIT(MSTOCOUNT(50));
        qwTotalTSC += g_pclTSC->kReadTSC() - qwLastTSC;
        
        g_pclConsole->kPrintf(".");
    }
    
    // Restore timer
    g_pclPIT->kSetPIT(MSTOCOUNT(1), true);
    g_pclIH->kEnableInterrupt();
    
    g_pclConsole->kPrintf("\nCPU Speed = %d MHz\n", 
                          qwTotalTSC / 10 / 1000 / 1000);
    
    return;
}