#include "cmdStringToDecimalHex.hpp"
#include "commandParameter.hpp"
#include "console.hpp"
#include "memoryHelper.hpp"
#include "stringHelper.hpp"

extern kConsole* g_pclConsole;
extern kMemoryHelper* g_pclMemoryHelper;
extern kStringHelper* g_pclStringHelper;

/// Constructor of kCommandStringToDecimalHex
kCommandStringToDecimalHex::kCommandStringToDecimalHex(void)
{
    // Command name
    pcCommandName = "strtod";
    
    // Help message
    pcHelp = "Convert string to decimal/hex";
}

/// Destructor of kCommandStringToDecimalHex
kCommandStringToDecimalHex::~kCommandStringToDecimalHex(void)
{

}

/// Initialize kCommandStringToDecimalHex
void kCommandStringToDecimalHex::kInitializeCommandStringToDecimalHex(void)
{

}

/// Execute to convert string to number
void kCommandStringToDecimalHex::kTask_do(const char* pcParameter)
{
    char caParameter[100];
    int iLength;
    kCommandParameter clCommandParameter;
    int iCount = 0;
    long lValue = 0;
    
    if (pcParameter == nullptr)
    {
        return;
    }
    
    // Initialize parameter
    clCommandParameter.kInitializeCommandParameter(pcParameter);
    
    while (1)
    {
        // Get next parameter
        // If the length of the parameter is 0, exit
        iLength = clCommandParameter.kGetNextParameter(caParameter);
        if (iLength == 0)
        {
            break;
        }
        
        // Print information of the parameter
        // Check it is decimal or hexadecimal
        // Then, print it as its type
        g_pclConsole->kPrintf("Param %d = '%s', Length = %d, ", iCount + 1, caParameter, iLength);
        
        // IF the parameter is started with "0x", it is hexadeimal
        // If not, it is assumed as decimal
        if (g_pclMemoryHelper->kMemCmp(caParameter, "0x", 2) == 0)
        {
            lValue = g_pclStringHelper->kAToI(caParameter + 2, HEXADECIMAL);
            g_pclConsole->kPrintf("HEX Value = %q\n", lValue);
        }
        else
        {
            lValue = g_pclStringHelper->kAToI(caParameter, DECIMAL);
            g_pclConsole->kPrintf("DEC Value = %d\n", lValue);
        }
        
        iCount++;
    }
    
    return;
}