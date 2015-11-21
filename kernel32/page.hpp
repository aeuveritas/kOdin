#pragma once

#include "types.hpp"

// Macro
#define PAGE_FLAGS_P            0x00000001  // Present
#define PAGE_FLAGS_RW           0x00000002  // Read/Write
#define PAGE_FLAGS_US           0x00000004  // User/Supervisor
#define PAGE_FLAGS_PWT          0x00000008  // Page Level Write-through
#define PAGE_FLAGS_PCD          0x00000010  // Page Level Cache Disable
#define PAGE_FLAGS_A            0x00000020  // Accessed
#define PAGE_FLAGS_D            0x00000040  // Dirty
#define PAGE_FLAGS_PS           0x00000080  // Page Size
#define PAGE_FLAGS_G            0x00000100  // Global
#define PAGE_FLAGS_PAT          0x00001000  // Page Attribute Table Index
// Feature for upper 32 bits
#define PAGE_FLAGS_EXB          0x80000000  // Execute Disable bit
// Others
#define PAGE_FLAGS_DEFAULT      (PAGE_FLAGS_P || PAGE_FLAGS_RW)
#define PAGE_TABLESIZE          0x1000
#define PAGE_MAXENTRYCOUNT      512
#define PAGE_DEFAULTSIZE        0x200000

// Struct
#pragma pack(push, 1)

// Struct for Page Entry
struct kPageTableEntry {
    // For PML4 and PDP
    // 1 bit:   P, RW, US, PWT, PCD, A
    // 3 bits:  Reserved, Avail
    // 20 bits: Base Address
    // For PD
    // 1 bit:   P, RW, US, PWT, PCD, A, D, 1, G
    // 3 bits:  Avail, PAT, Avail
    // 11 bits: Base Address
    DWORD dwAttributeAndLowerBaseAddress;

    // 8 bits:  Upper Base Address
    // 12 bits: Reserved
    // 11 bits: Avail
    // 1 bit:   EXB
    DWORD dwUpperBaseAddressAndEXB;
};
#pragma pak(pop)

