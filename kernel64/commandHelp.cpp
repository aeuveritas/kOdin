#include "commandHelp.hpp"
#include "console.hpp"

extern kConsole* g_pclConsole;

/// Constructor of kCommandHelp
kCommandHelp::kCommandHelp(void)
{
    // Command name
    pcCommandName = "help";
    
    // Help message
    pcHelp = "Show help of all commands";
}

/// Destructor of kCommandHelp
kCommandHelp::~kCommandHelp(void)
{

}

/// Initialize kInitializeCommandHelp
void kCommandHelp::kInitializeCommandHelp(kCommandList* pclCommandList)
{
    a_pclCommandList = pclCommandList;
}

/// Execute to screen help message
void kCommandHelp::kTask_do(const char* pcParameter)
{
    kCommandTask* pclTargetTask = nullptr;
    const char* pcNameBuffer;
    int iInterval = 0;
    int iNumEntry = 0;
    int iCursorX;
    int iCursorY;
    
    g_pclConsole->kPrintf(
    "============================================================\n");
    g_pclConsole->kPrintf(
    "                     kOdin Shell Help                       \n");
    g_pclConsole->kPrintf(
    "============================================================\n");
    
    // Find how many entries are in the command table
    iNumEntry = a_pclCommandList->kGetNumEntry();
    // Find the longest length in the command table
    iInterval = a_pclCommandList->kGetLongestCommandLength();
    
    // Print help message of each commands
    for (int iIndex = 0; iIndex < iNumEntry; iIndex++)
    {
        pclTargetTask = a_pclCommandList->kGetTask(iIndex);
        
        pcNameBuffer = pclTargetTask->kTask_getName();
        
        g_pclConsole->kPrintf("%s", pcNameBuffer);
        g_pclConsole->kGetCursor(&iCursorX, &iCursorY);
        g_pclConsole->kSetCursor(iInterval, iCursorY);
        g_pclConsole->kPrintf("  - ");
        
        pclTargetTask->kTask_help();
        g_pclConsole->kPrintf("\n");
    };
    
    return;
}