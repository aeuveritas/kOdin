#pragma once

#include "descriptionForSegment.hpp"
#include "descriptionForInterrupt.hpp"
#include "descriptionTableRegister.hpp"

#pragma pack(push, 1)

extern "C" 
{
    void _kLoadGDTR(QWORD qwGDTRAddress);
    void _kLoadTR(WORD wTSSSegmentOffset);
};

/// Class for Global Descriptor Table [IA-32e Mode]
class kGDT
{
    DTR* pstGDTR;
    GDTENTRY8* pstGDTEntry8;
    GDTENTRY16* pstGDTEntry16;
    TSS* pstTSS;
    
    void kSetGDTEntry8(GDTENTRY8* pstEntry, DWORD dwBaseAddress,
                       DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                       BYTE bType);
    void kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress,
                        DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                        BYTE bType);
public:
    kGDT(void);
    ~kGDT(void);
    
    void kInitializeGDT(void);
    void kInitializeTSS(void);
    
    void kLoadGDTR(QWORD qwGDTRAddress);
    void kLoadTR(WORD wTSSSegmentOffset);
};

#pragma pack(pop)