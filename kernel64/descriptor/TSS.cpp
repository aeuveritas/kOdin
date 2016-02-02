#include <memoryHelper.hpp>
#include "TSS.hpp"


extern kMemoryHelper* g_pclMemoryHelper;

/// Constructor of TSS
kTSS::kTSS(void)
{
    pstTSS = nullptr;
}

/// Destructor of kTSS
kTSS::~kTSS(void)
{
    pstTSS = nullptr;
}

/// Initialize TSS
void kTSS::kInitializeTSS(void)
{
    g_pclMemoryHelper->kMemSet(pstTSS, 0, sizeof(TSS));
    pstTSS->qwIST[0] = IST_STARTADDRESS + IST_SIZE;
    // Set OS with a larger number than the limit of TSS
    // to disable IO map
    pstTSS->wIOMapBaseAddress = 0xFFFF;
    
    return;
}

/// Upload TSS
void kTSS::kLoadTR(WORD wTSSSegmentOffset)
{
    _kLoadTR(wTSSSegmentOffset);
}

/**
  * Set 16 bytes GDT entry
  * TSS descriptor
  */
void kTSS::kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress, 
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

/// Set TSS address
void kTSS::kSetTSSAddress(GDTENTRY8* pstGDTEntry8)
{
    // set TSS
    pstTSS = (TSS*)((QWORD)pstGDTEntry8 + GDT_TABLESIZE);
    
    kSetGDTEntry16((GDTENTRY16*)&(pstGDTEntry8[3]), (QWORD)pstTSS,
                   sizeof(TSS) - 1, GDT_FLAGS_UPPER_TSS,
                   GDT_FLAGS_LOWER_TSS, GDT_TYPE_TSS);
}
