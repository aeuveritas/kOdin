#pragma once

#include "types.hpp"

extern "C" {
    QWORD _kReadTSC(void);
};

class kTSC
{
public:
    kTSC(void);
    ~kTSC(void);
    
    void kInitializeTSC(void);
    
    QWORD kReadTSC(void);
};