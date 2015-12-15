#pragma once

#include "types.hpp"

/// Macros for IDT

/// Default macros for combinations
#define IDT_TYPE_INTERRUPT      0x0E
#define IDT_TYPE_TRAP           0x0F
#define IDT_FLAGS_DPL0          0x00
#define IDT_FLAGS_DPL1          0x20
#define IDT_FLAGS_DPL2          0x40
#define IDT_FLAGS_DPL3          0x60
#define IDT_FLAGS_P             0x80
#define IDT_FLAGS_IST0          0
#define IDT_FLAGS_IST1          1

/// Actual macros
#define IDT_FLAGS_KERNEL \
    (IDT_FLAGS_DPL0 | IDT_FLAGS_P)
#define IDT_FLAGS_USER \
    (IDT_FLAGS_DPL3 | IDT_FLAGS_P)

// Other macros

/// The number of IDT entry
#define IDT_MAXENTRYCOUNT       100
/// The start address of IDTR - after TSS
#define IDTR_STARTADDRESS \
    (GDTR_STARTADDRESS + sizeof(DTR) + \
    GDT_TABLESIZE + TSS_SEGMENTSIZE)
/// The start address of IDT
#define IDT_STARTADDRESS \
    (IDTR_STARTADDRESS + sizeof(DTR))
/// Total size of IDT
#define IDT_TABLESIZE \
    (IDT_MAXENTRYCOUNT * sizeof(IDTENTRY))
/// The start address of IST
#define IST_STARTADDRESS        0x700000
/// The size of IST
#define IST_SIZE                0x100000

#pragma pack(push, 1)

/// Structure for IDT Gate Descriptor [IA-32e Mode]
typedef struct kIDTEntryStruct 
{
    WORD wLowerBaseAddress;
    WORD wSegmentSelector;
    // 3 bits IST, 5 bits 0
    BYTE bIST;
    // 4 bits Type, 1 bit 0, 2 bits DPL, 1 bit P
    BYTE bTypeAndFlags;
    WORD wMiddleBaseAddress;
    DWORD dwUpperBaseAddress;
    DWORD dwReserved;
} IDTENTRY;

#pragma pack(pop)