#include "cmdRamSize.hpp"
#include "console.hpp"
#include "memoryHelper.hpp"

extern kConsole* g_pclConsole;
extern kMemoryHelper* g_pclMemoryHelper;

/// Constructor of kCommandRamSize
kCommandRamSize::kCommandRamSize(void)
{
    // Command name
    pcCommandName = "ramsize";
    
    // Help message
    pcHelp = "Show Total RAM Size";
}

/// Destructor of kCommandRamSize
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
    
    if (pcParameter == nullptr)
    {
        return;
    }
    
    iRamSize = g_pclMemoryHelper->kGetTotalRAMSize();
    
    g_pclConsole->kPrintf("Total RAM Size = %d MB\n", iRamSize);

    return;
}