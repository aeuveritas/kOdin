#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Command to reboot [IA-32e Mode]
class kCommandReboot: public kCommandTask
{
public:
    void kTask_do(const char* pcParameterBuffer) override;
    
    kCommandReboot(void);
    ~kCommandReboot(void);
    
    void kInitializeCommandReboot(void);
};

#pragma pack(pop)