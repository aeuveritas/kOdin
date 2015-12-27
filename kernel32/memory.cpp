#include "memory.hpp"

/// Initialize kernel area for IA-32e with 0
bool k32Memory::kInitializeKernel64Area(void)
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

/// Check the size of memory is larget than the minimum
bool k32Memory::kIsMemoryEnough(void)
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

/// Copy IA-32e mode kernel to 0x200000 (= 2 MB)
void k32Memory::kCopyKernel64ImageTo2MB(void)
{
    WORD wKernel32SectorCount;
    WORD wTotalKernelSectorCount;
    DWORD* pdwSourceAddress;
    DWORD* pdwDestinationAddress;

    // Read the number of total sectors from 0x7C05
    wTotalKernelSectorCount = *((WORD*) 0x7C05);

    // Read the number of protected mode kernel sectors
    wKernel32SectorCount = *((WORD*) 0x7C07);

    pdwSourceAddress = (DWORD*)(0x10000 + wKernel32SectorCount * 512);
    pdwDestinationAddress = (DWORD*) 0x200000;

    // Copy IA-32e mode kernel sectors as the size
    for (int i = 0; i < 512 * (wTotalKernelSectorCount - wKernel32SectorCount) / 4; i++) {
        *pdwDestinationAddress = *pdwSourceAddress;
        pdwDestinationAddress++;
        pdwSourceAddress++;
    }
}

/// Initialize page manager
void k32Memory::kInitializePageManager(void)
{
    clPM.kInitPage();
}