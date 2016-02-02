#include "GDT.hpp"

/// Constructor of GDT
kGDT::kGDT(void)
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
}

/// Destructor of GDT
kGDT::~kGDT(void)
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
}

/// Initialize kGDT
void kGDT::kInitializeGDT(void)
{
    // Set GDTR
    pstGDTR = (DTR*)GDTR_STARTADDRESS;
    // Set GDT information
    pstGDTEntry8 = (GDTENTRY8*)(GDTR_STARTADDRESS + sizeof(DTR));
    pstGDTR->qwBaseAddress = (QWORD)pstGDTEntry8;
    pstGDTR->wLimit = GDT_TABLESIZE - 1;
    
    // Segment descriptors: NULL, Code, Data, TSS
    kSetGDTEntry8(&(pstGDTEntry8[0]), 0, 0, 0, 0, 0);
    kSetGDTEntry8(&(pstGDTEntry8[1]), 0, 0xFFFFF, GDT_FLAGS_UPPER_CODE,
                  GDT_FLAGS_LOWER_KERNELCODE, GDT_TYPE_CODE);
    kSetGDTEntry8(&(pstGDTEntry8[2]), 0, 0xFFFFF, GDT_FLAGS_UPPER_DATA,
                  GDT_FLAGS_LOWER_KERNELDATA, GDT_TYPE_DATA);
    
    return;
}

/** 
  * Set 8 bytes GDT entry
  * NULL, Code and Data segment descriptor
  */
void kGDT::kSetGDTEntry8(GDTENTRY8* pstEntry, DWORD dwBaseAddress, 
                       DWORD dwLimit, BYTE bUpperFlags,
                       BYTE bLowerFlags, BYTE bType)
{
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = dwBaseAddress & 0xFFFF;
    pstEntry->bUpperBaseAddress1 = (dwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAndLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0xFF) | 
                                         bUpperFlags;
    pstEntry->bUpperBaseAddress2 = (dwBaseAddress >> 24) & 0xFF;
    
    return;
}

/// Upload GDT
void kGDT::kLoadGDTR(QWORD qwGDTRAddress)
{
    _kLoadGDTR(qwGDTRAddress);
}

/// Read GDTEntry8 address
GDTENTRY8* kGDT::kGetGDTEntry8(void)
{
    return pstGDTEntry8;
}
