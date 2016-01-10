#pragma once

#include "GDT.hpp"
#include "IDT.hpp"

#pragma pack(push, 1)

/// Description table [IA-32e Mode]
class kDT
{
    kGDT clGDT;
    kIDT clIDT;
    
public:
    kDT(void);
    ~kDT(void);
    
    void kInitializeDT(void);
};

#pragma pack(pop)
