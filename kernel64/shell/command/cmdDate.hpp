#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Command to read TSC [IA-32e Mode]
class kCommandDate: public kCommandTask
{
public:
    void kTask_do(const char* pcParameter) override;
    
    kCommandDate(void);
    ~kCommandDate(void);
    
    void kInitializeCommandDate(void);
};

#pragma pack(pop)