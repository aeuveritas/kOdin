#include "commandTask.hpp"
#include "console.hpp"

extern kConsole* g_pclConsole;

/// Solve virtual problem
extern "C" 
{
    void __cxa_pure_virtual(void)
    {
        // Do nothing or print an error message.   
    }
};

/// Get command name
const char* kCommandTask::kTask_getName(void)
{
    return pcCommandName;
}

/// Print help message
void kCommandTask::kTask_help(void)
{
    g_pclConsole->kPrintf(pcHelp);
    
    return;    
}

/// Print example
void kCommandTask::kTask_example(void)
{
    g_pclConsole->kPrintf(pcExample);
    
    return;
}
