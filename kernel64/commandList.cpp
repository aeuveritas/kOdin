#include "commandList.hpp"
#include "stringHelper.hpp"

extern kStringHelper* g_pclStringHelper;

/// Constructor of kCommandList
kCommandList::kCommandList(void)
{

}

/// Destructor of kCommandList
kCommandList::~kCommandList(void)
{

}

/// Initialize kInitializeCommandList
void kCommandList::kInitializeCommandList(void)
{

}

/// Get command pointer
kCommandTask* kCommandList::kGetTask(int iIndex)
{
    return aCommandTable[iIndex].pclCommandTask;
}

/// Get the number of entries
int kCommandList::kGetNumEntry(void)
{
    return iNumEntry;
}

/// Get the longest length
int kCommandList::kGetLongestCommandLength(void)
{
    return iLongestCommandLength;
};

/// Count how many commands are 
void kCommandList::kCountCommandTableEntry(void)
{
    iNumEntry = sizeof(aCommandTable) / sizeof(SHELLCOMMAND);
    
    return;
}

/// Find the longest length in the commands
void kCommandList::kCountLongestCommandLength(void)
{
    int iLength = 0;
    int iLongestLength = 0;
    
    for (int iIndex = 0; iIndex < iNumEntry; iIndex++)
    {
        iLength = g_pclStringHelper->kStrLen(aCommandTable[iIndex].pclCommandTask->kTask_getName());
        
        if (iLength > iLongestLength)
        {
            iLongestLength = iLength;
        }
    }
    
    iLongestCommandLength = iLongestLength;
    
    return;
}

/// Register a command to the command table
bool kCommandList::kSetTask(COMMAND_TASK_TYPE _eCommandType, kCommandTask* pclTask)
{
    int iIndex = 0;
    bool bReturn = false;
    
    for (iIndex = 0; iIndex < iNumEntry; iIndex++)
    {
        if (aCommandTable[iIndex].eCommandType == _eCommandType)
        {
            aCommandTable[iIndex].pclCommandTask = pclTask;
            break;
        }
    }
    
    if (iIndex >= iNumEntry)
    {
        bReturn = false;
    }
    else
    {
        bReturn = false;
    }
    
    return bReturn;
}
