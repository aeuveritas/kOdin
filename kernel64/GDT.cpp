#include "GDT.hpp"

extern kUtils* g_pclUtils;

/// Constructor of GDT
kGDT::kGDT(void): kDT()
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
    pstGDTEntry16 = nullptr;
    pstTSS = nullptr;
}

/// Deconstructor of GDT
kGDT::~kGDT(void)
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
    pstGDTEntry16 = nullptr;
    pstTSS = nullptr;
}

/// Initialize GDT entries
void kGDT::kInitializeGDT(void)
{
    // Set GDTR
    pstGDTR = (DTR*)GDTR_STARTADDRESS;
    // Set GDT information
    pstGDTEntry8 = (GDTENTRY8*)(GDTR_STARTADDRESS + sizeof(DTR));
    pstGDTR->qwBaseAddress = (QWORD)pstGDTEntry8;
    pstGDTR->wLimit = GDT_TABLESIZE - 1;
    
    // set TSS
    pstTSS = (TSS*)((QWORD)pstGDTEntry8 + GDT_TABLESIZE);
    
    // Segment descriptors: NULL, Code, Data, TSS
    kSetGDTEntry8(&(pstGDTEntry8[0]), 0, 0, 0, 0, 0);
    kSetGDTEntry8(&(pstGDTEntry8[1]), 0, 0xFFFFF, GDT_FLAGS_UPPER_CODE,
                  GDT_FLAGS_LOWER_KERNELCODE, GDT_TYPE_CODE);
    kSetGDTEntry8(&(pstGDTEntry8[2]), 0, 0xFFFFF, GDT_FLAGS_UPPER_DATA,
                  GDT_FLAGS_LOWER_KERNELDATA, GDT_TYPE_DATA);
    kSetGDTEntry16((GDTENTRY16*)&(pstGDTEntry8[3]), (QWORD)pstTSS,
                   sizeof(TSS) - 1, GDT_FLAGS_UPPER_TSS,
                   GDT_FLAGS_LOWER_TSS, GDT_TYPE_TSS);
    
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

/**
  * Set 16 bytes GDT entry
  * TSS descriptor
  */
void kGDT::kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress, 
                        DWORD dwLimit, BYTE bUpperFlags, 
                        BYTE bLowerFlags, BYTE bType)
{
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = qwBaseAddress & 0xFFFF;
    pstEntry->bMiddleBaseAddress1 = (qwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAndLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0xFF) |
                                         bUpperFlags;
    pstEntry->bMiddleBaseAddress2 = (qwBaseAddress >> 24) & 0xFF;
    pstEntry->dwUpperBaseAddress = qwBaseAddress >> 32;
    pstEntry->dwReserved = 0;
    
    return;
}

/// Initialize TSS
void kGDT::kInitializeTSS(void)
{
    g_pclUtils->kMemSet(pstTSS, 0, sizeof(TSS));
    pstTSS->qwIST[0] = IST_STARTADDRESS + IST_SIZE;
    // Set OS with a larger number than the limit of TSS
    // to disable IO map
    pstTSS->wIOMapBaseAddress = 0xFFFF;
    
    return;
}

void kGDT::kLoadGDTR(QWORD qwGDTRAddress)
{
    _kLoadGDTR(qwGDTRAddress);
}

void kGDT::kLoadTR(WORD wTSSSegmentOffset)
{
    _kLoadTR(wTSSSegmentOffset);
}