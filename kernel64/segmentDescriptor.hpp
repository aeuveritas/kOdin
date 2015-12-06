#pragma once

#include "types.hpp"

/// Macros for GDT

/// Default macros for combinations
#define GDT_TYPE_CODE           0x0A
#define GDT_TYPE_DATA           0x02
#define GDT_TYPE_TSS            0x09
#define GDT_FLAGS_LOWER_S       0x10
#define GDT_FLAGS_LOWER_DPL0    0x00
#define GDT_FLAGS_LOWER_DPL1    0x20
#define GDT_FLAGS_LOWER_DPL2    0x40
#define GDT_FLAGS_LOWER_DPL3    0x60
#define GDT_FLAGS_LOWER_P       0x80
#define GDT_FLAGS_UPPER_L       0x20
#define GDT_FLAGS_UPPER_DB      0x40
#define GDT_FLAGS_UPPER_G       0x80

/// Actual macros

/// Lower flags are Code/Data/TSS, DPL0, Present.
#define GDT_FLAGS_LOWER_KERNELCODE \
    (GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
     GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_KERNELDATA \
    (GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
     GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_TSS \
    (GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_USERCODE \
    (GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
     GDT_FLAGS_DPL3 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_USERDATA \
    (GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
     GDT_FLAGS_DPL3 | GDT_FLAGS_LOWER_P)
/// Upper flags are 64 bits Code/Data and Granulaty
#define GDT_FLAGS_UPPER_CODE \
    (GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L)
#define GDT_FLAGS_UPPER_DATA \
    (GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L)
#define GDT_FLAGS_UPPER_TSS \
    (GDT_FLAGS_UPPER_G)

/// Segment descriptor offset
#define GDT_KERNELCODESEGMENT   0x08
#define GDT_KERNELDATASEGMENT   0x10
#define GDT_TSS                 0x18

/// Other macros

/// The start address of GDTR - 264 KB from 1 MB (264 KB for page table)
#define GDTR_STARTADDRESS       0x142000
/// The number of 8 bytes entry - NULL/Code/Data
#define GDT_MAXENTRY8COUNT      3
/// The number of 16 bytes entry - TSS
#define GDT_MAXENTRY16COUNT     1
/// Size of GDT
#define GDT_TABLESIZE \
    ((sizeof(GDTENTRY8) * GDT_MAXENTRY8COUNT) + \
    (sizeof(GDTENTRY16) * GDT_MAXENTRY16COUNT))
/// Size of TSS
#define TSS_SEGMENTSIZE \
    (sizeof(TSS))

#pragma pack(push, 1)

/// structures for descriptor table register, GDTR and IDTR
typedef struct kDTRStruct
{
    WORD wLimit;
    QWORD qwBaseAddress;
    // Address padding
    WORD wPadding;
    DWORD dwPadding;
} DTR;

/// 8 bytes GDT entry
typedef struct kGDTEntry8Struct
{
    WORD wLowerLimit;
    WORD wLowerBaseAddress;
    BYTE bUpperBaseAddress1;
    // 4 bits Type, 1 bit S, 2 bis DPL, 1 bit P
    BYTE bTypeAdnLowerFlag;
    // 4 bits Segment Limit, 1 bit AVL, L, D/B, G
    BYTE bUpperLimitAndUpperFlag;
    BYTE bUpperBaseAddress2;
} GDTENTRY8;

/// 16 bytes GDT entry
typedef struct kGDTEntry16Struct
{
    WORD wLowerLimit;
    WORD wLowerBaseAddress;
    BYTE bMiddleBaseAddress1;
    // 4 bits Type, 1 bit 0, 2 bits DPL, 1 bit P
    BYTE bTypeAdnLowerFlag;
    // 4 bits Segment Limit, 1 bit AVL, 0, 0, G
    BYTE bUpperLimitAndUpperFlag;
    BYTE bMiddleBaseAddress2;
    DWORD dwUpperBaseAddress;
    DWORD dwReserved;
} GDTENTRY16;

/// TSS data structure
typedef struct kTSSStruct
{
    DWORD dwReserved1;
    QWORD qwRsp[3];
    QWORD qwReservce2;
    QWORD qwIST[7];
    QWORD qwReserved3;
    WORD wReserved;
    WORD wIOMapBaseAddress;
} TSS;

#pragma pack(pop)
    