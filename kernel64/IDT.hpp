#pragma once

#include "descriptionForSegment.hpp"
#include "descriptionForInterrupt.hpp"
#include "descriptionTableRegister.hpp"
#include "asmISR.hpp"

#pragma pack(push, 1)

extern "C" 
{
    void _kLoadIDTR(QWORD qwIDTRAddress);
};

/// Class for Interrupt Descriptor Table [IA-32e Mode]
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