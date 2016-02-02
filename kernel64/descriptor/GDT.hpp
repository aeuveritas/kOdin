#pragma once

#include "descriptionForSegment.hpp"
#include "descriptionForInterrupt.hpp"
#include "descriptionTableRegister.hpp"

#pragma pack(push, 1)

extern "C" 
{
    void _kLoadGDTR(QWORD qwGDTRAddress);
};

/// Global descriptor table [IA-32e Mode]
class kGDT
{
    DTR* pstGDTR;
    GDTENTRY8* pstGDTEntry8;
    
    void kSetGDTEntry8(GDTENTRY8* pstEntry, DWORD dwBaseAddress,
                       DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags,
                       BYTE bType);

public:
    kGDT(void);
    ~kGDT(void);
    
    void kInitializeGDT(void);
    
    void kLoadGDTR(QWORD qwGDTRAddress);
    
    GDTENTRY8* kGetGDTEntry8(void);
};

#pragma pack(pop)