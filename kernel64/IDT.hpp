#pragma once

#include "utils.hpp"
#include "dSegment.hpp"
#include "dInterrupt.hpp"
#include "asmISR.hpp"

extern kUtils* g_pclUtils;

#pragma pack(push, 1)

extern "C" 
{
    void _kLoadIDTR(QWORD qwIDTRAddress);
};

/// Class for Interrupt Descriptor Table
class kIDT
{
    DTR* pstIDTR;
    IDTENTRY* pstIDTEntry;
    
    void kSetIDTEntry(IDTENTRY* pstEntry, void (*pvHandler)(void), 
                      WORD wSelector, BYTE bIST, BYTE bFlags, BYTE bType);
    
public:
    kIDT(void);
    ~kIDT(void);
    
    void kInitializeIDT();
    
    void kLoadIDTR(QWORD qwIDTRAddress);
};

#pragma pack(pop)