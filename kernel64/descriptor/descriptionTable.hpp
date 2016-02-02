#pragma once

#include "GDT.hpp"
#include "TSS.hpp"
#include "IDT.hpp"

#pragma pack(push, 1)

/// Description table [IA-32e Mode]
class kDT
{
    kGDT clGDT;
    kTSS clTSS;
    kIDT clIDT;
    
public:
    kDT(void);
    ~kDT(void);
    
    void kInitializeDT(void);
    
    void setTSSAddress(void);
};

#pragma pack(pop)
