#include "stringHelper.hpp"
#include "memory.hpp"
#include "console.hpp"

extern kMemory* g_pclMemory;
extern kConsole* g_pclConsole;

/// Constructor of kStringModifier
kStringHelper::kStringHelper(void)
{

}

/// Destructor of kStringModifier
kStringHelper::~kStringHelper(void)
{

}

/// Ininitialize kInitializeStringHelper
void kStringHelper::kInitializeStringHelper(void)
{

}

/// Check the length of the string
int kStringHelper::kStrLen(const char* pcBuffer)
{
    int iIndex =0;
    
    if (pcBuffer == nullptr)
    {
        return -1;
    }
    
    for (iIndex = 0; ; iIndex++)
    {
        if (pcBuffer[iIndex] == '\0')
        {
            break;
        }
    }
    
    return iIndex;
}

/// Translate ASCII to Integer
long kStringHelper::kAToI(const char* pcBuffer, kDECIMALTYPE _type)
{
    long lReturn;
    
    switch (_type)
    {
    // Hexadecimal
    case HEXADECIMAL:
        lReturn = kHexStringToQword(pcBuffer);
        break;  
    // Decimal or others
    case DECIMAL:
    default :
        lReturn = kDecimalStringToLong(pcBuffer);
        break;
    }
    
    return lReturn;
}

/// Translate hexadecimal string to QWORD
QWORD kStringHelper::kHexStringToQword(const char* pcBuffer)
{
    QWORD qwValue = 0;
        
    for (int iBufferIndex = 0; pcBuffer[iBufferIndex] != '\0'; iBufferIndex++)
    {
        qwValue *= 16;
        
        if (('A' <= pcBuffer[iBufferIndex]) && (pcBuffer[iBufferIndex] <= 'F'))
        {
            qwValue += (pcBuffer[iBufferIndex] - 'A') + 10;
        }
        else if (('a' <= pcBuffer[iBufferIndex]) && (pcBuffer[iBufferIndex] <= 'f'))
        {
            qwValue += (pcBuffer[iBufferIndex] - 'a') + 10;
        }
        else if (('0' <= pcBuffer[iBufferIndex]) && (pcBuffer[iBufferIndex] <= '9'))
        {
            qwValue += pcBuffer[iBufferIndex] - '0';
        }
        else
        {
            return 0;
        }
    }

    return qwValue;
}

/// Translate decimal string to long
long kStringHelper::kDecimalStringToLong(const char* pcBuffer)
{
    long lValue = 0;
    int iIndex = 0;
    bool isNegative = false;
    
    // Check the value is negative or not
    if (pcBuffer[0] == '-')
    {
        isNegative = true;
        iIndex = 1;
    }
    
    // Traverse the string and translate it
    for ( ; pcBuffer[iIndex] != '\0'; iIndex++)
    {
        lValue *= 10;
        lValue += pcBuffer[iIndex] - '0';
    }
    
    if (isNegative == true)
    {
        lValue = -lValue;
    }
    
    return lValue;
}

/// Translate integer to ASCII code
int kStringHelper::kIToA(long lValue, char* pcBuffer, kDECIMALTYPE _type)
{
    int iReturn = 0;
    
    switch(_type)
    {
        // Hexadecimal
        case HEXADECIMAL:
            iReturn = kHexToString(lValue, pcBuffer);
            break;
        case DECIMAL:
        default:
            iReturn = kDecimalToString(lValue, pcBuffer);
            break;
    }
    
    return iReturn;
}

/**
 * Translate hexadecimal number to string
 * Return the length of the output string
 **/
int kStringHelper::kHexToString(QWORD qwValue, char* pcBuffer)
{
    QWORD qwIndex = 0;
    QWORD qwCurrentValue = 0;
    
    // if the input is 0, return '0' directly.
    if (qwValue == 0)
    {
        pcBuffer[0] = '0';
        pcBuffer[1] = '\0';
        return 1;
    }
    
    // Store translated data to the buffer
    // The order is 1, 16, 256, ...
    for ( ; qwValue > 0; qwIndex++)
    {
        qwCurrentValue = qwValue % 16;
        
        if (qwCurrentValue >= 10)
        {
            pcBuffer[qwIndex] = 'A' + (qwCurrentValue - 10);
        }
        else
        {
            pcBuffer[qwIndex] = '0' + qwCurrentValue;
        }
        
        qwValue = qwValue / 16;
    }
    
    pcBuffer[qwIndex] = '\0';
    
    // Reverse the order
    kReverseString(pcBuffer);
    
    return qwIndex;
}

/**
 * Translate decimal number to string
 * Return the length of the output string
 **/
int kStringHelper::kDecimalToString(long lValue, char* pcBuffer)
{
    long lIndex = 0;
    bool isNegative = false;
    
    // if the input is 0, return '0' directly.
    if (lValue == 0)
    {
        pcBuffer[0] = '0';
        pcBuffer[1] = '\0';
        return 1;
    }
    
    // If the number is negative,
    // insert '-' to the output buffer and change the number to positive
    if (lValue < 0)
    {
        lIndex = 1;
        pcBuffer[0] = '-';
        lValue = -lValue;
    }
    else
    {
        lIndex = 0;
    }
    
    // Store translated data to the buffer
    // The order is 1, 10, 100, ...
    for ( ; lValue > 0; lIndex++)
    {
        pcBuffer[lIndex] = '0' + (lValue % 10);
        lValue = lValue / 10;
    }
    
    pcBuffer[lIndex] = '\0';
    
    // Reverse the order
    // If the number is negative,
    // skip the negative symbol
    if (isNegative == true)
    {
        kReverseString(&(pcBuffer[1]));
    }
    else
    {
        kReverseString(pcBuffer);
    }
    
    return lIndex;
}

/// Reverse the string
void kStringHelper::kReverseString(char* pcBuffer)
{
    int iLength = 0;
    int iBufferIndex = 0;
    char cTemp = 0;
    
    // Change left and right charaters
    iLength = kStrLen(pcBuffer);
    for ( ; iBufferIndex < iLength / 2; iBufferIndex++)
    {
        cTemp = pcBuffer[iBufferIndex];
        pcBuffer[iBufferIndex] = pcBuffer[iLength - 1 - iBufferIndex];
        pcBuffer[iLength - 1 - iBufferIndex ] = cTemp;
    }
    
    return;
}

/// Make output string at the specific buffer
int kStringHelper::kSPrintf(char* pcBuffer, const char* pcFormatString, ...)
{
    va_list ap;
    int iReturn;
    
    // Extract variable arguments and put it to vsprintf()
    va_start(ap, pcFormatString);
    iReturn = kVSPrintf(pcBuffer, pcFormatString, ap);
    va_end(ap);

    return iReturn;
}

/**
 * Change format string to output string
 * TODO: Variadic Template
 **/
int kStringHelper::kVSPrintf(char* pcBuffer, const char* pcFormatString, va_list ap)
{
    QWORD qwInputIndex = 0;
    QWORD qwOutputIndex = 0;
    int iFormatLength = 0;
    int iCopyLength = 0;
    char* pcCopyString = nullptr;
    QWORD qwValue = 0;
    int iValue = 0;
    
    // Copy data from pcFormatString to pcBuffer as mush as the length of pcFormatString
    iFormatLength = kStrLen(pcFormatString);
    for ( ; qwInputIndex < iFormatLength; qwInputIndex++)
    {
        // Check the current chracter is '%'
        if (pcFormatString[qwInputIndex] == '%')
        {
            // Check the next character
            qwInputIndex++;
            switch(pcFormatString[qwInputIndex])
            {
            // Print string
            case 's':
                // Read VA and translate it to string
                pcCopyString = (va_arg(ap, char*));
                iCopyLength = kStrLen(pcCopyString);
                // Store the string to the output buffer
                // and increase the index as much as the length of the string
                g_pclMemory->kMemCpy(pcBuffer + qwOutputIndex, 
                                     pcCopyString, iCopyLength);
                qwOutputIndex += iCopyLength;
                break;
            // Print character
            case 'c':
                // Read VA and translate it to character
                // Copy it to output buffer
                // Increase the index of the output buffer
                pcBuffer[qwOutputIndex] = (char) (va_arg(ap, int));
                qwOutputIndex++;
                break;
            // Print integer
            case 'd':
            case 'i':
                // Read VA and translate it to integer
                // Copy it to output buffer
                // Increase the index of the output buffer
                iValue = (int) (va_arg(ap, int));
                qwOutputIndex += kIToA(iValue, pcBuffer + qwOutputIndex, 
                                      DECIMAL);
                break;
            // Print 4 bytes hexadecimal
            case 'x':
            case 'X':
                // Read VA and translate it to DWORD
                // Copy it to output buffer
                // Increase the index of the output buffer
                qwValue = (DWORD) (va_arg(ap, DWORD)) && 0xFFFFFFFF;
                qwOutputIndex += kIToA(qwValue, pcBuffer + qwOutputIndex, 
                                       HEXADECIMAL);
                break;
            // Print 8 bytes hexadecimal
            case 'q':
            case 'Q':
            case 'p':
                // Read VA and translate it to QWORD
                // Copy it to output buffer
                // Increase the index of the output buffer
                qwValue = (QWORD) (va_arg(ap, QWORD));
                qwOutputIndex += kIToA(qwValue, pcBuffer + qwOutputIndex, 
                                       HEXADECIMAL);
                break;
                
            // If character does not belong to any cases,
            // Skip it
            default:
                pcBuffer[qwOutputIndex] = pcFormatString[qwInputIndex];
                qwOutputIndex++;
                break;
            }
        }
        else
        {
            // Copy data and increase the index of the buffer
            pcBuffer[qwOutputIndex] = pcFormatString[qwInputIndex];
            qwOutputIndex++;
        }
    }
    
    // Add NULL to the end of the buffer
    pcBuffer[qwOutputIndex] = '\0';
    
    return qwOutputIndex;
}