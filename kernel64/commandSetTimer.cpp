#include "commandSetTimer.hpp"
#include "commandParameter.hpp"
#include "console.hpp"
#include "stringHelper.hpp"
#include "PIT.hpp"

extern kConsole* g_pclConsole;
extern kStringHelper* g_pclStringHelper;
extern kPIT* g_pclPIT;

/// Constructor of kCommandSetTimer
kCommandSetTimer::kCommandSetTimer(void)
{
    // Command name
    pcCommandName = "settimer";
    
    // Help message
    pcHelp = "Set PIT controller conunter0";
    
    // Example message
    pcExample = "ex) settimer 10(ms) 1(period)";
}

/// Destructor of kCommandSetTimer
kCommandSetTimer::~kCommandSetTimer(void)
{

}

/// Initialize kCommandSetTimer
void kCommandSetTimer::kInitializeCommandSetTimer(void)
{

}

/// Execute to set timer
void kCommandSetTimer::kTask_do(const char* pcParameter)
{
    char caParameter[100];
    kCommandParameter clCommandParameter;
    long lValue;
    bool bPeriodic;
    
    // Initialize parameter
    clCommandParameter.kInitializeCommandParameter(pcParameter);
    
    // Extract milisecond
    if (clCommandParameter.kGetNextParameter(caParameter) == 0)
    {
        kTask_example();
        
        return;
    }
    lValue = g_pclStringHelper->kAToI(caParameter, DECIMAL);
    
    // Extract period
    if (clCommandParameter.kGetNextParameter(caParameter) == 0)
    {
        kTask_example();
        
        return;
    }
    bPeriodic = g_pclStringHelper->kAToI(caParameter, DECIMAL);
    
    g_pclPIT->kSetPIT(MSTOCOUNT(lValue), bPeriodic);
    g_pclConsole->kPrintf("Time= %d ms, Periodic= %d Change Complete\n",
                 lValue, bPeriodic);
    
    return;
}

