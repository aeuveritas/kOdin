#pragma once

#include "page.hpp"

// Structures
#pragma pack(push, 1)

// Class for Page Manager [Protected Mode]
class k32PageManager
{
    PTE* pstPML4T;
    PTE* pstPDPT;
    PTE* pstPDT;
    PTE* pstPT;

    void kSetPageTableAddress(PTE** pageTable, PTE* address);
    void kSetPageEntryData(
        PTE* pstEntry,
        unsigned int dwUpperBaseAddress,
        unsigned int dwLowerBaseAddress,
        unsigned int dwLowerFlags,
        unsigned int dwUpperFlag);

public:
    void kInitPage(void);
};
#pragma pack(pop)

