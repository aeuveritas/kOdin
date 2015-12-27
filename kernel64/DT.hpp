#pragma once

#include "utils.hpp"
#include "GDT.hpp"
#include "IDT.hpp"

#pragma pack(push, 1)

/// Class for description table [IA-32e Mode]
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
