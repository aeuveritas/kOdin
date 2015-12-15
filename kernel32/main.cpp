#include "types.hpp"
#include "utils.hpp"
#include "memory.hpp"
#include "cpu.hpp"

void main(void)
{
    DWORD dwLine;
    DWORD dwEAX, dwEBX, dwECX, dwEDX;
    char cVendorString[13] = {0, };

    kMemory clMem;
    kUtils clUtils;
    kCpu clCpu;

    dwLine = 3;

    clUtils.kPrintString(0, dwLine++,
                         "[ PASS ]  Start Protected Mode C++ Language Kernel");

    // Check the memory is larger than the minimum size
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Check Minimum Memory Size");
    if (clMem.kIsMemoryEnough() == false) {
        clUtils.kPrintString(2, dwLine++, "FAIL");
        clUtils.kPrintString(0, dwLine,
                         "Not Enough Memory!! Over 64 MB is required!!");

        while (1);
    } else {
        clUtils.kPrintString(2, dwLine++,
                           "PASS");
    }

    // Initialize kernel area for IA-32e mode
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Initialize IA-32e Kernel Area");
    if (clMem.kInitializeKernel64Area() == false) {
        clUtils.kPrintString(2, dwLine++,
                           "FAIL");
        clUtils.kPrintString(0, dwLine,
                         "Kernel Area initialization Fail!!");

        while (1);
    }
    clUtils.kPrintString(2, dwLine++,
                           "PASS");

    // Create the page tables for IA-32e mode
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Initialize IA-32e Page Tables");
    clMem.kInitializePageManager();
    clUtils.kPrintString(2, dwLine++,
                           "PASS");

    // Read information of processor vendor
    clCpu.kReadCPUID(0x00, &dwEAX, &dwEBX, &dwECX, &dwEDX);
    *(DWORD*)cVendorString = dwEBX;
    *((DWORD*)cVendorString + 1) = dwEDX;
    *((DWORD*)cVendorString + 2) = dwECX;
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Processor Vendor Message - ");
    clUtils.kPrintString(2, dwLine,
                           "PASS");
    clUtils.kPrintString(38, dwLine++, cVendorString);

    // Check 64 bits mode available
    clCpu.kReadCPUID(0x80000001, &dwEAX, &dwEBX, &dwECX, &dwEDX);
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Check 64 bits Mode Support");
    if (dwEDX & (1 << 29)) {
        clUtils.kPrintString(2, dwLine++,
                           "PASS");
    } else {
        clUtils.kPrintString(2, dwLine++,
                           "FAIL");
        clUtils.kPrintString(0, dwLine,
                         "This processor does not support 64 bits mode");

        while (1);
    }

    // Copy IA-32e mode kernel to 0x200000 (= 2 MB)
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Copy IA-32e Kernel To 2M Address");
    clMem.kCopyKernel64ImageTo2MB();
    clUtils.kPrintString(2, dwLine++,
                           "PASS");

    // Switch to the IA-32e mode
    clUtils.kPrintString(0, dwLine,
                         "[      ]  Switch to IA-32e Mode");
    clCpu.kSwitchAndExecute64bitsKernel();

    clUtils.kPrintString(2, dwLine,
                           "FAIL");
    while (1);
}


