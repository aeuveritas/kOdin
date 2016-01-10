#include "commandWait.hpp"
#include "commandParameter.hpp"
#include "console.hpp"
#include "stringHelper.hpp"
#include "interruptHandler.hpp"
#include "PIT.hpp"

extern kConsole* g_pclConsole;
extern kStringHelper* g_pclStringHelper;
extern kIH* g_pclIH;
extern kPIT* g_pclPIT;

/// Constructor of kCommandWait
kCommandWait::kCommandWait(void)
{
    // Command name
    pcCommandName = "wait";
    
    // Help message
    pcHelp = "Wait ms using PIT";
    
    // Example message
    pcExample = "ex) wait 100(ms)";
}

/// Deconstructor of kCommandWait
kCommandWait::~kCommandWait(void)
{

}

/// Initialize kCommandWait
void kCommandWait::kInitializeCommandWait(void)
{

}

/// Execute to wait
void kCommandWait::kTask_do(const char* pcParameter)
{
    char caParameter[100];
    int iLength;
    kCommandParameter clCommandParameter;
    long lMillisecond;
    
    // Initialize parameter
    clCommandParameter.kInitializeCommandParameter(pcParameter);
    if (clCommandParameter.kGetNextParameter(caParameter) == 0)
    {
        kTask_example();
        
        return;
    }
    
    lMillisecond = g_pclStringHelper->kAToI(pcParameter, DECIMAL);    
    g_pclConsole->kPrintf("%d ms Sleep Start...\n", lMillisecond);
    
    // Disable interrupt, and measure time from PIT directly
    g_pclIH->kDisableInterrupt();
    for (int iCount = 0; iCount < lMillisecond / 30; iCount++)
    {
        g_pclPIT->kWaitUsingDirectPIT(MSTOCOUNT(30));
    }
    g_pclPIT->kWaitUsingDirectPIT(MSTOCOUNT(lMillisecond%30));
    g_pclIH->kEnableInterrupt();
    g_pclConsole->kPrintf("%d ms sleep complete\n", lMillisecond);
    
    // Restore timer
    g_pclPIT->kSetPIT(MSTOCOUNT(1), true);
    
    return;
}