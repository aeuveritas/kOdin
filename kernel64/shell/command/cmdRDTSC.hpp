#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Command to read TSC [IA-32e Mode]
class kCommandRDTSC: public kCommandTask
{
public:
    void kTask_do(const char* pcParameter) override;
    
    kCommandRDTSC(void);
    ~kCommandRDTSC(void);
    
    void kInitializeCommandRDTSC(void);
};

#pragma pack(pop)