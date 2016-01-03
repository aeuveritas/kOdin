#include "commandRamSize.hpp"
#include "console.hpp"
#include "memory.hpp"

extern kConsole* g_pclConsole;
extern kMemory* g_pclMemory;

/// Constructor of kCommandRamSize
kCommandRamSize::kCommandRamSize(void)
{
    // Command Name
    pcCommandName = "ramsize";
    
    // Help message
    pcHelp = "Show Total RAM Size\n";
}

/// Deconstructor of kCommandRamSize
kCommandRamSize::~kCommandRamSize(void)
{

}

/// Initialize kCommandRamSize
void kCommandRamSize::kInitializeCommandRamSize(void)
{

}

/// Execute to print RAM size
void kCommandRamSize::kTask_do(const char* pcParameter)
{
    int iRamSize;
    
    iRamSize = g_pclMemory->kGetTotalRAMSize();
    
    g_pclConsole->kPrintf("Total RAM Size = %d MB\n", iRamSize);

    return;
}