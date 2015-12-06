#pragma once

#include "utils.hpp"
#include "asmUtils.hpp"
#include "segmentDescriptor.hpp"
#include "interruptDescriptor.hpp"

extern kUtils clUtils;

#pragma pack(push, 1)

/// Class for Description Table [IA-32e Mode]
class kDT
{
    DTR* pstGDTR;
    GDTENTRY8* pstGDTEntry8;
    GDTENTRY16* pstGDTEntry16;
    TSS* pstTSS;

    DTR* pstIDTR;
    IDTENTRY* pstIDTEntry;

    void kSetGDTEntry8(GDTENTRY8* pstEntry, DWORD dwBaseAddress,
                       DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                       BYTE bType);
    void kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress,
                        DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                        BYTE bType);
    void kSetIDTEntry(IDTENTRY* pstEntry, void (*pvHandler)(), 
                      WORD wSelector, BYTE bIST, BYTE bFlags, BYTE bType);
    static void kDummyHandler(void);
    
public:
    kDT();
    ~kDT();

    void kInitializeGDT(void);
    void kInitializeTSS(void);
    void kInitializeIDT(void);
    
    void kLoadGDTR(QWORD qwGDTRAddress);
    void kLoadTR(WORD wTSSSegmentOffset);
    void kLoadIDTR(QWORD qwIDTRAddress);
};

#pragma pack(pop)
