#include "memory.hpp"

/// Constructor of kMemory
kMemory::kMemory(void)
{

}

/// Destructor of kMemory
kMemory::~kMemory(void)
{

}

/// Initialize kMemory
void kMemory::kInitializeMemory(void)
{

}

/// Fill memory with data
void kMemory::kMemSet(void* pvDestination, unsigned char bData, int iSize)
{
    for (int iIndex = 0; iIndex < iSize; iIndex++)
    {
        ((char*)pvDestination)[iIndex] = bData;
    }

    return;
}

/// Copy value of memory
int kMemory::kMemCpy(void* pvDestination, const void* pvSource, int iSize)
{
    for (int iIndex = 0; iIndex < iSize; iIndex++)
    {
        ((char*)pvDestination)[iIndex] = ((char*)pvSource)[iIndex];
    }
    
    return iSize;
}

/// Compare values of memory
int kMemory::kMemCmp(const void* pvDestination,
                     const void* pvSource, int iSize)
{
    char cTemp;
    
    for (int iIndex = 0; iIndex < iSize; iIndex++)
    {
        cTemp = ((char*)pvDestination)[iIndex] - ((char*)pvSource)[iIndex];
        
        if (cTemp != 0)
        {
            return (int) cTemp;
        }
    }

    return 0;
}

/// Check RAM size
void kMemory::kCheckTotalRAMSize(void)
{
    DWORD* pdwCurrentAddress;
    DWORD dwPreviousValue;
    
    // From 64MB (0x4000000), Interval is 4MB
    pdwCurrentAddress = (DWORD*) 0x4000000;
    while (1)
    {
        // Back up data
        dwPreviousValue = *pdwCurrentAddress;
        
        // Write 0x12345678 to memory and read it
        // If they are the same, the size of memory is updated at that point
        *pdwCurrentAddress = 0x12345678;
        if (*pdwCurrentAddress != 0x12345678)
        {
            break;
        }
        
        // Restore previous data
        *pdwCurrentAddress = dwPreviousValue;
        
        // Move to the next 4 MB
        pdwCurrentAddress += (0x400000 / 4);
    }
    
    // Trnasform the memory size as MB unit
    qwTotalRAMSize = (QWORD) pdwCurrentAddress / 0x100000;
}

/// Get the size of RAM
QWORD kMemory::kGetTotalRAMSize(void)
{
    return qwTotalRAMSize;
}
