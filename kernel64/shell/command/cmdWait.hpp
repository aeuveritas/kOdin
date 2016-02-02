#pragma once

#include "commandTask.hpp"

/// Command to wait [IA-32e Mode]
class kCommandWait: public kCommandTask
{
public:
    void kTask_do(const char* pcParameter) override;
    
    kCommandWait(void);
    ~kCommandWait(void);
    
    void kInitializeCommandWait(void);
};