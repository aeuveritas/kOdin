#include "memory.hpp"

// Initialize kernel area for IA-32e with 0
bool kMemory::kInitializeKernel64Area(void)
{
    DWORD* pdwCurrentAddress;

    // Start point of initialization, 1 MB
    pdwCurrentAddress = (DWORD*) 0x100000;

    // Until 6 MB, initialize every 4 byte with 0
    while ((DWORD)pdwCurrentAddress < 0x600000) {
        *pdwCurrentAddress = 0x00;

        // After writing, check the written value.
        // If it is not the same, there is a problem.
        if (*pdwCurrentAddress != 0) {
            return false;
        }

        // Move to the next address
        pdwCurrentAddress++;
    }

    return true;
}

// Check the size of memory is larget than the minimum
bool kMemory::kIsMemoryEnough(void)
{
    DWORD* pdwCurrentAddress;

    // From 0x100000 (= 1MB)
    pdwCurrentAddress = (DWORD*) 0x100000;

    // Util 64 MB, check the memory
    while ((DWORD)pdwCurrentAddress < 0x4000000) {
        // Write an temporary value
        *pdwCurrentAddress = 0x12345678;

        // Read the address,
        // and if the value is not the same as what I write,
        // there is a a problem
        if (*pdwCurrentAddress != 0x12345678) {
            return false;
        }

        // Move to the next 1 MB
        pdwCurrentAddress += (0x100000 / 4);
    }

    return true;
}

void kMemory::kInitializePageManager(void)
{
    clPM.kInitPage();
}