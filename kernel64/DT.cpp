#include "DT.hpp"

/// Constructor of descriptor Table
kDT::kDT(void)
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
    pstGDTEntry16 = nullptr;
    pstTSS = nullptr;

    pstIDTR = nullptr;
    pstIDTEntry = nullptr;    
}

/// Deconstructor of descriptor Table
kDT::~kDT()
{
    pstGDTR = nullptr;
    pstGDTEntry8 = nullptr;
    pstGDTEntry16 = nullptr;
    pstTSS = nullptr;

    pstIDTR = nullptr;
    pstIDTEntry = nullptr;    
}

/// Initialize GDT entries
void kDT::kInitializeGDT(void)
{
    // Set GDTR
    pstGDTR = (DTR*)GDTR_STARTADDRESS;
    pstGDTEntry8 = (GDTENTRY8*)(GDTR_STARTADDRESS + sizeof(DTR));
    pstGDTR->wLimit = GDT_TABLESIZE - 1;
    pstGDTR->qwBaseAddress = (QWORD)pstGDTEntry8;
    
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
void kDT::kSetGDTEntry8(GDTENTRY8* pstEntry, DWORD dwBaseAddress, 
                       DWORD dwLimit, BYTE bUpperFlags,
                       BYTE bLowerFlags, BYTE bType)
{
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = dwBaseAddress & 0xFFFF;
    pstEntry->bUpperBaseAddress1 = (dwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAdnLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0xFF) | 
                                         bUpperFlags;
    pstEntry->bUpperBaseAddress2 = (dwBaseAddress >> 24) & 0xFF;
    
    return;
}

/**
  * Set 16 bytes GDT entry
  * TSS descriptor
  */
void kDT::kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress, 
                        DWORD dwLimit, BYTE bUpperFlags, 
                        BYTE bLowerFlags, BYTE bType)
{
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = qwBaseAddress & 0xFFFF;
    pstEntry->bMiddleBaseAddress1 = (qwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAdnLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0xFF) |
                                         bUpperFlags;
    pstEntry->bMiddleBaseAddress2 = (qwBaseAddress >> 24) & 0xFF;
    pstEntry->dwUpperBaseAddress = qwBaseAddress >> 32;
    pstEntry->dwReserved = 0;
    
    return;
}

/// Initialize TSS
void kDT::kInitializeTSS(void)
{
    clUtils.kMemSet(pstTSS, 0, sizeof(TSS));
    pstTSS->qwIST[0] = IST_STARTADDRESS + IST_SIZE;
    // Set OS with a larger number than the limit of TSS
    // to disable IO map
    pstTSS->wIOMapBaseAddress = 0xFFFF;
    
    return;
}

/// Initialize IDT
void kDT::kInitializeIDT(void)
{
    // Start address of IDTR
    pstIDTR = (DTR*)IDTR_STARTADDRESS;
    // Set IDT information
    pstIDTEntry = (IDTENTRY*)(IDTR_STARTADDRESS + sizeof(DTR));
    pstIDTR->qwBaseAddress = (QWORD)pstIDTEntry;
    pstIDTR->wLimit = IDT_TABLESIZE - 1;
    
    // Link 0 ~ 99 vectors to dummyHandler
    for (int i = 0; i < IDT_MAXENTRYCOUNT; i++)
    {
        kSetIDTEntry(&(pstIDTEntry[i]), kDT::kDummyHandler, 0x08, 
                     IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
}

/// Set IDT gate descriptor
void kDT::kSetIDTEntry(IDTENTRY* pstEntry, void (*pvHandler)(), 
                       WORD wSelector, BYTE bIST, BYTE bFlags, BYTE bType)
{
    pstEntry->wLowerBaseAddress = (QWORD)pvHandler & 0xFFFF;
    pstEntry->wSegmentSelector = wSelector;
    pstEntry->bIST = bIST & 0x3;
    pstEntry->bTypeAndFlags = bType | bFlags;
    pstEntry->wMiddleBaseAddress = ((QWORD)pvHandler >> 16) & 0xFFFF;
    pstEntry->dwUpperBaseAddress = (QWORD)pvHandler >> 32;
    pstEntry->dwReserved = 0;
}

/// Dummny handler for an interrupt and an exception
void kDT::kDummyHandler(void)
{
    clUtils.kPrintString(0, 0,
        "===========================================================");
    clUtils.kPrintString(0, 1, 
        "                   Dummy Handler Execute                   ");
    clUtils.kPrintString(0, 2, 
        "               Interrupt or Exception Occur                ");
    clUtils.kPrintString(0, 3, 
        "===========================================================");
    
    while(1);
}
    
void kDT::kLoadGDTR(QWORD qwGDTRAddress)
{
    _kLoadGDTR(qwGDTRAddress);
}

void kDT::kLoadTR(WORD wTSSSegmentOffset)
{
    _kLoadTR(wTSSSegmentOffset);
}

void kDT::kLoadIDTR(QWORD qwIDTRAddress)
{
    _kLoadIDTR(qwIDTRAddress);
}

