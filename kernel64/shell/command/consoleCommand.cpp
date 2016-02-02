#include "consoleCommand.hpp"
#include "console.hpp"
#include "memoryHelper.hpp"
#include "stringHelper.hpp"

extern kConsole* g_pclConsole;
extern kMemoryHelper* g_pclMemoryHelper;
extern kStringHelper* g_pclStringHelper;

/// Constructor of kConsoleCommand
kConsoleCommand::kConsoleCommand(void)
{

}

/// Destructor of kConsoleCommand
kConsoleCommand::~kConsoleCommand(void)
{

}

/// Initialize kConsoleCommand
void kConsoleCommand::kInitializeConsoleCommand(void)
{
    clCommandList.kInitializeCommandList();
    
    clCommandFactory.kInitializeCommandFactory(&clCommandList);
    clCommandFactory.kUpdateCommandTable();
}

/// Parse a command and execute the command
void kConsoleCommand::kExecuteCommand(const char* pcCommandBuffer)
{
    int iCount = 0;
    int iSpaceIndex = 0;
    int iCommandBufferLength = 0;
    int iCommandLength = 0;
    int iMaxCount = 0;
    
    kCommandTask* pclTargetTask;
    
    // Split by ' ', and extract command
    iCommandBufferLength = g_pclStringHelper->kStrLen(pcCommandBuffer);
    for (iSpaceIndex = 0; iSpaceIndex < iCommandBufferLength; iSpaceIndex++)
    {
        if (pcCommandBuffer[iSpaceIndex] == ' ')
        {
            break;
         }
    }
    
    // Find command which is the same as command buffer
    iMaxCount = clCommandList.kGetNumEntry();
    for (iCount = 0; iCount < iMaxCount; iCount++)
    {
        pclTargetTask= clCommandList.kGetTask(iCount);
        
        const char* pcTargetName = pclTargetTask->kTask_getName();
        iCommandLength = g_pclStringHelper->kStrLen(pcTargetName);
        
        // Compae the length and string of them
        if ((iCommandLength == iSpaceIndex) &&
            g_pclMemoryHelper->kMemCmp(pcTargetName, pcCommandBuffer, iSpaceIndex) == 0)
        {
            pclTargetTask->kTask_do(pcCommandBuffer + iSpaceIndex + 1);
            break;
        }
    }
    
    // Can not find the command
    if (iCount >= iMaxCount)
    {
        g_pclConsole->kPrintf("%s is not found\n", pcCommandBuffer);
    }
}