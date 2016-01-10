#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Command to measure cpu speed [IA-32e Mode]
class kCommandCpuSpeed: public kCommandTask
{
public:
    void kTask_do(const char* pcParameter) override;
    
    kCommandCpuSpeed(void);
    ~kCommandCpuSpeed(void);
    
    void kInitializeCommandCpuSpeed(void);
};

#pragma pack(pop)