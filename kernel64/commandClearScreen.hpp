#pragma once

#include "commandTask.hpp"

#pragma pack(push, 1)

/// Class for command to clear screen [IA-32e Mode]
class kCommandClearScreen: public kCommandTask
{
public:
    void kTask_do(const char* pcParameterBuffer) override;
    
    kCommandClearScreen(void);
    ~kCommandClearScreen(void);
    
    void kInitializeCommandClearScreen(void);
};

#pragma pack(pop)