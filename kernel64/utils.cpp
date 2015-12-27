#include "utils.hpp"

/// Initialize Utils
void kUtils::kInitializeUtils(DWORD offset)
{
    dwLine = offset;
    dwXIndex = 0;
    dwPairLine = 0;
    
    return;
}

/// Print string
bool kUtils::kPrintString(int iX, int iY, const char* pcString)
{
    CHARACTER* pstScreen = (CHARACTER*) 0xB8000;

    pstScreen += (iY * 80) + iX;

    for (int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharactor = pcString[i];
    }

    return true;
}

/// Print character
bool kUtils::kPrintChar(const char* pcString)
{
    kPrintString(dwXIndex++, dwLine, pcString);
}


/// Print message
bool kUtils::kPrintMessage(const char* pcString)
{
    kPrintString(0, dwLine, pcString);
    
    return true;
}

/// Print result
bool kUtils::kPrintResult(const char* pcString)
{
    kPrintString(2, dwLine++, pcString);
    
    return true;
}

/// Print pair message
bool kUtils::kPrintPairMessage(const char* pcString)
{
    dwPairLine = dwLine;
    
    kPrintString(0, dwLine++, pcString);
    
    return true;
}

/// Print pair result
bool kUtils::kPrintPairResult(const char* pcString)
{
    kPrintString(2, dwPairLine, pcString);
    
    return true;
}

/// Print exception message
void kUtils::kPrintException(const char* pcVectorNumber)
{
    kPrintString(0, 0,
        "===========================================================");
    kPrintString(0, 1, 
        "                     Exception Occur                       ");
    kPrintString(0, 2, 
        "                  Vector:                                  ");
    kPrintString(0, 3, 
        "===========================================================");
    
    kPrintString(26, 2, pcVectorNumber);
 
    return;
}

/// Print interrupt message
bool kUtils::kPrintInterrupt(const char* pcString)
{
    kPrintString(70, 0, pcString);
    
    return true;
}

/// Print keyboard interrupt message
bool kUtils::kPrintKeyboardInterrupt(const char* pcString)
{
    kPrintString(70, 1, pcString);

    return true;
}

/// Fill memory with data
void kUtils::kMemSet(void* pvDestination, unsigned char bData, int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        ((char*)pvDestination)[i] = bData;
    }

    return;
}

/// Copy value of memory
int kUtils::kMemCpy(void* pvDestination, const void* pvSource, int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        ((char*)pvDestination)[i] = ((char*)pvSource)[i];
    }
    
    return iSize;
}

/// Compare values of memory
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

/// Wait for GDB
void kUtils::kLock(void)
{
    volatile unsigned int k;

    for (k=0; k < 0xFFFFFFFF ; k++);

    return;
}