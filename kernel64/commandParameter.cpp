#include "commandParameter.hpp"
#include "stringHelper.hpp"
#include "memory.hpp"

extern kStringHelper* g_pclStringHelper;
extern kMemory* g_pclMemory;

/// Constuctor of kCommandParameter
kCommandParameter::kCommandParameter(void)
{

}

/// Destructor of kCommandParameter
kCommandParameter::~kCommandParameter(void)
{

}

/// Initialize kCommandParameter
void kCommandParameter::kInitializeCommandParameter(const char* pcParameter)
{
    pcBuffer = pcParameter;
    iLength = g_pclStringHelper->kStrLen(pcParameter);
    iCurrentPosition = 0;
}

/**
 * Split parameter wiith space
 * Return parameter and its length
 **/
int kCommandParameter::kGetNextParameter(char* pcParameter)
{
    int iCount = 0;
    int iParameterLength = 0;
    
    // If there is no reminded parameter, exit
    if (iLength <= iCurrentPosition)
    {
        return 0;
    }
    
    // Find space
    for (iCount = iCurrentPosition; iCount < iLength; iCount++)
    {
        if (pcBuffer[iCount] == ' ')
        {
            break;
        }
    }
    
    // Copy parameter and return its length
    g_pclMemory->kMemCpy(pcParameter, pcBuffer + iCurrentPosition, iCount);
    iParameterLength = iCount - iCurrentPosition;
    pcParameter[iParameterLength] = '\0';
    
    // Update pointer of parameter
    iCurrentPosition += iParameterLength + 1;
    
    return iParameterLength;
}