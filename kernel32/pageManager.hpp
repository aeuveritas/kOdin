#ifndef __PAGE_MANAGER_HPP__
#define __PAGE_MANAGER_HPP__

#include "page.hpp"

// Structures
#pragma pack(push, 1)

// Strructure for Page Manager
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
    void kInitPageManager(void);
};
#pragma pack(pop)

#endif /* __PAGE_MANAGER_HPP__ */
