#pragma once

#include "page.hpp"

// Structures
#pragma pack(push, 1)

// Class for Page Manager
class kPageManager
{
    kPageTableEntry* pstPML4T;
    kPageTableEntry* pstPDPT;
    kPageTableEntry* pstPDT;
    kPageTableEntry* pstPT;

    void kSetPageTableAddress(kPageTableEntry** pageTable,
                              kPageTableEntry* address);
    void kSetPageEntryData(
        kPageTableEntry* pstEntry,
        unsigned int dwUpperBaseAddress,
        unsigned int dwLowerBaseAddress,
        unsigned int dwLowerFlags,
        unsigned int dwUpperFlag);

public:
    void kInitPage(void);
};
#pragma pack(pop)

