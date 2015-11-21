#include "pageManager.hpp"

// Initialize page tables  for IA-32e mode
void kPageManager::kInitPage(void)
{
    // Allocate PML4 table
    kSetPageTableAddress(&pstPML4T, (kPageTableEntry*)0x100000);

    // Set all enties as 0, except for the first entry
    kSetPageEntryData(&(pstPML4T[0]), 0x00, 0x101000, PAGE_FLAGS_DEFAULT, 0);
    for (int i = 1; i < PAGE_MAXENTRYCOUNT; i++) {
        kSetPageEntryData(&(pstPML4T[i]), 0, 0, 0, 0);
    }

    // Allocate PDP table
    kSetPageTableAddress(&pstPDPT, (kPageTableEntry*)0x101000);

    // Set 64 entries to handle up to 64 GB
    // The others are set as 0
    for (int i = 0; i < 64; i++) {
        kSetPageEntryData(&(pstPDPT[i]), 0, 0x102000 + (i * PAGE_TABLESIZE),
                          PAGE_FLAGS_DEFAULT, 0);
    }
    for (int i = 64; i < PAGE_MAXENTRYCOUNT; i++) {
        kSetPageEntryData(&(pstPDPT[i]), 0, 0, 0, 0);
    }

    // Allocate PD table
    kSetPageTableAddress(&pstPDT, (kPageTableEntry*)0x102000);
    int dwMappingAddress = 0;

    // One page table can handle 2 MB
    // To set 64 GB, 2 * 512 * 64 times are required
    for (int i = 0; i < PAGE_MAXENTRYCOUNT * 64; i++) {
        // Total number of bits is 64 bits
        // To access above 32 bits, use shift operation
        kSetPageEntryData(&(pstPDT[i]), (i * (PAGE_DEFAULTSIZE >> 20)) >> 12,
                          dwMappingAddress,
                          PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 0);
        dwMappingAddress += PAGE_DEFAULTSIZE;
    }

    return;
}

// Set the base address of the page tables
void kPageManager::kSetPageTableAddress(kPageTableEntry** pageTable,
                                        kPageTableEntry* address)
{
    *pageTable = address;

    return;
}

// Set base address and flags for the page entry
void kPageManager::kSetPageEntryData(
    kPageTableEntry* pstEntry,
    unsigned int dwUpperBaseAddress,
    unsigned int dwLowerBaseAddress,
    unsigned int dwLowerFlags,
    unsigned int dwUpperFlag)
{
    pstEntry->dwAttributeAndLowerBaseAddress = dwLowerBaseAddress | dwLowerFlags;
    pstEntry->dwUpperBaseAddressAndEXB =(dwUpperBaseAddress & 0xFF) | dwUpperFlag;

    return;
}
