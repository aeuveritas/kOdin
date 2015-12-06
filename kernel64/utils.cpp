#include "utils.hpp"

/// Print message
bool kUtils::kPrintString(int iX, int iY, const char* pcString)
{
    CHARACTER* pstScreen = (CHARACTER*) 0xB8000;

    pstScreen += (iY * 80) + iX;

    for (int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharactor = pcString[i];
    }

    return true;
}

// Fill memory with data
void kUtils::kMemSet(void* pvDestination, unsigned char bData, int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        ((char*)pvDestination)[i] = bData;
    }

    return;
}

// Copy value of memory
int kUtils::kMemCpy(void* pvDestination, const void* pvSource, int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        ((char*)pvDestination)[i] = ((char*)pvSource)[i];
    }
    
    return iSize;
}

// Compare values of memory
int kUtils::kMemCmp(const void* pvDestination, const void* pvSource, int iSize)
{
    char cTemp;
    
    for (int i = 0; i < iSize; i++)
    {
        cTemp = ((char*)pvDestination)[i] - ((char*)pvSource)[i];
        
        if (cTemp != 0)
        {
            return (int) cTemp;
        }
    }
    
    return 0;
}

