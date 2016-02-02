#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Command to print RAM size [IA-32e Mode]
class kCommandRamSize: public kCommandTask
{
public:
    void kTask_do(const char* pcParameterBuffer) override;
    
    kCommandRamSize(void);
    ~kCommandRamSize(void);
    
    void kInitializeCommandRamSize(void);
};

#pragma pack(pop)