#pragma once

#include "descriptionForSegment.hpp"
#include "descriptionForInterrupt.hpp"

#pragma pack(push, 1)

extern "C" 
{
    void _kLoadTR(WORD wTSSSegmentOffset);
};

/// Task Statiement Struce [IA-32e Mode]
class kTSS
{
    TSS* pstTSS;
    GDTENTRY16* pstGDTEntry16;
    
    void kSetGDTEntry16(GDTENTRY16* pstEntry, QWORD qwBaseAddress,
                        DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                        BYTE bType);
    
public:
    kTSS(void);
    ~kTSS(void);
    
    void kInitializeTSS(void);
    
    void kLoadTR(WORD wTSSSegmentOffset);
    
    void kSetTSSAddress(GDTENTRY8* pstGDTEntry8);
};

#pragma pack(pop)