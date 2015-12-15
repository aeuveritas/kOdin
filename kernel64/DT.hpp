#pragma once

#include "utils.hpp"
#include "dSegment.hpp"
#include "dInterrupt.hpp"

#pragma pack(push, 1)

/// Class for description table [IA-32e Mode]
class kDT
{
protected:
    kDT(void);
    ~kDT(void);
    
    void kInitializeDT(void);
};

#pragma pack(pop)
